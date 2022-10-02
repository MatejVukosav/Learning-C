#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define C (BLOK/sizeof(zapis))  //9
#define N 10000
#define M (int)( (double)N*1.20/C) //1333
#define BLOK 512

/*
• ID klijenta – brojcana vrijednost 1000000<=9999999
• Prezime klijenta – do 20 znakova
• Ime klijenta – do 20 znakova
• Stanje na raèunu – realan broj
*/
typedef struct{
    int ID_klijenta;
	char prezime[20+1];
	char ime[20+1];
	float stanje_na_racunu;
}zapis;
zapis podaci;

typedef struct{
    zapis Pod[C];
}Ladica;
Ladica L;

int brojac=0;
 /**
    Odaberi nacin adresiranja;
	*/
int odabir=2;

/**
Adresiranje metodom preklapanja
*/
int Adresa1(int sifra){
	int i,adresa_pretinca=0;

    return adresa_pretinca;
}
/**
Adresiranje metodom dijeljenja;
*/
int Adresa2(int sifra){

	int i,prim=0,adresa_pretinca=0;

	for(i=N;i>(int)sqrt(N);i--){
        if(isPrime(i)){
            prim=i;
            break;
        }
	}
	adresa_pretinca=sifra%prim;

return adresa_pretinca%M; //jer je prevelik kljuc, a premali primarni broj
}

int Adresa3(){
	int i,adresa_pretinca=0;

    return adresa_pretinca;
}
/**
 Za odabranu vrstu adresiranja vraca lokaciju;
*/
int Adresa(zapis *podatak){
    int lokacija;
    if(odabir==1){
        lokacija= Adresa1(podatak->ID_klijenta);
        }
    else if(odabir==2){
        lokacija= Adresa2(podatak->ID_klijenta);
        }
    else{
        lokacija= Adresa3(podatak->ID_klijenta);
        }
    return lokacija;
}

/*
    Funkcija koja provjerava dali je broj primaran.
    Vraca 1 ako je, 0 ako nije.
*/
int isPrime(int n){
	int i,flag=1;
    for(i=2;i<=n/2;i++)
  		{
    		  if(n%i==0)
                {
        		  flag=0;
        		  break;
                }
  		}

  if (flag==1)
  	return 1;
     // printf("%d is a prime number.",n);
  else
     // printf("%d is not a prime number.",n);
  return 0;
    }

/**
Funkcija za dodavanje zapisa.
*/
void DodajZapis(FILE *fi,zapis *podatak){

    int i;
    int lokacija=0;
    int brojPreljeva=0;

    lokacija=Adresa(podatak);
    fseek(fi,lokacija*sizeof(Ladica),SEEK_SET);

    do{
        fread(&L,sizeof(Ladica),1,fi);
        for(i=0 ; i<C ; i++){ //idem po ladici;
             if(L.Pod[i].ID_klijenta==0){ //ako je pretinac prazan
                    L.Pod[i].ID_klijenta=podatak->ID_klijenta;
                    strcpy(L.Pod[i].ime , podatak->ime);
                    strcpy(L.Pod[i].prezime,podatak->prezime);
                    L.Pod[i].stanje_na_racunu=podatak->stanje_na_racunu;

                    fseek(fi,-1*sizeof(Ladica),SEEK_CUR);
                    fwrite(&L,sizeof(Ladica),1,fi); //upisi u izlaznu
                    return 1 ;
                    }
                }
        lokacija++;
        if(lokacija>=M){
                fseek(fi,0,SEEK_SET);
                lokacija=0;
                }
        }while(1);
}

/**
Izvlacim određenu ladicu (int hash) i ispisujem je
*/
void provjera_spremanja(FILE *fi,int hash){
    int i;
    fseek(fi,hash*sizeof(Ladica),SEEK_SET);
    fread(&L,sizeof(Ladica),1,fi);
    for(i=0 ; i<C ; i++){
        printf("Hash je: %3d, a podatak je: %7d;%s;%s;%.2f \n",hash,L.Pod[i].ID_klijenta,L.Pod[i].ime,L.Pod[i].prezime,L.Pod[i].stanje_na_racunu);
        }
}

