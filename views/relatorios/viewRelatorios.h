#ifndef VIEWRELATORIOS_H
#define VIEWRELATORIOS_H


#include "../../models/oficina/modelOficina.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pecasNotas/modelPecasNotas.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"

void gerenciarRelatorios(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                         struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                         struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                         struct ListaPecas *listaPecas, struct ListaOrdensServico *listaOrdensServicos,
                         struct ListaAgendamentos *listaAgendamentos, struct ListaCaixas *listaCaixas,
                         struct ListaPagamentosCliente *listaPagamentosCliente,
                         struct ListaPagamentosFornecedor *listaPagamentosFornecedor, int opcaoArmazenamento);

void gerenciarCadastrosBasicos(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                               struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                               struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                               struct ListaPecas *listaPecas);



void filtroRelatorioBasico(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                           struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                           struct ListaPecas *listaPecas, int tipoRelatorio);

void filtroRelatorioEstoque(struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServico,
                              struct ListaFuncionarios *listaFuncionarios, struct ListaVeiculos *listaVeiculos);

void filtroRelatorioProdutividade(struct ListaOrdensServico *listaOrdemServicos,
                                  struct ListaAgendamentos *listaAgendamentos,
                                  struct ListaFuncionarios *listafuncionarios);

void filtroRelatorioFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                               struct ListaPagamentosCliente *listaPagamentosCliente,
                               struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                               struct ListaClientes *listaClientes,
                               struct ListaFornecedores *listaFornecedores);


void filtroRelatorioServicosRealizados(struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos);

int formaDeImprimir();

#endif //VIEWRELATORIOS_H
