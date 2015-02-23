#include <stdio.h>
#include <stdlib.h>

#define MIN_OGRENCI_NO 1
#define MAX_OGRENCI_NO 10000

struct ogrenci //ogrenciye ait bilgileri ve ogrencileri baglayan dugum adresini iceren ogrenci yapisi..
{
    int ogr_no;
    char ad_soyad[30];
    int sinif;
    int kredi_say;
    float not_ort;
    struct ogrenci *sonraki;
};

struct notlar //dersi alan ogrencinin numarasi,notutunun ve dairesel baglarin dugum adreslerini iceren notlar yapisi..
{
    int ogr_no;
    int ogr_notu;
    struct notlar *noya_gore_sonraki;
    struct notlar *nota_gore_onceki;
    struct notlar *nota_gore_sonraki;
};

struct ders //derse ait bilgileri ve notlar yapisinin liste basi dugumunu iceren ders yapisi..
{
    int ders_kodu;
    char ders_adi[25];
    int ders_kredi;
    int dersi_alanlar;
    float genel_not_ort;
    struct notlar liste_basi;
};

int menu_goruntule(void);
int sayi_al(int, int);
struct ogrenci *ogrenci_ara(struct ogrenci *ilk_ptr, int aranan_ogrenci_no);
void ogrenci_ekle (struct ogrenci **ilk_ptr, struct ogrenci *yeni);
void ogr_nosuna_gore_not_ekle(struct notlar *liste_basi, struct notlar *yeni);
void notuna_gore_not_ekle(struct notlar *liste_basi, struct notlar *yeni);
struct notlar *notlar_listesinde_ara (struct notlar *liste_basi, int aranan_no);
void notuna_gore_notlar_listesinden_cikar (struct notlar *cikarilacak);
void ogrenci_listesinden_sil (struct ogrenci **ilk_ptr, struct ogrenci *silinecek);
void nosuna_gore_nolar_listesinden_cikar (struct notlar *liste_basi, int cikarilacak_no);
void notu_ustunde_olanlari_listele (struct ders *bir_ders, struct ogrenci **ogrenciler);
void notu_altinda_olanlari_listele (struct ders *bir_ders, struct ogrenci **ogrenciler);
void ders_ekle (struct ders **dersler, int donem);
void not_ekle (struct ogrenci **ilk_ptr, struct ders *bir_ders, int ogr_no);
void not_guncelleme (struct ogrenci **ilk_ptr, struct ders *bir_ders, int ogr_no);
void ogrenciye_ait_tum_bilgileri_sil (struct ogrenci **ilk_ptr, struct ders **dersler, int ogr_no);
void dersi_ve_ogrencileri_listele (struct ders *bir_ders, struct ogrenci **ogrenciler);
void bir_donemin_derslerini_listele (struct ders **dersler, int donem);
void bir_ogrenci_listele (struct ogrenci **ilk_ptr, int ogr_no);
void bir_ogrencinin_derslerini_listele (struct ders **dersler, int ogr_no);
void sinifi_listele(struct ogrenci **ogrenciler, int sinif);

