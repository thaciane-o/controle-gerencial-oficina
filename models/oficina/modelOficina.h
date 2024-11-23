#ifndef MODELOFICINA_H
#define MODELOFICINA_H
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"


struct Oficinas {
    int id;
    char nome[255];
    char endereco[255];
    char ddd[3];
    char telefone[11];
    char email[255];
    float porcentagemLucro;
    int deletado;
};

struct ListaOficinas {
    int qtdOficinas;
    struct Oficinas *listaOficinas;
};

// Controles de armazenamento
void buscarDadosOficinaModel(struct ListaOficinas *lista, int opcaoArmazenamento);

void armazenarDadosOficinaModel(struct ListaOficinas *lista, int opcaoArmazenamento);

// Controles de alocação de memória
void alocarMemoriaOficinaModel(struct ListaOficinas *lista);

void realocarMemoriaOficinaModel(struct ListaOficinas *oficinas, int qtdAloca);

// Controles de CRUD
void cadastrarOficinaModel(struct ListaOficinas *lista, struct Oficinas *oficinaCadastrando);

void deletarOficinaModel(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios, struct ListaServicos *listaServicos, int id);

void atualizarOficinaModel(struct ListaOficinas *lista, int id, struct Oficinas *oficinaAlterando);

int verificarIDOficinaModel(struct ListaOficinas *lista, int id);

void listarTodosOficinaModel(struct ListaOficinas *lista);

void buscarIdOficinaModel(struct ListaOficinas *lista, int id);

#endif //MODELOFICINA_H
