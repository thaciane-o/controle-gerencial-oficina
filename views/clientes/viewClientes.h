#ifndef CLIENTES_H
#define CLIENTES_H
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"

void cadastrarCliente(struct ListaClientes *lista);

void atualizarCliente(struct ListaClientes *lista);

void listarClientes(struct ListaClientes *lista);

void deletarCliente(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos);

void gerenciarClientes(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, int opcaoArmazenamento);

#endif //CLIENTES_H
