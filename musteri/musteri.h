#ifndef MUSTERİ_H
#define MUSTERİ_H

struct Yemek
{
    char yemekAdi[100];
    int fiyat;
    int hazirlanmaSuresi;
    int durum; // Mevcut durumu (1: Mevcut, 0: Mevcut Değil)
};

void dosyaOku(const char *dosya);

#endif /* RESTORAN_H */
