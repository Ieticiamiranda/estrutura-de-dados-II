#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include <string>
#include <list>
#include <iostream>
#include <algorithm> 

using namespace std;

struct No {
    string nome;
    char sexo;
    int idade;
    float peso;
    int altura;

    No* esq;
    No* dir;

    No(string n, char s, int i, float p);
};

class Arvore {

private:
    No* raiz;

    int getAltura(No* n);
    int getBalanceamento(No* n);
    No* rotacaoDireita(No* y);
    No* rotacaoEsquerda(No* x);
    No* menorNo(No* node);
    
    No* inserirAux(No* no, string nome, char sexo, int idade, float peso);
    No* removerAux(No* raiz, string nome);
    No* consultarAux(No* raiz, string nome);
    void listarAux(No* atual);
    void gerarListasAux(No* atual, list<No*>& homens, list<No*>& mulheres);

public:
    Arvore();

    void inserir(string nome, char sexo, int idade, float peso);
    void remover(string nome);
    void consultar(string nome);
    void listar();
    void gerarListas(list<No*>& homens, list<No*>& mulheres);
};

#endif