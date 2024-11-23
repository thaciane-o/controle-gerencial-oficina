#ifndef MODELSERVICOS_H
#define MODELSERVICOS_H


struct Servicos {
    int id;
    int idOficina;
    int idCliente;
    char descricao[255];
    float preco;
    float comissao;
    int deletado;
};

struct ListaServicos {
    int qtdServicos;
    struct Servicos *listaServicos;
};

// Controles de armazenamento
void buscarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento);

void armazenarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento);

// Controles de alocação de memória
void alocarMemoriaServicoModel(struct ListaServicos *lista);

void realocarMemoriaServicoModel(struct ListaServicos *lista, int qtdAloca);

// Controles de CRUD
void cadastrarServicoModel(struct ListaServicos *lista, struct Servicos *servicoCadastrando);

void deletarServicoModel(struct ListaServicos *lista, int id);

void atualizarServicoModel(struct ListaServicos *lista, int id, struct Servicos *servicoAlterando);

int verificarIDServicoModel(struct ListaServicos *lista, int id);

void listarTodosServicoModel(struct ListaServicos *lista);

void listarServicoModel(struct ListaServicos *lista, int id);

void buscarServicosPorOficinaModel(struct ListaServicos *lista, int idOficina);


#endif //MODELSERVICOS_H
