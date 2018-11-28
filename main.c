#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct inzeraty
{
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
    int pocetZaznamov=0,dlzkaStringu;
    char str[201];

    if((*file = fopen("auta.txt","r"))==NULL)
    {
        printf("Nepodarilo sa otvorit subor\n");
        return 0;
    }

    if (*file)
    {
        while (fscanf(*file, "%s", str)!=EOF)
            if(str[0]=='$')
                pocetZaznamov++;
    }
    *pocet_zaznamov=pocetZaznamov;

    rewind(*file);

    if((prvy = malloc(sizeof(struct inzeraty))) == NULL)
    {
        printf("Malo pamate.\n");
        return 0;
    }

    act=prvy;
    while(!feof(*file))
    {
        if((act->dalsi = malloc(sizeof(struct inzeraty))) == NULL)
        {
            printf("Malo pamate.\n");
            break;
        }
        fscanf(*file,"%*c");
        fscanf(*file,"%*c");

        fgets(act->kategoria,51,*file);
        dlzkaStringu=strlen(act->kategoria);
        act->kategoria[dlzkaStringu-1]='\0';

        fgets(act->znacka,51,*file);
        dlzkaStringu=strlen(act->znacka);
        act->znacka[dlzkaStringu-1]='\0';

        fgets(act->predajca,101,*file);
        dlzkaStringu=strlen(act->predajca);
        act->predajca[dlzkaStringu-1]='\0';

        fscanf(*file,"%d",&act->cena);
        fscanf(*file,"%*c");
        fscanf(*file,"%d",&act->rok_vyroby);
        fscanf(*file,"%*c");

        fgets(act->stav_vozidla,101,*file);
        dlzkaStringu=strlen(act->stav_vozidla);
        act->stav_vozidla[dlzkaStringu-1]='\0';

        act=act->dalsi;
    }
    printf("Podarilo sa nacitat %d prvkov\n",pocetZaznamov);
    return prvy;
}
void v(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act)
{
    int poradie=1;

    act = prvy;

    while(act != NULL)
    {
        if(poradie==*pocet_zaznamov+1)
            break;
        printf("%d.\n",poradie);
        printf("kategoria: %s\n",act->kategoria);
        printf("znacka: %s\n",act->znacka);
        printf("predajca: %s\n",act->predajca);
        printf("cena: %d\n",act->cena);
        printf("rok vyroby: %d\n",act->rok_vyroby);
        printf("stav vozidla: %s\n",act->stav_vozidla);

        act=act->dalsi;
        poradie++;
    }
}
struct inzeraty* p(FILE **file, int *pocet_zaznamov, struct inzeraty *prvy,struct inzeraty *act,struct inzeraty *novy)
{
    int k,pocitadlo=0;
    scanf("%d",&k);

    if(k<=0)
        return 0;

    if(k>*pocet_zaznamov)
        k=*pocet_zaznamov+1;

    novy=malloc(sizeof(struct inzeraty));

    scanf("%*c");
    scanf("%s",novy->kategoria);
    scanf("%s",novy->znacka);
    scanf("%s",novy->predajca);
    scanf("%d",&novy->cena);
    scanf("%*c");
    scanf("%d",&novy->rok_vyroby);
    scanf("%*c");
    scanf("%s",novy->stav_vozidla);

    if(*pocet_zaznamov==0)
    {
        novy->dalsi=NULL;
        *pocet_zaznamov+=1;
        return novy;

    }
        act=prvy;

