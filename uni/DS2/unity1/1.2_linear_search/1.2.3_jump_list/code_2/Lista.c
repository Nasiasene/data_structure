/****
 *
 * Exemplo: Listas Encadeadas com Saltos
 *
 * Se��o: 3.6
 *
 * Autor: Ulysses de Oliveira
 *
 * Data de Cria��o: 19/05/2015
 * �ltima modifica��o: 25/05/2015
 *
 * Entrada: V. exemplo de execu��o
 *
 * Sa�da: V. exemplo de execu��o
 *
 ****/

/************************ Includes ************************/

#include <stdio.h>    /* Entrada e sa�da  */
#include <stdlib.h>   /* Miscel�nea       */
#include <string.h>   /* Fun��es strXXX() */
#include <math.h>     /* Opera��es reais  */
#include <time.h>     /* Fun��o time()    */
#include "ASSEGURA.h" /* Macro ASSEGURA   */
#include "Lista.h"    /* Interface deste m�dulo */

/****************** Defini��es de Tipos *******************/

typedef enum {CARA, COROA} tCaraCoroa;

/********************* Fun��es Locais *********************/

/****
 *
 * CaraOuCoroa(): Simula o lan�amento de uma moeda
 *
 * Par�metros: Nenhum
 *
 * Retorno: CARA se o n�mero aleat�rio gerado for par;
 *          COROA se o n�mero aleat�rio gerado for �mpar
 *
 * Observa��es: Na primeira chamada desta fun��o, ela
 *              alimenta o gerador de n�meros aleat�rios
 *
 ****/
static tCaraCoroa CaraOuCoroa(void)
{
   static int primeiraChamada = 1;

   if (primeiraChamada) {
         /* Inicia o gerador de n�meros aleat�rios */
      srand(time(NULL));

         /* A pr�xima chamada n�o ser� mais a primeira */
      primeiraChamada = 0;
   }

      /* CARA corresponde a um n�mero par e COROA corresponde */
      /* a um n�mero �mpar, mas poderia ser o contr�rio       */
   return rand()%2 ? CARA : COROA;
}

/****
 *
 * ComprimentoPorNivel(): Calcula o n�mero de n�s de uma lista
 *                        com saltos num determinado n�vel
 *
 * Par�metros:
 *     lista (entrada) - lista com saltos cujo comprimento
 *                       ser� calculado
 *     nivel (entrada) - o referido n�vel
 *
 * Retorno: O n�mero de n�s da lista no n�vel especificado
 *
 ****/
static int ComprimentoPorNivel(tListaComSaltos lista, int nivel)
{
   int  tamanho = 0; /* Armazena o referido n�mero de n�s */
   tNoListaComSalto *ptrNo = lista.cabeca;

      /* Acessa cada n� da lista no n�vel especificado */
      /* e conta quantos n�s s�o acessados             */
   while (ptrNo->proximo[nivel] != lista.cabeca) {
      ++tamanho; /* Mais um n� foi encontrado */

         /* Passa para o pr�ximo n� neste n�vel */
      ptrNo = ptrNo->proximo[nivel];
   }

   return tamanho;
}

/******************* Fun��es de Depura��o *****************/

/****
 *
 * ApresentaComprimentosPorNivel(): Apresenta o n�mero de n�s
 *                                  de uma lista com saltos em
 *                                  cada n�vel
 *
 * Par�metros:
 *     lista (entrada) - a referida lista
 *
 * Retorno: Nada
 *
 ****/
void ApresentaComprimentosPorNivel(tListaComSaltos lista)
{
   int i,
       total = ComprimentoPorNivel(lista, 0);

   printf("\n>>> Numero total de nos: %d <<<\n", total);

   printf( "\nNivel\tComprimento\tEsperado"
           "\n=====\t===========\t========\n");

      /* Exibe na tela n�mero de n�s por n�vel da lista */
   for (i = 0; i < lista.nivelMax; ++i) {
      printf( "\n %2d\t  %6d\t %6d", i,
              ComprimentoPorNivel(lista, i),
             (int) lround(total/pow(2, i)) );
   }

   putchar('\n'); /* Embelezamento */
}

