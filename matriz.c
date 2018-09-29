#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matriz.h"

matriz montamatriz(int* vetor, int N,matriz m){
    //***************************************************************
    //Função que constrói uma matriz NxN com os valores de máximo,mínimo
    //e soma dos intervalos de um vetor. 
    //No final a matriz nova é retornada
    //***************************************************************
	int i,j,k;

	for(i=1; i<=N; i++){//Os dois primeiros laços for percorrem toda a matriz quadrada
		for(j=1;j<=N;j++){
			if(i<=j){//preenchem a matriz apenas onde precisa
                m[i][j].Max = vetor[i];
                m[i][j].Min = vetor[i];
                m[i][j].Sum = 0;
				for(k=i;k<=j;k++){//este laço percorre o vetor dado realizando as somas e definindo max e min
                    m[i][j].Sum= m[i][j].Sum + vetor[k];

                    if(vetor[k]<m[i][j].Min){//define o mínimo
                        m[i][j].Min=vetor[k];
                    }
                    if(vetor[k]>m[i][j].Max){//define o máximo
                        m[i][j].Max=vetor[k];
                    }
                }
            }

        }
    }
    return m;
}

matriz ADD(matriz m, int* vetor, int A, int B, int N){
    //***************************************************************
    //Função que atualiza os valores do vetor em +1
    //Após a atualização a função cria uma matriz com o novo vetor e 
    //no final a matriz nova é retornada
    //***************************************************************
    int i;

    for(i=A;i<=B;i++){
        vetor[i]++;
    }

    m = montamatriz(vetor,N,m);
    return m;
}

matriz SUB(matriz m, int* vetor, int A, int B, int N){
    //***************************************************************
    //Função que atualiza os valores do vetor em -1
    //Após a atualização a função cria uma matriz com o novo vetor e 
    //no final a matriz nova é retornada
    //***************************************************************
    int i;

    for(i=A;i<=B;i++){
        vetor[i]--;
    }

    m = montamatriz(vetor,N,m); 
    return m;
}

int main(){
	int N,M,A,B;
	int i,j;
	int* vetor;
	char* operacao = (char*)malloc (3*sizeof(char));

	scanf("%d%d",&N,&M);
	vetor = (int*) malloc ((N+1)*sizeof(int));
	for(i=1;i<=N;i++){
		scanf("%d",&vetor[i]);
	}
	//Alocação da matriz;
	matriz tabela= (elemento**)malloc((N+1)*sizeof(elemento*));
	for(i=1; i<=N;i++){
        tabela[i]= (elemento*)malloc(N*sizeof(elemento));
	}

	tabela = montamatriz(vetor,N,tabela);

    for(i=1;i<=N;i++){
        for(j=1;j<=N;j++){
                if(i<=j)
          printf("%d%d(%d,%d,%d)\n",i,j,tabela[i][j].Min,tabela[i][j].Max,tabela[i][j].Sum);
        }}

	for(i=0;i<M;i++){
		scanf("%s %d %d",operacao,&A,&B);
		if(strcmp("Add",operacao) == 0){
            tabela= ADD(tabela,vetor,A,B,N);
		}
		else if(strcmp("Sub",operacao) == 0){
            tabela= SUB(tabela,vetor,A,B,N);
		}
		else if(strcmp("Min",operacao) == 0){
            printf("%d\n",tabela[A][B].Min);
		}
		else if(strcmp("Max",operacao) == 0){
            printf("%d\n",tabela[A][B].Max);
		}
		else if(strcmp("Sum",operacao) == 0){
            printf("%d\n",tabela[A][B].Sum);
		}

	}
	free(tabela);
	free(vetor);
	free(operacao);
	return 0;
}
