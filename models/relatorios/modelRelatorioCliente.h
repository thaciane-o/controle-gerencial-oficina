#ifndef MODELRELATORIOCLIENTE.H
#define MODELRELATORIOCLIENTE

#include "../oficina/modelOficina.h"
#include "../clientes/modelClientes.h"

void imprimirRelatorioCliente(struct ListaClientes *listaClientes, struct ListaOficinas *listaOficinas, char *nome,
                              int id);

void armazenarRelatorioCliente(struct ListaClientes *listaClientes, struct ListaOficinas *listaOficinas, char *nome,
                              int id);

#endif //MODELRELATORIOCLIENTE
