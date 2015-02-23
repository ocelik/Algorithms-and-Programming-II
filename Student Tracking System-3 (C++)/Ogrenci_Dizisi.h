#ifndef OGRENCI_DIZISI_H
#define OGRENCI_DIZISI_H

#include <iostream>
using std::ostream;
#include "Bilgisayar.h"
#include "String.h"
#include "Tarih.h"
#include "Ogrenci.h"

#define MAX_OGR_SAY 1001 //maksimum ogrenci sayisi..

class Ogrenci_Dizisi{

    //output << operatorunu uye olmayan fonksiyon seklinde friend olarak asiri yukledim..
    friend ostream &operator<<(ostream &,Ogrenci_Dizisi &);

private:
    Ogrenci *dizi[MAX_OGR_SAY]; //Ogrenci sinifi tipinde MAX_OGR_SAY kapasiteli isaretci dizisi tanimladim..
public:
    Ogrenci_Dizisi(); //yapici fonksiyon..

    void ekle(Ogrenci *); //yeni ogrenci ekleme islemini gerceklestiren uye fonksiyon..
    void sil(Ogrenci *); //silme islemini gerceklestiren uye fonksiyon..
    Ogrenci *ara(int); //int tipinde bir deger alarak Ogrenci tipinde deger donduren fonksiyon..
    Ogrenci **diziOku(); //varolan dizi'yi donduren fonksiyon..
};

#endif
