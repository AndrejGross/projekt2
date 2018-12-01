#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct inzeraty
{
//zadefinovanie štruktúry
    char kategoria[51];
    char znacka[51];
    char predajca[101];
    int cena;
    int rok_vyroby;
    char stav_vozidla[201];
    struct inzeraty *dalsi;
};
struct inzeraty* n(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act)
{
    int pocetZaznamov=0;
    char str[201];

    if((*file=fopen("auta.txt","r"))==NULL) //otvorenie súboru + kontrola
        return 0;

//poèítanie záznamov na základe vıskytu znaku $
    if (*file)
    {
        while(fscanf(*file,"%s",str)!=EOF)
            if(str[0]=='$')
                pocetZaznamov++;
    }
    *pocet_zaznamov=pocetZaznamov; //poèet záznamov priradím smerníku

    rewind(*file); //na zaiatok súboru

    if((prvy=malloc(sizeof(struct inzeraty)))==NULL) //alokujem prvy záznam
        return 0;

    act=prvy;
    while(!feof(*file)) //po koniec súboru naèítava hodnoty zo súbora do záznamov
    {
        fscanf(*file,"%*c");
        fscanf(*file,"%*c");
        fscanf(*file,"%[^\n]",act->kategoria);
        fscanf(*file,"%*c");
        fscanf(*file,"%[^\n]",act->znacka);
        fscanf(*file,"%*c");
        fscanf(*file,"%[^\n]",act->predajca);
        fscanf(*file,"%*c");
        fscanf(*file,"%d",&act->cena);
        fscanf(*file,"%*c");
        fscanf(*file,"%d",&act->rok_vyroby);
        fscanf(*file,"%*c");
        fscanf(*file,"%[^\n]",act->stav_vozidla);
        fscanf(*file,"%*c");

        if((act->dalsi=malloc(sizeof(struct inzeraty)))==NULL) //alokujem miesto pre ïalši záznam
            return 0;

        act=act->dalsi; //posúvanie sa v medzi záznammi
    }
    printf("Nacitalo sa %d zaznamov\n",pocetZaznamov);

    return prvy; //vraciam smernik na prvı záznam
}
void v(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act)
{
    int poradie=1;

    act=prvy;
    while(act!=NULL) //vypisovanie záznamov kım nieje aktuálny záznam prázdny
    {
        if(poradie==*pocet_zaznamov+1)
            break;
        printf("%d.\n",poradie);
        printf("kategoria: %s\n",act->kategoria);
        printf("znacka: %s\n",act->znacka);
        printf("predajca: %s\n",act->predajca);
        printf("cena: %d\n",act->cena);
        printf("rok_vyroby: %d\n",act->rok_vyroby);
        printf("stav_vozidla: %s\n",act->stav_vozidla);

        act=act->dalsi;
        poradie++; //poèítadlo pre poradie
    }
}
struct inzeraty* p(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act,struct inzeraty *novy)
{
    int k,pocitadlo=0;
    scanf("%d",&k);

    if(k<=0) //ak je naèítané èíslo menšie alebo rovné nule, funkcia nepokraèuje
        return 0;

    if(k>*pocet_zaznamov) //ak je poèet záznamov väèší ako naèítané èíslo, záznam sa zapíše na koniec
        k=*pocet_zaznamov+1;

    if((novy=malloc(sizeof(struct inzeraty)))==NULL)
       return 0;

//naèítavanie nového záznam
    scanf("%*c");
    scanf("%[^\n]",novy->kategoria);
    scanf("%*c");
    scanf("%[^\n]",novy->znacka);
    scanf("%*c");
    scanf("%[^\n]",novy->predajca);
    scanf("%*c");
    scanf("%d",&novy->cena);
    scanf("%*c");
    scanf("%d",&novy->rok_vyroby);
    scanf("%*c");
    scanf("%[^\n]",novy->stav_vozidla);
    scanf("%*c");

    if(*pocet_zaznamov==0) //ak je poèet záznamov 0, tak sa novı záznam uloí na prvné miesto
    {
        novy->dalsi=NULL;
        *pocet_zaznamov+=1;
        return novy;

    }
        act=prvy;

