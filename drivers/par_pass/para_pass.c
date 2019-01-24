/************************************************************************************************
@ileName : para_pass.c
@author	 : Mahesh Terkar 
@teamLead: Rajesh Dommaraju 
@etails  : It is a parameter passing driver in the kernel  
@icense  : SpanIdea Systems Pvt. Ltd. All rights reserved.
************************************************************************************************/

/*******************************************************************************
			INCLUDES
*******************************************************************************/

#include <linux/init.h>// start the init 
#include <linux/kernel.h>//include kernel info
#include <linux/module.h>//all module 
#include <linux/moduleparam.h>//parameter passing 

/*******************************************************************************
			 LOCAL MACROS		
*******************************************************************************/

#define GPL_LICENSE				"GPL"
#define DRIVER_MODULE_AUTHOR			"SPANIDEA"
#define DRIVER_MODULE_DESC			"parameter passing Module"
#define DRIVER_MODULE_VERSION			"V1.0"
#define LOCAL					static
#define GLOBAL					extern
#define RET_TYPE 

/*******************************************************************************
			 LOCAL TYPEDEFS		
*******************************************************************************/
typedef int INTEGER;
/*******************************************************************************
			GLOBAL VARIABLES		
*******************************************************************************/

/*******************************************************************************
			LOCAL VARIABLES		
*******************************************************************************/
 int var;
 char *name;
 int arr[2];
 int cb_value;
/*******************************************************************************
			LOCAL FUNCTIONS		
*******************************************************************************/

module_param(name,charp,S_IRUSR | S_IWUSR);// create a sysfs entry(sys/module/para_pass/parameters/var)
module_param(var,int,S_IRUSR | S_IWUSR);
module_param_array(arr,int,NULL,S_IRUSR | S_IWUSR);

/**********************************************************************************************
function	 : mod_para_cb
description	 : This function is initialised when var value changed.
		   This function is passed as an argument to module_init.
input param      : Integer
output param     : Integer 
**********************************************************************************************/

LOCAL int notify_param(const char *val, const struct kernel_param *kp)
{
	int res= param_set_int(val,kp);
	if(res==0)
	{
	    printk("---->Call back function called...\n"); 
	    printk("---->updated value of cb_value = %d\n",cb_value);
	    return 0; 
	}
	return -1;
}
const struct kernel_param_ops  my_param_ops =
{
	.set = &notify_param,
	.get = &param_get_int,

};

module_param_cb(cb_value, &my_param_ops, &cb_value, S_IRUGO |S_IWUSR);

/**********************************************************************************************
function	 : init_function
description	 : This function is initialised when module gets inserted.
		   This function is passed as an argument to module_init.
input param      : Integer string and array
output param     : Integer string and array
**********************************************************************************************/

LOCAL RET_TYPE int __init init_function(void) {
    int i=0;
    printk("---->Module Inserting...\n"); 
    printk(KERN_INFO "---->var = %d\n",var);
    printk(KERN_INFO "---->Name = %s\n",name);
    for(i=0;i< (sizeof(arr)/sizeof(int));i++)
    printk(KERN_INFO "---->arr[%d] = %d\t",i,arr[i]);

    printk(KERN_DEBUG "File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
    return 0;
}

/**********************************************************************************************
function	 : exit_function
description	 : This function is initialised when module gets removed.
		   This function is passed as an argument to module_exit.
input param      : Integer string and array
output param     : Integer string and array
**********************************************************************************************/
LOCAL void __exit exit_function(void) {
    printk("---->Exiting ...\n"); 
    printk("File : %s, function : %s, line : %d\n", __FILE__, __func__, __LINE__);
}

module_init(init_function);// __initcall();
module_exit(exit_function);// __exitcall();

MODULE_LICENSE(GPL_LICENSE);
MODULE_AUTHOR(DRIVER_MODULE_AUTHOR);
MODULE_VERSION(DRIVER_MODULE_VERSION);
MODULE_DESCRIPTION(DRIVER_MODULE_DESC);

