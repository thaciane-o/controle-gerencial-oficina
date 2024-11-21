#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/oficina/modelOficina.h"

void gerenciarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas, int opcaoArmazenamento);

void cadastrarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas);

void deletarFuncionario(struct ListaFuncionarios *lista);

void listarFuncionario(struct ListaFuncionarios *lista);

void atualizarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas);

#endif //FUNCIONARIOS_H
