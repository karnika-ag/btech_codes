#include <linux/init.h>
#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/ioport.h>
//#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <asm/io.h>


static int Tick_init(void);
static void Tock_exit(void);
static int opendev(struct inode *, struct file *);
static int closedev(struct inode *, struct file *);
static ssize_t readme(struct file *, char *, size_t, loff_t *);
static ssize_t writeme(struct file *, const char *, size_t, loff_t *);
static int Major;            
#define SUCCESS 0
#define DEVICE_NAME "time"   

static struct file_operations fops = {
  .read = readme, 
  .write = writeme,
  .open = opendev,
  .release = closedev
};

static int opendev(struct inode * a, struct file * b)
{
	printk("Someone opened me!\n");
	//nothing to do!!!
	return SUCCESS;
}
static int closedev(struct inode * a, struct file * b)
{
	//nothing to do!!
	printk("Someone Closed me!\n");
	return SUCCESS;
}
int atoi(const char *str)
{
	int num=0;
	while(str)
	{
		num=num*10+ (*str)-'0';
		str++;
	}
	return num;
}
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}
static ssize_t readme(struct file *filp,char *buffer,size_t length,loff_t *offset)  
{
	 char *b;
	 int len;
   	struct timeval time;
   	do_gettimeofday(&time);
   	b=kmalloc(sizeof(char)*40,GFP_KERNEL);
   	b=itoa(time.tv_sec,b,10);
    len=strlen(b);
   	copy_to_user(buffer,b,len);
   	printk("Return val:%s\n",b);
   	return length;
}
static ssize_t writeme(struct file *filp,const char *buff,size_t len, loff_t *off)
{
  	int i=atoi(buff);
  	struct timespec ab;
  	ab.tv_sec=i;
  	ab.tv_nsec=0;
  	do_settimeofday(&ab);
  	return len;
}

static int Tick_init(void)
{
  	Major = register_chrdev(0, DEVICE_NAME, &fops);
 	if(Major>0)
 	{
 		printk("TickTock is Ready For Requests!: 		  %d\n",Major);
 		printk(KERN_INFO "\tuse \"mknod /dev/%s c %d 0\" for device file",DEVICE_NAME,Major);
 	}
 	else
 	{
 			printk("Something Bad happened OhOhhh: %d",Major);
 	}
 	//int major_number = MAJOR(dev_num); //extracts the major number and store in our variable (MACRO)
 	//printk(KERN_INFO "time: major number is %d",major_number);
 	
 	return 0;
}
static void Tock_exit(void)
{
 	unregister_chrdev(Major, DEVICE_NAME);
 	printk("Goodbye Crewl World!\n");
}
module_exit(Tock_exit);
module_init(Tick_init);
MODULE_LICENSE("GPL");
