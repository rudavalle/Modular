/***************************************************************************
*  $MCI Módulo de implementação: TPIL Teste pilha de símbolos
*
*  Arquivo gerado:              TestPIL.c
*  Letras identificadoras:      TPIL
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PILHA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   04/abr/2016 criar linguagem script simbólica
*     3       avs   11/abr/2016 uniformização dos exemplos
*     2       avs   18/abr/2016 unificação de todos os módulos em um só projeto
*     1       avs   24/abr/2016 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"

#include    "Pilha.h"

const char RESET_PILHA_CMD[]			= "=resetteste";
const char CRIAR_PILHA_CMD[]			= "=criapilha";
const char DESTRUIR_PILHA_CMD[]			= "=destruirpilha";
const char ESVAZIAR_PILHA_CMD[]			= "=esvaziarpilha";
const char PUSH_ELEM_CMD[]				= "=push";
const char POP_ELEM_CMD[]				= "=pop";

#define TRUE  1
#define FALSE 0

#define DIM_VT_PILHA   14
#define DIM_VALOR     100

tppPilha vtRefPilhas[DIM_VT_PILHA];

tppPilha vtPilhas[DIM_VT_PILHA];

/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxPilha(int inxPilha);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPIL &Testar pilha
*
*  $ED Descrição da função
*     Podem ser criadas até 14 pilhas, identificadas pelos índices 0 a 13
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de pilhas. Provoca vazamento de memória
*     =criarpilha                   inxPilha	CondRetEsp
*     =destruirpilha                inxPilha	CondRetEsp
*     =esvaziarpilha                inxPilha	CondRetEsp
*     =push							inxPilha	string				CondRetEsp
*     =pop							inxPilha	inxString			CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	TST_tpCondRet CondRet;
	char   StringDado[DIM_VALOR];
	char * pDado;	
	int i;

	int inxPilha = -1,
		numLidos = -1,
		CondRetEsp = -1;

	int numElem = -1;

	StringDado[0] = 0;

	/* Efetuar reset de teste de pilha */

	if (strcmp(ComandoTeste, RESET_PILHA_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_PILHA; i++)
		{
			vtPilhas[i] = NULL;
		} /* for */

		for (i = 0; i < DIM_VT_PILHA; i++)
		{
			vtRefPilhas[i] = NULL;
		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de pilha */

	/* Testar CriarPilha */

	else if (strcmp(ComandoTeste, CRIAR_PILHA_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&inxPilha, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxPilha(inxPilha)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = criaPilha(&(vtRefPilhas[inxPilha]));

		return TST_CompararInt(CondRetEsp, CondRet,
			"Erro em ponteiro de nova pilha.");

	} /* fim ativa: Testar CriarPilha */


	/* Testar Destruir pilha */

	else if (strcmp(ComandoTeste, DESTRUIR_PILHA_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&inxPilha, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxPilha(inxPilha)))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = DestruirPilha(vtRefPilhas[inxPilha]);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar destruir a pilha.");

	} /* fim ativa: Testar Destruir pilha */

	/* Testar empilhar elemento */

	else if (strcmp(ComandoTeste, PUSH_ELEM_CMD) == 0)
	{
		numLidos = LER_LerParametros("isi",
			&inxPilha, StringDado, &CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarInxPilha(inxPilha)))
		{
			return TST_CondRetParm;
		} /* if */

		pDado = (char *)malloc(strlen(StringDado) + 1);
		if (pDado == NULL)
		{
			return TST_CondRetMemoria;
		} /* if */

		strcpy(pDado, StringDado);


		CondRet = pilhaPush(vtRefPilhas[inxPilha], pDado);

		if (CondRet != PIL_CondRetOK)
		{
			free(pDado);
		} /* if */

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao empilhar.");

	} /* fim ativa: Testar empilhar elemento */

	/* Testar desempilhar elemento */

	else if (strcmp(ComandoTeste, POP_ELEM_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&inxPilha, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxPilha(inxPilha)))
		{
			return TST_CondRetParm;
		} /* if */

		pDado = (char *)malloc(strlen(StringDado) + 1);
		
		strcpy(pDado, StringDado);

		CondRet = pilhaPop(vtRefPilhas[inxPilha]);

		if (CondRet != PIL_CondRetOK)
		{
			free(pDado);
		} /* if */

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao desempilhar.");

	} /* fim ativa: Testar desempilhar elemento */


	return TST_CondRetNaoConhec;

} /* Fim função: TPIL &Testar pilha */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TPIL -Validar indice de pilha
*
***********************************************************************/

int ValidarInxPilha(int inxPilhas)
{

	if ((inxPilhas <   0)
		|| (inxPilhas >= DIM_VT_PILHA))
	{
		return FALSE;
	} /* if */

	return TRUE;

} /* Fim função: TPIL -Validar indice de pilha */

/********** Fim do módulo de implementação: TPIL Teste pilha de símbolos **********/
