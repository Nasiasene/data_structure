#ifndef _ArvoreMultiDesc_
#define _ArvoreMultiDesc_

#include <stdio.h>   

#define POSICAO_NULA -1

typedef struct  { 
          int chave;  /* Chave do registro              */
          int indice; /* Posicao do registro no arquivo, deve-se multiplicar pelo tamanho de um registro */
} tChaveIndice;

//dimensionar arvore
   
#define TB 4096 //tamanho bloco no disco, 4KB verificando manualmente
#define TCI sizeof(tChaveIndice) //tamanho chave/indice
#define TI sizeof(int) //tamanho int no compilador

//#define Grau ((TB + TCI - TI)/(TCI + TI) - 1)
#define G 4

typedef struct {
           int          nFilhos; 
           tChaveIndice chaves[G - 1]; 
           int          filhos[G];
        } tNoMultiMS, *tArvoreMultiMS;


extern int BuscaMultiMS(FILE *stream, int chave);
extern int InsereMultiMS(int *posicaoRaiz, tChaveIndice *chaveEIndice, FILE *streamArvore);
extern int RemoveChaveMultiMS(FILE **streamArvore, int chave);
extern tChaveIndice MenorChaveMultiMS(FILE *streamArvore, int raiz);
extern void CaminhamentoInfixoMultiMS(FILE *streamArvore, int posNo, FILE *streamChaves);
extern void CaminhamentoPreMultiMS(FILE *streamArvore, int posNo, FILE *streamChaves);

#endif
