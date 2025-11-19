#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <windows.h>
#include <list>
#include <string>
#include "arvoreAVL.h"

using namespace std;

void exibirLista(list<No*>& lista, string titulo) {
    cout << endl << "> " << titulo << ":" << endl;
    if (lista.empty()) {
        cout << "Nenhum registro encontrado." << endl;
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

void exibirMenuPrincipal() {
    cout<<"========================================================"<<endl;
    cout<<"            ESCOLHA UMA OPCAO NO MENU ABAIXO            "<<endl;
    cout<<"========================================================"<<endl;
    cout<<"  [1] INSERIR PESSOA NA ARVORE                          "<<endl;
    cout<<"  [2] LISTAR ARVORE COMPLETA                            "<<endl;
    cout<<"  [3] IMPRIMIR LISTAS ORDENADAS POR NOME                "<<endl;
    cout<<"  [4] REMOVER PESSOA DA ARVORE                          "<<endl;
    cout<<"  [5] CONSULTAR PESSOA POR NOME                         "<<endl;
    cout<<"  [6] SAIR DO PROGRAMA                                  "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"  OPCAO ESCOLHIDA: ";
}

void executarCase2(Arvore& arvore) {
    system("cls");
    cout << "--------------------------------------------" << endl;
    cout << "              ARVORE COMPLETA               " << endl;
    cout << "--------------------------------------------" << endl;
    arvore.listar();
    cout << endl;
    system("pause");
    system("cls");
}

void executarCase3(Arvore& arvore, list<No*>& homens, list<No*>& mulheres) {
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
}

#endif