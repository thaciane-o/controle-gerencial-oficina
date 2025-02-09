#ifndef MODELFORNECEDORES_H
#define MODELFORNECEDORES_H
#include "../../models/pecas/modelPecas.h"

struct Fornecedores {
    int id;
    char nomeFantasia[255];
    char razaoSocial[255];
    char inscricaoEstadual[14];
    char cnpj[15];
    char endereco[255];
    char ddd[3];
    char telefone[11];
    char email[255];
    int deletado;
};

struct ListaFornecedores {
    int qtdFornecedores;
    struct Fornecedores *listaFornecedores;
};

// Controles de armazenamento
void buscarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento);

void armazenarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento);

// Controles de alocação de memória
int alocarFornecedoresModel(struct ListaFornecedores *lista);

int realocarFornecedoresModel(struct ListaFornecedores *lista, int qtdAlocada);

// Controles de CRUD
void cadastrarFornecedoresModel(struct ListaFornecedores *lista, struct Fornecedores *fornecedor, int autoId);

void deletarFornecedoresModel(struct ListaFornecedores *lista, struct ListaPecas *pecasRelacionadas, int id);

int verificarIDFornecedoresModel(struct ListaFornecedores *lista, int id);

void atualizarFornecedoresModel(struct ListaFornecedores *lista, int id, struct Fornecedores *fornecedor);

void listarTodosFornecedoresModel(struct ListaFornecedores *lista);

void listarFornecedoresModel(struct ListaFornecedores *lista, int id);

#endif //MODELFORNECEDORES_H