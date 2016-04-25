/***************************************************************************
*  $MCI Módulo de implementação: TMAT Teste específico para o módulo matriz
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TST
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: C:\LIXO\INSTRUM.BSW
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
*     Este mÇodulo contém as funções específicas para o teste de um módulo.
*     Mais especificamente, contém a função que interpreta os comandos de
*     teste que exercitarão as funções do módulo em teste.
*
*     Caso o módulo em teste requeira um contexto explícito,
*     este contexto deverá ser estabelecido no presente módulo.
*
*     Uma possível maneira é incluir comandos de teste que constróem
*     ou destóem o contexto.
*     Alterar as funções TST_InicializarTeste e TST_TerminarTeste
*     contidas no módulo TesteGen deve ser evitado para manter
*     a integridade do arcabouço ("framework") de teste.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "CEspDin.h"
#include    "lerparm.h"

#include    "matriz.h"

/* Tabela dos nomes dos comandos de teste específicos */

const char RESET_CMD			[ ] = "=resetmatriz"	;
//const char CRIAR_MAT_CMD		[ ] = "=criarmat"       ;
//const char INS_LIN_CMD			[ ] = "=inserirlinha"   ;
//const char INS_COL_CMD			[ ] = "=inserircoluna"  ;
const char DESTRUIR_MAT_CMD		[ ] = "=destruirmat"    ;
const char CRIAR_TAB_CMD		[ ] = "=criartab"       ;
const char EMP_VAL_CMD			[ ] = "=empilhavalor"   ;
const char DESEMP_VAL_CMD		[ ] = "=desempilhavalor";

/* os comandos a seguir somente operam em modo _DEBUG */

const char VER_CABECA_CMD[ ] = "=verificarcabeca" ;
const char VER_MATRIZ_CMD[ ] = "=verificarmatriz" ;
const char VER_MEMORIA_CMD[ ] = "=verificarmemoria" ;
const char DETURPAR_CMD[ ]   = "=deturpar" ;

int estaInicializado = 0 ;

#define DIM_VT_MATRIZES  10

#define DIM_VALOR     100

