#ifndef ARVORES_H
#define ARVORES_H

#include <string>
#include <vector>

using namespace std;

struct NO
{
    int info;
    int contador;
    NO *esq;
    NO *dir;

    NO(int val);
};

class ArvoreBin
{
private:
    NO *raiz;

    NO *inserirRecursivo(NO *no, int valorInserir);
    void emOrdemRecursivo(NO *no);
    void preOrdemRecursivo(NO *no);
    void posOrdemRecursivo(NO *no);
    NO *encontrarMinimo(NO *no);
    NO *removerMinimo(NO *no);
    NO *removerRecursivo(NO *no, int valorRemover);
    int encontrarMaximoRecursivo(NO *no);
    void encontrarRepetidosRecursivo(NO *no, bool &encontrado);
    int ArvoreCheia(NO *no);

public:
    ArvoreBin();

    void inserir(int valorInserir);
    void remover(int valorRemover);
    void listar();
    void encontrarMaximo();
    void imprimirEmOrdem();
    void mostrarRepetidos();
    void verificarArvoreCheia();
};

#endif 