#ifndef VEICULOS_H
#define VEICULOS_H

#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/clientes/modelClientes.h"

void cadastrarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento);
void atualizarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento);
void listarVeiculo(struct ListaVeiculos *lista);
void deletarVeiculo(struct ListaVeiculos *lista);
void gerenciarVeiculos(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento);

#endif //VEICULOS_H
