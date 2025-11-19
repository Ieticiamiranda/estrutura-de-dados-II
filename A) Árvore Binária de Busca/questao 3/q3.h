#ifndef CASE3_H
#define CASE3_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

// --------------------------------------------------
// Estrutura do Nó da Árvore
// --------------------------------------------------
struct No {
    string nome;
    char sexo;
    int idade;
    float peso;

    No* esq;
    No* dir;

    No(string n, char s, int i, float p)
        : nome(n), sexo(s), idade(i), peso(p), esq(nullptr), dir(nullptr) {}
};

// --------------------------------------------------
// Classe da Árvore Binária de Busca (BST)
// --------------------------------------------------
class Arvore {

private:
    No* raiz;

    // ---- Inserção na BST ----
    void inserirAux(No*& atual, string nome, char sexo, int idade, float peso) {
        if (atual == nullptr) {
            atual = new No(nome, sexo, idade, peso);
            return;
        }

        if (nome < atual->nome)
            inserirAux(atual->esq, nome, sexo, idade, peso);
        else
            inserirAux(atual->dir, nome, sexo, idade, peso);
    }

    // ---- Listagem (in-order) ----
    void listarAux(No* atual) {
        if (atual == nullptr) return;

        listarAux(atual->esq);

        cout << "Nome: " << atual->nome
             << " | Sexo: " << atual->sexo
             << " | Idade: " << atual->idade
             << " | Peso: " << atual->peso << endl;

        listarAux(atual->dir);
    }

    // ---- Geração das listas ----
    void gerarListasAux(No* atual, list<No*>& homens, list<No*>& mulheres) {
        if (atual == nullptr) return;

        // Percurso IN-ORDER = ordenado por nome
        gerarListasAux(atual->esq, homens, mulheres);

        if (atual->sexo == 'M' || atual->sexo == 'm')
            homens.push_back(atual);
        else if (atual->sexo == 'F' || atual->sexo == 'f')
            mulheres.push_back(atual);

        gerarListasAux(atual->dir, homens, mulheres);
    }

public:

    Arvore() {
        raiz = nullptr;
    }

    // Inserção pública
    void inserir(string nome, char sexo, int idade, float peso) {
        inserirAux(raiz, nome, sexo, idade, peso);
    }

    // Listagem pública
    void listar() {
        if (raiz == nullptr) {
            cout << "> A arvore esta vazia.\n";
            return;
        }
        listarAux(raiz);
    }

    // Geração das listas ordenadas
    void gerarListas(list<No*>& homens, list<No*>& mulheres) {
        homens.clear();
        mulheres.clear();
        gerarListasAux(raiz, homens, mulheres);
    }
};

#endif
