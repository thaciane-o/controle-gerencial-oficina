#ifndef MODELRELATORIOFINANCEIRO_H
#define MODELRELATORIOFINANCEIRO_H


#include "../../oficina/modelOficina.h"
#include "../../clientes/modelClientes.h"
#include "../../fornecedores/modelFornecedores.h"
#include "../../pagamentoCliente/modelPagamentoCliente.h"
#include "../../pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../caixas/modelCaixa.h"

#include <time.h>


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
