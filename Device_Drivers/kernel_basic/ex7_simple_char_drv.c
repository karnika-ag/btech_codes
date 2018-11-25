#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>

int ex7_open(struct inode *pinode, struct file *pfile)
{
printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
return 0;
}
ssize_t ex7_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
return 0;
}
ssize_t ex7_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
return length;
}
int ex7_close(struct inode *pinode, struct file *pfile)
{
printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
return 0;
}

struct file_operations ex7_file_operations = {
       .owner = THIS_MODULE,
       .open  = ex7_open,
       .read  = ex7_read,
       .write = ex7_write,
       .release = ex7_close,
    };
int ex1_simple_module_init(void)
{
 printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
 /*register with kernel & indicate tht we r registering a char device driver*/
 register_chrdev(240 /*major_no*/,
                 "simple_char_drv"/*name of driver*/,
                  &ex7_file_operations/*file operations*/);
 return 0;
}
void ex1_simple_module_exit(void)
{
printk(KERN_ALERT "inside the %s function\n",__FUNCTION__);
/*unregister char device driver*/
unregister_chrdev(240,"simple_char_drv");
}
module_init(ex1_simple_module_init);
module_exit(ex1_simple_module_exit);
