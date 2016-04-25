#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "LISTA.H"

#define PILHA_OWN
#include "PILHA.h"
#undef PILHA_OWN

typedef struct tgPilha
{
	LIS_tppLista pLista;
}tpPilha;

void exclui (void * valor);

PIL_tpCondRet criaPilha(tppPilha * p)
{

	LIS_tpCondRet CondRet;

	*p = (tppPilha)malloc(sizeof(tppPilha));
	
	if(*p == NULL){
		return PIL_CondRetFaltouMemoria;
	}

	CondRet = LIS_CriarLista(&((*p)->pLista), exclui);

	if(CondRet == LIS_CondRetFaltouMemoria){
		return PIL_CondRetFaltouMemoria;
	}

	return PIL_CondRetOK;
	
}

PIL_tpCondRet pilhaPush(tppPilha p, void * valor, int tam){

	LIS_tpCondRet CondRet;

	valor = malloc(sizeof(tam));

	if(p == NULL){
		
		return PIL_CondRetPilhaVazia;
	}

	IrFinalLista(p->pLista);

	CondRet = LIS_InserirElementoApos(p->pLista, valor);
	
	if(CondRet == LIS_CondRetFaltouMemoria){
		return PIL_CondRetFaltouMemoria;
	}

	return PIL_CondRetOK;

}

PIL_tpCondRet DestruirPilha(tppPilha p){

	LIS_tpCondRet CondRet;

	if (p == NULL){
		return PIL_CondRetPilhaVazia;
	}

	if (p->pLista == NULL)
	{
		free(p);
		return PIL_CondRetOK;
	}


	while(LIS_ObterValor(p->pLista) != NULL){
		LIS_ExcluirElemento(p->pLista);
	}

	free(p->pLista);

	free(p);

	return PIL_CondRetOK;

}

	
PIL_tpCondRet pilhaPop(tppPilha p){
	
	LIS_tpCondRet CondRet;
	
	IrFinalLista(p->pLista);

	CondRet = LIS_ExcluirElemento(p->pLista);

	if(CondRet == LIS_CondRetListaVazia){
		return PIL_CondRetPilhaVazia;
	}
	
	return PIL_CondRetOK;

}

void exclui (void * valor){
	free(valor);
}
