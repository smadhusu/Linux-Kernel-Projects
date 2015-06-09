#define MODULE
#define LINUX
#define __KERNEL__
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int a=3;

static int __init a_init(void)
{
	printk(KERN_ALERT "The value of a is %d\n",a);
	return 0;
}

static void __exit a_exit(void)
{
	printk(KERN_ALERT "Exit a");
}

module_init(a_init);
module_exit(a_exit);
