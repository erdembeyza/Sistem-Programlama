#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

//iki dosya adı girilmeli
int main(int argc, char *argv[]){
	if(argc != 3){
		printf("hata! girdi ve çıktı dosya isimlerini belirt\n");
		printf("örnek: ./prog4 d1.txt d2.txt");
		exit(1);
	}
//argv[0]: ./prog4 kısmını temsil eder
//ilk önce girdi dosyası açılacak.dosyanın mevcut olması gerek. içinde 1 tane cümle yazacaktır.
//çıktı dosyasını ilk satırında verilen cümle yazılacak
	int fd_in = open(argv[1], O_RDONLY);
	if(fd_in < 0){
		printf("hata! dosya okumak icin acilamadi!\n");
		exit(2);
	}

//çıktının olduğu dosya oluşturulacak, açılacak, yazılacak
	int fd_out = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, FILE_MODE);
	if(fd_out < 0){
		printf("hata! 2. dosya yazmak icin acilamadi!\n");
		exit(3);
	}
//buf metin kutusuna yazıyı yazdık
	char buf[] = "Bu dosya Beyza Erdem tarafindan hazirlanmistir.\n";
	if(write(fd_out, buf, sizeof(buf) - 1) < 0){
		printf("hata! ikinci dosyaya yazi basilamadii!\n");
		exit(4);
	}
//kelime sayacı 1den başlar.
//durum bayrağı=0: boşluktayız. =1: kelimenin içindeyiz.
//1024 harf alacak olan buf2
	int sayac = 1;
	int flag = 0;
	char buf2[1024];
	int n;

//dosyalardan 1024 harf ver. okunan harf sayısını n değişkinine ata
//
	while((n = read(fd_in, buf2, sizeof(buf2))) > 0){
		for(int i = 0;i < n; i++){
                char  harfler = buf2[i];
                if(harfler != ' ' && harfler != '\n'){
               //ife girmeden önce flag 0(boşluktan geliyorsak) kelimenin ilk harfine dnek geldik, flag=1 olur
			if(flag == 0){
                          flag = 1;
                        }

//Daha sonra çıktı dosyasına, girdi dosyasında bulunan cümlenin tek numaralı kelimeleri yazılacaktır (1., 3. , 5... kelime). Cümleye ait diğer kelimeler ise yazılmayacaktır.
                        if(sayac % 2 != 0){
                                write(fd_out, &harfler, 1);
                        }
                }

		//okunan şey boşluksa eğer kelime bitti demektir
                else {
                        if(flag == 1){
                                if(sayac % 2 != 0){
                                        char bosluk = ' ';
                                        write(fd_out, &bosluk, 1);
                                }
                                sayac++;
                                flag = 0;
                        }
                }
        }
}
        close(fd_in);
        close(fd_out);
}

