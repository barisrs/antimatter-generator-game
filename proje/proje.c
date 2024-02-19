#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXUSER 20

//macbook'ta getch() kullanilmiyormus. bu yuzden benim kodlarim w a s d oynanma uzerine yapilmistir.
typedef struct
{
    char isim[10];
    char soyisim[10];
    char kullaniciadi[10]; //Login ve kullanici olusturulurken kullanilacak. Ayrica skor yazdirirken de skorlari okuma ve tutma isini yapacak
    char password[10];
    int puan; //Login ve kullanici olustururken kullanilmayacak sadece skor yazdirirken skorları okuma ve tutma isini yapacak.

}KULLANICI;

void skorKaydet(KULLANICI k1, int puan) {
    KULLANICI readkullanici;
    int kullanicikontrol = 0;
    FILE *skorfile = fopen("skortablosu.txt", "r+"); //okumak için skor dosyamızı actık

    if (skorfile == NULL) { //acılmıyorsa hata verdik
        perror("Dosya acilamadi");
        exit(1);
    }

    while (fscanf(skorfile, "%s %d", readkullanici.kullaniciadi, &readkullanici.puan) == 2) {
        if (strcmp(readkullanici.kullaniciadi, k1.kullaniciadi) == 0) {
            kullanicikontrol = 1;
            fseek(skorfile, -strlen(k1.kullaniciadi) - sizeof(KULLANICI), SEEK_SET);
            fprintf(skorfile, "%s %d\n", k1.kullaniciadi, puan);
            break;
        }
    }

    if (kullanicikontrol == 0) {
        fseek(skorfile, 0, SEEK_END);
        fprintf(skorfile, "%s %d\n", k1.kullaniciadi, puan);
    }

    fclose(skorfile);   //isimiz bitince dosyayi kapatiyoruz
}
void manuelOyna(char **array,int line,int count,KULLANICI k1){    //manuel oyna fonksiyonu için dizi satir sutun ve kullanici parametresi alinir
    int i,j,Xi,Xj,parcaciksayisi=0,geriKontrol=0,cikiskontrol=0,karadelikkontrol=0,surekontrol=0,countE=0,counte=0,countp=0,countP=0,countkarsitparcacik;
    int seconds=100,puan; //oyun suresi 100 saniye olarak tanimlanir
    char toplananParcaciklar[line*count],hareket; //toplanan parcaciklar icin bir dizi atanir ve hareket alinir.
    for ( i = 0; i < line; i++)
    {
        for (j = 0; j < count; j++)
        {
            if(array[i][j]=='X'){
                Xi=i;
                Xj=j;
            }
        }
        
    }
    printf("\n\nOYUN BASLADI.\nHareket etmek icin W A S D\n");
    while(cikiskontrol!=1&&karadelikkontrol!=1&&surekontrol!=1){ //eger cikiskontrol(cikis bulunduysa 1 dondurur) 1 değil ise ve karadeliğe girmediysek ve süre bitmediyse her seferinde tekrar hareket istenir.
        time_t start=time(NULL);
        char parcacikkontrol;
        printf("\n\n");
        for(i=0;i<line;i++){   //her seferinde array yazdirilir
            for (j = 0; j < count; j++)
            {
                printf("%c  ",array[i][j]); 
            }
            printf("\n\n");
        }
        printf("\nHareketiniz: "); //kullanicidan hareket al
        scanf(" %c",&hareket);
        printf("\n");

        if(hareket=='W'||hareket=='w'){
            if(Xi!=0&&array[Xi-1][Xj]!='1'){ //eger satir 0 degilse ve istenilen yönde 1 yoksa hareket saglanmasi icin Xi 1 azaltılır.
                Xi--;
                if(array[Xi][Xj]=='C') //istenilen yonde cikşs varsa cikiskontrol 1 yapılır
                    cikiskontrol=1;
                if(array[Xi][Xj]=='K') //İstenilen yonde karadelik varsa karadelikkontrol 1 yapilir
                    karadelikkontrol=1;
                parcacikkontrol=array[Xi][Xj]; //onun disinda gidilen yönde olan char parcacikkontrole aktarılır.
                array[Xi][Xj]='X';  //xin yeni yeri konulur altta ise Xin eski yerine 0 atanır.
                array[Xi+1][Xj]='0';
                if(geriKontrol==0){ //ilk basta X'in harekete gectigi yere G atanır
                    array[Xi+1][Xj]='G';
                    geriKontrol=1;
                }
            }

        }
        else if(hareket=='A'||hareket=='a'){ //diger yönler icin de tekrarlanir
            if(array[Xi][Xj-1]!='1'&& Xj!=0){
                Xj--;
                if(array[Xi][Xj]=='C')
                    cikiskontrol=1;
                if(array[Xi][Xj]=='K')
                    karadelikkontrol=1;
                parcacikkontrol=array[Xi][Xj];
                array[Xi][Xj]='X';
                array[Xi][Xj+1]='0';
                if(geriKontrol==0){
                    array[Xi][Xj+1]='G';
                    geriKontrol=1;
                }
            }
        }
        else if(hareket=='S'||hareket=='s'){
            if( Xi!=line-1&&array[Xi+1][Xj]!='1'){
                Xi++;
                if(array[Xi][Xj]=='C')
                    cikiskontrol=1;
                if(array[Xi][Xj]=='K')
                    karadelikkontrol=1;
                parcacikkontrol=array[Xi][Xj];
                array[Xi][Xj]='X';
                array[Xi-1][Xj]='0';
                if(geriKontrol==0){
                    array[Xi-1][Xj]='G';
                    geriKontrol=1;
                }
            }
        }
        else if(hareket=='D'||hareket=='d'){
            if(array[Xi][Xj+1]!='1'&& Xj!=count-1){
                Xj++;
                if(array[Xi][Xj]=='C')
                    cikiskontrol=1;
                if(array[Xi][Xj]=='K')
                    karadelikkontrol=1;
                parcacikkontrol=array[Xi][Xj];
                array[Xi][Xj]='X';
                array[Xi][Xj-1]='0';
                if(geriKontrol==0){
                    array[Xi][Xj-1]='G';
                    geriKontrol=1;
                }
            }

        }

        if(parcacikkontrol=='p'||parcacikkontrol=='e'||parcacikkontrol=='P'||parcacikkontrol=='E'){ //parcacikkontrol bu harflerden biriyse istenen diziye aktarilsin
            toplananParcaciklar[parcaciksayisi]=parcacikkontrol;
            parcaciksayisi++;
        }
        time_t end = time(NULL);
        seconds=seconds-difftime(end,start); //sure saydirmak icin fonksiyon
        if(seconds>0)
            printf("Kalan sureniz: %d\n",seconds); //her seferinde sure ne kadar kaldi yazilir
        if (seconds<=0)
            surekontrol=1;
        if(karadelikkontrol!=1&&surekontrol!=1)  //sure bitmediyse ve karadelige girilmediyse toplanan parcacikalr yazdirilir.
        {
            printf("Toplanan parcaciklar: ",parcaciksayisi);
            for ( i = 0; i < parcaciksayisi; i++){
                printf("%c ",toplananParcaciklar[i]); 
            }
        }
        printf("\n\n");
        parcacikkontrol='0';
        
    }
    if(cikiskontrol==1){ //cikis basariliysa toplanan parcaciklar yazdirilir ve p E sayilari hesaplanir ona göre karşıt madde sayısı hesaplanır
        printf("\nCikis basarili.\n");
        printf("Toplanan parcaciklar:");
        for ( i = 0; i < parcaciksayisi; i++)
        {
            printf(" %c",toplananParcaciklar[i]);
            if(toplananParcaciklar[i]=='e')
                counte++;
            else if(toplananParcaciklar[i]=='E')
                countE++;
            else if(toplananParcaciklar[i]=='p')
                countp++;
            else 
                countP++;
        }
            if((countp-countP)<(countE-counte))
                countkarsitparcacik=countp-countP;
            else
                countkarsitparcacik=countE-counte;
            if(countkarsitparcacik<0)
                countkarsitparcacik=0;
            printf("\nOlusturulan karsit parcacik sayisi: %d\n",countkarsitparcacik);
            puan=line*count*seconds*(countkarsitparcacik+1);
            printf("Puaniniz: %d",puan/100); //puan hesaplanır
    }
    if(karadelikkontrol==1){  //oyunu bitiremediyse hata ve puan=0
        printf("Oyun basarisiz! Kara delige girdiniz!");
        puan=0;
        printf("Puaniniz: %d",puan);
    }
    if(surekontrol==1){
        printf("Oyun basarisiz! Sureniz doldu!");
        puan=0;
        printf("Puaniniz: %d",puan);
    }
    skorKaydet(k1,puan/100);



}