/****
 *
 * ApresentaRelacoesEntreNiveis(): Apresenta rela��es entre
 *                                 n�meros de n�s de uma lista
 *                                 com saltos em n�veis
 *                                 consecutivos
 *
 * Par�metros:
 *     lista (entrada) - a referida lista
 *
 * Retorno: Nada
 *
 ****/
void ApresentaRelacoesEntreNiveis(tListaComSaltos lista)
{
   int i, nos1, nos2;

   printf( "\n\n    *** Relacoes entre Numeros de Nos ***"
           "\n        =============================\n");

      /* Exibe na tela n�mero de n�s por n�vel da lista */
   for (i = 0; i < lista.nivelMax; ++i) {
      nos1 = ComprimentoPorNivel(lista, i);
      nos2 = ComprimentoPorNivel(lista, i + 1);

      printf( "\n>>> Nos no nivel %2d / Nos no nivel %2d:  ",
              i, i + 1);

      if (nos2) {
         printf("%6.4f", (double) nos1/nos2);
      } else {
         printf("------");
      }
   }

   putchar('\n'); /* Embelezamento */
}

/****
 *
 * ApresentaNiveis(): Apresenta o n�mero m�ximo de n�veis e o
 *                    n�mero efetivo de n�veis de uma lista
 *                    com saltos
 *
 * Par�metros:
 *     lista (entrada) - a referida lista
 *
 * Retorno: Nada
 *
 ****/
void ApresentaNiveis(tListaComSaltos lista)
{
   printf( "\n\t>>> Numero maximo de niveis na lista:   %d",
           lista.nivelMax + 1 );
   printf( "\n\t>>> Numero de niveis efetivos na lista: %d\n",
           lista.nivel + 1 );

   putchar('\n'); /* Embelezamento */
}

/********************* Fun��es Globais ********************/

/****
 *
 * IniciaListaComSaltos(): Inicia uma lista com saltos
 *
 * Par�metros:
 *     *lista (sa�da) - a lista que ser� iniciada
 *      maxRegs (entrada) - n�mero m�ximo de registros
 *                          esperados na lista
 *
 * Retorno: Nada
 *
 ****/
void IniciaListaComSaltos(tListaComSaltos *lista, int maxRegs)
{
   int i, nMax;

      /* Determina o n�vel m�ximo de um n� da lista */
   nMax = lista->nivelMax = (int) floor(log2(maxRegs) )+ 1;
   //printf("nMax = %d, maxRegs = %d\n", nMax, maxRegs);

      /* Aloca a cabe�a da lista */
   lista->cabeca = malloc(sizeof(tNoListaComSalto));

      /* Se a aloca��o n�o foi poss�vel, aborta o programa */
   ASSEGURA(lista->cabeca, "Nao foi possivel alocar cabeca");

      /* Aloca o array de ponteiros da cabe�a */
   lista->cabeca->proximo = malloc((nMax + 1)*sizeof(tNoListaComSalto *));

      /* Se a aloca��o n�o foi poss�vel, aborta o programa */
   ASSEGURA(lista->cabeca->proximo, "Nao foi possivel alocar cabeca");

      /* A lista � circular com cabe�a, de modo que, inicialmente, */
      /* cada ponteiro proximo[i] aponta para a cabe�a da lista    */
   for (i = 0; i <= lista->nivelMax; i++)
      lista->cabeca->proximo[i] = lista->cabeca;

   lista->nivel = 0; /* O n�vel corrente da lista � 0 */
}

/****
 *
 * EstaVaziaListaComSaltos(): Verifica se uma lista com saltos
 *                            est� vazia
 *
 * Par�metros:
 *     lista (entrada) - a lista que ser� verificada
 *
 * Retorno:
 *    1, quando a lista est� vazia;
 *    0, em caso contr�rio
 *
 ****/
