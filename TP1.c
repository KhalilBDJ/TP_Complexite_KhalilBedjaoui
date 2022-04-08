#include <stdio.h>
#include <time.h>
#include <math.h>

/****************************MESURE TEMPS*************************************/

double mesureTemps(double (*fonction)(int), int n){

    clock_t deb, fin;
    double duree;


    deb = clock();
    (*fonction)(n);
    fin = clock();

    duree = ((double)(fin-deb))/CLOCKS_PER_SEC;

    return duree ;
}

void moyenneTemps(double (*fonction)(int), int n, int div){
    double temps;
    double moyenne=0;

    for(int i=1; i<=div; i++){
        temps = mesureTemps((*fonction),n);
        moyenne+=temps;
        printf("%lf\n",temps);
    }
    printf("Temps pour n=%d : %lf\n",n,moyenne/div);
}

/*************************FONCTIONS EXERCICE 1********************************/
void hanoi(int n, char A, char B, char C){
    if(n==1){

    }
    else{
        hanoi(n-1,A,C,B);
        hanoi(n-1,B,A,C);
    }
}

/*************************FONCTIONS EXERCICE 2********************************/

int iter(int n){

    int r=1;
    int un1=1, un2=1;
    int i;
    for(i=1; i<=n-1; i++){
        r = un1 + un2;
        un2 = un1;
        un1 = r;
    }
    return(r);
}

int recur(int n){
    if(n== 1 || n==0){
        return(1);
    }
    else{
        return(recur(n-1)+recur(n-2));
    }
}

double opti(int n){
    double A,B;
    n = n + 1;
    A = (1+sqrt(5))/2;
    B = (1-sqrt(5))/2;
    return((1/sqrt(5))*pow(A,n) - (1/sqrt(5))*pow(B,n));
}

/*************************FONCTIONS EXERCICE 3********************************/

void crible(int *A, int n){

    int i,j;

    for(i=2; i<n; i++){
        if(A[i] != -1){
            for(j=i+1; j<n; j++){
                if(A[j]%A[i] == 0){
                    A[j] = -1;
                }
            }
        }
    }
}

double mesureTempsCrible(int *A, int n){

    clock_t deb, fin;
    double duree;


    deb = clock();
    crible(A,n);
    fin = clock();

    duree = ((double)(fin-deb))/CLOCKS_PER_SEC;

    return duree ;
}


/******************************** MAIN ***************************************/

int main(){

//EXERCICE 1
#if 0
    moyenneTemps(&tourDeHanoi,34,5);
#endif

//EXERCICE 2
#if 0
//moyenneTemps(&iter,100000,5);
//moyenneTemps(&recur,45,5);
//moyenneTemps(&opti,pow(10,10),5);
#endif

//EXERCICE 3
#if 0
    int i, m=500000, n=m;
    int A[m];
    double temps, moyenne=0;

    //Initialisation du tableau
    A[0] = -1;
    A[1] = -1;
    for(i=2; i<m; i++){
        A[i] = i;
    }

    //On effectue la moyenne des temps sur 5 r�p�titions
    for(int i=1; i<=5; i++){
        temps = mesureTempsCrible(A,n);
        moyenne+=temps;
        printf("%lf\n",temps);
    }
    printf("Temps pour n=%d : %lf\n",n,moyenne/5);

#endif
    return(0);

}
