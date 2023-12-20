#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure d'un fournisseur
typedef struct {
int code;
char *nom,*adresse,*nationalite;

}fournisseur;

//structure d'un medicament
typedef struct{
    char *nom,*code,*categorie;
    float prix;
   unsigned int quant_stock;
    fournisseur forn;

}medicament;
//fontion d'affichage des cas possible
void affichage(int a,int N,medicament *med){
int i,somme_med_valable=0;
//
for(i=0;i<N;i++){
switch (a)
{
case 1:
//premier cas si l'utilisateur entre la valeur 1 
for(i=0;i<N;i++){
    printf("Medicament : %s =>Valable en stock:%u\n",(med+i)->nom,(med+i)->quant_stock);
somme_med_valable+=(med+i)->quant_stock;
}
printf("La somme des medicaments valable est:%d",somme_med_valable);
    break;
case 2:


break;
case 3:
char c;
printf("Entrer :\na-D'apres le fournisseur donnee\nb-D'apres ca categorie donnee\nc-D'apres le prix\n");
scanf("%c",&c);
switch (c)
{
case 'a':
char *s;
s=(char*)malloc(10*sizeof(char));
printf("Entrer le nom du fournisseur:\n");
    scanf("%s",s);
    for(i=0;i<N;i++){
        if(s==(med+i)->forn.nom){
            printf("Medicament:%s\tCode:%s\tCategorie:%s\tValable en stock:%u\tPrix:%.2f\n",(med+i)->nom,(med+i)->code,(med+i)->categorie,(med+i)->quant_stock,(med+i)->prix);
        }
    }
    free(s);
    break;
case 'b':
char *s;
s=(char*)malloc(10*sizeof(char));
    printf("Entrer la categorie:\n");
    scanf("%s",s);
     for(i=0;i<N;i++){
        if(s==(med+i)->categorie){
            printf("Medicament:%s\tCode:%s\tCategorie:%s\tValable en stock:%u\tPrix:%.2f\n",(med+i)->nom,(med+i)->code,(med+i)->categorie,(med+i)->quant_stock,(med+i)->prix);
        }
    }
    free(s);
    break;
    case 'c':
    float pr;
          printf("Entrer le prix:\n");
            scanf("%f",&pr);
     for(i=0;i<N;i++){
        if(abs(pr-(med+i)->prix) < 1e-9){
            printf("Medicament:%s\tCode:%s\tCategorie:%s\tValable en stock:%u\tPrix:%.2f\n",(med+i)->nom,(med+i)->code,(med+i)->categorie,(med+i)->quant_stock,(med+i)->prix);
        }}
    break;
default:
printf("Error");
    break;
}


break;
default:
    break;
    }
}


}
//fontion d'initialisation qui retourne la premiere adresse du tableau de type med(medicaments)
medicament* init(int n,medicament *med){
    int i;
    for(i=0;i<n;i++){
       printf("Entrer le nom et la qt");
       scanf("%s%u",(med+i)->nom,&(med+i)->quant_stock);
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












