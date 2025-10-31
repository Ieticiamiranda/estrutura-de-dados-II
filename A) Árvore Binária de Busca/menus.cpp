#include "menus.h"
#include "arvores.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int menuArvoreInteiros()
{
    int escolha;
    system("cls");
    cout<<"========================================================"<<endl;
    cout<< "            ESCOLHA UMA OPCAO NO MENU ABAIXO           "<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  [1] INSERIR DADO NA ARVORE                            "<<endl;
    cout<<"  [2] LISTAR ARVORE COMPLETA                            "<<endl;
    cout<<"  [3] EXCLUIR DADO DA ARVORE                            "<<endl;
    cout<<"  [4] IMPRIMIR MAIOR VALOR ARMAZENADO                   "<<endl;
    cout<<"  [5] CONSULTAR DADOS REPETIDOS                         "<<endl;
    cout<<"  [6] VERIFICAR SE A ARVORE ESTA CHEIA                  "<<endl;
    cout<<"  [7] SAIR                                              "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
    cin >> escolha;
    return escolha;
}

void menuArvorePessoas()
{
    system("cls");
    cout << "===== QUESTAO 3 (ARVORE DE PESSOAS) =====" << endl
         << endl;

    NoArvore *RAIZ = NULL;

    RAIZ = inserirPessoa(RAIZ, {"Carlos", 'M', 30, 80.5});
    RAIZ = inserirPessoa(RAIZ, {"Ana", 'F', 25, 60.2});
    RAIZ = inserirPessoa(RAIZ, {"Zelia", 'F', 45, 68.0});
    RAIZ = inserirPessoa(RAIZ, {"Bruno", 'M', 22, 75.0});
    RAIZ = inserirPessoa(RAIZ, {"Maria", 'F', 50, 65.7});
    RAIZ = inserirPessoa(RAIZ, {"Heitor", 'M', 19, 70.1});
    RAIZ = inserirPessoa(RAIZ, {"Debora", 'F', 33, 58.9});

    vector<Pessoa> listaHomens;
    vector<Pessoa> listaMulheres;

    gerarListasOrdenadas(RAIZ, listaHomens, listaMulheres);

    imprimirLista("Lista de Homens (Ordenada por Nome)", listaHomens);
    imprimirLista("Lista de Mulheres (Ordenada por Nome)", listaMulheres);

    limparArvore(RAIZ);

    system("pause");
}

int menuPrincipal()
{
    int escolhaPrincipal;
    system("cls");
    cout<<"========================================================"<<endl;
    cout<< "                  MENU PRINCIPAL                       "<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  [1] QUESTOES 1, 2, 4 e 5                              "<<endl;
    cout<<"  [2] QUESTAO 3                                         "<<endl;
    cout<<"  [3] SAIR DO PROGRAMA                                  "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
    cin >> escolhaPrincipal;
    return escolhaPrincipal;
}