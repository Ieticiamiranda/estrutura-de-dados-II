#include "menus.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int menuPrincipal()
{
    system("cls");
    cout<<"========================================================"<<endl;
    cout<< "                  MENU PRINCIPAL                       "<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  [1] QUESTAO 1                                         "<<endl;
    cout<<"  [2] QUESTAO 2                                         "<<endl;
    cout<<"  [3] SAIR DO PROGRAMA                                  "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
    int op;
    cin >> op;
    return op;
}

int menuQuestao1()
{
    system("cls");
    cout<<"========================================================"<<endl;
    cout<<"            ESCOLHA UMA OPCAO NO MENU ABAIXO            "<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  [1] INSERIR ARESTA                                    "<<endl;
    cout<<"  [2] EXCLUIR ARESTA                                    "<<endl;
    cout<<"  [3] IMPRIMIR MATRIZ DE ADJACENCIA                     "<<endl;
    cout<<"  [4] IMPRIMIR MATRIZ DE DISTANCIAS                     "<<endl;
    cout<<"  [5] IMPRIMIR GRAU DOS VERTICES                        "<<endl;
    cout<<"  [6] LISTAR GRAFO COMPLETO                             "<<endl;
    cout<<"  [7] SAIR                                              "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
    int op;
    cin >> op;
    return op;
}

void inserirAresta(Graph *G)
{
    int o, d, p;
    system("cls");
    cout << "Digite origem, destino e peso: ";
    cin >> o >> d >> p;
    G->inserirArco(o, d, p);
    G->atualizaPropriedades();
    cout << "> Aresta inserida!!" << endl;
    system("pause");
}

void removerAresta(Graph *G)
{
    int o, d;
    system("cls");
    cout << "Digite origem e destino: ";
    cin >> o >> d;
    G->removerArco(o, d);
    G->atualizaPropriedades();
    cout << "> Aresta removida!!" << endl;
    system("pause");
}

void imprimirMatrizUI(Graph *G, int tipo)
{
    int V = G->getV();
    if (V == 0) return;

    const int larguraColuna = 6;
    system("cls");
    cout << (tipo == 1 ? "===== MATRIZ DE DISTANCIAS =====" : "===== MATRIZ DE ADJACENCIA =====") << endl << endl;
    
    cout << right << setw(larguraColuna) << " "; 
    for (int j = 0; j < V; ++j) cout << setw(larguraColuna) << j;
    cout << endl << setw(larguraColuna) << " ";
    for (int j = 0; j < V; ++j) cout << setw(larguraColuna) << "------";
    cout << endl;

    for (int i = 0; i < V; i++)
    {
        cout << setw(larguraColuna - 2) << i << " |"; 
        for (int j = 0; j < V; j++)
        {
            cout << setw(larguraColuna);
            int val = (tipo == 1) ? G->getDist(i, j) : G->getAdj(i, j);
            if (val == INF) cout << "inf";
            else cout << val;
        }
        cout << endl; 
    }
    cout << endl;
    system("pause");
}

void exibirGrauGUI(Graph *G)
{
    system("cls");
    int V = G->getV();
    if (V == 0) return;

    cout << "Grau dos vertices:" << endl;
    for (int i = 0; i < V; i++)
        cout << "vertice " << i << " -> " << G->getGrau(i) << endl;
    system("pause");
}

void listaGrafoUI(Graph *G)
{
    system("cls");
    int V = G->getV();
    
    cout << endl << "Grafo G(V,A)" << endl;
    cout << "> Numero de Vertices: " << V << endl;
    cout << "> Numero de Arestas: " << G->getA() << endl;

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
            if (G->getAdj(v, w) == 1)
            {
                if (!primeiro) cout << ", ";
                cout << w;
                primeiro = false;
            }
        }
        if (primeiro) cout << "(Nenhum)";
        cout << endl;
    }
    cout << "  +----------+-------------------------------+" << endl;
    system("pause");
}

void executarFloyd()
{
    system("cls");
    Graph G_temp;
    
    if (G_temp.entGrafoArquivo("grafo.txt") > 0)
    {
        int** matrizFloyd = G_temp.calcularFloydWarshall();
        int V = G_temp.getV();

        cout << "Matriz de caminhos minimos (floyd-warshall):" << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (matrizFloyd[i][j] == INF) cout << "inf ";
                else cout << matrizFloyd[i][j] << " ";
            }
            cout << endl;
        }
        
        for(int i=0; i < V; i++) delete[] matrizFloyd[i];
        delete[] matrizFloyd;
    }
    else
    {
        cout << "Erro ao carregar grafo.txt" << endl;
    }
    system("pause");
}