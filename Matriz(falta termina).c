#include <stdio.h>
#include <stdlib.h>

#include "PILHA.H"
#include "Matriz.h"

typedef struct tgNo{
	
	int coluna;

	int linha;

	struct tgNo * norte;

	struct tgNo * sul;
	
	struct tgNo * leste;

	struct tgNo * oeste;

	tppPilha pilha;

}tpNo;

typedef struct tgMatriz{
	
	tpNo * noRaiz;

	tpNo * noCorr;

	int qLinha;

	int qColuna;

}tpMatriz;

MAT_tpCondRet criaMatriz(tppMatriz * mat){
	
	if(mat == NULL){
		return MAT_CondRetMatrizNaoExiste;
	}

	*mat = (tpMatriz*)malloc(sizeof(tpMatriz));

	if(mat == NULL){
		return MAT_CondRetFaltouMemoria;
	}

	(*mat)->noCorr = NULL;
	(*mat)->noRaiz = NULL;
	(*mat)->qColuna = 0;
	(*mat)->qLinha = 0;

	return MAT_CondRetOK;
}

MAT_tpCondRet inserirLinha(tppMatriz mat){

	int i;
	tpNo * temp;
	
	if(mat == NULL){
		return MAT_CondRetMatrizVazia;
	}

	mat->qLinha++;

	if(mat->noRaiz == NULL){
		tpNo * novo = (tpNo*)malloc(sizeof(tpNo));
		
		if(novo == NULL){
			return MAT_CondRetFaltouMemoria;
		}

		mat->qColuna++;

		novo->coluna = mat->qColuna;
		novo->linha = mat->qLinha;
		
		novo->norte = NULL;
		novo->sul = NULL;
		novo->leste = NULL;
		novo->oeste = NULL;
		
		novo->pilha = NULL;

		mat->noRaiz = novo;
		mat->noCorr = novo;
		
	}else {
		
		temp = mat->noRaiz;
			
			while(temp->sul != NULL){
				temp = temp->sul;
			}
			
			for(i=0;i < mat->qColuna; i++){
				tpNo * novo = (tpNo*)malloc(sizeof(tpNo));
				
				if(novo == NULL){
					return MAT_CondRetFaltouMemoria;
				}

				novo->linha = mat->qLinha;
				novo->coluna = (i+1);
				novo->pilha = NULL;

				mat->noCorr = novo;

				novo->norte = temp;
				temp->sul = novo;

				if(temp->oeste == NULL){
					novo->oeste = NULL;
				}else {
					novo->oeste = temp->oeste->sul;
					temp->oeste->sul->leste = novo;
				}

				novo->leste = NULL;

				novo->sul = NULL;

				if(temp->oeste != NULL){
					temp = temp->oeste;
				}
			}
	}

	printf("ola");

	return MAT_CondRetOK;

}

MAT_tpCondRet inserirColuna(tppMatriz mat){
	
	int i;
	tpNo * temp;
	
	if(mat == NULL){
		return MAT_CondRetMatrizVazia;
	}

	mat->qColuna++;

	if(mat->noRaiz == NULL){
		tpNo * novo = (tpNo*)malloc(sizeof(tpNo));
		
		if(novo == NULL){
			return MAT_CondRetFaltouMemoria;
		}

		mat->qLinha++;

		novo->coluna = mat->qColuna;
		novo->linha = mat->qLinha;
		novo->norte = NULL;
		novo->sul = NULL;
		novo->leste = NULL;
		novo->oeste = NULL;
		
		novo->pilha = NULL;

		mat->noRaiz = novo;
		mat->noCorr = novo;
	
	}else {
		
		temp = mat->noRaiz;
			
			while(temp->leste != NULL){
				temp = temp->leste;
			}
			
			for(i=0;i < mat->qLinha; i++){
				tpNo * novo = (tpNo*)malloc(sizeof(tpNo));
				
				if(novo == NULL){
					return MAT_CondRetFaltouMemoria;
				}

				novo->coluna = mat->qColuna;
				novo->linha = (i+1);

				novo->pilha = NULL;
				mat->noCorr = novo;

				novo->oeste = temp;
				temp->leste = novo;

				if(temp->norte == NULL){
					novo->norte = NULL;
				}else {
					novo->norte = temp->norte->leste;
					novo->norte->sul = novo;
				}

				novo->leste = NULL;

				novo->sul = NULL;

				if(temp->sul != NULL){
					temp = temp->sul;
				}

			}
	}


	return MAT_CondRetOK;

}

MAT_tpCondRet criarTabuleiro(tppMatriz * mat, int numColuna, int numLinha){
	
	int i;
	
	MAT_tpCondRet CondRet;

	CondRet = criaMatriz(&(*mat));

	for(i=0;i < numColuna; i++){
		CondRet = inserirColuna(*mat);
	}

	for(i=0;i < numLinha; i++){
		CondRet = inserirLinha(*mat);
	}

}

MAT_tpCondRet moverSul(tppMatriz mat){

	if(mat == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noRaiz == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noCorr->sul == NULL){
		return MAT_CondRetNoNaoExiste;
	}

	mat->noCorr = mat->noCorr->sul;

}

MAT_tpCondRet moverLeste(tppMatriz mat){
	
	if(mat == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noRaiz == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noCorr->leste == NULL){
		return MAT_CondRetNoNaoExiste;
	}

	mat->noCorr = mat->noCorr->leste;

}

MAT_tpCondRet moverCorrParaRaiz(tppMatriz mat){
	
	if(mat == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noRaiz == NULL){
		return MAT_CondRetMatrizVazia;
	}

	mat->noCorr = mat->noRaiz;

}

MAT_tpCondRet empilhaValor(tppMatriz mat, void * valor, int col, int lin){

	MAT_tpCondRet CondRetm;

	PIL_tpCondRet CondRetp;

	tppPilha p;

	CondRetp = criaPilha(&p);
	
	while(mat->noCorr->linha != lin){

		CondRetm = moverSul(mat);
	}
	
	while(mat->noCorr->coluna != col){
		CondRetm = moverLeste(mat);
	}

	pilhaPush(p, (void *)valor);

	mat->noCorr->pilha = p;
	
	return CondRetm;

}

int main(void){
	int i = 1;
	MAT_tpCondRet CondRet;

	tpMatriz * mat;

	//criaMatriz(&mat);

	criarTabuleiro(&mat, 4, 4);

	//moverCorrParaRaiz(mat);

	//moverSul(mat);

	printf("%d", mat->noCorr->linha);

	

return 0;

}
