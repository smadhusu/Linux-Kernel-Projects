
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEVICE "/dev/my_own"

int main()
{
	int i,fd;
	char ch, write_buf[100], read_buf[100];
	
	fd=open(DEVICE,O_RDWR);
	
	if(fd==-1)
	{
		printf("File %s either does not exist or has been locked by another process\n",DEVICE);
		exit(-1);
	}
	
	printf("r=read from device\nw=write to device\nEnter command:");
	scanf("%c",&ch);
	fflush(stdin);
	
	switch(ch)
	{
		case 'w':
		printf("Enter data: ");
//		scanf("%s",write_buf);
//		gets(write_buf);
//		memset(write_buf,0,sizeof(write_buf));
		getchar();
		fgets(write_buf, sizeof(write_buf), stdin);
		write(fd,write_buf,sizeof(write_buf));
		break;
		case 'r':
		read(fd,read_buf,sizeof(read_buf));
		printf("\n-- Device: Reversal of input --%s\n\n",read_buf);
		break;
		default:
		printf("Command not recognized\n");
		break;
	}
		close(fd);
	
	return 0;
}

