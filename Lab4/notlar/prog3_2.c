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
	int fd = open(argv[1], O_RDONLY);
	int fd2 = open("metin_sesli_harfsiz.txt", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	char buf[1];
	while((n = read(fd,buf,sizeof(buf))) > 0)
	{
		if(buf[0] != 'a' && buf[0] != 'i' && buf[0] != 'o' && buf[0] != 'u' && buf[0] != 'e' && buf[0] != 'A' && buf[0] != 'E' && buf[0] != 'I' && buf[0] != 'O' && buf[0] != 'U')
			write(fd2,buf,n);
	}
	close(fd);
	close(fd2);
	return 0;
}

