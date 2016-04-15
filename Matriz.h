#if ! defined( Matriz_ )
#define Matriz_
/***************************************************************************
*#if ! defined( Matriz_ )
#define Matriz_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: MAT  Matriz duplamente encadeada
*
*  Arquivo gerado:              Matriz.h
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Matriz.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa Matrizs gen�ricas duplamente encadeadas.
*     Podem existir n Matrizs em opera��o simultaneamente.
*     As Matrizs possuem uma cabe�a encapsulando o seu estado.
*
*     Cada Matriz � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da Matriz referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da Matriz.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada Matriz referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma Matriz.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da Matriz seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( Matriz_OWN )
   #define Matriz_EXT
#else
   #define Matriz_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma Matriz */

typedef struct tgMatriz * tppMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da Matriz
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0,
               /* Concluiu corretamente */

         MAT_CondRetMatrizVazia = 1,
               /* A Matriz n�o cont�m elementos */

         MAT_CondRetFimMatriz = 2,
               /* Foi atingido o fim de Matriz */

         MAT_CondRetNaoAchou = 3,
               /* N�o encontrou o valor procurado */

         MAT_CondRetFaltouMemoria = 4,
               /* Faltou mem�ria ao tentar criar um elemento de Matriz */

		 MAT_CondRetMatrizNaoExiste = 5,

		 MAT_CondRetNoNaoExiste = 6

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: MAT  &Criar Matriz
*
*  $ED Descri��o da fun��o
*     Cria uma Matriz gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � Matriz.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a Matriz.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta Matriz.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   MAT_tpCondRet criaMatriz(tppMatriz * p) ;


/***********************************************************************
*
*  $FC Fun��o: MAT  &Destruir Matriz
*
*  $ED Descri��o da fun��o
*     Destr�i a Matriz fornecida.
*     O par�metro ponteiro para a Matriz n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a Matriz resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     MAT_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   MAT_tpCondRet empilhaValor(tppMatriz mat, void * valor, int col, int lin);


/***********************************************************************
*
*  $FC Fun��o: MAT  &Esvaziar Matriz
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a Matriz
*
*  $EP Par�metros
*     pMatriz - ponteiro para a Matriz a ser esvaziada
*
***********************************************************************/

  MAT_tpCondRet inserirLinha(tppMatriz mat);


/***********************************************************************
*
*  $FC Fun��o: MAT  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a Matriz esteja vazia, insere o primeiro elemento da Matriz.
*
*  $EP Par�metros
*     pMatriz - ponteiro para a Matriz onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet inserirColuna(tppMatriz mat);

   MAT_tpCondRet criarTabuleiro(tppMatriz mat, int numColuna, int numLinha);

   MAT_tpCondRet moverSul(tppMatriz mat);

   MAT_tpCondRet moverLeste(tppMatriz mat);

   MAT_tpCondRet moverCorrParaRaiz(tppMatriz mat);


#undef Matriz_EXT

/********** Fim do m�dulo de defini��o: MAT  Matriz duplamente encadeada **********/

#else
#endif