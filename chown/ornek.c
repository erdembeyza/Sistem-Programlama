#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    const char *dosya_adi = "ornek_dosya.txt";
    uid_t yeni_sahip = -1; // -1: Sahibini değiştirme
    gid_t yeni_grup = 1001; // Yeni grup numarası

    int sonuc = chown(dosya_adi, yeni_sahip, yeni_grup);

    if (sonuc == 0) {
        printf("İşlem başarılı! Grup 1001 olarak değiştirildi.\n");
    } else {
        perror("Hata oluştu"); 
    }
    return 0;
}