tppMatriz vtRefMatriz[ DIM_VT_MATRIZES ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int VerificarInx( int inxMatriz ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TMAT &Efetuar operações específicas
*
*  $ED Descrição da função
*     Comandos de teste específicos para testar o módulo matriz:
*
*     Podem ser criadas até 5 matrizes simultaneamente
*     As matrizes são conhecidas pelo seu índice de 0 a 9
*
*     =resetmatriz
*
*     =criar   <inxMatriz>  <Cond ret>
*                   - chama a função MAT_CriarMatriz( )
*
*     =insdir  <inxMatriz> <Char> <Cond ret>
*                   - chama a função MAT_InserirDireita( )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     =insesq  <inxMatriz> <Char> <Cond ret>
*                   - chama a função MAT_InserirEsquerda( )
*
*     =irpai   <inxMatriz> <Cond ret>
*                   - chama a função MAT_IrPai( )
*
*     =iresq   <inxMatriz> <Cond ret>
*                   - chama a função MAT_IrEsquerda( )
*
*     =irdir   <inxMatriz> <Cond ret>
*                   - chama a função MAT_IrDireita( )
*
*     =obter   <inxMatriz> <Char> <Cond ret>
*                   - chama a função MAT_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*
*     =destroi <inxMatriz> <Cond ret>
*                   - chama a função destruirMatriz( )
*
*
*     Estes comandos somente podem ser executados se o modulo tiver sido
*     compilado com _DEBUG ligado
*
*     =verificarcabeca       <inxMatriz>
*
*     =verificarmatriz       <inxMatriz>
*
*     =verificarmemoria
*
*     =deturpar              <inxMatriz> < idCodigoDeturpa >
*
*
*
*     Ver explicação detalhada em TST_ESPC.H
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver condicoes de retorno em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      MAT_tpCondRet CondRetObtido   = MAT_CondRetOK ;
      MAT_tpCondRet CondRetEsperada = MAT_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

	  char   StringDado[  DIM_VALOR ] ;
	  int i ,
				valor;
	  int numColuna,
				numLinha;
      int  NumLidos      = -1 ;
      int  inxMatriz     = -1 ;
	  numColuna = -1;
	  numLinha = -1;
	  valor = -1;

	  StringDado[ 0 ] = 0 ;     

      #ifdef _DEBUG
         int  IntEsperado   = -1 ;
      #endif

      /* Tratar: inicializar contexto */

         if ( strcmp( ComandoTeste , RESET_CMD ) == 0 )
         {

            if ( estaInicializado )
            {
               for( i = 0 ; i < DIM_VT_MATRIZES ; i++ )
               {
                  destruirMatriz( ( vtRefMatriz[ i ] )) ;
               } /* for */
            } /* if */

            for( i = 0 ; i < DIM_VT_MATRIZES ; i++ )
            {
               vtRefMatriz[ i ] = 0 ;
            } /* for */

            estaInicializado = 1 ;

         } /* fim ativa: Tratar: inicializar contexto */

      /* Testar MAT Criar matriz */

   //      else if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
   //      {

   //         NumLidos = LER_LerParametros( "ii" ,
   //                            &inxMatriz , &CondRetEsperada ) ;
   //         if ( ( NumLidos != 2 )
   //           || !VerificarInx( inxMatriz ))
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

			//CondRetObtido = criarMatriz( &(vtRefMatriz[inxMatriz] ));

   //         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
   //                                 "Retorno errado ao criar matriz." );

   //      } /* fim ativa: Testar MAT Criar matriz */

      /* Testar MAT Adicionar linha à matriz */

   //      else if ( strcmp( ComandoTeste , INS_LIN_CMD ) == 0 )
   //      {

   //         NumLidos = LER_LerParametros( "ii" ,
   //                            &inxMatriz , &CondRetEsperada ) ;
   //         if ( ( NumLidos != 2 )
   //           || !VerificarInx( inxMatriz ))
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

			//CondRetObtido = inserirLinha(*vtRefMatriz[inxMatriz]);

   //         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
   //                                 "Retorno errado inserir à direita." );

   //      } /* fim ativa: Testar MAT Adicionar linha à matriz */

   //   /* Testar MAT Adicionar coluna à matriz */

   //      else if ( strcmp( ComandoTeste , INS_COL_CMD ) == 0 )
   //      {

   //         NumLidos = LER_LerParametros( "ii" ,
   //                            &inxMatriz , &CondRetEsperada ) ;
   //         if ( ( NumLidos != 2 )
   //           || !VerificarInx( inxMatriz ))
   //         {
   //            return TST_CondRetParm ;
   //         } /* if */

			//CondRetObtido = inserirColuna(*vtRefMatriz[inxMatriz]);

   //         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
   //                                 "Retorno errado ao inserir à esquerda." );

   //      } /* fim ativa: Testar MAT Adicionar coluna à matriz */

      /* Testar MAT Criar tabuleiro */

         else if ( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iiii" ,
                               &inxMatriz , &numLinha, &numColuna, &CondRetEsperada ) ;
            if ( ( NumLidos != 4 )
              || !VerificarInx( inxMatriz ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = criarTabuleiro(&(vtRefMatriz[inxMatriz]), numLinha, numColuna);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar tabuleiro." );

         } /* fim ativa: Testar MAT Criar tabuleiro */

      /* Testar MAT Empilhar valor */

         else if ( strcmp( ComandoTeste , EMP_VAL_CMD ) == 0 )
         {
			 printf("Entrou no empilhar");

            NumLidos = LER_LerParametros( "iiiii" ,
                               &inxMatriz , &valor, &numLinha, &numColuna, &CondRetEsperada ) ;
            if ( ( NumLidos != 5 )
              || !VerificarInx( inxMatriz ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = 
				empilharValor(vtRefMatriz[0], 1,
				numLinha, numColuna ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao empilhar valor." );

         } /* fim ativa: Testar MAT Empilhar valor */

      /* Testar MAT Desempilhar valor */

         else if ( strcmp( ComandoTeste , DESEMP_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iiii" ,
				&inxMatriz , &numLinha, &numColuna, &CondRetEsperada ) ;
            if ( ( NumLidos != 4 )
              || !VerificarInx( inxMatriz ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = desempilharValor( vtRefMatriz[ inxMatriz ], numLinha, numColuna);			

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao desempilhar valor." );						
			
			
         } /* fim ativa: Testar MAT Desempilhar valor */

		  /* Testar MAT Destruir matriz */
		 else if( strcmp( ComandoTeste, DESTRUIR_MAT_CMD) == 0)
		 {
			 NumLidos = LER_LerParametros( "ii" ,
                               &inxMatriz, &CondRetEsperada  ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxMatriz ))
            {
               return TST_CondRetParm ;
            
			} /* if */

			CondRetObtido = destruirMatriz( vtRefMatriz[ inxMatriz ] );				

			return TST_CompararInt(CondRetEsperada, CondRetObtido,
				"Retorno errado destruir matriz.");

		 }/* fim ativa: Testar MAT Destruir matriz */


      
      return TST_CondRetNaoConhec ;

   } /* Fim função: TMAT &Efetuar operações específicas */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TMAT -Verificar índice de matriz
*
*  $FV Valor retornado
*     0 - inxMatriz não vale
*     1 - inxMatriz vale
*
***********************************************************************/

   int VerificarInx( int inxMatriz )
   {

      if ( ( inxMatriz <   0 )
        || ( inxMatriz >= DIM_VT_MATRIZES ))
      {
         return 0 ;
      } /* if */

      return 1 ;

   } /* Fim função: TMAT -Verificar índice de matriz */
   

/********** Fim do módulo de implementação: TMAT Teste específico para o módulo matriz **********/

