#include <stdio.h>
#include <stdlib.h>
#include "tabelaIndexada.h"

struct rotTabIdx {
    tDados *elementos;   /* Ponteiro para o array que contem os elementos */
    int    nElementos;   /* Numero de elementos */
    int    tamanhoArray;
};

static int qOperacoes = 0;

tTabelaIdx * CriaTabelaIdx(void){
    tTabelaIdx * tabela;

        /* Aloca espaco para a estrutura que armazena a tabela */
    tabela = malloc(sizeof(struct rotTabIdx));
    if (!tabela){
        puts("Erro ao alocar tabela.");
        exit(1);
    }

    tabela->elementos = calloc(1, sizeof(tDados)); //aloca elementos
    if (!tabela->elementos){
        puts("Erro ao alocar elementos.");
        exit(1);
    }

    tabela->tamanhoArray = 1;
    tabela->nElementos = 0;

    return tabela;
}

void DestroiTabelaIdx(tTabelaIdx * tabela){
    free(tabela->elementos);
    free(tabela);
}

int ComprimentoIdx(tTabelaIdx * tabela){
    return tabela->nElementos; 
}

tDados ObtemElementoIdx(tTabelaIdx * tabela, int indice){
    if (indice < 0 || indice >= tabela->nElementos){
        puts("Indice inexistente para obtencao.");
        exit(1);
    }

    return tabela->elementos[indice];
}

tDados RemoveElementoIdx(tTabelaIdx * tabela, int indice){
    tDados itemRemovido;

    if (indice < 0 || indice >= tabela->nElementos){
        puts("Indice inexistente para remocao.");
        exit(1);
    }

    itemRemovido = tabela->elementos[indice];
    for (int i = indice; i < tabela->nElementos - 1; i++)
        tabela->elementos[i] = tabela->elementos[i + 1];

    tabela->nElementos--; 

    return itemRemovido;
}

int EstaVaziaIdx(tTabelaIdx * tabela){
    return tabela->nElementos == 0;
}

void AcrescentaElementoIdx(tTabelaIdx * tabela, const tDados *elemento){
    tDados *novoArray; 

    if (tabela->nElementos >= tabela->tamanhoArray) { //array completo
        tabela->tamanhoArray *= 2;

        novoArray = realloc(tabela->elementos,
                            tabela->tamanhoArray*sizeof(tDados));

        if (!novoArray){
            puts("Erro ao realocar tabela.");
            exit(1);
        }

        tabela->elementos = novoArray;
    }

    tabela->elementos[tabela->nElementos] = *elemento;

    ++tabela->nElementos;
}

void OrdenaBolha(tTabelaIdx *tab){
    int trocou = 1;

    while(trocou){
        trocou = 0;
        for(int i = 0; i < ComprimentoIdx(tab) - 1; i++){
            if (tab->elementos[i].matricula > tab->elementos[i+1].matricula){
                tDados aux = tab->elementos[i];
                tab->elementos[i] = tab->elementos[i+1];
                tab->elementos[i+1] = aux;
                trocou = 1;
            }
        }
    }
}

int BuscaBinaria(tTabelaIdx *tab, int chave){
    int inf = 0, sup = tab->nElementos-1;
    int meio;

    qOperacoes = 0;
    meio = inf + (sup - inf) / 2;

    while (inf <= sup){
        if (chave == tab->elementos[meio].matricula)
            return meio;
        if (chave > tab->elementos[meio].matricula){
            inf = meio + 1;
        }else{
            sup = meio - 1;
        }
        meio = inf + (sup - inf) / 2;
        qOperacoes++;
    }

    return -1;
}

int BuscaInterpolacao(tTabelaIdx *tab, int chave){
    int inf = 0, sup = tab->nElementos-1;
    int meio;

    qOperacoes = 0;
    meio = inf + (sup - inf) * (chave - tab->elementos[inf].matricula)/(tab->elementos[sup].matricula - tab->elementos[inf].matricula);

    while (inf <= sup){
        if (chave == tab->elementos[meio].matricula)
            return meio;
        if (chave > tab->elementos[meio].matricula){
            inf = meio + 1;
        }else{
            sup = meio - 1;
        }
        meio = inf + (sup - inf) * (chave - tab->elementos[inf].matricula)/(tab->elementos[sup].matricula - tab->elementos[inf].matricula);
        qOperacoes++;
    }

    return -1;
}

int QuantOperacoes(){
    return qOperacoes;
}