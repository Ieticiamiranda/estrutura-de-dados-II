#include "menus.h"
#include <iostream>
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
    cout << "> Digite origem, destino e peso: ";
    cin >> o >> d >> p;
    G->inserirArco(o, d, p);
    G->matrizAdj();
    G->numArestas();
    G->grauG();
    cout << "Aresta inserida!!" << endl;
    system("pause");
}

void removerAresta(Graph *G)
{
    int o, d;
    system("cls");
    cout << "> Digite origem e destino: ";
    cin >> o >> d;
    G->removerArco(o, d);
    G->matrizAdj();
    G->numArestas();
    G->grauG();
    cout << "Aresta removida!!" << endl;
    system("pause");
}

void executarFloyd()
{
    system("cls");
    Graph G;
    if (G.entGrafoArquivo("grafo.txt") > 0)
    {
        G.matrizAdj();
        G.numArestas();
        G.grauG();
        G.floydWarshall();
    }
    else
    {
        cout << "Erro ao carregar grafo.txt" << endl;
    }
    system("pause");
}