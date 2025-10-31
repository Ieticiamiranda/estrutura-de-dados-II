#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para std::max
#include <limits>    // Para limpar o buffer de entrada

// Usar o namespace std para facilitar
using namespace std;

/**
 * 1. ESTRUTURAS DE DADOS
 */

// Estrutura para os dados da pessoa (fornecida por você)
struct Pessoa {
    string nome;
    char sexo;
    int idade;
    double peso;

    Pessoa(string n = "", char s = ' ', int i = 0, double p = 0.0)
        : nome(n), sexo(s), idade(i), peso(p) {}
};

// Estrutura do Nó da Árvore (Modificada para AVL)
struct NoArvore {
    Pessoa dados;
    NoArvore *esq;
    NoArvore *dir;
    int altura; // Campo ADICIONAL para AVL

    // Construtor modificado
    NoArvore(Pessoa p) : dados(p), esq(NULL), dir(NULL), altura(1) {}
};


/**
 * 2. FUNÇÕES AUXILIARES DA AVL
 */

// Retorna a altura de um nó (seguro para nós nulos)
int alturaDoNo(NoArvore *no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Atualiza a altura de um nó com base em seus filhos
void atualizarAltura(NoArvore *no) {
    if (no != NULL) {
        no->altura = 1 + max(alturaDoNo(no->esq), alturaDoNo(no->dir));
    }
}

// Calcula o Fator de Balanceamento (FB) de um nó
int fatorBalanceamento(NoArvore *no) {
    if (no == NULL)
        return 0;
    // FB = Altura(Esquerda) - Altura(Direita)
    return alturaDoNo(no->esq) - alturaDoNo(no->dir);
}

/**
 * 3. ROTAÇÕES DA AVL
 */

/*
       y                               x
      / \                             / \
     x   T3  -- Rotação Direita(y) ->  T1  y
    / \                                 / \
   T1  T2                               T2  T3
*/
NoArvore *rotacaoDireita(NoArvore *y) {
    NoArvore *x = y->esq;
    NoArvore *T2 = x->dir;

    // Realiza a rotação
    x->dir = y;
    y->esq = T2;

    // Atualiza alturas (IMPORTANTE: atualizar y ANTES de x)
    atualizarAltura(y);
    atualizarAltura(x);

    return x; // Nova raiz
}

/*
    x                               y
   / \                             / \
  T1  y   -- Rotação Esquerda(x) -> x   T3
     / \                           / \
    T2  T3                         T1  T2
*/
NoArvore *rotacaoEsquerda(NoArvore *x) {
    NoArvore *y = x->dir;
    NoArvore *T2 = y->esq;

    // Realiza a rotação
    y->esq = x;
    x->dir = T2;

    // Atualiza alturas (IMPORTANTE: atualizar x ANTES de y)
    atualizarAltura(x);
    atualizarAltura(y);

    return y; // Nova raiz
}

// Função auxiliar para encontrar o menor nó (sucessor em ordem)
NoArvore* menorNo(NoArvore* no) {
    NoArvore* atual = no;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}


/**
 * 4. FUNÇÕES PRINCIPAIS DO MENU
 */

// --- Inserir Dado (Versão AVL) ---
NoArvore *inserirPessoa(NoArvore *raiz, Pessoa p) {
    // 1. Inserção padrão de BST
    if (raiz == NULL) {
        return new NoArvore(p);
    }

    if (p.nome < raiz->dados.nome) {
        raiz->esq = inserirPessoa(raiz->esq, p);
    } else if (p.nome > raiz->dados.nome) {
        raiz->dir = inserirPessoa(raiz->dir, p);
    } else {
        // Nomes duplicados não são permitidos
        cout << "Erro: Pessoa com nome '" << p.nome << "' ja existe." << endl;
        return raiz;
    }

    // 2. Atualizar a altura deste nó ancestral
    atualizarAltura(raiz);

    // 3. Obter o fator de balanceamento para verificar se desbalanceou
    int fb = fatorBalanceamento(raiz);

    // 4. Rebalancear, se necessário (4 casos)

    // Caso Esquerda-Esquerda (LL)
    if (fb > 1 && p.nome < raiz->esq->dados.nome) {
        return rotacaoDireita(raiz);
    }

    // Caso Direita-Direita (RR)
    if (fb < -1 && p.nome > raiz->dir->dados.nome) {
        return rotacaoEsquerda(raiz);
    }

    // Caso Esquerda-Direita (LR)
    if (fb > 1 && p.nome > raiz->esq->dados.nome) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Caso Direita-Esquerda (RL)
    if (fb < -1 && p.nome < raiz->dir->dados.nome) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    // Se já estava balanceado, retorna a raiz original
    return raiz;
}

// --- Remoção de Dado (Versão AVL) ---
NoArvore *removerPessoa(NoArvore *raiz, string nome) {
    // 1. Remoção padrão de BST
    if (raiz == NULL) {
        cout << "Erro: Pessoa com nome '" << nome << "' nao encontrada." << endl;
        return raiz;
    }

    if (nome < raiz->dados.nome) {
        raiz->esq = removerPessoa(raiz->esq, nome);
    } else if (nome > raiz->dados.nome) {
        raiz->dir = removerPessoa(raiz->dir, nome);
    } else {
        // Nó encontrado! Vamos removê-lo

        // Caso 1: Nó com 0 ou 1 filho
        if (raiz->esq == NULL || raiz->dir == NULL) {
            NoArvore *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) { // 0 filhos
                temp = raiz;
                raiz = NULL;
            } else { // 1 filho
                *raiz = *temp; // Copia o conteúdo do filho
            }
            delete temp;
        } else {
            // Caso 2: Nó com 2 filhos
            // Pega o sucessor em ordem (menor da subárvore direita)
            NoArvore* temp = menorNo(raiz->dir);

            // Copia os dados do sucessor para este nó
            raiz->dados = temp->dados;

            // Remove o sucessor (que agora é uma duplicata)
            raiz->dir = removerPessoa(raiz->dir, temp->dados.nome);
        }
    }

    // Se a árvore ficou vazia após a remoção (era o único nó)
    if (raiz == NULL) {
        return raiz;
    }

    // 2. Atualizar a altura
    atualizarAltura(raiz);

    // 3. Obter o fator de balanceamento
    int fb = fatorBalanceamento(raiz);

    // 4. Rebalancear, se necessário (4 casos)

    // Caso LL
    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0) {
        return rotacaoDireita(raiz);
    }

    // Caso LR
    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Caso RR
    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0) {
        return rotacaoEsquerda(raiz);
    }

    // Caso RL
    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}


