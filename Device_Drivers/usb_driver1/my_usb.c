#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>

int example_open (struct inode *pi, struct file *pf)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

ssize_t example_read (struct file *pf, char __user *buffer, size_t length, loff_t *offset)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return length;
}

ssize_t example_write (struct file *pf, const char __user *buffer, size_t length, loff_t *offset)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return length;
}

int example_release (struct inode *pi, struct file *pf)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

/* For to perform the device specific operations */
static long example_ioctl(struct file *p_file, unsigned int command, unsigned long parameter)
{
    return 0;
}

struct file_operations example_fops = 
{
    .owner = THIS_MODULE,
    .open = example_open,
    .read = example_read,
    .write = example_write,
    .release = example_release,
    .unlocked_ioctl = example_ioctl,
};

struct usb_class_driver example_class_driver = 
{
    .name = "usb2serial%d",
    .fops = &example_fops,
    .minor_base = 16,
};


//probe func(it is called whenever a device is inserted in our system)

static int pen_probe(struct usb_interface *interface,const struct usb_device_id *id)
{
printk(KERN_INFO "[*]Sony pendrive (%04X %04X) plugged\n",id->idVendor,id->idProduct);
return 0;//return 0 indicates we will manage this device
}

//disconnect

static void pen_disconnect(struct usb_interface *interface)
{
printk(KERN_INFO "[*]Sony Pendrive removed \n");
}



//usb_device_id
static struct usb_device_id pen_table[] =
{
//054c-05ba
{ USB_DEVICE(0x0951,0x1643) },
{}
};

MODULE_DEVICE_TABLE(usb,pen_table);

//usb_driver
static struct usb_driver pen_driver =
{
.name      =  "MY SONY USB DEVICE",
.id_table  =  pen_table,   //usb_device_id
.probe     =  pen_probe,
.disconnect=  pen_disconnect,
};

static __init int pen_init(void)
{
int ret=-1;
printk(KERN_INFO "[*]Sony constructor of device \n");
printk(KERN_INFO "\tRegistering device with kernel \n");
ret=usb_register(&pen_driver);
printk(KERN_INFO "\t Registration complete\n");
return ret;
}

static void __exit pen_exit(void)
{
printk(KERN_INFO "[*]Sony Destructor of device \n");
usb_deregister(&pen_driver);
printk(KERN_INFO "\t unregistration complete \n");
}

module_init(pen_init);
module_exit(pen_exit);
MODULE_LICENSE("GPL");
