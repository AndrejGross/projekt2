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

struct inzeraty* n(FILE **file,int *pocet_zaznamov)
{
    int pocitadlo=0,count=0;
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

    struct inzeraty *prv;
    struct inzeraty *act;
    prv=NULL;
    if((prv = malloc(sizeof(struct inzeraty))) == NULL)
    {
        printf("Malo pamate.\n");
        return 0;
    }
    act=prv;
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
        fgets(act->znacka,51,*file);
        fgets(act->predajca,101,*file);
        fscanf(*file,"%d",&act->cena);
        fscanf(*file,"%*c");
        fscanf(*file,"%d",&act->rok_vyroby);
        fscanf(*file,"%*c");
        fgets(act->stav_vozidla,101,*file);

        act=act->dalsi;
        count++;
    }
        act->dalsi=NULL;

        printf("Podarilo sa nacitat %d prvkov\n",count);

    return prv;
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
        printf("kategoria: %s",act->kategoria);
        printf("znacka: %s",act->znacka);
        printf("predajca: %s",act->predajca);
        printf("cena: %d\n",act->cena);
        printf("rok vyroby: %d\n",act->rok_vyroby);
        printf("stav vozidla: %s\n",act->stav_vozidla);

        act=act->dalsi;
        count++;
    }
}

/*struct inzeraty* p(FILE **file, int *pocet_zaznamov, struct *prvy)
{
return prvy;
}*/

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
            case('n'): prvy = n(&file,&pocet_zaznamov);break;
            case('k'): k(&file);break;
            case('v'): v(&file,&pocet_zaznamov,prvy);break;
            //case('p'): prvy = p(&file,&pocet_zaznamov,prvy);break;
        }
    }
    return 0;
}
