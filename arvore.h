#ifndef ARVORE_H
#define ARVORE_H

typedef struct element{
	int Min,Max,Sum; //Guarda os valores de Mínimo, Máximo e Soma de um intervalo, respectivamente.
	int esq,dir; //Guarda qual intervalo abrange o nódulo, que será [esq,dir].
}elemento;

typedef elemento* arvore; // Uma árvore é um ponteiro para uma struct

arvore constroi(int* vetor, int atual, int esq, int dir,arvore arv); //Função para construir a árvore
elemento pesquisa (arvore arv, int A, int B, int atual); // Função para pesquisar um intervalo [A,B] na árvore
void ADD (arvore arv, int A, int B, int atual); //Função para atualizar em +1 um intervalo [A,B] na árvore
void SUB (arvore arv, int A, int B, int atual); //Função para atualizar em -1 um intervalo [A,B] na árvore

#endif