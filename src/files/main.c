#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

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
void init(int n, medicament *t);
void code_unique(char *s);

void affiche_min_categ(int N, medicament *t)
{
    char Categ[10];
    unsigned int min = UINT_MAX;

    for (int i = 0; i < N; i++)
    {
        unsigned int total = 0;
        for (int j = 0; j < N; j++)
        {
            if (strcmp((t + i)->categorie, (t + j)->categorie) == 0)
            {
                total += (t + j)->quant_stock;
            }
        }

        if (total < min)
        {
            min = total;
            strcpy(Categ, (t + i)->categorie);
        }
    }

    printf("Medicaments de la categorie avec la moins de medicament:\n");

    for (int i = 0; i < N; i++)
    {
        if (strcmp((t + i)->categorie, Categ) == 0)
        {
            printf("Medicament %d:\n", i + 1);
            printf("Code: %s\n", (t + i)->code);
            printf("Nom: %s\n", (t + i)->nom);
            printf("Categorie: %s\n", (t + i)->categorie);
            printf("Prix: %.2f\n", (t + i)->prix);
            printf("Quantite en stock: %u\n", (t + i)->quant_stock);
            printf("Fournisseur:\n");
            printf("\tCode Four: %d\n", (t + i)->forn.code);
            printf("\tNom: %s\n", (t + i)->forn.nom);
            printf("\tAdresse: %s\n", (t + i)->forn.adresse);
            printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
            printf("--------------------\n");
        }
    }
}

void upper_everything(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        *(s + i) = toupper(*(s + i));
    }
}

