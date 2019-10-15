#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/random.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>



#define DEV_MAJOR 75
#define DEV_MINOR 0
#define DEV_NAME "mydev"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character device driver for conversation");
MODULE_AUTHOR("55pp");

#define MAXSTR 1024
#define MEM_INFO (28 * 3 - 1)

static char msg[MAXSTR] = {0};
static char mem_info[MEM_INFO] = {0};
static int times = 0;
static struct task_struct *memory_thread;

int mem_fun(void *ptr);

static int dev_open(struct inode *, struct file *);
static int dev_rls(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

//#######################################################################################################

static bool init = true;

#define MAX_RESP_LEN 65
#define MAX_RESP_NO 10
#define MAX_KEY 17
#define TRANSPOSE 14
#define MAX_USER_INPUT 100
#define MAX_KWD_LEN 62
#define DELAY 20

char displ_msg[MAXSTR];

char user[30];
char wordin[TRANSPOSE][MAX_RESP_LEN];
char wordout[TRANSPOSE][MAX_RESP_LEN];

unsigned int ranNum(int max);
void initialize_global(void);

struct progstr
{
	char userip[MAX_USER_INPUT];
	char keyword[62];
	int keyfound;
	int keyno;
	int nullip;
} ip;

struct resp
{
	int tot_resp;
	int last_resp;
	char replys[MAX_RESP_NO][MAX_RESP_LEN];
	char word[MAX_KWD_LEN];
} keys[MAX_KEY] = {0};

struct resp null_resp = {0};
struct resp signon = {0};
struct resp no_key = {0};
struct resp bye = {0};

//struct resp keys[MAX_KEY] = {0};

void display_resp(struct resp* resp, int num)
{
	strcpy(displ_msg, "ELIZA > ");
	
	int size = strlen(resp->replys[num]);
	int i = 0;
	while(i < size){		
		if(resp->replys[num][i] == '*'){
			char *s1 = ip.userip+strlen(ip.keyword);
			short int flag = 0;
			
			int m = 0;
			while(m < TRANSPOSE){
				char *s2 = wordin[m];
				char *ptr = NULL;
				ptr = strstr(s1, s2);
				
				if(ptr != NULL){
					flag = 1;
					int times = ptr - s1;
					
					int j = 0;
					while(j < times){
						strncat(displ_msg, &ip.userip[strlen(ip.keyword) + j], 1);
						++j;
					}
					strcat(displ_msg, wordout[m]);
					char c;
					c = *(ptr + strlen(wordin[m]));
					int t = 0;
					while(c != '\0'){
						strncat(displ_msg, (ptr + strlen(wordin[m]) + t), 1);
						++t;
						c = *(ptr + strlen(wordin[m]) + t);
					}
				}
				
				++m;
			}
			if(flag == 0){
				char c;
				c = *(s1 + strlen(ip.keyword));
				int t = 0;
				while(c != '\0'){
					strncat(displ_msg, (s1 + t), 1);
					++t;
					c = *(s1 + t);
				}
			}
			break;
		} else {
			//printk(KERN_NOTICE "%s\n", displ_msg);
			strncat(displ_msg, &resp->replys[num][i], 1);
		}
		
		++i;
	}
	strcat(displ_msg, "\n");
	strcpy(msg, displ_msg);
}

void quit_display_resp(struct resp* resp, int num)
{
	strcpy(displ_msg, "ELIZA >");
	int size = strlen(resp->replys[num]);
	int i = 0;
	while(i < size){
		if(ranNum(6) == 0){
			char c = ranNum(100);
			if(c == '\n' || c == '\b' || c == 13)
				strcat(displ_msg, "w");
			else
				strcat(displ_msg, &c);
			strcat(displ_msg, "\b");
		}
	}
	
	strcpy(msg, displ_msg);
}

unsigned int ranNum(int max)
{
	unsigned int i;
	get_random_bytes(&i, sizeof(i));
	return (i % max);
}

void delete_whitespace(char *dest, char *src)
{
	int c = 0;
	int d = 0;
	bool f = false;
	while(src[c] != '\0' && src[c] != '\n'){
		if(src[c] == ' '){
			f = true;
			while(src[c] == ' ' && src[c] != '\0' && src[c] != '\n'){
				if(src[c] == ' ')
					++c;
			}
		}
		if(f && src[c] != '\0' && src[c] != '\n'){
			dest[d] = ' ';
			++d;
			f = false;
		}
		dest[d] = src[c];
		++c;
		++d;
	}
	dest[d - 1] = '\0';
}

void find_keyword(void)
{
	int len = 0;
	int lenkey = 0;
	int key_no = 0;
	char teststr[50];
	while((ip.keyfound == 0) && (key_no != MAX_KEY)){
		lenkey = strlen(keys[key_no].word);
		
		char *ptr = NULL;
		printk(KERN_NOTICE "%s - %s\n", ip.userip, keys[key_no].word);
		ptr = strstr(ip.userip, keys[key_no].word);
		if(ptr != NULL){
			ip.keyfound = 1;
			ip.keyno = key_no;
			strcpy(ip.keyword, keys[key_no].word);
			break;
		}
		
		++key_no;
	}
}

int file_read(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size)
{
	//mm_segment_t oldfs;
	int ret;
	
	//oldfs = get_fs();
	//set_fs(get_fs());
	
	ret = kernel_read(file, data, size, &offset);
	
	//set_fs(oldfs);
	return ret;
}

struct file* file_open(const char *path, int flags, int rights)
{
	struct file *filp = NULL;
	//mm_segment_t oldfs;
	int err = 0;
	
	//oldfs = get_fs();
	//set_fs(get_fs());
	filp = filp_open(path, flags, rights);
	//set_fs(oldfs);
	if(IS_ERR(filp)){
		err = PTR_ERR(filp);
		return NULL;
	}
	return filp;
}

void file_close(struct file *file)
{
	filp_close(file, NULL);
}


/*int file_write(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size)
{
	mm_segment_t oldfs;
	int ret;
	
	oldfs = get_fs();
	set_fs(get_fs());
	
	ret = kernel_write(file, data, size, &offset);
	
	set_fs(oldfs);
	return ret;
}

int file_sync(struct file *file)
{
	vfs_fsync(file, 0);
	return 0;
}
*/

void read_from_file(void)
{
	struct file *file;
	char line[62] = {0};
	char tmp_line[62] = {0};
	size_t len = 0;
	ssize_t read;
	unsigned long long off = 0;
	
	int index = -1;
	
	file = file_open("/home/tester/data", O_RDONLY, FMODE_READ);
	if(file == NULL){
		printk(KERN_ALERT "File not found\n");
		return;
	}
	
	/*while((read = getline(&line, &len, file)) != -1){
		char *ptr = NULL;
		ptr = strstr("@KWD@", line);
		if(strlen(line) < 1)
			break;
		else if(ptr != NULL){
			read = getline(&line, &len, file);
			strcpy(keys[++index].word, line);
		} else
			strcpy(keys[index].replys[++keys[index].last_resp], line);
	}*/
	
	int i = 0;
		
	while(i < 73){
		//printk(KERN_NOTICE ">START<\n");
		file_read(file, off, tmp_line, 60);
		off += 60;
		++i;
		delete_whitespace(line, tmp_line);
		char *ptr = NULL;
		ptr = strstr(line, "@KWD@");
		//printk(KERN_NOTICE "%s", line);
		int line_size = strlen(line);
		//printk(KERN_NOTICE "%d\n", line_size);
		if(line_size < 1)
			break;
		else if(ptr != NULL){
			//printk(KERN_NOTICE ">IF<\n");
			file_read(file, off, tmp_line, 60);
			off += 60;
			++i;
			delete_whitespace(line, tmp_line);
			//printk(KERN_NOTICE "%s", line);
			//printk(KERN_NOTICE ">INDEX: %d<\n", index);
			strcpy(keys[++index].word, line);
		} else
			//printk(KERN_NOTICE ">ELSE<\n");
			strcpy(keys[index].replys[keys[index].last_resp++], line);
	}
	
	file_close(file);

}

void initialize_global(void)
{
	strcpy(wordin[0], "ARE");
	strcpy(wordout[0], "AM");
	
	strcpy(wordin[1], "AM");
	strcpy(wordout[1], "ARE");
	
	strcpy(wordin[2], "WERE");
	strcpy(wordout[2], "WAS");
	
	strcpy(wordin[3], "WAS");
	strcpy(wordout[3], "WERE");
	
	strcpy(wordin[4], "YOU");
	strcpy(wordout[4], "ME");
	
	strcpy(wordin[5], "I ");
	strcpy(wordout[5], "YOU");
	
	strcpy(wordin[6], "YOUR");
	strcpy(wordout[6], "MY");
	
	strcpy(wordin[7], "MY");
	strcpy(wordout[7], "YOUR");
	
	strcpy(wordin[8], "I'VE");
	strcpy(wordout[8], "YOU'VE");
	
	strcpy(wordin[9], "YOU'VE");
	strcpy(wordout[9], "I'VE");
	
	strcpy(wordin[10], "I'M");
	strcpy(wordout[10], "YOU'RE");
	
	strcpy(wordin[11], "YOU'RE");
	strcpy(wordout[11], "I'M");
	
	strcpy(wordin[12], "ME");
	strcpy(wordout[12], "YOU");
	
	strcpy(wordin[13], "YOU");
	strcpy(wordout[13], "ME");
	
	strcpy(null_resp.replys[null_resp.last_resp++], "HUH?");
	strcpy(null_resp.replys[null_resp.last_resp++], "WHAT?");
	strcpy(null_resp.replys[null_resp.last_resp++], "COME AGAIN?");
	strcpy(null_resp.replys[null_resp.last_resp++], "HOW I AM SUPPOSED TO TALK IF YOU DON'T SAY ANYTHING?");
	
	strcpy(signon.replys[signon.last_resp++], "HI, I'M ELIZA. WHAT DO YOU WANT TO TALK ABOUT?");
	strcpy(signon.replys[signon.last_resp++], "SO HOW ARE DOING TODAY?");
	strcpy(signon.replys[signon.last_resp++], "HELLO, WHAT'S UP TODAY?");
	
	strcpy(no_key.replys[no_key.last_resp++], "PLEASE GO ON...");
	strcpy(no_key.replys[no_key.last_resp++], "WHAT DOES THAT SUGGEST TO YOU?");
	strcpy(no_key.replys[no_key.last_resp++], "I SEE");
	strcpy(no_key.replys[no_key.last_resp++], "I'M NOT SURE I KNOW WAHT YOU ARE TALKING ABOUT");
	strcpy(no_key.replys[no_key.last_resp++], "WHAT'S THAT SUPPOSED TO MEAN");
	strcpy(no_key.replys[no_key.last_resp++], "CAN YOU CLARIFY THAT A BIT");
	strcpy(no_key.replys[no_key.last_resp++], "THAT'S INTERESTING");
	strcpy(no_key.replys[no_key.last_resp++], "AND????");
	strcpy(no_key.replys[no_key.last_resp++], "TELL ME MORE");
	strcpy(no_key.replys[no_key.last_resp++], "OK, CONTINUE I'M LISTENING");
	strcpy(no_key.replys[no_key.last_resp++], "I DONT UNDERSTAND WHAT YOU ARE TRYING TO SAY");
	
	strcpy(bye.replys[bye.last_resp++], "GOOD BYE, HAVE A NICE DAY...");
	strcpy(bye.replys[bye.last_resp++], "BYE, HOPE TO SEE YOU SOON...");
	strcpy(bye.replys[bye.last_resp++], "BYE AND KEEP IN TOUCH...");
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct workqueue_struct *ram_wq;
int task_delay = 30 * 1000;
struct timer_list ram_timer;
static int rezolution;
bool live = true;

struct my_work_t {
	struct delayed_work my_work;
};

int delay;
struct my_work_t wrk;

static void read_mem_info(struct work_struct *work)
{
	struct my_work_t *in_s = (struct my_work_t*) (work);
	
	if(live)
		queue_delayed_work(ram_wq, (struct delayed_work*) work, delay);
		
	struct sysinfo info = {0};
	
	si_meminfo(&info);
	
	char str[100];
	char all_info[MAXSTR] = "Info:\n";
	
	sprintf(str, "Total RAM: %ld Mb\n", ((info.totalram * info.mem_unit) >> 20));
	strcat(all_info, str);
	sprintf(str, "Free RAM: %ld Mb\n", ((info.freeram * info.mem_unit) >> 20));
	strcat(all_info, str);
	
	strcpy(mem_info, all_info);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct file_operations fops =
{
    .read = dev_read,
    .open = dev_open,
    .write = dev_write,
    .release = dev_rls
};

int init_module(void)
{
    int err = register_chrdev(DEV_MAJOR, DEV_NAME, &fops);

    if(err < 0)
        printk(KERN_ALERT "Device registration failed\n");
    else
        printk(KERN_ALERT "Device registered\n");
    
    rezolution = 1000 / HZ;
    delay = task_delay / rezolution;
    ram_wq = create_workqueue("ram_queue");
    
    if(ram_wq){
    	wrk.my_work.timer = ram_timer;
    	INIT_DELAYED_WORK(((struct delayed_work*) &wrk), read_mem_info);
    	queue_delayed_work(ram_wq, (struct delayed_work*) &wrk, delay);
    }
        
    return err;
}

void cleanup_module(void)
{
    unregister_chrdev(DEV_MAJOR, DEV_NAME);
    
    live = false;
    cancel_delayed_work_sync((struct delayed_work*) &wrk);
    flush_workqueue(ram_wq);
    destroy_workqueue(ram_wq);
}

static int dev_open(struct inode *inod, struct file *fil)
{
    ++times;
    printk(KERN_ALERT "Device opened %d times\n", times);
    
    return 0;
}

static ssize_t dev_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
    int size = len >= strlen(msg) ? strlen(msg) : len;

    if(*off >= strlen(msg))
        return 0;

    if(copy_to_user(buff, msg, size))
        return -EFAULT;

    *off += size;
    return len;
}

static void process(void)
{
	if(init){
		init = false;
	    initialize_global();
	    printk(KERN_NOTICE "global init\n");
    	read_from_file();
    	printk(KERN_NOTICE "read from file\n");
	}
	
	if(strcmp(msg, "Hello\n") == 0){
		strncpy(msg, strcat(msg, "Hi\n"), MAXSTR);
	} else if(strcmp(msg, "Memory\n") == 0){		
		strncpy(msg, mem_info, MEM_INFO);
		strncpy(msg, strcat(msg, "\n"), MAXSTR);
	} else {
		ip.keyno = -1;
		ip.keyfound = 0;
		
		strcpy(ip.userip, msg);
		
		//printk(KERN_NOTICE "<SIZE: %d>\n", strlen(ip.userip));
		
		find_keyword();
		if(strlen(ip.userip) < 2){
			int num = ranNum(null_resp.last_resp);
			//printk(KERN_NOTICE "%d, %d\n", num, null_resp.last_resp);
			display_resp(&null_resp, num);
		} else if(ip.keyfound == 1){
			display_resp(&keys[ip.keyno], ranNum(keys[ip.keyno].last_resp));
		} else {
			display_resp(&no_key, ranNum(no_key.last_resp));
		}
	}
}

static ssize_t dev_write(struct file *fil, const char *buff, size_t len, loff_t *off)
{
    unsigned long ret;
    printk(KERN_INFO "dev write\n");
    if(len > sizeof(msg) -1)
        return -EINVAL;
    ret = copy_from_user(msg, buff, len);
    if(ret)
        return -EFAULT;
    msg[len] = '\0';
    process();
    return len;
}

static int dev_rls(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "Device closed\n");

    return 0;
}
