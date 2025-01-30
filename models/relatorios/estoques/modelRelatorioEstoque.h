//
// Created by ferna on 29/01/2025.
//

#ifndef MODELRELATORIOESTOQUE_H
#define MODELRELATORIOESTOQUE_H

#include "../../oficina/modelOficina.h"
#include "../../fornecedores/modelFornecedores.h"
#include "../../funcionarios/modelFuncionarios.h"
#include "../../pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../ordensServico/modelOrdensServico.h"
#include "../../agendamentos/modelAgendamentos.h"
#include "../../clientes/modelClientes.h"
#include "../../notasFiscais/modelNotasFiscais.h"
#include "../../pecas/modelPecas.h"
#include "../../pecasNotas/modelPecasNotas.h"

void imprimirRelatorioEstoque(struct ListaNotasFiscais *listaNotas, struct ListaPecasNotas *listaPecasNotas,
                              struct ListaPecas *listaPecas, struct ListaClientes *listaClientes, struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFornecedores *listaFornecedores,
                              struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                              struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                              struct ListaPagamentosCliente *listaPagamentosCliente,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id);

void armazenarRelatorioEstoque(struct ListaNotasFiscais *listaNotas, struct ListaPecasNotas *listaPecasNotas,
                              struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaFornecedores *listaFornecedores,
                              struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                              struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                              struct ListaPagamentosCliente *listaPagamentosCliente,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id);

#endif //MODELRELATORIOESTOQUE_H
