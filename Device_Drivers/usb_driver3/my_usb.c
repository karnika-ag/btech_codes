#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>


#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define BULK_EP_OUT 0x01
#define BULK_EP_IN 0x82
#define MAX_PKT_SIZE 512
 
static struct usb_device pen_driver;
static struct usb_class_driver example_class_driver;
static unsigned char bulk_buf[MAX_PKT_SIZE];
 

int pen_open (struct inode *pi, struct file *pf)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}
/*
ssize_t pen_read (struct file *pf, char __user *buffer, size_t length, loff_t *offset)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return length;
}

ssize_t pen_write (struct file *pf, const char __user *buffer, size_t length, loff_t *offset)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return length;
}
*/
static ssize_t pen_read(struct file *f, char __user *buf, size_t cnt, loff_t *off)
{
    int retval;
    int read_cnt;
 
    /* Read the data from the bulk endpoint */
    retval = usb_bulk_msg(&pen_driver, usb_rcvbulkpipe(&pen_driver, BULK_EP_IN),
            bulk_buf, MAX_PKT_SIZE, &read_cnt, 5000);
    if (retval)
    {
        printk(KERN_ERR "Bulk message returned %d\n", retval);
        return retval;
    }
    if (copy_to_user(buf, bulk_buf, MIN(cnt, read_cnt)))
    {
        return -EFAULT;
    }
 
    return MIN(cnt, read_cnt);
}
static ssize_t pen_write(struct file *f, const char __user *buf, size_t cnt, loff_t *off)
{
    int retval;
    int wrote_cnt = MIN(cnt, MAX_PKT_SIZE);
 
    if (copy_from_user(bulk_buf, buf, MIN(cnt, MAX_PKT_SIZE)))
    {
        return -EFAULT;
    }
 
    /* Write the data into the bulk endpoint */
    retval = usb_bulk_msg(&pen_driver, usb_sndbulkpipe(&pen_driver, BULK_EP_OUT),
            bulk_buf, MIN(cnt, MAX_PKT_SIZE), &wrote_cnt, 5000);
    if (retval)
    {
        printk(KERN_ERR "Bulk message returned %d\n", retval);
        return retval;
    }
 
    return wrote_cnt;
}

int pen_release (struct inode *pi, struct file *pf)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

/* For to perform the device specific operations */
static long pen_ioctl(struct file *p_file, unsigned int command, unsigned long parameter)
{
    return 0;
}

struct file_operations example_fops = 
{
    .owner = THIS_MODULE,
    .open = pen_open,
    .read = pen_read,
    .write = pen_write,
    .release = pen_release,
    .unlocked_ioctl = pen_ioctl,
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
{ USB_DEVICE(0x054c,0x05ba) },
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
printk(KERN_INFO "[*]Sony constructor of device ");
printk(KERN_INFO "\tRegistering device with kernel");
ret=usb_register(&pen_driver);
printk(KERN_INFO "\t Registration complete");
return ret;
}

static void __exit pen_exit(void)
{
printk(KERN_INFO "[*]Sony Destructor of device ");
usb_deregister(&pen_driver);
printk(KERN_INFO "\t unregistration complete ");
}

module_init(pen_init);
module_exit(pen_exit);
MODULE_LICENSE("GPL");
