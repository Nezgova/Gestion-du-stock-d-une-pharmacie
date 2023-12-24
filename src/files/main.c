#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

int N;
// qsort(t, N, sizeof(medicament), (int (*)(const void *, const void *))strcmp);

// structure d'un fournisseur
typedef struct
{
    int code;
    char nom[10], adresse[30], nationalite[10];

} fournisseur;

// structure d'un medicament
typedef struct
{
    char nom[10], code[10], categorie[10];
    float prix;
    unsigned int quant_stock;
    fournisseur forn;

} medicament;
void upper_everything(char *s);
void init(int n, medicament *med);
void affichage(int choix, medicament *med);
void code_unique(char *s);

void affiche_min_categ(int N, medicament *med)
{
    char Categ[10];
    unsigned int min = UINT_MAX;

    for (int i = 0; i < N; i++)
    {
        unsigned int total = 0;
        for (int j = 0; j < N; j++)
        {
            if (strcmp((med + i)->categorie, (med + j)->categorie) == 0)
            {
                total += (med + j)->quant_stock;
            }
        }

        if (total < min)
        {
            min = total;
            strcpy(Categ, (med + i)->categorie);
        }
    }

    printf("Medicaments de la categorie avec la moins de medicament:\n");

    for (int i = 0; i < N; i++)
    {
        if (strcmp((med + i)->categorie, Categ) == 0)
        {
            printf("Medicament %d:\n", i + 1);
            printf("Code: %s\n", (med + i)->code);
            printf("Nom: %s\n", (med + i)->nom);
            printf("Categorie: %s\n", (med + i)->categorie);
            printf("Prix: %.2f\n", (med + i)->prix);
            printf("Quantite en stock: %u\n", (med + i)->quant_stock);
            printf("Fournisseur:\n");
            printf("\tCode Four: %d\n", (med + i)->forn.code);
            printf("\tNom: %s\n", (med + i)->forn.nom);
            printf("\tAdresse: %s\n", (med + i)->forn.adresse);
            printf("\tNationalite: %s\n", (med + i)->forn.nationalite);
            printf("--------------------\n");
        }
    }
}

