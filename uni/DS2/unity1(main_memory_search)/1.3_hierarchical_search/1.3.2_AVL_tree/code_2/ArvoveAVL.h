#ifndef _ArvoveAVL_H_
#define _ArvoveAVL_H_

typedef struct rotNoAVL {
        struct rotNoAVL *esquerda, *direita;
        int chave, altura;
    } tNoAVL, *tArvoreAVL;

extern void IniciaArvoreAVL(tArvoreAVL *arvore);
extern tNoAVL *BuscaArvoreBB(tArvoreAVL arvore, int chave);
extern tArvoreAVL InsereArvoreAVL(tArvoreAVL arvore, int chave);
extern tArvoreAVL RemoveArvoreAVL(tArvoreAVL arvore, int chave);
extern void ImprimeInfixa(tArvoreAVL arvore);
extern void ImprimePrefixa(tArvoreAVL arvore);
extern int AlturaAVL(tArvoreAVL arvore);

#endif