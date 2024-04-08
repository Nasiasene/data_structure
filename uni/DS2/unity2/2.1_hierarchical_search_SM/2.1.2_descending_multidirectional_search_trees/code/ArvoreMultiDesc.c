
#include <stdio.h>    
#include <stdlib.h>   
#include "ArvoreMultiDesc.h" 

static void IniciaNoMultiMS(const tChaveIndice *chaveIndice, tNoMultiMS *pNo){
   int i;

   if (chaveIndice) //ao iniciar so tera uma chave, verificando se nao eh NULL
      pNo->chaves[0] = *chaveIndice;

   pNo->nFilhos = chaveIndice ? 2 : 0;
   for (i = 0; i < G; ++i)
      pNo->filhos[i] = POSICAO_NULA;
}

static void LeNoMultiMS(FILE *stream, int pos, tNoMultiMS *no){
   if (feof(stream))
      return;
   fseek(stream, sizeof(tNoMultiMS)*pos, SEEK_SET);
   fread(no, sizeof(tNoMultiMS), 1, stream);
}

static void EscreveNoMultiMS(FILE *stream, int pos, const tNoMultiMS *pNo){
   fseek(stream, sizeof(*pNo)*pos, SEEK_SET);
   fwrite(pNo, sizeof(*pNo), 1, stream);
}

static int BuscaEmNoMultiMS(int chave, const tNoMultiMS *no){
   int i, nChaves = no->nFilhos - 1; 

      /* Procura no no uma chave que seja maior */
      /* do que ou igual a chave de busca       */
   for (i = 0; i < nChaves; ++i)
      if (chave <= no->chaves[i].chave)
         return i;   /* A chave foi encontrada */

   return nChaves; /* A chave nao foi encontrada, retornando ultimo filho */
}

static int EncontraNoMultiMS(FILE *stream, int chave,int *posicaoDaChaveNoNo, int *encontrado){ //posicao do no com a chave ou do pai dele para insercao
   int        p,  /* p contera a posicaoo desejada    */
              q,  /* q contera a posicao do pai de p */
              posChave;
   tNoMultiMS umNo;

   fseek(stream, 0, SEEK_SET);

   p = 0; //busca comeca pela raiz
   q = POSICAO_NULA; //pai da raiz nao existe

   while (p != POSICAO_NULA) {
      LeNoMultiMS(stream, p, &umNo);
      posChave = BuscaEmNoMultiMS(chave, &umNo);

      if((posChave < umNo.nFilhos - 1) && chave == umNo.chaves[posChave].chave) {
         *encontrado = 1;  /* A chave foi encontrada */
         *posicaoDaChaveNoNo = posChave;

         return p; //posicao no arquivo do no com a chave
      }

      //ainda nao encontrada, descer um nivel
      q = p;
      p = umNo.filhos[posChave];
   }

   *encontrado = 0; //chave nao encontrada
   *posicaoDaChaveNoNo = posChave; //posicao para insercao

   return q;  //retorna o indice/posicao do no pai, onde sera inserido (nele se tiver espaco)
}

static void InsereEmFolhaMultiMS(FILE *stream, int posicaoNo, int posicaoDaChave, tChaveIndice chaveEIndice){
   int        i;
   tNoMultiMS umNo;

   LeNoMultiMS(stream, posicaoNo, &umNo);

   //faz shift das chaves, sempre havera espaco por ser no incompleto de arvore descendente
   for (i = umNo.nFilhos - 1; i > posicaoDaChave; --i)
      umNo.chaves[i] = umNo.chaves[i - 1];

   umNo.chaves[posicaoDaChave] = chaveEIndice; //insere nova chave
   ++umNo.nFilhos;

   EscreveNoMultiMS(stream, posicaoNo, &umNo); //atualiza no no arquivo
}

static void CompactaNoMultiMS(tNoMultiMS *pNo, int posicao){
   int i;

      /* Primeiro, move as chaves */
   for (i = posicao; i < pNo->nFilhos - 2; ++i)
      pNo->chaves[i] = pNo->chaves[i + 1];

      /* A movimentação de filhos depende de qual dos filhos  */
      /* da chave removida é vazio. Se o filho esquerdo não   */
      /* for vazio, a movimentação começa uma posição adiante */
   if (pNo->filhos[posicao])
      posicao++;

      /* Move os filhos do n� */
   for (i = posicao; i < pNo->nFilhos - 1; ++i)
      pNo->filhos[i] = pNo->filhos[i + 1];

   --pNo->nFilhos; /* O n�mero de filhos (e de chaves) diminuiu */
}

