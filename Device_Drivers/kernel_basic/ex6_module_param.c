#include<linux/init.h>
#include<linux/module.h>
#include <linux/moduleparam.h>
int count=1;
module_param(count,int,0);
int ex6_simple_module_init(void)
{
int index=0;
 printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
 for(index=0;index<count;index++)
 {
 printk(KERN_ALERT "hello world index=  %d \n",index);
 }
 return 0;
}
void ex6_simple_module_exit(void)
{
printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
}
module_init(ex6_simple_module_init);
module_exit(ex6_simple_module_exit);