int main()
{
    struct ogrenci *ogrenci_tablosu[101]= {NULL}; //ogrencileri iceren hash tablosu, ogrenciler sirali tek bagli sekildedir..
    struct ders *ders_tablosu[80]= {NULL}; //dersleri iceren isaretci dizisi..
    struct ogrenci *bir_ogrenci; //bir ogrenciye ait bilgileri iceren ogrenci yapisinda degisken..
    int secenek,hash,ogr_no,donem_no,ders_kodu,sinif_no;
    char devam;

    do
    {
        secenek=menu_goruntule();

        switch (secenek)
        {
        case 1:
            printf("Eklenecek ogrencinin numarasini giriniz:");
            ogr_no=sayi_al(MIN_OGRENCI_NO,MAX_OGRENCI_NO);
            hash=(ogr_no-1)/100+1; //hash tablosunun indisi olusturuluyor..

            if (ogrenci_ara(ogrenci_tablosu[hash],ogr_no)!=NULL) //girilen numarada ogrencinin olup olmadigi kontrol ediliyor..
                printf("Bu numarali bir ogrenci zaten vardir..!\n");
            else
            {
                //ogrenci yoksa yeni ogrenciye ait bilgiler aliniyor..
                bir_ogrenci=malloc(sizeof(struct ogrenci));
                bir_ogrenci->ogr_no=ogr_no;
                printf("Ogrencinin adini giriniz:");
                fflush(stdin);
                gets(bir_ogrenci->ad_soyad);
                printf("Ogrencinin sinifini giriniz:");
                bir_ogrenci->sinif=sayi_al(1,4);
                bir_ogrenci->not_ort=0;
                bir_ogrenci->kredi_say=0; //yeni ogrencinin kredi sayisi sifirlaniyor..
                //yeni ogrencinin bilgileri fonksiyona gonderilerek hash tablosunda ilgili indise ve dugume ekleniyor..
                ogrenci_ekle(&ogrenci_tablosu[hash],bir_ogrenci);
                printf("%d numarali ogrenci eklenmistir..\n",ogr_no);
            }
            break;

        case 2:
            printf("Eklenecek dersin donemini giriniz:");
            donem_no=sayi_al(1,8);

            if(ders_tablosu[donem_no*10-1]==NULL) //Eger o donemdeki max. ders sayisina ulasilmamissa yeni ders ekleme yapiliyor..
                ders_ekle (ders_tablosu,donem_no);
            else printf("\nDonemdeki maximum ders sayisina ulasildi.. Bu doneme ders ekleyemezsiniz..!\n");
            break;

        case 3:
            printf("Ders kodunu giriniz:");
            ders_kodu=sayi_al(10,89);

            if (ders_tablosu[ders_kodu-10]==NULL) //Dersin olup olmadigi kontrol ediliyor..
                printf("Ders bulunamadi..!\n");
            else
            {
                do
                {
                    printf("Notu eklenecek ogrencinin numarasini giriniz:");
                    ogr_no=sayi_al(MIN_OGRENCI_NO,MAX_OGRENCI_NO);
                    hash=(ogr_no-1)/100+1;

                    if (ogrenci_ara(ogrenci_tablosu[hash],ogr_no)==NULL)
                        printf("Ogrenci bulunamadi..!\n");
                    else //Girilen ogrenci varsa..
                    {
                        //ve o ogrenci daha once bu dersi almiyorsa eklemeye yapiliyor..
                        if(notlar_listesinde_ara(&(ders_tablosu[ders_kodu-10]->liste_basi),ogr_no)==NULL)
                            not_ekle(&ogrenci_tablosu[hash],ders_tablosu[ders_kodu-10],ogr_no);
                        else printf("Bu ogrenci bu dersi zaten almaktadir..!\n");
                    }

                    printf("\nBaska ogrenci var mi?: "); //Baska ogrenci olup olmadigi kontrol ediliyor..
                    scanf("%c",&devam);
                    devam=getchar();
                }
                while(devam=='e' || devam=='E');
            }
            break;

        case 4:
            printf("Ders kodunu giriniz:");
            ders_kodu=sayi_al(10,89);

            if(ders_tablosu[ders_kodu-10]==NULL)
                printf("Ders bulunamadi..!\n");
            else
            {
                printf("Notu guncellenecek ogrencinin numarasini giriniz:");
                ogr_no=sayi_al(MIN_OGRENCI_NO,MAX_OGRENCI_NO);

                hash=(ogr_no-1)/100+1;

                if (ogrenci_ara(ogrenci_tablosu[hash],ogr_no)==NULL)
                    printf("Ogrenci bulunamadi..!\n");
                else
                {
                    if(notlar_listesinde_ara(&(ders_tablosu[ders_kodu-10]->liste_basi),ogr_no)==NULL)
                        //girilen derse gore o dersi alan ogrencilerin dugumunde numarasi girilen ogrencinin olup olmadigi kontrol ediliyor..
                        printf("Bu ogrenci bu dersi almamaktadir..!\n");
                    else not_guncelleme(&ogrenci_tablosu[hash],ders_tablosu[ders_kodu-10],ogr_no); //varsa guncelleme yapiliyor..
                }
            }
            break;

        case 5:
            printf("Silinecek ogrencinin numarasini giriniz:");
            ogr_no=sayi_al(MIN_OGRENCI_NO,MAX_OGRENCI_NO);
            hash=(ogr_no-1)/100+1;
            //ogrencinin olup olmadigi kontrol edilir..
            if (ogrenci_ara(ogrenci_tablosu[hash],ogr_no)==NULL)
                printf("Ogrenci zaten yok..!\n");
            else //oyle bir ogrenci varsa silme yapilir..
                {
                ogrenciye_ait_tum_bilgileri_sil(&ogrenci_tablosu[hash],ders_tablosu,ogr_no);
                printf("%d numarali ogrenci silinmistir..\n",ogr_no);
                }

            break;

        case 6:
            printf("Ders kodunu giriniz:");
            ders_kodu=sayi_al(10,89);

            if(ders_tablosu[ders_kodu-10]==NULL)
                printf("Ders bulunamadi..!\n");
            else dersi_ve_ogrencileri_listele(ders_tablosu[ders_kodu-10],ogrenci_tablosu);
            break;

        case 7:
            printf("Ders kodunu giriniz:");
            ders_kodu=sayi_al(10,89);

            if(ders_tablosu[ders_kodu-10]==NULL)
                printf("Ders bulunamadi..!\n"); //girilen ders varsa bilgileri listelenir..
            else notu_ustunde_olanlari_listele(ders_tablosu[ders_kodu-10],ogrenci_tablosu);

            break;
        case 8:
            printf("Ders kodunu giriniz:");
            ders_kodu=sayi_al(10,89);

            if(ders_tablosu[ders_kodu-10]==NULL)
                printf("Ders bulunamadi..!\n"); //girilen ders varsa bilgileri listelenir..
            else notu_altinda_olanlari_listele (ders_tablosu[ders_kodu-10],ogrenci_tablosu);

            break;

        case 9:
            printf("Donemi giriniz:");
            donem_no=sayi_al(1,8);
            //alinan donem numarasina gore donemin dersleri listelenir..
            bir_donemin_derslerini_listele(ders_tablosu,donem_no);
            break;
        case 10:
            printf("Ogrenci numarasini giriniz:");
            ogr_no=sayi_al(MIN_OGRENCI_NO,MAX_OGRENCI_NO);
            hash=(ogr_no-1)/100+1;

            if(ogrenci_ara(ogrenci_tablosu[hash],ogr_no)!=NULL)
                bir_ogrenci_listele(&ogrenci_tablosu[hash],ogr_no); //girilen numarada ogrenci varsa bilgileri listelenir..
            else printf("Boyle bir ogrenci yoktur..!");
            break;
        case 11:
            printf("Ogrenci numarasini giriniz:");
            ogr_no=sayi_al(MIN_OGRENCI_NO,MAX_OGRENCI_NO);
            hash=(ogr_no-1)/100+1;

            if(ogrenci_ara(ogrenci_tablosu[hash],ogr_no)!=NULL)
            {
                bir_ogrenci=ogrenci_ara(ogrenci_tablosu[hash],ogr_no);
                bir_ogrenci_listele(&ogrenci_tablosu[hash],ogr_no); //girilen numarada ogrenci varsa bilgileri listelenir..
                if(bir_ogrenci->kredi_say!=0)
                    bir_ogrencinin_derslerini_listele(ders_tablosu,ogr_no); //ogrenci ders aliyorsa ders bilgileri de listelenir..
                else printf("Ogrencinin aldigi ders yoktur..!");
            }
            else printf("Boyle bir ogrenci yoktur..!");
            break;
        case 12:
            printf("Sinif numarasini giriniz:");
            sinif_no=sayi_al(1,4);
            //sinif numarasina gore o sinifin ogrencileri listelenir..
            sinifi_listele(ogrenci_tablosu,sinif_no);
            break;
        }
    }
    while(secenek!=13);

    return 0;
}

