/*
https://docs.google.com/document/d/1n2K9iVMPZMRXeMMaGEXGU1qGXTD1TE6DZbKHPIa3zKE/edit
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//struct
typedef struct{
	int li, lf, ci, cf;
}ROI;
//aloca memoria
char** alocaMemoriaMatriz(int tam, int tm){
	char** ar;
	ar = (char**) malloc(tam*sizeof(char*));
	for (int i=0; i < tam; i++){
  	  ar[i] = (char*) malloc(tm*sizeof(char));
	}
	return ar;
}
char* alocaMemoriaVetor(int tm){
	char* vet;
	vet = (char*) malloc(tm);
	return vet;
}

//libera memoria
void freeMatriz(char** ar, int tam){
	for (int i=0; i < tam; i++){
  	  free(ar[i]);
	}
	free(ar);
}
void freeVet(char* vet){
	free(vet);
}
//recebe tamanho da grade
int recebeTamanhoGrade(){
	int tm;
	printf("Insira o altura ou comprimento da matriz quadrada: \n");
	scanf("%i", &tm);
	return tm;
}
//recebe vetor
char * recebeGrade(int tm){
	char* grade = alocaMemoriaVetor((pow(tm, 2)));
	printf("\nInsira os valores para formar o caça palavras(em vetor): \n");
	getc(stdin);
	scanf("%[^\n]", grade);
	return grade;
}
//print matriz
void printMatriz(int tm, char* vet){
	printf("\n");
    for(int i = 0; i < tm; i++){
   	 for(int j = 0;j < tm; j++){
   	 printf(" %c ", vet[(j+i*tm)]);
   	 }
    printf("\n");
    }
}
//receve quantidade de palavras
int recebeQuantidadeDePalavras(){
	int tam;
	printf("\nInsira o numero de palavras que precisa encontrar: \n");
	scanf("%i", &tam);
	return tam;
}
//recebe palavras
char ** recebePalavras(int tm, int tam){
	char** palavras;
	palavras = alocaMemoriaMatriz(tam, tm);
	for(int i = 0; i < tam; i++){
    	printf("Escreva a palavra %i (tamanho maximo=%i):", (i+1), tm);
    	getc(stdin);
    	scanf("%[^\n]", palavras[i]);
	}
	return palavras;
}
//caso nao encontrado
ROI semPosicao(){
	ROI posicao = (ROI){.li = 0, .ci = 0, .lf = 0, .cf = 0};
	return posicao;
}
//verifica horizontal
ROI verificaHorizontal(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
	for(k = 0; (k < tmpalavra) && (k+i < tm) && (grade[((k+j)+i*tm)] == palavra[k]); k++){}
	ROI posicao;
	if(k == tmpalavra){
    	posicao = (ROI){.li = j, .ci = i, .lf = (j+k-1), .cf = i};
	}else{
    	posicao = semPosicao();
	}
	return posicao;
}
//verifica vertical
ROI verificaVertical(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
	for(k = 0; (k < tmpalavra) && (k+i < tm) && (grade[(j+(i+k)*tm)] == palavra[k]); k++){}
	ROI posicao;
	if(k == tmpalavra){
    	posicao = (ROI){.li = j, .ci = i, .lf = j, .cf = (i+k-1)};
	}else{
    	posicao = semPosicao();
	}
	return posicao;
}
//verifica diagonal para baixo
ROI verificaDiagonalParaBaixo(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
	for(k = 0; (k < tmpalavra) && (k+i < tm) && (k+j < tm) && (grade[((j+k)+(i+k)*tm)] == palavra[k]); k++){}
	ROI posicao;
	if(k == tmpalavra){
    	posicao = (ROI){.li = j, .ci = i, .lf = (j+k-1), .cf = (i+k-1)};
	}else{
    	posicao = semPosicao();
	}
	return posicao;
}
//verifica diagonal para cima
ROI verificaDiagonalParaCima(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
	for(k = 0; (k < tmpalavra) && (i-k >= 0) && (k+j < tm) && (grade[((j+k)+(i-k)*tm)] == palavra[k]); k++){}
	ROI posicao;
	if(k == tmpalavra){
    	posicao = (ROI){.li = j, .ci = i, .lf = (j+k-1), .cf = (i-k+1)};
	}else{
    	posicao = semPosicao();
	}
	return posicao;
}
//verifica horizontal invertida
ROI verificaHorizontalInvertida(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
    for(k = 0; (k < tmpalavra) && (j-k >= 0) && (grade[((j-k)+i*tm)] == palavra[k]); k++){}
	ROI posicao;
	if(k == tmpalavra){
    	posicao = (ROI){.li = j, .ci = i, .lf = (j-k+1), .cf = i};
	}else{
    	posicao = semPosicao();
	}
	return posicao;
}
//verifica vertical invertida
ROI verificaVerticalInvertida(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
	for(k = 0; (k < tmpalavra) && (i-k < tm) && (grade[(j+(i-k)*tm)] == palavra[k]); k++){}
	ROI posicao;
	if(k == tmpalavra){
    	posicao = (ROI){.li = j, .ci = i, .lf = j, .cf = (i-k+1)};
	}else{
    	posicao = semPosicao();
	}
	return posicao;
}
//verifica diagonal para baixo invertida
ROI verificaDiagonalParaBaixoInvertida(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
    for(k = 0; (k < tmpalavra) && (k+i < tm) && (j-k >= 0) && (grade[((j-k)+(i+k)*tm)] == palavra[k]); k++){}
	ROI posicao;
    	if(k == tmpalavra){
        	posicao = (ROI){.li = j, .ci = i, .lf = (j-k+1), .cf = (i+k-1)};
    	}else{
        	posicao = semPosicao();
    	}
	return posicao;
}
//verifica diagonal para cima invertida
ROI verificaDiagonalParaCimaInvertida(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	int k;
    for(k = 0; (k < tmpalavra) && (j-k >= 0) && (j-k >= 0) && (grade[((j-k)+(i-k)*tm)] == palavra[k]); k++){}
	ROI posicao;
    	if(k == tmpalavra){
        	posicao = (ROI){.li = j, .ci = i, .lf = (j-k+1), .cf = (i-k+1)};
    	}else{
        	posicao = semPosicao();
    	}
	return posicao;
}
//verifica palavra na posicao
ROI verificaPalavraPosicao(int tm, char* grade, char* palavra, int tmpalavra, int i, int j){
	ROI posicao = semPosicao();
	if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
   	 posicao = (ROI) verificaHorizontal(tm, grade, palavra, tmpalavra, i, j);
   	 if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
        	posicao = (ROI) verificaVertical(tm, grade, palavra, tmpalavra, i, j);
   		 if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
            	posicao = (ROI) verificaDiagonalParaBaixo(tm, grade, palavra, tmpalavra, i, j);
            	if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
                	posicao = (ROI) verificaDiagonalParaCima(tm, grade, palavra, tmpalavra, i, j);
                	if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
                    	posicao = (ROI) verificaHorizontalInvertida(tm, grade, palavra, tmpalavra, i, j);
                    	if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
                        	posicao = (ROI) verificaVerticalInvertida(tm, grade, palavra, tmpalavra, i, j);
                        	if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
                            	posicao = (ROI) verificaDiagonalParaBaixoInvertida(tm, grade, palavra, tmpalavra, i, j);
                            	if(posicao.li == 0 && posicao.ci==0 && posicao.lf == 0 && posicao.cf == 0){
                                	posicao = (ROI) verificaDiagonalParaCimaInvertida(tm, grade, palavra, tmpalavra, i, j);
                            	}
                        	}
                    	}
                	}
            	}
   	 	}
   	 }
	}
	return posicao;
}
//verifica palavra
ROI localizaPalavra(int tm, char* grade, char* palavra){
    int j = 0, i = 0;
	//tamanho da palavra
	int tmpalavra = strlen(palavra);
	//ROI
    ROI posicao = semPosicao();
    for(i = 0; i < tm; i++){
   	 for(j = 0; j < tm; j++){
   		 //se letra = 1 letra da palavra
   		 if(palavra[0] == grade[(j+i*tm)] ){
   		 	posicao = (ROI) verificaPalavraPosicao(tm, grade, palavra, tmpalavra, i, j);
   		 }
        	if(posicao.li!=0 || posicao.ci!=0 || posicao.lf!=0 || posicao.cf!=0){
            	return posicao;
        	}
   	 }
    }
    return posicao;
}

int main(){
//grade
	//grade[] = {"SAPAACAVAAAAPADAVUUJTAPAAPASONASJAVMVARAJPOATRRASRAOJALORAAAOPAOMOUPSLPAPPMVAUAAOATALSVAPAAOTTRAASOP"};
	int tm = recebeTamanhoGrade();
	char * grade = recebeGrade(tm);
	//print matriz
    printMatriz(tm, grade);
	//palavras para pesquisar
	int tam = recebeQuantidadeDePalavras();
	char ** palavras = recebePalavras(tm, tam);
	//varaveis
	ROI posicao[tam];
    //acha palavra
    for(int i = 0; i < tam; i++){
   	 char* palavra = &palavras[i][0];
   	 posicao[i] = localizaPalavra (tm, grade, palavra);
    	printf("\n %s: \n [%i][%i] ate [%i][%i]", palavra, posicao[i].li, posicao[i].ci, posicao[i].lf, posicao[i].cf);
	}
	//limpa matriz
	freeVet(grade);
	freeMatriz(palavras, tam);
    return 0;
}
