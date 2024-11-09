#ifndef MODELCLIENTES_H
#define MODELCLIENTES_H


struct Clientes {
    int isDeleted;
    int id;
    char DDD[3];
    char telefone[11];
    char CPF[12];
    char nome[255];
    char email[255];
    char endereco[255];
};

struct ListaClientes {
    int qtdClientes;
    struct Clientes *listaClientes;
};

void buscarDadosClientesModel(struct ListaClientes *lista);
void armazenarDadosClienteModel(struct ListaClientes *lista);
void alocarClientesModel(struct ListaClientes *lista);
void realocarClientesModel(struct ListaClientes *lista, int qtdAlocada);
void cadastrarClientesModel(struct ListaClientes *lista, struct Clientes *cliente);
void deletarClientesModel(struct ListaClientes *lista, int id);
void atualizarClientesModel(struct ListaClientes *lista, int id, struct Clientes *cliente);
void listarTodosClientesModel(struct ListaClientes *lista);
void listarClienteModel(struct ListaClientes *lista, int id);

#endif //MODELCLIENTES_H