    while(act!=NULL)
    {
        pocitadlo++;
        if(act==prvy&&k==1) //ak chceme uloi záznam na prvé miesto
        {
            novy->dalsi=prvy;
            prvy=novy;
        }
        else
        if(k==pocitadlo+1) //ak chceme uloi záznam na hoci aké iné miesto
        {
            novy->dalsi=act->dalsi;
            act->dalsi=novy;
        }

    act=act->dalsi;
    }
    *pocet_zaznamov+=1;
    return prvy;
}
struct inzeraty* h(FILE **file,struct inzeraty *prvy,struct inzeraty *act)
{
    char znacka_auta[51],act_znacka[51];
    int cena_ponuky,poradie=0,i,j=0;

    scanf("%*c");
    scanf("%[^\n]",znacka_auta); //naèítanie znaèky auta
    scanf("%*c");
    scanf("%d",&cena_ponuky); //naèítanie ceny

    while(znacka_auta[j]) //zmena na ve¾ké písmená
        {
            if(znacka_auta[j]!=' ')
            {
                if (znacka_auta[j]<'A'||znacka_auta[j]>'Z')
                    znacka_auta[j]=znacka_auta[j]-32;
            }
            j++;
        }

    act=prvy;
    while(act!=NULL)
    {
        i=0;
        sprintf(act_znacka,"%s",act->znacka); //vytvorenie pomocnej pre aktuálnu znaèku prvku

        while(act_znacka[i])  //zmena na ve¾ké písmená
        {
            if(act_znacka[i]!=' ')
            {
                 if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                    act_znacka[i]=act_znacka[i]-32;
            }
            i++;
        }

        if((strcmp(act_znacka,znacka_auta)==0)&&(act->cena<=cena_ponuky))   //ak je lex. dåka zhodná
        {                                                                   //a zároveò cena auta je menšia
            poradie++;                                                      //alebo rovná zadanej tak záznam vypíše
            printf("%d.\n",poradie);
            printf("kategoria: %s\n",act->kategoria);
            printf("znacka: %s\n",act->znacka);
            printf("predajca: %s\n",act->predajca);
            printf("cena: %d\n",act->cena);
            printf("rok_vyroby: %d\n",act->rok_vyroby);
            printf("stav_vozidla: %s\n",act->stav_vozidla);
        }
        act=act->dalsi;
    }
    if(poradie==0) //ak nieje iadny záznam vyhovujúci
        printf("V ponuke nie su pozadovane auta\n");

    return prvy;
}
struct inzeraty* a(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act)
{
    int rokVyroby,pocitadlo=0,j=0,i;
    char znacka_auta[51],act_znacka[51];

    scanf("%*c");
    scanf("%[^\n]",znacka_auta);
    scanf("%*c");
    scanf("%d",&rokVyroby);

    if(*pocet_zaznamov==0) //ak je poèet záznamov 0, funkcia nepokraèuje
        {
            printf("Aktualizovalo sa %d zaznamov\n",pocitadlo);
            return 0;
        }

    act=prvy;

    while(znacka_auta[j]) //na ve¾ké písmená
        {
            if (znacka_auta[j]<'A'||znacka_auta[j]>'Z')
                znacka_auta[j]=znacka_auta[j]-32;
            j++;
        }

    while(act!=NULL)
    {
        i=0;
        sprintf(act_znacka,"%s",act->znacka); //vytvorenie pomocnej pre aktuálnu znaèku

        while(act_znacka[i]) //na ve¾ké písmená
        {
            if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                act_znacka[i]=act_znacka[i]-32;
            i++;
        }

        if(strcmp(act_znacka,znacka_auta)==0&&act->rok_vyroby==rokVyroby)   //ak je lex. dåka zhodná
        {                                                                   //a zadanı rok vıroby sa zhoduje
            if(act->cena-100<0)                                             //s rokom vıroby auta tak sa záznam vypíše
                act->cena=0;
                else
                act->cena-=100;
            pocitadlo++; //poèítadlo pre vyhovujúce záznamy
        }
    act=act->dalsi;
    }
    printf("Aktualizovalo sa %d zaznamov\n",pocitadlo);