int menu_goruntule(void)
{
    int secim;

    printf("\n\t*****************ANA MENU************************\n\n");
    printf("1. Yeni Ogrenci Ekle\n");
    printf("2. Yeni Ders Ekle\n");
    printf("3. Bir Dersi Alan Ogrenciye Not Ekle\n");
    printf("4. Bir Dersi Alan Ogrencinin Notunu Guncelle\n");
    printf("5. Bir Ogrenci Sil\n");
    printf("6. Bir Dersin Bilgilerini ve O Dersi Alan Ogrencileri Listele\n");
    printf("7. Bir Dersi Alan Ogrencilerden Notu Belirli Bir Notun Uzerinde Olan Ogrenciler\n");
    printf("8. Bir Dersi Alan Ogrencilerden Notu Belirli Bir Notun Altinda Olan Ogrenciler\n");
    printf("9. Bir Donemin Derslerini Listele\n");
    printf("10. Bir Ogrencinin Bilgilerini Listele\n");
    printf("11. Bir Ogrencinin Bilgilerini ve Aldigi Dersleri Listele\n");
    printf("12. Bir Sinifta Okuyan Ogrencileri Listele\n");
    printf("13. Cikis\n");

    do
    {
        printf("\nSeciminizi Giriniz:");
        scanf("%d", &secim);
    }
    while(secim<1 || secim>13);

    return secim;
}

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

struct ogrenci *ogrenci_ara(struct ogrenci *ilk_ptr, int aranan_ogrenci_no)
{
    while(ilk_ptr!=NULL && aranan_ogrenci_no>ilk_ptr->ogr_no) //listede ogrenci bulunana kadar arama yapiliyor..
    {
        ilk_ptr=ilk_ptr->sonraki;
    }
    if((ilk_ptr==NULL) || (aranan_ogrenci_no<ilk_ptr->ogr_no))
        return NULL; //ogrenci listede bulunamazsa NULL dondurulur
    else return ilk_ptr; //bulunursa isaretcisi dondurulur
}

