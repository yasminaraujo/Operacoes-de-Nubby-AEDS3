//arvore.c
//Solução para o tp0 com a implementação de uma árvore segmentada


#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

arvore constroi(int* vetor, int atual, int esq, int dir,arvore arv){
	//***************************************************************
	//Função que constrói uma segment tree por meio de recursividade
	//int atualdir,atualesq: variáveis que indicam o índice do filhos 
	//da direita e esquerda, respectivamente
	//***************************************************************
	int meio,atualdir,atualesq;

	if(esq == dir){ //define o valor para as folhas
		arv[atual].Sum = vetor[esq];
		arv[atual].Max = vetor[esq];
		arv[atual].Min = vetor[esq];
		arv[atual].dir = dir;
		arv[atual].esq = esq;
    }

	else{ 
		meio = (esq+dir)/2;
		atualesq = atual*2;
		atualdir = (atual*2)+1;

		constroi(vetor,atualesq,esq,meio,arv); //chama a recursividade para os ramos da esquerda
		constroi(vetor,atualdir,meio+1,dir,arv);//chama a recursividade para os ramos da direita
		
		//Soma o valor das somas dos filhos do nódulo para caso ele não seja uma folha
		arv[atual].Sum = arv[atualesq].Sum + arv[atualdir].Sum;  

		//Compara os valores de máximo e mínimo entre os filhos para achar os valores para o nódulo
		if(arv[atualdir].Max > arv[atualesq].Max){
        	arv[atual].Max = arv[atualdir].Max;
		}
        else{
            arv[atual].Max = arv[atualesq].Max;
        }
        if(arv[atualdir].Min < arv[atualesq].Min){
            arv[atual].Min = arv[atualdir].Min;
        }
        else{
            arv[atual].Min = arv[atualesq].Min;
        }

        //Guarda o valor do intervalo do vetor que o nódulo abrange 
		arv[atual].dir = dir;
		arv[atual].esq = esq;
	}

	return arv;
}

elemento pesquisa (arvore arv, int A, int B, int atual){
    //***************************************************************
    //Função que pesquisa um intervalo do vetor no árvore
    //int atualdir,atualesq: variáveis que indicam o índice do filhos 
    //da direita e esquerda, respectivamente
    //elemento esquerda, direita: Elementos que salvam a recursão para
    // esquerda e direita, respectivamente
    //elemento novo: elemento retornado na recursão, ou seja, o intervalo
    //procurado
    //***************************************************************

    int atualesq, atualdir;
    elemento esquerda,direita,novo;

    if (B< arv[atual].esq || arv[atual].dir <A){//caso o intervalo não esteja na árvore
        novo.Sum = 0; // a soma retornada será 0
        novo.Max = -2147483647; //valores limite de entrada definidos na documentação
        novo.Min = 2147483647;
        return novo;
    }
    else if(A <= arv[atual].esq && arv[atual].dir<= B ){//caso o intervalo esteja completamente contido na árvore
         return arv[atual]; //retorna o próprio nódulo da ávore

    }

        atualesq = atual*2;
        atualdir = (atual*2)+1;


        esquerda=pesquisa(arv,A,B,atualesq); // começa a recursão para a esquerda
        direita=pesquisa(arv,A,B,atualdir); // começa a recursão para a direita

        novo.Sum = esquerda.Sum + direita.Sum; //a soma do intervalo é igual a soma dos seus filhos na árvore

        //comparações com os filhos para achar o máximo e o mínimo.
        if(esquerda.Min < direita.Min){ 
            novo.Min = esquerda.Min;
        }
        else{
            novo.Min=direita.Min;
        }
        if(direita.Max > esquerda.Max){
            novo.Max = direita.Max;
		}
        else{
            novo.Max = esquerda.Max;
        }

        return novo;
}

