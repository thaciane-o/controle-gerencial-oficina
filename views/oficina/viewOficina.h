#ifndef VIEWOFICINA_H
#define VIEWOFICINA_H
#include "../../models/oficina/modelOficina.h"
#include "../../models/funcionarios/modelFuncionarios.h"

void gerenciarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios, struct ListaClientes *listaClientes, int opcaoArmazenamento);

void cadastrarOficina(struct ListaOficinas *lista);

void deletarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios, struct ListaClientes *listaClientes);

void atualizarOficina(struct ListaOficinas *lista);

void listarOficina(struct ListaOficinas *lista);

#endif //VIEWOFICINA_H
