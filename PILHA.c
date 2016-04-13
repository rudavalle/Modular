#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
#include "LISTA.H"
#include "PILHA.h"
 
typedef struct tgPilha{
    LIS_tppLista lista;
}tpPilha;
 
void (*exclui) (void * dado);
 
PIL_tpCondRet criaPilha(tpPilha ** p){
 
    tpPilha * p = (tpPilha*)malloc(sizeof(tpPilha));
     
    if(p == NULL)
        return PIL_CondRetOK;
 
    (*p)->lista = LIS_CriarLista(exclui);
 
    return PIL_CondRetOK;
 
}
 
PIL_tpCondRet pilhaPush(tpPilha * p, void * valor){
 
    LIS_tpCondRet CondRet;
 
    if(p == NULL)
         
 
    IrFinalLista(p->lista);
 
    CondRet = LIS_InserirElementoApos(p->lista, valor);
 
    return PIL_CondRetOK;
 
}
 
PIL_tpCondRet DestruirPilha(tpPilha * p){
 
    LIS_tpCondRet CondRet;
 
    if(p->lista == NULL){
        free(p);
        return PIL_CondRetOK;
    }
     
    LIS_DestruirLista(p->lista);
 
    free(p);
 
    return PIL_CondRetOK;
 
}
     
     
PIL_tpCondRet pilhaPop(tpPilha * p, void * valorProcura, void ** valor){
     
    LIS_tpCondRet CondRet;
 
    *valor = NULL;
     
    IrFinalLista(p->lista);
 
    CondRet = LIS_ProcurarValor(p->lista, valorProcura);
 
    *valor = LIS_ObterValor(p->lista);
 
    CondRet = LIS_ExcluirElemento(p->lista);
 
    return PIL_CondRetOK;
 
}
