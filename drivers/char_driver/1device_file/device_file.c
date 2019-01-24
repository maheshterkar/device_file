/************************************************************************************************
@ileName : device_fil.c
@author	 : Mahesh Terkar 
@teamLead: Rajesh Dommaraju 
@etails  : It is a driver file creation module in the kernel  
@icense  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/*******************************************************************************
			INCLUDES
*******************************************************************************/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>// all related device nimber api stored 
#include<linux/kdev_t.h>// for device file creation
#include<linux/device.h>//for device file

/*******************************************************************************
			 LOCAL MACROS		
*******************************************************************************/

#define GPL_LICENSE				"GPL"
#define DRIVER_MODULE_AUTHOR			"SPANIDEA"
#define DRIVER_MODULE_DESC			"Simple Hello World With Major and Minor Module"
#define DRIVER_MODULE_VERSION			"V1.0"
#define LOCAL					static 
#define GLOBAL					extern
#define RETURN

/*******************************************************************************
			 LOCAL TYPEDEFS		
*******************************************************************************/

typedef  int INTEGER;

/*******************************************************************************
			GLOBAL VARIABLES		
*******************************************************************************/


/*******************************************************************************
			LOCAL VARIABLES		
*******************************************************************************/
dev_t dev=0;

struct class *dev_class;

/*******************************************************************************
			LOCAL FUNCTIONS		
*******************************************************************************/
LOCAL int init_function(void);
LOCAL void exit_function(void);

/**********************************************************************************************
function	 : init_function
description	 : This function is initialised when module gets inserted.
		   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/

LOCAL RETURN INTEGER __init init_function(void) {

    if((alloc_chrdev_region(&dev,0,1,"spanidea"))<0)
    {	
      printk(KERN_INFO "---->ERROR:Can Not Dyanamically assign Major & Minor Number ...\n");
      return -1;
    }
    printk(KERN_INFO "---->Driver inserted successfully ...\n");
    printk(KERN_INFO "Major=%d Minor=%d\n",MAJOR(dev),MINOR(dev));
    printk(KERN_DEBUG "File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
   
    if((dev_class = class_create(THIS_MODULE,"spanidea_class")) == NULL)// create class in /sys/class
    {
      printk(KERN_INFO "---->ERROR:Can Not create class ...\n");
      goto r_class; 
    }
    if((device_create(dev_class,NULL,dev,NULL,"spanidea_dev")) == NULL){// create device /dev
    
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
description	 : This function is initialised when module gets removed.
		   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/

LOCAL RETURN void __exit exit_function(void) {
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
    unregister_chrdev_region(dev,1);
    printk(KERN_INFO "---->Exiting Module successfully ...\n"); 
    printk("File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
}

module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);

