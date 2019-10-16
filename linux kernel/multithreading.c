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

unsigned int random_num(int max)
{
	unsigned int i;
	get_random_bytes(&i, sizeof(i));
	return (i % max) + 1;
}

struct s_pipe
{
	struct semaphore read;
	struct semaphore write;
	char* mem;
};

struct s_pipe *init_factory_p;
struct s_pipe *init_player_p;
struct s_pipe *init_map_p;

struct s_pipe *map_init_p;
struct s_pipe *map_player_p;

struct s_pipe *factory_enemy_p;

struct s_pipe *enemy_factory_p;
struct s_pipe *enemy_player_p;

struct s_pipe *player_enemy_p;
struct s_pipe *player_map_p;
struct s_pipe *player_init_p;

struct task_struct *init_p;
struct task_struct *factory_p;
struct task_struct *enemy_p;
struct task_struct *player_p;
struct task_struct *map_p;

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
	
	char* message = (char *)vmalloc(16 * sizeof(char));
	
	while(iterations--){
		printk(KERN_NOTICE "init_f: send message to factory\n");
		pipe_write(init_factory_p, "50 10 10");
		printk(KERN_NOTICE "init_f: success send\n");
		
		printk(KERN_NOTICE "init_f: send message to player\n");
		pipe_write(init_player_p, "100 25");
		printk(KERN_NOTICE "init_f: success send\n");

		printk(KERN_NOTICE "init_f: send message to map\n");
		pipe_write(init_map_p, "start");
		printk(KERN_NOTICE "init_f: success send\n");

		
		printk(KERN_NOTICE "init_f: wait message from player\n");
		pipe_read(player_init_p, &message[0]);
		printk(KERN_NOTICE "init_f: success receive - %s\n", message);
		
		int score;
		
		sscanf(message, "done %d", &score);
		
		if(score > 0){
			printk(KERN_NOTICE "init_f: level complited - Score -> %d\n", score);
		} else {
			printk(KERN_NOTICE "init_f: level failed\n");
		}
		
	}
	
	pipe_write(init_factory_p, "-1");
	pipe_write(init_player_p, "-1");
	pipe_write(init_map_p, "stop");
	
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
	int boost = 0;
	
	while(true){
		printk(KERN_NOTICE "factory_f: wait message from init\n");
		pipe_read(init_factory_p, &message[0]);
		printk(KERN_NOTICE "factory_f: success receive - %s\n", message);
	
		char* num;
	
		sscanf(message, "%d %d %d %d", &health, &damage, &boost);
		
		if(health <= 0)
			break;
	
		printk(KERN_NOTICE "factory_f: %d %d %d %d\n", health, damage, boost);
	
		while(true){
			printk(KERN_NOTICE "factory_f: send message to enemy\n");
			sprintf(message, "%d %d", health, damage);
			pipe_write(factory_enemy_p, message);
			printk(KERN_NOTICE "factory_f: success send\n");
		
			health += boost << 1;
			damage += boost >> 1;
		
			printk(KERN_NOTICE "factory_f: wait message from enemy\n");
			pipe_read(enemy_factory_p, &message[0]);
			printk(KERN_NOTICE "factory_f: success receive - %s\n", message);
		
			if(strstr(message, "pdead") != NULL)
				break;
		}
	}
	
	pipe_write(factory_enemy_p, "-1");
	
	while(!kthread_should_stop()){
		schedule();
	}

	return 0;
}

bool fight_with_enemy(int* health, int damage)
{
	char* message = (char *)vmalloc(16 * sizeof(char));
	
	bool end = false;
	bool dead = false;
	
	int enemy_damage = 0;
	
	while(!end && !dead){
		if(*health <= 0){
			damage = 0;
			dead = true;
		}
		
		printk(KERN_NOTICE "fight_player: send damage to enemy\n");
		sprintf(message, "%d", damage);
		pipe_write(player_enemy_p, message);
		printk(KERN_NOTICE "fight_player: success send\n");
		
		printk(KERN_NOTICE "fight_player: wait damage from enemy\n");
		pipe_read(enemy_player_p, &message[0]);
		printk(KERN_NOTICE "fight_player: Success receive - %s\n", message);
		
		sscanf(message, "%d", &enemy_damage);
		
		if(enemy_damage == 0){
			end = true;
		}
		
		*health -= enemy_damage;
	}
	
	return dead;
}

