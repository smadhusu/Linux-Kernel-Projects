#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

#define __KERNEL__


static int a[3];
int i;

module_param_array(a, int, NULL, S_IRUSR | S_IWUSR);

static int mod_init(void)
{
	for(i=0;i<3;i++)
	printk("Hello, the passed parameter is %d\n",a[i]);
	return 0;
}

static void cleanmod(void)
{
	printk("Hello, the module with the parameter passing is exiting\n");
}

module_init(mod_init);
module_exit(cleanmod);
