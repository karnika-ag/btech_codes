#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>


static int start_fun(void)
{
	printk("hello hi device driver: karnika==>\n");
	printk("its started\n");
	return 0;
}
static void exit_fun(void)
{
	printk("bye\n");
	return 0;
}
module_init(start_fun);
module_exit(exit_fun);


/*
first type on # prompot
#make
#insmod hello.ko
#dmesg
*/
