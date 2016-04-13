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
	*p = NULL;

	*p = (tppPilha)malloc(sizeof(tppPilha));
	
	if(*p == NULL)
		return PIL_CondRetOK;

	(*p)->pLista = LIS_CriarLista(exclui);

	return PIL_CondRetOK;

}

PIL_tpCondRet pilhaPush(tpPilha * p, void * valor){

	LIS_tpCondRet CondRet;

	if(p == NULL)
		

	IrFinalLista(p->pLista);

	CondRet = LIS_InserirElementoApos(p->pLista, valor);

	return PIL_CondRetOK;

}

PIL_tpCondRet DestruirPilha(tpPilha * p){

	LIS_tpCondRet CondRet;

	if(p->pLista == NULL){
		free(p);
		return PIL_CondRetOK;
	}
	
	LIS_DestruirLista(p->pLista);

	free(p);

	return PIL_CondRetOK;

}
	
	
PIL_tpCondRet pilhaPop(tpPilha * p, void ** valor)
{
	
	LIS_tpCondRet CondRet;

	*valor = NULL;
	
	IrFinalLista(p->pLista);

	*valor = LIS_ObterValor(p->pLista);

	CondRet = LIS_ExcluirElemento(p->pLista);

	return PIL_CondRetOK;

}

int main(void)
{

	PIL_tpCondRet condRet;
	tpPilha * p;
	int * val2 = (int*)malloc(sizeof(int));
	int val;
	condRet = criaPilha(&p);
	val = 30;
	*val2 = 40;

	pilhaPush(p, (void *) val);

	pilhaPop(p, (void **)&val2);

	printf("%d", val2);
	
	
	return 0;


}
