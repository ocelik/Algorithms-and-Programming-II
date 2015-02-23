#ifndef TARIH_H
#define TARIH_H

#include <iostream>

using std::ostream;
using std::istream;

class Tarih
{
    //output << ve input >> operatorunu uye olmayan fonksiyon seklinde friend olarak asiri yukledim..
    friend ostream &operator<<(ostream&,const Tarih &);
    friend istream &operator>>(istream&,Tarih &);

private:
    int gun; //Tarihe dair degiskenleri integer tipinde tanimladim..
    int ay;
    int yil;

public:
    Tarih(int=22,int=4,int=1993); //ilk degerleri atanmis 3 parametre degeri alan yapici fonksiyon..
    bool operator==(const Tarih &)const; //karsilastirma operatorlerinin asiri yuklendigi fonksiyonlar..
    bool operator!=(const Tarih &right) const
    {
        return !(*this==right);
    }
    bool operator>(const Tarih &)const;
    bool operator<(const Tarih &)const;

    int gunOku() const; //tarihe ait degiskenleri donduren uye fonksiyonlar..
    int ayOku() const; //eger const bir nesne yaratilirsa o nesne tarafindan kullanilmalari icin const tanimlanmislardir..
    int yilOku() const;
};

#endif