void ogrenci_ekle (struct ogrenci **ilk_ptr, struct ogrenci *yeni)
{
    struct ogrenci *onceki, *gecici;

    if (*ilk_ptr==NULL) //eger liste bossa..
    {
        yeni->sonraki=NULL; //eklenen ogrencinin sonraki dugumu null'a ataniyor..
        *ilk_ptr=yeni; //eklenen ogrencinin adresi ilke ataniyor..
    }

    else if ((*ilk_ptr)->ogr_no>yeni->ogr_no) //eger en basa ekleniyorsa..
    {
        yeni->sonraki=*ilk_ptr; //ilkin gosterdigi yeninin sonrakisine ataniyor..
        *ilk_ptr=yeni; //eklenen ogrencinin adresi ilke ataniyor..
    }
    else //arada bir yere ekleniyorsa..
    {
        onceki=*ilk_ptr;
        gecici=(*ilk_ptr)->sonraki;

        while(gecici!=NULL && gecici->ogr_no<yeni->ogr_no) //uygun yer bulunana kadar arama yapiliyor..
        {
            onceki=gecici;
            gecici=gecici->sonraki;
        }
        yeni->sonraki=gecici; //yeni ogrenci dugume baglaniyor onceki ve sonrakilere adresleri atanarak..
        onceki->sonraki=yeni;
    }
}

void ogr_nosuna_gore_not_ekle(struct notlar *liste_basi, struct notlar *yeni)
{
    struct notlar *onceki=liste_basi;
    struct notlar *gecici=liste_basi->noya_gore_sonraki;

    while (gecici!=liste_basi && gecici->ogr_no<yeni->ogr_no) //notlar listesinde numaraya gore uygun yer araniyor..
    {
        onceki=gecici;
        gecici=gecici->noya_gore_sonraki;
    }
    yeni->noya_gore_sonraki=gecici; //tek bagli dairesel listede uygun yere baglaniyor..
    onceki->noya_gore_sonraki=yeni;
}

void notuna_gore_not_ekle(struct notlar *liste_basi, struct notlar *yeni)
{
    struct notlar *gecici=liste_basi->nota_gore_sonraki;

    while(gecici!=liste_basi && gecici->ogr_notu<yeni->ogr_notu) //notlar listesinde nota gore uygun yer araniyor..
    {
        gecici=gecici->nota_gore_sonraki;
    }

    yeni->nota_gore_onceki=gecici->nota_gore_onceki; //cift bagli dairesel listede uygun dugume ekleme yapiliyor..
    yeni->nota_gore_sonraki=gecici;
    gecici->nota_gore_onceki->nota_gore_sonraki=yeni;
    gecici->nota_gore_onceki=yeni;
}

struct notlar *notlar_listesinde_ara (struct notlar *liste_basi, int aranan_no)
{
    struct notlar *gecici;

    gecici=liste_basi->nota_gore_sonraki;

    while (gecici!=liste_basi) //notlar listesinde liste basine gore ogrenci araniyor..
    {
        if(gecici->ogr_no==aranan_no) return gecici; //ogrenci listede bulunursa isaretcisi bulunamazsa NULL dondurulur..
        gecici=gecici->nota_gore_sonraki;
    }
    return NULL;
}

void notuna_gore_notlar_listesinden_cikar (struct notlar *cikarilacak) //adresi verilen dugumu listeden cikarir ama yok etmez..
{
    cikarilacak->nota_gore_onceki->nota_gore_sonraki=cikarilacak->nota_gore_sonraki;
    cikarilacak->nota_gore_sonraki->nota_gore_onceki=cikarilacak->nota_gore_onceki;
}

void ogrenci_listesinden_sil (struct ogrenci **ilk_ptr, struct ogrenci *silinecek)
{
    struct ogrenci *onceki,*gecici;
    if((*ilk_ptr)->ogr_no==silinecek->ogr_no) //silinen ogrenci listedeki ilk ogrenci ise..
        *ilk_ptr=(*ilk_ptr)->sonraki;

    else //listenin arasinda bir yerde silinme oluyorsa..
    {
        onceki=*ilk_ptr;
        gecici=(*ilk_ptr)->sonraki;

        while(gecici!=NULL && gecici->ogr_no < silinecek->ogr_no) //silinecek ogrenci araniyor..
        {
            onceki=gecici;
            gecici=gecici->sonraki;
        }
        if (gecici!=NULL && gecici->ogr_no==silinecek->ogr_no)
            onceki->sonraki=gecici->sonraki;
    }
    free(silinecek); //ogrencinin bilgileri yok ediliyor..
}

