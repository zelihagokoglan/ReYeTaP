#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cProject/restoran/yemeklistesi.txt"
#include "../musteri/musteri.h"

void dosyaOku(const char *dosya)
{
    FILE *dosya;
    struct Yemek yemek;
    dosya = fopen(dosya, "../cProject/restoran/yemeklistesi.txt", "r");

    fprintf(dosya, "Yemek Adi: %s\nYemek Fiyati: %s\nHazirlanma Suresi: %s\nMevcut Durum: %s\n\n",
            yemek.yemekAdi, yemek.fiyat, yemek.hazirlanmaSuresi, yemek.durum);
    fclose(dosya);
}