int EstaVaziaListaComSaltos(tListaComSaltos lista)
{
      /* Todos os n�s da lista aparecem no n�vel 0. Logo, */
      /* se o ponteiro para o primeiro n� desse n�vel     */
      /* aponta para a cabe�a, a lista est� vazia.        */
   return lista.cabeca->proximo[0] == lista.cabeca;
}

/****
 *
 * ComprimentoListaComSalto(): Calcula o n�mero de n�s de uma
 *                             lista com saltos
 *
 * Par�metros:
 *     lista (entrada) - lista cujo comprimento ser� calculado
 *
 * Retorno: O n�mero de n�s da referida lista
 *
 ****/
int ComprimentoListaComSalto(tListaComSaltos lista)
{
   int  tamanho = 0; /* Armazena o n�mero de n�s da lista */
   tNoListaComSalto *ptrNo = lista.cabeca; /* Apontar� para cada */
                              /* n� da lista        */

      /* Acessa cada n� no primeiro n�vel da lista */
      /* e conta quantos n�s s�o acessados         */
   while (ptrNo->proximo[0] != lista.cabeca) {
      ++tamanho; /* Mais um n� foi encontrado */
      ptrNo = ptrNo->proximo[0]; /* Passa para o pr�ximo n� */
   }

   return tamanho;
}

/****
 *
 * BuscaListaComSaltos(): Retorna o endere�o do conte�do do
 *                        n� que possui uma determinada chave
 *                        numa lista com saltos
 *
 * Par�metros:
 *      lista (entrada) - lista que ser� pesquisada
 *      chave (entrada) - chave de busca
 *
 * Retorno: Valor associado � chave, se ela for encontrada;
 *          caso contr�rio, -1.
 *
 ****/
int BuscaListaComSaltos(tListaComSaltos lista, tCEP chave)
{
   int               i; /* Representar� um n�vel da lista  */
   tNoListaComSalto *ptrNo = lista.cabeca; /* Ponteiro utilizado para */
                                           /* visitar n�s da lista    */

      /* A busca come�a sempre no n�vel mais alto */
      /* da lista e termina sempre no n�vel 0     */
   for (i = lista.nivel; i >= 0; i--) {
         /* A busca prossegue no mesmo n�vel at� que a sentinela ou uma  */
         /* chave maior do que ou igual a chave de busca seja encontrada */
      while (ptrNo->proximo[i] != lista.cabeca &&
             strcmp(ptrNo->proximo[i]->conteudo.chave, chave) < 0)
            /* Passa para o pr�ximo n� no mesmo n�vel */
         ptrNo = ptrNo->proximo[i];
   }

   /*****************************************************/
   /* Neste ponto o pr�ximo n� no n�vel 0 adiante de    */
   /* ptrNo � a cabe�a da lista ou � o primeiro n� cuja */
   /* chave � maior do que ou igual � chave de busca    */
   /*****************************************************/

      /* Faz ptrNo apontar para a cabe�a da lista ou para o primeiro */
      /* n� cuja chave � maior do que ou igual a chave de busca      */
   ptrNo = ptrNo->proximo[0];

      /* Verifica se a chave foi encontrada */
   if ( ptrNo != lista.cabeca && !strcmp(ptrNo->conteudo.chave, chave) )
      return ptrNo->conteudo.valor; /* Chave encontrada */

   return -1; /* A chave n�o foi encontrada */
}

/****
 *
 * InsereListaComSaltos(): Insere um novo n� numa lista com saltos
 *
 * Par�metros:
 *    *lista (entrada/sa�da) - lista na qual ser� feita a inser��o
 *     conteudo (entrada) - conte�do do n� que ser� inserido
 *
 * Retorno: Endere�o do novo n� ou NULL se a chave do novo
 *          elemento j� se encontra na lista
 *
 * Observa��o: A chave � considerada prim�ria
 *
 ****/
