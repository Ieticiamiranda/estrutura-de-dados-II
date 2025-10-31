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

            int valores_iniciais[] = {20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40};
            for (int val : valores_iniciais)
            {
                arvore.inserir(val);
            }
            arvore.remover(9);
            arvore.remover(5);
            arvore.remover(20);

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
                    arvore.encontrarMaximo();
                    break;
                case 5:
                    arvore.mostrarRepetidos();
                    break;
                case 6:
                    arvore.verificarArvoreCheia();
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
            menuArvorePessoas();
            break;

        case 3:
            cout << "> Saindo do programa..." << endl;
            break;

        default:
            cout << "Opcao invalida. Tente novamente." << endl;
            system("pause");
        }

    } while (escolhaPrincipal != 3);

    return 0;
}