
#ifndef MODELRELATORIOORDENSSERVICOS_H
#define MODELRELATORIOORDENSSERVICOS_H

#include <time.h>

#include "../../oficina/modelOficina.h"
#include "../../fornecedores/modelFornecedores.h"
#include "../../funcionarios/modelFuncionarios.h"
#include "../../ordensServico/modelOrdensServico.h"
#include "../../agendamentos/modelAgendamentos.h"
#include "../../clientes/modelClientes.h"
#include "../../pecas/modelPecas.h"
#include "../../pecasNotas/modelPecasNotas.h"
#include "../../pagamentoCliente/modelPagamentoCliente.h"
#include "../../veiculos/modelVeiculos.h"


void imprimirRelatorioServicosRealizados(struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id);

void armazenarRelatorioServicosRealizados(struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos,
                              struct tm dataInicial, struct tm dataFinal, int tipo,
                              int id);

#endif //MODELRELATORIOORDENSSERVICOS_H
