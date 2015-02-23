#include <iostream>
#include <iomanip>

using namespace std;

#include "Bilgisayar.h"
#include "String.h"

Bilgisayar::Bilgisayar(String num,String mrk,String mod) //yapici fonksiyon..
{
    numara=num;
    marka=mrk;
    model=mod;
}
//get fonksiyonlari..
String Bilgisayar::numaraOku() const
{
    return numara;
}

String Bilgisayar::modelOku() const
{
    return model;
}

String Bilgisayar::markaOku() const
{
    return marka;
}

//input >> ve output << operatorlerinin asiri yuklenmesi..
ostream &operator<<(ostream &output, const Bilgisayar &pc)
{
    //formatli cikti icin bu fonksiyon icinde liste isimlerini yazdim..

    cout << endl << "Tasinabilir bilgisayar:"<<endl;
    cout <<std::left<<setw(14)<<"Seri Numarasi"<<setw(11)<< "Marka"<<setw(10) << "Model"<<endl;
    cout <<std::left<<setw(14)<<"-------------"<< setw(11)<< "----------" <<setw(10) << "----------"<<endl;
    output <<std::left<<setw(14)<< pc.numara<<setw(11)<<pc.marka<<setw(11)<<pc.model<<endl;
    return output;
}

istream &operator>>(istream &input, Bilgisayar &pc)
{
    cout << "\t\tSeri numarasini giriniz: ";
    input >> pc.numara;
    cout << "\t\tMarkasini giriniz: ";
    input >> pc.marka;
    cout << "\t\tModelini giriniz: ";
    input >> pc.model;

    return input;
}