bool is_code_unique(char *s, medicament *t, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (strcmp(s, (t + i)->code) == 0)
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
void init(int N, medicament *t)
{
    for (int i = 0; i < N; i++)
    {
        printf("Le Nom du Medicament : ");
        scanf("%s", (t + i)->nom);

        printf("\t Categorie: ");
        scanf("%s", (t + i)->categorie);

        printf("\t Le prix: ");
        while (1)
        {
            if (scanf("%f", &(t + i)->prix) == 1 && (t + i)->prix >= 0)
            {
                break;
            }
            else
            {
                printf("entrer un prix > 0: ");
                while (getchar() != '\n')
                    ;
            }
        }

        printf("\t La quantite: ");
        while (1)
        {
            if (scanf("%u", &(t + i)->quant_stock) == 1)
            {
                break;
            }
            else
            {
                printf("entrer un prix > 0: ");
                while (getchar() != '\n')
                    ;
            }
        }

        printf("\t Nom fournisseur: ");
        scanf("%s", (t + i)->forn.nom);

        printf("\t Adresse du fournisseur: ");
        scanf("%s", (t + i)->forn.adresse);

        printf("\t Nationalite: ");
        scanf("%s", (t + i)->forn.nationalite);

        upper_everything((t + i)->nom);
        upper_everything((t + i)->categorie);
        upper_everything((t + i)->forn.nom);

        do
        {
            code_unique((t + i)->code);
        } while (!is_code_unique((t + i)->code, t, i));

        (t + i)->forn.code = rand();
    }
}

void affiche_stock(int N, medicament *t)
{

    int somme_med_valable = 0;

    printf("Stock details:\n");

    for (int i = 0; i < N; i++)
    {
        printf("Medicament %d:\n", i + 1);
        printf("Code: %s\n", (t + i)->code);
        printf("Nom: %s\n", (t + i)->nom);
        printf("Categorie: %s\n", (t + i)->categorie);
        printf("Prix: %.2f\n", (t + i)->prix);
        printf("Quantite en stock: %u\n", (t + i)->quant_stock);
        printf("Fournisseur:\n");
        printf("\tCode Four: %d\n", (t + i)->forn.code);
        printf("\tNom: %s\n", (t + i)->forn.nom);
        printf("\tAdresse: %s\n", (t + i)->forn.adresse);
        printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
        printf("--------------------\n");
        somme_med_valable += (t + i)->quant_stock;
    }
    printf("La somme des medicaments valable est:%d\n", somme_med_valable);
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
    int j = 0;
    char c;
    char s[10];
    medicament temp;
    medicament med1 = {0};
    float pr = 0;
    char cat[10] = {0};
    int i = 0;
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
        switch (choix)
        {
        case 1:
            // premier cas si l'utilisateur entre la valeur 1
            affiche_stock(N, t);
            break;
        case 2:
            // 2eme cas si l'utilisateur entre le nombre 2
            affiche_min_categ(N, t);
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
                assert(s != 0);
                for (i = 0; i < N; i++)
                {
                    if (strcmp(s, (t + i)->forn.nom) == 0)
                    {
                        found = true;
                        printf("Medicament %d:\n", i + 1);
                        printf("Code: %s\n", (t + i)->code);
                        printf("Nom: %s\n", (t + i)->nom);
                        printf("Categorie: %s\n", (t + i)->categorie);
                        printf("Prix: %.2f\n", (t + i)->prix);
                        printf("Quantite en stock: %u\n", (t + i)->quant_stock);
                        printf("Fournisseur:\n");
                        printf("\tCode Four: %d\n", (t + i)->forn.code);
                        printf("\tNom: %s\n", (t + i)->forn.nom);
                        printf("\tAdresse: %s\n", (t + i)->forn.adresse);
                        printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
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
                upper_everything(s);
                rewind(stdin);
                assert(s != 0);
                for (i = 0; i < N; i++)
                {
                    if (strcmp(s, (t + i)->categorie) == 0)
                    {
                        found = true;
                        printf("Medicament %d:\n", i + 1);
                        printf("Code: %s\n", (t + i)->code);
                        printf("Nom: %s\n", (t + i)->nom);
                        printf("Categorie: %s\n", (t + i)->categorie);
                        printf("Prix: %.2f\n", (t + i)->prix);
                        printf("Quantite en stock: %u\n", (t + i)->quant_stock);
                        printf("Fournisseur:\n");
                        printf("\tCode Four: %d\n", (t + i)->forn.code);
                        printf("\tNom: %s\n", (t + i)->forn.nom);
                        printf("\tAdresse: %s\n", (t + i)->forn.adresse);
                        printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
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
                printf("Entrer le prix:\n");
                rewind(stdin);
                scanf("%f", &pr);
                rewind(stdin);
                for (i = 0; i < N; i++)
                {
                    if ((float)abs(pr - (t + i)->prix) < 1e-9)
                    {
                        found = true;
                        printf("Medicament %d:\n", i + 1);
                        printf("Code: %s\n", (t + i)->code);
                        printf("Nom: %s\n", (t + i)->nom);
                        printf("Categorie: %s\n", (t + i)->categorie);
                        printf("Prix: %.2f\n", (t + i)->prix);
                        printf("Quantite en stock: %u\n", (t + i)->quant_stock);
                        printf("Fournisseur:\n");
                        printf("\tCode Four: %d\n", (t + i)->forn.code);
                        printf("\tNom: %s\n", (t + i)->forn.nom);
                        printf("\tAdresse: %s\n", (t + i)->forn.adresse);
                        printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
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

            printf("Entrer :\na-Au debut du tableau\nb-A la fin du tableau\nc-En une position a votre choix\nd-Apres le 2eme medicament de meme categorie\n");
            rewind(stdin);
            scanf("%c", &c);
            rewind(stdin);
            init(1, &med1);
            medicament *temp2;
            switch (c)
            {
            case 'a':
                temp2 = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
                assert(temp2 != NULL);
                t = temp2;
                for (i = N; i > 0; i--)
                {
                    *(t + i) = *(t + i - 1);
                }
                *t = med1;
                (N)++;

                break;
            case 'b':
                temp2 = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
                t = temp2;
                assert(t != NULL);
                *(t + N) = med1;
                (N)++;
                break;
            case 'c':
                printf("Veuiller donner la position ou vous voulez ajouter votre nouveau medicament:\n");
                do
                {
                    scanf("%d", &j);
                } while (j < 1 || j > N + 1);
                rewind(stdin);
                temp2 = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
                t = temp2;
                assert(t != NULL);
                j--;
                for (i = N; i > j; i--)
                {
                    *(t + i) = *(t + i - 1);
                }
                *(t + j) = med1;
                (N)++;
                break;
            case 'd':
                j = 0;
                printf("Veuiller Entrer La Categorie:");
                rewind(stdin);
                scanf("%10s", cat);
                rewind(stdin);
                temp2 = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
                t = temp2;
                assert(t != NULL);
                for (i = 0; i < N; i++)
                {
                    if (strcmp(cat, (t + i)->categorie) == 0)
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
                    *(t + i) = *(t + i - 1);
                }
                *(t + j) = med1;
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

                for (int i = 0; i < N - 1; i++)
                {
                    *(t + i) = *(t + i + 1);
                }

                t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
                (N)--;
                break;
            case 'b':
                t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
                (N)--;
                break;
            case 'c':
                printf("Entrer votre position:\n");
                do
                {
                    scanf("%d", &j);
                } while (j < 1 || j > N + 1);

                j--;

                for (int k = j; k < N - 1; k++)
                {
                    *(t + k) = *(t + k + 1);
                }

                t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
                (N)--;
                break;
            case 'd':
                j = -1;
                printf("Entrer le nom du medicament:");
                scanf("%s", s);
                rewind(stdin);
                upper_everything(s);
                for (i = 0; i < N; i++)
                {
                    if (strcmp((t + i)->nom, s) == 0)
                    {
                        j = i;
                        break;
                    }
                }
                if (j != -1)
                {
                    for (int k = j; k < N - 1; k++)
                    {
                        *(t + k) = *(t + k + 1);
                    }
                    t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
                    (N)--;
                }
                else
                {
                    printf("pas de med : %s\n", s);
                }

                break;
            case 'e':
                j = -1;
                printf("Entrer le code du fournisseur:\n");
                int code_f;
                scanf("%d", &code_f);
                rewind(stdin);

                for (i = 0; i < N; i++)
                {
                    if (code_f == (t + i)->forn.code)
                    {
                        j = i;
                        break;
                    }
                }
                if (j != -1)
                {
                    for (int k = j; k < N - 1; k++)
                    {
                        *(t + k) = *(t + k + 1);
                    }
                    t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
                    (N)--;
                }
                else
                {
                    printf("code not found: \n");
                }

                break;
            case 'f':
                char lettre = 0;
                printf("Entrer la lettre souhaiter:\n");
                scanf("%c", &lettre);
                rewind(stdin);
                int nombre_suppr = 0;
                lettre == toupper(lettre);
                
                for (int i = 0; i < N; i++)
                {
                    char last_Letter = (t + i)->forn.nom[strlen((t + i)->forn.nom) - 1];

                    if (last_Letter == lettre)
                    {
                        for (int k = i; k < N - 1; k++)
                        {
                            *(t+k) = *(t + k + 1);
                        }

                        t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
                        assert(t != NULL);

                        (N)--;
                        nombre_suppr++;
                        i--;
                    }
                }

                if (nombre_suppr > 0)
                {
                    printf("%d medic supprimer\n", nombre_suppr);
                }
                else
                {
                    printf("No medicament trouve.\n");
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

        rewind(stdin);
        if (choix == 6)
            quit = true;

    } while (!quit);
    free(t);
    return 0;
}
