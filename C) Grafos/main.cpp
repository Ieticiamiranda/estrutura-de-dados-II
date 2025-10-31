#include "Grafo.h"
#include "menus.h"
#include <iostream>
using namespace std;

int main()
{
    bool continuar = true;
    Graph *G = nullptr;

    while (continuar)
    {
        int op_principal = menuPrincipal();

        switch (op_principal)
        {
        case 1:
        {
            delete G;
            G = new Graph();
            if (G->entGrafoArquivo("grafo.txt") > 0)
            {
                G->matrizAdj();
                G->numArestas();
                G->grauG();
                system("pause");

                bool sair_q1 = false;
                while (!sair_q1)
                {
                    int op_q1 = menuQuestao1();
                    switch (op_q1)
                    {
                    case 1:
                        inserirAresta(G);
                        break;
                    case 2:
                        removerAresta(G);
                        break;
                    case 3:
                        G->imprimirMatriz(2);
                        break;
                    case 4:
                        G->imprimirMatriz(1);
                        break;
                    case 5:
                        G->exibirGrauG();
                        break;
                    case 6:
                        G->listaGrafo();
                        break;
                    case 7:
                        sair_q1 = true;
                        break;
                    default:
                        cout << "Opcao invalida." << endl;
                        system("pause");
                        break;
                    }
                }
            }
            else
            {
                cout << "Falha ao carregar grafo.txt" << endl;
                delete G;
                G = nullptr;
                system("pause");
            }
            break;
        }
        case 2:
            executarFloyd();
            break;
        case 3:
            continuar = false;
            break;
        default:
            cout << "Opcao invalida." << endl;
            system("pause");
            break;
        }
    }

    delete G;
    return 0;
}