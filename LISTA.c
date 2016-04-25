/***************************************************************************
*  $MCI Mзdulo de implementaусo: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
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
*  $TC Tipo de dados: LIS Descritor da cabeуa de lista
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
               /* NЩmero de elementos da lista */
 
         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a funусo de destruiусo do valor contido em um elemento */
 
   } LIS_tpLista ;
 
/***** Protзtipos das funушes encapuladas no mзdulo *****/
 
   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;
 
   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;
 
   static void LimparCabeca( LIS_tppLista pLista ) ;
 
/*****  Cзdigo das funушes exportadas pelo mзdulo  *****/
 
/***************************************************************************
*
*  Funусo: LIS  &Criar lista
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
 
   } /* Fim funусo: LIS  &Criar lista */


 
/***************************************************************************
*
*  Funусo: LIS  &Inserir elemento antes
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
 
   } /* Fim funусo: LIS  &Inserir elemento antes */
 
/***************************************************************************
*
*  Funусo: LIS  &Inserir elemento apзs
*  ****/
 
   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       
   {
 
      tpElemLista * pElem ;
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      /* Criar elemento a inerir apзs */
 
         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */
 
      /* Encadear o elemento apзs o elemento */
 
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
 
   } /* Fim funусo: LIS  &Inserir elemento apзs */
 
/***************************************************************************
*
*  Funусo: LIS  &Excluir elemento
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
 
      /* Desencadeia Я esquerda */
 
         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */
 
      /* Desencadeia Я direita */
 
         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */
 
      LiberarElemento( pLista , pElem ) ;
 
      return LIS_CondRetOK ;
 
   } /* Fim funусo: LIS  &Excluir elemento */
 
/***************************************************************************
*
*  Funусo: LIS  &Obter referЖncia para o valor contido no elemento
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
 
   } /* Fim funусo: LIS  &Obter referЖncia para o valor contido no elemento */
 
/***************************************************************************
*
*  Funусo: LIS  &Ir para o elemento inicial
*  ****/
 
   void IrInicioLista( LIS_tppLista pLista )
   {
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      pLista->pElemCorr = pLista->pOrigemLista ;
 
   } /* Fim funусo: LIS  &Ir para o elemento inicial */
 
/***************************************************************************
*
*  Funусo: LIS  &Ir para o elemento final
*  ****/
 
   void IrFinalLista( LIS_tppLista pLista )
   {
 
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
 
      pLista->pElemCorr = pLista->pFimLista ;
 
   } /* Fim funусo: LIS  &Ir para o elemento final */
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  -Liberar elemento da lista
*
*  $ED Descriусo da funусo
*     Elimina os espaуos apontados pelo valor do elemento e o
*     prзprio elemento.
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
 
   } /* Fim funусo: LIS  -Liberar elemento da lista */
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  -Criar o elemento
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
 
   } /* Fim funусo: LIS  -Criar o elemento */
 
 
/***********************************************************************
*
*  $FC Funусo: LIS  -Limpar a cabeуa da lista
*
***********************************************************************/
 
   void LimparCabeca( LIS_tppLista * pLista )
   {
 
	  (*pLista)->pOrigemLista = NULL ;
      (*pLista)->pFimLista = NULL ;
      (*pLista)->pElemCorr = NULL ;
      (*pLista)->numElem   = 0 ;
 
   } /* Fim funусo: LIS  -Limpar a cabeуa da lista */
 
/********** Fim do mзdulo de implementaусo: LIS  Lista duplamente encadeada **********/
