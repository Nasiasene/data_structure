#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ArvoveAVL.h"

#define MAIOR(a, b) (((a) > (b)) ? (a) : (b))
#define DEBUG 1

static tArvoreAVL RotacaoEsquerdaAVL(tArvoreAVL raiz){
   tArvoreAVL pivo = raiz->direita;

   raiz->direita = pivo->esquerda;
   pivo->esquerda = raiz;

      /* Atualiza as alturas */
   raiz->altura = MAIOR(AlturaAVL(raiz->esquerda), AlturaAVL(raiz->direita)) + 1;
   pivo->altura = MAIOR(AlturaAVL(pivo->esquerda), AlturaAVL(pivo->direita)) + 1;

   return pivo; /* Retorna a nova raiz */
}

static tArvoreAVL RotacaoDireitaAVL(tArvoreAVL raiz)
{
   tArvoreAVL pivo = raiz->esquerda;

   raiz->esquerda = pivo->direita;
   pivo->direita = raiz;

      /* Atualiza as alturas */
   raiz->altura = MAIOR(AlturaAVL(raiz->esquerda), AlturaAVL(raiz->direita)) + 1;
   pivo->altura = MAIOR(AlturaAVL(pivo->esquerda), AlturaAVL(pivo->direita)) + 1;

      /* Retorna a nova raiz */
   return pivo;
}

static int BalanceamentoAVL(tArvoreAVL pNo){
   return pNo ? AlturaAVL(pNo->esquerda) - AlturaAVL(pNo->direita) : 0;
}

int AlturaAVL(tArvoreAVL arvore){
   return arvore ? arvore->altura : 0;
}

void IniciaArvoreAVL(tArvoreAVL *arvore){
   *arvore = NULL;
}

tNoAVL *BuscaArvoreBB(tArvoreAVL arvore, int chave){ //mesmo que ABB
    tNoAVL *noAtual = arvore;

    while(noAtual){
        if (chave == noAtual->chave){
            return noAtual;
        }

        if (chave < noAtual->chave){
            noAtual = noAtual->esquerda;
        }else{
            noAtual = noAtual->direita;
        }
    }

    return NULL;
}

static tNoAVL *NovoNo(int chave){
    tNoAVL *novo = malloc(sizeof(tNoAVL));
    if (!novo)
        return NULL;
    
    novo->chave = chave;
    novo->esquerda = novo->direita = NULL;
    novo->altura = 1; //folha

    return novo;
}

tArvoreAVL InsereArvoreAVL(tArvoreAVL arvore, int chave){
    if (!arvore){ //arvore vazia
        arvore = NovoNo(chave);
        if (DEBUG) 
            puts("criou raiz");
        return arvore;
    }

    if (chave == arvore->chave){ //como eh recursivo, arvore aqui eh a subarvore sendo visitada
        if (DEBUG) 
            puts("chave ja existe");
        return arvore; //chave é primária (atencao, no livro estah NULL)
    }

    /* se chegou ate aqui, a arvore nao esta vazia, entao sera inserido recursivamente */
    if (chave < arvore->chave){
        if (DEBUG) 
            puts("insere esquerda");
        arvore->esquerda = InsereArvoreAVL(arvore->esquerda, chave);
    }else{
        if (DEBUG) 
            puts("insere direita");
        arvore->direita = InsereArvoreAVL(arvore->direita, chave);
    }

    //esse ponto eh atingido apos a insercao do novo no e retorno das recursoes 

    //atualizar altura da [sub]arvore 
    arvore->altura = MAIOR(AlturaAVL(arvore->esquerda), AlturaAVL(arvore->direita)) + 1;

    int balanceamento = BalanceamentoAVL(arvore); //balanceamento de um nó, diferenca das alturas
    if (DEBUG)
        printf("atualizou altura noh %d, balanceamento eh %d\n", arvore->chave, balanceamento);

    //examinar os 4 casos de desbalanceamento 

    if (balanceamento > 1){     //PERGUNTA: quantas vezes irah/poderah realizar ajustes/rotacoes?
        //esquerda-esquerda ou esquerda-direita

        if (chave < arvore->esquerda->chave){
            //esquerda-esquerda
            if (DEBUG) 
                puts("esquerda-esquerda");
            return RotacaoDireitaAVL(arvore);
        }

        if (chave > arvore->esquerda->chave){
            //esquerda-direita
            if (DEBUG) 
                puts("esquerda-direita");
            arvore->esquerda = RotacaoEsquerdaAVL(arvore->esquerda);
            return RotacaoDireitaAVL(arvore);
        }
    }

    if (balanceamento < -1){
        //direita-direita ou direita-esquerda

        if (chave > arvore->direita->chave){
            //direita-direita
            if (DEBUG) 
                puts("direita-direita");
            return RotacaoEsquerdaAVL(arvore);
        }

        if (chave < arvore->direita->chave){
            //direita-esquerda
            if (DEBUG) 
                puts("direita-esquerda");
            arvore->direita = RotacaoDireitaAVL(arvore->direita);
            return RotacaoEsquerdaAVL(arvore); 
        }
    }

    return arvore; //se chegou aqui nao precisou rebalanceamento
}