void nosuna_gore_nolar_listesinden_cikar (struct notlar *liste_basi, int cikarilacak_no)
{
    struct notlar *onceki=liste_basi;
    struct notlar *gecici=liste_basi->noya_gore_sonraki;

    while (gecici!=liste_basi && gecici->ogr_no < cikarilacak_no) //cikarilacak ogrenci araniyor..
    {
        onceki=gecici;
        gecici=gecici->noya_gore_sonraki;
    }

    if(gecici!=liste_basi && gecici->ogr_no == cikarilacak_no) //eger bulunursa listedeki dugum kopariliyor..
        onceki->noya_gore_sonraki=gecici->noya_gore_sonraki;
}

void notu_ustunde_olanlari_listele (struct ders *bir_ders, struct ogrenci **ogrenciler)
{
    int not_baraji,baraj_say=0,hash;
    struct ogrenci *bir_ogrenci;
    struct notlar *liste_basi;
    struct notlar *gecici;

    printf("Not barajini giriniz:");
    scanf("%d", &not_baraji);

    if(bir_ders->liste_basi.nota_gore_sonraki!=&(bir_ders->liste_basi)) //eger o dersi alan ogrenci varsa bilgiler listeleniyor..
    {
        printf("\nNotu Yuksek Olan Ogrenciler:\n");
        printf("Ogr No Ad Soyad                       Sinif Notu\n");
        printf("------ ------------------------------ ----- ----\n");

        liste_basi=&(bir_ders->liste_basi);
        gecici=liste_basi->nota_gore_onceki;

        while(gecici!=liste_basi) //notlar listesi nota gore bastan sona araniyor..
        {
            hash=(gecici->ogr_no-1)/100+1; //notlar listesinden gelen ogrenci numarasi indise cevriliyor..
            bir_ogrenci=ogrenci_ara(ogrenciler[hash],gecici->ogr_no); //ogrencinin bilgileri aliniyor..

            if(gecici->ogr_notu>not_baraji) //notu yuksekse listeleniyor..
            {
                baraj_say++; //baraji gecen ogrenci sayisi artiriliyor..
                printf("%-6d %-30s %-5d %d\n",gecici->ogr_no,bir_ogrenci->ad_soyad,bir_ogrenci->sinif,gecici->ogr_notu);
            }
            gecici=gecici->nota_gore_onceki;
        }
        printf("\nNotu %d'nin ustunde olan ogrenci sayisi ve yuzdesi: %d - %.2f\n",not_baraji,baraj_say,
               (float)(baraj_say*100)/bir_ders->dersi_alanlar);
    }
    else printf("Dersi alan ogrenci yoktur..\n");
}

void ders_ekle (struct ders **dersler, int donem)
{
    int ders_kodu,i;
    struct ders *bir_ders;

    for(i=0; i<10; i++)
    {
        ders_kodu=donem*10+i;
        if (dersler[ders_kodu-10]==NULL) //dersin donemine gore donemdeki ilk bos ders yerine yeni ders ekleniyor..
        {
            bir_ders=malloc(sizeof(struct ders)); //bellekte yer ayriliyor..
            bir_ders->ders_kodu=ders_kodu;
            break;
        }
    }
    printf("Ders kodunuz: %d\n",bir_ders->ders_kodu);
    //dersin bilgileri aliniyor..
    printf("Dersin adini giriniz:");
    fflush(stdin);
    gets(bir_ders->ders_adi);

    printf("Dersin kredisini giriniz:");
    scanf("%d",&bir_ders->ders_kredi);

    bir_ders->dersi_alanlar=0;
    bir_ders->genel_not_ort=0;

    bir_ders->liste_basi.noya_gore_sonraki=&(bir_ders->liste_basi);
    bir_ders->liste_basi.nota_gore_sonraki=&(bir_ders->liste_basi);
    bir_ders->liste_basi.nota_gore_onceki=&(bir_ders->liste_basi);

    dersler[ders_kodu-10]=bir_ders; //yeni ders isaretci dizisine ataniyor..

    printf("%d kodlu ders eklenmistir..\n",bir_ders->ders_kodu);
}