// fontion d'affichage des cas possible
void affichage(int choix, medicament *med)
{
    int i, j = 0;
    char c;
    char *s;
    medicament temp;
    s = (char *)malloc(10 * sizeof(char));
    switch (choix)
    {
    case 1:
        // premier cas si l'utilisateur entre la valeur 1
        int somme_med_valable = 0;
        printf("Stock details:\n");
        for (int i = 0; i < N; i++)
        {
            printf("Medicament %d:\n", i + 1);
            printf("Code: %s\n", (med + i)->code);
            printf("Nom: %s\n", (med + i)->nom);
            printf("Categorie: %s\n", (med + i)->categorie);
            printf("Prix: %.2f\n", (med + i)->prix);
            printf("Quantite en stock: %u\n", (med + i)->quant_stock);
            printf("Fournisseur:\n");
            printf("\tCode Four: %d\n", (med + i)->forn.code);
            printf("\tNom: %s\n", (med + i)->forn.nom);
            printf("\tAdresse: %s\n", (med + i)->forn.adresse);
            printf("\tNationalite: %s\n", (med + i)->forn.nationalite);
            printf("--------------------\n");
            somme_med_valable += (med + i)->quant_stock;
        }
        printf("La somme des medicaments valable est:%d\n", somme_med_valable);
        break;
    case 2:
        // 2eme cas si l'utilisateur entre le nombre 2
        affiche_min_categ(N, med);
        break;
    case 3:
        // 3eme cas si l'utilisateur entre le nombre 3
        printf("Entrer :\na-D'apres le fournisseur donnee\nb-D'apres ca categorie donnee\nc-D'apres le prix\n");
        rewind(stdin);
        bool found = false;
        scanf("%c", &c);
        rewind(stdin);
        switch (c)
        {
        case 'a':
            // cas d'affichage de tous lesmedicaments d'apres un fournisseur
            printf("Entrer le nom du fournisseur:\n");
            scanf("%s", s);
            rewind(stdin);
            upper_everything(s);

            for (i = 0; i < N; i++)
            {
                if (strcmp(s, (med + i)->forn.nom) == 0)
                {
                    found = true;
                    printf("Medicament %d:\n", i + 1);
                    printf("Code: %s\n", (med + i)->code);
                    printf("Nom: %s\n", (med + i)->nom);
                    printf("Categorie: %s\n", (med + i)->categorie);
                    printf("Prix: %.2f\n", (med + i)->prix);
                    printf("Quantite en stock: %u\n", (med + i)->quant_stock);
                    printf("Fournisseur:\n");
                    printf("\tCode Four: %d\n", (med + i)->forn.code);
                    printf("\tNom: %s\n", (med + i)->forn.nom);
                    printf("\tAdresse: %s\n", (med + i)->forn.adresse);
                    printf("\tNationalite: %s\n", (med + i)->forn.nationalite);
                    printf("--------------------\n");
                }
            }
            if (!found)
            {
                printf("Not found:\n");
            }

            break;
        case 'b':
            // cas d'affichage de tous les medicaments d'apres la categorie
            printf("Entrer la categorie:\n");
            rewind(stdin);
            scanf("%s", s);
            rewind(stdin);

            for (i = 0; i < N; i++)
            {
                if (strcmp(s, (med + i)->categorie) == 0)
                {
                    found = true;
                    printf("Medicament %d:\n", i + 1);
                    printf("Code: %s\n", (med + i)->code);
                    printf("Nom: %s\n", (med + i)->nom);
                    printf("Categorie: %s\n", (med + i)->categorie);
                    printf("Prix: %.2f\n", (med + i)->prix);
                    printf("Quantite en stock: %u\n", (med + i)->quant_stock);
                    printf("Fournisseur:\n");
                    printf("\tCode Four: %d\n", (med + i)->forn.code);
                    printf("\tNom: %s\n", (med + i)->forn.nom);
                    printf("\tAdresse: %s\n", (med + i)->forn.adresse);
                    printf("\tNationalite: %s\n", (med + i)->forn.nationalite);
                    printf("--------------------\n");
                }
            }
            if (!found)
            {
                printf("Not found:\n");
            }

            break;
        case 'c':
            // cas d'affichage de tous lesmedicaments d'apres le prix
            float pr;
            printf("Entrer le prix:\n");
            rewind(stdin);
            scanf("%f", &pr);
            rewind(stdin);
            for (i = 0; i < N; i++)
            {
                if (abs(pr - (med + i)->prix) < 1e-9)
                {
                    found = true;
                    printf("Medicament %d:\n", i + 1);
                    printf("Code: %s\n", (med + i)->code);
                    printf("Nom: %s\n", (med + i)->nom);
                    printf("Categorie: %s\n", (med + i)->categorie);
                    printf("Prix: %.2f\n", (med + i)->prix);
                    printf("Quantite en stock: %u\n", (med + i)->quant_stock);
                    printf("Fournisseur:\n");
                    printf("\tCode Four: %d\n", (med + i)->forn.code);
                    printf("\tNom: %s\n", (med + i)->forn.nom);
                    printf("\tAdresse: %s\n", (med + i)->forn.adresse);
                    printf("\tNationalite: %s\n", (med + i)->forn.nationalite);
                    printf("--------------------\n");
                }
            }
            if (!found)
            {
                printf("Not found:\n");
            }
            break;
        default:
            printf("Erreur Choix INVALIDE\n");
            break;
        }
        break;
    case 4:
        // 4eme cas d'ajout d'un medicament
        medicament med1;
        printf("Entrer :\na-Au debut du tableau\nb-A la fin du tableau\nc-En une position a votre choix\nd-Apres le 2eme medicament de meme categorie\n");
        rewind(stdin);
        scanf(" %c", &c);
        rewind(stdin);
        init(1, &med1);
        switch (c)
        {
        case 'a':
            med = (medicament *)realloc(med, (N + 1) * sizeof(medicament));
            for (i = N; i > 0; i--)
            {
                *(med + i) = *(med + i - 1);
            }
            *med = med1;
            (N)++;
            for (int i = 0; i < N; i++)
            {
                printf("Medicament %d:\n", i + 1);
                printf("Code: %s\n", (med + i)->code);
                printf("Nom: %s\n", (med + i)->nom);
                printf("Categorie: %s\n", (med + i)->categorie);
                printf("Prix: %.2f\n", (med + i)->prix);
                printf("Quantite en stock: %u\n", (med + i)->quant_stock);
                printf("Fournisseur:\n");
                printf("\tCode Four: %d\n", (med + i)->forn.code);
                printf("\tNom: %s\n", (med + i)->forn.nom);
                printf("\tAdresse: %s\n", (med + i)->forn.adresse);
                printf("\tNationalite: %s\n", (med + i)->forn.nationalite);
                printf("--------------------\n");
                somme_med_valable += (med + i)->quant_stock;
            }

            break;
        case 'b':
            med = (medicament *)realloc(med, (N + 1) * sizeof(medicament));
            *(med + N) = med1;
            (N)++;
            break;
        case 'c':
            printf("Veuiller donner la position ou vous voulez ajouter votre nouveau medicament:\n");
            scanf("%d", &j);
            med = (medicament *)realloc(med, (N + 1) * sizeof(medicament));
            for (i = N; i > j; i--)
            {
                *(med + i) = *(med + i - 1);
            }
            *(med + j) = med1;
            (N)++;
            break;
        case 'd':
            char cat[10];
            printf("Veuiller Entrer La Categorie:");
            rewind(stdin);
            scanf("%s", cat);
            rewind(stdin);
            med = (medicament *)realloc(med, (N + 1) * sizeof(medicament));
            for (i = 0; i < N; i++)
            {
                if (strcmp(cat, (med + i)->categorie) == 0)
                {
                    j++;
                }
                if (j == 2)
                {
                    break;
                }
            }
            j = i + 1;
            for (i = N; i > j; i++)
            {
                *(med + i) = *(med + i - 1);
            }
            *(med + j) = med1;
            (N)++;
            break;
        default:
            printf("Erreur Choix INVALIDE\n");
            break;
        }
        break;
    case 5:
        // 5eme cas de supression d'un medicament
        printf("Entrer :\na-Au debut du tableau\nb-A la fin du tableau\nc-En une position a votre choix\nd-Par Nom Du Medicament\ne-Par fournisseur\nf-Dont nom du fournisseur termine par une lettre donne:\n");
        rewind(stdin);
        scanf("%c", &c);
        rewind(stdin);
        switch (c)
        {
        case 'a':
            temp = *(med + N);
            *(med + N) = *med;
            *med = temp;
            med = (medicament *)realloc(med, (N - 1) * sizeof(medicament));
            (N)--;
            break;
        case 'b':
            med = (medicament *)realloc(med, (N - 1) * sizeof(medicament));
            (N)--;
            break;
        case 'c':
            printf("Entrer votre position:\n");
            scanf("%d", &j);
            temp = *(med + N);
            *(med + N) = *(med + j);
            *(med + j) = temp;
            med = (medicament *)realloc(med, (N - 1) * sizeof(medicament));
            (N)--;
            break;
        case 'd':
            printf("Entrer le nom du medicament:");
            scanf("%s", s);
            for (i = 0; i < N; i++)
            {
                if (strcmp((med + i)->nom, s) == 0)
                {
                    j = i;
                    break;
                }
            }
            temp = *(med + N);
            *(med + N) = *(med + j);
            *(med + j) = temp;
            med = (medicament *)realloc(med, (N - 1) * sizeof(medicament));
            (N)--;
            break;
        case 'e':
            printf("Entrer le code du fournisseur:\n");
            scanf("%d", j);
            for (i = 0; i < N; i++)
            {
                if (j == (med + i)->forn.code)
                {
                    j = i;
                    break;
                }
            }
            temp = *(med + N);
            *(med + N) = *(med + j);
            *(med + j) = temp;
            med = (medicament *)realloc(med, (N - 1) * sizeof(medicament));
            (N)--;
            break;
        case 'f':
            printf("Entrer la lettre souhaiter:\n");
            scanf("%c", &c);
            i = 0;
            while (i < N)
            {
                if (c == (med + i)->forn.nom[strlen((med + i)->forn.nom) - 1])
                {
                    j = i;
                    temp = *(med + N);
                    *(med + N) = *(med + j);
                    *(med + j) = temp;
                    med = (medicament *)realloc(med, (N - 1) * sizeof(medicament));
                    (N)--;
                    i = 0;
                }
                i++;
            }
            break;
        default:
            printf("Erreur Choix INVALIDE\n\n");
            break;
        }
        break;
    case 6:
        break;
    default:
        printf("Erreur Choix INVALIDE\n");
        break;
    }
    free(s);
}

