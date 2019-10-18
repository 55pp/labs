#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/ip.h>

static struct nf_hook_ops nfho_in;
struct sk_buff* sock_buff_in;
struct udphdr* udp_header_in;
struct iphdr* ip_header_in;

static struct nf_hook_ops nfho_out;
struct sk_buff* sock_buff_out;
struct udphdr* udp_header_out;
struct iphdr* ip_header_out;

int output_packets = 0;
int input_packets = 0;

void print_packet(struct sk_buff* skb)
{
	int dadd;
	int sadd;
	int bit1;
	int bit2;
	int bit3;
	int bit4;
	unsigned int src_port;
	unsigned int dst_port;
	struct tcphdr* tcp_header;
	struct iphdr* ip_header = (struct iphdr*) skb_network_header(skb);
	
	dadd = ip_header->daddr;
	sadd = ip_header->saddr;
	
	tcp_header = (struct tcphdr*)((__u32*)ip_header + ip_header->ihl);
	src_port = (unsigned int) ntohs(tcp_header->source);
	dst_port = (unsigned int) ntohs(tcp_header->dest);
	
	bit1 = 255 & sadd;
	bit2 = (0xff00 & sadd) >> 8;
	bit3 = (0xff0000 & sadd) >> 16;
	bit4 = (0xff000000 & sadd) >> 24;
	printk(" %d.%d.%d.%d: %u -> ", bit1, bit2, bit3, bit4, src_port);
	//printk(" %pI4 ->", &ip_header->saddr);
	
	bit1 = 255 & dadd;
	bit2 = (0xff00 & dadd) >> 8;
	bit3 = (0xff0000 & dadd) >> 16;
	bit4 = (0xff000000 & dadd) >> 24;
	printk("-> %d.%d.%d.%d: %u", bit1, bit2, bit3, bit4, dst_port);
}

unsigned int hook_func_in(void* priv, struct sk_buff* skb, const struct nf_hook_state* state)
{
	sock_buff_in = skb;
	ip_header_in = (struct iphdr*)skb_network_header(sock_buff_in);
	if(!sock_buff_in)
		return NF_ACCEPT;
	if(ip_header_in->protocol == IPPROTO_UDP){
		udp_header_in = (struct udphdr*)skb_transport_header(sock_buff_in);
		++input_packets;
		print_packet(skb);
		printk(KERN_INFO "Input: %d Output: %d All: %d\n", input_packets, output_packets, (input_packets + output_packets));
		return NF_ACCEPT;
	}
	return NF_ACCEPT;
}

unsigned int hook_func_out(void* priv, struct sk_buff* skb, const struct nf_hook_state* state)
{
	sock_buff_out = skb;
	ip_header_out = (struct iphdr*)skb_network_header(sock_buff_out);
	if(!sock_buff_out)
		return NF_ACCEPT;
	if(ip_header_out->protocol == IPPROTO_UDP){
		udp_header_out = (struct udphdr*)skb_transport_header(sock_buff_out);
		++output_packets;
		print_packet(skb);
		printk(KERN_INFO "Input: %d Output: %d All: %d\n", input_packets, output_packets, (input_packets + output_packets));
		return NF_ACCEPT;
	}
	return NF_ACCEPT;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("55PP");
MODULE_DESCRIPTION("Kernel Packet Sniffer");

int init_module(void)
{
	nfho_in.hook = hook_func_in;
	nfho_in.hooknum = NF_INET_PRE_ROUTING;
	nfho_in.pf = PF_INET;
	nfho_in.priority = NF_IP_PRI_FIRST;
	
	nfho_out.hook = hook_func_out;
	nfho_out.hooknum = NF_INET_POST_ROUTING;
	nfho_out.pf = PF_INET;
	nfho_out.priority = NF_IP_PRI_FIRST;
	
	nf_register_net_hook(&init_net, &nfho_in);
	nf_register_net_hook(&init_net, &nfho_out);
	
	return 0;
}

void cleanup_module(void)
{
	nf_unregister_net_hook(&init_net, &nfho_in);
	nf_unregister_net_hook(&init_net, &nfho_out);
}
