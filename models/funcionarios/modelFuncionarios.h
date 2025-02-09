#ifndef MODELFUNCIONARIOS_H
#define MODELFUNCIONARIOS_H

#include "../../models/agendamentos/modelAgendamentos.h"

struct Funcionarios {
    int id;
    char nome[255];
    char cpf[12];
    char cargo[255];
    float salario;
    int idOficina;
    int deletado;
};

struct ListaFuncionarios {
    int qtdFuncionarios;
    struct Funcionarios *listaFuncionarios;
};

void buscarDadosFuncionariosModel(struct ListaFuncionarios *lista, int opcaoArmazenamento);

void armazenarDadosFuncionariosModel(struct ListaFuncionarios *lista, int opcaoArmazenamento);

int alocarFuncionariosModel(struct ListaFuncionarios *lista);

int realocarFuncionariosModel(struct ListaFuncionarios *lista, int qtdAlocada);

void cadastrarFuncionariosModel(struct ListaFuncionarios *lista, struct Funcionarios *funcionario, int autoId);

void deletarFuncionariosModel(struct ListaFuncionarios *lista, struct ListaAgendamentos *listaAgendamentos, int id);

int verificarIDFuncionariosModel(struct ListaFuncionarios *lista, int id);

void atualizarFuncionariosModel(struct ListaFuncionarios *lista, int id, struct Funcionarios *funcionario);

void listarTodosFuncionariosModel(struct ListaFuncionarios *lista);

void listarFuncionariosModel(struct ListaFuncionarios *lista, int id);

void buscarFuncionarioPorOficinaModel(struct ListaFuncionarios *lista, int idOficina);

int verificarRelacaoFuncionarioComOficinaModel(struct ListaFuncionarios *listaFuncionarios,
                                 int idOficina, int idFuncionario);

#endif //MODELFUNCIONARIOS_H
