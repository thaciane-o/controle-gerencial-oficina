#ifndef MODELORDENSSERVICOS_H
#define MODELORDENSSERVICOS_H
#include "../../models/pecas/modelPecas.h"
#include "../../models/agendamentos/modelAgendamentos.h"

struct OrdensServico {
    char descricao[255];
    int idPecas;
    int idAgendamentos;
    float valorTotal;
    int deletado;
};

struct ListaOrdensServico {
    int qtdOrdensServico;
    struct OrdensServico *listaOrdensServico;
};

void buscarDadosOrdensServicoModel(struct ListaOrdensServico *lista, int opcaoArmazenamento);

void armazenarDadosOrdensServicoModel(struct ListaOrdensServico *lista, int opcaoArmazenamento);

int alocarOrdensServicoModel(struct ListaOrdensServico *lista);

int realocarOrdensServicoModel(struct ListaOrdensServico *lista, int qtdAlocada);

void cadastrarOrdensServicoModel(struct ListaOrdensServico *lista, struct OrdensServico *ordensServico);

void atualizarOrdensServicoModel(struct ListaOrdensServico *lista, int id, struct OrdensServico *ordensServico);

void listarOrdensServicoModel(struct ListaOrdensServico *lista, int id);

void deletarOrdensServicoModel(struct ListaOrdensServico *lista, int id);

#endif //MODELORDENSSERVICOS_H
