#include "arvoreAVL.h"

// --------------------------------------------------
// Implementação do Construtor do Nó
// --------------------------------------------------
No::No(string n, char s, int i, float p)
    : nome(n), sexo(s), idade(i), peso(p), altura(1), esq(nullptr), dir(nullptr) {}

// --------------------------------------------------
// Implementação da Classe Arvore
// --------------------------------------------------

Arvore::Arvore() {
    raiz = nullptr;
}

// ---- Utilitários AVL ----

int Arvore::getAltura(No* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

int Arvore::getBalanceamento(No* n) {
    if (n == nullptr) return 0;
    return getAltura(n->esq) - getAltura(n->dir);
}

// ---- Rotações ----

No* Arvore::rotacaoDireita(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(getAltura(y->esq), getAltura(y->dir)) + 1;
    x->altura = max(getAltura(x->esq), getAltura(x->dir)) + 1;

    return x;
}

No* Arvore::rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(getAltura(x->esq), getAltura(x->dir)) + 1;
    y->altura = max(getAltura(y->esq), getAltura(y->dir)) + 1;

    return y;
}

No* Arvore::menorNo(No* node) {
    No* atual = node;
    while (atual->esq != nullptr)
        atual = atual->esq;
    return atual;
}

// ---- Lógica de Inserção ----

No* Arvore::inserirAux(No* no, string nome, char sexo, int idade, float peso) {
    if (no == nullptr)
        return new No(nome, sexo, idade, peso);

    if (nome < no->nome)
        no->esq = inserirAux(no->esq, nome, sexo, idade, peso);
    else if (nome > no->nome)
        no->dir = inserirAux(no->dir, nome, sexo, idade, peso);
    else
        return no; // Não permite duplicatas

    no->altura = 1 + max(getAltura(no->esq), getAltura(no->dir));

    int balance = getBalanceamento(no);

    // Casos de Rotação
    if (balance > 1 && nome < no->esq->nome)
        return rotacaoDireita(no);

    if (balance < -1 && nome > no->dir->nome)
        return rotacaoEsquerda(no);

    if (balance > 1 && nome > no->esq->nome) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    if (balance < -1 && nome < no->dir->nome) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

void Arvore::inserir(string nome, char sexo, int idade, float peso) {
    raiz = inserirAux(raiz, nome, sexo, idade, peso);
}

// ---- Lógica de Remoção ----

No* Arvore::removerAux(No* raiz, string nome) {
    if (raiz == nullptr) return raiz;

    if (nome < raiz->nome)
        raiz->esq = removerAux(raiz->esq, nome);
    else if (nome > raiz->nome)
        raiz->dir = removerAux(raiz->dir, nome);
    else {
        // Nó encontrado
        if ((raiz->esq == nullptr) || (raiz->dir == nullptr)) {
            No* temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            } else {
                *raiz = *temp;
            }
            delete temp;
        } else {
            No* temp = menorNo(raiz->dir);
            raiz->nome = temp->nome;
            raiz->sexo = temp->sexo;
            raiz->idade = temp->idade;
            raiz->peso = temp->peso;
            raiz->dir = removerAux(raiz->dir, temp->nome);
        }
    }

    if (raiz == nullptr) return raiz;

    raiz->altura = 1 + max(getAltura(raiz->esq), getAltura(raiz->dir));
    int balance = getBalanceamento(raiz);

    if (balance > 1 && getBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    if (balance > 1 && getBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && getBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    if (balance < -1 && getBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void Arvore::remover(string nome) {
    if (consultarAux(raiz, nome) == nullptr) {
        cout << "> Erro: Pessoa nao encontrada na arvore." << endl;
        return;
    }
    raiz = removerAux(raiz, nome);
    cout << "> Pessoa removida com sucesso!" << endl;
}

// ---- Lógica de Consulta ----

No* Arvore::consultarAux(No* raiz, string nome) {
    if (raiz == nullptr || raiz->nome == nome)
        return raiz;

    if (nome < raiz->nome)
        return consultarAux(raiz->esq, nome);

    return consultarAux(raiz->dir, nome);
}

void Arvore::consultar(string nome) {
    No* res = consultarAux(raiz, nome);
    if (res != nullptr) {
        cout << endl;
        cout << "--------------------------------------------" << endl;
        cout << "              REGISTRO ENCONTRADO           " << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Nome: " << res->nome << endl;
        cout << "Sexo: " << res->sexo << endl;
        cout << "Idade: " << res->idade << endl;
        cout << "Peso: " << res->peso << endl;
    } else {
        cout << "> Registro nao encontrado para: " << nome << endl;
    }
}

// ---- Lógica de Listagem ----

void Arvore::listarAux(No* atual) {
    if (atual == nullptr) return;

    listarAux(atual->esq);

    cout << "Nome: " << atual->nome
         << " | Sexo: " << atual->sexo
         << " | Idade: " << atual->idade
         << " | Peso: " << atual->peso << endl;

    listarAux(atual->dir);
}

void Arvore::listar() {
    if (raiz == nullptr) {
        cout << "> A arvore esta vazia." << endl;
        return;
    }
    listarAux(raiz);
}

// ---- Geração de Listas ----

void Arvore::gerarListasAux(No* atual, list<No*>& homens, list<No*>& mulheres) {
    if (atual == nullptr) return;

    gerarListasAux(atual->esq, homens, mulheres);

    if (atual->sexo == 'M' || atual->sexo == 'm')
        homens.push_back(atual);
    else if (atual->sexo == 'F' || atual->sexo == 'f')
        mulheres.push_back(atual);

    gerarListasAux(atual->dir, homens, mulheres);
}

void Arvore::gerarListas(list<No*>& homens, list<No*>& mulheres) {
    homens.clear();
    mulheres.clear();
    gerarListasAux(raiz, homens, mulheres);
}