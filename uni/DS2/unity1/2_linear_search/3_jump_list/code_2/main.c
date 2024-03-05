/****
 *
 * Exemplo: Lista com Saltos
 *
 * Se��o: 3.6
 *
 * Descri��o:
 *    -> A tabela de busca � implementada como lista com saltos
 *       em que cada elemento cont�m uma a chave e a posi��o
 *       do respetivo registro no arquivo
 *
 *    -> Os registros s�o mantidos em arquivo
 *
 *    -> Tipo de busca: com saltos
 *
 *    -> Arquivo de dados: CEPs.bin
 *
 * Observa��o: Para reconstruir o arquivo bin�rio, use o
 *             programa CriaArquivoBin.c neste diret�rio
 *
 ****/

/*********************** Includes *************************/

#include <stdio.h>    /* Fun��es de Entrada/Sa�da */
#include <string.h>   /* Processamento de strings */
#include <stdlib.h>   /* Fun��o strtod()          */
#include <time.h>     /* Medi��o de tempo         */
#include "Lista.h"    /* Interface do tipo lista  */
#include "Leitura.h"  /* Leitura via teclado      */
#include "Registros.h" /* Interface do m�dulo Registros */
#include "ASSEGURA.h"  /* Macro ASSEGURA()        */

/***************** Constantes Simb�licas ******************/

   /* Nome do arquivo de dados */
#define NOME_ARQUIVO_BIN "CEPs.bin"

   /* Nome do arquivo contendo as chaves da tabela de busca */
#define NOME_ARQUIVO_CHAVES "ListaDeChaves.txt"

   /* Estimativa para o n�mero de registros removidos */
#define MAX_REMOVIDOS       10

/**************** Compila��o Condidicional ****************/

#define DEPURACAO 0

/***************** Defini��es de Fun��es ******************/

/****
 *
 * EscreveListaEmArquivo(): Escreve em arquivo, em forma de
 *                          tabela, os elementos de uma lista
 *                          armazenada num array
 *
 * Par�metros:
 *     lista (entrada) - a lista
 *     tamanho (entrada) - tamanho da lista
 *
 * Retorno: Nada
 *
 ****/
void EscreveListaEmArquivo(tListaComSaltos lista, int tamanho)
{
   tCEP_Ind *ptrElemento;
   FILE      *stream;

      /* Tenta abrir o arquivo para escrita em modo texto */
   stream = fopen(NOME_ARQUIVO_CHAVES, "w");

      /* Se arquivo n�o foi aberto, aborta o programa */
   ASSEGURA(stream,
            "Impossivel criar arquivo para escrita de chaves");

   printf("\nEscrevendo lista em arquivo...");

      /* Cabe�alho de apresenta��o */
   fprintf( stream,
            "   Chave   \tIndice\n"
            "   =====   \t======\n");

      /* Apresenta cada estrutura numa linha separada */
   while ((ptrElemento = ProximoListaComSaltos(lista))) {
      fprintf( stream, "%s\t%d\n", ptrElemento->chave,
               ptrElemento->valor );
   }

   fclose(stream);

   printf( "\n*** Resultado escrito no arquivo %s *** \n",
           NOME_ARQUIVO_CHAVES );
}

/****
 *
 * ExibeLista(): Apresenta na tela ou em arquivo
 *               os elementos da tabela de busca
 *
 * Par�metros:
 *     lista (entrada) - a tabela
 *
 * Retorno: Nada
 *
 ****/
void ExibeLista(tListaComSaltos lista)
{
   tCEP_Ind *ptrElemento;
   int        tamanho = ComprimentoListaComSalto(lista),
              op,
              i = 1;

      /* Se a lista estiver vazia, n�o h� o que exibir */
   if (!tamanho) {
      printf("\n*** Lista Vazia *** \n");
      return;
   }

      /* Garante que a exibi��o iniciar� no come�o da lista */
   while (ProximoListaComSaltos(lista)) {
       ; /* Vazio */
   }

      /* Se a lista for considerada grande demais, oferece   */
      /* ao usu�rio a op��o de exbir apenas alguns elementos */
   if (tamanho > 1000) {
      printf( "\nA lista possui %d elementos. "
              "\nTem certeza que quer exibi-la inteira (s/n)? ",
              tamanho );
      op = LeOpcao("snSN");

      if (op == 'n' || op == 'N') {
         printf("\nQuantos elementos deseja exibir? ");
         tamanho = LeInteiroEntre(1, tamanho);
      } else {
            /* N�o faz sentido exibir uma */
            /* tabela t�o grande na tela  */
         EscreveListaEmArquivo(lista, tamanho);

         return; /* Servi�o conclu�do */
      }
   }

      /* Cabe�alho de apresenta��o na tela */
   printf( "\n   Chave   \tIndice"
           "\n   =====   \t======\n");

      /* Apresenta cada estrutura numa linha separada */
      /* Apresenta cada estrutura numa linha separada */
   while ( (ptrElemento = ProximoListaComSaltos(lista)) &&
           i++ <= tamanho ) {
      printf("%s\t%d\n", ptrElemento->chave, ptrElemento->valor);
   }

   putchar('\n'); /* Embelezamento apenas */
}

