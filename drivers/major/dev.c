/************************************************************************************************
@ileName : dev.c
@author	 : mahesh Terkar 
@teamLead: Rajesh Dommaraju 
@etails  : It is a Major and minor number driver to load a module in the kernel  
@icense  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/*******************************************************************************
			INCLUDES
*******************************************************************************/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>// 
#include<linux/fs.h>// all related device number api stored 
#include<linux/kdev_t.h>

/*******************************************************************************
			 LOCAL MACROS		
*******************************************************************************/

#define GPL_LICENSE				"GPL"
#define DRIVER_MODULE_AUTHOR			"SPANIDEA"
#define DRIVER_MODULE_DESC			"Simple Hello World With Major and Minor Module"
#define DRIVER_MODULE_VERSION			"V1.0"
#define LOCAL 					static

#define STATIC
/*******************************************************************************
			 LOCAL TYPEDEFS		
*******************************************************************************/


/*******************************************************************************
			GLOBAL VARIABLES		
*******************************************************************************/

#ifdef STATIC
  dev_t dev = MKDEV(300,0);
#else
  dev_t dev=0;
#endif

/*******************************************************************************
			LOCAL VARIABLES		
*******************************************************************************/

/*******************************************************************************
			LOCAL FUNCTIONS		
*******************************************************************************/


/**********************************************************************************************
function	 : init_function
description	 : This function is initialised when module gets inserted.
		   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL int __init init_function(void) {
#ifdef STATIC
    register_chrdev_region(dev,1,"spanidea");
    printk(KERN_INFO "---->Inserting Driver and statically assign Major & Minor Number ...\n");
#else
    if((alloc_chrdev_region(&dev,0,1,"spanidea")) < 0)
    {	
      printk(KERN_INFO "ERROR : Can Not Dyanamically assign Major & Minor Number ...\n");
    }
      printk(KERN_INFO "---->Inserting Driver and Dyanamically assign Major & Minor Number ...\n");
#endif
    printk(KERN_INFO "Major = %d Minor = %d\n",MAJOR(dev),MINOR(dev));
    printk(KERN_DEBUG "File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
    return 0;
}

/**********************************************************************************************
function	 : exit_function
description	 : This function is initialised when module gets removed.
		   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL void __exit exit_function(void) {
    unregister_chrdev_region(dev,1);
    printk("Exiting ...\n"); 
    printk("File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
}

module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);

