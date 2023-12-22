#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure d'un fournisseur
typedef struct {
int code;
char nom[10],adresse[30],nationalite[10];

}fournisseur;

//structure d'un medicament
typedef struct{
    char nom[10],code[10],categorie[10];
    float prix;
   unsigned int quant_stock;
    fournisseur forn;

}medicament;
void init(int n,medicament *med);
void affichage(int a,int *N,medicament *med);

//fontion d'affichage des cas possible
void affichage(int a,int *N,medicament *med){
int i,j;
char c;
char *s;
medicament temp;
s=(char*)malloc(10*sizeof(char));
switch (a)
{
case 1:
//premier cas si l'utilisateur entre la valeur 1
 int somme_med_valable=0;
for(i=0;i<*N;i++){
    printf("Medicament : %s =>Valable en stock:%u\n",(med+i)->nom,(med+i)->quant_stock);
somme_med_valable+=(med+i)->quant_stock;
}
printf("La somme des medicaments valable est:%d",somme_med_valable);
    break;
case 2:
//2eme cas si l'utilisateur entre le nombre 2

break;
case 3:
//3eme cas si l'utilisateur entre le nombre 3
printf("Entrer :\na-D'apres le fournisseur donnee\nb-D'apres ca categorie donnee\nc-D'apres le prix\n");
scanf("%c",&c);
switch (c)
{
case 'a':
//cas d'affichage de tous lesmedicaments d'apres un fournisseur
printf("Entrer le nom du fournisseur:\n");
    scanf("%s",s);
    for(i=0;i<*N;i++){
        if(s==(med+i)->forn.nom){
            printf("Medicament:%s\tCode:%s\tCategorie:%s\tValable en stock:%u\tPrix:%.2f\n",(med+i)->nom,(med+i)->code,(med+i)->categorie,(med+i)->quant_stock,(med+i)->prix);
        }
    }
    free(s);
    break;
case 'b':
//cas d'affichage de tous lesmedicaments d'apres la categorie
    printf("Entrer la categorie:\n");
    scanf("%s",s);
     for(i=0;i<*N;i++){
        if(s==(med+i)->categorie){
            printf("Medicament:%s\tCode:%s\tCategorie:%s\tValable en stock:%u\tPrix:%.2f\n",(med+i)->nom,(med+i)->code,(med+i)->categorie,(med+i)->quant_stock,(med+i)->prix);
        }
    }
    free(s);
    break;
    case 'c':
    //cas d'affichage de tous lesmedicaments d'apres le prix
    float pr;
          printf("Entrer le prix:\n");
            scanf("%f",&pr);
     for(i=0;i<*N;i++){
        if(abs(pr-(med+i)->prix) < 1e-9){
            printf("Medicament:%s\tCode:%s\tCategorie:%s\tValable en stock:%u\tPrix:%.2f\n",(med+i)->nom,(med+i)->code,(med+i)->categorie,(med+i)->quant_stock,(med+i)->prix);
        }}
    break;
default:
printf("Error");
    break;
}
break;
case 4:
//4eme cas d'ajout d'un medicament
medicament med1;
init(1,&med1);
printf("Entrer :\na-Au debut du tableau\nb-A la fin du tableau\nc-En une position a votre choix\nd-Apres le 2eme medicament de meme categorie\n");
scanf("%c",&c);
switch (c)
{
case 'a':
med=(medicament*)realloc(med,(*N+1)*sizeof(int));
for(i=*N;i>0;i--){
*(med+i)=*(med+i-1);
}
*med=med1;
*N=(*N)+1;
    break;
    case 'b':
med=(medicament*)realloc(med,(*N+1)*sizeof(int));
*(med+*N)=med1;
*N=(*N)+1;
    break;
    case 'c':
printf("Veuiller donner la position ou vous voulez ajouter votre nouveau medicament:\n");
scanf("%d",&j);
med=(medicament*)realloc(med,(*N+1)*sizeof(int));
for(i=*N;i>j;i++){
*(med+i)=*(med+i-1);
}
*(med+j)=med1;
*N=(*N)+1;
    break;
    case 'd':
    char cat[10];
    printf("Veuiller Entrer La Categorie:");
    scanf("%s",cat);
    med=(medicament*)realloc(med,(*N+1)*sizeof(int));
    for(i=0;i<*N;i++){
if(strcmp(cat,(med+i)->categorie)==0){
    j++;
}
if(j==2){
    break;
}
    }
    j=i+1;
    for(i=*N;i>j;i++){
*(med+i)=*(med+i-1);
    }
    *(med+j)=med1;
*N=(*N)+1;;
    break;
default:
printf("Error");
    break;
}
break;
case 5:
//5eme cas de supression d'un medicament
printf("Entrer :\na-Au debut du tableau\nb-A la fin du tableau\nc-En une position a votre choix\nd-Par Nom Du Medicament\ne-Par fournisseur\nf-Dont nom du fournisseur termine par une lettre donne:\n");
scanf("%c",&c);
switch (c)
{
case 'a':
temp=*(med+*N);
*(med+*N)=*med;
*med=temp;
med=(medicament*)realloc(med,(*N-1)*sizeof(medicament));
    break;
    *N=(*N)-1;
case 'b':
med=(medicament*)realloc(med,(*N-1)*sizeof(medicament));
*N=(*N)-1;
break;
case 'c':
printf("Entrer votre position:\n");
scanf("%d",&j);
temp=*(med+*N);
*(med+*N)=*(med+j);
*(med+j)=temp;
med=(medicament*)realloc(med,(*N-1)*sizeof(medicament));
*N=(*N)-1;
break;
case 'd':
printf("Entrer le nom du medicament:");
scanf("%s",s);
for(i=0;i<*N;i++){
    if(strcmp((med+i)->nom,s)==0){
        j=i;
        break;
    }
}
temp=*(med+*N);
*(med+*N)=*(med+j);
*(med+j)=temp;
med=(medicament*)realloc(med,(*N-1)*sizeof(medicament));
*N=(*N)-1;
break;
case 'e':

break;
default:
    break;
}
break;
default:
    break;
    }



}
//fontion d'initialisation
void init(int n,medicament *med){
    int i;
    for(i=0;i<n;i++){
       printf("Entrer Le Nom,La Categorie,Le prix,La Quantite en stock,Le Nom du fournisseur et son adresse et la nationalite\n");
       scanf("%s%s%f%u%s%s%s",(med+i)->nom,(med+i)->categorie,(med+i)->prix,&(med+i)->quant_stock,(med+i)->forn.nom,(med+i)->forn.adresse,(med+i)->forn.nationalite);
    }
}


int main(){
  int N,i; 
   printf("Entrer le nombre des medicaments:\n");
    scanf("%d",&N);
printf("Menu De Gestion\n");

medicament *t;
t=(medicament*)malloc(N*sizeof(medicament));
init(N,t);
affichage(1,&N,t);


    return 0;
}
