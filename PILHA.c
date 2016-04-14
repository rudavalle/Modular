#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "LISTA.H"
#include "PILHA.h"

typedef struct tgPilha
{
	LIS_tppLista pLista;
}tpPilha;

void (*exclui) (void * dado);

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

PIL_tpCondRet pilhaPush(tppPilha p, void * valor){

	LIS_tpCondRet CondRet;

	if(p == NULL)
		

	IrFinalLista(p->pLista);

	CondRet = LIS_InserirElementoApos(p->pLista, valor);
	
	if(CondRet == LIS_CondRetFaltouMemoria){
		return PIL_CondRetFaltouMemoria;
	}

	return PIL_CondRetOK;

}

PIL_tpCondRet DestruirPilha(tppPilha p){

	LIS_tpCondRet CondRet;

	if(p == NULL){
		return PIL_CondRetPilhaVazia;
	}

	if(p->pLista == NULL){
		free(p);
		return PIL_CondRetOK;
	}
	
	CondRet = LIS_DestruirLista(p->pLista);

	if(CondRet == LIS_CondRetListaVazia){
		
		return PIL_CondRetPilhaVazia;
	}

	free(p);

	return PIL_CondRetOK;

}

	
PIL_tpCondRet pilhaPop(tppPilha p, void ** valor){
	
	LIS_tpCondRet CondRet;
	
	IrFinalLista(p->pLista);

	*valor = LIS_ObterValor(p->pLista);

	CondRet = LIS_ExcluirElemento(p->pLista);

	if(CondRet == LIS_CondRetListaVazia){
		return PIL_CondRetPilhaVazia;
	}

	return PIL_CondRetOK;

}

int main(void)
{
	
	char * teste = "teste1";
	char * val = "teste2";
	char * ola = "teste3";
	PIL_tpCondRet condRet;
	tpPilha * p;

	
	condRet = criaPilha(&p);

	condRet = pilhaPush(p, (void *) ola);

	condRet = pilhaPop(p, (void **)&teste);

	printf ("%s\n", teste);

	printf("%s\n", teste);
	
	
	return 0;


}
