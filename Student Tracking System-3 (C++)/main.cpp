#include <iostream>
#include "stdlib.h"
#include <cstdio>
#include "String.h"
#include <iomanip>
#include "Tarih.h"
#include "Bilgisayar.h"
#include "Ogrenci.h"
#include "Ogrenci_Dizisi.h"

using namespace std;

int menu_goruntule(void);

int main()
{
    Ogrenci_Dizisi Ogrenciler;
    int ogr_no,secenek,sinif,bir_yil,sinif_ogr_say,i;
    Ogrenci *bir_ogrenci;
    String ad(15), soyad(20);
    String marka(10),model(12),numara(12);
    Bilgisayar bir_pc;
    Tarih dogum_tarihi,kayit_tarihi, bir_tarih;
    double not_ort;

    do
    {
        secenek=menu_goruntule();
        switch (secenek)
        {
        case 1:
            cout << "Yeni Kazanan Ogrencinin;"<<endl<<endl;
            cout << "\tNumarasini giriniz(1-1000): ";
            cin >> ogr_no;
            if(Ogrenciler.ara(ogr_no)==NULL) //eger girilen numarada ogrenci yoksa ekleme islemi icin gereken bilgiler alinir..
            {
                cout << "\tAdini giriniz: ";
                fflush(stdin);
                cin >> ad;

                cout << "\tSoyadini giriniz: ";
                fflush(stdin);
                cin >> soyad;

                cout << "\tDogum tarihini 29-10-1923 biciminde giriniz: ";
                cin >> dogum_tarihi;

                cout << "\tKayit tarihini 29-10-1923 biciminde giriniz: ";
                cin >> kayit_tarihi;

                cout << "\tBilgisayarina ait; "<<endl;
                fflush(stdin);
                cin >> bir_pc;

                bir_ogrenci=new Ogrenci(ogr_no,ad,soyad,dogum_tarihi,kayit_tarihi,bir_pc); //yeni alan yaratilarak bilgilere bir_ogrenci'ye aktariliyor..
                Ogrenciler.ekle(bir_ogrenci); //Ogrenci_Dizisi'ndeki ekle fonksiyonu ile bir_ogrenci , iþaretçi dizisine ekleniyor..

                cout <<endl<< "*** Ogrenci basariyla kaydedilmistir.. ***"<<endl;
            }
            else cout << "Bu numarada ogrenci zaten vardir..!" <<endl; //eger girilen numarada ogrenci varsa uyari mesaji verilerek ana menüye dönülür..
            break;
        case 2:
            cout << "Yatay Gecisle Gelen Ogrencinin;" <<endl<<endl;
            cout << "\tNumarasini giriniz(1-1000): ";
            cin >> ogr_no;
            if(Ogrenciler.ara(ogr_no)==NULL) //eger girilen numarada ogrenci yoksa ekleme islemi icin gereken bilgiler alinir..
            {
                cout << "\tAdini giriniz: ";
                fflush(stdin);
                cin >> ad;

                cout << "\tSoyadini giriniz: ";
                fflush(stdin);
                cin >> soyad;

                cout << "\tDogum tarihini 29-10-1923 biciminde giriniz: ";
                cin >> dogum_tarihi;

                cout << "\tKayit tarihini 29-10-1923 biciminde giriniz: ";
                cin >> kayit_tarihi;

                cout << "\tBilgisayarina ait; "<<endl;
                fflush(stdin);
                cin >> bir_pc;

                cout << "\tSinifini giriniz: "; //Yatay gecisle gelen ogrenciden bilgilere ek olarak sinif ve not ortalamasi da alinir..
                cin >> sinif;

                cout << "\tNot ortalamasini giriniz: ";
                cin >> not_ort;

                bir_ogrenci=new Ogrenci(ogr_no,ad,soyad,dogum_tarihi,kayit_tarihi,bir_pc,sinif,not_ort); //bir_ogrenci icin Ogrenci tipinde alan yaratilarak bilgiler aktariliyor..
                Ogrenciler.ekle(bir_ogrenci);

                cout << endl << "*** Ogrenci basariyla kaydedilmistir.. ***"<<endl;
            }
            else cout << "Bu numarada ogrenci zaten vardir..!" <<endl;
            break;
        case 3:
            for(i=1; i<MAX_OGR_SAY; i++) //Tum dizi taranarak var olan ogrenciler icin yeni sinif ve not ortalamasi aliniyor..
            {
                bir_ogrenci=Ogrenciler.ara(i);
                if(bir_ogrenci!=NULL)
                {
                    cout << i <<" numarali ogrencinin;" << endl;
                    cout <<"\tYeni sinifini giriniz:";
                    cin >> sinif;
                    bir_ogrenci->sinifAyarla(sinif);

                    cout <<"\tYeni not ortalamasini giriniz:";
                    cin >> not_ort;
                    bir_ogrenci->notAyarla(not_ort);
                }
            }
            cout << "***Guncellemeler basariyla yapilmistir..***"<<endl;
            break;
        case 4:
            cout <<"Kaydi silinecek ogrencinin numarasini giriniz(1-1000): ";
            cin >> ogr_no;
            bir_ogrenci=Ogrenciler.ara(ogr_no);
            if(bir_ogrenci!=NULL) //Eger girilen numarada ogrenci varsa silme islemi gerceklesir..
            {
                Ogrenciler.sil(bir_ogrenci); //Ogrenci_Dizisi sýnýfýndaki sil fonksiyonu ile silme yapilir..
                delete bir_ogrenci; //Alan temizlenir..
                cout << "***Ogrenci basariyla silinmistir..***"<<endl;
            }
            else cout << "Boyle bir ogrenci zaten yoktur..!"<<endl; //eger oyle bir ogrenci yoksa uyari mesaji verilir..
            break;
        case 5:
            cout <<"Bilgilerini istediginiz ogrencinin numarasini giriniz(1-1000): ";
            cin >> ogr_no;
            bir_ogrenci=Ogrenciler.ara(ogr_no);
            if(bir_ogrenci!=NULL) //Girilen numarada ogrenci varsa bilgisi ekrana yazdirilir..
            {
                cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
                cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
                cout << *bir_ogrenci<< bir_ogrenci->pcOku();
            }
            else cout << endl <<"Bu numarada ogrenci yoktur..!"<<endl;
            break;
        case 6:
            cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
            cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
            cout << Ogrenciler; //Okuldaki tum ogrencileri listeler.. Ogrenci_Dizisi'nda output<< operatorunun asiri yuklenmesi sayesinde..
            break;
        case 7:
            sinif_ogr_say=0; //Bir siniftaki ogrenci sayisini tutar. Her 7. maddeye giriste sifirlanir..

            cout <<"Bilgilerini gormek istediginiz sinifin numarasini giriniz:";
            cin >> sinif;
            cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
            cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
            for(i=1; i<MAX_OGR_SAY; i++) //Tum numaralar gezilerek var olan ogrencilerden sinif numarasi girilene esit olanlar ekrana yazdirilir..
            {
                bir_ogrenci=Ogrenciler.ara(i);
                if(bir_ogrenci!=NULL)
                {
                    if(bir_ogrenci->sinifOku()==sinif)
                    {
                        cout << *bir_ogrenci;
                        sinif_ogr_say++; //Sinifin ogrenci sayisi artirilir..
                    }
                }
            }
            cout << endl << "Sinifin ogrenci sayisi: " << sinif_ogr_say <<endl;
            break;
        case 8:
            cout << "Adi giriniz: ";
            cin >> ad;
            cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
            cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
            for(i=1; i<MAX_OGR_SAY; i++) //Tum numaralar gezilerek var olan ogrencilerden adi girilen ada esit olanlar yazdirilir..
            {
                bir_ogrenci=Ogrenciler.ara(i);
                if(bir_ogrenci!=NULL)
                {
                    if(bir_ogrenci->adOku()==ad)
                        cout << *bir_ogrenci;
                }
            }
            break;
        case 9:
            cout << "Tarihi 29-10-1923 biciminde giriniz: ";
            cin >> bir_tarih;
            cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
            cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
            for(i=1; i<MAX_OGR_SAY; i++) //Tum numaralar gezilerek var olan ogrencilerden dogum tarihi girilen tarihten kucuk olanlar yazdirilir..
            {
                bir_ogrenci=Ogrenciler.ara(i);
                if(bir_ogrenci!=NULL)
                {
                    if(bir_ogrenci->dogumOku()<bir_tarih)
                        cout << *bir_ogrenci;
                }
            }
            break;
        case 10:
            cout << "Yili giriniz: ";
            cin >> bir_yil;
            cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
            cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
            for(i=1; i<MAX_OGR_SAY; i++) //Tum numaralar gezilerek var olan ogrencilerden kayit yili girilen yildan buyuk olanlar yazdirilir..
            {
                bir_ogrenci=Ogrenciler.ara(i);
                if(bir_ogrenci!=NULL)
                {
                    if(bir_ogrenci->kayitOku().yilOku()>bir_yil)
                        cout << *bir_ogrenci;
                }
            }
            break;
        case 11:
            cout <<"Tasinabilir bilgisayarin seri numarasini giriniz: ";
            cin >> numara;
            for(i=1; i<MAX_OGR_SAY; i++) //Tum numaralar gezilerek var olan ogrencilerin bilgisayarinin seri numarasi;
            {                               //girilen seri numarasina esit olanlar yazdirilir..
                bir_ogrenci=Ogrenciler.ara(i);
                if(bir_ogrenci!=NULL)
                {
                    if(bir_ogrenci->pcOku().numaraOku()==numara)
                    {
                        cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
                        cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
                        cout << *bir_ogrenci;
                        break;
                    }
                }
            }
            break;
        case 12:
            cout <<"Markayi giriniz: ";
            cin >> marka;
            cout <<"Modeli giriniz: ";
            cin >> model;
            cout << "Ogr No Ad              Soyad                Sinif Not Ort Dogum Tarh Kayit Tarh"<<endl;
            cout << "------ --------------- -------------------- ----- ------- ---------- ----------"<<endl;
            for(i=1; i<MAX_OGR_SAY; i++)  //Tum numaralar gezilerek var olan ogrencilerin bilgisayarinin marka ve model,
            {                                   //girilen marka ve modele esit olanlar yazdirilir..
                bir_ogrenci=Ogrenciler.ara(i);
                if(bir_ogrenci!=NULL)
                {
                    if(bir_ogrenci->pcOku().modelOku()==model && bir_ogrenci->pcOku().markaOku()==marka)
                        cout << *bir_ogrenci;
                }
            }
            break;
        }
    }
    while(secenek!=13); //Girilen secenek 13 oldugunda program sonlanir..
    return 0;
}

