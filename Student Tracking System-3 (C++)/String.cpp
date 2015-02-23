#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#include "String.h"

String::String(int s) //sadece integer tipinde boyut parametresi alan yapýcý fonksiyon..
{
    size=s; //boyut ayarlanýp yeni alan yaratýlýyor..
    ptr=new char[size];
    ptr[0]='\0'; //NULL'a atandý..
}

String::String(const char *p) //karakter dizisi þeklinde parametre alan yapýcý fonksiyon..
{
    if(p!=NULL) //eger gelen deger null degilse gerekli kopyalama islemleri yapiliyor..
    {
        size=strlen(p); //boyut ayarlanýp yeni alan yaratýlýyor..
        ptr=new char[size+1];
        strcpy(ptr,p);
        strupr(ptr);
    }
    else strcpy(ptr,p);
}

String::String(const String &s) //String tipinde parametre alan yapýcý fonksiyon..
{
    size=s.size; //boyut ayarlanýp yeni alan yaratýlýyor..
    ptr=new char[size+1];
    strcpy(ptr,s.ptr);
    strupr(ptr);
}

String::~String()
{
    delete [] ptr;
}

const String &String::operator=(const String &s) // = operatorunun asiri yuklenmesi..
{
    if(*this==s)
        return *this;

    delete [] ptr;
    size = strlen(s.ptr);
    ptr = new char[size+1];
    strcpy(ptr,s.ptr);

    return *this;
}
// == karsilastirma operatorunun iki farkli sekilde asiri yuklenmesi..
bool String::operator==(const String &right) const
{
    if (strcmp(ptr,right.ptr)==0)
        return true;

    return false;
}

bool String::operator==(const char *s) const
{
    if(strcmp(ptr,s)==0)
        return true;
    return false;
}

// input >> ve output << operatorlerinin asiri yuklenmesi..
ostream &operator<<(ostream &output, const String &s)
{
    output << s.ptr;
    return output;
}

istream &operator>>(istream &input, String &s)
{
    char tmp[s.size];
    input >> tmp;
    s=String(tmp);
    return input;
}
