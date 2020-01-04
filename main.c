#include <stdio.h>

#include <stdlib.h>

#include <time.h>
 // global degiskenler
int sayisalLoto_istatistik(int x, int y, int z);
int sansTopu_istatistik(int x, int y, int z);
int on_numara_istatistik(int x, int y, int z);
int super_loto_istatistik(int x, int y, int z);

int diziSiralamaKontrol; // 1 deðeri sayisal loto, 2 deðeri þans topu, 3 deðeri 10 numara, 4 deðeri süper loto içindir.
// bu degiskeni dizi siralama fonksiyonunun birden fazla kez yazýlmasýný engeller.
int main() {

  // Bilgisayarin her seferinde ayni sayiyi uretmemesi icin(seed degeri) srand fonksiyonu kullanildi
  srand(time(NULL));

  Menu();

  return 0;
}

void Menu() {
  int anaMenuSecim, altMenuSecim;
  char cikisCevap;

  anaMenuSecimGit:
    printf("\n***************************\n1-Sans oyunlari\n2-Cekilis Istatistikleri\n3-Cikis\n************************\nSecim yapiniz:");

  scanf("%d", & anaMenuSecim);

  switch (anaMenuSecim) {
  case 1:
    altMenuSecimGit:

      printf("\n\nSans Oyunlari\n----------------\n1-Sayisal Loto Oyna\n2-Sans Topu Oyna\n3-On Numara Oyna\n4-Super Loto Oyna\n5-Ana Menuye Don\n(Toplam odulunuz: 0 puan) Seciniz:");
    scanf("%d", & altMenuSecim);

    if (altMenuSecim == 1) {

      SayisalLoto();

    } else if (altMenuSecim == 2) {
      SansTopu();
    } else if (altMenuSecim == 3) {
      OnNumara();
    } else if (altMenuSecim == 4) {
      SuperLoto();
    } else if (altMenuSecim == 5) {
      goto anaMenuSecimGit;
    } else {
      printf("Hatali giris!\nTekrar deneyiniz\n\n");
      goto altMenuSecimGit;
    }

    // break;

  case 2:
    printf("Cekilis Istatistikleri");
    CekilisIstatistikleri();
    break;

  case 3:
    anaMenuCikisGit:

      printf("Emin misiniz?(E/e veya H/h):");
    scanf(" %c", & cikisCevap);

    if (cikisCevap == 'E' || cikisCevap == 'e') {
      break;

    } else if (cikisCevap == 'H' || cikisCevap == 'h') {
      goto anaMenuSecimGit;

    } else {
      printf("Yanlis secim!\n");
      goto anaMenuCikisGit;
    }
  default:
    printf("\nYanlis deger girdiniz!\nTekrar deneyiniz\n\n");
    goto anaMenuSecimGit;
    break;

  }
}

// Sayisal loto fonksiyonu

