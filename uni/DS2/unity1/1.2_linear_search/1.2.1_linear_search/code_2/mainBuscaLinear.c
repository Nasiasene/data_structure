#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaIndexada.h"

void RemoveQuebraLinha(char *str){
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

int CarregaArquivo(const char *arq, tTabelaIdx *tab){
    FILE *fp;
    char linha[101], *mat, *nome, *virg;
    int cont;
    tDados dado;

    fp = fopen(arq, "r");
    if (!fp){
        puts("Erro ao abrir arquivo.");
        exit(1);
    }

    cont = 0;
    while(1){
        fgets(linha, 101, fp);
        if (feof(fp)){
            break;
        }
        RemoveQuebraLinha(linha);
        virg = strchr(linha, ';');
        if (virg){
            *virg = '\0';
            mat = linha;
            nome = virg + 1;
            cont++;
            if (strlen(mat) >= 11){
                mat += 2;
            }
            //printf("%s/%s\n", mat, nome);
            dado.matricula = atoi(mat);
            strcpy(dado.nome, nome);
            AcrescentaElementoIdx(tab, &dado);
        }
    }

    fclose(fp);
    return cont;
}


int main(void){
    tTabelaIdx *tab;
    int q, mat;

    tab = CriaTabelaIdx();
    q = CarregaArquivo("../alunosCC.csv", tab);
    printf("%d discentes\n", q);
    printf("tamanho tabela: %d\n", ComprimentoIdx(tab));

    OrdenaBolha(tab);

    /*
    for(int i = 0; i < ComprimentoIdx(tab); i++){
        tDados dado = ObtemElementoIdx(tab, i);
        printf("%03d: %d/%s\n", i, dado.matricula, dado.nome);
    }
    */
    

   while(1){
        printf("Matricula: ");
        scanf("%d", &mat);

        int ind = BuscaBinaria(tab, mat);
        printf("Operacoes busca binaria: %d\n", QuantOperacoes());
        if (ind < 0){
            puts("discente nao encontrado");
        }else{
            tDados disc = ObtemElementoIdx(tab, ind);
            printf("%d/%s\n", disc.matricula, disc.nome);
        }

        ind = BuscaInterpolacao(tab, mat);
        printf("Operacoes busca inter: %d\n", QuantOperacoes());
        if (ind < 0){
            puts("discente nao encontrado");
        }else{
            tDados disc = ObtemElementoIdx(tab, ind);
            printf("%d/%s\n", disc.matricula, disc.nome);
        }

   }

    DestroiTabelaIdx(tab);
    return 0;
}