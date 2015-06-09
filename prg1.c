#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

int func1(void)
{
	printk(KERN_ALERT "\nHello\n");
	return 0;
}

 int func2(void)
{
	printk(KERN_ALERT "\nBye\n");
	return 0;
}

module_init(func1);
module_exit(func2);