static long TamanhoDeArquivo(FILE *stream){
   fseek(stream, 0, SEEK_END);
   return ftell(stream);
}

static int NumeroDeRegistros(FILE *stream, int tamRegistro){
   long nBytes = TamanhoDeArquivo(stream);
   return nBytes/tamRegistro;
}

int BuscaMultiMS(FILE *stream, int chave){
   tNoMultiMS no;   //para armazenar nos lidos de arquivo
   int        posNo = 0, //indice da posicao da raiz
              i; //indices chaves dentro de nos

   while (posNo != POSICAO_NULA) {
      LeNoMultiMS(stream, posNo, &no);

      i = BuscaEmNoMultiMS(chave, &no);

      if (i < no.nFilhos - 1 && chave == no.chaves[i].chave)
         return no.chaves[i].chave; /* A chave foi encontrada */

      posNo = no.filhos[i]; //descer um nivel 
   }

   return POSICAO_NULA;  /* A chave nao foi encontrada */
}

int InsereMultiMS(int *posicaoRaiz, tChaveIndice *chaveEIndice, FILE *streamArvore){ //1 em caso de sucesso, 0 caso contrario
   tNoMultiMS no, novoNo;
   int        pNo, pNovoNo,
              encontrado,    //indica se a chave foi encontrada
              indiceDaChave; //indice encontrado ou para insercao

   if (*posicaoRaiz == POSICAO_NULA) {
      IniciaNoMultiMS(chaveEIndice, &no); //criar arvore
      *posicaoRaiz = 0;
      chaveEIndice->indice = 0;

      EscreveNoMultiMS(streamArvore, 0, &no); //armazenar raiz no arquivo
      return 1; //deu certo  
   }
   pNo = EncontraNoMultiMS(streamArvore, chaveEIndice->chave, &indiceDaChave, &encontrado);

   if (encontrado)
      return 0; //chave primaria

   //chave nao encontrada, inserir

   LeNoMultiMS(streamArvore, pNo, &no); //le o no encontrado

   if (no.nFilhos < G) { //tem espaço no no
      InsereEmFolhaMultiMS( streamArvore, pNo, indiceDaChave, *chaveEIndice ); //eh folha por ser descendente, ainda nao cheio
      return 1;  //inserido
   }

   //o no retornado nao tem espaco para a chave, sera necessario criar um novo
   IniciaNoMultiMS(chaveEIndice, &novoNo);
   //posicao/indice do novo no sera ao final do arquivo
   pNovoNo = NumeroDeRegistros(streamArvore, sizeof(tNoMultiMS));

   no.filhos[indiceDaChave] = pNovoNo; //como nao tinha espaco, o indice da chave pai eh o mesmo do filho onde sera alocado
   EscreveNoMultiMS(streamArvore, pNo, &no); //atualiza no pai do novo no, com novo filho

   //adicionar novo no no arquivo
   fseek(streamArvore, 0, SEEK_END);
   fwrite(&novoNo, sizeof(tNoMultiMS), 1, streamArvore);

   return 1;  //inserido
}

