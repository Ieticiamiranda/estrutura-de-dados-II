#include <iostream>
#include <windows.h>
#include <string>
#include <list>
#include "arvoreAVL.h"
#include "menus.h"

using namespace std;

int main() {
    system("cls");
    Arvore arvore;
    list<No*> homens;
    list<No*> mulheres;

    int opcao;
    string nome;
    char sexo;
    int idade;
    float peso;

    do {
        exibirMenuPrincipal();
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Digite o nome: ";
                cin.ignore();
                getline(cin, nome);

                cout << "Digite o sexo (M/F): ";
                cin >> sexo;

                cout << "Digite a idade: ";
                cin >> idade;

                cout << "Digite o peso: ";
                cin >> peso;

                arvore.inserir(nome, sexo, idade, peso);

                cout << endl << "> Pessoa inserida com sucesso!" << endl;
                system("pause");
                system("cls");
                break;

            case 2:
                executarCase2(arvore);
                break;

            case 3:
                executarCase3(arvore, homens, mulheres);
                break;

            case 4:
                cout << "Digite o nome para remover: ";
                cin.ignore();
                getline(cin, nome);
                arvore.remover(nome);
                system("pause");
                system("cls");
                break;

            case 5:
                cout << "Digite o nome para consultar: ";
                cin.ignore();
                getline(cin, nome);
                arvore.consultar(nome);
                system("pause");
                system("cls");
                break;

            default:
                if (opcao != 6)
                    cout << "Opcao invalida. Tente novamente." << endl;
                system("pause");
                system("cls");
        }

    } while (opcao != 6);

    cout << "> Encerrando o programa..." << endl;
    return 0;
}