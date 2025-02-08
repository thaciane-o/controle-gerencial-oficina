//
// Created by ferna on 07/02/2025.
//

#ifndef MODELRELATORIOFINANCEIRO_H
#define MODELRELATORIOFINANCEIRO_H


#include "../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../models/oficina/modelOficina.h"
#include "../models/caixas/modelCaixa.h"
#include "../models/clientes/modelClientes.h"
#include "../models/fornecedores/modelFornecedores.h"

void imprimirRelatorioFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                                 struct ListaPagamentosCliente *listaPagamentosCliente,
                                 struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                 struct ListaClientes *listaClientes,
                                 struct ListaFornecedores *listaFornecedores, int id, int tipoConta, int tipoFiltro,
                                 struct tm dataHoraInicial,
                                 struct tm dataHoraFinal);

void armazenarRelatorioFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                                 struct ListaPagamentosCliente *listaPagamentosCliente,
                                 struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                 struct ListaClientes *listaClientes,
                                 struct ListaFornecedores *listaFornecedores, int id, int tipoConta, int tipoFiltro,
                                 struct tm dataHoraInicial,
                                 struct tm dataHoraFinal);

#endif //MODELRELATORIOFINANCEIRO_H
