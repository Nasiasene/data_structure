#include <stdio.h>

#define SORTE 2 //constante
float pi= 3.14; //global


void teste_func(int var){
    printf("\nPI: %f\nSorte: %d\nVar: %d\n", pi, SORTE, var);
} 

typedef struct{
   char nome[30];
    int dia, mes, ano;
} tRegistro;

int main(){
    tRegistro registroDaPessoa = {"Davi", 25, 4, 1998};
    registroDaPessoa.ano = 2003;

    tRegistro *ptrRegistro = &registroDaPessoa;
    ptrRegistro->mes = 8;
    (*ptrRegistro).dia = 10;

    printf("\n%i\n", registroDaPessoa.ano);
    printf("%i\n", ptrRegistro->dia);
    printf("%i\n", (*ptrRegistro).mes);
    printf("%s \n", ptrRegistro->nome);

    int var=22;
    teste_func(var);

    for(int i=0; i<=10; i++){
        if (i % 2 == 0){
            printf("\nE' Par: %d", i);
        }
        else {
            printf("\nE' Impar: %d", i);
        }
    }

    int i = 10;
    do {
        printf("\nI = %d", i);
        i--;
    } while (i == 10);
    
    return 0;
}