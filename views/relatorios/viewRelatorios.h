#ifndef VIEWRELATORIOS_H
#define VIEWRELATORIOS_H


#include "../../models/oficina/modelOficina.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/pecasNotas/modelPecasNotas.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"

void gerenciarRelatorios(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                         struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                         struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                         struct ListaPecas *listaPecas, struct ListaPagamentosCliente *listaPagamentosCliente,
                         struct ListaAgendamentos *listaAgendamentos,
                         struct ListaNotasFiscais *listaNotas, struct ListaOrdensServico *listaOrdensServico,
                         struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                         struct ListaPecasNotas *listaPecasNotas, int opcaoArmazenamento);

void gerenciarCadastrosBasicos(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                               struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                               struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                               struct ListaPecas *listaPecas);



void filtroRelatorioBasico(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                           struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                           struct ListaPecas *listaPecas, int tipoRelatorio);

void filtroRelatorioEstoque(struct ListaNotasFiscais *listaNotas, struct ListaPecasNotas *listaPecasNotas,
                              struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServico,
                              struct ListaFornecedores *listaFornecedores,
                              struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                              struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                              struct ListaPagamentosCliente *listaPagamentosCliente, struct ListaVeiculos *listaVeiculos);

void filtroRelatorioProdutividade(struct ListaOrdensServico *listaOrdemServicos,
                                  struct ListaAgendamentos *listaAgendamentos,
                                  struct ListaFuncionarios *listafuncionarios);

int formaDeImprimir();

#endif //VIEWRELATORIOS_H
