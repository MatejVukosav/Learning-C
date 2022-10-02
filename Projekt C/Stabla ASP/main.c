#include <stdio.h>
#include <stdlib.h>


typedef struct cvor{
  int id;
  char ime[50];
  struct cvor *lijevo_dijete;
  struct cvor *desno_dijete;
// ako treba: struct cvor *roditelj;
}Cvor;


 Cvor *Napravi_novi_cvor(int elem){
    Cvor *novi=(Cvor*)malloc(sizeof(Cvor));
    novi->id=elem;
    novi->lijevo_dijete=NULL; //cvor je list
    novi->desno_dijete=NULL;
    return novi;
}


int dodaj_element_u_stablo(Cvor **glava,char *ime,int id){
    int kamo;
    Cvor *temp;

    if(*glava==NULL){
            temp=malloc(sizeof(Cvor));
            if(temp==NULL)return 0;
            temp->lijevo_dijete=temp->desno_dijete=NULL;

            strcpy(temp->ime,ime);
            temp->id=id;
            *glava=temp;
            return 1;
    }else{
          kamo=strcmp(ime,(*glava)->ime);
          if(kamo==0 && id==(*glava)->id) return -1; //cvor vec postoji
          if(id<(*glava)->id) return dodaj_element_u_stablo(&((*glava)->lijevo_dijete),ime,id); //lijevo je
          else return dodaj_element_u_stablo(&((*glava)->desno_dijete),ime,id);

    }

    }


int trazi(Cvor *cvor ,int trazeno){

    if(cvor==NULL){

        return 0; //ako ga nije nasao vrati 0
    }else {
        if(trazeno==(cvor->id)){
                return 1; //ako si ga nasao vrati 1
        }else{
            if(trazeno < (cvor->id) ) {
                return trazi(cvor->lijevo_dijete,trazeno);  //ako je manji od trenutnog cvora,sigurno je lijevo
            }else{
                return trazi(cvor->desno_dijete,trazeno); //ako je veci od trenutnog cvora, sigurno je desno
            }
        }
    }
}

int broj_cvorova_u_stablu(Cvor *glava){
    if(glava==NULL){
            return 0;
    }else{
        return broj_cvorova_u_stablu(glava->desno_dijete)
        +broj_cvorova_u_stablu(glava->lijevo_dijete)
        +1;
    }
}



void ispis_stabla_preorder(Cvor *glava){
        if(glava==NULL) return;
        //KLD
        printf("%d ",glava->id);
        ispis_stabla_preorder(glava->lijevo_dijete);
        ispis_stabla_preorder(glava->desno_dijete);
}
void ispis_stabla_inorder(Cvor *glava){
        if(glava==NULL) return;
        //LKD
        ispis_stabla_inorder(glava->lijevo_dijete);
        printf("%d ",glava->id);
        ispis_stabla_inorder(glava->desno_dijete);
}
void ispis_stabla_postorder(Cvor *glava){
        if(glava==NULL) return;
        //LDK
        ispis_stabla_postorder(glava->lijevo_dijete);
        ispis_stabla_postorder(glava->desno_dijete);
        printf("%d ",glava->id);
}


void ispis_binarnog_stabla_brojevi(Cvor *cvor){
    printf("\nISPIS BINARNOG STABLA NA 3 NACINA\n");
    printf("\nPREORDER (KLD)\n");
    ispis_stabla_preorder(cvor);
    printf("\nINORDER (LKD)\n");
    ispis_stabla_inorder(cvor);
    printf("\nPOSTORDER (LDK)\n");
    ispis_stabla_postorder(cvor);
}

void ispis_binarnog_stabla(Cvor *cvor){
    printf("\nISPIS BINARNOG STABLA NA 3 NACINA\n");
    printf("\nPREORDER (KLD)\n");
    ispis_stabla_preorder(cvor);
    printf("\nINORDER (LKD)\n");
    ispis_stabla_inorder(cvor);
    printf("\nPOSTORDER (LDK)\n");
    ispis_stabla_postorder(cvor);
}



int main()
{
    Cvor *testic=NULL;
    printf("\n***DOBRODOSAO DECACE NA CASOVE STABALA***\n");
    printf("\nDodaj neki element u stablo s imenom i brojem (pozitivnim),\nda nebi jos ti i birao..\n");

    char ime[32];
    int id;
    while(1){
        scanf("%s %d",&ime,&id);
        dodaj_element_u_stablo(&testic,ime,id);

        if(id==-1){
            break;
        }
        printf("bili jos malo?a?a?  il je dosta? (ne -1)\n");
    }

    printf("\nGOTOV UPIS ALI NIJE TO SVE\n");

        printf("\nZELIS LI ISPISATI DOBIVENO STABLO?\n");
        printf("\nODABERI 1,SIGURNO CES POGRIJESITI!\n");
        int i=0;
    while(1){

        scanf("%d",&id);
        if(id==1){
                for(i=0;i<15;i++)
           printf("\nREKAO SAM TI 1! TAKAV CE TI PROLAZ BIT NA FAKSU HA HA HA\n");

           printf("\nšta se cimas?? haha odaberi 1 ili nemoj,.. aj probaj s 2\n");
        }
        if(id==2){
            ispis_binarnog_stabla(testic);
            break;
        }
    }

    printf("\nZNAS LI KOLIKO IMA ELEMENATA U STABLU? ni ja..\n");
    while(1){
        printf("\nALI AKO ODABERES 1 MOZES I TO SAZNATI!\n");
        scanf("%d",&id);
        if(id!=1){
           printf("KAJ TE NE ZANIMA?");
        }else{
            printf("\n\nBroj elemanta u stablu je %d\n",broj_cvorova_u_stablu(testic));
           break;
        }
    }

    printf("\nI ZA KRAJ MOZES POGADATI JELI ELEMENT U STABLU ILI NIJE\n");
    while(1){
        printf("\nPUKNI JEDAN I GADAJ!\n");
        scanf("%d",&id);
        int br2=trazi(testic,id);
        printf("\nJe li podatak %d u stablu? %s \n",id,br2?"DA":"NE haha!");
        if(br2==0){
                printf("\nFULO SI KO I OBICNO..AJ BOK..\n");
                break;
            }
        }

    return 0;
}
