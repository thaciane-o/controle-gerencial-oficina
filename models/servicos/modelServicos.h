#ifndef MODELSERVICOS_H
#define MODELSERVICOS_H

struct Servicos {
    int id;
    int idOficina;
    char descricao[255];
    float preco;
    float comissao;
    int deletado;
};

struct ListaServicos {
    int qtdServicos;
    struct Servicos *listaServicos;
};

void buscarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento);

void armazenarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento);

int alocarMemoriaServicoModel(struct ListaServicos *lista);

int realocarMemoriaServicoModel(struct ListaServicos *lista, int qtdAloca);

void cadastrarServicoModel(struct ListaServicos *lista, struct Servicos *servicoCadastrando);

void deletarServicoModel(struct ListaServicos *lista, int id);

void atualizarServicoModel(struct ListaServicos *lista, int id, struct Servicos *servicoAlterando);

int verificarIDServicoModel(struct ListaServicos *lista, int id);

void listarTodosServicoModel(struct ListaServicos *lista);

void listarServicoModel(struct ListaServicos *lista, int id);

void buscarServicosPorOficinaModel(struct ListaServicos *lista, int idOficina);


#endif //MODELSERVICOS_H
