#ifndef MODELRELATORIOFUNCIONARIO.H
#define MODELRELATORIOFUNCIONARIO

#include "../../oficina/modelOficina.h"
#include "../../funcionarios/modelFuncionarios.h"

void imprimirRelatorioFuncionario(struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                              char *nome, int id);

void armazenarRelatorioFuncionario(struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                               char *nome, int id);

#endif //MODELRELATORIOFUNCIONARIO
