#ifndef CLIENTES_H
#define CLIENTES_H
#include "../../models/clientes/modelClientes.h"

void cadastrarCliente(struct ListaClientes *lista);

void atualizarCliente(struct ListaClientes *lista);

void listarClientes(struct ListaClientes *lista);

void deletarCliente(struct ListaClientes *lista);

void gerenciarClientes(struct ListaClientes *lista, int opcaoArmazenamento);

#endif //CLIENTES_H