void not_ekle (struct ogrenci **ilk_ptr, struct ders *bir_ders, int ogr_no)
{
    struct notlar *bir_not;
    struct ogrenci *bir_ogrenci;
    float kredi_carpim,not_ort_carpim;

    bir_not=malloc(sizeof(struct notlar)); //bellekte yer ayriliyor..
    bir_not->ogr_no=ogr_no;
    printf("Ogrencinin aldigi notu giriniz:");
    bir_not->ogr_notu=sayi_al(0,100);

    bir_ogrenci=ogrenci_ara(*ilk_ptr,ogr_no);
    kredi_carpim=bir_ogrenci->kredi_say*bir_ogrenci->not_ort;
    bir_ogrenci->kredi_say=bir_ogrenci->kredi_say+bir_ders->ders_kredi;
    bir_ogrenci->not_ort=(float)(kredi_carpim+bir_not->ogr_notu*bir_ders->ders_kredi)/bir_ogrenci->kredi_say;
    //not,kredi hesaplamalari yapiliyor..
    not_ort_carpim=bir_ders->genel_not_ort*bir_ders->dersi_alanlar;
    bir_ders->dersi_alanlar++;
    bir_ders->genel_not_ort=(float)(not_ort_carpim+bir_not->ogr_notu)/bir_ders->dersi_alanlar;

    ogr_nosuna_gore_not_ekle(&(bir_ders->liste_basi),bir_not); //notlar listesine eklemeler yapiliyor..
    notuna_gore_not_ekle(&(bir_ders->liste_basi),bir_not);

    printf("%d numarali ogrencinin %d kodlu dersi icin notu %d olarak eklenmistir..\n",ogr_no,bir_ders->ders_kodu,bir_not->ogr_notu);
}

void notu_altinda_olanlari_listele (struct ders *bir_ders, struct ogrenci **ogrenciler)
{
    int not_baraji,baraj_say=0,hash;
    struct ogrenci *bir_ogrenci;
    struct notlar *liste_basi;
    struct notlar *gecici;

    printf("Not barajini giriniz:");
    scanf("%d", &not_baraji);

    if(bir_ders->liste_basi.nota_gore_sonraki!=&(bir_ders->liste_basi)) //eger o dersi alan ogrenci varsa bilgiler listeleniyor..
    {
        baraj_say=0;

        printf("\nNotu Dusuk Olan Ogrenciler:\n");
        printf("Ogr No Ad Soyad                       Sinif Notu\n");
        printf("------ ------------------------------ ----- ----\n");

        liste_basi=&(bir_ders->liste_basi);
        gecici=liste_basi->nota_gore_sonraki;

        while(gecici!=liste_basi) //notlar listesi nota gore bastan sona araniyor..
        {
            hash=(gecici->ogr_no-1)/100+1; //notlar listesinden gelen ogrenci numarasi indise cevriliyor..
            bir_ogrenci=ogrenci_ara(ogrenciler[hash],gecici->ogr_no); //ogrencinin bilgileri aliniyor..

            if(gecici->ogr_notu<not_baraji) //notu dusukse listeleniyor..
            {
                baraj_say++; //baraji gecemeyen ogrenci sayisi artiriliyor..
                printf("%-6d %-30s %-5d %d\n",gecici->ogr_no,bir_ogrenci->ad_soyad,bir_ogrenci->sinif,gecici->ogr_notu);
            }
            gecici=gecici->nota_gore_sonraki;
        }
        printf("\nNotu %d'nin altinda olan ogrenci sayisi ve yuzdesi: %d - %.2f\n",not_baraji,baraj_say,
               (float)(baraj_say*100)/bir_ders->dersi_alanlar);
    }
}

void not_guncelleme (struct ogrenci **ilk_ptr, struct ders *bir_ders, int ogr_no)
{
    struct notlar *bir_not;
    struct ogrenci *bir_ogrenci;
    float not_ort_carpim, kredi_carpim;
    //girilen ders kodu ve ogrenci numarasina gore bilgiler listelerden aliniyor..
    bir_ogrenci=ogrenci_ara(*ilk_ptr,ogr_no);
    bir_not=notlar_listesinde_ara(&(bir_ders->liste_basi),ogr_no);

    not_ort_carpim=bir_ders->genel_not_ort*bir_ders->dersi_alanlar;
    not_ort_carpim=not_ort_carpim-bir_not->ogr_notu;
    //kredi ve not hesaplamalari yapiliyor..
    kredi_carpim=bir_ogrenci->kredi_say*bir_ogrenci->not_ort-bir_ders->ders_kredi*bir_not->ogr_notu;

    printf("Yeni notu giriniz:");
    bir_not->ogr_notu=sayi_al(0,100);

    bir_ders->genel_not_ort=(float)(not_ort_carpim+bir_not->ogr_notu)/bir_ders->dersi_alanlar;
    bir_ogrenci->not_ort=(float)(kredi_carpim+bir_not->ogr_notu*bir_ders->ders_kredi)/bir_ogrenci->kredi_say;

    //girilen yeni nota gore notlar listesinde nota gore yer degisecekse cikarma ve ekleme islemleri yapiliyor..
    if((bir_not->nota_gore_onceki!=&(bir_ders->liste_basi) && bir_not->ogr_notu < bir_not->nota_gore_onceki->ogr_notu) ||
            (bir_not->nota_gore_sonraki!=&(bir_ders->liste_basi) && bir_not->ogr_notu > bir_not->nota_gore_sonraki->ogr_notu))
    {
        notuna_gore_notlar_listesinden_cikar(bir_not);
        notuna_gore_not_ekle(&(bir_ders->liste_basi),bir_not);
    }
    printf("%d numarali ogrencinin %d kodlu dersi icin notu %d olarak guncellenmistir..\n",ogr_no,bir_ders->ders_kodu,bir_not->ogr_notu);
}

