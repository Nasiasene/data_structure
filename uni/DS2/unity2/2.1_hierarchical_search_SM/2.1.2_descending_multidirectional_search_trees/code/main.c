#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArvoreMultiDesc.h"

void ImprimeTamanhosEstruturas(){
    printf("tamanho tNoMultiMS = %zu\n", sizeof(tNoMultiMS));
    printf("tamanho tChaveIndice = %zu\n", sizeof(tChaveIndice));
    printf("G = %d\n", G);
}

int main(){
    tArvoreMultiMS arvore;
    FILE *arqArvore;
    int pRaiz = POSICAO_NULA;

    //ImprimeTamanhosEstruturas();
    //return 0;

    srand(time(NULL));
    arqArvore = fopen("arvoreMultiDesc.bin", "wb+");
    if (!arqArvore){
        puts("erro ao abrir arquivo da arvore");
        return 1;
    }
    
    printf("Insercoes: \n");
    for(int i = 0; i < 15; i++){
        int chave = rand() % 20;
        tChaveIndice chaveIndice = {.chave=chave, .indice=-1};
        printf("inserir %d (enter para continuar)\n", chave);
        scanf("%*c");
        int r = InsereMultiMS(&pRaiz, &chaveIndice, arqArvore);
        if (r == 1){
            printf("\tInserida %d\n", chave);
        }else{
            printf("\tErro ao inserir %d (duplicada?)\n", chave);
        }
        printf("infixa: ");
        //ImprimeInfixa(arvore);
        CaminhamentoInfixoMultiMS(arqArvore, pRaiz, NULL);
        puts("");

        printf("prefixa: ");
        //ImprimePrefixa(arvore);
        CaminhamentoPreMultiMS(arqArvore, pRaiz, NULL);
        puts("");
    }

    printf("infixa: ");
    CaminhamentoInfixoMultiMS(arqArvore, pRaiz, NULL);
    puts("");

    printf("prefixa: ");
    CaminhamentoPreMultiMS(arqArvore, pRaiz, NULL);
    puts("");

    printf("Buscas: \n");
    for(int i = 0; i < 3; i++){
        int chave = rand() % 20;
        if ( chave != BuscaMultiMS(arqArvore, chave) ){
            printf("\tChave %d NAO encontrada\n", chave);
        }else{
            printf("\tChave %d encontrada\n", chave);
        }
    }

    printf("Remocoes: \n");
    for(int i = 0; i < 8; i++){
        int chave = rand() % 20;
        printf("\tRemover %d (enter para continuar)\n", chave);
        scanf("%*c");
        int r = RemoveChaveMultiMS(&arqArvore, chave);
        if (r == 1){
            printf("\tRemovida %d\n", chave);
        }else{
            printf("\tErro ao remover %d (nao existia ou arvore ficou vazia?)\n", chave);
        }
        printf("infixa: ");
        //ImprimeInfixa(arvore);
        CaminhamentoInfixoMultiMS(arqArvore, pRaiz, NULL);
        puts("");

        printf("prefixa: ");
        //ImprimePrefixa(arvore);
        CaminhamentoPreMultiMS(arqArvore, pRaiz, NULL);
        puts("");
    }

    printf("infixa: ");
    CaminhamentoInfixoMultiMS(arqArvore, pRaiz, NULL);
    puts("");

    printf("prefixa: ");
    CaminhamentoPreMultiMS(arqArvore, pRaiz, NULL);
    puts("");

    fclose(arqArvore);
    return 0;
}