void SayisalLoto() {

  diziSiralamaKontrol = 1;

  int kullaniciSayilar[6]; // 6 indisli int türünde dizi oluþturuldu
  int randomSayilar[6]; // random atanan sayilar için 6 deðiþkenli integer türünde dizi oluþturuldu
  int i, j, gecici; // 3 int deðiþkeni atandý
  int toplamPuan = 0, ayniSayi = 0;

  char secim;

  sayisalLotoGit:

    // Kullanicinin sayi girmesini saglayan dongu
    for (i = 0; i < 6; i++) {
      printf("\n%2d. Sayiyi giriniz[1-49 Araliginda]: ", (i + 1));

      scanf("%d", & kullaniciSayilar[i]);

      // Aralik sarti icin kontrol
      while (kullaniciSayilar[i] < 1 || kullaniciSayilar[i] > 49) {
        printf("Girebileceginiz sayilar 1-49 araliginda olmali!\n%d. sayiyi tekrar giriniz:", (i + 1));
        scanf("%d", & kullaniciSayilar[i]);
      }

    }
  // Kullanicinin sectigi sayilarin farkli olup olmadigini kontrol etmek icin yapilan islem
  for (i = 0; i < 6; i++) {
    for (j = i + 1; j < 6; j++) {
      if (kullaniciSayilar[i] == kullaniciSayilar[j]) {
        ayniSayi++;
        printf("\n%d. ve %d. sayi birbirine esit!\nLutfen tekrar sayi seciniz", i + 1, j + 1);
        goto sayisalLotoGit;
      }
    }
  }

  // Diziyi sirala
  printf("\n\nSectiginiz sayilar\n");
  diziSirala(kullaniciSayilar);

  // Bilgisayarin 1-49 arasi birbirinden farkli random sayi olusturmasi ve diziye atmasi
  sayisalLoto_RandomSayiOlustur:
    for (i = 0; i < 6; i++) {

      // Random sayi [1-49 araliginda]
      int r = (rand() % 49) + 1;
      randomSayilar[i] = r;

      sayisalLoto_istatistik(randomSayilar[i]-1,0,1);
      sayisalLoto_istatistik(randomSayilar[i]-1,1,randomSayilar[i]);

    }

  // Random sayilarin farkli olup olmadigini kontrol etmek icin kontrol
  for (i = 0; i < 6; i++) {
    for (j = i + 1; j < 6; j++) {
      while (randomSayilar[i] == randomSayilar[j]) {
        ayniSayi++;
        goto sayisalLoto_RandomSayiOlustur;
      }
    }
  }

  printf("\nCekilis sonuclari\n");
  diziSirala(randomSayilar);

  int sayac = 0, puan = 0;

  // Dizileri karsilastir

  for (i = 0; i < 6; i++) {
    if (kullaniciSayilar[i] == randomSayilar[i]) {
      sayac++;
    }
  }

  // Puan hesaplamalari

  if (sayac == 3) {
    puan += 32;
    toplamPuan += puan;
  } else if (sayac == 4) {
    puan += 64;
    toplamPuan += puan;

  } else if (sayac == 5) {
    puan += 128;
    toplamPuan += puan;

  } else if (sayac == 6) {
    puan += 256;
    toplamPuan += puan;
  } else {
    puan += 0;
    toplamPuan += puan;

  }

  printf("\nTutturdugunuz sayilar: %d\nBu oyunda kazandiginiz puan:%d\nSayisal lotoda kazandiginiz toplam puan:%d\n", sayac, puan, toplamPuan);

  printf("Yeni bir sayisal loto oyunu oynamak ister misiniz?(E/e veya H/h):");
  scanf(" %c", & secim);

  if (secim == 'E' || secim == 'e') {
    goto sayisalLotoGit;
  } else if (secim == 'H' || secim == 'h') {

    // Alt menuye git
    oyunCikis();
  }

}

// Sans topu fonksiyonu

