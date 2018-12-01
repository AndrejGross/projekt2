#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct inzeraty
{
//zadefinovanie �trukt�ry
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

    if((*file=fopen("auta.txt","r"))==NULL) //otvorenie s�boru + kontrola
        return 0;

//po��tanie z�znamov na z�klade v�skytu znaku $
    if (*file)
    {
        while(fscanf(*file,"%s",str)!=EOF)
            if(str[0]=='$')
                pocetZaznamov++;
    }
    *pocet_zaznamov=pocetZaznamov; //po�et z�znamov prirad�m smern�ku

    rewind(*file); //na za�iatok s�boru

    if((prvy=malloc(sizeof(struct inzeraty)))==NULL) //alokujem prvy z�znam
        return 0;

    act=prvy;
    while(!feof(*file)) //po koniec s�boru na��tava hodnoty zo s�bora do z�znamov
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

        if((act->dalsi=malloc(sizeof(struct inzeraty)))==NULL) //alokujem miesto pre �al�i z�znam
            return 0;

        act=act->dalsi; //pos�vanie sa v medzi z�znammi
    }
    printf("Nacitalo sa %d zaznamov\n",pocetZaznamov);

    return prvy; //vraciam smernik na prv� z�znam
}
void v(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act)
{
    int poradie=1;

    act=prvy;
    while(act!=NULL) //vypisovanie z�znamov k�m nieje aktu�lny z�znam pr�zdny
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
        poradie++; //po��tadlo pre poradie
    }
}
struct inzeraty* p(FILE **file,int *pocet_zaznamov,struct inzeraty *prvy,struct inzeraty *act,struct inzeraty *novy)
{
    int k,pocitadlo=0;
    scanf("%d",&k);

    if(k<=0) //ak je na��tan� ��slo men�ie alebo rovn� nule, funkcia nepokra�uje
        return 0;

    if(k>*pocet_zaznamov) //ak je po�et z�znamov v��� ako na��tan� ��slo, z�znam sa zap�e na koniec
        k=*pocet_zaznamov+1;

    if((novy=malloc(sizeof(struct inzeraty)))==NULL)
       return 0;

//na��tavanie nov�ho z�znam
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

    if(*pocet_zaznamov==0) //ak je po�et z�znamov 0, tak sa nov� z�znam ulo�� na prvn� miesto
    {
        novy->dalsi=NULL;
        *pocet_zaznamov+=1;
        return novy;

    }
        act=prvy;

