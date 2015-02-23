#include <iostream>
#include <iomanip>

#include "Bilgisayar.h"
#include "String.h"
#include "Tarih.h"

using namespace std;

#include "Ogrenci.h"

//yapici fonksiyon.. gelen degerleri parametre olarak alip direk atamalari gerceklestiriyor..
Ogrenci::Ogrenci(int no,String a, String s,Tarih d,Tarih k,Bilgisayar p,int snf,float ort)
    :ogr_no(no),ad(a),soyad(s),dogum(d),kayit(k),pc(p),sinif(snf),not_ort(ort)
{}

//set fonksiyonlari, gelen parametre degerlerini eskisiyle degistiriyor..
void Ogrenci::sinifAyarla(int no)
{
    sinif=no;
}

void Ogrenci::notAyarla(float notu)
{
    not_ort=notu;
}

//oku fonksiyonlari.. int,String,Bilgisayar,Tarih ve float tipinde deger dondururler..
int Ogrenci::numOku() const
{
    return ogr_no;
}

String Ogrenci::adOku() const
{
    return ad;
}

String Ogrenci::soyadOku() const
{
    return soyad;
}

Tarih Ogrenci::dogumOku() const
{
    return dogum;
}

Tarih Ogrenci::kayitOku() const
{
    return kayit;
}

Bilgisayar Ogrenci::pcOku() const
{
    return pc;
}

int Ogrenci::sinifOku() const
{
    return sinif;
}

float Ogrenci::notOku() const
{
    return not_ort;
}

//output << operatorunun asiri yuklenmesi.. Bilgisayar sinifina ait degiskenleri yazdirmak icin onlari ayri cagirdim..
ostream &operator<<(ostream &output, const Ogrenci &ogr)
{
    output << std::left << setw(7)  << ogr.ogr_no << setw(16) << ogr.ad <<  setw(21) << ogr.soyad <<  setw(6)
    << ogr.sinif << setw(8) << ogr.not_ort << ogr.dogum <<" "<< ogr.kayit <<endl;
    return output;
}