void SansTopu() {

  int snsTpKullaniciSayilar[5]; // 1-34 araliginda 5 farkli sayi icin dizi olusturuldu
  int snsTpRandomSayilar[5];
  int i, k, toplamPuan = 0, z, tekSayi, ayniSayi = 0;

  diziSiralamaKontrol = 2;

  SansTopuOynaGit:

    for (k = 0; k < 5; k++) {
      printf("\n%2d. Sayiyi giriniz[1-34 Araliginda]: ", (k + 1));

      scanf("%d", & snsTpKullaniciSayilar[k]);

      // Aralik sarti icin kontrol
      while (snsTpKullaniciSayilar[k] < 1 || snsTpKullaniciSayilar[k] > 34) {
        printf("Girebileceginiz sayilar 1-34 araliginda olmali!\n%d. sayiyi tekrar giriniz:", (k + 1));
        scanf("%d", & snsTpKullaniciSayilar[k]);
      }
    }

  // Kullanicinin girdigi sayilarin farkli olup olmadigini kontrol etmek icin yapilan islem
  for (i = 0; i < 5; i++) {
    for (z = i + 1; z < 5; z++) {
      if (snsTpKullaniciSayilar[i] == snsTpKullaniciSayilar[z]) {
        ayniSayi++;
        printf("\n%d. ve %d. sayi birbirine esit!\nLutfen tekrar sayi seciniz", i + 1, z + 1);
        goto SansTopuOynaGit;
      }
    }
  }

  // Kullanicidan tek sayi alma islemi
  printf("\n Sayiyi giriniz[1-14 Araliginda]:");
  scanf("%d", & tekSayi);
  while (tekSayi < 1 || tekSayi > 14) {
    printf("Girebileceginiz sayilar 1-14 araliginda olmali!\n Sayiyi tekrar giriniz:");
    scanf("%d", & tekSayi);
  }

  // Diziyi Sirala
  printf("\n\nSectiginiz sayilar\n");
  diziSirala(snsTpKullaniciSayilar);
  printf("+\t%d", tekSayi);

  sansTopu_RandomSayiOlustur:
    for (i = 0; i < 5; i++) {
      // Random sayi [1-34 araliginda]
      int r = (rand() % 34) + 1;

      //Hizli test yapmak icin
      //int r = (rand() % 5) + 1;

      snsTpRandomSayilar[i] = r;
       sansTopu_istatistik(snsTpRandomSayilar[i]-1,0,1);
       sansTopu_istatistik(snsTpRandomSayilar[i]-1,1,snsTpRandomSayilar[i]);
    }

  // Random sayilarin farkli olup olmadigini kontrol etme islemi
  for (i = 0; i < 5; i++) {
    for (z = i + 1; z < 5; z++) {
      while (snsTpRandomSayilar[i] == snsTpRandomSayilar[z]) {
        ayniSayi++;
        goto sansTopu_RandomSayiOlustur;
      }
    }
  }

  // Hizli test yapmak icin
  // int tekSayiRandom = (rand() % 3) + 1;

  // 1-14 araliginda random sayi
  int tekSayiRandom = (rand() % 14) + 1;

  printf("\nCekilis sonuclari\n");
  diziSirala(snsTpRandomSayilar);
  printf("+\t%d", tekSayiRandom);

  int sayac = 0, sansTopuSayac = 0, puan = 0, j;
  char secim;

  // Dizileri karsilastir

  for (j = 0; j < 5; j++) {

    if (snsTpKullaniciSayilar[j] == snsTpRandomSayilar[j] && tekSayi == tekSayiRandom) {
      sayac++;
      sansTopuSayac = 1; // Kullanicinin tek sayisi random sayiya esitse sans topu sayacini 1'e sabitle (Puan hesaplamasi icin)

    } else if (snsTpKullaniciSayilar[j] == snsTpRandomSayilar[j]) {
      sayac++;
      sansTopuSayac = 0;
    }

  }

  // Puan hesaplamalari

  if (sayac == 1 && sansTopuSayac == 1) {
    puan += 2;
    toplamPuan += puan;
  } else if (sayac == 2 && sansTopuSayac == 1) {
    puan += 4;
    toplamPuan += puan;
  } else if (sayac == 3 && sansTopuSayac != 1) {
    puan += 8;
    toplamPuan += puan;
  } else if (sayac == 3 && sansTopuSayac == 1) {
    puan += 16;
    toplamPuan += puan;
  } else if (sayac == 4 && sansTopuSayac != 1) {
    puan += 32;
    toplamPuan += puan;
  } else if (sayac == 4 && sansTopuSayac == 1) {
    puan += 64;
    toplamPuan += puan;
  } else if (sayac == 5 && sansTopuSayac != 1) {
    puan += 128;
    toplamPuan += puan;
  } else if (sayac == 5 && sansTopuSayac == 1) {
    puan += 256;
    toplamPuan += puan;
  } else {
    puan += 0;
    toplamPuan += puan;

  }

  printf("\nTutturdugunuz sayilar: %d\nSans topu:%d\nBu oyunda kazandiginiz puan:%d\nSans topunda kazandiginiz toplam puan:%d\n", sayac, sansTopuSayac, puan, toplamPuan);

  printf("Yeni bir sans topu oyunu oynamak ister misiniz?(E/e veya H/h):");
  scanf(" %c", & secim);

  if (secim == 'E' || secim == 'e') {
    goto SansTopuOynaGit;
  } else if (secim == 'H' || secim == 'h') {

    // Alt menuye git
    oyunCikis();
  }

}

