#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#define MODULE
#define LINUX
#define __KERNEL__

int init_module(void)
{
	printk("Hello world from ker.c\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_ALERT "Goodbye from ker.c\n");
}

