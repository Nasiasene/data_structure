#ifndef _TABELAINDEXADA_H_
#define _TABELAINDEXADA_H_

typedef struct rotDado{
    int matricula; //key
    char nome[71];
    } tDados;

typedef struct rotTabIdx tTabelaIdx;

extern tTabelaIdx * CriaTabelaIdx(void);
extern void DestroiTabelaIdx(tTabelaIdx * tabela);
extern int ComprimentoIdx(tTabelaIdx * tabela);
extern tDados ObtemElementoIdx(tTabelaIdx * tabela, int indice);
extern tDados RemoveElementoIdx(tTabelaIdx * tabela, int indice);
extern int EstaVaziaIdx(tTabelaIdx * tabela);
extern void AcrescentaElementoIdx(tTabelaIdx * tabela, const tDados *elemento);
extern void OrdenaBolha(tTabelaIdx *tab);
extern int BuscaBinaria(tTabelaIdx *tab, int chave);
extern int BuscaInterpolacao(tTabelaIdx *tab, int chave);
extern int QuantOperacoes();
#endif