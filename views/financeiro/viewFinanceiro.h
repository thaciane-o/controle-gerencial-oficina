#ifndef FINANCEIRO_H
#define FINANCEIRO_H
#include "../../models/caixas/modelCaixa.h"
#include "../../models/oficina/modelOficina.h"

void gerenciarFinanceiro(struct ListaCaixas *lista, struct ListaOficinas *listaOficinas, struct ListaClientes *listaClintes, struct ListaPagamentosCliente *listaPagamentosCliente, int opcaoArmazenamento);

void consultarValorCaixa(struct ListaCaixas *lista);

void registrarRecebimentoCliente(struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas, struct ListaPagamentosCliente *listaPagamentosCliente);

void consultarContasAReceber(struct ListaPagamentosCliente *listaPagamentosCliente, struct ListaCaixas *listaCaixas);

#endif //FINANCEIRO_H