// On numara fonksiyonu
void OnNumara() {

  diziSiralamaKontrol = 3;

  int kullaniciSayilar[10]; // 10 indisli int türünde dizi oluþturuldu
  int randomSayilar[22]; // random atanan sayilar için 22 deðiþkenli integer türünde dizi oluþturuldu
  int i, j, gecici;
  int toplamPuan = 0, ayniSayi = 0;

  char secim;

  onNumaraGit:

    // Kullanicinin sayi girmesini saglayan dongu
    for (i = 0; i < 10; i++) {
      printf("\n%2d. Sayiyi giriniz[1-80 Araliginda]: ", (i + 1));

      scanf("%d", & kullaniciSayilar[i]);

      // Aralik sarti icin kontrol
      while (kullaniciSayilar[i] < 1 || kullaniciSayilar[i] > 80) {
        printf("Girebileceginiz sayilar 1-49 araliginda olmali!\n%d. sayiyi tekrar giriniz:", (i + 1));
        scanf("%d", & kullaniciSayilar[i]);
      }

    }
  // Kullanicinin sectigi sayilarin farkli olup olmadigini kontrol etmek icin yapilan islem
  for (i = 0; i < 10; i++) {
    for (j = i + 1; j < 10; j++) {
      if (kullaniciSayilar[i] == kullaniciSayilar[j]) {
        ayniSayi++;
        printf("\n%d. ve %d. sayi birbirine esit!\nLutfen tekrar sayi seciniz", i + 1, j + 1);
        goto onNumaraGit;
      }
    }
  }

  // Diziyi sirala
  printf("\n\nSectiginiz sayilar\n");
  diziSirala(kullaniciSayilar);

  // Bilgisayarin 1-80 arasi birbirinden farkli random sayi olusturmasi ve diziye atmasi
  onNumara_RandomSayiOlustur:
    for (i = 0; i < 22; i++) {

      // Random sayi [1-80 araliginda]
      int r = (rand() % 80) + 1;
      randomSayilar[i] = r;

       on_numara_istatistik(randomSayilar[i]-1,0,1);
        on_numara_istatistik(randomSayilar[i]-1,1,randomSayilar[i]);

    }

  // Random sayilarin farkli olup olmadigini kontrol etmek icin kontrol
  for (i = 0; i < 22; i++) {
    for (j = i + 1; j < 22; j++) {
      while (randomSayilar[i] == randomSayilar[j]) {
        ayniSayi++;
        goto onNumara_RandomSayiOlustur;
      }
    }
  }

  printf("\nCekilis sonuclari\n");

  // Siralama
  int a, b;
  for (a = 0; a < 22; a++) {
    for (b = 0; b < 22 - a - 1; b++) {
      // ilk iki sayiyi karsilastir
      if (randomSayilar[b] > randomSayilar[b + 1]) {
        // Eger 0. index 1. indexten buyukse 0. indexi gecici degiskenine aktar
        gecici = randomSayilar[b];
        // kucuk olan 1. indexi buyuk olan 0. index ile yer degistir
        randomSayilar[b] = randomSayilar[b + 1];
        // gecici degiskeni(buyuk olan index) 1. indexe yerlestir
        randomSayilar[b + 1] = gecici;
      }
    }
  }

  for (a = 0; a < 22; a++) {
    printf("%d\t", randomSayilar[a]);
  }

  int sayac = 0, puan = 0;

  // Dizileri karsilastir

  for (i = 0; i < 22; i++) {
    if (kullaniciSayilar[i] == randomSayilar[i]) {
      sayac++;
    }
  }

  // Puan hesaplamalari

  if (sayac == 0) {
    puan += 8;
    toplamPuan += puan;
  } else if (sayac == 6) {
    puan += 16;
    toplamPuan += puan;

  } else if (sayac == 7) {
    puan += 32;
    toplamPuan += puan;

  } else if (sayac == 8) {
    puan += 64;
    toplamPuan += puan;
  } else if (sayac == 9) {
    puan += 128;
    toplamPuan += puan;
  } else if (sayac == 10) {
    puan += 256;
    toplamPuan += puan;
  } else {
    puan += 0;
    toplamPuan += puan;

  }

  printf("\nTutturdugunuz sayilar: %d\nBu oyunda kazandiginiz puan:%d\nSayisal lotoda kazandiginiz toplam puan:%d\n", sayac, puan, toplamPuan);

  printf("Yeni bir on numara oyunu oynamak ister misiniz?(E/e veya H/h):");
  scanf(" %c", & secim);

  if (secim == 'E' || secim == 'e') {
    goto onNumaraGit;
  } else if (secim == 'H' || secim == 'h') {

    // Alt menuye git
    oyunCikis();
  }

}
void SuperLoto() {

  diziSiralamaKontrol = 4;

  int kullaniciSayilar[6];
  int randomSayilar[6];
  int i, j, gecici;
  int toplamPuan = 0, ayniSayi = 0;

  char secim;

  superLotoGit:
    for (i = 0; i < 6; i++) {
      printf("\n%2d. Sayiyi giriniz[1-54 Araliginda]: ", (i + 1));
      scanf("%d", & kullaniciSayilar[i]);

      while (kullaniciSayilar[i] < 1 || kullaniciSayilar[i] > 49) {
        printf("Girebileceginiz sayilar 1-54 araliginda olmalidir!\n%d. sayiyi tekrar giriniz:", (i + 1));
        scanf("%d", & kullaniciSayilar[i]);
      }

    }
  for (i = 0; i < 6; i++) {
    for (j = i + 1; j < 6; j++) {
      if (kullaniciSayilar[i] == kullaniciSayilar[j]) {
        ayniSayi++;
        printf("\n%d. ve %d. sayi birbirine esit!\nLutfen tekrar sayi seciniz", i + 1, j + 1);
        goto superLotoGit;
      }
    }
  }

  printf("\n\nSectiginiz sayilar\n");

  diziSirala(kullaniciSayilar);

  superLoto_RandomSayiOlustur:

    for (i = 0; i < 6; i++) {
      int r = (rand() % 54) + 1;
      randomSayilar[i] = r;
       super_loto_istatistik(randomSayilar[i]-1,0,1);
        super_loto_istatistik(randomSayilar[i]-1,1,randomSayilar[i]);
    }

  for (i = 0; i < 6; i++) {
    for (j = i + 1; j < 6; j++) {
      while (randomSayilar[i] == randomSayilar[j]) {
        ayniSayi++;
        goto superLoto_RandomSayiOlustur;
      }
    }
  }
  printf("\nCekilis sonuclari\n");
  diziSirala(randomSayilar);

  // Karsilastirma yap
  int sayac = 0, puan = 0;
  for (i = 0; i < 6; i++); {
    if (kullaniciSayilar[i] == randomSayilar[i]) {
      sayac++;
    }
  }
  // Puan hesapla
  if (sayac == 3) {
    puan += 32;
    toplamPuan += puan;
  } else if (sayac == 4) {
    puan += 64;
    toplamPuan += puan;
  } else if (sayac == 5) {
    puan += 128;
    toplamPuan += puan;
  } else if (sayac == 6) {
    puan += 256;
    toplamPuan += puan;
  }

    puan += 0;
    toplamPuan += puan;

  printf("\n Tutturdugunuz sayilar: %d\n Bu oyunda kazandiginiz puan:%d\n Super Lotoda kazandiginiz toplam puan:%d\n", sayac, puan, toplamPuan);
  printf("Yeni bir super loto oynamak ister misiniz?(E/e veya H/h):");
  scanf(" %c", & secim);

  if (secim == 'E' || secim == 'e') {
    goto superLotoGit;
  } else if (secim == 'H' || secim == 'h') {
    oyunCikis();
  }

}

