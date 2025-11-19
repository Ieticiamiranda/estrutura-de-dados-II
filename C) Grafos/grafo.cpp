#include "Grafo.h"
#include <iostream>
#include <cstdio>

using namespace std;

int **Graph::Aloca_MatrizInt(int l, int c)
{
    int **m = new int *[l];
    for (int i = 0; i < l; i++)
        m[i] = new int[c];
    return m;
}

Graph::Graph() : V(0), A(0), adj(nullptr), dist(nullptr), grau(nullptr)
{
}

Graph::~Graph()
{
    LimpaGrafo();
}

void Graph::LimpaGrafo()
{
    if (adj != nullptr)
    {
        for (int i = 0; i < V; ++i) delete[] adj[i];
        delete[] adj;
        adj = nullptr;
    }
    if (dist != nullptr)
    {
        for (int i = 0; i < V; ++i) delete[] dist[i];
        delete[] dist;
        dist = nullptr;
    }
    if (grau != nullptr)
    {
        delete[] grau;
        grau = nullptr;
    }
    V = 0; A = 0;
}

void Graph::inicializarGrafo(int num_vertices)
{
    LimpaGrafo();
    V = num_vertices;
    adj = Aloca_MatrizInt(V, V);
    dist = Aloca_MatrizInt(V, V);

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
        {
            adj[i][j] = 0;
            dist[i][j] = (i == j) ? 0 : INF;
        }

    grau = new int[V];
    for (int i = 0; i < V; ++i) grau[i] = 0;
    A = 0;
}

void Graph::inserirArco(int v, int w, int peso)
{
    if (v < 0 || v >= V || w < 0 || w >= V) return;
    
    dist[v][w] = peso;
    dist[w][v] = peso; 
}

void Graph::removerArco(int v, int w)
{
    if (v < 0 || v >= V || w < 0 || w >= V) return;
    dist[v][w] = INF;
    dist[w][v] = INF;
}

void Graph::atualizaPropriedades()
{
    if (V == 0) return;
    
    A = 0;
    for (int i = 0; i < V; i++) {
        grau[i] = 0;
        for (int j = 0; j < V; j++) {
            if (dist[i][j] != 0 && dist[i][j] != INF) {
                adj[i][j] = 1;
                grau[i]++;
                if (i < j) A++;
            } else {
                adj[i][j] = 0;
            }
        }
    }
}

int Graph::entGrafoArquivo(const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) return 0;

    int num_vertices, num_arestas;
    fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);
    inicializarGrafo(num_vertices);

    int o, d, p;
    while (fscanf(arquivo, "%d %d %d", &o, &d, &p) == 3)
    {
        inserirArco(o, d, p);
    }
    fclose(arquivo);
    
    atualizaPropriedades();
    return V;
}

int** Graph::calcularFloydWarshall()
{
    if (V == 0) return nullptr;

    int **menor = Aloca_MatrizInt(V, V);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            menor[i][j] = dist[i][j];

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (menor[i][k] + menor[k][j] < menor[i][j])
                    menor[i][j] = menor[i][k] + menor[k][j];

    return menor;
}

int Graph::getV() { return V; }
int Graph::getA() { return A; }
int Graph::getDist(int i, int j) { return dist[i][j]; }
int Graph::getAdj(int i, int j) { return adj[i][j]; }
int Graph::getGrau(int i) { return grau[i]; }