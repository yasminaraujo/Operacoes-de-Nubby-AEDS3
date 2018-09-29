#ifndef MATRIZ_H
#define MATRIZ_H
//struct que guarda os valores de máximo, mínimo e soma dos intervalos do vetor
typedef struct element{
    int Min,Max,Sum;
}elemento; 

//matriz é um tipo de vetor de vetores de struct
typedef elemento** matriz;

matriz montamatriz(int* vetor,int N,matriz m); //Função que monta uma matriz já alocada
matriz ADD(matriz m, int* vetor, int A, int B, int N);//Função que adiciona +1 no intervalo [A,B] e retorna uma matriz feita a partir do novo vetor
matriz SUB(matriz m, int* vetor, int A, int B, int N);//Função que subtrai -1 no intervalo [A,B] e retorna uma matriz feita a partir do novo vetor

#endif