    while(act!=NULL)
    {
        pocitadlo++;
        if(act==prvy&&k==1) //ak chceme ulo�i� z�znam na prv� miesto
        {
            novy->dalsi=prvy;
            prvy=novy;
        }
        else
        if(k==pocitadlo+1) //ak chceme ulo�i� z�znam na hoci ak� in� miesto
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
    scanf("%[^\n]",znacka_auta); //na��tanie zna�ky auta
    scanf("%*c");
    scanf("%d",&cena_ponuky); //na��tanie ceny

    while(znacka_auta[j]) //zmena na ve�k� p�smen�
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
        sprintf(act_znacka,"%s",act->znacka); //vytvorenie pomocnej pre aktu�lnu zna�ku prvku

        while(act_znacka[i])  //zmena na ve�k� p�smen�
        {
            if(act_znacka[i]!=' ')
            {
                 if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                    act_znacka[i]=act_znacka[i]-32;
            }
            i++;
        }

        if((strcmp(act_znacka,znacka_auta)==0)&&(act->cena<=cena_ponuky))   //ak je lex. d�ka zhodn�
        {                                                                   //a z�rove� cena auta je men�ia
            poradie++;                                                      //alebo rovn� zadanej tak z�znam vyp�e
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
    if(poradie==0) //ak nieje �iadny z�znam vyhovuj�ci
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

    if(*pocet_zaznamov==0) //ak je po�et z�znamov 0, funkcia nepokra�uje
        {
            printf("Aktualizovalo sa %d zaznamov\n",pocitadlo);
            return 0;
        }

    act=prvy;

    while(znacka_auta[j]) //na ve�k� p�smen�
        {
            if (znacka_auta[j]<'A'||znacka_auta[j]>'Z')
                znacka_auta[j]=znacka_auta[j]-32;
            j++;
        }

    while(act!=NULL)
    {
        i=0;
        sprintf(act_znacka,"%s",act->znacka); //vytvorenie pomocnej pre aktu�lnu zna�ku

        while(act_znacka[i]) //na ve�k� p�smen�
        {
            if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                act_znacka[i]=act_znacka[i]-32;
            i++;
        }

        if(strcmp(act_znacka,znacka_auta)==0&&act->rok_vyroby==rokVyroby)   //ak je lex. d�ka zhodn�
        {                                                                   //a zadan� rok v�roby sa zhoduje
            if(act->cena-100<0)                                             //s rokom v�roby auta tak sa z�znam vyp�e
                act->cena=0;
                else
                act->cena-=100;
            pocitadlo++; //po��tadlo pre vyhovuj�ce z�znamy
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
    scanf("%[^\n]",znacka_auta); //na��tanie zna�ky auta
    scanf("%*c");

    while(znacka_auta[j]) //na ve�k� p�smen�
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
        sprintf(act_znacka,"%s",act->znacka); //vytvorenie pomocnej pre aktu�lnu zna�ku auta
        while(act_znacka[i])
        {
            if(act_znacka[i]!=' ')
            {
                if (act_znacka[i]<'A'||act_znacka[i]>'Z')
                    act_znacka[i]=act_znacka[i]-32;
            }
            i++;
        }
        if(strstr(act_znacka,znacka_auta)!=NULL) //ak sa string znacka_auta nach�dza v zna�ke auta aktu�lneho z�znamu
        {
            if(act==prvy) //ak je aktu�lny z�znam z�rove� aj prv�
            {
                prvy=prvy->dalsi; //nasleduj�ci z�znam po prvom sa st�va prv�m
            }
            else
            {
                pred=prvy;              //ak nie akt. z�znam prv�, tak predch�dzaj�ci je prv�
                while(pred->dalsi!=act) //k�m sa predch�dzaj�ci �al�� nerovn� aktu�lnemu z�znamu
                    pred=pred->dalsi;   //prehlad�vanie medzi z�znammi

                pred->dalsi=act->dalsi; //ak je predch�dzaj�ci �al�� rovn� aktu�lnemu z�znamu, tak akt. �al�� je pred. �al��
            }
            *pocet_zaznamov-=1; //odpo��ta 1 z po�tu prvkov
            free(act);          //odstr�� aktu�lny z�znam
            pocitadlo++;        //po��tadlo pre po�et vymazan�ch z�znamov
        }
        act=act->dalsi; //prech�dzanie z�znammi
    }
    printf("Vymazalo sa %d zaznamov\n",pocitadlo);

    return prvy;
}
void k(FILE **file,struct inzeraty *prvy,struct inzeraty *act)
{
    if(*file!=NULL) //ak bol s�bor otvoren�, tak s�bor zavrie
        fclose(*file);

//mazanie z�znamov
    act=prvy->dalsi;
    while(act!=NULL)
    {
        free(prvy);
        prvy=act;
        act=act->dalsi;
    }
    exit(EXIT_SUCCESS); //ukon�enie programu
}
int main()
{
    int pocet_zaznamov=0;
    char c;

    FILE *file=NULL; //zadefinovanie s�boru

    //zadefinovanie pointrov na �trukt�ru
    struct inzeraty *prvy;
    struct inzeraty *act;
    struct inzeraty *pred;
    struct inzeraty *novy;

    while(1) //nekone�n� cyklus
    {
        scanf("%c",&c); //na��tavanie znaku pre volanie funkcie
        switch(c)       //switch pre vyberanie funkcie
        {
            case('n'): prvy = n(&file,&pocet_zaznamov,prvy,act);break;      //na��tanie z�znamov zo s�bora
            case('k'): k(&file,prvy,act);break;                             //vy�istenie pam�te, zatvorenie s�boru a ukon�enie programu
            case('v'): v(&file,&pocet_zaznamov,prvy,act);break;             //v�pis z�znamov
            case('p'): prvy = p(&file,&pocet_zaznamov,prvy,act,novy);break; //vlo�enie z�znamu
            case('h'): prvy = h(&file,prvy,act);break;                      //vyh�ada� a vyp�sa� z�znamy pod�a zna�ky auta a ceny ponuky
            case('a'): prvy = a(&file,&pocet_zaznamov,prvy,act);break;      //aktualiz�cia z�znamu pod�a zna�ky auta a roku v�roby
            case('z'): prvy = z(&file,&pocet_zaznamov,prvy,act,pred);break; //mazanie z�znamov pod�a zna�ky auta
        }
    }
    return 0;
}
