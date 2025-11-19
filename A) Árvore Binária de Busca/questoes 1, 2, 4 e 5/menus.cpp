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
    cout<<"  [1] INSERIR DADO NA ARVORE                            "<<endl; // OBS da questao 1 - parte A
    cout<<"  [2] LISTAR ARVORE COMPLETA                            "<<endl; // OBS da questao 1 - parte A
    cout<<"  [3] EXCLUIR DADO DA ARVORE                            "<<endl; // OBS da questao 1 - parte A
    cout<<"  [4] IMPRIMIR MAIOR VALOR ARMAZENADO                   "<<endl; // questao 2 - parte A
    cout<<"  [5] CONSULTAR DADOS REPETIDOS                         "<<endl; // questao 4 - parte A
    cout<<"  [6] VERIFICAR SE A ARVORE ESTA CHEIA                  "<<endl; // questao 5 - parte A
    cout<<"  [7] SAIR                                              "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
    cin >> escolha;
    return escolha;
}

int menuPrincipal()
{
    int escolhaPrincipal;
    system("cls");
    cout<<"========================================================"<<endl;
    cout<< "                  MENU PRINCIPAL                       "<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  [1] QUESTOES 1, 2, 4 e 5                              "<<endl;
    cout<<"  [2] SAIR DO PROGRAMA                                  "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
    cin >> escolhaPrincipal;
    return escolhaPrincipal;
}