// Dizi siralama fonksiyonu (Bubble sort ile)
void diziSirala(int dizi[]) {

  int diziLimit = 0;
  if (diziSiralamaKontrol == 1)
    diziLimit = 6;

  else if (diziSiralamaKontrol == 2)
    diziLimit = 5;

  else if (diziSiralamaKontrol == 3)
    diziLimit = 10;

  else if (diziSiralamaKontrol == 4)
    diziLimit = 6;

  // Siralama
  int i, j, gecici;
  for (i = 0; i < diziLimit; i++) {
    for (j = 0; j < diziLimit - i - 1; j++) {
      // ilk iki sayiyi karsilastir
      if (dizi[j] > dizi[j + 1]) {
        // Eger 0. index 1. indexten buyukse 0. indexi gecici degiskenine aktar
        gecici = dizi[j];
        // kucuk olan 1. indexi buyuk olan 0. index ile yer degistir
        dizi[j] = dizi[j + 1];
        // gecici degiskeni(buyuk olan index) 1. indexe yerlestir
        dizi[j + 1] = gecici;
      }
    }
  }

  for (i = 0; i < diziLimit; i++) {
    printf("%d\t", dizi[i]);
  }
}

void oyunCikis() {
  char altMenuSecim;
  altMenuSecimGit:
    printf("\n\nSans Oyunlari\n--------\n1-Sayisal Loto Oyna\n2- Sans Topu Oyna\n3-On Numara Oyna\n4-Super Loto Oyna\n5-Ana Menuye Don\n(Toplam Odulunuz 0 puan) Seciniz:");
  scanf("%d", & altMenuSecim);

  if (altMenuSecim == 1) {
    SayisalLoto();
  } else if (altMenuSecim == 2) {
    SansTopu();
  } else if (altMenuSecim == 3) {
    OnNumara();
  } else if (altMenuSecim == 4) {
    SuperLoto();
  } else if (altMenuSecim == 5) {
    Menu();
  } else {
    printf("Hatali giris!\nTekrar deneyiniz\n\n");
    goto altMenuSecimGit;

  }

}

