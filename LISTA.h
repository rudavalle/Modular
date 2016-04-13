#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Mзdulo de definiусo: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouуo para a automaусo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizaусo dos testes de mзdulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histзrico de evoluусo:
*     Versсo  Autor    Data     Observaушes
*     4       avs   01/fev/2006 criar linguagem script simbзlica
*     3       avs   08/dez/2004 uniformizaусo dos exemplos
*     2       avs   07/jul/2003 unificaусo de todos os mзdulos em um sз projeto
*     1       avs   16/abr/2003 inьcio desenvolvimento
*
*  $ED Descriусo do mзdulo
*     Implementa listas genжricas duplamente encadeadas.
*     Podem existir n listas em operaусo simultaneamente.
*     As listas possuem uma cabeуa encapsulando o seu estado.
*
*     Cada lista ж homogЖnea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contжm.
*
*     Os ponteiros para os dados sсo copiados para elementos da lista.
*        Nсo ж copiado o valor apontado por estes ponteiros.
*
*     O controle da destruiусo do valor de um elemento a ser excluьdo
*        ж realizado por uma funусo fornecida pelo usuрrio.
*
*     Cada lista referencia uma funусo que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A funусo de liberaусo dos valores contidos nos elementos deve
*        assegurar a liberaусo de todos os espaуos referЖnciados pelo
*        valor contido em um elemento.
*        Esta funусo ж chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso nсo seja necessрrio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a funусo de liberaусo poderр ser NULL .
*        Caso o elemento da lista seja a Щnica Рncora do valor referenciado,
*        esta funусo deve promover a destruiусo (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
  
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif
 
/***** Declaraушes exportadas pelo mзdulo *****/
 
/* Tipo referЖncia para uma lista */
 
typedef struct LIS_tagLista * LIS_tppLista ;
 
 
/***********************************************************************
*
*  $TC Tipo de dados: LIS Condiушes de retorno
*
*
*  $ED Descriусo do tipo
*     Condiушes de retorno das funушes da lista
*
***********************************************************************/
 
   typedef enum {
 
         LIS_CondRetOK ,
               /* Concluiu corretamente */
 
         LIS_CondRetListaVazia ,
               /* A lista nсo contжm elementos */
 
         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */
 
         LIS_CondRetNaoAchou ,
               /* Nсo encontrou o valor procurado */
 
         LIS_CondRetFaltouMemoria
               /* Faltou memзria ao tentar criar um elemento de lista */
 
   } LIS_tpCondRet ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Criar lista
*
*  $ED Descriусo da funусo
*     Cria uma lista genжrica duplamente encadeada.
*     Os possьveis tipos sсo desconhecidos a priori.
*     A tipagem ж implicita.
*     Nсo existe identificador de tipo associado Я lista.
*
*  $EP ParРmetros
*     ExcluirValor  - ponteiro para a funусo que processa a
*                     exclusсo do valor referenciado pelo elemento
*                     a ser excluьdo.
*                     Ver descriусo do mзdulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro serр utilizado pelas funушes que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memзria ou dados errados,
*     a funусo retornarр NULL.
*     Nсo serр dada mais informaусo quanto ao problema ocorrido.
*
***********************************************************************/
 
   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Destruir lista
*
*  $ED Descriусo da funусo
*     Destrзi a lista fornecida.
*     O parРmetro ponteiro para a lista nсo ж modificado.
*     Se ocorrer algum erro durante a destruiусo, a lista resultarр
*     estruturalmente incorreta.
*     OBS. nсo existe previsсo para possьveis falhas de execuусo.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/
 
   void LIS_DestruirLista( LIS_tppLista pLista ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Esvaziar lista
*
*  $ED Descriусo da funусo
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP ParРmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/
 
   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Inserir elemento antes
*
*  $ED Descriусo da funусo
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP ParРmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/
 
   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Inserir elemento apзs
*
*  $ED Descriусo da funусo
*     Insere novo elemento apрs o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP ParРmetros
*     ParРmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/
 
   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Excluir elemento
*
*  $ED Descriусo da funусo
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente serр o novo corrente.
*     Se nсo existir e existir o elemento Я direita, este se tornarр corrente.
*     Se este tambжm nсo existir a lista tornou-se vazia.
*
*  $EP ParРmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/
 
   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Obter referЖncia para o valor contido no elemento
*
*  $ED Descriусo da funусo
*     Obtem a referЖncia para o valor contido no elemento corrente da lista
*
*  $EP ParРmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     nсo NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/
 
   void * LIS_ObterValor( LIS_tppLista pLista ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Ir para o elemento inicial
*
*  $ED Descriусo da funусo
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista estр vazia.
*
*  $EP ParРmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/
 
   void IrInicioLista( LIS_tppLista pLista ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Ir para o elemento final
*
*  $ED Descriусo da funусo
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista estр vazia.
*
*  $EP ParРmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/
 
   void IrFinalLista( LIS_tppLista pLista ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Avanуar elemento
*
*  $ED Descriусo da funусo
*     Avanуa o elemento corrente numElem elementos na lista
*     Se numElem for positivo avanуa em direусo ao final
*     Se numElem for negativo avanуa em direусo ao inьcio
*     numElem pode ser maior do que o nЩmro de elementos existentes na
*               direусo desejada
*     Se numElem for zero somente verifica se a lista estр vazia
*
*  $EP ParРmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o nЩmero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista estр vazia
*
***********************************************************************/
 
   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  &Procurar elemento contendo valor
*
*  $ED Descriусo da funусo
*     Procura o elemento que referencia o valor dado.
*     A funусo compara ponteiro e nсo conteЩdo apontado.
*
*  $EP ParРmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente ж o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contжm o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro nсo foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/
 
   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;
 
#undef LISTA_EXT
 
/********** Fim do mзdulo de definiусo: LIS  Lista duplamente encadeada **********/
 
#else
#endif
