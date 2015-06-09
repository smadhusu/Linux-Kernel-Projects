#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>
#include<linux/fs.h>
#include<linux/cdev.h>

struct cdev *mycdev;
int major_number;
int ret;
char data[100];
dev_t dev_num;

#define DEVICE_NAME "my_own"

int device_open(struct inode *inode,struct file *filp)
{
	printk(KERN_INFO "Device open\n");
	return 0;
}

ssize_t device_read(struct file* filp,char *buf,ssize_t bufcount,loff_t* curoffset)
{
	char temp[bufcount];
	int i=0,j,size;
	
	for(j=0; data[j] != '\0'; j++)
	{
		printk(KERN_INFO"INSIDE First loop - j=%d\n",j);
	}
	
	size = j;

	for(i=0;i < size; i++)
	{
		temp[i]=data[--j];
		printk(KERN_INFO" !!! %c\n",temp[i]);
	}

	temp[i] = '\0';

	printk(KERN_INFO"Device reading, temp = %s, j = %d\n",temp,j);

	ret = copy_to_user(buf,temp,bufcount);
	return ret;
}

ssize_t device_write(struct file* filp, char* buf,ssize_t bufcount,loff_t* curoffset)
{
	printk(KERN_INFO"Device writing\n");
	ret = copy_from_user(data,buf,bufcount);
	return ret;
}

int device_close(struct inode *inode,struct file *filp)
{
	printk(KERN_INFO"Device close\n");
	return 0;
}

struct file_operations fops={
	.owner=THIS_MODULE,
        .open=device_open,
        .release=device_close,
        .write=device_write,
        .read=device_read
};

static int driver_entry()
{
	ret = alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
//	dev_num = MKDEV(247,0);
//	ret = register_chrdev_region(dev_num,1,DEVICE_NAME);
	if(ret<0)
	{
		printk(KERN_ALERT"alloc_chrdev_region failed\n");
		return ret;
	}

	major_number=MAJOR(dev_num);
	printk(KERN_INFO "Registered");
	printk(KERN_INFO "The major number is %d\n",major_number);
	printk(KERN_INFO "\t use \"mknod /dev/%s c %d 0\" for device file\n",DEVICE_NAME,major_number);
        mycdev=cdev_alloc();
        mycdev->ops=&fops;
        mycdev->owner=THIS_MODULE;

        ret=cdev_add(mycdev,dev_num,1);

	if(ret<0)
	{
		printk(KERN_ALERT "cdev_add failed\n");
		return ret;
	}

	return 0;
}

static void driver_exit(void) 
{
	cdev_del(mycdev);
	unregister_chrdev_region(dev_num,1);
	printk(KERN_ALERT "\nmy_own: Unloaded module\n");
}

module_init(driver_entry);
module_exit(driver_exit);