void oyunSekli(char **array,int line, int count,KULLANICI k1){  //parametreler ile birlikte kullanıcıdan oyunu nasıl oynamak istedigi secilir
        manuelOyna(array,line,count,k1);
}

int haritaSec(KULLANICI k1){  //kendi haritasını mı kullanmak istiyor yoksa varolan haritalardan mı sececek sorulur
    int secim,count=0,line=1,i,j;
    char c,yenisecim[20];
    printf("\nKendi haritanizi kullanmak icin 1, varolan haritalardan secmek icin 2yi seciniz.\nSeciminiz: ");
    scanf("%d",&secim);
    if(secim==1)
        printf("\nKendi haritanizin ismini .txt halinde giriniz.\n");
    else if(secim==2)
        printf("\nIstediginiz haritanin ismini .txt halinde giriniz.\n1-harita1.txt\n2-harita2.txt\n3-harita3.txt\nSeciminz.: ");
    scanf("%s",yenisecim);
    FILE *file=fopen(yenisecim,"r");
    while((c=fgetc(file))!='\n'){
        count++;
    }
    rewind(file);
    do
    {
        c=fgetc(file);
        if(c=='\n')
        line++;
        
    } 
    while (c!=EOF);
    rewind(file);
    
    char **array=(char**)malloc(sizeof(char*)*line);

    for (i = 0; i < line; i++)
    {
        array[i]=(char*)malloc(sizeof(char)*count);
    }
      for (int i = 0; i < line; i++) {
        j = 0;
        while ((c = fgetc(file)) != '\n' && c != EOF) {
            array[i][j++] = c;
        }
        array[i][j] = '\0'; 
    }
    oyunSekli(array,line,count,k1);
    
}

