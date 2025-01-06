#ifndef MODELAGENDAMENTOS_H
#define MODELAGENDAMENTOS_H
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/ordensServico/modelOrdensServico.h"

struct Agendamentos {
    int id;
    char datahoraInicial[17];
    int idVeiculo;
    int idServico;
    int idFuncionario;
    int finalizado;
    int deletado;
};

struct ListaAgendamentos {
    int qtdAgendamentos;
    struct Agendamentos *listaAgendamentos;
};

void buscarDadosAgendamentosModel(struct ListaAgendamentos *lista, int opcaoArmazenamento);

void armazenarDadosAgendamentosModel(struct ListaAgendamentos *lista, int opcaoArmazenamento);

int alocarAgendamentosModel(struct ListaAgendamentos *lista);

int realocarAgendamentosModel(struct ListaAgendamentos *lista, int qtdAlocada);

void cadastrarAgendamentosModel(struct ListaAgendamentos *lista, struct Agendamentos *agendamento);

int verificarIDAgendamentoModel(struct ListaAgendamentos *lista, int id);

void listarTodosAgendamentosModel(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico);

void listarAgendamentoModel(struct ListaAgendamentos *lista, int id, struct ListaOrdensServico *listaOrdensServico);

void buscarAgendamentosPorServicoModel(struct ListaAgendamentos *lista, int idServico, struct ListaOrdensServico *listaOrdensServico);

void buscarAgendamentosPorFuncionarioModel(struct ListaAgendamentos *lista, int idFuncionario, struct ListaOrdensServico *listaOrdensServico);

void buscarAgendamentosPorVeiculoModel(struct ListaAgendamentos *lista, int idVeiculo, struct ListaOrdensServico *listaOrdensServico);

void deletarAgendamentosModel(struct ListaAgendamentos *lista, int id, struct ListaOrdensServico *listaOrdensServico);

void finalizarAgendamentoModel(struct ListaAgendamentos *lista, int id);

#endif //MODELAGENDAMENTOS_H    