/**
Inicijalizacija svih Ladica;
*/
void inicijalizacija_izlazne_datoteke(FILE *fi){
    int i;
    for(i=0;i<C;i++){
        L.Pod[i].ID_klijenta=0;
        strcpy(L.Pod[i].ime,"ime");
        strcpy(L.Pod[i].prezime,"prezime");
        L.Pod[i].stanje_na_racunu=0.0;
        }
    for(i=0;i<M;i++){
        fwrite(&L,sizeof(L),1,fi);
        }
}

/**
Funkcija traži ukupan broj preljeva prilikom spremanja datoteke
*/
int ukupan_broj_preljeva(FILE *fi){
    int br_preljeva=0,i,j,upisan;
    int lokacija;

    for(i=0;i<M;i++){ //odi po svim zapisima
        fseek(fi,i*sizeof(Ladica),SEEK_SET);
        fread(&L,sizeof(Ladica),1,fi); //procitaj cijelu ladicu

        for(j=0;j<C;j++){ //odi po svim pretincima
                if(L.Pod[j].ID_klijenta!=0){ //ako pretinac postoji, 10 000 puta ude unutra
                    lokacija=Adresa(&L.Pod[j].ID_klijenta); //odredi gdje bi trebao biti po adresi
                    if(lokacija!=i){ //ako nije tamo gdje je trebao biti, u lokacija treba biti,ali se nalazi u i
                    br_preljeva++;
                    }
                }
                else {
                    break; //znaci da je ostatak pretinca prazan pa ne moram gledat
                    }
        }
    }
	return br_preljeva;
}

/**
Funkcija trazi maksimalan broj zapisa koji su bili upuceni u isti pretinac. (nebitno jesu li i spremljeni tamo)
*/
int max_br_zapisa_upucenih_u_isti_pretinac(FILE *fi){
    int broj_zapisa[N]={0},i,j,max=0;

    for(i=0;i<M;i++){ //odi po svim zapisima
        fseek(fi,i*sizeof(Ladica),SEEK_SET);
        fread(&L,sizeof(Ladica),1,fi);
         for(j=0;j<C;j++){
             if(L.Pod[j].ID_klijenta!=0){
                broj_zapisa[Adresa(&L.Pod[j].ID_klijenta)]++;
                //povecaj brojac od onog pretinca u koji se podatak trebao spremit,
                //nebitno jeli se tamo spremio ili zbog preljeva nije
             }
         }
    }

    for(i=0;i<M;i++){ //nadi maksimum iz polja broj_zapisa[]
        if(broj_zapisa[i]>=max){
            max=broj_zapisa[i];
        }
    }

	return max;
}

/**
MAIN
*/
int main(void){
	FILE *fu=NULL;
	FILE *fi=NULL;

	fu=fopen("podaci.dat","rb");
            if(fu==NULL){
                printf("Otvaranje ulazne datoteke \"podaci.dat\" nije uspjelo. Prekidam.\n");
                return -1;
            }


	fi=fopen("rezultat.dat","wb+");
            if(fi==NULL){
                printf("Stvaranje izlazne datoteke \"rezultat.dat\" nije uspjelo. Prekidam.\n");
                return -2;
            }

        int i;
        inicijalizacija_izlazne_datoteke(fi);


    /** Zapisujem sve podatke u strukturu podaci[N];
    */
    char charID[100]; //jer kad citam mi spremi kao char,a meni u podaci.ID_klijenta mora bit int
   for(i=0;i<N-1;i++){
            fscanf(fu,"%[^\;];%[^\;];%[^\;];%f\n",charID,&podaci.ime,&podaci.prezime,&podaci.stanje_na_racunu);
            podaci.ID_klijenta=atoi(charID);
            /**
            Saljem sve podatke u funkciju.
            */
            DodajZapis(fi,&podaci);
   }

        //provjera_spremanja(fi,i);


    int ukupno_preljeva = ukupan_broj_preljeva(fi);
    //printf("Ukupan broj preljeva je: %d\n",ukupno_preljeva);

    int max_zapisa = max_br_zapisa_upucenih_u_isti_pretinac(fi);
    //printf("Maksimalan broj zapisa upucenih u isti pretinac je: %d\n", max_zapisa);


	fclose(fu);
	fclose(fi);
	return 0;
}