    return prvy;
}
struct inzeraty* z(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act,struct inzeraty *pred)
{
    int pocitadlo=0,j=0,i;
    char znacka_auta[51],act_znacka[51];

    scanf("%*c");
    scanf("%[^\n]",znacka_auta); //naèítanie znaèky auta
    scanf("%*c");

    while(znacka_auta[j]) //na ve¾ké písmená
    {
        if(znacka_auta[j]!=' ')
        {
            if (znacka_auta[j]<'A'||znacka_auta[j]>'Z')
                znacka_auta[j]=znacka_auta[j]-32;
        }
        j++;

    }

    act=prvy;
    while(act!=NULL)
    {
        i=0;
        sprintf(act_znacka,"%s",act->znacka); //vytvorenie pomocnej pre aktuálnu znaèku auta
        while(act_znacka[i])
        {
            if(act_znacka[i]!=' ')
            {
                if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                    act_znacka[i]=act_znacka[i]-32;
            }
            i++;
        }
        if(strstr(act_znacka,znacka_auta)!=NULL) //ak sa string znacka_auta nachádza v znaèke auta aktuálneho záznamu
        {
            if(act==prvy) //ak je aktuálny záznam zároveò aj prvı
            {
                prvy=prvy->dalsi; //nasledujúci záznam po prvom sa stáva prvım
            }
            else
            {
                pred=prvy;              //ak nie akt. záznam prvı, tak predchádzajúci je prvı
                while(pred->dalsi!=act) //kım sa predchádzajúci ïalší nerovná aktuálnemu záznamu
                    pred=pred->dalsi;   //prehladávanie medzi záznammi

                pred->dalsi=act->dalsi; //ak je predchádzajúci ïalší rovnı aktuálnemu záznamu, tak akt. ïalší je pred. ïalší
            }
            *pocet_zaznamov-=1; //odpoèíta 1 z poètu prvkov
            free(act);          //odstráò aktuálny záznam
            pocitadlo++;        //poèítadlo pre poèet vymazanıch záznamov
        }
        act=act->dalsi; //prechádzanie záznammi
    }
    printf("Vymazalo sa %d zaznamov\n",pocitadlo);

    return prvy;
}
void k(FILE **file,struct inzeraty *prvy,struct inzeraty *act)
{
    if(*file!=NULL) //ak bol súbor otvorenı, tak súbor zavrie
        fclose(*file);

//mazanie záznamov
    act=prvy->dalsi;
    while(act!=NULL)
    {
        free(prvy);
        prvy=act;
        act=act->dalsi;
    }
    exit(EXIT_SUCCESS); //ukonèenie programu
}
int main()
{
    int pocet_zaznamov=0;
    char c;

    FILE *file=NULL; //zadefinovanie súboru

    //zadefinovanie pointrov na štruktúru
    struct inzeraty *prvy;
    struct inzeraty *act;
    struct inzeraty *pred;
    struct inzeraty *novy;

    while(1) //nekoneènı cyklus
    {
        scanf("%c",&c); //naèítavanie znaku pre volanie funkcie
        switch(c)       //switch pre vyberanie funkcie
        {
            case('n'): prvy = n(&file,&pocet_zaznamov,prvy,act);break;      //naèítanie záznamov zo súbora
            case('k'): k(&file,prvy,act);break;                             //vyèistenie pamäte, zatvorenie súboru a ukonèenie programu
            case('v'): v(&file,&pocet_zaznamov,prvy,act);break;             //vıpis záznamov
            case('p'): prvy = p(&file,&pocet_zaznamov,prvy,act,novy);break; //vloenie záznamu
            case('h'): prvy = h(&file,prvy,act);break;                      //vyh¾ada a vypísa záznamy pod¾a znaèky auta a ceny ponuky
            case('a'): prvy = a(&file,&pocet_zaznamov,prvy,act);break;      //aktualizácia záznamu pod¾a znaèky auta a roku vıroby
            case('z'): prvy = z(&file,&pocet_zaznamov,prvy,act,pred);break; //mazanie záznamov pod¾a znaèky auta
        }
    }
    return 0;
}
