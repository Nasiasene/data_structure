#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArvoreFunil.h"

int main(){
    tArvoreFunil arvore;

    srand(time(NULL));
    IniciaArvoreFunil(&arvore);
    
    printf("Insercoes: \n");
    for(int i = 0; i < 10; i++){
        int chave = rand() % 15;
        printf("inserir %d (enter para continuar)\n", chave);
        scanf("%*c");
        int r = InsereNoArvoreFunil(&arvore, chave);
        if (r == 0){
            printf("\tInserida %d\n", chave);
        }else{
            printf("\tErro ao inserir %d (duplicada?)\n", chave);
        }
        printf("infixa: ");
        ImprimeInfixa(arvore);
        puts("");

        printf("prefixa: ");
        ImprimePrefixa(arvore);
        puts("");
    }

    printf("infixa: ");
    ImprimeInfixa(arvore);
    puts("");

    printf("prefixa: ");
    ImprimePrefixa(arvore);
    puts("");

    printf("Buscas: \n");
    for(int i = 0; i < 3; i++){
        int chave = rand() % 15;
        if ( chave != BuscaArvoreFunil(&arvore, chave) ){
            printf("\tChave %d NAO encontrada\n", chave);
        }else{
            printf("\tChave %d encontrada\n", chave);
        }
    }

    printf("Remocoes: \n");
    for(int i = 0; i < 3; i++){
        int chave = rand() % 15;
        printf("\tRemover %d (enter para continuar)\n", chave);
        scanf("%*c");
        int r = RemoveNoArvoreFunil(&arvore, chave);
        if (r == 0){
            printf("\tRemovida %d\n", chave);
        }else{
            printf("\tErro ao remover %d (nao existia ou arvore ficou vazia?)\n", chave);
        }
        printf("infixa: ");
        ImprimeInfixa(arvore);
        puts("");

        printf("prefixa: ");
        ImprimePrefixa(arvore);
        puts("");
    }

    printf("infixa: ");
    ImprimeInfixa(arvore);
    puts("");

    printf("prefixa: ");
    ImprimePrefixa(arvore);
    puts("");

    return 0;
}