void ogrenciye_ait_tum_bilgileri_sil (struct ogrenci **ilk_ptr, struct ders **dersler, int ogr_no)
{
    struct ogrenci *bir_ogrenci;
    struct notlar *bir_not;
    float not_ort_carpim;
    int i;

    bir_ogrenci=ogrenci_ara(*ilk_ptr,ogr_no);
    if(bir_ogrenci->kredi_say!=0) //eger ogrenci ders aliyorsa..
    {
        for (i=0; i<80; i++)
        {
            if (dersler[i]!=NULL) //oyle bir ders varsa..
            {
                if (notlar_listesinde_ara(&(dersler[i]->liste_basi),ogr_no)!=NULL) //ogrenci o dersi aliyorsa..
                {

                    bir_not=notlar_listesinde_ara(&(dersler[i]->liste_basi),ogr_no); //ogrencinin o dersten aldigi nota ulasiliyor..
                    notuna_gore_notlar_listesinden_cikar(bir_not); //notlar listesinden noya ve nota gore cikarma yapiliyor..
                    nosuna_gore_nolar_listesinden_cikar(&(dersler[i]->liste_basi),ogr_no);
                    if(dersler[i]->dersi_alanlar!=1) //silinen ogrenci eger o dersi alan tek ogrenci degilse..
                    {
                        not_ort_carpim=dersler[i]->genel_not_ort*dersler[i]->dersi_alanlar;
                        not_ort_carpim=not_ort_carpim-bir_not->ogr_notu;
                        dersler[i]->dersi_alanlar--;
                        dersler[i]->genel_not_ort=(float)not_ort_carpim/dersler[i]->dersi_alanlar;
                    }
                    else //dersi sadece silinen ogrenci aliyorsa..
                    {
                        dersler[i]->genel_not_ort=0;
                        dersler[i]->dersi_alanlar--;
                    }
                    free(bir_not); //bellekten notlar yapisindaki alan siliniyor..
                }
            }
        }
    }
    ogrenci_listesinden_sil(ilk_ptr,bir_ogrenci); //ogrenci listesinden ogrenci siliniyor..
}

void dersi_ve_ogrencileri_listele (struct ders *bir_ders, struct ogrenci **ogrenciler)
{
    struct notlar *liste_basi,*gecici;
    struct ogrenci *bir_ogrenci;
    int hash;

    printf("\n");
    printf("Ders Kodu Ders Adi                  Kredi Ogrenci Say Not Ort\n");
    printf("--------- ------------------------- ----- ----------- -------\n");
    printf("%-9d %-25s %-5d %-11d %.2f\n", bir_ders->ders_kodu,bir_ders->ders_adi,bir_ders->ders_kredi, bir_ders->dersi_alanlar,
           bir_ders->genel_not_ort);

    if(bir_ders->liste_basi.noya_gore_sonraki!=&(bir_ders->liste_basi)) //eger dersi alan ogrenci varsa bilgiler listeleniyor..
    {
        printf("\nDersi Alan Ogrenciler:\n");
        printf("Ogr No Ad Soyad                       Sinif Notu\n");
        printf("------ ------------------------------ ----- ----\n");

        liste_basi=&(bir_ders->liste_basi);
        gecici=liste_basi->noya_gore_sonraki;

        while(gecici!=liste_basi) //notlar listesinde ogrencilerin ders notuna ulasmak ve bilgilerini listelemek icin listenin sonuna kadar arama yapiliyor..
        {
            hash=(gecici->ogr_no-1)/100+1;
            bir_ogrenci=ogrenci_ara(ogrenciler[hash],gecici->ogr_no);
            printf("%-6d %-30s %-5d %d\n",gecici->ogr_no,bir_ogrenci->ad_soyad,bir_ogrenci->sinif,gecici->ogr_notu);
            gecici=gecici->noya_gore_sonraki;
        }
    }
    else printf("Dersi alan ogrenci yoktur..\n");
}

