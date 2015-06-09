#include<linux/init.h>
#include<linux/module.h>
#include<linux/debugfs.h>
#include<linux/fs.h>



static struct file_operations fops =
{
	.read = dev_read,
	.open = dev_open,
	.write = dev_write,
	.release = dev_rls,
};

static ssize_t dev_write(struct file *filp,const char *buff, size_t len, loff_t *off)
{




	printk("Data written");





}

static int hello_init(void)
{
	struct dentry *d;
	printk(KERN_ALERT "This is hello_init from ker1.c\n");
        debugfs_create_file("debug_ex", 0644, NULL, NULL,
                        &fops);
	
	int i=10;
	

	return 0;
}

static int hello_exit(void)
{
	printk(KERN_ALERT "This is hello_exit from ker1.c\n");
	return 0;
}

module_init(hello_init);
module_exit(hello_exit);
