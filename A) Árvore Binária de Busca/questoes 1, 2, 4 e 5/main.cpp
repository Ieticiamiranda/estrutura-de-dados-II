#include "menus.h"
#include "arvores.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int escolhaPrincipal;

    do
    {
        escolhaPrincipal = menuPrincipal();

        switch (escolhaPrincipal)
        {
        case 1:
        {
            ArvoreBin arvore;

            int valores_iniciais[] = {20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40}; // a) - parte A
            for (int val : valores_iniciais)
            {
                arvore.inserir(val);
            }
            arvore.remover(9); // b) - parte A
            arvore.remover(5); // b) - parte A
            arvore.remover(20); // b) - parte A

            int escolha_arvore;
            int valor;

            do
            {
                escolha_arvore = menuArvoreInteiros();

                switch (escolha_arvore)
                {
                case 1:
                    cout << "Digite o dado a ser inserido na arvore: ";
                    cin >> valor;
                    arvore.inserir(valor);
                    break;
                case 2:
                    arvore.listar();
                    break;
                case 3:
                    cout << "Digite o dado a ser excluido da arvore: ";
                    cin >> valor;
                    arvore.remover(valor);
                    break;
                case 4:
                    arvore.encontrarMaximo(); // questao 2 - parte A
                    break;
                case 5:
                    arvore.mostrarRepetidos(); // questao 4 - parte A
                    break;
                case 6:
                    arvore.verificarArvoreCheia(); // questao 5 - parte A
                    break;
                case 7:
                    cout << "> Voltando ao Menu Principal..." << endl;
                    break;
                default:
                    cout << "Opcao invalida. Tente novamente." << endl;
                }

                if (escolha_arvore != 7)
                {
                    system("pause");
                }

            } while (escolha_arvore != 7);
        }
        break;

        case 2:
            cout << "> Saindo do programa..." << endl;
            break;

        default:
            cout << "Opcao invalida. Tente novamente." << endl;
            system("pause");
        }

    } while (escolhaPrincipal != 2);

    return 0;
}