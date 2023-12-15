#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure d'un fournisseur
typedef struct {
int code;
char *nom,*adresse,*nationalite;

}fournissuer;

//structure d'un medicament
typedef struct{
    char *nom,*code,*categorie;
    float prix;
   unsigned int quant_stock;
    fournissuer forn;

}medicament;

void affichage(int a,int N,medicament *med){
int i;
for(i=0;i<N;i++){

printf("Le Nom du Medicament est %s ,Valable:%u",(med+i)->nom,(med+i)->quant_stock);

}
medicament* init(int N;medicament *med){
    int i;
    for(i=0;i<N;i++){
       printf("Entrer le nom et la qt");
       scanf("%s%u",(med+i)->nom,&(med+i)->quant_stock);
    }
}
return med;

}


int main(){
  int N,i; 
   printf("Entrer le nombre des medicaments:\n");
    scanf("%d",&N);
printf("Menu De Gestion\n");

medicament *t;
//allocation dynamique
t=(medicament*)malloc(N*sizeof(medicament));
for(i=0;i<N;i++){
(t+i)->nom=(char*)malloc(10*sizeof(char));
(t+i)->code=(char*)malloc(10*sizeof(char));
(t+i)->categorie=(char*)malloc(10*sizeof(char));
(t+i)->forn.nom=(char*)malloc(10*sizeof(char));
(t+i)->forn.adresse=(char*)malloc(30*sizeof(char));
(t+i)->forn.nationalite=(char*)malloc(10*sizeof(char));
}
t=init(N,t);
affichage(1,N,t);


    return 0;
}












