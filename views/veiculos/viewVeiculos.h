#ifndef VEICULOS_H
#define VEICULOS_H

#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/agendamentos/modelAgendamentos.h"

void cadastrarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista);

void atualizarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista);

void listarVeiculo(struct ListaVeiculos *lista);

void deletarVeiculo(struct ListaVeiculos *lista, struct ListaAgendamentos *listaAgendamentos);

void gerenciarVeiculos(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista,
                       struct ListaAgendamentos *listaAgendamentos, int opcaoArmazenamento);

#endif //VEICULOS_H
