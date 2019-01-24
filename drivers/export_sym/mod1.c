/************************************************************************************************
@ileName : mod1.c
@author	 : mahesh Terkar 
@teamLead: Rajesh Dommaraju 
@etails  : It is a simple export symbol module in the kernel  
@icense  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/*******************************************************************************
			INCLUDES
*******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>

/*******************************************************************************
			 LOCAL MACROS		
*******************************************************************************/

#define GPL_LICENSE				"GPL"
#define DRIVER_MODULE_AUTHOR			"SPANIDEA"
#define DRIVER_MODULE_DESC			"export symbol Module"
#define DRIVER_MODULE_VERSION			"V1.0"
#define LOCAL					 static
#define GLOBAL                                  
#define RET_TYPE
/*******************************************************************************
			 LOCAL TYPEDEFS		
*******************************************************************************/

/*******************************************************************************
			GLOBAL VARIABLES		
*******************************************************************************/
GLOBAL int exp_var = 1;

/*******************************************************************************
			LOCAL VARIABLES		
*******************************************************************************/

/*******************************************************************************
			LOCAL FUNCTIONS		
*******************************************************************************/
LOCAL RET_TYPE int init_function(void);
LOCAL RET_TYPE void exit_function(void);


EXPORT_SYMBOL(exp_var);

/**********************************************************************************************
function	 : hello_init
description	 : This function is initialised when module gets inserted.
		   This function is passed as an argument to module_init.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL int __init init_function(void) {
    printk(KERN_INFO "---->Hello World...\n");
    printk(KERN_DEBUG "File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
    return 0;
}

/**********************************************************************************************
function	 : hello_exit
description	 : This function is initialised when module gets removed.
		   This function is passed as an argument to module_exit.
input param      : NONE
output param     : NONE
**********************************************************************************************/
LOCAL void __exit exit_function(void) {
    printk(KERN_INFO"---->Exiting ...\n"); 
    printk("File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
}

module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);