void kullaniciGir(){ //kullanici login mi olustur mu sectirilir.
    int secim;
    int kullanicikontrol=0;
    KULLANICI k1;
    KULLANICI readkullanici;
    printf("\n1-login 2-olustur\nSeciminiz: ");
    scanf("%d",&secim);
    if(secim==1){
        kullanicikontrol=0;
        printf("KULLANICI GIRISI YAPILIYOR.\nKULLANICI ADINIZI GIRIN:");
        scanf("%s",k1.kullaniciadi);
        printf("\nSIFRENIZI GIRIN:");
        scanf("%s",k1.password);
        FILE *file = fopen("userdatas.bin", "rb+"); //userdatas.bin'e  kullanıcı bilgileri aktarılır.
        if (file == NULL) {
                printf("Dosya olusturma hatasi");
                exit(1);
            }
        while (fread(&readkullanici, sizeof(KULLANICI), 1, file) == 1) {
            if (strcmp(readkullanici.kullaniciadi, k1.kullaniciadi) == 0&&strcmp(readkullanici.password,k1.password)==0) { //eger böyle bir kullancı varsa login basarılı der
                fclose(file);
                kullanicikontrol = 1;
                break;
            }
        }
        if(kullanicikontrol==0){
            printf("GIRIS BASARISIZ. Lutfen tekrar giris yapin veya yeni kullanici olusturun");
            kullaniciGir();
        }     
        else if(kullanicikontrol==1){
            printf("\nGIRIS BASARILI!");
        }
    }
    else if(secim==2){
        kullanicikontrol=1;
        while(kullanicikontrol==1){
            printf("\nYENI KULLANICI OLUSTURULUYOR.\nIsminizi girin: "); //boyle bir kullanıcı yoksa olustur metoduyla bilgiler alınır.
            scanf("%s", k1.isim);
            printf("\nSoyisminizi girin: ");
            scanf("%s", k1.soyisim);
            printf("\nKullanici adi girin: ");
            scanf("%s", k1.kullaniciadi);
            printf("\nSifre girin: ");
            scanf("%s", k1.password);
            FILE *file = fopen("userdatas.bin", "ab+");
            if (file == NULL) {
                printf("Dosya olusturma hatasi");
                exit(1);
            }
            rewind(file);
            kullanicikontrol=0;
            while (fread(&readkullanici, sizeof(KULLANICI), 1, file) == 1) {
                if (strcmp(readkullanici.kullaniciadi, k1.kullaniciadi) == 0) {
                    fclose(file);
                    kullanicikontrol = 1;
                    break;
                }
                else{
                    kullanicikontrol=0;
                }
            }
            if (kullanicikontrol == 0) {
                fseek(file, 0, SEEK_END);  
                fwrite(&k1, sizeof(KULLANICI), 1, file);
                fclose(file);
                printf("\nOlusturma basarili\n");
            } 
            else if(kullanicikontrol==1){
                printf("Boyle bir kullanici var. Olusturma basarisiz.\n");
            }
        }
    }
    haritaSec(k1);
}