void upper_everything(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        *(s + i) = toupper(*(s + i));
    }
}

bool is_code_unique(char *s, medicament *med, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (strcmp(s, (med + i)->code) == 0)
        {
            return false;
        }
    }

    return true;
}

// generateur du code unique
void code_unique(char *s)
{
    int i, r;
    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (i = 0; i < 9; i++)
    {
        r = rand() % (sizeof(alphanum) - 1);
        *(s + i) = *(alphanum + r);
    }
    *(s + 9) = '\0';
}
// fontion d'initialisation
void init(int N, medicament *med)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("Le Nom du Medicament : ");
        rewind(stdin);
        scanf("%s", (med + i)->nom);
        printf("\t categorie: ");
        rewind(stdin);
        scanf("%s", (med + i)->categorie);
        printf("\t le prix: ");
        rewind(stdin);
        scanf("%f", &(med + i)->prix);
        printf("\t la quantite: ");
        rewind(stdin);
        scanf("%u", &(med + i)->quant_stock);
        rewind(stdin);
        printf("\t Nom fournisseur: ");
        rewind(stdin);
        scanf("%s", (med + i)->forn.nom);
        printf("\t Adresse du fournisseur: ");
        rewind(stdin);
        scanf("%s", (med + i)->forn.adresse);
        printf("\t Nationalite: ");
        rewind(stdin);
        scanf("%s", (med + i)->forn.nationalite);
        rewind(stdin);
        upper_everything((med + i)->nom);
        upper_everything((med + i)->categorie);
        upper_everything((med + i)->forn.nom);
        do
        {
            code_unique((med + i)->code);
        } while (!is_code_unique((med + i)->code, med, i));

        (med + i)->forn.code = rand() % RAND_MAX;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if ((strcmp((med + i)->nom, (med + j)->nom)) == 0)
            {
                strcpy((med + j)->code, (med + i)->code);
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    int choix;
    bool quit = false;
    printf("Entrer un entier N :");
    scanf("%d", &N);
    medicament *t = malloc(N * sizeof(medicament));
    init(N, t);

    do
    {
        printf("********Menu De Gestion********\n");
        printf("1. Afficher le detail du stock de la pharmacie\n\n");
        printf("2. Afficher les medicaments de la categorie ayant le moins de medicament de la pharmacie\n\n");
        printf("3. Afficher medicaments:\n\ta. D'un fournisseur donne\n\tb. D'une cateforie donnee\n\tc. Ayant un prix donne\n\n");
        printf("4. Ajouter un medicament:\n\ta. Au debut du tableau\n\tb. A la fin du tableau\n\tc. En une position donnee\n\td. Apres le 2eme medicament ayant la meme categorie aue celui a inserer\n\n");
        printf("5. Supprimier un medicament:\n\ta. Au debut\n\tb. A la fin\n\tc. En une position donnee\n\td.Par nom du medicament\n\te. Par fournisseur\n\tf. Dont nom du fournisseur se termine par une lettre donnee\n\n");
        printf("6. Quitter le programe\n\n");
        printf("********************************************************************\n");

        rewind(stdin);
        scanf("%d", &choix);
        rewind(stdin);
        affichage(choix, t);
        rewind(stdin);
        if (choix == 6)
            quit = true;

    } while (!quit);
    free(t);
    return 0;
}
