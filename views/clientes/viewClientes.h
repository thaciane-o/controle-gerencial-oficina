#ifndef CLIENTES_H
#define CLIENTES_H
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/oficina/modelOficina.h"

void cadastrarCliente(struct ListaClientes *lista, struct ListaOficinas *listaOficinas);

void atualizarCliente(struct ListaClientes *lista, struct ListaOficinas *listaOficinas);

void listarClientes(struct ListaClientes *lista);

void deletarCliente(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos);

void gerenciarClientes(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, struct ListaOficinas *listaOficinas, int opcaoArmazenamento);

#endif //CLIENTES_H
