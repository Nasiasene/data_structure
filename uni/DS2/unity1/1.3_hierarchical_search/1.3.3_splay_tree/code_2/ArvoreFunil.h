#ifndef _ArvoreFunil_
#define _ArvoreFunil_

#include <stdio.h>   

typedef struct rotNoFunil {
        struct rotNoFunil *esquerda, *direita;
        int chave;
    } tNo, *tArvoreFunil;


extern void IniciaArvoreFunil(tArvoreFunil *arvore);
extern int NumeroNosArvoreFunil(tArvoreFunil arvore);
extern int ProfundidadeArvoreFunil(tArvoreFunil arvore);
extern int BuscaArvoreFunil(tArvoreFunil *arvore, int chave);
extern int InsereNoArvoreFunil( tArvoreFunil *arvore, int chave);
extern int RemoveNoArvoreFunil(tArvoreFunil *arvore, int chave);
extern int EstaVaziaLSE(tArvoreFunil arvore);
extern void DestroiArvoreBin(tArvoreFunil arvore);
extern void ImprimeInfixa(tArvoreFunil arvore);
extern void ImprimePrefixa(tArvoreFunil arvore);
extern int MenorChave(tArvoreFunil p);
extern int MaiorChave(tArvoreFunil p);

#endif