int RemoveChaveMultiMS(FILE **streamArvore, int chave) { //1 em caso de sucesso ou 0
   tChaveIndice sucessoraEIndice;
   tNoMultiMS    no, //no atual
                noPai; //no pai de no
   int          i,
                posNo = 0, //busca comeca pela raiz
                posNoPai = POSICAO_NULA, //raiz nao tem pai
                iPai; /* indice do filho do penultimo no  */
                      /* visitado que contem a posicao no */
                      /* arquivo de 'no'                  */

   while (posNo != POSICAO_NULA) {
      LeNoMultiMS(*streamArvore, posNo, &no);

      i = BuscaEmNoMultiMS(chave, &no);
      if (i < no.nFilhos - 1 && chave == no.chaves[i].chave)
         break; /* A chave foi encontrada */

      posNoPai = posNo;
      noPai = no;
      iPai = i;

      posNo = no.filhos[i]; //desce um no
   }

   if (posNo == POSICAO_NULA) {
      return 0; //chave nao encontrada
   }

   /*********************************************************/
   /* Neste ponto sabe-se que 'no' contém a chave que será  */
   /* removida e que a posição dessa chave nesse nó é i.    */
   /* O índice do filho de 'noPai' que contém a posição em  */
   /* arquivo de 'no' é 'iPai'.                             */
   /*                                                       */
   /* O nó será logicamente removido, visto que ele não     */
   /* poderá mais ser acessado, mas continuará ocupando es- */
   /* paço no arquivo até que a árvore seja reconstruída.   */
   /*********************************************************/

   if ( no.filhos[i] == POSICAO_NULA || no.filhos[i + 1] == POSICAO_NULA ){
      //chave tem 1 ou 0 filho

      if(no.nFilhos == 2) {
         //ultima chave do no, remover tambem o no

         if (posNoPai == POSICAO_NULA) {
            *streamArvore = NULL; //a raiz so tinha uma chave
            return 1; //removido
         }

         if(no.filhos[i] != POSICAO_NULA) {
            //o no tem filho esquerdo (filho mesma posicao da chave). o pai do no q sera removido apontara para seu filho diretamente
            noPai.filhos[iPai] = no.filhos[i];
            EscreveNoMultiMS(*streamArvore, posNoPai, &noPai);
         } else if(no.filhos[i + 1] != POSICAO_NULA) {
            //o no tem filho direito (filho na posicao da chave+1). o pai do no q sera removido apontara para seu filho diretamente
            noPai.filhos[iPai] = no.filhos[i + 1];
            EscreveNoMultiMS(*streamArvore, posNoPai, &noPai);
         } else {
            //no sem filhos, seu pai apontara para NULL
            noPai.filhos[iPai] = POSICAO_NULA;
         }
      } else { 
         //no tinha outras chaves, compactar e atualizar
         CompactaNoMultiMS(&no, i);
         EscreveNoMultiMS(*streamArvore, posNo, &no);
      }

      return 1;
   }

   //chave com dois filhos, achar sucessora, etc
   sucessoraEIndice = MenorChaveMultiMS(*streamArvore, no.filhos[i + 1]);

   //removo sucessora recursivamente (1 unica recursao, ela nao tera dois filhos)
   if (!RemoveChaveMultiMS(streamArvore, sucessoraEIndice.chave))
      return 0;

   no.chaves[i] = sucessoraEIndice; //substitui pela sucessora
   EscreveNoMultiMS(*streamArvore, posNo, &no);

   return 1;
}

tChaveIndice MenorChaveMultiMS(FILE *streamArvore, int raiz){
   tNoMultiMS umNo;
   int       pos; 


   LeNoMultiMS(streamArvore, raiz, &umNo);

   pos = umNo.filhos[0];

   while (pos != POSICAO_NULA) {
      LeNoMultiMS(streamArvore, pos, &umNo);

      pos = umNo.filhos[0];
   }

   return umNo.chaves[0];
}

void CaminhamentoInfixoMultiMS(FILE *streamArvore, int posNo, FILE *streamChaves){
   int  i;
   tNoMultiMS  umNo;

   if (posNo != POSICAO_NULA) {
      LeNoMultiMS(streamArvore, posNo, &umNo);

      for (i = 0; i < umNo.nFilhos-1; ++i) {
         CaminhamentoInfixoMultiMS( streamArvore, umNo.filhos[i], streamChaves);
         if (streamChaves)
            fprintf(streamChaves, "%d\n", umNo.chaves[i].chave);
         else{
            printf("%d ", umNo.chaves[i].chave);
         }
      }

      CaminhamentoInfixoMultiMS(streamArvore, umNo.filhos[umNo.nFilhos-1], streamChaves);
   }
}

void CaminhamentoPreMultiMS(FILE *streamArvore, int posNo, FILE *streamChaves){
   int  i;
   tNoMultiMS  umNo;

   if (posNo != POSICAO_NULA) {
      LeNoMultiMS(streamArvore, posNo, &umNo);

      for (i = 0; i < umNo.nFilhos-1; ++i) {
         if (streamChaves)
            fprintf(streamChaves, "%d\n", umNo.chaves[i].chave);
         else{
            printf("%d ", umNo.chaves[i].chave);
         }
         CaminhamentoPreMultiMS( streamArvore, umNo.filhos[i], streamChaves);
      }

      CaminhamentoPreMultiMS(streamArvore, umNo.filhos[umNo.nFilhos-1], streamChaves);
   }
}