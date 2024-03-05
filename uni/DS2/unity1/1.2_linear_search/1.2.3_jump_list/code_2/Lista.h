#ifndef _Lista_H_
#define _Lista_H_

#include "Registros.h" /* Interface do m�dulo Registros */

/****************** Defini��es de Tipos *******************/

   /* Tipo de chave */
typedef char tCEP[TAM_CEP + 1];

typedef struct {
           tCEP chave; /* CEP */
           int  valor; /* �ndice do CEP no arquivo */
        } tCEP_Ind;

   /* Tipo de n� do n�vel 0 */
typedef struct rotNoLS {
           tCEP_Ind         conteudo; /* Conte�do efetivo    */
           struct rotNoLS **proximo;  /* Pr�ximo n� da lista */
        } tNoListaComSalto;

   /* Tipo de lista com saltos */
typedef struct {
           tNoListaComSalto *cabeca;   /* Cabe�a da lista         */
           int               nivel;    /* N�vel corrente da lista */
           int               nivelMax; /* N�vel m�ximo da lista   */
        } tListaComSaltos;

/************************* Alus�es ************************/

extern void ApresentaComprimentosPorNivel(tListaComSaltos lista);
extern void ApresentaRelacoesEntreNiveis(tListaComSaltos lista);
extern void ApresentaNiveis(tListaComSaltos lista);

extern void IniciaListaComSaltos( tListaComSaltos *lista, int maxRegs );
extern int EstaVaziaListaComSaltos(tListaComSaltos lista);
extern int ComprimentoListaComSalto(tListaComSaltos lista);
extern int BuscaListaComSaltos(tListaComSaltos lista, tCEP chave);
extern tNoListaComSalto *InsereListaComSaltos( tListaComSaltos *lista,
                                                 tCEP_Ind conteudo );
extern int RemoveListaComSaltos( tListaComSaltos *lista, tCEP chave );
extern tCEP_Ind *ProximoListaComSaltos(tListaComSaltos lista);
extern void DestroiListaComSaltos(tListaComSaltos lista);

#endif