tNoListaComSalto *InsereListaComSaltos(tListaComSaltos *lista, tCEP_Ind conteudo)
{
   int                i, /* Representar� um n�vel da lista */
                      novoNivel; /* N�vel do novo n� */
   tNoListaComSalto **enderecos, /* Apontar� para um array */
                                 /* de ponteiros para n�s  */
                     *novoNo, /* Ponteiro para o n� a ser criado */
                     *ptrNo; /* Ponteiro utilizado para visitar n�s da lista */

      /* Aloca um array auxiliar de ponteiros para n�s.  */
      /* Esses ponteiros apontar�o para n�s que ter�o    */
      /* ponteiros 'proximo' apontando para o novo n�.   */
   enderecos = calloc(lista->nivelMax + 1, sizeof(tNoListaComSalto *));

      /* Se o array n�o foi alocado aborta o programa */
   ASSEGURA(enderecos, "Nao foi possivel alocar array");

         /**********************************/
         /* Encontra a posi��o de inser��o */
         /**********************************/

   ptrNo = lista->cabeca; /* Faz ptrNo apontar para a cabe�a da lista */

      /* A busca come�a sempre no n�vel mais alto e termina no n�vel 0 */
   for (i = lista->nivel; i >= 0; i--) {
         /* A busca prossegue no mesmo n�vel at� que a sentinela ou uma  */
         /* chave maior do que ou igual a chave de busca seja encontrada */
      while ( ptrNo->proximo[i] != lista->cabeca &&
              strcmp(ptrNo->proximo[i]->conteudo.chave, conteudo.chave ) < 0)
         ptrNo = ptrNo->proximo[i]; /* Passa para o pr�ximo n� no mesmo n�vel */

         /* O array enderecos[] armazena o endere�o do */
         /* �ltimo n� visitado no n�vel i antes que    */
         /* se atinja o local da poss�vel inser��o     */
      enderecos[i] = ptrNo;
   }

      /* Verifica se a chave foi encontrada. Aqui, a chave */
      /* � considerada prim�ria e n�o ser� duplicada.      */
   if ( ptrNo->proximo[0] != lista->cabeca &&
        !strcmp( ptrNo->proximo[0]->conteudo.chave, conteudo.chave ) ) {

      /* A chave foi encontrada */

      free(enderecos); /* Este array n�o � mais necess�rio */

      return NULL; /* Retorna NULL indicando que n�o houve inser��o */
   }

      /* Determina o n�vel do novo n� por meio do lan�amento de uma moeda;  */
      /* i.e., enquanto o resultado do lan�amento for CARA, o n�vel do novo */
      /* n� vai aumentando (se preferir COROA, o resultado ser� o mesmo)    */
   for (novoNivel = 0; CaraOuCoroa() == CARA &&
                       novoNivel < lista->nivelMax; novoNivel++)
      ; /* Vazio */

   novoNo = malloc(sizeof(tNoListaComSalto));  /* Cria um n� novo */

      /* Se a aloca��o n�o ocorreu, aborta o programa */
   ASSEGURA(novoNo, "Impossivel criar um no'");

      /* Cria o array ponteiros do novo n� */
   novoNo->proximo = malloc((novoNivel + 1)*sizeof(tNoListaComSalto *));

      /* Se a aloca��o n�o ocorreu, aborta o programa */
   ASSEGURA(novoNo->proximo, "Impossivel criar um no'");

   novoNo->conteudo = conteudo; /* Armazena o conte�do do novo n� */

      /* Se o n�vel do novo n� for maior do que o n�vel   */
      /* corrente da lista, os ponteiros 'proximo' dos    */
      /* n�veis excedentes do novo n� apontar�o para a    */
      /* cabe�a, j� que os demais n�s t�m n�veis menores  */
      /* e o novo n� n�o dever� apontar para nenhum deles */
   if (novoNivel > lista->nivel) {
      for (i = lista->nivel + 1; i <= novoNivel; i++)
            /* O array 'enderecos' armazena os endere�os dos  */
            /* n�s que apontar�o para o novo n�. Como o n�vel */
            /* desse n� � maior do que o n�vel corrente, o    */
            /* �nico n� com n�vel maior do que o n�vel        */
            /* corrente que apontar� para ele � a cabe�a.     */
         enderecos[i] = lista->cabeca;

         /* O n�vel da lista passa a ser igual ao n�vel do novo n� */
      lista->nivel = novoNivel;
   }

      /* Ajusta os ponteiros do novo n� e dos n�s que o antecedem */
   for (i = 0; i <= novoNivel; i++) {
         /* Faz o novo n� apontar para os n�s para  */
         /* os quais os antecessores dele apontavam */
      novoNo->proximo[i] = enderecos[i]->proximo[i];

         /* Faz os antecessores do novo n� apontarem para ele */
      enderecos[i]->proximo[i] = novoNo;
   }

   free(enderecos); /* O array auxiliar n�o � mais necess�rio */

   return novoNo; /* Retorna o endere�o do novo n� */
}

