#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> //S_IRUSR chmod fonksiyonu

int main(int argc, char *argv[]) {
	if(argc != 2){
		printf("hata!dosya ismi veriniz!\n");
		exit(1);
	}
//Sadece dosya sahibi okur/yazar
	int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd < 0){
		printf("dosya oluşturulamadığı için açılamadı!\n");
		exit(2);
	}
	char buf[] = "Bu dosya sadece Beyza Erdem tarafindan okunabilir.\n";
	if(write(fd, buf, sizeof(buf) - 1) < 0) {
		printf("hata!dosya yazılamamıştır\n");
		exit(3);
	}
	close(fd);
// Daha sonra programınız dosyayı tekrar açacak ve dosyanın izinlerini değiştirerek "Dosya sahibi okur/yazar, grup arkadaşları yazar, diğerleri okur" olarak ayarlayacaktır.
	//dosyanın sonuna eklenecektir: O_APPEND. lseek kullanılmıyor
	int fd2 = open(argv[1], O_WRONLY | O_APPEND);
	if (fd2 < 0) {
		printf("dosya tekrar açılamamıştır.\n");
		exit(4);
	}

	//chmod: izinleri değiştirmek
	//S_IRUSR: SAHİP
	//S_WGRP: GRUP ARKADŞLARI YAZAR
	//S_IROTH: DİĞERLERİ OKUR
	if (chmod(argv[1], S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH) < 0) {
		printf("hata!izinler değiştirilemedi");
		exit(5);
	}

	char buf2[] = "Dosya sahibi okur/yazar, grup arkadaşları yazar, diğerleri okur";
	if(write(fd, buf2, sizeof(buf2) - 1) < 0) {
		printf("hata!ikinci kez dosyaya yazılamamıştırr\n");
		exit(6);
	}
	close(fd2);
}

