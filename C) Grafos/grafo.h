#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#define INF 9999999

class Graph
{
private:
    int V;
    int A;
    int **adj;
    int **dist;
    int *grau;

    int **Aloca_MatrizInt(int l, int c);
    void LimpaGrafo();

public:
    Graph();
    ~Graph();

    void inicializarGrafo(int num_vertices);
    void inserirArco(int v, int w, int peso);
    void removerArco(int v, int w);
    void listaGrafo();
    void matrizAdj();
    void numArestas();
    void grauG();
    void exibirGrauG();
    void imprimirMatriz(int tipo);
    int entGrafoArquivo(const char *nome_arquivo);
    void floydWarshall();
};

#endif