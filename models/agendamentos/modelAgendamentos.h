#ifndef MODELAGENDAMENTOS_H
#define MODELAGENDAMENTOS_H
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/funcionarios/modelFuncionarios.h"

struct Agendamentos {
    int id;
    char data[11];
    char hora[6];
    int idVeiculo;
    int idServico;
    int idFuncionario;
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

void atualizarAgendamentosModel(struct ListaAgendamentos *lista, int id, struct Agendamentos *agendamento);

void listarTodosAgendamentosModel(struct ListaAgendamentos *lista);

void listarAgendamentosModel(struct ListaAgendamentos *lista, int id);

void buscarAgendamentosPorServicoModel(struct ListaAgendamentos *lista, int idServico);

void buscarAgendamentosPorFuncionarioModel(struct ListaAgendamentos *lista, int idFuncionario);

void buscarAgendamentosPorVeiculoModel(struct ListaAgendamentos *lista, int idVeiculo);

void deletarAgendamentosModel(struct ListaAgendamentos *lista, int id);

#endif //MODELAGENDAMENTOS_H