    while(act!=NULL)
    {
        pocitadlo++;
        if(act==prvy&&k==1)
        {
            novy->dalsi=prvy;
            prvy=novy;
        }
        else
        if(k==pocitadlo+1)
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

    scanf("%s",znacka_auta);
    scanf("%d",&cena_ponuky);

    act=prvy;
    while(znacka_auta[j])
        {
            if (znacka_auta[j]<'A'||znacka_auta[j]>'Z')
                znacka_auta[j]=znacka_auta[j]-32;
            j++;
        }

    while(act!=NULL)
    {
        i=0;
        sprintf(act_znacka,"%s",act->znacka);

        while(act_znacka[i])
        {
            if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                act_znacka[i]=act_znacka[i]-32;
            i++;
        }

        if((strcmp(act_znacka,znacka_auta)==0)&&(act->cena<=cena_ponuky))
        {
            poradie++;
            printf("%d.\n",poradie);
            printf("kategoria: %s\n",act->kategoria);
            printf("znacka: %s\n",act->znacka);
            printf("predajca: %s\n",act->predajca);
            printf("cena: %d\n",act->cena);
            printf("rok vyroby: %d\n",act->rok_vyroby);
            printf("stav vozidla: %s\n",act->stav_vozidla);
        }
        act=act->dalsi;
    }
    if(poradie==0)
        printf("V ponuke nie su pozadovane auta\n");
    return prvy;
}
struct inzeraty* a(FILE **file,struct inzeraty *prvy,struct inzeraty *act)
{
    int rokVyroby,pocitadlo=0,j=0,i;
    char znacka_auta[51],act_znacka[51];

    scanf("%s",znacka_auta);
    scanf("%d",&rokVyroby);

    act=prvy;

    while(znacka_auta[j])
        {
            if (znacka_auta[j]<'A'||znacka_auta[j]>'Z')
                znacka_auta[j]=znacka_auta[j]-32;
            j++;
        }

    while(act!=NULL)
    {
        i=0;
        sprintf(act_znacka,"%s",act->znacka);

        while(act_znacka[i])
        {
            if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                act_znacka[i]=act_znacka[i]-32;
            i++;
        }

        if(strcmp(act_znacka,znacka_auta)==0&&act->rok_vyroby==rokVyroby)
        {
            if(act->cena-100<0)
                act->cena=0;
                else
                act->cena-=100;
            pocitadlo++;
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

    scanf("%s",znacka_auta);

    while(znacka_auta[j])
    {
        if (znacka_auta[j]<'A'||znacka_auta[j]>'Z')
            znacka_auta[j]=znacka_auta[j]-32;
        j++;
    }

    act=prvy;
    while(act!=NULL)
    {
        i=0;
        sprintf(act_znacka,"%s",act->znacka);
        while(act_znacka[i])
        {
            if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                act_znacka[i]=act_znacka[i]-32;
            i++;
        }
        if(strstr(act_znacka,znacka_auta)!=NULL)
        {
            if(act==prvy)
                prvy=prvy->dalsi;
                else
                {
                    pred=prvy;
                    while(pred->dalsi!=act)
                        pred=pred->dalsi;
                    pred->dalsi=act->dalsi;
                }
            free(act);
            *pocet_zaznamov-=1;
            pocitadlo++;
        }
        act=act->dalsi;
    }
    printf("Vymazalo sa %d zaznamov\n",pocitadlo);
    return prvy;
}
void k(FILE **file,struct inzeraty *prvy,struct inzeraty *act)
{
    if(*file!=NULL)
        fclose(*file);

    act=prvy->dalsi;
    while(act!=NULL)
    {
        free(prvy);
        prvy=act;
        act=act->dalsi;
    }
    exit(EXIT_SUCCESS);
}
int main()
{
    FILE *file=NULL;
    struct inzeraty *prvy;
    struct inzeraty *act;
    struct inzeraty *pred;
    struct inzeraty *novy;

    int pocet_zaznamov=0;
    char c;
    while(1)
    {
        scanf("%c",&c);
        switch(c)
        {
            case('n'): prvy = n(&file,&pocet_zaznamov,prvy,act);break;
            case('k'): k(&file,prvy,act);break;
            case('v'): v(&file,&pocet_zaznamov,prvy,act);break;
            case('p'): prvy = p(&file,&pocet_zaznamov,prvy,act,novy);break;
            case('h'): prvy = h(&file,prvy,act);break;
            case('a'): prvy = a(&file,prvy,act);break;
            case('z'): prvy = z(&file,&pocet_zaznamov,prvy,act,pred);break;
        }
    }
    return 0;
}
