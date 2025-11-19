#include "arvores.h"
#include <iostream>
#include <climits>
#include <stdlib.h>

using namespace std;

NO::NO(int val) : info(val), contador(1), esq(NULL), dir(NULL) {}

ArvoreBin::ArvoreBin() : raiz(NULL) {}

NO *ArvoreBin::inserirRecursivo(NO *no, int valorInserir)
{
    if (no == NULL)
    {
        return new NO(valorInserir);
    }
    if (valorInserir < no->info)
    {
        no->esq = inserirRecursivo(no->esq, valorInserir);
    }
    else if (valorInserir > no->info)
    {
        no->dir = inserirRecursivo(no->dir, valorInserir);
    }
    else
    {
        no->contador++;
    }
    return no;
}

void ArvoreBin::emOrdemRecursivo(NO *no)
{
    if (no != NULL)
    {
        emOrdemRecursivo(no->esq);
        cout << no->info << " ";
        emOrdemRecursivo(no->dir);
    }
}

void ArvoreBin::preOrdemRecursivo(NO *no)
{
    if (no != NULL)
    {
        cout << no->info << " ";
        preOrdemRecursivo(no->esq);
        preOrdemRecursivo(no->dir);
    }
}

void ArvoreBin::posOrdemRecursivo(NO *no)
{
    if (no != NULL)
    {
        posOrdemRecursivo(no->esq);
        posOrdemRecursivo(no->dir);
        cout << no->info << " ";
    }
}

NO *ArvoreBin::encontrarMinimo(NO *no)
{
    while (no != NULL && no->esq != NULL)
    {
        no = no->esq;
    }
    return no;
}

NO *ArvoreBin::removerMinimo(NO *no)
{
    if (no->esq == NULL)
    {
        NO *temp = no->dir;
        delete no;
        return temp;
    }
    no->esq = removerMinimo(no->esq);
    return no;
}

NO *ArvoreBin::removerRecursivo(NO *no, int valorRemover)
{
    if (no == NULL)
    {
        return NULL;
    }
    if (valorRemover < no->info)
    {
        no->esq = removerRecursivo(no->esq, valorRemover);
    }
    else if (valorRemover > no->info)
    {
        no->dir = removerRecursivo(no->dir, valorRemover);
    }
    else
    {
        if (no->contador > 1)
        {
            no->contador--;
            return no;
        }
        if (no->esq == NULL)
        {
            NO *temp = no->dir;
            delete no;
            return temp;
        }
        else if (no->dir == NULL)
        {
            NO *temp = no->esq;
            delete no;
            return temp;
        }
        NO *sucessor = encontrarMinimo(no->dir);
        no->info = sucessor->info;
        no->contador = sucessor->contador;
        no->dir = removerMinimo(no->dir);
    }
    return no;
}

int ArvoreBin::encontrarMaximoRecursivo(NO *no) // questao 2 - parte A
{
    if (no == NULL)
        return INT_MIN;
    if (no->dir == NULL)
        return no->info;
    return encontrarMaximoRecursivo(no->dir);
}

void ArvoreBin::encontrarRepetidosRecursivo(NO *no, bool &encontrado) // questao 4 - parte A
{
    if (no == NULL)
        return;
    encontrarRepetidosRecursivo(no->esq, encontrado);
    if (no->contador > 1)
    {
        cout << "> Valor: " << no->info << " (aparece " << no->contador << " vezes)" << endl;
        encontrado = true;
    }
    encontrarRepetidosRecursivo(no->dir, encontrado);
}

int ArvoreBin::ArvoreCheia(NO *no) // questao 5 - parte A
{
    if (no == NULL)
        return 1;
    if (no->esq == NULL && no->dir == NULL)
        return 1;
    if ((no->esq == NULL) ^ (no->dir == NULL))
        return 0;
    return ArvoreCheia(no->esq) && ArvoreCheia(no->dir);
}

void ArvoreBin::inserir(int valorInserir)
{
    raiz = inserirRecursivo(raiz, valorInserir);
}

void ArvoreBin::remover(int valorRemover)
{
    raiz = removerRecursivo(raiz, valorRemover);
}

void ArvoreBin::listar()
{
    if (raiz == NULL)
    {
        cout << "A Arvore esta vazia." << endl;
        return;
    }
    int escolha;
    system("cls");
    cout << "========================================================" << endl;
    cout << "             SELECIONE UM TIPO DE LISTAGEM              " << endl;
    cout << "========================================================" << endl;
    cout << "  [1] EM ORDEM                                          " << endl;
    cout << "  [2] PRE-ORDEM                                         " << endl;
    cout << "  [3] POS-ORDEM                                         " << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "  OPCAO ESCOLHIDA: ";
    cin >> escolha;
    switch (escolha)
    {
    case 1:
    system("cls");
        cout << "--------------------------------------------" << endl;
        cout << "           IMPRESSAO EM ORDEM               " << endl;
        cout << "--------------------------------------------" << endl;
        emOrdemRecursivo(raiz);
        break;
    case 2:
    system("cls");
        cout << "--------------------------------------------" << endl;
        cout << "           IMPRESSAO PRE-ORDEM              " << endl;
        cout << "--------------------------------------------" << endl;
        preOrdemRecursivo(raiz);
        break;
    case 3:
    system("cls");
        cout << "--------------------------------------------" << endl;
        cout << "           IMPRESSAO POS-ORDEM              " << endl;
        cout << "--------------------------------------------" << endl;
        posOrdemRecursivo(raiz);
        break;
    default:
        cout << "Opcao invalida." << endl;
        break;
    }
    cout << endl;
}

void ArvoreBin::encontrarMaximo() // questao 2 - parte A
{
    int valorMaximo = encontrarMaximoRecursivo(raiz);
    if (valorMaximo == INT_MIN)
    {
        cout << "> A arvore esta vazia." << endl;
    }
    else
    {
        cout << "> O maior valor na arvore eh: " << valorMaximo << endl;
    }
}

void ArvoreBin::imprimirEmOrdem()
{
    if (raiz == NULL)
    {
        cout << "> Arvore (Em Ordem): [vazia]" << endl;
        return;
    }
    cout << "> Arvore (Em Ordem): ";
    emOrdemRecursivo(raiz);
    cout << endl;
}

void ArvoreBin::mostrarRepetidos() // questao 4 - parte A
{
    if (raiz == NULL)
    {
        cout << "Arvore esta vazia." << endl;
        return;
    }
    cout << "--------------------------------------------" << endl;
    bool algumRepetido = false;
    encontrarRepetidosRecursivo(raiz, algumRepetido);
    if (!algumRepetido)
    {
        cout << "> Nenhum numero repetido encontrado na arvore." << endl;
    }
}

void ArvoreBin::verificarArvoreCheia() // questao 5 - parte A
{
    int resultado = ArvoreCheia(raiz);
    cout << "--------------------------------------------" << endl;
    if (resultado == 1)
    {
        cout << "> A arvore ESTA cheia (retorno 1)." << endl;
        cout << "> Ou seja, esta vazia ou todos os nos tem 0 ou 2 filhos." << endl;
    }
    else
    {
        cout << "> A arvore NAO esta cheia (retorno 0)." << endl;
        cout << "> Ou seja, pelo menos um no tem apenas 1 filho." << endl;
    }
}