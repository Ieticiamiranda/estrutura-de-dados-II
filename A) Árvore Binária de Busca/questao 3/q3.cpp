#include "q3.h"
#include <windows.h>
#include <list>
#include <string>
#include <iostream>

using namespace std;

// Função auxiliar para exibir as listas
void exibirLista(list<No*>& lista, string titulo) {
    cout << "\n> " << titulo << ":\n";
    if (lista.empty()) {
        cout << "Nenhum registro encontrado.\n";
        return;
    }

    for (list<No*>::iterator it = lista.begin(); it != lista.end(); ++it) {
        No* pessoa = *it;
        cout << "Nome: " << pessoa->nome
             << " | Sexo: " << pessoa->sexo
             << " | Idade: " << pessoa->idade
             << " | Peso: " << pessoa->peso << endl;
    }
}

int main() {
    Arvore arvore;
    list<No*> homens;
    list<No*> mulheres;

    int opcao;
    string nome;
    char sexo;
    int idade;
    float peso;

    do {
    cout<<"========================================================"<<endl;
    cout<<"            ESCOLHA UMA OPCAO NO MENU ABAIXO            "<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  [1] INSERIR PESSOA NA ARVORE                          "<<endl;
    cout<<"  [2] LISTAR ARVORE COMPLETA                            "<<endl;
    cout<<"  [3] IMPRIMIR LISTAS ORDENADAS POR NOME                "<<endl;
    cout<<"  [4] VOLTAR AO MENU PRINCIPAL                          "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
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

                cout << "\n> Pessoa inserida com sucesso!\n";
                system("pause");
                system("cls");
                break;

            case 2:
                system("cls");
                cout << "--------------------------------------------" << endl;
                cout << "              ARVORE COMPLETA               " << endl;
                cout << "--------------------------------------------" << endl;
                arvore.listar();
                cout << endl;
                system("pause");
                system("cls");
                break;

            case 3:
                system("cls");
                cout << "--------------------------------------------" << endl;
                cout << "           LISTAS ORDENADAS POR NOME        " << endl;
                cout << "--------------------------------------------" << endl;
                arvore.gerarListas(homens, mulheres);
                exibirLista(homens, "HOMENS");
                exibirLista(mulheres, "MULHERES");
                cout << endl;
                system("pause");
                system("cls");
                break;

            default:
                if (opcao != 0)
                    cout << "Opcao invalida. Tente novamente.\n";
                system("pause");
                cin >> opcao;
                system("cls");
        }

    } while (opcao != 4);

    cout << "> Encerrando o programa...\n";
    return 0;
}