/****
 *
 * LeArquivo(): L� arquivo de bin�rio e armazena as chaves e
 *              os �ndices dos registro numa lista encadeada
 *
 * Par�metros:
 *      arqBin (entrada) - nome do arquivo bin�rio
 *     *lista (sa�da) - lista que conter� as chaves e os
 *                      �ndices dos registros lidos
 *
 * Retorno: Stream associado ao arquivo aberto para
 *          leitura e escrita
 *
 ****/
FILE *LeArquivo( const char *arqBin, tListaComSaltos *lista )
{
   FILE      *stream;
   tCEP_Ind  umElemento;
   tRegistroCEP  umRegistro;
   int        indiceReg = 0,
              nRegistros; /* N�mero de registros no arquivo */

      /* Tenta abrir o arquivo bin�rio para leitura e escrita */
   stream = fopen(arqBin, "rb+");

      /* Se o arquivo n�o pode ser aberto, aborta o programa */
   ASSEGURA(stream, "Arquivo nao pode ser aberto");

      /* Calcula o n�mero de registros do arquivo */
   nRegistros = NumeroDeRegistros( stream, sizeof(tRegistroCEP) );

      /* Inicia a lista que armazena a tabela de busca */
   IniciaListaComSaltos(lista, nRegistros);

      /* Rebobina o arquivo */
   rewind(stream);

      /* L� cada registro do arquivo e acrescenta */
      /* sua chave (CEP) e seu �ndice na lista    */
   while (1) {
         /* L� um registro no arquivo */
      fread( &umRegistro, sizeof(umRegistro), 1, stream);

         /* Verifica se ocorreu erro ou o */
         /* final do arquivo foi atingido */
      if (ferror(stream) || feof(stream)) {
         break;
      }

         /* A chave n�o � armazenada como string no registro. */
         /* Portanto, n�o se pode usar strcpy().              */
      strncpy(umElemento.chave, umRegistro.CEP, TAM_CEP);

         /* Transforma a chave num string. Isso n�o � */
         /* essencial, mas facilita o processamnto.   */
      umElemento.chave[TAM_CEP] = '\0';

         /* Armazena no novo elemento da tabela o */
         /* �ndice do registro no arquivo e, ao   */
         /* mesmo tempo, incrementa esse �ndice   */
      umElemento.valor = indiceReg++;

         /* Acrescenta o novo elemento � tabela */
      InsereListaComSaltos(lista, umElemento);
   }

      /* Se ocorreu erro de leitura no arquivo, fecha */
      /* o arquivo e aborta o programa                */
   if (ferror(stream)) {
      fclose(stream);
      ASSEGURA(0, "Erro de leitura de arquivo ");
   }

   return stream;
}

/****
 *
 * ApresentaMenu(): Apresenta um menu de op��es para o usu�rio
 *
 * Par�metros:
 *      opcoes[] (entrada) - array de strings contendo as
 *                           op��es do usu�rio
 *      nOpcoes (entrada) - o n�mero de op��es
 *
 * Retorno: Nada
 *
 ****/
static void ApresentaMenu(const char *opcoes[], int nOpcoes)
{
   int i;

   printf("\nEscolha uma das opcoes a seguir:\n");

   for (i = 0; i < nOpcoes; ++i)
      printf("\n\t[%d] %s", i + 1, opcoes[i]);

   printf("\n\n\t>>> ");
}

/****
 *
 * AtualizaArquivoBin(): Cria um novo arquivo bin�rio contendo
 *                       cada registro de outro arquivo bin�rio
 *                       cuja chave n�o fa�a parte de uma lista
 *                       de registros que devem ser removidos
 *
 * Par�metros:
 *      nomeArquivo (entrada) - nome do arquivo bin�rio original
 *      removidos (entrada) - lista contendo as estruturas que
 *                            N�O ser�o escritas no novo arquivo
 *
 * Retorno: Nenhum
 *
 ****/
