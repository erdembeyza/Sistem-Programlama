#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[])
{
        if(argc != 3)
        {
                printf("Bir girdi ve bir cikti dosya ismi vermelisiniz\n");
                exit(-1);
        }
        int n;
        int fd = open(argv[1], O_RDONLY);
        int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
        char buf[] = "Bu dosya Dincer Erbas tarafindan yazilmistir.\n";
        write(fd2,buf,sizeof(buf));

        char buf2[1];
        int ctr = 1;
        while((n = read(fd,buf2,sizeof(buf2))) > 0)
        {
                if(ctr || buf2[0] == '.')
                        write(fd2,buf2,n);
                if(buf2[0] == ' ')
                	ctr = 1 - ctr;
        }
        close(fd);
        close(fd2);
        return 0;
}

