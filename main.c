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

struct inzeraty* n(FILE **file,int *pocet_zaznamov, struct inzeraty *prvy)
{
    int pocitadlo=0,count=0,len;
    char str[201];

    *file = fopen( "auta.txt" , "r");

    if (*file)
    {
        while (fscanf(*file, "%s", str)!=EOF)
            if(str[0]=='$')
                pocitadlo++;

    }
    *pocet_zaznamov=pocitadlo;

    rewind(*file);

    struct inzeraty *act;
    prvy=NULL;
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
        len=strlen(act->kategoria);
        act->kategoria[len-1]='\0';

        fgets(act->znacka,51,*file);
        len=strlen(act->znacka);
        act->znacka[len-1]='\0';

        fgets(act->predajca,101,*file);
        len=strlen(act->predajca);
        act->predajca[len-1]='\0';

        fscanf(*file,"%d",&act->cena);
        fscanf(*file,"%*c");
        fscanf(*file,"%d",&act->rok_vyroby);
        fscanf(*file,"%*c");

        fgets(act->stav_vozidla,101,*file);
        len=strlen(act->stav_vozidla);
        act->stav_vozidla[len-1]='\0';

        act=act->dalsi;
        count++;
    }
        act->dalsi=NULL;

        printf("Podarilo sa nacitat %d prvkov\n",count);

    return prvy;
}
void v(FILE **file,int *pocet_zaznamov, struct inzeraty *prvy)
{
    int count=1;
    struct inzeraty *act;
    act = prvy;
     while(act != NULL)
    {
        if(count==*pocet_zaznamov+1)
            break;
        printf("%d.\n",count);
        printf("kategoria: %s\n",act->kategoria);
        printf("znacka: %s\n",act->znacka);
        printf("predajca: %s\n",act->predajca);
        printf("cena: %d\n",act->cena);
        printf("rok vyroby: %d\n",act->rok_vyroby);
        printf("stav vozidla: %s\n",act->stav_vozidla);

        act=act->dalsi;
        count++;
    }
}

struct inzeraty* p(FILE **file, int *pocet_zaznamov, struct inzeraty *prvy)
{
    int k,poc=0;
    struct inzeraty *act;
    struct inzeraty *novy;
    scanf("%d",&k);

    if(k<0)
        return 0;

    if(k>*pocet_zaznamov)
        k=*pocet_zaznamov+1;
    act=prvy;

    while(act!=NULL)
    {
        poc++;

        if(k==poc+1||k==1)
        {
            novy=malloc(sizeof(struct inzeraty));
                scanf("%*c");
                printf("Mozes vypisovat\n");
                scanf("%s",novy->kategoria);
                scanf("%s",novy->znacka);
                scanf("%s",novy->predajca);
                scanf("%d",&novy->cena);
                scanf("%*c");
                scanf("%d",&novy->rok_vyroby);
                scanf("%*c");
                scanf("%s",novy->stav_vozidla);
            if(act==prvy)
            {
                novy->dalsi=prvy;
                prvy=novy;
            }
            else
            {
                novy->dalsi=act->dalsi;
                act->dalsi=novy;
            }
            break;
        }
        act=act->dalsi;
    }*pocet_zaznamov+=1;

    return prvy;
}
struct inzeraty* h(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy)
{
    char znacka_auta[51],act_znacka[51];
    int cena_ponuky,count=0,i,j=0;
    struct inzeraty *act;

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

        if((strstr(act_znacka,znacka_auta)!=NULL)&&(act->cena<=cena_ponuky))
        {
            count++;
            printf("%d.\n",count);
            printf("kategoria: %s\n",act->kategoria);
            printf("znacka: %s\n",act->znacka);
            printf("predajca: %s\n",act->predajca);
            printf("cena: %d\n",act->cena);
            printf("rok vyroby: %d\n",act->rok_vyroby);
            printf("stav vozidla: %s\n",act->stav_vozidla);
        }
        act=act->dalsi;
    }
    if(count==0)
        printf("V ponuke nie su pozadovane auta\n");

    return prvy;
}
void k(FILE **file)
{
    if(file!=NULL)
        fclose(*file);
    //free(prvy);
    exit(EXIT_SUCCESS);
}
int main()
{
    FILE *file;
    struct inzeraty *prvy;
    int pocet_zaznamov=0;
    char c;
    while(1)
    {
        scanf("%c",&c);
        switch(c)
        {
            case('n'): prvy = n(&file,&pocet_zaznamov,prvy);break;
            case('k'): k(&file);break;
            case('v'): v(&file,&pocet_zaznamov,prvy);break;
            case('p'): prvy = p(&file,&pocet_zaznamov,prvy);break;
            case('h'): prvy = h(&file,&pocet_zaznamov,prvy);break;
        }
    }
    return 0;
}