int sayisalLoto_istatistik(int x, int y, int z)
{
    static int dizi[49][2],oyun=0;
    int i;
    if(oyun==0)
        for(i=0;i<49;i++)
            dizi[i][0]=0;
    oyun=1;
    if(y==0)
        dizi[x][y] +=z;
    else if(z!=0)
        dizi[x][y] =z;

    return dizi[x][y];
}

int sansTopu_istatistik(int x,int y,int z)
{
    static int dizi[34][2],oyun=0;
    int i;
    if(oyun==0)
        for(i=0;i<34;i++)
        dizi[i][0]=0;
    oyun=1;
    if(y==0)
        dizi[x][y] +=z;
    else if(z!=0)
        dizi[x][y] =z;

    return dizi[x][y];

}

int on_numara_istatistik(int x,int y,int z)
{

    static int dizi[80][2],oyun=0;
    int i;
    if(oyun==0)
        for(i=0;i<80;i++)
        dizi[i][0]=0;
    oyun=1;
    if(y==0)
        dizi[x][y] +=z;
    else if(z!=0)
        dizi[x][y] =z;

    return dizi[x][y];

}
int super_loto_istatistik(int x, int y, int z)
{

    static int dizi[54][2],oyun=0;
    int i;
    if(oyun==0)
        for(i=0;i<54;i++)
        dizi[i][0]=0;
    oyun=1;
    if(y==0)
        dizi[x][y] +=z;
    else if(z!=0)
        dizi[x][y] =z;

    return dizi[x][y];

}

