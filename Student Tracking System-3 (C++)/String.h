#ifndef STRING_H
#define STRING_H

#include <iostream>

using std::ostream;
using std::istream;

class String
{
    //output << ve input >> operatorunu uye olmayan fonksiyon seklinde friend olarak asiri yukledim..
    friend ostream &operator<<(ostream &, const String &);
    friend istream &operator>>(istream &, String &);

private:
    int size; //Karakter dizisini ve uzunlugu tutan degiskenleri tanimladim..
    char *ptr;

public:
    String(int=0); //3 farkli parametre alan yapici fonksiyon kullandim;
    String(const char *p); //sadece boyutu ile, karakter dizisi þeklinde veya kendi String tipinde bir nesne yaratýlmasýna karþýn..
    String(const String &s);
    ~String(); //yikici fonksiyon..

    const String &operator=(const String &); //Esittir atama operatorunu asiri yukledim..
    bool operator==(const char*) const; //Karsilastirma operatorlerini asiri yukledim..
    bool operator==(const String &) const;
    bool operator!=(const String &right) const
    {
        return !(*this==right);
    }
};

#endif
