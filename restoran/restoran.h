#ifndef RESTORAN_H
#define RESTORAN_H

struct Yemek
{
    char yemekAdi[100];
    int fiyat;
    int hazirlanmaSuresi;
    int durum; // Mevcut durumu (1: Mevcut, 0: Mevcut Değil)
};

void yemekListesiOlustur();
void yemekGuncelle(const char *dosyaAdi, const char *aramaYemekAdi, const struct Yemek *yeniBilgiler);
void yemekSil(const char *dosyaAdi, const char *silinecekYemekAdi);

#endif /* RESTORAN_H */