/****
 *
 * RemoveListaComSaltos(): Remove de uma lista com saltos um
 *                         n� que cont�m um valor especificado
 *
 * Par�metros:
 *     *lista (entrada/sa�da) - lista na qual ser� feita a remo��o
 *      chave (entrada) - chave do n� a ser removido
 *
 * Retorno: 0, se a remo��o for bem sucedida, ou 1, se o n� a
 *          ser removido n�o for encontrado.
 *
 ****/
int RemoveListaComSaltos(tListaComSaltos *lista, tCEP chave)
{
   int                i; /* Representar� um n�vel da lista */
   tNoListaComSalto **enderecos, /* Apontar� para um array */
                                 /* de ponteiro para n�s   */
                     *ptrNo; /* Ponteiro utilizado para visitar n�s da lista */

      /* Aloca um array auxiliar de ponteiros */
   enderecos = calloc(lista->nivelMax + 1, sizeof(tNoListaComSalto *));

      /* Se o array n�o foi alocado aborta o programa */
   ASSEGURA(enderecos, "Nao foi possivel alocar array");

         /*************************************/
         /* Procura o elemento a ser removido */
         /*************************************/

   ptrNo = lista->cabeca; /* Faz ptrNo apontar para a cabe�a da lista */

      /* A busca come�a sempre no n�vel mais alto e termina no n�vel 0 */
   for (i = lista->nivel; i >= 0; i--) {
         /* A busca prossegue no mesmo n�vel at� que a sentinela ou uma  */
         /* chave maior do que ou igual a chave de busca seja encontrada */
      while ( ptrNo->proximo[i] != lista->cabeca &&
              strcmp( ptrNo->proximo[i]->conteudo.chave, chave ) < 0 )
         ptrNo = ptrNo->proximo[i]; /* Passa para o pr�ximo n� no mesmo n�vel */

         /* O array enderecos[] armazena o endere�o do �ltimo n� visitado */
         /* no n�vel i antes  que se encontre o n� a ser removido         */
      enderecos[i] = ptrNo;
   }

      /* Se o elemento n�o foi encontrado,  ele n�o pode ser removido */
   if ( ptrNo->proximo[0] == lista->cabeca ||
        strcmp( ptrNo->proximo[0]->conteudo.chave, chave ) ) {
      return 1; /* Elemento n�o foi encontrado */
   }

      /* Neste ponto, ptrNo aponta para o n� antecessor  */
      /* daquele que ser� removido. Agora, faz-se ptrNo  */
      /* apontar para esse �ltimo n�. Esta instru��o n�o */
      /* � essencial, mas facilita a escrita das demais. */
   ptrNo = ptrNo->proximo[0];

      /* Faz os antecessores do n� removido apontarem para  */
      /* o sucessor dele. A atualiza��o come�a no n�vel 0 e */
      /* encerra quando o n�vel da lista for atingido ou    */
      /* quando for encontrado um n� que n�o aponta para o  */
      /* n� a ser removido.                                 */
   for (i = 0; i <= lista->nivel && enderecos[i]->proximo[i] == ptrNo; i++)
      enderecos[i]->proximo[i] = ptrNo->proximo[i]; /* Efetua o desvio */

      /* Libera o espa�o ocupado pelo n� removido e pelo array auxiliar */
   free(ptrNo);
   free (enderecos);

      /* � poss�vel que o n� removido tenha o mesmo n�vel da lista e que ele */
      /* seja o �nico n� com esse n�vel.  Logo, se esse for o caso, ajusta-  */
      /* se o n�vel da  lista de modo que n�o exista nenhum ponteiro que     */
      /* emane da cabe�a e termine na pr�pria cabe�a.                        */
   while (lista->nivel > 0 &&
          lista->cabeca->proximo[lista->nivel] == lista->cabeca)
      lista->nivel--;

   return 0;
}

