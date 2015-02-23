#include <stdio.h>
#include <stdlib.h>

#define MAX_OGRENCI_SAY 900
#define BOS_KAYIT 0
#define MAX_DERS_SAY 90

struct ogrenciler //bir ogrenci ile ilgili cesitli verileri tutan yapi tanimlamasi yapildi.
{
    int ogr_no;
    char ad_soyad[30];
    int sinif_no;
    int kredi_say;
    float not_ort;
};

struct dersler //bir derse iliskin verileri tutan yapi tanimlamasi yapildi.
{
    int ders_kodu;
    char ders_adi[25];
    int ders_krd;
    char ogr_uyesi[30];
    char derslik_adi[20];
};

typedef struct dersler Ders_type;
typedef struct ogrenciler Ogr_type;

int menu_goruntule();
int bir_ogrenci_goruntule(FILE *);
int bir_ders_goruntule(FILE *);
void donemi_listele (FILE *);
void bir_ogrenci_dersleri (FILE *, FILE *, FILE *);
void bir_ders_ogrencileri (FILE *, FILE *, FILE *);
void sinifi_listele(FILE *);
void yeni_ogrenci_ekle(FILE *);
void ogrenci_sil(FILE *, FILE *);
void guncelleme (FILE *);
void yeni_ders_ekle(FILE *);
void not_girilmesi (FILE *, FILE *,FILE *);
void istatistik (FILE *);
int sayi_al(int, int);

