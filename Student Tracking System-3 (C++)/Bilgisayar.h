#ifndef BILGISAYAR_H
#define BILGISAYAR_H

#include "String.h"

class Bilgisayar
{
    //output << ve input >> operatorunu uye olmayan fonksiyon seklinde friend olarak asiri yukledim..
    friend ostream &operator<<(ostream &, const Bilgisayar &);
    friend istream &operator>>(istream&,Bilgisayar &);

private:
    String numara; //String tipinde 3 farkli private seklinde uye degiskenleri tanimladim..
    String marka;
    String model;

public:
    Bilgisayar(String="",String="",String=""); //Yapici fonksiyon 3 farkli String degeri alir,ilk degerleri bostur..

    String numaraOku() const; //String tipinde deger donduren const tanimli get fonksiyonlari..
    String markaOku() const;
    String modelOku() const;
};

#endif
