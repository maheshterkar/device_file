#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE	1024

char write_buff[BUFF_SIZE];
char read_buff[BUFF_SIZE];

int main()
{

	int fd;
	int choice;
	printf("\tWelcome to spanidea system...\n\n");
	fd = open("/dev/spanidea_dev",O_RDWR);
	if(fd<0)
	{
		printf("ERROR:unable to open file...\n");
		return 0;
	}

	while(1)
	{
		printf("\n\tEnter your choice..\n");
		printf("\t\t1.Write \n");
		printf("\t\t2.Read  \n");
		printf("\t\t3.close \n");
		scanf("%d",&choice);
		printf("\tYour choice is = %d\n",choice);

		switch(choice)
		{
			case 1:
				printf("\tEnter Data to write into Driver :");
				scanf("%s",write_buff);
				printf("\tData writing..\n");
				write(fd,write_buff,strlen(write_buff)+1);
				printf("\tcomplited..\n");
				break;

			case 2:
				printf("\tData Reading\n");
				read(fd,read_buff,BUFF_SIZE);
				printf("\tcomplited..\n");
				printf("\n\tData : %s\n",read_buff);
				break;

			case 3:
				close(fd);
				exit(1);
				break;

			default:
				printf("\n\tEnter valid choice...\n");
				break;

		}//switch close

	}// while close
	close(fd);

}// main close	
