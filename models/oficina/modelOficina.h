#ifndef MODELOFICINA_H
#define MODELOFICINA_H
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/clientes/modelClientes.h"

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

void buscarDadosOficinaModel(struct ListaOficinas *lista, int opcaoArmazenamento);

void armazenarDadosOficinaModel(struct ListaOficinas *lista, int opcaoArmazenamento);

int alocarMemoriaOficinaModel(struct ListaOficinas *lista);

int realocarMemoriaOficinaModel(struct ListaOficinas *oficinas, int qtdAloca);

void cadastrarOficinaModel(struct ListaOficinas *lista, struct Oficinas *oficinaCadastrando);

void deletarOficinaModel(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios, struct ListaServicos *listaServicos, struct ListaClientes *listaClientes, int id);

void atualizarOficinaModel(struct ListaOficinas *lista, int id, struct Oficinas *oficinaAlterando);

int verificarIDOficinaModel(struct ListaOficinas *lista, int id);

void listarTodosOficinaModel(struct ListaOficinas *lista);

void listarOficinaModel(struct ListaOficinas *lista, int id);

#endif //MODELOFICINA_H
