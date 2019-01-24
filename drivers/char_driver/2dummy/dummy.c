/************************************************************************************************
@ileName : dummy.c
@author	 : Mahesh Terkar 
@teamLead: Rajesh Dommaraju 
@etails  : It is a dummy  driver to load a module in the kernel  
@icense  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/*******************************************************************************
			INCLUDES
*******************************************************************************/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>// all related device number api stored 
#include<linux/kdev_t.h>// for device file creation
#include<linux/device.h>//for device file
#include<linux/cdev.h>//for cdev struct

/*******************************************************************************
			 LOCAL MACROS		
*******************************************************************************/

#define GPL_LICENSE				"GPL"
#define DRIVER_MODULE_AUTHOR			"SPANIDEA"
#define DRIVER_MODULE_DESC			"Simple Hello World With Major and Minor Module"
#define DRIVER_MODULE_VERSION			"V1.0"
#define LOCAL 					static
#define GLOBAL					extern
#define RETURN

/*******************************************************************************
			 LOCAL TYPEDEFS		
*******************************************************************************/
//typedef int INTEGER;


/*******************************************************************************
			GLOBAL VARIABLES		
*******************************************************************************/


/*******************************************************************************
			LOCAL VARIABLES		
*******************************************************************************/
dev_t dev=0;
LOCAL struct class *dev_class;
LOCAL struct cdev etx_cdev;


/*******************************************************************************
			LOCAL FUNCTIONS		
*******************************************************************************/

LOCAL RETURN int  __init init_function(void);
LOCAL RETURN void __exit exit_function(void);
LOCAL int etx_open(struct inode *inode,struct file *file);
LOCAL int etx_release(struct inode *inode,struct file *file);
LOCAL ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
LOCAL ssize_t etx_write(struct file *filp, const char *buf, size_t len, loff_t *off);

LOCAL struct file_operations fops =
{
	.owner   =  THIS_MODULE,
	.read    =  etx_read,
	.write   =  etx_write,
	.open    =  etx_open,
	.release =  etx_release,
};
/**********************************************************************************************
function	 : etx_open
description	 : This function is initialised when module gets loaded.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL int etx_open(struct inode *inode,struct file *file)
{
	printk(KERN_INFO "---->open function called...\n");
	return 0;

}

/**********************************************************************************************
function	 : etx_release
description	 : This function is released when module unloaded.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL int etx_release(struct inode *inode,struct file *file)
{
 
	printk(KERN_INFO "---->release function called...\n");
	return 0;
}

/**********************************************************************************************
function	 : etx_read
description	 : This function is called when trying to read
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{

	printk(KERN_INFO "---->read function called...\n");
	return 0;
}

/**********************************************************************************************
function	 : etx_writing
description	 : This function is called when trying to write .
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL ssize_t etx_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{

	printk(KERN_INFO "---->write function called...\n");
	return len;

}

/**********************************************************************************************
function	 : init_function
description	 : This function is initialised when module gets inserted.
		   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL int __init init_function(void) {

    if((alloc_chrdev_region(&dev,0,1,"etx_dev"))<0)
    {	
      printk(KERN_INFO "---->ERROR:Can Not Dyanamically assign Major & Minor Number ...\n");
      return -1;
    }
    printk(KERN_INFO "---->Module inserted successfully ...\n");
    printk(KERN_INFO "---->Major = %d Minor = %d\n",MAJOR(dev),MINOR(dev));
    printk(KERN_DEBUG "File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
   
    cdev_init(&etx_cdev,&fops);//creating cdev structure

    if((cdev_add(&etx_cdev,dev,1))<0)// Adding chara device to the system.
    {
      printk(KERN_INFO "---->ERROR:Can Not add device ...\n");
      goto r_class; 
    }

    if((dev_class = class_create(THIS_MODULE,"spanidea_class")) == NULL)//create entry in /sys/class
    {
      printk(KERN_INFO "---->ERROR:Can Not create class ...\n");
      goto r_class; 
    }

    if((device_create(dev_class,NULL,dev,NULL,"spanidea_dev"))==NULL)//create entry /dev/
    {
      printk(KERN_INFO "---->ERROR:Can Not create device ...\n");
      goto r_dev;
    }
    return 0;

r_dev:
      class_destroy(dev_class);
r_class:
      unregister_chrdev_region(dev,1);
      return -1;
}

/**********************************************************************************************
function	 : exit_function
descript`ion	 : This function is initialised when module gets removed.
		   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL void __exit exit_function(void) {
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    unregister_chrdev_region(dev,1);
    cdev_del(&etx_cdev);
    printk("---->Module removed successfully...\n"); 
    printk("File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
}

module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);

