File : hello.c
Description :
		This file is a paramter passing  module. 
		Contains basic module_init and module_exit functions as well as some callback .
		
Steps to compile :
1.Run				make
2.Insert module			sudo insmod para_pass.ko
3.See the added module		cat /proc/modules | grep para
4.See the logs in dmesg 	dmesg | tail -10
  kernel ring buffer	
5.Remove module			sudo rmmod para
6.Run				make clean


Keypoints to remember:
1.static int hello_init();
2.void hello_exit();
3.module_init();
4.module_exit();

