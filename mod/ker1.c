#include<linux/init.h>
#include<linux/module.h>

static int hello_init(void)
{
	printk("This is hello_init from ker1.c\n");
	return 0;
}

static int hello_exit(void)
{
	printk("This is hello_exit from ker1.c\n");
	return 0;
}

module_init(hello_init);
module_exit(hello_exit);
