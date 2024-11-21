
#ifndef MODELPECAS_H
#define MODELPECAS_H

struct Pecas {
    int id;
    char descricao[255];
    char fabricante[255];
    float precoCusto;
    float precoVenda;
    int qtdEstoque;
    int estoqueMinimo;
    int idFornecedor;
    int deletado;
};

struct ListaPecas {
    int qtdPecas;
    struct Pecas *listaPecas;
};

// Controles de armazenamento
void buscarDadosPecaModel(struct ListaPecas *lista, int opcaoArmazenamento);
void armazenarDadosPecaModel(struct ListaPecas *lista, int opcaoArmazenamento);

// Controles de alocação de memória
void alocarMemoriaPecaModel(struct ListaPecas *lista);
void realocarMemoriaPecaModel(struct ListaPecas *oficinas, int qtdAloca);

// Controles de CRUD
void cadastrarPecaModel(struct ListaPecas *lista, struct Pecas *pecaCadastrando);
void deletarPecaModel(struct ListaPecas *lista, int id);
void atualizarPecaModel(struct ListaPecas *lista, int id, struct Pecas *pecaAlterando);
int verificarIDPecaModel(struct ListaPecas *lista, int id);
void listarTodosPecaModel(struct ListaPecas *lista);
void buscarIdPecaModel(struct ListaPecas *lista, int id);
void buscarPecasPorFornecedorModel(struct ListaPecas *lista, int idFornecedor);

#endif //MODELPECAS_H