tArvoreAVL RemoveArvoreAVL(tArvoreAVL arvore, int chave){

    if (!arvore){
        if (DEBUG)
            puts("arvore vazia, nada a remover");
        return NULL; //arvore vazia, nao hao que remover
    }

    tArvoreAVL pNo = NULL; //no a ser liberado com free, o procurado ou o sucessor

    if (chave < arvore->chave){
        if (DEBUG) 
            puts("procurar e remover na arvore esquerda");
        arvore->esquerda = RemoveArvoreAVL(arvore->esquerda, chave);
    }else if (chave > arvore->chave){
        if (DEBUG) 
            puts("procurar e remover na arvore direita");
        arvore->direita = RemoveArvoreAVL(arvore->direita, chave);
    }else{ //arvore esta apontando para chave
        //chave encontrada
        if (DEBUG) 
            puts("achou a chave");
        if( (!arvore->esquerda) || (!arvore->direita) ) {
            /* Nó só possui um filho ou nenhum, pNo apontara para o nó filho
            a ser removido devido a substituicao do conteudo do pai por ele */
            pNo = arvore->esquerda ? arvore->esquerda : arvore->direita;

            if(!pNo) { 
                //sem filhos
                if (DEBUG) 
                    puts("no a remover nao tem filhos");
                pNo = arvore; //sem filhos, vai apenas dar o free
                arvore = NULL; // [sub]arvore ficou vazia, pai que chamou recursivamente apontara para NULL
            } else{ 
                //um filho
                if (DEBUG) 
                    puts("no a remover tem 1 filho");
                *arvore = *pNo; //copia conteudo (chave e filhos) desse unico filho para o pai
            }
            free(pNo); /* Libera o nó */
        } else { 
            //no a remover tem dois filhos
            if (DEBUG) 
                puts("no a remover tem 2 filhos");

            /* pNo apontará para o sucessor do nó a ser removido (seu substituto) 
            q precisará ser removido após seu conteúdo ser copiado para o no a ser removido 
            */
            pNo = arvore->direita; 
            while (pNo->esquerda){
                pNo = pNo->esquerda;
            }

            arvore->chave = pNo->chave; //apenas conteúdo do nó substituto substitui o nó a ser removido
            /* Após a substituicao do conteudo, o nó substituo precisa ser removido da arvore,
            seguindo as mesmas regras gerais. Essa remoção ocorre na árvore direita e pode alterá-la */
            if (DEBUG) 
                puts("remover o sucessor, que ja substituiu");
            arvore->direita = RemoveArvoreAVL(arvore->direita, pNo->chave);
        }
    }

    //[sub]arvore só tinha um nó (a raiz)
    if (!arvore){
        if (DEBUG) 
            puts("encerrando pq subarvore só tinha 1 nó raiz (no sem filhos foi removido)");
        return arvore;
    }

    //atualiza altura da [sub]arvore atual, o nó corrente
    arvore->altura = MAIOR(AlturaAVL(arvore->esquerda), AlturaAVL(arvore->direita)) + 1;
    int balanceamento = BalanceamentoAVL(arvore); //a arvore ficou desbalanceada?
    if (DEBUG)
        printf("atualizou altura noh %d, balanceamento eh %d\n", arvore->chave, balanceamento);


    //analisar os 4 casos de desbalanceamento?
    if (DEBUG) 
        printf("analisar balanceamento de %d(%d)\n", arvore->chave, balanceamento);

    //esquerda-esquerda
    if (balanceamento > 1 && BalanceamentoAVL(arvore->esquerda) >= 0){ // Atenção ao >= da operacao mais eficiente 
        if (DEBUG) 
            puts("esquerda-esquerda");
        return RotacaoDireitaAVL(arvore);
    }
    
    //esquerda-direita
    if (balanceamento > 1 && BalanceamentoAVL(arvore->esquerda) < 0) {
        if (DEBUG) 
            puts("esquerda-direita");
        arvore->esquerda =  RotacaoEsquerdaAVL(arvore->esquerda);
        return RotacaoDireitaAVL(arvore);
    }

    //direita-direita 
    if (balanceamento < -1 && BalanceamentoAVL(arvore->direita) <= 0){
        if (DEBUG) 
            puts("direita-direita");
        return RotacaoEsquerdaAVL(arvore);
    }

    //direita-esquerda
    if (balanceamento < -1 && BalanceamentoAVL(arvore->direita) > 0) {
        if (DEBUG) 
            puts("direita-esquerda");
        arvore->direita = RotacaoDireitaAVL(arvore->direita);
        return RotacaoEsquerdaAVL(arvore);
    }

    if (DEBUG) 
        puts("sem desbalanceamento");
    return arvore; /* Nao ocorreu desbalanceamento */
}

void ImprimeInfixa(tArvoreAVL arvore){
    if (!arvore)
        return;
    
    ImprimeInfixa(arvore->esquerda);
    printf("%d(%d) ", arvore->chave, BalanceamentoAVL(arvore));
    ImprimeInfixa(arvore->direita);
}

void ImprimePrefixa(tArvoreAVL arvore){
    if (!arvore)
        return;
    
    printf("%d(%d) ", arvore->chave, BalanceamentoAVL(arvore));
    ImprimePrefixa(arvore->esquerda);
    ImprimePrefixa(arvore->direita);
}
