#ifndef MODELFORNECEDORES_H
#define MODELFORNECEDORES_H

struct Fornecedores {
    int id;
    char nomeFantasia[255];
    char razaoSocial[255];
    char inscricaoEstadual[10];
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

void buscarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento);
void armazenarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento);
void alocarFornecedoresModel(struct ListaFornecedores *lista);
void realocarFornecedoresModel(struct ListaFornecedores *lista, int qtdAlocada);
void cadastrarFornecedoresModel(struct ListaFornecedores *lista, struct Fornecedores *fornecedor);
void deletarFornecedoresModel(struct ListaFornecedores *lista, int id);
int verificarIDFornecedoresModel(struct ListaFornecedores *lista, int id);
void atualizarFornecedoresModel(struct ListaFornecedores *lista, int id, struct Fornecedores *fornecedor);
void listarTodosFornecedoresModel(struct ListaFornecedores *lista);
void listarFornecedoresModel(struct ListaFornecedores *lista, int id);

#endif //MODELFORNECEDORES_H