int player_f(void* data)
{
	char* message = (char *)vmalloc(16 * sizeof(char));

	bool dead = false;
	int health = 0;
	int damage = 0;
	int key = 0;
	
	while(true){
		printk(KERN_NOTICE "player_f: wait message from init\n");
		pipe_read(init_player_p, &message[0]);
		printk(KERN_NOTICE "player_f: success receive - %s\n", message);

		sscanf(message, "%d %d", &health, &damage);
	
		printk(KERN_NOTICE "player_f: %d %d\n", health, damage);	
		
		if(health <= 0)
			break;
		
		int deadEnemy = 0;
		
		while(!dead && key != 3){
			printk(KERN_NOTICE "player_f: send message to map\n");
			pipe_write(player_map_p, "next");
			printk(KERN_NOTICE "player_f: success send\n");
			
			printk(KERN_NOTICE "player_f: wait message from map\n");
			pipe_read(map_player_p, &message[0]);
			printk(KERN_NOTICE "player_f: success receive - %s\n", message);
			
			if(strstr(message, "health") != NULL){
				int hp_boost;
				sscanf(message, "health: %d", &hp_boost);
				printk(KERN_NOTICE "player_f: hp %d -> %d\n", health, (health + hp_boost));
				health += hp_boost;
			} else if(strstr("key", message) != NULL){
				printk(KERN_NOTICE "player_f: key %d -> %d\n", key, key + 1);
				++key;
			} else if(strstr("enemy", message) != NULL){
				dead = fight_with_enemy(&health, damage);
			}
		}
		
		if(!dead){
			sprintf(message, "done %d", health);
		
			printk(KERN_NOTICE "player_f: send message to init\n");
			pipe_write(player_init_p, &message[0]);
			printk(KERN_NOTICE "player_f: success send\n");
		} else {
			printk(KERN_NOTICE "player_f: send message to init\n");
			pipe_write(player_init_p, "done -1");
			printk(KERN_NOTICE "player_f: success send\n");
		}	
		
		printk(KERN_NOTICE "player_f: send message to map\n");
		pipe_write(player_map_p, "stop");
		printk(KERN_NOTICE "player_f: success send\n");
		
		printk(KERN_NOTICE "player_f: send message to enemy\n");
		pipe_write(player_enemy_p, "0");
		printk(KERN_NOTICE "player_f: success send\n");	
	}
	
	while(!kthread_should_stop()){
		schedule();
	}

	return 0;
}

int map_f(void* data)
{
	char* message = (char *)vmalloc(16 * sizeof(char));

	while(true){
		printk(KERN_NOTICE "map_f: receive message from init\n");
		pipe_read(init_map_p, message);
		printk(KERN_NOTICE "map_f: success receive - %s\n", message);
		
		if(strcmp(message, "start") != 0)
			break;
		
		while(true){
			printk(KERN_NOTICE "map_f: receive message from player\n");
			pipe_read(player_map_p, message);
			printk(KERN_NOTICE "map_f: success receive - %s\n", message);
			
			if(strcmp(message, "next") == 0){
				int num = (int) random_num(100);
				printk(KERN_NOTICE "map_f: send message to player %d\n", num);
				if(num < 33){
					printk(KERN_NOTICE "map_f: roll hp\n");
					pipe_write(map_player_p, "health: 50");
					printk(KERN_NOTICE "map_f: success send\n");
				} else if(num >= 34 && num < 67){
					printk(KERN_NOTICE "map_f: roll key\n");
					pipe_write(map_player_p, "key");
					printk(KERN_NOTICE "map_f: success send\n");
				} else if(num >= 67){
					printk(KERN_NOTICE "map_f: roll enemy\n");
					pipe_write(map_player_p, "enemy");
					printk(KERN_NOTICE "map_f: success send\n");
				}
			} else {
				break;
			}
		}
	}
	
	while(!kthread_should_stop()){
		schedule();
	}
	
	return 0;
}

