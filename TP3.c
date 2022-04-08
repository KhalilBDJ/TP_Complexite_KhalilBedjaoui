#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** Effectue les opération de base**/
int operation(int a, int b, int choix)
{
    if(choix == 1){
        return(a+b);
    }
    else if(choix == 2 && a-b>=0){
        return(a-b);
    }
    else if(choix == 3){
        return(a*b);
    }
    else if(b!=0 && choix == 4 && a%b == 0){
        return(a/b);
    }
    else{
        return(-1);
    }
}

/** Affiche le caractère d'opération voulu**/
char* afficheChar(int choix)
{
    if(choix == 1){
        return("+");
    }
    else if(choix == 2){
        return("-");
    }
    else if(choix == 3){
        return("*");
    }
    else if(choix == 4){
        return("/");
    }
    else{
        return("?");
    }
}

/**Affiche un tableau d'entiers de longueur n**/
void printTab(int *t, int n)
{
    printf("{%d",t[0]);
    for(int i=1; i<n; i++){
        printf(", %d",t[i]);
    }
    printf("}\n");
}

/** Algorithme récursif de recherche**/
int recherche(int R, int *tab, int n, int nbPlaque)
{
    int i,j,k,m;
    int t[nbPlaque];

    for(i=0; i<n-1; i++){
        for(j=i+1; j<n; j++){
            for(k=1;k<=4;k++){

                for(m=0; m<nbPlaque; m++){
                    t[m] = tab[m];
                }

                t[i]=operation(tab[i],tab[j],k);//
                if (t[i] == -1){
                    continue;
                }

                for(m=j;m<n-1;m++){
                    t[m] = t[m+1];
                }

                if(t[i] == R){
                    printf("%d %c %d = %d\n", tab[i], *afficheChar(k),tab[j],t[i]);
                    return(1);
                }

                if(recherche(R,t,n-1,nbPlaque)){
                    printf("%d %c %d = %d\n", tab[i], *afficheChar(k),tab[j],t[i]);
                    return(1);
                }
            }
        }
    }
    return(0);
}

int tirageAleatoire(int tab[], int nb)
{
    int plaques[28] ={1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,25,25,50,50,75,75,100,100};
    int i,posAlea;

    srand(time(NULL));
    for(i=0; i<nb; i++){
        do{
            posAlea = rand()%28;
            tab[i] = plaques[posAlea];
        }while(plaques[posAlea]==-1);
        plaques[posAlea] = -1;
    }

    return rand()%900+100;
}


void compteEstBon(int nbPlaques){
    int R;
    int plaquesIni[nbPlaques];

    if(nbPlaques >28 || nbPlaques<1){
        printf("NOMBRE DE PLAQUES INCORRECTES");
        exit(0);
    }

    R = tirageAleatoire(plaquesIni,nbPlaques);


    printf("Voici les plaques :\n");
    printTab(plaquesIni,nbPlaques);
    printf("Resultat a trouver : %d\n",R);


    if(recherche(R, plaquesIni, nbPlaques, nbPlaques)==0){
        printf("Pas de solutions possibles...");
    }

}

/********************************MESURE TEMPS*************************************************************/


int rechercheDuree(int R, int *tab, int n, int nbPlaque)
{
    int i,j,k,m;
    int t[nbPlaque];


    for(i=0; i<n-1; i++){
        for(j=i+1; j<n; j++){
            for(k=1;k<=4;k++){

                for(m=0; m<nbPlaque; m++){
                    t[m] = tab[m];
                }

                t[i]=operation(tab[i],tab[j],k);
                if (t[i] == -1){
                    continue;
                }
                for(m=j;m<n-1;m++){
                    t[m] = t[m+1];
                }

                if(t[i] == R){
                    return(1);
                }

                if(rechercheDuree(R,t,n-1,nbPlaque)){

                    return(1);
                }
            }
        }
    }
    return(0);
}

double mesureTemps(int (*fonction)(int, int*, int, int), int R, int tab[], int n, int nbPlaque){

    clock_t deb, fin;
    double duree;


    deb = clock();
    (*fonction)(R,tab,n,nbPlaque);
    fin = clock();

    duree = ((double)(fin-deb))/CLOCKS_PER_SEC;

    return duree ;
}

double compteEstBonCalcul(int nbPlaques){
    int R;
    int plaquesIni[nbPlaques];

    R = tirageAleatoire(plaquesIni,nbPlaques);

    return(mesureTemps(&rechercheDuree,R,plaquesIni,nbPlaques,nbPlaques));
}

void moyenneTemps(int n, int div){

    double temps;
    double moyenne=0;

    for(int i=1; i<=div; i++){
        temps = compteEstBonCalcul(n);
        moyenne+=temps;
        printf("%lf\n",temps);
    }
    printf("Temps pour n=%d : %lf\n",n,moyenne/div);
}

int main()
{
    //compteEstBon(6);
    moyenneTemps(22,5);

    return 0;
}

