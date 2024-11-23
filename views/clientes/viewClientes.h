#ifndef CLIENTES_H
#define CLIENTES_H
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"

void cadastrarCliente(struct ListaClientes *lista, struct ListaOficinas *listaOficinas);

void atualizarCliente(struct ListaClientes *lista, struct ListaOficinas *listaOficinas);

void listarClientes(struct ListaClientes *lista);

void deletarCliente(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, struct ListaServicos *listaServicos);

void gerenciarClientes(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, struct ListaOficinas *listaOficinas, struct ListaServicos *listaServicos, int opcaoArmazenamento);

#endif //CLIENTES_H