bool fight_with_player(int health, int damage)
{
	char* message = (char *)vmalloc(16 * sizeof(char));

	bool end = false;
	bool dead = false;
	
	int player_damage = 0;
	
	while(!end && !dead){
		if(health <= 0){
			dead = true;
			damage = 0;
		}
		
		printk(KERN_NOTICE "fight_enemy: wait damage from player\n");
		pipe_read(player_enemy_p, &message[0]);
		printk(KERN_NOTICE "fight_enemy: success receive - %s\n", message);
		
		sscanf(message, "%d", &player_damage);
		
		if(player_damage == 0)
			end = true;
			
		health -= player_damage;
		
		printk(KERN_NOTICE "fight_enemy: send damage to player\n");
		sprintf(message, "%d", damage);
		pipe_write(enemy_player_p, &message[0]);
		printk(KERN_NOTICE "fight_enemy: success send\n");
	}
	
	return dead;
}

int enemy_f(void* data)
{
	char* message = (char *)vmalloc(16 * sizeof(char));
	
	int health = 0;
	int damage = 0;
	bool dead = false;
	
	while(true){
		printk(KERN_NOTICE "enemy_f: wait message from factory\n");
		pipe_read(factory_enemy_p, &message[0]);
		printk(KERN_NOTICE "enemy_f: success receive - %s\n", message);
	
		sscanf(message, "%d %d", &health, &damage);
		
		if(health <= 0)
			break;
			
		dead = fight_with_player(health, damage);
		
		if(dead){
			printk(KERN_NOTICE "enemy_f: send message to factory\n");
			pipe_write(enemy_factory_p, "dead");
			printk(KERN_NOTICE "enemy_f: success send\n");
		} else {
			printk(KERN_NOTICE "enemy_f: send message to factory\n");
			pipe_write(enemy_factory_p, "pdead");
			printk(KERN_NOTICE "enemy_f: success send\n");
		}
	}
	
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
	init_map_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	map_init_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	map_player_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	factory_enemy_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	enemy_factory_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	enemy_player_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	player_enemy_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	player_map_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
	player_init_p = (struct s_pipe*)vmalloc(sizeof(struct s_pipe));
    
    init_pipe(init_factory_p);
    init_pipe(init_player_p);
    init_pipe(init_map_p);
    init_pipe(map_init_p);
    init_pipe(map_player_p);
    init_pipe(factory_enemy_p);
    init_pipe(enemy_factory_p);
    init_pipe(enemy_player_p);
    init_pipe(player_enemy_p);
    init_pipe(player_map_p);
    init_pipe(player_init_p);
   
	

	factory_p = kthread_run(&factory_f, NULL, "factory");
	init_p = kthread_run(&init_f, NULL, "init");
	player_p = kthread_run(&player_f, NULL, "player");
	map_p = kthread_run(&map_f, NULL, "map");
	enemy_p = kthread_run(&enemy_f, NULL, "enemy");

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
    release_pipe(init_map_p);
    release_pipe(map_init_p);
    release_pipe(map_player_p);
    release_pipe(factory_enemy_p);
    release_pipe(enemy_factory_p);
    release_pipe(enemy_player_p);
    release_pipe(player_enemy_p);
    release_pipe(player_map_p);
    release_pipe(player_init_p);

    //unregister_chrdev(DEV_MAJOR, DEV_NAME);
    
    kthread_stop(init_p);
    kthread_stop(factory_p);
    kthread_stop(player_p);
    kthread_stop(map_p);
    kthread_stop(enemy_p);
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