// --- Consulta de Dado ---
Pessoa* consultarPessoa(NoArvore *raiz, string nome) {
    if (raiz == NULL) {
        return NULL; // Não encontrado
    }

    if (nome == raiz->dados.nome) {
        return &(raiz->dados); // Encontrado! Retorna ponteiro para os dados
    }

    if (nome < raiz->dados.nome) {
        return consultarPessoa(raiz->esq, nome);
    } else {
        return consultarPessoa(raiz->dir, nome);
    }
}

// --- Listagem de Árvore (Em Ordem) ---
void imprimirEmOrdem(NoArvore *raiz) {
    if (raiz == NULL) {
        return;
    }
    imprimirEmOrdem(raiz->esq);
    
    cout << "  - Nome: " << raiz->dados.nome
         << ", Sexo: " << raiz->dados.sexo
         << ", Idade: " << raiz->dados.idade
         << ", Peso: " << raiz->dados.peso << endl;
         
    imprimirEmOrdem(raiz->dir);
}


/**
 * 5. FUNÇÕES DE LISTAGEM POR SEXO (Reutilizadas do seu código)
 */

// Função de impressão (fornecida por você)
void imprimirLista(const string &titulo, const vector<Pessoa> &lista) {
    cout << "--- " << titulo << " ---" << endl;
    if (lista.empty()) {
        cout << "(Lista vazia)" << endl;
        return;
    }
    for (const auto &p : lista) {
        cout << "Nome: " << p.nome
             << ", Sexo: " << p.sexo
             << ", Idade: " << p.idade
             << ", Peso: " << p.peso << endl;
    }
    cout << endl;
}

// Função de preenchimento (fornecida por você)
void preencherListasPorSexo(NoArvore *no,
                            vector<Pessoa> &listaHomens,
                            vector<Pessoa> &listaMulheres)
{
    if (no == NULL) {
        return;
    }
    preencherListasPorSexo(no->esq, listaHomens, listaMulheres);
    if (no->dados.sexo == 'M' || no->dados.sexo == 'm') {
        listaHomens.push_back(no->dados);
    } else if (no->dados.sexo == 'F' || no->dados.sexo == 'f') {
        listaMulheres.push_back(no->dados);
    }
    preencherListasPorSexo(no->dir, listaHomens, listaMulheres);
}

