#if ! defined( PILHA_ )
#define PILHA_
/***************************************************************************
*
*  $MCD Módulo de definição: PIL  PILHA duplamente encadeada
*
*  Arquivo gerado:              PILHA.h
*  Letras identificadoras:      PIL
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PILHA.BSW
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
*     Implementa PILHAs genéricas duplamente encadeadas.
*     Podem existir n PILHAs em operação simultaneamente.
*     As PILHAs possuem uma cabeça encapsulando o seu estado.
*
*     Cada PILHA é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da PILHA referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da PILHA.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada PILHA referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma PILHA.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da PILHA seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( PILHA_OWN )
   #define PILHA_EXT
#else
   #define PILHA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma PILHA */

typedef struct tgPilha * tppPilha ;


/***********************************************************************
*
*  $TC Tipo de dados: PIL Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da PILHA
*
***********************************************************************/

   typedef enum {

         PIL_CondRetOK ,
               /* Concluiu corretamente */

         PIL_CondRetPILHAVazia ,
               /* A PILHA não contém elementos */

         PIL_CondRetFimPILHA ,
               /* Foi atingido o fim de PILHA */

         PIL_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         PIL_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de PILHA */

   } PIL_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PIL  &Criar PILHA
*
*  $ED Descrição da função
*     Cria uma PILHA genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à PILHA.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a PILHA.
*     Este ponteiro será utilizado pelas funções que manipulem esta PILHA.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   PIL_tpCondRet criaPilha(tppPilha * p) ;


/***********************************************************************
*
*  $FC Função: PIL  &Destruir PILHA
*
*  $ED Descrição da função
*     Destrói a PILHA fornecida.
*     O parâmetro ponteiro para a PILHA não é modificado.
*     Se ocorrer algum erro durante a destruição, a PILHA resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     PIL_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   PIL_tpCondRet pilhaPush(tppPilha p, void * valor) ;


/***********************************************************************
*
*  $FC Função: PIL  &Esvaziar PILHA
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a PILHA
*
*  $EP Parâmetros
*     pPILHA - ponteiro para a PILHA a ser esvaziada
*
***********************************************************************/

   PIL_tpCondRet DestruirPilha(tppPilha p) ;


/***********************************************************************
*
*  $FC Função: PIL  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a PILHA esteja vazia, insere o primeiro elemento da PILHA.
*
*  $EP Parâmetros
*     pPILHA - ponteiro para a PILHA onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetFaltouMemoria
*
***********************************************************************/

   PIL_tpCondRet pilhaPop(tppPilha p, void ** valor) ;


#undef PILHA_EXT

/********** Fim do módulo de definição: PIL  PILHA duplamente encadeada **********/

#else
#endif
