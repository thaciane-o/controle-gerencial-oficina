#ifndef MODELRELATORIOVEICULO.H
#define MODELRELATORIOVEICULO

#include "../../veiculos/modelVeiculos.h"
#include "../../clientes/modelClientes.h"

void imprimirRelatorioVeiculo(struct ListaVeiculos *listaVeiculos, struct ListaClientes *listaClientes, char *nome,
                              int id);

void armazenarRelatorioVeiculo(struct ListaVeiculos *listaVeiculos, struct ListaClientes *listaClientes, char *nome,
                               int id);

#endif //MODELRELATORIOVEICULO
