#ifndef OGRENCI_H
#define OGRENCI_H

#include "Bilgisayar.h"
#include "String.h"
#include "Tarih.h"

#include <iostream>

using namespace std;

class Ogrenci{

    //output << operatorunu uye olmayan fonksiyon seklinde friend olarak asiri yukledim..
    friend ostream &operator<<(ostream &, const Ogrenci &);

private:
    const int ogr_no; //const tipindeki degiskenler..
    const String ad;
    const String soyad;
    const Tarih dogum;
    const Tarih kayit;
    const Bilgisayar pc;
    int sinif; //sinif ve not_ort const tanimlanmadi, cunku daha sonradan degistirilebilirler..
    float not_ort;

public:
    //yapici fonksiyon butun uyelerini parametre olarak aliyor ancak sinif ve not_ort'a ilk deger ataniyor..
    Ogrenci(int,String,String,Tarih,Tarih,Bilgisayar,int=1,float=0);

    int numOku() const; //get fonksiyonlari..
    String adOku() const;
    String soyadOku() const;
    Tarih dogumOku() const;
    Tarih kayitOku() const;
    Bilgisayar pcOku() const;
    int sinifOku() const;
    float notOku() const;

    void sinifAyarla(int); //sinif ve not_ort'u ayarlayan set fonksiyonlari..
    void notAyarla(float);
};

#endif
