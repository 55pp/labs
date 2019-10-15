#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
//
#include <linux/random.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
//#include <linux/sched.h>
//#include <linux/delay.h>

#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/kernel.h>



#define DEV_MAJOR 75
#define DEV_MINOR 0
#define DEV_NAME "mydev"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character device driver for conversation");
MODULE_AUTHOR("55pp");

#define MAXSTR 1024

static char msg[MAXSTR] = {0};


static int dev_open(struct inode *, struct file *);
static int dev_rls(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

////////////////////////////////////////////////////////////////////////////////////////////////////////


struct s_pipe
{
	struct semaphore read;
	struct semaphore write;
	char* mem;
};

struct s_pipe *init_factory_p;
struct s_pipe *init_player_p;

struct s_pipe *map_init_p;

struct s_pipe *factory_enemy_p;

struct s_pipe *enemy_factory_p;
struct s_pipe *enemy_player_p;

struct s_pipe *player_enemy_p;
struct s_pipe *player_map_p;

struct task_struct *init_p;
struct task_struct *factory_p;
struct task_struct *enemy_p;
struct task_struct *player_p;
struct task_struct *roll_p;

void init_pipe(struct s_pipe *pipe)
{
	//printk(KERN_NOTICE "sem read\n");
	sema_init(&pipe->read, 1);
	down_interruptible(&pipe->read);
	//printk(KERN_NOTICE "sem write\n");
	sema_init(&pipe->write, 1);
	up(&pipe->write);
	
	//printk(KERN_NOTICE "mem file\n");
	pipe->mem = (char *)__get_free_pages(GFP_KERNEL, 0);
	//pipe->mem = (char *)kmalloc(32, GFP_KERNEL);
	
	if(!pipe->mem)
		printk(KERN_ALERT "Can't allocated memory\n");
	
	//printk(KERN_NOTICE "reserved\n");
	SetPageReserved(virt_to_page((unsigned long)pipe->mem));

}

void release_pipe(struct s_pipe* pipe)
{
	ClearPageReserved(virt_to_page((unsigned long)pipe->mem));
	
	//kfree(pipe->mem);
	
	
}

void pipe_write(struct s_pipe* pipe, char* str)
{
	//printk(KERN_NOTICE "write: down sem\n");
	down_interruptible(&pipe->write);
	
	//printk(KERN_NOTICE "write: memcpy\n");
	memcpy(pipe->mem, str, strlen(str) + 1);
	
	//printk(KERN_NOTICE "write: up sem\n");
	up(&pipe->read);
}

void pipe_read(struct s_pipe* pipe, char* str)
{
	//printk(KERN_NOTICE "read: down sem\n");
	down_interruptible(&pipe->read);
	
	//printk(KERN_NOTICE "read: memcpy\n");
	memcpy(str, pipe->mem, strlen(pipe->mem) + 1);
	
	//printk(KERN_NOTICE "read: up sem\n");
	up(&pipe->write);
}

int init_f(void* data)
{
	printk(KERN_NOTICE "init_p\n");
	
	int iterations = 1;
	
	while(iterations--){
		printk(KERN_NOTICE "init_f: send message to factory\n");
		pipe_write(init_factory_p, "50 10 10 2");
		printk(KERN_NOTICE "init_f: success send\n");
		
		/*printk(KERN_NOTICE "init_f: send message to player\n");
		pipe_write(init_factory_p, "100 25");
		printk(KERN_NOTICE "init_f: success send\n");*/
	}
	
	while(!kthread_should_stop()){
		schedule();
	}
	
	return 0;
}

int factory_f(void* data)
{
	printk(KERN_NOTICE "factory_f\n");
	
	//char message[16] = {0};
	char* message = (char *)vmalloc(16 * sizeof(char));
	
	int health = 0;
	int damage = 0;
	int enemy_count = 0;
	int boost = 0;
	
	printk(KERN_NOTICE "factory_f: wait message from init\n");
	pipe_read(init_factory_p, &message[0]);
	printk(KERN_NOTICE "factory_f: success receive - %s\n", message);
	
	char* num;
	
	/*num = strsep(&message, " ");
	kstrtol(num, 10, &health);
	
	num = strsep(&message, " ");
	kstrtol(num, 10, &damage);
	
	num = strsep(&message, " ");
	kstrtol(num, 10, &boost);
	
	num = strsep(&message, " ");
	kstrtol(num, 10, &enemy_count);*/
	
	sscanf(message, "%d %d %d %d", &health, &damage, &boost, &enemy_count);
	
	printk(KERN_NOTICE "factory_f: %d %d %d %d\n", health, damage, boost, enemy_count);
	
	while(!kthread_should_stop()){
		schedule();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////



static struct file_operations fops =
{
    .read = dev_read,
    .open = dev_open,
    .write = dev_write,
    .release = dev_rls
};

int init_module(void)
{
    //int err = register_chrdev(DEV_MAJOR, DEV_NAME, &fops);
    
    init_factory_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	init_player_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	map_init_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	factory_enemy_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	enemy_factory_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	enemy_player_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	player_enemy_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	player_map_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
    
    init_pipe(init_factory_p);
    init_pipe(init_player_p);
    init_pipe(map_init_p);
    init_pipe(factory_enemy_p);
    init_pipe(enemy_factory_p);
    init_pipe(enemy_player_p);
    init_pipe(player_enemy_p);
    init_pipe(player_map_p);
   
	

	factory_p = kthread_run(&factory_f, NULL, "reader");
	init_p = kthread_run(&init_f, NULL, "writer");

    /*if(err < 0)
        printk(KERN_ALERT "Device registration failed\n");
    else
        printk(KERN_ALERT "Device registered\n");*/
            
    return 0;
}

void cleanup_module(void)
{
    release_pipe(init_factory_p);
    release_pipe(init_player_p);
    release_pipe(map_init_p);
    release_pipe(factory_enemy_p);
    release_pipe(enemy_factory_p);
    release_pipe(enemy_player_p);
    release_pipe(player_enemy_p);
    release_pipe(player_map_p);

    //unregister_chrdev(DEV_MAJOR, DEV_NAME);
    
    kthread_stop(init_p);
    kthread_stop(factory_p);
    /*kthread_stop(enemy_p);
    kthread_stop(player_p);
    kthread_stop(roll_p);*/
}

static int dev_open(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "Device opened\n");
    
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