void ADD (arvore arv, int A, int B, int atual){
    //***************************************************************
    //Função que atualiza o valor do intervalo adicionando +1 em cada
    //elemento
    //int atualdir,atualesq: variáveis que indicam o índice do filhos 
    //da direita e esquerda, respectivamente
    //elemento esquerda,direita,novo: vide explicação dos elementos de 
    //mesmo nome na função pesquisa.
    //***************************************************************
    int atualesq, atualdir;
    elemento esquerda,direita,novo;

    if (B< arv[atual].esq || arv[atual].dir <A){ //caso o intervalo não esteja contido
        return;
    }
    if(arv[atual].esq == arv[atual].dir){//caso seja um nó folha
         arv[atual].Max++; //como no nó folha todos os valores são iguais soma +1 para todos
         arv[atual].Min++;
         arv[atual].Sum++;

         return;
    }

    atualesq = 2*atual;
    atualdir = atualesq+1;

        ADD(arv,A,B,atualesq); //começa a recursão para a esquerda
        ADD(arv,A,B,atualdir); // começa a recursão para a direita


        arv[atual].Sum = arv[atualesq].Sum + arv[atualdir].Sum; //atualiza a soma

        //Compara os max e min para atualiza-los
        if(arv[atualesq].Min < arv[atualdir].Min){
           arv[atual].Min=arv[atualesq].Min;
        }
        else{
            arv[atual].Min=arv[atualdir].Min;
        }
        if(arv[atualdir].Max > arv[atualesq].Max){
            arv[atual].Max = arv[atualdir].Max;
		}
        else{
            arv[atual].Max = arv[atualesq].Max;
        }

        return;
}

void SUB (arvore arv, int A, int B, int atual){
    //***************************************************************
    //Função que atualiza o valor do intervalo subtraindo -1 em cada
    //elemento
    //Esta função funciona exatamente igual a ADD, com a diferença que
    //subtrai ao contrário de somar
    //***************************************************************
    int atualesq, atualdir;
    elemento esquerda,direita,novo;

    if (B< arv[atual].esq || arv[atual].dir <A){
        return;
    }

    if(arv[atual].esq == arv[atual].dir){ //laço condicional que a diferencia da ADD
         arv[atual].Max--; // subtrai -1 dos elementos da folha
         arv[atual].Min--;
         arv[atual].Sum--;

         return;
    }

        atualesq = 2*atual;
        atualdir = atualesq+1;

        SUB(arv,A,B,atualesq);
        SUB(arv,A,B,atualdir);


        arv[atual].Sum = arv[atualesq].Sum + arv[atualdir].Sum;

        if(arv[atualesq].Min < arv[atualdir].Min){
           arv[atual].Min=arv[atualesq].Min;
        }
        else{
            arv[atual].Min=arv[atualdir].Min;
        }
        if(arv[atualdir].Max > arv[atualesq].Max){
            arv[atual].Max = arv[atualdir].Max;
		}
        else{
            arv[atual].Max = arv[atualesq].Max;
        }

        return;
}

int main(){
	int N,M,A,B;
	int i,j;
	int* vetor;
	arvore arv;
	elemento elm;
	char* operacao = (char*)malloc (3*sizeof(char));

	scanf("%d%d",&N,&M);
	vetor = (int*) malloc ((N+1)*sizeof(int));
	for(i=1;i<=N;i++){
		scanf("%d",&vetor[i]);
	}
	
	arv = (elemento*) malloc((N*N)*sizeof(elemento));

	for(i=0;i<M;i++){
		scanf("%s %d %d",operacao,&A,&B);
		if(strcmp("Add",operacao) == 0){
            tabela= ADD(arv,A,B,1);
		}
		else if(strcmp("Sub",operacao) == 0){
            tabela= SUB(arv,A,B,1);
		}
		
		else{
			elm = pesquisa(arv,A,B,1);

			if(strcmp("Min",operacao) == 0){
	            printf("%d\n",elm.Min);
			}
			else if(strcmp("Max",operacao) == 0){
	            printf("%d\n",elm.Max);
			}
			else if(strcmp("Sum",operacao) == 0){
	            printf("%d\n",elm.Sum);
			}
		}
	}

	free(vetor);
	free(arv);
	free(operacao);
	
	return 0;
}