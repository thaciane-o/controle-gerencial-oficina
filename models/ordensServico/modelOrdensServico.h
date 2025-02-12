#ifndef MODELORDENSSERVICOS_H
#define MODELORDENSSERVICOS_H
#include "../../models/pecas/modelPecas.h"
#include "../../models/agendamentos/modelAgendamentos.h"

struct OrdensServico {
    char descricao[255];
    int idPecas;
    int qtdPecas;
    int idAgendamento;
    float valorTotal;
    float tempoGasto;
    char datahoraFinal[17];
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

void cadastrarOrdensServicoModel(struct ListaOrdensServico *lista, struct OrdensServico *ordensServico, int autoId);

void listarOrdensServicoModel(struct ListaOrdensServico *lista, int id);

void deletarOrdensServicoModel(struct ListaOrdensServico *lista, int id);

void finalizarOrdemServicoModel(struct ListaOrdensServico *lista, struct ListaAgendamentos *listaAgendamentos,
                                int idAgendamento, int idServico);

#endif //MODELORDENSSERVICOS_H
