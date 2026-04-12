#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("hata! dosya ismini giriniz!\n");
        exit(-1);
    }

//sadece okuyacağız    
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0){
        printf("hata! okunmak icin acilamadi\n");
        exit(-1);
    }


    int fd2 = open("metin_sesli_harfsiz.txt", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
    if (fd2 < 0) {
        printf("hata!ikinci dosya olusturulamadi\n");
        exit(-2);
    }

//tek harf okunacağı için
//dosyadan 1 byte oku, byte sayısını n e ata.
//eğer nden  büyükse hata! kısa tutmak için
    char buf_rd[1];
    int n;
    while( (n = read(fd, buf_rd, sizeof(buf_rd)) > 0) ){

        if (buf_rd[0] != 'a' && buf_rd[0] != 'e' &&
	buf_rd[0] != 'i' && buf_rd[0] != 'o' && buf_rd[0] != 'u') {
        
//eğer okunan harf kucuk sesli hharflerdene biri DEĞİLSE
//o harfi yeni dosyaya yazdır: fd2ye
//
		if (write(fd2, buf_rd, sizeof(buf_rd)) < 0) {
                printf("hata!dosyanin icine yazdirilmadi");
                exit(-3);
            }
        }
    }
	    close(fd);
    close(fd2);
    return 0;
}
