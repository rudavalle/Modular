#if ! defined( Matriz_ )
#define Matriz_
/***************************************************************************
*#if ! defined( Matriz_ )
#define Matriz_
/***************************************************************************
*
*  $MCD Módulo de definição: MAT  Matriz duplamente encadeada
*
*  Arquivo gerado:              Matriz.h
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Matriz.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa Matrizs genéricas duplamente encadeadas.
*     Podem existir n Matrizs em operação simultaneamente.
*     As Matrizs possuem uma cabeça encapsulando o seu estado.
*
*     Cada Matriz é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da Matriz referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da Matriz.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada Matriz referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma Matriz.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da Matriz seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( Matriz_OWN )
   #define Matriz_EXT
#else
   #define Matriz_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma Matriz */

typedef struct tgMatriz * tppMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da Matriz
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0,
               /* Concluiu corretamente */

         MAT_CondRetMatrizVazia = 1,
               /* A Matriz não contém elementos */

         MAT_CondRetFimMatriz = 2,
               /* Foi atingido o fim de Matriz */

         MAT_CondRetNaoAchou = 3,
               /* Não encontrou o valor procurado */

         MAT_CondRetFaltouMemoria = 4,
               /* Faltou memória ao tentar criar um elemento de Matriz */

		 MAT_CondRetMatrizNaoExiste = 5,

		 MAT_CondRetNoNaoExiste = 6

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT  &Criar Matriz
*
*  $ED Descrição da função
*     Cria uma Matriz genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à Matriz.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a Matriz.
*     Este ponteiro será utilizado pelas funções que manipulem esta Matriz.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   MAT_tpCondRet criaMatriz(tppMatriz * p) ;


/***********************************************************************
*
*  $FC Função: MAT  &Destruir Matriz
*
*  $ED Descrição da função
*     Destrói a Matriz fornecida.
*     O parâmetro ponteiro para a Matriz não é modificado.
*     Se ocorrer algum erro durante a destruição, a Matriz resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     MAT_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   MAT_tpCondRet empilhaValor(tppMatriz mat, void * valor, int col, int lin);


/***********************************************************************
*
*  $FC Função: MAT  &Esvaziar Matriz
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a Matriz
*
*  $EP Parâmetros
*     pMatriz - ponteiro para a Matriz a ser esvaziada
*
***********************************************************************/

  MAT_tpCondRet inserirLinha(tppMatriz mat);


/***********************************************************************
*
*  $FC Função: MAT  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a Matriz esteja vazia, insere o primeiro elemento da Matriz.
*
*  $EP Parâmetros
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

/********** Fim do módulo de definição: MAT  Matriz duplamente encadeada **********/

#else
#endif