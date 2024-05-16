#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../restoran/restoran.h"

void yemekListesiOlustur()
{
    FILE *dosya;
    char devam = 'e'; // Kullanıcı devam etmek istediği sürece döngüye devam eder
    struct Yemek yemekEkle;

    // Dosyayı 'append' modunda aç
    dosya = fopen("yemeklistesi.txt", "a");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.");
        return;
    }

    // Kullanıcı yeni yemek eklemek istediği sürece döngüye devam et
    while (devam == 'e' || devam == 'E')
    {
        printf("Yemek adini giriniz: ");
        scanf(" %[^\n]", yemekEkle.yemekAdi);

        printf("Yemek fiyatini giriniz: ");
        scanf("%d", &yemekEkle.fiyat);

        printf("Yemek hazirlanma suresini giriniz: ");
        scanf("%d", &yemekEkle.hazirlanmaSuresi);

        printf("Yemegin mevcut durumunu giriniz (1: Mevcut, 0: Mevcut Degil): ");
        scanf("%d", &yemekEkle.durum);

        // Yemek bilgilerini dosyaya yaz
        fprintf(dosya, "Yemek Adi: %s\nYemek Fiyati(TL): %d\nHazirlanma Suresi(dk): %d\nMevcut Durum: %d\n\n",
                yemekEkle.yemekAdi, yemekEkle.fiyat, yemekEkle.hazirlanmaSuresi, yemekEkle.durum);

        // Kullanıcıdan devam etmek isteyip istemediğini sor
        printf("Yeni yemek eklemek istiyor musunuz? (E/e: Evet, H/h: Hayir): ");
        scanf(" %c", &devam);
        while (getchar() != '\n')
            ; // Bufferı temizle
    }

    // Dosyayı kapat
    fclose(dosya);

    printf("Yemek listesi basariyla olusturuldu ve dosyaya kaydedildi.\n");
}

void yemekGuncelle(const char *dosyaAdi, const char *aramaYemekAdi, const struct Yemek *yeniBilgiler)
{
    FILE *dosya;
    FILE *tempDosya;
    struct Yemek yemek;

    // Geçici bir dosya oluştur
    tempDosya = fopen("temp.txt", "w");
    if (tempDosya == NULL)
    {
        printf("Gecici dosya olusturulamadi.");
        return;
    }

    // Dosyayı okuma modunda aç
    dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.");
        fclose(tempDosya);
        return;
    }

    // Dosyanın sonuna kadar oku
    while (fscanf(dosya, "Yemek Adi: %[^\n]\nYemek Fiyati(TL): %d\nHazirlanma Suresi(dk): %d\nMevcut Durum: %d\n\n", &yemek.yemekAdi, &yemek.fiyat, &yemek.hazirlanmaSuresi, &yemek.durum) == 4)

    {
        // Aranan yemek adına sahip yemeği bul
        if (strcmp(yemek.yemekAdi, aramaYemekAdi) == 0)
        {
            // Yeni bilgileri yaz
            fprintf(tempDosya, "Yemek Adi: %s\nYemek Fiyati: %d\nHazirlanma Suresi: %d\nMevcut Durum: %d\n\n",
                    yeniBilgiler->yemekAdi, yeniBilgiler->fiyat, yeniBilgiler->hazirlanmaSuresi, yeniBilgiler->durum ? "Mevcut" : "Mevcut Degil");
        }
        else
        {
            // Aranan yemek adına sahip yemek dışındaki yemekleri geçici dosyaya yaz
            fprintf(tempDosya, "Yemek Adi: %s\nYemek Fiyati: %s\nHazirlanma Suresi: %s\nMevcut Durum: %s\n\n",
                    yemek.yemekAdi, yemek.fiyat, yemek.hazirlanmaSuresi, yemek.durum);
        }
    }

    // Dosyaları kapat
    fclose(dosya);
    fclose(tempDosya);

    // Geçici dosyayı orijinal dosyanın üzerine taşı
    remove(dosyaAdi);
    rename("temp.txt", dosyaAdi);

    printf("Yemek bilgileri basariyla guncellendi.\n");
}

void yemekSil(const char *dosyaAdi, const char *silinecekYemekAdi)
{
    FILE *dosya;
    FILE *tempDosya;
    struct Yemek yemek;

    // Geçici bir dosya oluştur
    tempDosya = fopen("temp.txt", "w");
    if (tempDosya == NULL)
    {
        printf("Gecici dosya olusturulamadi.");
        return;
    }

    // Dosyayı okuma modunda aç
    dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.");
        fclose(tempDosya);
        return;
    }

    // Dosyanın sonuna kadar oku
    while (fscanf(dosya, "Yemek Adi: %[^\n]\nYemek Fiyati: %[^\n]\nHazirlanma Suresi: %[^\n]\nMevcut Durum: %[^\n]\n\n", yemek.yemekAdi, yemek.fiyat, yemek.hazirlanmaSuresi, yemek.durum) == 4)
    {
        // Silinecek yemeği bul
        if (strcmp(yemek.yemekAdi, silinecekYemekAdi) != 0)
        {
            // Silinmeyecek yemekleri geçici dosyaya yaz
            fprintf(tempDosya, "Yemek Adi: %s\nYemek Fiyati: %s\nHazirlanma Suresi: %s\nMevcut Durum: %s\n\n",
                    yemek.yemekAdi, yemek.fiyat, yemek.hazirlanmaSuresi, yemek.durum);
        }
    }

    // Dosyaları kapat
    fclose(dosya);
    fclose(tempDosya);

    // Geçici dosyayı orijinal dosyanın üzerine taşı
    remove(dosyaAdi);
    rename("temp.txt", dosyaAdi);

    printf("Yemek basariyla silindi.\n");
}

int main()
{

    char islem;

    printf("Yemek listesinde hangi islemi yapmak istiyorsunuz?\n");
    printf("Ekleme icin: e/E\nGuncelleme icin: g/G\nSilme icin: s/S\n");
    scanf("%c", &islem); // Boşluk karakterini ekledik

    if (islem == 'e' || islem == 'E')
    {
        yemekListesiOlustur();
    }
    else if (islem == 'g' || islem == 'G')
    {
        char aramaYemekAdi[100]; // Güncellenecek yemeğin adını almak için bir tampon
        struct Yemek yeniBilgiler;

        printf("Guncellenecek yemegin adini giriniz: ");
        scanf(" %[^\n]", aramaYemekAdi);

        // Yeni bilgileri al
        printf("Yeni yemek adini giriniz: ");
        scanf(" %[^\n]", &yeniBilgiler.yemekAdi);
        printf("Yeni yemek fiyatini giriniz: ");
        scanf(" %[^\n]", &yeniBilgiler.fiyat);
        printf("Yeni hazirlanma suresini giriniz: ");
        scanf(" %[^\n]", &yeniBilgiler.hazirlanmaSuresi);
        printf("Yemegin mevcut durumunu giriniz (1: Mevcut, 0: Mevcut Degil): ");
        scanf("%d", &yeniBilgiler.durum);

        yemekGuncelle("yemeklistesi.txt", aramaYemekAdi, &yeniBilgiler);
    }
    else if (islem == 's' || islem == 'S')
    {
        char silinecekYemekAdi[100];

        printf("Silinecek yemegin adini giriniz: ");
        scanf(" %[^\n]", silinecekYemekAdi);
        while (getchar() != '\n')
            ; // Bufferı temizle

        yemekSil("yemeklistesi.txt", silinecekYemekAdi);
    }
    else
    {
        printf("Gecersiz islem! Lutfen e/E, g/G veya s/S girin.\n");
    }

    return 0;
}