#ifndef MODELEXPORTACAO_H
#define MODELEXPORTACAO_H

#include <stdio.h>

#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/pecasNotas/modelPecasNotas.h"

void exportaDadosModel(struct ListaClientes *listaClientes,
                       struct ListaVeiculos *listaVeiculos,
                       struct ListaOficinas *listaOficinas,
                       struct ListaPecas *listaPecas,
                       struct ListaFornecedores *listaFornecedores,
                       struct ListaServicos *listaServicos,
                       struct ListaFuncionarios *listaFuncionarios,
                       struct ListaCaixas *listaCaixas,
                       struct ListaPagamentosCliente *listaPagamentosCliente,
                       struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                       struct ListaAgendamentos *listaAgendamentos,
                       struct ListaOrdensServico *listaOrdensServico,
                       struct ListaNotasFiscais *listaNotasFiscais,
                       struct ListaPecasNotas *listaPecasNotas,
                       int *opcoesExportacao);

void importaDadosModel(struct ListaClientes *listaClientes,
                       struct ListaVeiculos *listaVeiculos,
                       struct ListaOficinas *listaOficinas,
                       struct ListaPecas *listaPecas,
                       struct ListaFornecedores *listaFornecedores,
                       struct ListaServicos *listaServicos,
                       struct ListaFuncionarios *listaFuncionarios,
                       struct ListaCaixas *listaCaixas,
                       struct ListaPagamentosCliente *listaPagamentosCliente,
                       struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                       struct ListaAgendamentos *listaAgendamentos,
                       struct ListaOrdensServico *listaOrdensServico,
                       struct ListaNotasFiscais *listaNotasFiscais,
                       struct ListaPecasNotas *listaPecasNotas,
                       FILE* arquivo,
                       int *opcoesImportacao,
                       int opcaoArmazenamento);

#endif //MODELEXPORTACAO_H