void AtualizaArquivoBin( const char *nomeArquivo,
                         tListaComSaltos removidos )
{
   char      ar[L_tmpnam]; /* Nome de um arquivo tempor�rio */
   FILE     *stream, /* Stream associado ao arquivo original */
            *streamTmp; /* Stream associado ao tempor�rio */
   tRegistroCEP umRegistro; /* Um registro do arquivo */
   tCEP_Ind conteudo;
   int       ocorreuErro = 0; /* Indicar� se ocorreu erro */

      /* Tenta abrir o arquivo original para leitura */
   ASSEGURA( stream = fopen(nomeArquivo, "rb"),
             "Nao foi possivel atualizar arquivo" );

      /* Obt�m o nome de um arquivo tempor�rio */
   tmpnam(ar);

      /* Tenta abrir o arquivo tempor�rio */
      /* para escrita em modo bin�rio     */
   ASSEGURA(streamTmp = fopen(ar, "wb"),
            "Nao foi possivel abrir arquivo temporario");

      /* O la�o encerra quando n�o for */
      /* mais poss�vel ler um registro */
   while (1) {
         /* L� um registro no arquivo de entrada */
      fread(&umRegistro, sizeof(umRegistro), 1, stream);

         /* Testa se final do arquivo de entrada foi */
         /* atingido ou ocorreu erro de leitura      */
      if (feof(stream) || ferror(stream)) {
         break; /* Processamento encerrado */
      }

         /* Cria uma chave (string). O campo CEP */
         /* do registro n�o � string.            */
      strncpy(conteudo.chave, umRegistro.CEP, TAM_CEP);
      conteudo.chave[TAM_CEP] = '\0';

         /* Se a chave do registro lido n�o faz parte da  */
         /* lista de removidos, escreve-o no novo arquivo */
      if (BuscaListaComSaltos(removidos, conteudo.chave) < 0) {
            /* Escreve o registro lido no arquivo de sa�da */
         fwrite(&umRegistro, sizeof(umRegistro), 1, streamTmp);

            /* Verifica se ocorreu erro de escrita */
         if (ferror(streamTmp)) {
            break;
         }
      }
   }

      /* Verifica se ocorreu erro de leitura ou escrita */
   if ( ferror(stream) || ferror(streamTmp) ) {
      ocorreuErro = 1;
   }

      /* Fecha os arquivos */
   fclose(stream);
   fclose(streamTmp);

      /* Se ocorreu erro de leitura ou */
      /* escrita, aborta o programa    */
   ASSEGURA(!ocorreuErro, "Erro na atualizacao do arquivo");

      /* Tenta apagar o arquivo original. Se isso */
      /* n�o for poss�vel, aborta o programa      */
   ASSEGURA( !remove(nomeArquivo),
             "Erro na atualizacao do arquivo" );

      /* Tenta rebatizar o arquivo tempor�rio */
      /* com o nome do arquivo original       */
   ocorreuErro = rename(ar, nomeArquivo);

   if (ocorreuErro) {
      printf( "\n\t>>> O resultado da atualizacao se encontra"
              "no arquivo \"%s\". Nao foi possivel "
              "rebatiza-lo.\n", ar );
      ASSEGURA( 0, "Erro em batismo de arquivo" );
   }
}

/****
 *
 * MedidaDeTempo(): Mede intervalos de tempo entre duas
 *                  chamadas consecutivas
 *
 * Par�metros: Nenhum
 *
 * Retorno: Nada
 *
 * Observa��o: Esta fun��o deve ser chamada aos pares; i.e.,
 *             na primeira chamada ela marca o in�cio da
 *             contagem de tempo e na segunda chamada ela
 *             apresenta o intervalo de tempo decorrido
 *             desde a �ltima chamada
 *
 ****/
void MedidaDeTempo(void)
{
   static int    numeroDeChamadas = 0;
   static time_t t0; /* Instante inicial */
   time_t        tf; /* Instante final   */

      /* Esta fun��o foi chamada mais uma vez */
   ++numeroDeChamadas;

      /* Se o n�mero da chamada for �mpar, esta */
      /* chamada � a primeira de um par         */
   if (numeroDeChamadas%2) { /* Calcula o instante inicial */
      t0 = time(NULL);
   } else { /* Calcula e apresenta o intervalo de   */
            /* tempo entre as duas �ltimas chamadas */
      tf = time(NULL);

      printf( "\n\n\t*** Tempo gasto na operacao: "
              "%5.2f segundos ***\n", difftime(tf, t0) );
   }
}

