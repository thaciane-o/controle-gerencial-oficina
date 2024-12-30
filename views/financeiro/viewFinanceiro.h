#ifndef FINANCEIRO_H
#define FINANCEIRO_H

#include "../../models/caixas/modelCaixa.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/fornecedores/modelFornecedores.h"

void gerenciarFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                         struct ListaClientes *listaClientes, struct ListaPagamentosCliente *listaPagamentosCliente,
                         struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                         struct ListaFornecedores *listaFornecedor,
                         int opcaoArmazenamento);

void consultarValorCaixa(struct ListaCaixas *lista, struct ListaPagamentosCliente *listaPagamentosCliente);

void registrarRecebimentoCliente(struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                                 struct ListaPagamentosCliente *listaPagamentosCliente);

void consultarContasAReceber(struct ListaPagamentosCliente *listaPagamentosCliente, struct ListaCaixas *listaCaixas);

void consultarContasAPagar(struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                           struct ListaCaixas *listaCaixas);

void efetuarPagamentoFornecedor(struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                struct ListaFornecedores *listaFornecedores, struct ListaCaixas *listaCaixas);

#endif //FINANCEIRO_H