char anaMenu(){
    int secim,puan,temppuan; 
    char isim[10];
    printf("\n\n1-Oyuncu Skorlari\n2-Nasil oynanir\n3-Oyuna basla\nSeciminiz: "); //ana menu yazılır kullanıcının ne yapmak istedigi ondan alınır
    scanf("%d",&secim);
    if(secim==1){
        int kullanicisayisi=0;
        int puanlar[MAXUSER]; //En fazla 20 kisinin puanini tutar.
        KULLANICI kullanicilar[MAXUSER]; //En fazla 20 kisinin kullanici adini tutar.
        KULLANICI tempuser;
         FILE *file = fopen("skortablosu.txt", "r+"); 
    if (file == NULL) {
        perror("Dosya acilamadi");
        exit(1);
    }
    while(fscanf(file,"%s %d",kullanicilar[kullanicisayisi].kullaniciadi,&kullanicilar[kullanicisayisi].puan)==2){
        puanlar[kullanicisayisi]=kullanicilar[kullanicisayisi].puan;
        kullanicisayisi++;
        if(kullanicisayisi>=MAXUSER){
            printf("Maksimum kullanici sayisi"); //maks sayıya ulasıldı hatası verilir.
            break;
        }
    }
    fclose(file);
    for (int i = 0; i < kullanicisayisi - 1; i++) {
        for (int j = 0; j < kullanicisayisi - i - 1; j++) {
            if (puanlar[j] < puanlar[j + 1]) {
                temppuan = puanlar[j];
                puanlar[j] = puanlar[j + 1];
                puanlar[j + 1] = temppuan;
                tempuser = kullanicilar[j];
                kullanicilar[j] = kullanicilar[j + 1];
                kullanicilar[j + 1] = tempuser;
            }
        }
    }
    printf("En yuksek 5 puan:\n");
    for (int i = 0; i < (kullanicisayisi < 5 ? kullanicisayisi : 5); i++) {
        printf("Kullanici Adi: %s Puan: %d\n", kullanicilar[i].kullaniciadi, kullanicilar[i].puan);
    }
    anaMenu();
    }
    else if(secim==2){
        printf("\nOyunumuz,oyun haritanizi secmenizle baslar. Ya kendi haritanizi kullanabilir, ya da hali hazirda bulunan haritalari kullanarak oyunu oynayabilirsiniz. X, sizin bulunduğunuz yerdir. W A S D tuşları ile hareket edebilirsiniz. \nAmaciniz daha cok p ve E toplayarak karsit madde uretmek. Topladiginiz P'ler p'leri; e'ler ise E'leri yok eder.\n1'ler duvardır ve buralardan hareket edemezsiniz. Yollar 0 ile gösterilir ve buradan ilerleyebilirsiniz. \nK'ye denk gelmemeye ozen gosterin cunku bunlar karadeliktir ve sizi yutarlar! Amaciniz en kisa sure icinde C'ye yani cikisa ulasmaktir. \nSakin unutmayin sureniz kisitli! 100 saniye icinde cikisa ulasamazsaniz oyun biter.");
        anaMenu();
    }
    else{
        kullaniciGir();
    }
}

int main(){
    srand(time(NULL));
    anaMenu();



    return 0;
}