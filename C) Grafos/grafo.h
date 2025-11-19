#ifndef GRAFO_H
#define GRAFO_H

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
    int entGrafoArquivo(const char *nome_arquivo);
    void atualizaPropriedades();
    int** calcularFloydWarshall();

    int getV();
    int getA();
    int getDist(int i, int j);
    int getAdj(int i, int j);
    int getGrau(int i);
};

#endif