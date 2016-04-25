#include <stdio.h>
#include <malloc.h>

#include "PILHA.H"
#include "Matriz.h"

typedef struct tgNo{

	int linha;

	int coluna;

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

/***** Protótipos das funções encapuladas no módulo *****/

 static void destroiNos( tpMatriz * mat );

 static void moverCorrParaRaiz(tppMatriz mat);

 /*****  Código das funções exportadas pelo módulo  *****/


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

void moverCorrParaRaiz(tppMatriz mat){

	mat->noCorr = mat->noRaiz;

}

MAT_tpCondRet inserirLinha(tppMatriz mat){
	int i;
	tpNo * temp;

	mat->qLinha++;
	
	if(mat == NULL){
		return MAT_CondRetMatrizVazia;
	}

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
			
			for(i=0;i < (mat->qColuna); i++){

				tpNo * novo = (tpNo*)malloc(sizeof(tpNo));
				
				if(novo == NULL){
					return MAT_CondRetFaltouMemoria;
				}

				novo->linha = mat->qLinha;
				novo->coluna = (i + 1);

				novo->pilha = NULL;

				mat->noCorr = novo;

				novo->norte = temp;
				temp->sul = novo;

				if(temp->oeste == NULL){
					novo->oeste = NULL;

				}else {
					novo->oeste = temp->oeste->sul;
					novo->norte->oeste->sul->leste = novo;
				}

				novo->leste = NULL;

				novo->sul = NULL;

				if(temp->leste != NULL){
					temp = temp->leste;
				}
			}
	}

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
				novo->linha = mat->qLinha;

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

	if(CondRet != MAT_CondRetOK){
		return CondRet;
	}

	for(i=0;i < numColuna; i++){
		CondRet = inserirColuna(*mat);
	}

	if(CondRet != MAT_CondRetOK){
		return CondRet;
	}

	for(i=1;i < numLinha; i++){
		CondRet = inserirLinha(*mat);
	}

	if(CondRet != MAT_CondRetOK){
		return CondRet;
	}

	moverCorrParaRaiz(*mat);

	return MAT_CondRetOK;

}

MAT_tpCondRet moverSul(tppMatriz mat){

	if(mat == NULL){
		return MAT_CondRetMatrizNaoExiste;
	}

	if(mat->noRaiz == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noCorr->sul == NULL){
		return MAT_CondRetNoNaoExiste;
	}

	mat->noCorr = mat->noCorr->sul;

	return MAT_CondRetOK;

}

MAT_tpCondRet moverLeste(tppMatriz mat){
	
	if(mat == NULL){
		return MAT_CondRetMatrizNaoExiste;
	}

	if(mat->noRaiz == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noCorr->leste == NULL){
		return MAT_CondRetNoNaoExiste;
	}

	mat->noCorr = mat->noCorr->leste;

	return MAT_CondRetOK;

}

MAT_tpCondRet moverOeste(tppMatriz mat){
	
	if(mat == NULL){
		return MAT_CondRetMatrizNaoExiste;
	}

	if(mat->noRaiz == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noCorr->leste == NULL){
		return MAT_CondRetNoNaoExiste;
	}

	mat->noCorr = mat->noCorr->oeste;

	return MAT_CondRetOK;

}

MAT_tpCondRet moverNorte(tppMatriz mat){
	if(mat == NULL){
		return MAT_CondRetMatrizNaoExiste;
	}

	if(mat->noRaiz == NULL){
		return MAT_CondRetMatrizVazia;
	}

	if(mat->noCorr->leste == NULL){
		return MAT_CondRetNoNaoExiste;
	}
	
	mat->noCorr = mat->noCorr->norte;

	return MAT_CondRetOK;

}

MAT_tpCondRet empilharValor(tppMatriz mat, void * valor, int lin, int col){

	MAT_tpCondRet CondRetm;

	PIL_tpCondRet CondRetp;
	
	while(mat->noCorr->linha != lin){

		CondRetm = moverSul(mat);
	}
	
	if(CondRetm != MAT_CondRetOK){
		return CondRetm;
	}

	while(mat->noCorr->coluna != col){
		CondRetm = moverLeste(mat);
	}

	if(CondRetm != MAT_CondRetOK){
		return CondRetm;
	}

	if(mat->noCorr->pilha == NULL){
		tppPilha p;
		
		CondRetp = criaPilha(&p);

		pilhaPush(p, (void *)valor);

		mat->noCorr->pilha = p;

		if(CondRetp != MAT_CondRetOK){
			return MAT_CondRetFaltouMemoria;
		}

	}else {

		CondRetp = pilhaPush(mat->noCorr->pilha, (void*)valor);

	}

	if(CondRetp == PIL_CondRetPilhaVazia){
		
		return MAT_CondRetPilhaVazia;
	}

	if(CondRetp == PIL_CondRetFimPilha){
		
		return MAT_CondRetFimPilha;
	}
	
	moverCorrParaRaiz(mat);

	return CondRetm;
	
}

MAT_tpCondRet desempilharValor(tppMatriz mat, int lin, int col){

	MAT_tpCondRet CondRetm;

	PIL_tpCondRet CondRetp;

	while(mat->noCorr->linha != lin){

		CondRetm = moverSul(mat);
	}

	if(CondRetm != MAT_CondRetOK){
		return CondRetm;
	}
	
	while(mat->noCorr->coluna != col){
		CondRetm = moverLeste(mat);
	}

	if(CondRetm != MAT_CondRetOK){
		return CondRetm;
	}

	if(mat->noCorr->pilha == NULL){
		return MAT_CondRetPilhaVazia;
	}
	
	CondRetp = pilhaPop(mat->noCorr->pilha);

	moverCorrParaRaiz(mat);

	return MAT_CondRetOK;

}


MAT_tpCondRet destruirMatriz(tppMatriz mat){
	
	if(mat != NULL){
		destroiNos(mat);
		free(mat);
	}else {
		return MAT_CondRetMatrizNaoExiste;
	}

	return MAT_CondRetOK;

}


void destroiNos(tpMatriz * mat){
	int i;
	int j=0;
	int z;

	moverCorrParaRaiz(mat);
	
	for(i=0;i<(mat->qColuna);i++){
			free(mat->noCorr);
			moverLeste(mat);

		z=i;
		z++;
		moverCorrParaRaiz(mat);
		while(j<z){
			moverSul(mat);
			j++;
		}
		j=0;
	}
}
