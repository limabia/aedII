/*
enquanto a pilha não está vazia faça
	seja  v  o vértice no topo da pilha
	se A(v) não está vazio
		então retire um arco (v,w) de A(v)
			se w não está marcado
				então marque w
  					coloque w no topo da pilha
	senão retire v do topo da pilha
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define true 1
#define false 0 

typedef int bool;
typedef int TIPOPESO;

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

typedef struct adjacencia {
	int vertice;
	TIPOPESO peso;
	struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice{
	ADJACENCIA *cabeca;
} VERTICE;

typedef struct grafo{
	int vertices;
	int arestas;
	VERTICE *adj; // ponteiro para a lista de vertices 
} GRAFO;

void visitaP (GRAFO *g, int u, int *cor){
	cor[u] = AMARELO;

	// pego as adjacencias do meu vertice
	ADJACENCIA *v = g->adj[u].cabeca;
	// verifico se ainda posso descer mais ou
	// se é hr de voltar visitando
	while(v){
		if (cor[v->vertice] == BRANCO){
			printf("%d -> %d\n", u, v->vertice);
			visitaP(g, v->vertice, cor);
		}
		v = v->prox;
	}
	// visito efetivamente
	cor[u] = VERMELHO;
}

void profundidade (GRAFO *g){
	// para cada vertice uma posição guardando a cor
	int cor[g->vertices];
	// pinta todos os vertices de branco
	for(int u = 0; u < g->vertices; u++){
		cor[u] = BRANCO;
	}
	// vai percorrer todos os vertices 
	//inclusive se o grafo for desconexo
	for(int u = 0; u < g->vertices; u++) {
		if (cor[u] == BRANCO){
			printf("Raiz da busca: %d\n", u);
			visitaP(g, u, cor);
		}
	}
}

GRAFO * inicializaGrafo(int nVertices){
	if(nVertices < 0){
		return NULL;
	}
	GRAFO* novoGrafo = (GRAFO*)malloc(sizeof(novoGrafo));

	novoGrafo->vertices = nVertices;
	novoGrafo->arestas = 0;

	novoGrafo->adj = (VERTICE*)malloc(nVertices * sizeof(VERTICE));

	for(int i = 0; i < nVertices; i++){
		novoGrafo->adj->cabeca = NULL;
	}

	return novoGrafo;
}

bool verticeValido(GRAFO *grafo, int vertice) {
 	// verifica se o vertice é positivo e se ele está no intervalo de numeros de vertices possiveis no grafo
	if (vertice >= 0 && vertice < grafo->vertices)
		return true;
	return false;
}

bool verticeJaExiste(GRAFO *grafo, int vertice1, int vertice2) {
	ADJACENCIA *v = grafo->adj[vertice1].cabeca;
	while(v) {
		if (v->vertice == vertice2) {
			return true;
		}
		v = v->prox;
	}
	return false;
}

bool criaAresta(GRAFO *grafo, int vertice, int vizinho, TIPOPESO pesoAresta) {
	if (!verticeValido(grafo, vertice) || !verticeValido(grafo, vizinho) || verticeJaExiste(grafo, vertice, vizinho)) {
		return false;
	}

	// criar aresta para os vertices
	ADJACENCIA *aresta = (ADJACENCIA*) malloc(sizeof(ADJACENCIA));
	aresta->vertice = vizinho;
	aresta->peso = pesoAresta;

	// coloca a aresta como a primeira na lista de adjacencia
	aresta->prox = grafo->adj[vertice].cabeca;
	grafo->adj[vertice].cabeca = aresta;

	return true;
}


int main(){
	GRAFO *grafo = inicializaGrafo(6);

	// cria todas as arestas do grafo
	criaAresta(grafo, 0, 1, 1);
	criaAresta(grafo, 1, 0, 1);
	grafo->arestas++;

	criaAresta(grafo, 1, 2, 1);
	criaAresta(grafo, 2, 1, 1);
	grafo->arestas++;

	criaAresta(grafo, 2, 4, 1);
	criaAresta(grafo, 4, 2, 1);
	grafo->arestas++;

	criaAresta(grafo, 2, 5, 1);
	criaAresta(grafo, 5, 2, 1);
	grafo->arestas++;

	// busca em profundidade
	profundidade(grafo);

	// TODO dar um free em toda memória alocada
	return 0;
}
