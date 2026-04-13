#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Bir dosya ismi vermelisiniz\n");
		exit(-1);
	}
	int n;
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	if(fd < 0)
	{
		printf("Dosya acma hatasi\n");
		exit(-2);
	}
	printf("Dosya belirteci: %d\n",fd);
	char buf[19] = "Bu benim ilk yazim";
	if(n = write(fd,buf,sizeof(buf)-1) < 0)
	{
		printf("Yazma hatasi\n");
		exit(-3);
	}
	close(fd);
	
	fd = open(argv[1], O_RDONLY);
	char buf2[10];
	while((n = read(fd,buf2,sizeof(buf2))) > 0)
	{
		write(STDOUT_FILENO,buf2,n);
	}
	write(STDOUT_FILENO,"\n",sizeof("\n"));
	printf("Standart cikti: %d\n",STDOUT_FILENO);
	printf("Standart girdi: %d\n",STDIN_FILENO);
	close(fd);
	exit(0);
}

