#include<linux/init.h>
#include<linux/module.h>
int ex2_simple_module_init(void)
{
 printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
 return 0;
}
module_init(ex2_simple_module_init);
