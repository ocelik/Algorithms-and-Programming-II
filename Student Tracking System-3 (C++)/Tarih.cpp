#include <iostream>
#include <iomanip>

using namespace std;

#include "Tarih.h"

Tarih::Tarih(int g,int a,int y):gun(g),ay(a),yil(y) {} //yapici fonksiyon..

// karsilastirma operatorlerininin (==,<,>,=>,<=) asiri yuklendigi fonksiyonlar..
bool Tarih::operator==(const Tarih &right) const
{
    if(yil==right.yil && ay==right.ay && gun==right.gun)  //eger gun,ay ve yil esitse 1,degilse 0 degeri dondurur..
        return true;
    return false;
}

bool Tarih::operator>(const Tarih &right) const //buyuktur operatorunun asiri yuklenmesi, 1 veya 0 degeri dondurur..
{
    if(yil<right.yil)
        return false;
    else if(yil==right.yil)
    {
        if(ay<right.ay)
            return false;
        else if (ay==right.ay && gun<right.gun)
            return false;
    }
    return true;
}

bool Tarih::operator<(const Tarih &right) const //kucuktur operatorunun asiri yuklenmesi, 1 veya 0 degeri dondurur..
{
    if(yil<right.yil)
        return true;
    else if(yil==right.yil)
    {
        if(ay<right.ay)
            return true;
        else if(ay==right.ay && gun<right.gun)
            return true;
    }
    return false;
}

//input ve output operatorlerinin asiri yuklenmesi..
ostream &operator<<(ostream &output, const Tarih &birTarih)
{
    if(birTarih.gun<10) //eger girilen gun veya ay 10'dan kucukse yazdirmada sayinin basina 0 eklenir..
        output << "0" << birTarih.gun <<"-";
    else output << birTarih.gun <<"-";
    if(birTarih.ay<10)
        output <<"0"<<birTarih.ay<<"-";
    else output <<birTarih.ay<<"-";
    output<<birTarih.yil;

    return output;
}

istream &operator>>(istream &input, Tarih &birTarih)
{
    input >> birTarih.gun;
    input.ignore();
    input >> birTarih.ay;
    input.ignore();
    input >> birTarih.yil;

    return input;
}
//gun, ay ve yili donduren fonksiyonlar..
int Tarih::gunOku() const
{
    return gun;
}

int Tarih::ayOku() const
{
    return ay;
}

int Tarih::yilOku() const
{
    return yil;
}
