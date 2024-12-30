#ifndef VIEWOFICINA_H
#define VIEWOFICINA_H
#include "../../models/oficina/modelOficina.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/caixas/modelCaixa.h"

void gerenciarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios, struct ListaServicos *listaServicos, struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas, int opcaoArmazenamento);

void cadastrarOficina(struct ListaOficinas *lista, struct ListaCaixas *listaCaixas);

void deletarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios, struct ListaServicos *listaServicos, struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas);

void atualizarOficina(struct ListaOficinas *lista);

void listarOficina(struct ListaOficinas *lista);

#endif //VIEWOFICINA_H