/********************* Fun��o main() **********************/

/****
 *
 * main(): Implementa opera��es sobre tabela implementada como
 *         lista encadeada N�O ordenada contendo os registros
 *         do tipo tCEP e com busca com movimenta��o para o in�cio
 *
 * Par�metros: Nenhum
 *
 * Retorno: Zero
 *
 ****/
int main (void)
{
   tListaComSaltos lista, /* Tabela de busca */
                  removidos; /* Chaves dos registros a ser  */
                             /* removidos quando o arquivo  */
                             /* de registros for atualizado */
   tRegistroCEP   umRegistro; /* Armazenam um registro */
   tCEP_Ind   elemento; /* Um elemento da lista */
   const char *opcoes[] = { "Consulta dados de um CEP",
                            "Acrescenta um CEP",
                            "Remove um CEP",
                            "Apresenta a lista de CEPs",
                            "Encerra o programa"
                          };
   int         op, /* Op��o escolhida pelo usu�rio */
               nOpcoes = sizeof(opcoes)/sizeof(opcoes[0]);
   FILE       *stream; /* Stream associado ao  */
                        /* arquivo de registros */
   int         primeiroByte, /* Indica a posi��o do */
                             /* primeiro byte de um */
                             /* registro no arquivo */
               atualizarArq = 0, /* Indica se o arquivo de    s*/
                                 /* registros ser� atualizado */
                nRegistros, /* N�mero de registros no arquivo */
                posRegistro, /* �ndice de um registro no arquivo */
                tamLista;   /* Tamanho da tabela de busca     */

   MedidaDeTempo();
   printf("\nCriando lista...");

      /* Inicia a lista que armazena os �ndices */
      /* dos registros removidos                */
   IniciaListaComSaltos(&removidos, MAX_REMOVIDOS);

      /* L� o conte�do do arquivo de */
      /* dados e o armazena na lista */
   stream = LeArquivo(NOME_ARQUIVO_BIN, &lista);

   printf("\n...lista criada com sucesso\n");
   MedidaDeTempo();

#if DEPURACAO == 1

   MedidaDeTempo();
   printf("\nChecando a consistencia do programa...");

      /* Calcula o n�mero de elementos na lista */
   tamLista = ComprimentoListaComSalto(lista);

      /* Calcula o n�mero de registros do arquivo */
   nRegistros = NumeroDeRegistros( stream, sizeof(tRegistroCEP) );

   printf( "\n\n\t>>> Numero de registros no arquivo: %d",
           nRegistros );
   printf( "\n\t>>> Numero de elementos na lista:   %d\n\n",
           tamLista );

//   ASSEGURA( tamLista == nRegistros,
//             "This program is fucking wrong!!!" );

      /* Apresenta o n�mero de n�veis da lista */
   ApresentaNiveis(lista);

      /* Apresenta o n�mero de elementos */
      /* em cada n�vel da lista          */
   ApresentaComprimentosPorNivel(lista);

      /* Apresenta as relac�es entre n�mero de n�s */
      /* em n�veis adjacentes da lista             */
   ApresentaRelacoesEntreNiveis(lista);

   printf("\n...consistencia OK");
   MedidaDeTempo();

#endif

      /* O la�o a seguir encerra quando o usu�rio */
      /* escolher a op��o de encerramento         */
   while (1) {
      ApresentaMenu(opcoes, nOpcoes);

      op = LeOpcao("12345");

         /* Verifica se o usu�rio quer encerrar o programa */
      if (op == '5') { /* Encerra o programa */
         fclose(stream);

            /* A tabela de busca n�o � mais necess�ria */
         DestroiListaComSaltos(lista);

         break; /* Sa�da do la�o */
      }

         /* Processa as demais op��es */
      switch (op) {
         case '1': /* Consulta dados de um CEP */
               /* L� um CEP introduzido pelo usu�rio */
            LeMatricula("CEP", elemento.chave, TAM_CEP + 1);

               /* Procura o CEP na tabela de busca */
            posRegistro = BuscaListaComSaltos(lista, elemento.chave);

               /* Se a chave for encontrada, utiliza-se o */
               /* �ndice associado a ela para recuperar   */
               /* o registro correspondente no arquivo    */
            if (posRegistro < 0) {
               printf("\n>>> CEP nao foi encontrado\n");
            } else {
                  /* Utilizando o �ndice do registro, */
                  /* calcula-se a posi��o no arquivo  */
                  /* do primeiro byte do registro     */
               primeiroByte = posRegistro*sizeof(tRegistroCEP);

                  /* Move o apontador de posi��o para o   */
                  /* primeiro byte do registro. Se isso   */
                  /* n�o for poss�vel, aborta o programa. */
               ASSEGURA( !fseek(stream, primeiroByte, SEEK_SET),
                         "Erro de posicionamento em arquivo" );

                  /* L� o registro no arquivo */
               fread(&umRegistro, sizeof(umRegistro), 1, stream);

                  /* Se ocorreu erro de leitura aborta */
               ASSEGURA(!ferror(stream), "Erro de leitura");

                  /* Apresenta o registro ao usu�rio */
               ExibeRegistro(&umRegistro);

               putchar('\n'); /* Embelezamento */
            }

            break;

         case '2': /* Acrescenta um registro de CEP */
               /* L� dados do novo CEP */
            LeRegistro(&umRegistro);

               /* O valor do campo 'numero' corresponde � */
               /* posi��o do registro no arquivo de CEPs  */
               /* (isso � coisa dos Correios)             */
            umRegistro.numero = ComprimentoListaComSalto(lista) + 1;

               /* Cria a chave a ser inserida na tabela de */
               /* busca. Na tabela, a chave � um string    */
               /* mas no registro CEP n�o � string         */
            strncpy(elemento.chave, umRegistro.CEP, TAM_CEP);

               /* Torna a chave um string */
            elemento.chave[TAM_CEP] = '\0';

               /* Acrescenta o �ndice do registro ao elemento */
            elemento.valor = umRegistro.numero;

               /* Insere novo elemento � tabela de busca */
               /* apenas se sua chave ainda n�o existir  */
            if(!InsereListaComSaltos(&lista, elemento)) {
               printf("\n>>> Este CEP ja existe\n");

               break;
            }

               /* Move apontador de posi��o para o final */
               /* do arquivo. Se isso n�o for poss�vel,  */
               /* aborta o programa.                     */
            ASSEGURA( !fseek(stream, 0, SEEK_END),
                      "Erro de posicionamento em arquivo");

               /* Escreve o novo registro no final do arquivo */
            fwrite(&umRegistro, sizeof(umRegistro), 1, stream);

               /* Se ocorreu erro de escrita, aborta */
            ASSEGURA(!ferror(stream),
                     "Erro de escrita em arquivo ");

            printf("\n>>> Acrescimo bem sucedido\n");

            break;

         case '3': /* Remove um CEP */
               /* L� um CEP introduzido pelo usu�rio */
            LeMatricula("CEP", elemento.chave, TAM_CEP + 1);

               /* Se a chave for encontrada, remove-a da    */
               /* tabela de busca e acrescenta-se um novo   */
               /* elemento na lista de removidos. A remo��o */
               /* do registro do arquivo s� ser� efetuada   */
               /* ao final do programa.                     */
            if (!RemoveListaComSaltos(&lista, elemento.chave)){
                  /* Acrescenta um novo elemento */
                  /* � lista de removidos        */
               InsereListaComSaltos(&removidos, elemento);

                  /* Arquivo de registros precisar� */
                  /* ser atualizado                 */
               atualizarArq = 1;

               printf("\n>>> Remocao bem sucedida\n");
            } else {
               printf("\n>>> CEP nao encontrado\n");
            }

            break;

         case '4': /* Apresenta a lista na tela */
            ExibeLista(lista);
            break;

         default: /* O programa n�o deve chegar at� aqui */
            printf("\nEste programa contem um erro\n");
            return 1;
      }
   }

      /* Atualiza arquivo bin�rio se for necess�rio */
   if (atualizarArq) {
      MedidaDeTempo();
      printf("\nAtualizando arquivo...");

         /* Atualiza arquivo bin�rio */
      AtualizaArquivoBin(NOME_ARQUIVO_BIN, removidos);

      printf("\n... Atualizacao bem sucedida");
      MedidaDeTempo();
   }

      /* Despede-se do usu�rio */
   printf( "\n\t>>> Obrigado por usar este programa\n\n");

   return 0;
}

/******************* Exemplo de Execu��o ******************



**********************************************************/
