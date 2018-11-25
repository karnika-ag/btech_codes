#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>

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
