#include <iostream>
#include "String.h"

using namespace std;

#include "Ogrenci_Dizisi.h"
#include "Ogrenci.h"
#include "Tarih.h"
#include "Bilgisayar.h"

Ogrenci_Dizisi::Ogrenci_Dizisi() //yapici fonksiyon, isaretci dizisinin hepsi NULL'a ataniyor..
{
    for(int i=0; i<MAX_OGR_SAY; i++)
        dizi[i]=NULL;
}

void Ogrenci_Dizisi::ekle(Ogrenci *yeni) //ekle fonksiyonu..
{
    if(dizi[yeni->numOku()]==NULL) //eger bossa ekleme yapiliyor..
        dizi[yeni->numOku()]=yeni;
    else cout <<"Bu numarada ogrenci vardir.." << endl;
}

Ogrenci *Ogrenci_Dizisi::ara(int arananNo) //arama fonksiyonu..
{
    return dizi[arananNo]; //dizinin istenen indisi donduruluyor..
}

void Ogrenci_Dizisi::sil(Ogrenci *silinecek) //silme fonksiyonu..
{
    dizi[silinecek->numOku()]=NULL; //NULL'a ataniyor..
}

Ogrenci **Ogrenci_Dizisi::diziOku() //dizi donduruluyor..
{
    return dizi;
}

//output << operatorunun asiri yuklenmesi..
ostream &operator<<(ostream &output, Ogrenci_Dizisi &bir_ogrenci_dizisi)
{
    Ogrenci **bir_dizi=bir_ogrenci_dizisi.diziOku();
    Ogrenci *birOgrenci;

    for(int i=1; i<MAX_OGR_SAY; i++)
    {
        if(bir_dizi[i]!=NULL)
         {
            birOgrenci=bir_dizi[i];
            output<<*birOgrenci;
         }
    }
    return output;
}
