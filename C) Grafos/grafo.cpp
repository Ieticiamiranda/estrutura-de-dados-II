#include "Grafo.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <iomanip>
#include <sstream>

#define inf 9999999
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
    cout << "> Grafo G(V,A) instanciado!" << endl;
}

Graph::~Graph()
{
    LimpaGrafo();
    cout << "> Grafo G(V,A) desalocado da memoria!" << endl;
}

void Graph::LimpaGrafo()
{
    if (adj != nullptr)
    {
        for (int i = 0; i < V; ++i)
            delete[] adj[i];
        delete[] adj;
        adj = nullptr;
    }

    if (dist != nullptr)
    {
        for (int i = 0; i < V; ++i)
            delete[] dist[i];
        delete[] dist;
        dist = nullptr;
    }

    if (grau != nullptr)
    {
        delete[] grau;
        grau = nullptr;
    }

    V = 0;
    A = 0;
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
            dist[i][j] = (i == j) ? 0 : inf;
        }

    grau = new int[V];
    for (int i = 0; i < V; ++i)
        grau[i] = 0;

    A = 0;
}

void Graph::inserirArco(int vertex_v, int vertex_w, int peso)
{
    if (vertex_v < 0 || vertex_v >= V || vertex_w < 0 || vertex_w >= V)
        return;

    if (adj[vertex_v][vertex_w] == 0)
        A++;

    adj[vertex_v][vertex_w] = 1;
    adj[vertex_w][vertex_v] = 1;
    dist[vertex_v][vertex_w] = peso;
    dist[vertex_w][vertex_v] = peso;
}

void Graph::removerArco(int vertex_v, int vertex_w)
{
    if (vertex_v < 0 || vertex_v >= V || vertex_w < 0 || vertex_w >= V)
    return;
    
    if (adj[vertex_v][vertex_w] == 1)
    A--;
    
    adj[vertex_v][vertex_w] = 0;
    adj[vertex_w][vertex_v] = 0;
    dist[vertex_v][vertex_w] = inf;
    dist[vertex_w][vertex_v] = inf;
}

void Graph::listaGrafo()
{
    system("cls");
    cout << endl << "Grafo G(V,A)" << endl;
    cout << "> Numero de Vertices: " << V << endl;
    cout << "> Numero de Arestas: " << A << endl;

    cout << setfill(' ');
    cout << "\n  +----------+-------------------------------+" << endl;
    cout << "  | " << setw(8) << right << "VERTICE" << " | " << left << "ARESTAS" << endl;
    cout << "  +----------+-------------------------------+" << endl;
    cout << left;

    for (int v = 0; v < V; ++v)
    {
        cout << "  | " << "   " << setw(5) << left << v << " | ";

        bool primeiro = true;
        for (int w = 0; w < V; ++w)
        {
            if (adj[v][w] == 1)
            {
                if (!primeiro)
                {
                    cout << ", ";
                }
                cout << w;
                primeiro = false;
            }
        }

        if (primeiro)
        {
            cout << "(Nenhum)";
        }

        cout << endl;
    }
    cout << "  +----------+-------------------------------+" << endl;


    system("pause");
}

void Graph::matrizAdj()
{
    if (V == 0)
        return;

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = (dist[i][j] != 0 && dist[i][j] != inf) ? 1 : 0;
}

void Graph::numArestas()
{
    int Na = 0;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if ((i < j) && (adj[i][j] == 1))
                Na++;
    A = Na;
}

void Graph::grauG()
{
    if (V == 0)
        return;

    for (int i = 0; i < V; i++)
    {
        grau[i] = 0;
        for (int j = 0; j < V; j++)
            if (adj[i][j] == 1)
                grau[i]++;
    }
}

void Graph::exibirGrauG()
{
    system("cls");
    if (V == 0)
        return;

    cout << "Grau dos vertices:" << endl;
    for (int i = 0; i < V; i++)
        cout << "vertice " << i << " -> " << grau[i] << endl;

    system("pause");
}

void Graph::imprimirMatriz(int tipo)
{
    if (V == 0)
        return;

    const int larguraColuna = 6;
    if (tipo == 1)
    {
        system("cls");
        cout << "===== MATRIZ DE DISTANCIAS =====" << endl << endl;
        cout << right; 
        cout << setw(larguraColuna) << " "; 
        for (int j = 0; j < V; ++j) {
            cout << setw(larguraColuna) << j;
        }
        cout << endl;
        cout << setw(larguraColuna) << " ";
        for (int j = 0; j < V; ++j) {
            cout << setw(larguraColuna) << "------";
        }
        cout << endl;
        for (int i = 0; i < V; i++)
        {
            cout << setw(larguraColuna - 2) << i << " |"; 
            
            for (int j = 0; j < V; j++)
            {
                cout << setw(larguraColuna);
                if (dist[i][j] == inf)
                    cout << "inf";
                else
                    cout << dist[i][j];
            }
            cout << endl; 
        }
        cout << endl;
    }
    else
    {
        system("cls");
        cout << "===== MATRIZ DE ADJACENCIA =====" << endl << endl;
        cout << right;
        cout << setw(larguraColuna) << " "; 
        for (int j = 0; j < V; ++j) {
            cout << setw(larguraColuna) << j;
        }
        cout << endl;
        cout << "      "; 
        for (int j = 0; j < V; ++j) {
            cout << setw(larguraColuna) << "------";
        }
        cout << endl;
        for (int i = 0; i < V; i++)
        {
            cout << setw(larguraColuna - 2) << i << " |";

            for (int j = 0; j < V; j++)
            {
                cout << setw(larguraColuna) << adj[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    system("pause");
}
int Graph::entGrafoArquivo(const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo)
    {
        cout << "Erro ao abrir o arquivo." << endl;
        return 0;
    }

    int num_vertices, num_arestas;

    fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);
    inicializarGrafo(num_vertices);

    int origem, destino, peso;

    while (fscanf(arquivo, "%d %d %d", &origem, &destino, &peso) == 3)
    {
        inserirArco(origem, destino, peso);
    }

    fclose(arquivo);

    matrizAdj();
    numArestas();
    grauG();

    return V;
}

void Graph::floydWarshall()
{
    if (V == 0)
    {
        cout << "Grafo vazio!!" << endl;
        return;
    }

    int **menor = Aloca_MatrizInt(V, V);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            menor[i][j] = dist[i][j];

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (menor[i][k] + menor[k][j] < menor[i][j])
                    menor[i][j] = menor[i][k] + menor[k][j];

    cout << "Matriz de caminhos minimos (floyd-warshall):" << endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (menor[i][j] == inf)
                cout << "inf ";
            else
                cout << menor[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < V; i++)
        delete[] menor[i];
    delete[] menor;

    system("pause");
}