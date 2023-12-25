#include <sdl2/SDL_UI.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef enum
{
    PAGE_VAL_NOT_INIT,
    PAGE_VAL_INT,
    PAGE_MAIN_MENU,
} STATE;

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
void init(int n, medicament *t, bool have_cat);
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
    *(s + strlen(s)) = '\0';
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
void init(int N, medicament *t, bool have_cat)
{
    for (int i = 0; i < N; i++)
    {
        printf("Le Nom du Medicament : ");
        scanf("%s", (t + i)->nom);
        if (!have_cat)
        {
            printf("\t Categorie: ");
            scanf("%s", (t + i)->categorie);
        }

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
void cmp_codes_name(int N, medicament *t)
{

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (strcmp((t + i)->nom, (t + j)->nom) == 0)
            {
                strcpy((t + j)->code, (t + i)->code);
            }
        }
    }
}
void initUIElement(UIElement_t *element, int x, int y, int width, int height, int border_radius, bool (*onClick)(void *data), void *onClickData, SDL_Texture *tex)
{
    element->rect = (SDL_Rect){x, y, width, height};
    element->border_radius = border_radius;
    element->onClick = onClick;
    element->onClickData = onClickData;
    element->texture = tex;
}

void initPage2(UIElement_t *Page2, int *height)
{

    int x = 100;
    int initialY = 100;
    int border_radius = 10;

    initUIElement(&Page2[0], x, *height, 50, 50, border_radius, NULL, NULL, NULL);
    initUIElement(&Page2[1], x, *height, 80, 30, border_radius, NULL, NULL, NULL);
    *height += 60;

    initUIElement(&Page2[2], x, *height, 80, 30, border_radius, NULL, NULL, NULL);
    initUIElement(&Page2[2], x, *height, 80, 30, border_radius, NULL, NULL, NULL);
    *height += 40;
}
bool iteration_left_onclick(void *data)
{
    int *i = (int *)data;
    if (*i > 0)
    {
        (*i)--;
    }

    return true;
}
bool iteration_right_onclick(void *data)
{
    int *i = (int *)data;
        printf("%d",*i);

    if (*i >= 0 && *i < N)
    {
        (*i)++;
        printf("%d",*i);
    }

    return true;
}