void bir_donemin_derslerini_listele (struct ders **dersler, int donem)
{
    int kredi_top=0,i,ders_kodu;

    printf("\nDers Kodu Ders Adi                  Kredi Ogrenci Say Not Ort\n");
    printf("--------- ------------------------- ----- ----------- -------\n");

    for (i=0; i<10; i++)
    {
        ders_kodu=donem*10+i; //girilen donem numarasina gore ders koduna donusum yapiliyor..
        if (dersler[ders_kodu-10]!=NULL) //eger oyle bir ders varsa bilgileri listeleniyor..
        {
            printf("%-9d %-25s %-5d %-11d %.2f\n",dersler[ders_kodu-10]->ders_kodu,dersler[ders_kodu-10]->ders_adi,
                   dersler[ders_kodu-10]->ders_kredi,dersler[ders_kodu-10]->dersi_alanlar,dersler[ders_kodu-10]->genel_not_ort);
            kredi_top=kredi_top+dersler[ders_kodu-10]->ders_kredi;
        }
    }
    printf("\nDerslerin kredi toplami: %d\n",kredi_top);
}

void bir_ogrenci_listele (struct ogrenci **ilk_ptr, int ogr_no)
{
    struct ogrenci *bir_ogrenci;

    bir_ogrenci=ogrenci_ara(*ilk_ptr,ogr_no); //ogrencinin bilgileri alinip yazdirma yapiliyor..

    printf("\nOgr No Ad Soyad                       Sinif Kredi Say Not Ort\n");
    printf("------ ------------------------------ ----- --------- -------\n");
    printf("%-6d %-30s %-5d %-9d %.2f\n",bir_ogrenci->ogr_no,bir_ogrenci->ad_soyad,
           bir_ogrenci->sinif,bir_ogrenci->kredi_say,bir_ogrenci->not_ort);
}

void bir_ogrencinin_derslerini_listele (struct ders **dersler, int ogr_no)
{
    struct notlar *bir_not;
    int i;

    printf("\nAldigi dersler:\n");
    printf("Ders Kodu Ders Adi                  Kredi Notu\n");
    printf("--------- ------------------------- ----- ----\n");

    for (i=0; i<80; i++)
    {
        if (dersler[i]!=NULL) //eger oyle bir ders varsa..
        {
            if(notlar_listesinde_ara(&(dersler[i]->liste_basi),ogr_no)!=NULL) //ve ogrenci o dersi aliyorsa yazdirma yapiliyor..
            {
                bir_not=notlar_listesinde_ara(&(dersler[i]->liste_basi),ogr_no);
                printf("%-9d %-25s %-5d %d\n",dersler[i]->ders_kodu,dersler[i]->ders_adi,
                       dersler[i]->ders_kredi,bir_not->ogr_notu);
            }
        }
    }
}

void sinifi_listele(struct ogrenci **ogrenciler, int sinif)
{
    int sinif_ogr_say=0, altmis_alti_ogr=0,i;
    float not_ort_top=0;
    struct ogrenci *gecici;

    printf("\nOgr No Ad Soyad                       Sinif Kredi Say Not Ort\n");
    printf("------ ------------------------------ ----- --------- -------\n");

    for (i=1; i<101; i++) //ogrenciler hash tablosunun tamamina bakiliyor..
    {
        gecici=ogrenciler[i];

        while (gecici!=NULL) //ogrenciler listesinin sonuna kadar arama yapiliyor..
        {
            if (gecici->sinif==sinif) //ogrencinin sinifi girilen sinif degerine esitse yazdirma ve diger islemler yapiliyor..
            {
                printf("%-6d %-30s %-5d %-9d %.2f\n",gecici->ogr_no,gecici->ad_soyad,
                       gecici->sinif,gecici->kredi_say,gecici->not_ort);
                sinif_ogr_say++;
                not_ort_top=not_ort_top+gecici->not_ort;
                if(gecici->not_ort<60)
                    altmis_alti_ogr++;
            }
            gecici=gecici->sonraki;
        }
    }
    printf("\nSinifin ogrenci sayisi: %d\n",sinif_ogr_say);
    if(sinif_ogr_say!=0)
    {
        printf("Sinifin genel not ortalamasi: %.2f\n",(float)not_ort_top/sinif_ogr_say);
        printf("Donemlik agirlikli not ortalamasi 60 in altinda olan ogr sayisi ve yuzdesi: %d - %.2f\n",altmis_alti_ogr,
               (float)(altmis_alti_ogr*100)/sinif_ogr_say);
    }
}
