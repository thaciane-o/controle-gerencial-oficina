#ifndef MODELCLIENTES_H
#define MODELCLIENTES_H
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/servicos/modelServicos.h"

struct Clientes {
    int id;
    char ddd[3];
    char telefone[11];
    char cpf_cnpj[15];
    char nome[255];
    char email[255];
    char endereco[255];
    int idOficina;
    int deletado;
};

struct ListaClientes {
    int qtdClientes;
    struct Clientes *listaClientes;
};

void buscarDadosClientesModel(struct ListaClientes *lista, int opcaoArmazenamento);

void armazenarDadosClienteModel(struct ListaClientes *lista, int opcaoArmazenamento);

int alocarClientesModel(struct ListaClientes *lista);

int realocarClientesModel(struct ListaClientes *lista, int qtdAlocada);

void cadastrarClientesModel(struct ListaClientes *lista, struct Clientes *cliente, int autoId);

void deletarClientesModel(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, int id);

void atualizarClientesModel(struct ListaClientes *lista, int id, struct Clientes *cliente);

int verificarIDClienteModel(struct ListaClientes *lista, int id);

void listarTodosClientesModel(struct ListaClientes *lista);

void listarClienteModel(struct ListaClientes *lista, int id);

void buscarClientesPorOficinaModel(struct ListaClientes *lista, int idOficina);

int getIdOficinaClientesModel(struct ListaClientes *lista, int idCliente);

int verificarRelacaoClienteComOficinaModel(struct ListaClientes *listaClientes,
                                 int idOficina, int idCliente);

#endif //MODELCLIENTES_H
