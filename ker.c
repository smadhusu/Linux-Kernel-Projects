#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#include<linux/module.h>
//#define MODULE
//#define LINUX
//#define __KERNEL__

static int startmod(void)
{
	printk("Hello world from ker.c");
	return 0;
}

static void exitmod(void)
{
	printk(KERN_ALERT "Goodbye from ker.c");
}

module_init(startmod);
module_exit(exitmod);