/****
 *
 * ProximoListaComSaltos(): Encontra o pr�ximo n� de uma lista
 *                          com saltos
 *
 * Par�metros:
 *     lista (entrada) - a referida lista com saltos
 *
 * Retorno: Endere�o do conte�do do pr�ximo n�, se ele existir.
 *          NULL, se n�o existir pr�ximo n�.
 *
 ****/
tCEP_Ind *ProximoListaComSaltos(tListaComSaltos lista)
{
      /* A vari�vel a seguir indica qual � o pr�ximo n� */
      /* a ser visitado. Quando ela � NULL, o pr�ximo   */
      /* n� a ser visitado � o primeiro da lista.       */
   static tNoListaComSalto *proximoNo = NULL;

      /* Verifica se a lista est� vazia */
   if (lista.cabeca->proximo[0] != lista.cabeca) {
         /* Se 'proximoNo' for NULL, o pr�ximo n� ser� o   */
         /* primeiro da lista. Caso contr�rio, 'proximoNo' */
         /* aponta para o n� que foi acessado na �ltima    */
         /* chamada desta fun��o.                          */
      if (!proximoNo) {
            /* Obt�m o primeiro da lista */
         proximoNo = lista.cabeca->proximo[0];
      } else {
            /* Obt�m o pr�ximo da lista */
         proximoNo = proximoNo->proximo[0];

            /* Se 'proximoNo' estiver apontando para a  */
            /* cabe�a da lista, � porque a lista acabou */
         if (proximoNo == lista.cabeca) {
            proximoNo = NULL; /* A lista acabou */
         }
      }

         /* Se houver pr�ximo n�, retorna seu */
         /* conte�do. Sen�o, retorna NULL.    */
      return proximoNo ? &proximoNo->conteudo : NULL;
   } else {
      return NULL; /* A lista est� vazia */
   }
}

/****
 *
 * DestroiListaComSaltos(): Libera o espa�o ocupado pelos n�s de
 *                          uma lista com saltos, tornando-a vazia
 *
 * Par�metros:
 *     lista (entrada/sa�da) - lista com saltos que ser� destru�da
 *
 * Retorno: Nada
 *
 ****/
void DestroiListaComSaltos(tListaComSaltos lista)
{
   tNoListaComSalto *p, /* Aponta para o pr�ximo n� a ser liberado */
       *q; /* Ponteiro auxiliar */

       /* Verifica se a lista est� vazia */
   if (lista.cabeca->proximo[0] == lista.cabeca) {
         /* Libera array de ponteiros da cabe�a */
         /* e depois libera a pr�pria cabe�a    */
      free(lista.cabeca->proximo);
      free(lista.cabeca);

      return; /* Lista vazia n�o precisa ser destru�da */
   }

      /* Faz p e q apontarem para o in�cio da lista */
   q = p = lista.cabeca->proximo[0];

      /* Visita cada n� da lista liberando-o */
   do {
         /* Faz q apontar para o pr�ximo n� antes */
         /* que o n� corrente seja destru�do      */
      q = q->proximo[0];

         /* Libera o array de ponteiros do n�      */
         /* corrente e depois libera o pr�prio n�  */
      free(p->proximo);
      free(p);

         /* Faz p apontar para o pr�ximo n�,   */
         /* cujo endere�o est� armazenado em q */
      p = q;
   } while (p != lista.cabeca);

      /* Libera array de ponteiros da cabe�a */
      /* e depois libera a pr�pria cabe�a    */
   free(lista.cabeca->proximo);
   free(lista.cabeca); /* Libera a cabe�a */
}
