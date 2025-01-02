#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H

#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"

void gerenciarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas,
                           struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                           struct ListaPagamentosCliente *listaPagamentosCliente, int opcaoArmazenamento);

void cadastrarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas,
                           struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                           struct ListaPagamentosCliente *listaPagamentosCliente);

void atualizarAgendamento(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                          struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos);

void listarAgendamentos(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico);

void deletarAgendamento(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico);

void finalizarAgendamento(struct ListaAgendamentos *lista);

#endif //AGENDAMENTOS_H