void renderText_mod(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_Rect *pos, int wrapLength)
{
    SDL_Surface *surface;
    if (wrapLength == -1)
    {
        surface = TTF_RenderText_Blended(font, text, color);
    }
    else
    {
        surface = TTF_RenderText_Blended_Wrapped(font, text, color, wrapLength);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth, textHeight;
    TTF_SizeText(font, text, &textWidth, &textHeight);

    pos->w = textWidth;

    SDL_RenderCopy(renderer, texture, NULL, pos);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void init_withrender(SDL_Renderer *renderer, TTF_Font *font, medicament *t, bool have_cat, int i)
{
    SDL_Color black = {.a = 255, .r = 27, .g = 27, .b = 27};
    SDL_Rect pos = {.x = 30, .y = 100, .w = 100, .h = 20};
    renderText_mod(renderer, font, "Le Nom du Medicament : ", black, &pos, -1);
    pos.y += 70;
    if (!have_cat)
    {
        renderText_mod(renderer, font, "Categorie: ", black, &pos, -1);
        pos.y += 70;
    }

    renderText_mod(renderer, font, "Le prix: ", black, &pos, -1);
    pos.y += 70;

    renderText_mod(renderer, font, "La quantite: ", black, &pos, -1);
    pos.y += 70;

    renderText_mod(renderer, font, "Nom fournisseur: ", black, &pos, -1);
    pos.y += 70;

    renderText_mod(renderer, font, "Adresse du fournisseur: ", black, &pos, -1);
    pos.y += 70;

    renderText_mod(renderer, font, "Nationalite: ", black, &pos, -1);
}

bool return_to_main_menu(void *data)
{
    STATE *states = (STATE *)data;
    *states = PAGE_MAIN_MENU;
    if (states == NULL)
    {
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("Gestion Stock d'une pharmacie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    char text_N[30];
    bool is_N_init = false;
    STATE states = PAGE_VAL_NOT_INIT;

    
    int choix;
    bool quit = false;
    medicament *t = malloc(N * sizeof(medicament));

    int j = 0;
    char c;
    char s[10];
    medicament temp;
    medicament med1 = {0};
    float pr = 0;
    char cat[10] = {0};
    int i = 0;

    UIElement_t Page1[] = {
        {.rect = {0, 0, 800, 600}, .border_radius = 20, .onClick = NULL, .onClickData = NULL, .texture = NULL},
        {.rect = {400 - 50, 300 - 50, 150, 70}, .border_radius = 10, .onClick = textfieldOnClick, .onClickData = text_N, .texture = NULL},
        {.rect = {20, 20, 800 - 40, 70}, .border_radius = 0, .onClick = NULL, .onClickData = NULL, .texture = NULL},

    };
    UITextField_t PHARMACIEDEF = {.base = Page1[2], .font = TTF_OpenFont("../fonts/arial.ttf", 26), .text = "GESTION STOCK PHARMACIE", .bgColor = {.a = 255, .r = 255, .g = 255, .b = 255}, .textColor = {.a = 255, .r = 55, .g = 40, .b = 15}};
    UITextField_t textfield_N = {.base = Page1[1], .font = TTF_OpenFont("../fonts/arial.ttf", 20), .text = "", .bgColor = {.a = 255, .r = 255, .g = 0, .b = 0}, .textColor = {.a = 255, .r = 55, .g = 40, .b = 15}};
    int numElements = sizeof(Page1) / sizeof(Page1[0]);
    int counter_of_i = 0;
    UIElement_t NAV_PAGES[10] = {
        {.rect = {20, 20, 50, 50}, .border_radius = 0, .onClick = return_to_main_menu, .onClickData = &states, .texture = NULL},
        {.rect = {375, 570, 30, 30}, .border_radius = 0, .onClick = iteration_left_onclick, .onClickData = &counter_of_i, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = iteration_right_onclick, .onClickData = &counter_of_i, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = NULL, .onClickData =NULL, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = NULL, .onClickData =NULL, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = NULL, .onClickData =NULL, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = NULL, .onClickData =NULL, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = NULL, .onClickData =NULL, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = NULL, .onClickData =NULL, .texture = NULL},
        {.rect = {575, 570, 30, 30}, .border_radius = 0, .onClick = NULL, .onClickData =NULL, .texture = NULL},

    };

    UIButton_t NAV_PAGES_BUTTON[3] = {
        {.base = NAV_PAGES[0], .font = textfield_N.font, .isHovered = false, .normalColor = {.a = 255, .r = 136, .g = 171, .b = 142}, .hoverColor = {.a = 255, .r = 79, .g = 111, .b = 82}, .label = "<>"},
        {.base = NAV_PAGES[1], .font = textfield_N.font, .isHovered = false, .normalColor = {.a = 255, .r = 136, .g = 171, .b = 142}, .hoverColor = {.a = 255, .r = 79, .g = 111, .b = 82}, .label = "<"},
        {.base = NAV_PAGES[2], .font = textfield_N.font, .isHovered = false, .normalColor = {.a = 255, .r = 136, .g = 171, .b = 142}, .hoverColor = {.a = 255, .r = 79, .g = 111, .b = 82}, .label = ">"},

    };

    UITextField_t NAV_PAGES_TEXTFIELD[7] = {
    };
    SDL_Color grey = {.r = 107, .g = 107, .b = 107, .a = 255};
    SDL_Color black = {.r = 0, .g = 0, .b = 0, .a = 255};

    // init(N, t, false);

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (states == PAGE_VAL_NOT_INIT)
            {

                switch (event.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;

                default:
                    break;
                }

                handleEditableTextFieldEvents(&textfield_N, &event, text_N);
            }
            else if (states == PAGE_VAL_INT)
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEMOTION:
                    updateButtonState(NAV_PAGES_BUTTON, event.motion.x, event.motion.y);
                    updateButtonState(NAV_PAGES_BUTTON + 1, event.motion.x, event.motion.y);
                    updateButtonState(NAV_PAGES_BUTTON + 2, event.motion.x, event.motion.y);

                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        printf("x:%d,y:%d, counter:%d\n",event.button.x, event.button.y, counter_of_i);
                        for (int i = 0; i < sizeof(NAV_PAGES_BUTTON) / sizeof(NAV_PAGES_BUTTON[0]); i++)
                        {
                            if (pointInRect(event.button.x, event.button.y, NAV_PAGES_BUTTON[i].base.rect))
                            {
                                if (NAV_PAGES_BUTTON[i].base.onClick != NULL)
                                {
                                    NAV_PAGES_BUTTON[i].base.onClick(NAV_PAGES_BUTTON[i].base.onClickData);
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {

                switch (event.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;

                default:
                    break;
                }
            }
        }
        // printf("********Menu De Gestion********\n");
        // printf("1. Afficher le detail du stock de la pharmacie\n\n");
        // printf("2. Afficher les medicaments de la categorie ayant le moins de medicament de la pharmacie\n\n");
        // printf("3. Afficher medicaments:\n\ta. D'un fournisseur donne\n\tb. D'une cateforie donnee\n\tc. Ayant un prix donne\n\n");
        // printf("4. Ajouter un medicament:\n\ta. Au debut du tableau\n\tb. A la fin du tableau\n\tc. En une position donnee\n\td. Apres le 2eme medicament ayant la meme categorie aue celui a inserer\n\n");
        // printf("5. Supprimier un medicament:\n\ta. Au debut\n\tb. A la fin\n\tc. En une position donnee\n\td.Par nom du medicament\n\te. Par fournisseur\n\tf. Dont nom du fournisseur se termine par une lettre donnee\n\n");
        // printf("6. Quitter le programe\n\n");
        // printf("********************************************************************\n");
        //
        // rewind(stdin);
        // scanf("%d", &choix);
        // rewind(stdin);
        // switch (choix)
        // {
        // case 1:
        //     // premier cas si l'utilisateur entre la valeur 1
        //     affiche_stock(N, t);
        //     break;
        // case 2:
        //     // 2eme cas si l'utilisateur entre le nombre 2
        //     affiche_min_categ(N, t);
        //     break;
        // case 3:
        //     // 3eme cas si l'utilisateur entre le nombre 3
        //     printf("Entrer :\na-D'apres le fournisseur donnee\nb-D'apres ca categorie donnee\nc-D'apres le prix\n");
        //     rewind(stdin);
        //     bool found = false;
        //     scanf("%c", &c);
        //     rewind(stdin);
        //     switch (c)
        //     {
        //     case 'a':
        //         // cas d'affichage de tous lesmedicaments d'apres un fournisseur
        //         printf("Entrer le nom du fournisseur:\n");
        //         scanf("%s", s);
        //         rewind(stdin);
        //         upper_everything(s);
        //         assert(s != 0);
        //         for (i = 0; i < N; i++)
        //         {
        //             if (strcmp(s, (t + i)->forn.nom) == 0)
        //             {
        //                 found = true;
        //                 printf("Medicament %d:\n", i + 1);
        //                 printf("Code: %s\n", (t + i)->code);
        //                 printf("Nom: %s\n", (t + i)->nom);
        //                 printf("Categorie: %s\n", (t + i)->categorie);
        //                 printf("Prix: %.2f\n", (t + i)->prix);
        //                 printf("Quantite en stock: %u\n", (t + i)->quant_stock);
        //                 printf("Fournisseur:\n");
        //                 printf("\tCode Four: %d\n", (t + i)->forn.code);
        //                 printf("\tNom: %s\n", (t + i)->forn.nom);
        //                 printf("\tAdresse: %s\n", (t + i)->forn.adresse);
        //                 printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
        //                 printf("--------------------\n");
        //             }
        //         }
        //         if (!found)
        //         {
        //             printf("Not found:\n");
        //         }

        //         break;
        //     case 'b':
        //         // cas d'affichage de tous les medicaments d'apres la categorie
        //         printf("Entrer la categorie:\n");
        //         rewind(stdin);
        //         scanf("%s", s);
        //         upper_everything(s);
        //         rewind(stdin);
        //         assert(s != 0);
        //         for (i = 0; i < N; i++)
        //         {
        //             if (strcmp(s, (t + i)->categorie) == 0)
        //             {
        //                 found = true;
        //                 printf("Medicament %d:\n", i + 1);
        //                 printf("Code: %s\n", (t + i)->code);
        //                 printf("Nom: %s\n", (t + i)->nom);
        //                 printf("Categorie: %s\n", (t + i)->categorie);
        //                 printf("Prix: %.2f\n", (t + i)->prix);
        //                 printf("Quantite en stock: %u\n", (t + i)->quant_stock);
        //                 printf("Fournisseur:\n");
        //                 printf("\tCode Four: %d\n", (t + i)->forn.code);
        //                 printf("\tNom: %s\n", (t + i)->forn.nom);
        //                 printf("\tAdresse: %s\n", (t + i)->forn.adresse);
        //                 printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
        //                 printf("--------------------\n");
        //             }
        //         }
        //         if (!found)
        //         {
        //             printf("Not found:\n");
        //         }

        //         break;
        //     case 'c':
        //         // cas d'affichage de tous lesmedicaments d'apres le prix
        //         printf("Entrer le prix:\n");
        //         rewind(stdin);
        //         scanf("%f", &pr);
        //         rewind(stdin);
        //         for (i = 0; i < N; i++)
        //         {
        //             if ((float)abs(pr - (t + i)->prix) < 1e-9)
        //             {
        //                 found = true;
        //                 printf("Medicament %d:\n", i + 1);
        //                 printf("Code: %s\n", (t + i)->code);
        //                 printf("Nom: %s\n", (t + i)->nom);
        //                 printf("Categorie: %s\n", (t + i)->categorie);
        //                 printf("Prix: %.2f\n", (t + i)->prix);
        //                 printf("Quantite en stock: %u\n", (t + i)->quant_stock);
        //                 printf("Fournisseur:\n");
        //                 printf("\tCode Four: %d\n", (t + i)->forn.code);
        //                 printf("\tNom: %s\n", (t + i)->forn.nom);
        //                 printf("\tAdresse: %s\n", (t + i)->forn.adresse);
        //                 printf("\tNationalite: %s\n", (t + i)->forn.nationalite);
        //                 printf("--------------------\n");
        //             }
        //         }
        //         if (!found)
        //         {
        //             printf("Not found:\n");
        //         }
        //         break;
        //     default:
        //         printf("Erreur Choix INVALIDE\n");
        //         break;
        //     }
        //     break;
        // case 4:
        //     // 4eme cas d'ajout d'un medicament

        //     printf("Entrer :\na-Au debut du tableau\nb-A la fin du tableau\nc-En une position a votre choix\nd-Apres le 2eme medicament de meme categorie\n");
        //     rewind(stdin);
        //     scanf("%c", &c);
        //     rewind(stdin);
        //     medicament *temp2;
        //     switch (c)
        //     {
        //     case 'a':
        //         temp2 = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
        //         assert(temp2 != NULL);
        //         t = temp2;
        //         for (i = N; i > 0; i--)
        //         {
        //             *(t + i) = *(t + i - 1);
        //         }
        //         printf("Entrer un nouveau med :\n");
        //         init(1, t, false);
        //         cmp_codes_name(N, t);
        //         (N)++;

        //         break;
        //     case 'b':
        //         temp2 = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
        //         t = temp2;
        //         assert(t != NULL);
        //         printf("Entrer un nouveau med :\n");
        //         init(1, t + N, false);
        //         cmp_codes_name(N, t);
        //         (N)++;
        //         break;
        //     case 'c':
        //         printf("Veuiller donner la position ou vous voulez ajouter votre nouveau medicament:\n");
        //         do
        //         {
        //             scanf("%d", &j);
        //         } while (j < 1 || j > N);
        //         rewind(stdin);
        //         temp2 = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
        //         t = temp2;
        //         assert(t != NULL);
        //         j--;
        //         for (i = N; i > j; i--)
        //         {
        //             *(t + i) = *(t + i - 1);
        //         }
        //         printf("Entrer un nouveau med :\n");
        //         init(1, t + j, false);
        //         cmp_codes_name(N, t);
        //         (N)++;
        //         break;
        //     case 'd':
        //         j = 0;
        //         printf("Veuiller Entrer La Categorie:");
        //         rewind(stdin);
        //         scanf("%9s", cat);
        //         rewind(stdin);
        //         upper_everything(cat);

        //         int CMB_CAT = 0;
        //         int pos = -1;

        //         for (int i = 0; i < N; i++)
        //         {
        //             if (strcmp(cat, (t + i)->categorie) == 0)
        //             {
        //                 CMB_CAT++;
        //                 if (CMB_CAT == 2)
        //                 {
        //                     pos = i + 1;
        //                     break;
        //                 }
        //             }
        //         }

        //         if (CMB_CAT >= 2)
        //         {
        //             t = (medicament *)realloc(t, (N + 1) * sizeof(medicament));
        //             assert(t != NULL);

        //             for (int i = N; i > pos; i--)
        //             {
        //                 *(t + i) = *(t + i - 1);
        //             }

        //             init(1, t + pos, true);
        //             strcpy((t + pos)->categorie, cat);
        //             cmp_codes_name(N, t);

        //             (N)++;
        //         }
        //         else
        //         {
        //             printf("il n'ya pas assez de med de meme cat: .\n");
        //         }
        //         break;
        //     default:
        //         printf("Erreur Choix INVALIDE\n");
        //         break;
        //     }
        //     break;
        // case 5:
        //     // 5eme cas de supression d'un medicament
        //     printf("Entrer :\na-Au debut du tableau\nb-A la fin du tableau\nc-En une position a votre choix\nd-Par Nom Du Medicament\ne-Par fournisseur\nf-Dont nom du fournisseur termine par une lettre donne:\n");
        //     rewind(stdin);
        //     scanf("%c", &c);
        //     rewind(stdin);
        //     switch (c)
        //     {
        //     case 'a':

        //         for (int i = 0; i < N - 1; i++)
        //         {
        //             *(t + i) = *(t + i + 1);
        //         }

        //         t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
        //         (N)--;
        //         break;
        //     case 'b':
        //         t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
        //         (N)--;
        //         break;
        //     case 'c':
        //         printf("Entrer votre position:\n");
        //         do
        //         {
        //             scanf("%d", &j);
        //         } while (j < 1 || j > N);

        //         j--;

        //         for (int k = j; k < N - 1; k++)
        //         {
        //             *(t + k) = *(t + k + 1);
        //         }

        //         t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
        //         (N)--;
        //         break;
        //     case 'd':
        //         j = -1;
        //         printf("Entrer le nom du medicament:");
        //         scanf("%s", s);
        //         rewind(stdin);
        //         upper_everything(s);
        //         for (i = 0; i < N; i++)
        //         {
        //             if (strcmp((t + i)->nom, s) == 0)
        //             {
        //                 j = i;
        //                 break;
        //             }
        //         }
        //         if (j != -1)
        //         {
        //             for (int k = j; k < N - 1; k++)
        //             {
        //                 *(t + k) = *(t + k + 1);
        //             }
        //             t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
        //             (N)--;
        //         }
        //         else
        //         {
        //             printf("pas de med : %s\n", s);
        //         }

        //         break;
        //     case 'e':
        //         j = -1;
        //         printf("Entrer le code du fournisseur:\n");
        //         int code_f;
        //         scanf("%d", &code_f);
        //         rewind(stdin);

        //         for (i = 0; i < N; i++)
        //         {
        //             if (code_f == (t + i)->forn.code)
        //             {
        //                 j = i;
        //                 break;
        //             }
        //         }
        //         if (j != -1)
        //         {
        //             for (int k = j; k < N - 1; k++)
        //             {
        //                 *(t + k) = *(t + k + 1);
        //             }
        //             t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
        //             (N)--;
        //         }
        //         else
        //         {
        //             printf("code not found: \n");
        //         }

        //         break;
        //     case 'f':
        //         printf("Entrer la lettre souhaiter:\n");
        //         char lettre = 0;
        //         scanf("%c", &lettre);
        //         rewind(stdin);
        //         int nombre_suppr = 0;
        //         lettre = toupper(lettre);

        //         for (int i = 0; i < N; i++)
        //         {
        //             char last_Letter = *((t + i)->forn.nom + strlen((t + i)->forn.nom) - 1);

        //             if (last_Letter == lettre)
        //             {
        //                 for (int k = i; k < N - 1; k++)
        //                 {
        //                     *(t + k) = *(t + k + 1);
        //                 }

        //                 t = (medicament *)realloc(t, (N - 1) * sizeof(medicament));
        //                 assert(t != NULL);

        //                 (N)--;
        //                 nombre_suppr++;
        //                 i--;
        //             }
        //         }

        //         if (nombre_suppr > 0)
        //         {
        //             printf("%d medic supprimer\n", nombre_suppr);
        //         }
        //         else
        //         {
        //             printf("No medicament trouve.\n");
        //         }
        //         break;
        //     default:
        //         printf("Erreur Choix INVALIDE\n\n");
        //         break;
        //     }
        //     break;
        // case 6:
        //     quit = true;
        //     break;
        // default:
        //     printf("Erreur Choix INVALIDE\n");
        //     break;
        // }

        if (states == PAGE_VAL_NOT_INIT)
        {
            if (!is_N_init)
            {
                if (atoi(text_N) > 0 && atoi(text_N) < 9)
                {
                    is_N_init = true;
                    N = atoi(text_N);
                    states = PAGE_VAL_INT;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        renderTextFieldRr(renderer, &PHARMACIEDEF, 0, grey, "");

        if (states == PAGE_VAL_NOT_INIT)
        {
            for (int i = 0; i < numElements; ++i)
            {
                switch (i)
                {
                case 0:

                    renderPlacementFieldRr(renderer, (UIPlacementField_t *)&Page1[i], 1);
                    break;
                case 1:
                    renderTextFieldRr(renderer, &textfield_N, 1, grey, "Fill N: ");
                    break;
                }
            }
        }
        else if (states == PAGE_VAL_INT)
        {
            renderButtonRr(renderer, NAV_PAGES_BUTTON, false, black);
            renderButtonRr(renderer, NAV_PAGES_BUTTON + 1, false, black);
            renderButtonRr(renderer, NAV_PAGES_BUTTON + 2, false, black);

            init_withrender(renderer, textfield_N.font, t, false, i);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    free(t);
    TTF_CloseFont(textfield_N.font);
    TTF_CloseFont(PHARMACIEDEF.font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}