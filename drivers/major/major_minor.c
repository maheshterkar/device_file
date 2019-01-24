#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");

dev_t dev= MKDEV(300,0);

static int major_init(void)
{

	register_chrdev_region(dev,1,"spanidea");
	printk(KERN_INFO "Major=%d Minor=%d\n",MAJOR(dev),MINOR(dev));
	printk(KERN_INFO "Module Inserted...\n");
	return 0;

}

static void major_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Module removed...\n");

}

module_init(major_init);
module_exit(major_exit);