int menu_goruntule(void) //menu goruntuleme fonksiyonu..
{
    int secim;

    cout << endl << "\t *****************ANA MENU************************" << endl;
    cout << "1. Yeni Kazanan Ogrenciyi Kaydet" <<endl;
    cout << "2. Yatay Gecisle Gelen Ogrenciyi Kaydet" << endl;
    cout << "3. Yil Sonu Sinif ve Not Ortalamasi Guncelle" << endl;
    cout << "4. Bir Ogrencinin Kaydini Sil" << endl;
    cout << "5. Bir Ogrencinin Bilgilerini Goruntule" << endl;
    cout << "6. Okuldaki Tum Ogrencileri Listele" << endl;
    cout << "7. Bir Sinifta Okuyan Ogrencileri Listele" << endl;
    cout << "8. Belirli Bir Ada Sahip Ogrencileri Listele" << endl;
    cout << "9. Belirli Bir Tarihten Once Dogan Ogrencileri Listele" << endl;
    cout << "10. Belirli Bir Yildan Sonra Bolume Kaydedilmis Ogrencileri Listele" << endl;
    cout << "11. Bir Tasinabilir Bilgisayarin Verilmis Oldugu Ogrenciyi Goruntule" << endl;
    cout << "12. Belirli Bir Marka ve Model Bilgisayarin Verilmis Oldugu Ogrencileri Listele" << endl;
    cout << "13. Cikis" << endl;

    do
    {
        cout << endl << "Seciminizi Giriniz:";
        cin >> secim;
    }
    while(secim<1 || secim>13); //Ana menu icin secim 1-13 arasinda oldugunda secenegi dondurur..
    return secim;
}
