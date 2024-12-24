#ifndef FINANCEIRO_H
#define FINANCEIRO_H
#include "../../models/caixas/modelCaixa.h"
#include "../../models/oficina/modelOficina.h"

void gerenciarFinanceiro(struct ListaCaixas *lista, struct ListaOficinas *listaOficinas, int opcaoArmazenamento);

void consultarValorCaixa(struct ListaCaixas *lista);

#endif //FINANCEIRO_H