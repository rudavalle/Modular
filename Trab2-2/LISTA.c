/***************************************************************************
*  $MCI M?dulo de implementa??o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou?o para a automa??o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza??o dos testes de m?dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist?rico de evolu??o:
*     Vers?o  Autor    Data     Observa??es
*     4       avs   01/fev/2006 criar linguagem script simb?lica
*     3       avs   08/dez/2004 uniformiza??o dos exemplos
*     2       avs   07/jul/2003 unifica??o de todos os m?dulos em um s? projeto
*     1       avs   16/abr/2003 in?cio desenvolvimento
*
***************************************************************************/
 
#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
 
#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN
 
/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/
 
   typedef struct tagElemLista {
 
         void * pValor ;
               /* Ponteiro para o valor contido no elemento */
 
         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */
 
         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */
 
   } tpElemLista ;
 
/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe?a de lista
*
*
***********************************************************************/
 
   typedef struct LIS_tagLista {
 
         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */
 
         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */
 
         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */
 
         int numElem ;
               /* N?mero de elementos da lista */
 
         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun??o de destrui??o do valor contido em um elemento */
 
   } LIS_tpLista ;
 
/***** Prot?tipos das fun??es encapuladas no m?dulo *****/
 
   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;
 
   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;
 
   static void LimparCabeca( LIS_tppLista pLista ) ;
 
/*****  C?digo das fun??es exportadas pelo m?dulo  *****/
 
/***************************************************************************
*
*  Fun??o: LIS  &Criar lista
*  ****/
 
   LIS_tpCondRet LIS_CriarLista(LIS_tppLista * lista, void   ( * ExcluirValor ) ( void * pDado ) )
   {
 
      //LIS_tpLista * pLista = NULL ;
 
      *lista = ( LIS_tpLista *) malloc( sizeof( LIS_tpLista )) ;
      if ( lista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */
 
      LimparCabeca( lista ) ;
 
      (*lista)->ExcluirValor = ExcluirValor ;
 
      return LIS_CondRetOK ;
 
   } /* Fim fun??o: LIS  &Criar lista */


 
/***************************************************************************
*
*  Fun??o: LIS  &Inserir elemento antes
*  ****/
    
   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista , void * pValor)
   {
 
      tpElemLista * pElem ;
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      /* Criar elemento a inerir antes */
 
         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */
 
      /* Encadear o elemento antes do elemento corrente */
 
         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */
 
            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */
 
         pLista->pElemCorr = pElem ;
 
         return LIS_CondRetOK ;
 
   } /* Fim fun??o: LIS  &Inserir elemento antes */
 
/***************************************************************************
*
*  Fun??o: LIS  &Inserir elemento ap?s
*  ****/
 
   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       
   {
 
      tpElemLista * pElem ;
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      /* Criar elemento a inerir ap?s */
 
         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */
 
      /* Encadear o elemento ap?s o elemento */
 
         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */
 
            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;
 
         } /* if */
                   
         pLista->pElemCorr = pElem ;
                   
         return LIS_CondRetOK ;
 
   } /* Fim fun??o: LIS  &Inserir elemento ap?s */
 
/***************************************************************************
*
*  Fun??o: LIS  &Excluir elemento
*  ****/
 
   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {
 
      tpElemLista * pElem ;
 
      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif
 
      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */
 
      pElem = pLista->pElemCorr ;
 
      /* Desencadeia ? esquerda */
 
         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */
 
      /* Desencadeia ? direita */
 
         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */
 
      LiberarElemento( pLista , pElem ) ;
 
      return LIS_CondRetOK ;
 
   } /* Fim fun??o: LIS  &Excluir elemento */
 
/***************************************************************************
*
*  Fun??o: LIS  &Obter refer?ncia para o valor contido no elemento
*  ****/
 
   void * LIS_ObterValor( LIS_tppLista pLista )
   {
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      if ( pLista->pElemCorr == NULL )
      {
        return NULL ;
      } /* if */
 
      return pLista->pElemCorr->pValor ;
 
   } /* Fim fun??o: LIS  &Obter refer?ncia para o valor contido no elemento */
 
/***************************************************************************
*
*  Fun??o: LIS  &Ir para o elemento inicial
*  ****/
 
   void IrInicioLista( LIS_tppLista pLista )
   {
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      pLista->pElemCorr = pLista->pOrigemLista ;
 
   } /* Fim fun??o: LIS  &Ir para o elemento inicial */
 
/***************************************************************************
*
*  Fun??o: LIS  &Ir para o elemento final
*  ****/
 
   void IrFinalLista( LIS_tppLista pLista )
   {
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      pLista->pElemCorr = pLista->pFimLista ;
 
   } /* Fim fun??o: LIS  &Ir para o elemento final */
 
 
/***********************************************************************
*
*  $FC Fun??o: LIS  -Liberar elemento da lista
*
*  $ED Descri??o da fun??o
*     Elimina os espa?os apontados pelo valor do elemento e o
*     pr?prio elemento.
*
***********************************************************************/
 
   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {
 
      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */
 
      free( pElem ) ;
 
      pLista->numElem-- ;
 
   } /* Fim fun??o: LIS  -Liberar elemento da lista */
 
 
/***********************************************************************
*
*  $FC Fun??o: LIS  -Criar o elemento
*
***********************************************************************/
 
   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {
 
      tpElemLista * pElem ;
 
      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */
 
      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;
 
      pLista->numElem ++ ;
 
      return pElem ;
 
   } /* Fim fun??o: LIS  -Criar o elemento */
 
 
/***********************************************************************
*
*  $FC Fun??o: LIS  -Limpar a cabe?a da lista
*
***********************************************************************/
 
   void LimparCabeca( LIS_tppLista * pLista )
   {
 
	  (*pLista)->pOrigemLista = NULL ;
      (*pLista)->pFimLista = NULL ;
      (*pLista)->pElemCorr = NULL ;
      (*pLista)->numElem   = 0 ;
 
   } /* Fim fun??o: LIS  -Limpar a cabe?a da lista */
 
/********** Fim do m?dulo de implementa??o: LIS  Lista duplamente encadeada **********/
