obj-m +=hello.o

build:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
insert:	
	sudo insmod hello.ko

remove: 
	sudo rmmod hello.ko

print:
	dmesg | tail -5
