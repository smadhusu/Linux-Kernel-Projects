#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MY_MACIG 'G'
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)
 
static int major; 
static char msg[200];

static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
  	printk(KERN_INFO "!!!!device_read\n");
        printk(KERN_INFO "!!!%s\n",msg);
	return simple_read_from_buffer(buffer, length, offset, msg, 200);
}


static ssize_t device_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{
        printk(KERN_INFO "!!!!device_write\n");
	if (len > 199)
		return -EINVAL;
	copy_from_user(msg, buff, len);
	msg[len] = '\0';
        printk(KERN_INFO "!!!%s\n",msg);
	return len;
}

//char buf[200];

int device_ioctl(struct file *filep, unsigned int cmd, unsigned long arg) {
	int len = 200;
	printk(KERN_ALERT "device_ioctl=%s,cmd=%d\n",(char *)arg,cmd);
	switch(cmd) {
	case READ_IOCTL:	
		printk(KERN_ALERT "READ_IOCTL\n");
		copy_to_user((char *)arg, buf, 200);
		break;
	
	case WRITE_IOCTL:
		printk(KERN_ALERT "WRITE_IOCTL\n");
		copy_from_user(buf, (char *)arg, len);
		break;

	default:
		return -ENOTTY;
	}

	printk(KERN_ALERT "moving out of device_ioctl with len=%d\n",len);

	return len;

}
static struct file_operations fops = {
	.read = device_read, 
	.write = device_write,
//	.unlocked_ioctl = device_ioctl
};

static int __init cdevexample_module_init(void)
{
	major = register_chrdev(0, "my_device_dobbindi", &fops);
	if (major < 0) {
     		printk ("Registering the character device failed with %d\n", major);
	     	return major;
	}
	printk("cdev example: assigned major: %d\n", major);
	printk("create node with mknod /dev/cdev_example c %d 0\n", major);
 	return 0;
}

static void __exit cdevexample_module_exit(void)
{
	unregister_chrdev(major, "my_device");
}  

module_init(cdevexample_module_init);
module_exit(cdevexample_module_exit);
MODULE_LICENSE("GPL");
