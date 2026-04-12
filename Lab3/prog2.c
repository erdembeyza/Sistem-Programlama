#include <stdio.h> //printf
#include <fcntl.h> //open O_WRONLY
#include <stdlib.h> //exit
#include <unistd.h>//write close

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
//bunun yerine 0644 de yazabilirsin

//argc 2 olmalı-> ./prog2 1.argümandır. dosyadı 2.argümandır

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("hata! dosya ismini giriniz.\n");
        exit(-1);
    }

//dosyayı ilk defa açacağız.
//argc[1] : terminalden girilen dosyanın ismi
//O_WRONLY: sadece yazma modunu aç
//O_CREAT: dosya yoksa oluştur
//O_TRUNC: dosya zaten varsa içindekileri silip sıfırla

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
    if (fd < 0) {
        printf("dosya olusturulamadi\n");
        exit(-2);
    }

//30 karakterlik buffer açıldı ve metin konuldu
//write: fd numaralı dosyanın içine buf metnini ve boyutu kadar yaz
    char buf[30] = "Bu dosya yeni olusturuldu";
    if (write(fd, buf, sizeof(buf)) < 0) {
        printf("hata! dosyanin icine yazdirilmadi");
        exit(-3);
    }
    close(fd);

//2.defa dosyayı açıyoruz. filemode ve creat yok. dosya mevcut çünkü
//O_APPEND: dosyanın sonuna yazmasını istediğimiz için
    fd = open(argv[1], O_WRONLY | O_APPEND);
    if (fd < 0) {
        printf("hata!ikinci kez acilamadi\n");
        exit(-5);
    }

    char buf2[30] = "\nDosyanin ikinci satiri\n";
    if (write(fd, buf2, sizeof(buf2)) < 0) {
        printf("hata!ikinci satiri yazdirilamadi\n");
        exit(-6);
    }
    close(fd);
    return 0;
}
