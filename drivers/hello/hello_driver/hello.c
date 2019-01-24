/****************************************************************************
@file Name : Hello_Driver
@author    : Mahesh Terkar

****************************************************************************/


#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

//**************************Module_Init_start*******************************
static int hello_in(void)
{
	printk(KERN_ALERT "HELLO WORLD");
	return 0;
}
//**************************Module_Init_End*********************************



//**************************Module_Exit_Start*******************************
static void hello_ex(void)
{
	printk(KERN_ALERT "Exiting From Module");
}
//***************************Module_Exit_End*********************************

module_init(hello_in);
module_exit(hello_ex);
