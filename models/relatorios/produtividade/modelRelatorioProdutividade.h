#ifndef MODELRELATORIOPRODUTIVIDADE.H
#define MODELRELATORIOPRODUTIVIDADE

#include "../../ordensServico/modelOrdensServico.h"
#include "../../funcionarios/modelFuncionarios.h"
#include "../../agendamentos/modelAgendamentos.h"

void imprimirRelatorioProdutividade(struct ListaOrdensServico *listaOrdensServicos,
                                    struct ListaAgendamentos *listaAgendamentos,
                                    struct ListaFuncionarios *listaFuncionarios, int funcionario, int servico,
                                    struct tm dataHoraInicial,
                                    struct tm dataHoraFinal);

void armazenarRelatorioProdutividade(struct ListaOrdensServico *listaOrdensServicos,
                                     struct ListaAgendamentos *listaAgendamentos,
                                     struct ListaFuncionarios *listaFuncionarios, int funcionario, int servico,
                                     struct tm dataHoraInicial,
                                     struct tm dataHoraFinal);

#endif //MODELRELATORIOPRODUTIVIDADE