void sayisalLoto_ist()
{
    int i,j;
        int a[49][2];
        for(i=0;i<49;i++)
            a[i][0]=sayisalLoto_istatistik(i,0,0);
        for(i=0;i<49;i++)
            a[i][1]=sayisalLoto_istatistik(i,1,0);
        for(i=0;i<49;i++)
        {
            for(j=0;j<48;j++)
            {
                if(a[j][0]<a[j+1][0]){
                    int gecici;
                    gecici = a[j][0];
                    a[j][0] = a[j+1][0];
                    a[j+1][0] = gecici;
                    gecici = a[j][1];
                    a[j][1] = a[j+1][1];
                    a[j+1][1] = gecici;
                }
            }
        }
        printf("Sayisal Loto Istatistik:\n");
        for(i=0;i<6;i++){
            printf("%d\t%d\n",a[i][1],a[i][0]);
        }
}

void sansTopu_ist()
{
           int i,j;
        int b[34][2];
        for(i=0;i<34;i++)
            b[i][0]=sansTopu_istatistik(i,0,0);
        for(i=0;i<34;i++)
            b[i][1]=sansTopu_istatistik(i,1,0);
        for(i=0;i<34;i++)
        {
            for(j=0;j<34;j++)
            {
                if(b[j][0]<b[j+1][0]){
                    int gecici;
                    gecici = b[j][0];
                    b[j][0] = b[j+1][0];
                    b[j+1][0] = gecici;
                    gecici = b[j][1];
                    b[j][1] = b[j+1][1];
                    b[j+1][1] = gecici;
                }
            }
        }
        printf("Sans Topu  Istatistik:\n");
            for(i=0;i<5;i++){
            printf("%d\t%d\n",b[i][1],b[i][0]);
            }


}
void on_numara_ist()
{
    int i,j;
        int a[80][2];
        for(i=0;i<80;i++)
            a[i][0]=on_numara_istatistik(i,0,0);
        for(i=0;i<80;i++)
            a[i][1]=on_numara_istatistik(i,1,0);
        for(i=0;i<80;i++)
        {
            for(j=0;j<80;j++)
            {
                if(a[j][0]<a[j+1][0]){
                    int gecici;
                    gecici = a[j][0];
                    a[j][0] = a[j+1][0];
                    a[j+1][0] = gecici;
                    gecici = a[j][1];
                    a[j][1] = a[j+1][1];
                    a[j+1][1] = gecici;
                }
            }
        }
        printf("On Numara Istatistik:\n");
        for(i=0;i<10;i++){
            printf("%d\t%d\n",a[i][1],a[i][0]);
        }

}
void super_loto_ist()
{
    int i,j;
        int a[54][2];
        for(i=0;i<54;i++)
            a[i][0]=super_loto_istatistik(i,0,0);
        for(i=0;i<54;i++)
            a[i][1]=super_loto_istatistik(i,1,0);
        for(i=0;i<54;i++)
        {
            for(j=0;j<54;j++)
            {
                if(a[j][0]<a[j+1][0]){
                    int gecici;
                    gecici = a[j][0];
                    a[j][0] = a[j+1][0];
                    a[j+1][0] = gecici;
                    gecici = a[j][1];
                    a[j][1] = a[j+1][1];
                    a[j+1][1] = gecici;
                }
            }
        }
        printf("Super Loto Istatistik:\n");
        for(i=0;i<6;i++){
            printf("%d\t%d\n",a[i][1],a[i][0]);
        }

}

void CekilisIstatistikleri()
{
    int secim;
    printf("1.Sayisal Loto Istatistikleri\n");
    printf("2.Sans Topu Istatistikleri\n");
    printf("3.On Numara Istatistikler\n");
    printf("4.Super Loto Istatistikler\n");
    printf("Seciminizi Girin:\n");
    scanf("%d",&secim);

    switch(secim){
case 1:
    sayisalLoto_ist();
    break;
case 2:
    sansTopu_ist();

case 3:
    on_numara_ist();
    break;

case 4:
    super_loto_ist();
    break;

    }
}
