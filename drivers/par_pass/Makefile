obj-m +=para_pass.o

#KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insert:
	sudo insmod para_pass.ko var=10 name="spanidea" arr=1,2

remove:
	sudo rmmod para_pass

print:
	dmesg | tail -10

cb_value:
	echo 100 > /sys/module/para_pass/parameters/cb_value

	
