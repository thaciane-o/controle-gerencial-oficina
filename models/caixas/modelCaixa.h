#ifndef MODELCAIXA_H
#define MODELCAIXA_H

struct Caixas {
    int id;
    float valorCaixa;
    int idOficina;
    int deletado;
};

struct ListaCaixas {
    int qtdCaixas;
    struct Caixas *listaCaixas;
};

void buscarDadosCaixasModel(struct ListaCaixas *lista, int opcaoArmazenamento);

void armazenarDadosCaixasModel(struct ListaCaixas *lista, int opcaoArmazenamento);

int alocarCaixasModel(struct ListaCaixas *lista);

int realocarCaixasModel(struct ListaCaixas *lista, int qtdAlocada);

void iniciarCaixasModel(struct ListaCaixas *lista, int idOficina);

void deletarCaixasModel(struct ListaCaixas *lista, int idOficina);

void mostrarCaixasModel(struct ListaCaixas *lista, int idOficina);

// Adiciona dinheiro a um caixa
void creditarDinheiroCaixaModel();

int debitarDinheiroCaixaModel(struct ListaCaixas *lista, int idOficina, float valorDebitado);

int getIdCaixaPorOficinaModel(struct ListaCaixas *lista, int idOficina);

int getIdOficinaPorCaixaModel(struct ListaCaixas *lista, int idCaixa);
#endif //MODELCAIXA_H