#include <stdio.h>
#include <string.h>    
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#define okulNO 48

int otoSayac = 1;
int seferSayac = 0;
int otobusler[100][3];//kapasite - personel sayisi - ID
char modeller[100][10];
char seferNolar[100][10];//SeferNo
int seferNoInt[100];
char basSehirler[100][10];
char sonSehirler[100][10];
int seferInt[100][5];//oto basSaat sonSaat hasilat kapasite
char sifreAnahtarlar[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char musteriler[100][100] = {};//"a3x42","c2x21","b4x1","a4x1"
char rezNolar[100][10];
char isimler[100][20];
char soyadlar[100][20];
int musteriTotalSayac=0;
int musteriAnlik;
int rezSayac=0;


void anaMenu();
void firmaGiris();
void otobusEkle();
void seferEkle();
void seferBilgisi();
void musteriMenu();
void koltukGoster(int i);
int kapat();
void controller(int kod);
float checkTime(float saat);
int charToInt(int letter);
void sortArray();
void seferListele();
void rezervasyonYap();
void rezGoster();

void controller(int kod){

    switch (kod)
    {
    case 1:
        anaMenu();
        break;
    case 11:
        firmaGiris();
        break;
    case 12:
        musteriMenu();
        break;
    case 21:
        otobusEkle();
        break;
    case 22:
        seferEkle();
        break;
    case 23:
        seferBilgisi();
        break;
    case 31:
        seferListele();
        break;
    case 32:
        rezervasyonYap();
        break;
    case 34:
        rezGoster();
        break;
    }
}

int charToInt(int letter){
    return (48 -(int)letter)*(-1);
}

void sortArray(){
    int tempRes = 0;
    int val,tempPow,temp;
    char tempChar[10];
    int len = 5;

    for (int j = 0; j < seferSayac; j++)//48A4F5
    {
        len = 5;
        for (int i = 0; i < 6; i++)
        {
            
            if(seferNolar[j][i]>='0' && seferNolar[j][i]<='9')//4
            {
                val = seferNolar[j][i] - 48;//52-48 => val = 4 
            }
            else if(seferNolar[j][i]>='A' && seferNolar[j][i]<='F')
            {
                val = seferNolar[j][i] - 65 + 10;
            }
            tempPow = pow(16,len);// = 16^5
            tempRes += tempPow * val;// += 16^5 * 4
            len--; // 4
        }

        seferNoInt[j] = tempRes;
        tempRes = 0;
    }

    for (int i = 0; i < seferSayac; i++)
    {
        for (int j = i+1; j < seferSayac; j++)
        {
               if (seferNoInt[i] < seferNoInt[j]) 
                {
 
                    temp =  seferNoInt[i];
                    strcpy(tempChar,seferNolar[i]);

                    seferNoInt[i] = seferNoInt[j];
                    strcpy(seferNolar[i], seferNolar[j]);

                    seferNoInt[j] = temp;
                    strcpy(seferNolar[j],tempChar);
 
                } 
        }
    }
    
}

int kapat(){
    return 0;
}

void koltukGoster(int no){
    int otoKapasite,hasilat,isInt,row,column,x,y,isFull;
    musteriAnlik=0;
    otoKapasite = seferInt[no][4];
    hasilat = seferInt[no][3];
    isInt = otoKapasite % 4 == 0 ? 0 : otoKapasite % 4;//0
    row = isInt == 0 ? otoKapasite/4 : ((int)((float)otoKapasite / 4))+1 ;//8
    column = 4;
    int xNums[100],yNums[100];

    for (int i = 0; i < musteriTotalSayac; i++)
    {
        if((musteriler[i][0]) == 97 + no){
            x = charToInt(musteriler[i][1]);
            y = charToInt(musteriler[i][3]);
            if(musteriler[i][4]){
                y = (y * 10) + (charToInt(musteriler[i][4]));
            }
            musteriAnlik++;
            xNums[i] = x;
            yNums[i] = y;
        }
    }

    printf("\n     1   2      3   4\n");
    for (int i = 0; i < row ; i++)
    {
        if (i == row-1 && isInt != 0)
        {
            column = isInt;
        }
        else{
            column = 4;
        }
        
        if (i >= 9)
        {
            printf("%d. ",i+1);
        }
        else{
            printf("%d.  ",i+1);
        }
        
        for (int j = 0; j < column; j++)
        {
            for (int k = 0; k < musteriTotalSayac; k++)
            {
                if (j+1 == xNums[k] && i+1 == yNums[k])
                {
                    isFull = 1;
                    break;
                }
                else
                {
                    isFull = 0;
                }
            }
            if (isFull == 1)
            {
                printf("[X] ");
            }
            else
            {
                printf("[ ] "); 
            }
            
            if (j == 1)
            {
                printf("   ");
            }

        }        
        
        printf("\n");
        
    }
}

void rezGoster(){
    char girRezNo[10];
    int ID,x,y;
    printf("Rezervasyon numaranizi giriniz: ");
    scanf("%s",girRezNo);
    for (int i = 0; i < rezSayac; i++)
    {
        if (strcmp(rezNolar[i],girRezNo) == 0)
        {
            ID = i;
        }
        
    }
    
    x = charToInt(musteriler[ID][1]);
    y = charToInt(musteriler[ID][3]);
    if(musteriler[ID][4]){
        y = (y * 10) + (charToInt(musteriler[ID][4]));
    }
    
    printf("\n- Rezervasyon bilgileri -\n");
    printf("Rezervasyon sahibinin ismi: %s\n",isimler[ID]);
    printf("Rezervasyon sahibinin soyismi: %s\n",soyadlar[ID]);
    printf("Rezervasyon sahibinin koltuk numarasi : %dx%d\n",x,y);
    printf("\n- Sefer bilgileri -\n");
    printf("\n%d. Sefer => %s\n",ID+1,seferNolar[ID]);
    printf("Baslangic ve Bitis Sehri: %s - %s\n",basSehirler[ID],sonSehirler[ID]);
    printf("Baslangic ve Bitis Saat: %d:%d - %d:%d\n",(int)(seferInt[ID][1]/100),okulNO,(int)(seferInt[ID][2]/100),okulNO);
    printf("Otobus Numarasi: %d\n",seferInt[ID][0]);
    printf("Kisi basi ucret: %d\n\n\n",(seferInt[ID][3]/seferInt[ID][4]));

    anaMenu();
}

void rezervasyonYap(){
    sortArray();
    char girSeferNo[10],isim[20],soyad[20],sifre[6],onay,rezNo[8];
    int seferID,sutun,satir,x,y,durum,kod;

    printf("Sefer numaranizi giriniz\n");
    scanf("%s",girSeferNo);

    for (int i = 0; i < seferSayac; i++)
    {
        if (strcmp(girSeferNo,seferNolar[i]) == 0)
        {
            seferID = i;
        }
        
    }
    koltukGoster(seferID);
    printf("\n\n");

    printf("Adiniz: ");
    scanf("%s",isimler[musteriTotalSayac]);
    printf("Soyadiniz: ");
    scanf("%s",soyadlar[musteriTotalSayac]);

    sutunTekrar:
    printf("Sutun no giriniz: (1,2,3,4)");
    scanf("%d",&sutun);
    if (sutun < 1 || sutun > 4)
    {
        printf("Hatalı koltuk girdiniz\n");
        goto sutunTekrar;
    }

    satirTekrar:
    printf("Satir no giriniz: ");
    scanf("%d",&satir);
    if ((4 * satir) - (4-sutun) > seferInt[seferID][4]  )
    {
        printf("Hatalı koltuk girdiniz\n");
        goto satirTekrar;
    }
    printf("\n");
    for (int i = 0; i < musteriTotalSayac; i++)
    {
        if ((musteriler[i][0]) == 97 + seferID)
        {
            x = charToInt(musteriler[i][1]);
            y = charToInt(musteriler[i][3]);
            if(musteriler[i][4]){
                y = (y * 10) + (charToInt(musteriler[i][4]));
            }
            if (x == sutun && y == satir)
            {
                printf("Rezervasyon almak istediginiz yer dolu\n");
                goto sutunTekrar;
                break;
            }
            
        }
        
    }
    
    //Sifre ekleme
    sifre[0] = 97+seferID;
    sifre[1] = sutun + '0';
    sifre[2] = 'x';
    if(satir / 10 == 2){
        sifre[3] = (satir / 10) + '0';
        sifre[4] = (satir % 10) + '0';
    }
    else{sifre[3] = satir + '0';}

    strcpy(musteriler[musteriTotalSayac],sifre);

    musteriTotalSayac++;

    printf("%d",musteriTotalSayac);
    koltukGoster(seferID);

    printf("Onayliyor musunuz? E/H \n");
    scanf(" %c",&onay);

    if(tolower(onay) == 'h'){   
        musteriTotalSayac--;
        strcpy(musteriler[musteriTotalSayac],"");
        strcpy(isimler[musteriTotalSayac],"");
        strcpy(soyadlar[musteriTotalSayac],"");
        musteriMenu();
    }
    else if(tolower(onay) == 'e'){
        srand(time(NULL));
        for (int i = 0; i < 8; i++)
        {
            durum = rand() % 3;
            if (durum == 0)
            {
                kod = 97 + rand() % (122 - 97 + 1);
                rezNo[i] = kod;
            }
            else if (durum == 1)
            {
                kod = 65 + rand() % (90 - 65 + 1);
                rezNo[i] = kod;
            }
            else{
                kod = 48 + rand() % (57 - 48 + 1);
                rezNo[i] = kod;
            }
            
        }
        printf("\nRezervasyon Numaraniz: %s",rezNo);
        strcpy(rezNolar[rezSayac],rezNo);
        rezSayac++;
        musteriMenu();
    }
    
}

void seferListele(){
    char cikisYapici;
    sortArray();
    for (int i = 0; i < seferSayac; i++)
    {
        printf("\n%d. Sefer => %s\n",i+1,seferNolar[i]);
        printf("Baslangic ve Bitis Sehri: %s - %s\n",basSehirler[i],sonSehirler[i]);
        printf("Baslangic ve Bitis Saat: %d:%d - %d:%d\n",(int)(seferInt[i][1]/100),okulNO,(int)(seferInt[i][2]/100),okulNO);
        printf("Otobus Numarasi: %d\n",seferInt[i][0]);
        printf("Musait koltuk sayisi: %d\n",(seferInt[i][4]-musteriAnlik));
        printf("Kisi basi ucret: %d\n\n\n",(seferInt[i][3]/seferInt[i][4]));
    }
    //BURAYA
    musteriMenu();
    
}

void seferBilgisi(){
    int id,row,column,otoKapasite,isInt,hasilat,topPara,basSaatKisim,sonSaatKisim;
    char x;
    char y;

    sortArray();

    for (int i = 0; i < seferSayac; i++)
    {
        printf("%d. %s\n",i+1,seferNolar[i]);
    }
    printf("\n Sefer no giriniz: ");
    scanf("%d",&id);
    
    koltukGoster(id-1);
    printf("%d",musteriAnlik);
    otoKapasite = seferInt[id-1][4];
    hasilat = seferInt[id-1][3];
    topPara = (hasilat/otoKapasite)*musteriAnlik;
    basSaatKisim = (int)(seferInt[id-1][1]/100);
    sonSaatKisim = (int)(seferInt[id-1][2]/100);

    printf("\n ------Bilgiler------ \n");
    printf("Toplam Hasilat: %d\n",topPara);
    printf("Toplam Bos Koltuk Sayisi: %d\n",otoKapasite-musteriAnlik);
    printf("Baslangic Sehri: %s\n",basSehirler[id-1]);
    printf("Bitis Sehri: %s\n",sonSehirler[id-1]);
    printf("Kalkis Saat: %d:%d\n",basSaatKisim,okulNO);
    printf("Varis Saat: %d:%d\n",sonSaatKisim,okulNO);
    printf("Sefer Numara: %s\n",seferNolar[id-1]);
    printf("Otobus Numara: %d\n",otobusler[id-1][2]);

    anaMenu();
}

float checkTime(float saat){

    if(saat >= 100 && saat < 2500){
        float isCheck = (saat-okulNO)/100;
        printf("%f : %d\n",isCheck,(int)isCheck);
        if ((int)isCheck != isCheck) // eğer bu değer sağlanirsa kullanici 2245 girmiştir mesela
        {
            printf("Sefer bu saate gerçekleştirilemez\n");
            saat = (((int)(saat/100))*100)+okulNO;
            // 2245 => 2245/100 => 22.45 => int => 22 => 22 * 100 => 2200 => 2200 + 48 => 2248
            //her türlü sonu 48 çikarticak
        }
        else{
            printf("Else");
        }
    }
    else if(saat >= 0 && saat <= 24){
        printf("Sefer bu saate gerçekleştirilemez\n");
        saat = (saat*100)+48;
    }
    else{
        printf("Lütfen düzgün bir sayi giriniz\n");
        saat = 0;
    }
    return saat;
}

void seferEkle(){
    char sifre[10];
    int kontrol = 0;
    int oto,hasilat,sure,otoKapasite,otoPersonel;
    float basSaat,sonSaat;
    char basSehir,sonSehir;

    while (1)
    {   
        printf("Otobus numarasini giriniz: ");
        scanf("%d",&oto);
        if(oto < otoSayac && oto > 0){
            break;
        }
        printf("Varolan bir otobus numarasi giriniz\n");
        printf("Seceneklerimiz: \n");
        for (int i = 1; i < otoSayac; i++)
        {
            printf("%d ",i);
        }
        printf("\n");
    }
    
    checkPoint:
    
    while(1){
        printf("Hangi saatte yola çikicaksiniz: ");
        scanf("%f",&basSaat);
        basSaat = checkTime(basSaat);
        if((int)basSaat != 0){
            break;
        }
    }

    while (1)
    {
        printf("Tahmini varis saatini giriniz: ");
        scanf("%f",&sonSaat);

        sonSaat = checkTime(sonSaat);

        if((int)sonSaat != 0){
            break;
        }

    }
        

    if (sonSaat > basSaat)
    {
        sure = (int)(sonSaat - basSaat) / 100;
    }
    else{
        sure = 24 - (((int)(basSaat - sonSaat))/100);
    }

    otoKapasite = otobusler[oto-1][0];
    seferInt[seferSayac][4] = otoKapasite;
    otoPersonel = otobusler[oto-1][1];

    int basSaatKismi = (int)(basSaat/100);
    int sonSaatKismi = (int)(sonSaat/100);

    if (sure > 4)
    {
        if(otoKapasite >= 30 && otoPersonel == 3){
            printf("Baslangic %d:%d \nbitis %d:%d \nsaat: %d saat\n",basSaatKismi,okulNO,sonSaatKismi,okulNO,sure);
        }
        else{
            printf("Lutfen 4 saatten kisa bir süre secin\n");
            goto checkPoint;
        }   
    }
    else{
        printf("\nBaslangic %d:%d \nbitis %d:%d \nsaat: %d saat\n",basSaatKismi,okulNO,sonSaatKismi,okulNO,sure);
    }

    printf("\nBaslangic sehrini girin: ");
    scanf("%s[^\n]",basSehirler[seferSayac]);

    printf("Bitis sehrini girin: ");
    scanf("%s[^\n]",sonSehirler[seferSayac]);

    printf("Toplam hasilat girin: ");
    scanf("%d",&hasilat);

    printf("Kisi basina dusen ucret: %.2f\n",(float)hasilat / (float)otoKapasite);

    sifrePoint:
    srand(time(NULL));

    for (int i = 0; i < 4; i++)
    {
        int r= rand() % 16;
        sifre[i] = sifreAnahtarlar[r];
    }

    // int boyut = strlen(sifre)-4;
    // sifre[boyut] = '\0';//Sondaki gereksizler kaldirildi

    if(seferSayac > 0){ //Hiç sefer eklenmemiş
        for (int i = 0; i < seferSayac + 1; i++)
        {
            if(sifre == seferNolar[i]){
                kontrol += 1;
            }
        }
        if(kontrol != 0){
            goto sifrePoint;
        }
    }
    
    sifre[6] = '\0';
    sifre[5] = sifre[3];
    sifre[4] = sifre[2];
    sifre[3] = sifre[1];
    sifre[2] = sifre[0];
    sifre[1] = '8';
    sifre[0] = '4';

    // int boyut = strlen(sifre)-1;
    // sifre[boyut] = '\0';
    strcpy(seferNolar[seferSayac],sifre);
    //seferNolar[seferSayac] = sifre;//oto bassaat sonsaat hasilat

    seferInt[seferSayac][0] = oto;
    seferInt[seferSayac][1] = basSaat;
    seferInt[seferSayac][2] = sonSaat;
    seferInt[seferSayac][3] = hasilat;
    
    seferSayac += 1;

    firmaGiris();
}

void otobusEkle(){
    int perSayi,kapasite;

    printf("yolcu kapasitesini girin: ");
    scanf("%d",&kapasite);
    
    while (1)
    {
        printf("personal sayisi girin: ");
        scanf("%d",&perSayi);
        if(perSayi == 3 || perSayi == 2){
            break;
        }
        printf("Hatali personel sayisi girdiniz!!!!\n");
    }
    
    printf("Model giriniz: ");
    scanf("%s[^\n]",modeller[otoSayac-1]);

    otobusler[otoSayac-1][0] = kapasite;
    otobusler[otoSayac-1][1] = perSayi;
    otobusler[otoSayac-1][2]=otoSayac;
        
    otoSayac += 1;
    firmaGiris();
}

void musteriMenu(){
    int kod;

    printf("\n1-SEFERLERI LISTELE\n");
    printf("2-SEFER REZERVASYON YAP\n");
    printf("3-BIR UST MENUYE DON\n");
    printf("4-REZERVASYON GOSTER\n");
    scanf("%d",&kod);

    if(kod == 3){anaMenu();}

    else{
        controller(kod+30);
    }
}

void firmaGiris(){
    int kod;

    printf("\n1-OTOBUS EKLE\n");
    printf("2-SEFER BILGISI\n");
    printf("3-SEFER/KOLTUK BILGISI\n");
    printf("4-BIR UST MENUYE DON\n");
    scanf("%d",&kod);

    if(kod == 4){anaMenu();}

    else{
        controller(kod+20);
    }
    
    
}

void anaMenu(){
    int kod;

    printf("\nANA MENU\n");
    printf("1.FIRMA GIRISI\n");
    printf("2.MUSTERI GIRISI\n");
    printf("3.CIKIS\n");
    printf("Lutfen bir giris yapiniz:->");

    scanf("%d",&kod);

    if(kod == 3) kapat();
    
    controller(kod+10);
}

int main(){
   anaMenu();
    
   return 0;
}

