#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/servicos/modelServicos.h"

void cadastrarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos);

void gerenciarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                       struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                       int opcaoArmazenamento);

#endif //AGENDAMENTOS_H