int main()
{
    //Dosyalar formatlarina gore acilarak kullanicinin sectigi fonksiyona girilir ve program cikisinda dosyalar kapatilir.
    FILE *fOgr;
    FILE *fDers;
    FILE *fNot;

    int secenek;

    if((fOgr=fopen("ogrenciler.dat","rb+"))==NULL)
        printf("Ogrenciler dosyasi acilamadi.");

    else
    {
        if((fDers=fopen("dersler.dat","rb+"))==NULL)
            printf("Dersler dosyasi acilamadi.");

        else
        {
            if ((fNot=fopen("notlar.txt","a+"))==NULL)
                printf("Notlar dosyasi acilamadi.");
            else
            {
                do
                {
                    secenek=menu_goruntule();
                    switch (secenek)
                    {
                    case 1:
                        bir_ogrenci_goruntule(fOgr);
                        break;
                    case 2:
                        bir_ogrenci_dersleri(fOgr,fDers,fNot);
                        break;
                    case 3:
                        sinifi_listele(fOgr);
                        break;
                    case 4:
                        istatistik(fOgr);
                        break;
                    case 5:
                        bir_ders_goruntule(fDers);
                        break;
                    case 6:
                        bir_ders_ogrencileri(fOgr,fDers,fNot);
                        break;
                    case 7:
                        donemi_listele(fDers);
                        break;
                    case 8:
                        yeni_ogrenci_ekle(fOgr);
                        break;
                    case 9:
                        yeni_ders_ekle(fDers);
                        break;
                    case 10:
                        guncelleme(fDers);
                        break;
                    case 11:
                        not_girilmesi(fDers,fNot,fOgr);
                        break;
                    case 12:
                        ogrenci_sil(fOgr, fNot);
                        break;
                    }
                }
                while(secenek!=13);
            }
        }
    }
    fclose(fOgr);
    fclose(fNot);
    fclose(fDers);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////
int menu_goruntule(void)
{
    int secim;

     printf("\n\t*****************ANA MENU************************\n\n");
     printf("\n        1>  BIR OGRENCI BILGILERI\n");
     printf("        2>  BIR OGRENCI BILGILERI & DERSLERININ BILGILERI\n");
     printf("        3>  BIR SINIFIN OGRENCILERININ BILGILERI\n");
     printf("        4>  BOLUMUN BASARI ISTATISTIKLERI\n");
     printf("        5>  BIR DERSIN BILGILERI\n");
     printf("        6>  BIR DERSIN BILGILERI VE DERSI ALAN OGRENCILER\n");
     printf("        7>  BIR DONEMDE VERILEN DERSLERIN BILGILERI\n");
     printf("        8>  YENI OGRENCI EKLEME\n");
     printf("        9>  YENI DERS EKLEME\n");
     printf("       10>  BIR DERSIN OGRETIM UYESI & DERSLIGINI GUNCELLEME\n");
     printf("       11>  BIR DERSI ALAN OGRENCILERIN NOTLARININ GIRILMESI\n");
     printf("       12>  OGRENCI KAYDI SILME\n");
     printf("       13>  CIKIS\n");
    printf("\n");
    do
    {
        printf("\nSeciminizi Giriniz:");
        scanf("%d", &secim);
    }
    while(secim<1 || secim>13);

    return secim;
}
//////////////////////////////////////////////////////////////////////////////
int bir_ogrenci_goruntule(FILE *fOgr) //Ogrenciler dosyasina erisim icin fOgr isaretcisi parametre olarak alinir.
{
    Ogr_type bir_ogr; //yapi tipinde bir_ogr degiskeni tanimlanir.
    int ogr_no;
    int kayit_no;

    printf("Bilgilerini istediginiz ogrencinin numarasini giriniz(100-999): ");
    ogr_no=sayi_al(100,999); //sayi_al fonksiyonu ile 100-999 arasinda bir ogrenci numarasi girdisi isteniyor..

    kayit_no=ogr_no-99; //Ogrenci numarasi,dosyanin kayitlarina erismek icin bir anahtar deger olarak kullanilir.Kayit numarasi hesaplanir.
    fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET); //fOgr,dosya baslangicina getirilir.
    fread(&bir_ogr,sizeof(Ogr_type),1,fOgr); //Dogrudan erisimli dosyadan ilk kayit okunur.

    if(bir_ogr.ogr_no==BOS_KAYIT) //Bir ogrencinin numarasinin 0 olmasi o kaydin bos oldugu anlamini tasir.
        printf("Girdiginiz ogrenci numarasina sahip ogrenci bulunmamaktadir.\n");

    else
    {
        printf("Sira No Ogr No Ad Soyad                       Sinif Kredi Say Not Ort \n");
        printf("------- ------ ------------------------------ ----- --------- ------- \n");
        printf("%-7d %-6d %-30s %-5d %-9d %.2f\n", kayit_no,bir_ogr.ogr_no,bir_ogr.ad_soyad,bir_ogr.sinif_no,bir_ogr.kredi_say,bir_ogr.not_ort);
    }
    rewind(fOgr);
    return ogr_no;
}
//////////////////////////////////////////////////////////////////////////////
void bir_ogrenci_dersleri(FILE *fOgr, FILE *fDers, FILE *fNot) //Tum dosyalara erisim icin isaretciler parametre olarak alinir.
{
    int ogr_no, bulundu=0;
    int ders_kodu, ogr_no2, ogr_not,kayit_no;
    Ders_type bir_ders; //yapi tipinde bir_ders degiskeni tanimlanir.
    Ogr_type bir_ogr; //yapi tipinde bir_ogr degiskeni tanimlanir.

    ogr_no=bir_ogrenci_goruntule(fOgr);

    kayit_no=ogr_no-99;
    fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
    fread(&bir_ogr,sizeof(Ogr_type),1,fOgr);

    if(bir_ogr.ogr_no!=BOS_KAYIT)
    {
        printf("\nBu donem aldigi dersler:\n");
        printf("Ders Kodu Ders Adi             Kredi Notu\n");
        printf("--------- -------------------- ----- ----\n");

        fscanf(fNot,"%d %d %d", &ders_kodu, &ogr_no2, &ogr_not); //Siradan erisimli bir dosyadan veriler okunur.

        while (!feof(fNot)) //Dongu,fNot isaretcisiyle notlar dosyasinin sonuna gelinceye kadar doner.
        {
            if (ogr_no==ogr_no2) //Kullanicinin girdigi ogrenci numarasi,notlar dosyasindan okunan ogrencinin numarasina esitse
            {
                fseek(fDers,(ders_kodu-1)*sizeof(Ders_type), SEEK_SET);
                fread(&bir_ders,sizeof(Ders_type),1,fDers); //dersler dosyasindan ogrencinin ders bilgileri okunur.

                printf("%-9d %-20s %-5d %d\n", ders_kodu, bir_ders.ders_adi, bir_ders.ders_krd, ogr_not);
                bulundu=1; //Yukaridaki kosul saglandigi icin dersleri goruntulenmek istenen ogrenci bulunmustur ve flag islemi yapilmistir.
            }
            fscanf(fNot, "%d %d %d", &ders_kodu, &ogr_no2, &ogr_not); //Ogrencinin bulunamamasina karsilik(kosula girilmediyse) notlar dosyasindan takrar okuma yapilir.
        }
        if (bulundu==0) //Girilen ogrenci numarasina sahip ogrenci numarasi bulunamadiysa bir mesaj yazdirlir.
            printf("Ogrencinin bu donem aldigi ders yoktur.");
    }
    //Isaretciler dosya baslangicina getirilir.
    rewind(fNot);
    rewind(fDers);
    rewind(fOgr);
    return;
}
////////////////////////////////////////////////////////////////////////////
void sinifi_listele(FILE *fOgr)
{
    int i,j,sinif_no,h=0;

    Ogr_type bir_ogr[MAX_OGRENCI_SAY]; //maximum ogrenci sayisina sahip Ogr_type (yapi) tipinde bir_ogr dizisi tanimlanmistir.
    Ogr_type gecici[MAX_OGRENCI_SAY]; //maximum ogrenci sayisina sahip Ogr_type (yapi) tipinde gecici dizisi tanimlanmistir.

    printf("Bilgilerini istediginiz sinifin numarasini giriniz: ");
    sinif_no=sayi_al(1,4); //sayi_al fonksiyonu ile 1-4 arasinda bir sinif numarasi girdisi isteniyor..

    for(i=0; i<MAX_OGRENCI_SAY; i++) //ogrenciler dosyasindan tum ogrencilerin bilgileri okunmustur.
        fread(&bir_ogr[i],sizeof(Ogr_type),1,fOgr);

    for (j=0; j<MAX_OGRENCI_SAY; j++) //Ogrencilerin not ortalamalari bubble sort ile buyukten kucuge siralanmistir.
    {
        for(i=1; i<MAX_OGRENCI_SAY-j; i++)
        {
            if (bir_ogr[i-1].not_ort<bir_ogr[i].not_ort) //Ust siradaki ogrencinin not ortalamasi alt siradakinden kucukse yer degistirirler.
            {
                gecici[i]=bir_ogr[i-1];
                bir_ogr[i-1]=bir_ogr[i];
                bir_ogr[i]=gecici[i];
            }
            else if (bir_ogr[i-1].not_ort==bir_ogr[i].not_ort) //Not ortalamalarini esit olan ogrencilerin kredi sayilarina bakilir.
            {
                if (bir_ogr[i-1].kredi_say<bir_ogr[i].kredi_say) //Kredi sayilarina gore de buyukten kucuge siralama yapilir.Ust siradaki ogrencinin kredi sayisi alt siradakinden kucukse yer degisikligi yapilir.
                {
                    gecici[i]=bir_ogr[i-1];
                    bir_ogr[i-1]=bir_ogr[i];
                    bir_ogr[i]=gecici[i];
                }
            }
        }
    }
    printf("Sira No Ogr No Ad Soyad                  Sinif Kredi Say Not Ort\n");
    printf("------- ------ ------------------------- ----- --------- -------\n");
    for (i=0; i<MAX_OGRENCI_SAY; i++)
    {
        if(bir_ogr[i].ogr_no!=BOS_KAYIT && sinif_no==bir_ogr[i].sinif_no) //Okunan kayitlardan bos olmayanlar ve kullanicidan alinan sinif numarasina esit ogrencilerin sinif numarasi varsa,ogrenci bilgileri yazdirilir.
        {
            h++;
            printf("%-7d %-6d %-25s %-5d %-9d %.2f\n",h, bir_ogr[i].ogr_no,bir_ogr[i].ad_soyad,bir_ogr[i].sinif_no,bir_ogr[i].kredi_say,bir_ogr[i].not_ort);
        }
    }

    rewind(fOgr);
    return;
}
///////////////////////////////////////////////////////////////////////////////////
int bir_ders_goruntule(FILE *fDers)
{
    Ders_type bir_ders;
    int ders_kodu;

    printf("Bilgilerini istediginiz dersin kodunu giriniz(10-89): ");
    ders_kodu=sayi_al(10,89);

    fseek(fDers,(ders_kodu-1)*sizeof(Ders_type), SEEK_SET);
    fread(&bir_ders,sizeof(Ders_type),1,fDers);

    if (bir_ders.ders_kodu==BOS_KAYIT)
        printf("Girdiginiz ders kodunda ders bulunamamistir.\n");

    else
    {
        printf("\n");
        printf("Ders Kodu Ders Adi             Kredi Ogretim Uyesi             Derslik\n");
        printf("--------- -------------------- ----- ------------------------- ---------------\n");
        printf("%-9d %-20s %-5d %-25s %s\n", bir_ders.ders_kodu,bir_ders.ders_adi,bir_ders.ders_krd,bir_ders.ogr_uyesi,bir_ders.derslik_adi);
        printf("\n");
    }
    rewind(fDers);

    return ders_kodu;
}
////////////////////////////////////////////////////////////////////////////////////
void bir_ders_ogrencileri(FILE *fOgr, FILE *fDers, FILE *fNot)
{
    int ders_kodu_al,i,bulundu=0;
    Ogr_type bir_ogr[MAX_OGRENCI_SAY];
    int ogr_no, ogr_not, ders_kodu2;
    int ogr_say=0, not_top=0, altmis_say=0;
    float genel_not_ort, altmis_yuzde;
    Ders_type bir_ders;

    ders_kodu_al=bir_ders_goruntule(fDers);

    fseek(fDers,(ders_kodu_al-1)*sizeof(Ders_type), SEEK_SET);
    fread(&bir_ders,sizeof(Ders_type),1,fDers);

    if (bir_ders.ders_kodu!=BOS_KAYIT)
    {
        printf("Bu Donem Alan Ogrenciler:\n");
        printf("Ogr No Ad Soyad                       Sinif Notu\n");
        printf("------ ------------------------------ ----- ----\n");

        fscanf(fNot,"%d %d %d", &ders_kodu2, &ogr_no, &ogr_not); //Notlar dosyasindan okuma yapilir.

        while (!feof(fNot)) //Notlar dosyasinin sonuna  kadar gidebilmek icin  dongu kurulmustur.
        {
            if(ders_kodu_al==ders_kodu2) //Kullanicidan alinan ders kodu dosyadan okunan ders koduna esitse,
            {
                for (i=0; i<MAX_OGRENCI_SAY; i++)
                {
                    fread(&bir_ogr[i],sizeof(Ogr_type),1,fOgr); //ogrenciler dosyasindan ogrencinin bilgileri okunur.
                    if (bir_ogr[i].ogr_no==ogr_no) //her iki dosyadan okunan ogrencinin numarasi birbirine esitse ogrencinin bilgileri yazdirilir.
                        printf("%-6d %-30s %-5d %d\n", bir_ogr[i].ogr_no,bir_ogr[i].ad_soyad,bir_ogr[i].sinif_no,ogr_not);
                }
                ogr_say++;
                not_top=not_top+ogr_not;
                if (ogr_not<60)
                    altmis_say++;
                bulundu=1;
            }
            fscanf(fNot,"%d %d %d", &ders_kodu2, &ogr_no, &ogr_not);
        }

        if (bulundu==1)
        {
            genel_not_ort=not_top/ogr_say;
            altmis_yuzde=altmis_say*100/ogr_say;
            printf("\nDersi alan ogrenci sayisi: %d\n",ogr_say);
            printf("Dersin genel not ortalamasi: %.2f\n",genel_not_ort);
            printf("Notu 60'in altinda olan ogr sayisi ve yuzdesi: %d - %.2f\n",altmis_say,altmis_yuzde);
        }
        else printf("Bu dersi alan ogrenci yoktur.");
    }
    rewind(fNot);
    rewind(fOgr);
    rewind(fDers);
    return;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void donemi_listele(FILE *fDers)
{
    int i, donem_no;
    Ders_type bir_ders;
    int kredi_top=0;

    printf("O donemdeki dersleri gormek istediginiz donemi giriniz(1-8): ");
    donem_no=sayi_al(1,8);

    printf("\n");
    printf("Ders Kodu Ders Adi             Kredi Ogretim Uyesi             Derslik\n");
    printf("--------- -------------------- ----- ------------------------- ---------------\n");

    for (i=1; i<MAX_DERS_SAY; i++)
    {
        fread(&bir_ders,sizeof(Ders_type),1,fDers);

        if (bir_ders.ders_kodu<(donem_no*10+9) && bir_ders.ders_kodu>=donem_no*10) //Kullanicidan alinan donem numarasina gore ders kodu araligi belirlenir.
        {
            printf("%-9d %-20s %-5d %-25s %-s\n", bir_ders.ders_kodu,bir_ders.ders_adi,bir_ders.ders_krd,bir_ders.ogr_uyesi,bir_ders.derslik_adi);
            kredi_top=bir_ders.ders_krd+kredi_top; //dersin kredisi,kredi toplamina eklenir.
        }
    }
    printf("\n");
    printf("Derslerin kredi toplami:%d\n",kredi_top);

    rewind(fDers);
    return;
}
///////////////////////////////////////////////////////////////////////////////////////////
void yeni_ogrenci_ekle (FILE *fOgr)
{
    Ogr_type bir_ogr;
    int ogr_numara;
    int kayit_no;

    printf("Eklemek istediginiz ogrencinin numarasini giriniz(100-999): ");
    ogr_numara=sayi_al(100,999);

    kayit_no=ogr_numara-99;
    fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
    fread(&bir_ogr,sizeof(Ogr_type),1,fOgr);

    while(bir_ogr.ogr_no==ogr_numara)
    {
        printf("Girdiginiz ogrenci numarasina sahip ogrenci bulunmaktadir.Yeni bir numara giriniz: \n");
        scanf("%d", &ogr_numara);

        kayit_no=ogr_numara-99;
        fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
        fread(&bir_ogr,sizeof(Ogr_type),1,fOgr);
    }

    if (bir_ogr.ogr_no==BOS_KAYIT)
    {
        bir_ogr.ogr_no=ogr_numara; //Bos kayittaki ogrenci numarasi kismina kullanicinin girdigi ogrenci numarasi atanir.
        printf("Ogrencinin adini giriniz: ");
        fflush(stdin);
        gets(bir_ogr.ad_soyad);

        printf("Ogrencinin sinifini giriniz: ");
        bir_ogr.sinif_no=sayi_al(1,4);

        bir_ogr.kredi_say=0; //Ogrencinin kredi sayisi ve not ortalamasi 0'a atanir.
        bir_ogr.not_ort=0;

        fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
        fwrite(&bir_ogr,sizeof(Ogr_type),1,fOgr); //Eklenen bilgiler dosyadaki belirlenen bos kayda yazdirilir.

        printf("%d numarali ogrenci eklenmistir.\n",ogr_numara);
    }
    rewind(fOgr);
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void yeni_ders_ekle(FILE *fDers)
{
    Ders_type bir_ders;
    int donem_no,ders_kodu,i;

    printf("Eklemek istediginiz dersin donemini giriniz(1-8):");
    donem_no=sayi_al(1,8);

    for(i=0; i<=9; i++)
    {
        ders_kodu=(donem_no*10)+i; //Kullanicidan alinan donem numarasina gore ders kodu belirlenir.

        fseek(fDers,(ders_kodu-1)*sizeof(Ders_type),SEEK_SET);
        fread(&bir_ders,sizeof(Ders_type),1,fDers);

        if(bir_ders.ders_kodu==BOS_KAYIT) //Okunan kayit bos ise,
        {
            bir_ders.ders_kodu=ders_kodu; //Belirlenen ders kodu bu ogrencinin ders kodu olarak atanir.
            printf("Ders kodunuz: %d",(donem_no*10)+i); //Hesaplanan ders kodu yazdirilir.
            printf("\nDersin adini giriniz: ");
            fflush(stdin);
            gets(bir_ders.ders_adi);
            printf("\nDersin kredisini giriniz: ");
            scanf("%d",&bir_ders.ders_krd);
            printf("\nDersin ogretim uyesini giriniz: ");
            fflush(stdin);
            gets(bir_ders.ogr_uyesi);
            printf("\nDersin derslik adini giriniz: ");
            fflush(stdin);
            gets(bir_ders.derslik_adi);

            fseek(fDers,(ders_kodu-1)*sizeof(Ders_type),SEEK_SET);
            fwrite(&bir_ders,sizeof(Ders_type),1,fDers);

            printf("%d kodlu ders eklenmistir.\n",ders_kodu);
            break;
        }
    }
    rewind(fDers);
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void guncelleme (FILE *fDers)
{
    Ders_type bir_ders;
    int ders_kodu;

    printf("Bilgilerini istediginiz dersin kodunu giriniz(10-89):");
    ders_kodu=sayi_al(10,89);

    fseek(fDers,(ders_kodu-1)*sizeof(Ders_type), SEEK_SET);
    fread(&bir_ders,sizeof(Ders_type),1,fDers);

    if (bir_ders.ders_kodu==BOS_KAYIT)
        printf("Girdiginiz ders kodunda ders bulunamamistir.\n");
    else
    {
        printf("Guncellemek istediginiz ogretim uyesinin adini giriniz: ");
        fflush(stdin);
        gets(bir_ders.ogr_uyesi);
        printf("Guncellemek istediginiz dersligin adini giriniz: ");
        fflush(stdin);
        gets(bir_ders.derslik_adi);

        fseek(fDers,(ders_kodu-1)*sizeof(Ders_type),SEEK_SET);
        fwrite(&bir_ders,sizeof(Ders_type),1,fDers);

        printf("%d kodlu ders guncellenmistir.\n",ders_kodu);
    }
    rewind(fDers);
    return;
}
/////////////////////////////////////////////////////////////////////
void ogrenci_sil (FILE *fOgr, FILE *fNot)
{
    FILE *gecici;
    Ogr_type bir_ogr;
    int ogr_numara,ogr_no2,ders_kodu2,ogr_not2;
    int kayit_no;

    printf("Silmek istediginiz ogrencinin numarasini giriniz(100-999):");
    ogr_numara=sayi_al(100,999);

    kayit_no=ogr_numara-99;
    fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
    fread(&bir_ogr,sizeof(Ogr_type),1,fOgr);

    if(bir_ogr.ogr_no==BOS_KAYIT)
        printf("Girdiginiz numaraya sahip ogrenci bulunmamaktadir.\n");
    else
    {
        bir_ogr.ogr_no=BOS_KAYIT;
        bir_ogr.kredi_say=BOS_KAYIT;
        bir_ogr.not_ort=BOS_KAYIT;
        bir_ogr.sinif_no=BOS_KAYIT;

        fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
        fwrite(&bir_ogr,sizeof(Ogr_type),1,fOgr);

        gecici=fopen("gecici.txt","w");

        fscanf (fNot, "%d %d %d", &ders_kodu2, &ogr_no2, &ogr_not2);

        while(!feof(fNot))
        {
            if(ogr_numara!=ogr_no2)
                fprintf (gecici,"%d %d %d\n",ders_kodu2,ogr_no2,ogr_not2);

            fscanf (fNot, "%d %d %d", &ders_kodu2, &ogr_no2, &ogr_not2);
        }
        fclose(gecici);
        fclose(fNot);
        remove("notlar.txt");
        rename("gecici.txt","notlar.txt");

        if ((fNot=fopen("notlar.txt","a+"))==NULL)
            printf("Notlar dosyasi acilamadi.");

        printf("Girdiginiz numaraya sahip ogrenci silinmistir.\n");
    }
    rewind(fNot);
    rewind(fOgr);
    return;
}
////////////////////////////////////////////////////////////////////////////
void not_girilmesi (FILE *fDers, FILE *fNot, FILE *fOgr)
{
    Ders_type bir_ders;
    Ogr_type bir_ogr;
    int ders_kodu,ogr_no,ogr_not,kayit_no,kredi_carpim;
    char devam;

    printf("Ders Kodunu giriniz(10-89): ");
    ders_kodu=sayi_al(10,89);

    fseek(fDers,(ders_kodu-1)*sizeof(Ders_type), SEEK_SET);
    fread(&bir_ders,sizeof(Ders_type),1,fDers);

    if(bir_ders.ders_kodu==BOS_KAYIT)
        printf("Girdiginiz ders koduna sahip ders bulunmamaktadir.\n");
    else
    {
        do
        {
            printf("Notunu girmek istediginiz ogrencinin numarasini giriniz(100-999): ");
            ogr_no=sayi_al(100,999);

            kayit_no=ogr_no-99;
            fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
            fread(&bir_ogr,sizeof(Ogr_type),1,fOgr);

            if (bir_ogr.ogr_no==BOS_KAYIT)
                printf("Girdiginiz ogrenci numarasina sahip ogrenci bulunmamaktadir.");

            else
            {
                printf("Ogrencinin bu dersten aldigi notu giriniz:");
                ogr_not=sayi_al(0,100);

                kredi_carpim=bir_ogr.kredi_say*bir_ogr.not_ort; //ogrencinin kredi sayisi ile not ortalamasinin carpimi hesaplanir.

                bir_ogr.kredi_say=bir_ogr.kredi_say+bir_ders.ders_krd; //Ogrencinin dersinin kredisi,kredi sayisina eklenir.
                bir_ogr.not_ort=(float)(kredi_carpim+ogr_not*bir_ders.ders_krd)/bir_ogr.kredi_say; //Ogrencinin yeni not ortalamsi hesaplanir.

                fprintf (fNot,"%d %d %d\n",ders_kodu,bir_ogr.ogr_no,ogr_not);

                fseek(fOgr,(kayit_no-1)*sizeof(Ogr_type),SEEK_SET);
                fwrite(&bir_ogr,sizeof(Ogr_type),1,fOgr);
            }
            printf("Guncelleme basarili.\n");
            printf("\nBaska ogrenci var mi?: "); //Baska ogrenci olup olmadigi kontrol edilir.
            scanf("%c",&devam);
            devam=getchar();
        }
        while(devam=='e' && devam=='E');
    }
    rewind(fDers);
    rewind(fNot);
    rewind(fOgr);
    return;
}
////////////////////////////////////////////////////////////////////////////
void istatistik (FILE *fOgr)
{
    Ogr_type bir_ogr;
    int toplam_ogr=0;
    int frekans[10]= {0},i,rakam; //her not araligindaki ogrencileri sayilarini tutan bir frekans dizisi tanimlanmistir.

    for (i=0; i<900; i++)
    {
        fread(&bir_ogr,sizeof(Ogr_type),1,fOgr); //Dongu icinde her ogrencinin bilgileri okutulur.

        if (bir_ogr.ogr_no!=BOS_KAYIT) //Okunan kayit bos degilse(bir ogrenci gorulduyse) toplam ogrenci sayisi artirilir.
        {
            toplam_ogr++;
            rakam=bir_ogr.not_ort/10; //Ogrencinin not ortalamasinin frekans dizisinin hangi not araligina dahil edilecegi belirlenir.

            if(rakam==10)
                rakam=9;

            frekans[rakam]++; //Belirlenen indekste artis yapilir.
        }
    }
    printf("Not araligi Ogrenci Sayisi    Ogrenci Yuzdesi\n");
    printf("----------- --------------    ---------------\n");
    printf("  90-100          %-7d          %.2f\n", frekans[9], (float)frekans[9]*100/toplam_ogr);

    for (i=8; i>=0; i--)
        printf("%5d-%-11d %-16d %.2f\n", i*10,(i+1)*10-1, frekans[i], (float)frekans[i]*100/toplam_ogr);

    rewind(fOgr);
    return;
}
//////////////////////////////////////////////////////////////////////////////
int sayi_al(int alt_sinir, int ust_sinir) //parametre alan ve deger donduren fonksiyon
{
    int sayi;
    scanf("%d",&sayi);

    while (sayi<alt_sinir || sayi>ust_sinir) //sayi dogru girilinceye kadar bekleniyor..
    {
        printf("Hatali veri girisi, veriyi %d ile %d arasinda tekrar giriniz:",alt_sinir,ust_sinir);
        scanf("%d",&sayi);
    }
    return sayi;
}