// Função principal de listagem (fornecida por você)
void gerarListasOrdenadas(NoArvore *RAIZ,
                          vector<Pessoa> &listaHomens,
                          vector<Pessoa> &listaMulheres)
{
    listaHomens.clear();
    listaMulheres.clear();
    preencherListasPorSexo(RAIZ, listaHomens, listaMulheres);
}

// Função de limpeza (fornecida por você)
void limparArvore(NoArvore *no)
{
    if (no == NULL)
        return;
    limparArvore(no->esq);
    limparArvore(no->dir);
    delete no;
}

// Função auxiliar para limpar o buffer de entrada (cin)
void limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * 6. FUNÇÃO MAIN (Menu)
 */

int main() {
    NoArvore* RAIZ = NULL;
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n--- MENU ARVORE AVL ---" << endl;
        cout << "1. Inserir Pessoa" << endl;
        cout << "2. Remover Pessoa" << endl;
        cout << "3. Consultar Pessoa" << endl;
        cout << "4. Listar Arvore (em ordem)" << endl;
        cout << "5. Listar por Sexo (H/M)" << endl;
        cout << "0. Sair" << endl;
        cout << "-----------------------" << endl;
        cout << "Escolha uma opcao: ";
        
        cin >> opcao;

        // Validação de entrada
        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, digite um numero." << endl;
            cin.clear();
            limparBufferEntrada();
            opcao = -1; // Reseta a opção para continuar no loop
            continue;
        }

        limparBufferEntrada(); // Limpa o '\n' deixado pelo cin >>

        switch (opcao) {
            case 1: {
                // Inserir
                string nome, temp;
                char sexo;
                int idade;
                double peso;
                
                cout << "Nome: ";
                getline(cin, nome);
                cout << "Sexo (M/F): ";
                cin >> sexo;
                sexo = toupper(sexo); // Garante maiúscula
                cout << "Idade: ";
                cin >> idade;
                cout << "Peso: ";
                cin >> peso;
                limparBufferEntrada(); // Limpa o buffer após o último cin >>

                if (sexo != 'M' && sexo != 'F') {
                    cout << "Sexo invalido. Abortando insercao." << endl;
                } else {
                    Pessoa p(nome, sexo, idade, peso);
                    RAIZ = inserirPessoa(RAIZ, p);
                    cout << "Pessoa inserida (ou ja existia)." << endl;
                }
                break;
            }
            case 2: {
                // Remover
                string nome;
                cout << "Nome da pessoa a remover: ";
                getline(cin, nome);
                RAIZ = removerPessoa(RAIZ, nome);
                cout << "Remocao tentada." << endl;
                break;
            }
            case 3: {
                // Consultar
                string nome;
                cout << "Nome da pessoa a consultar: ";
                getline(cin, nome);
                Pessoa* p = consultarPessoa(RAIZ, nome);
                if (p != NULL) {
                    cout << "Pessoa encontrada:" << endl;
                    cout << "  - Nome: " << p->nome
                         << ", Sexo: " << p->sexo
                         << ", Idade: " << p->idade
                         << ", Peso: " << p->peso << endl;
                } else {
                    cout << "Pessoa com nome '" << nome << "' nao encontrada." << endl;
                }
                break;
            }
            case 4: {
                // Listar (em ordem)
                cout << "\n--- Listagem em Ordem Alfabética ---" << endl;
                if (RAIZ == NULL) {
                    cout << "(Arvore vazia)" << endl;
                } else {
                    imprimirEmOrdem(RAIZ);
                }
                break;
            }
            case 5: {
                // Listar por Sexo
                vector<Pessoa> homens, mulheres;
                gerarListasOrdenadas(RAIZ, homens, mulheres);
                
                cout << "\n--- Listagem por Sexo ---" << endl;
                imprimirLista("Homens", homens);
                imprimirLista("Mulheres", mulheres);
                break;
            }
            case 0: {
                // Sair
                cout << "Encerrando o programa..." << endl;
                break;
            }
            default: {
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
            }
        }
    }

    // Limpa toda a memória alocada pela árvore antes de sair
    limparArvore(RAIZ);
    return 0;
}