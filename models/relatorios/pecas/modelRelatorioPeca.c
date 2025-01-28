#ifndef MODELRELATORIOPECA.H
#define MODELRELATORIOPECA

#include "../../oficina/modelOficina.h"
#include "../../fornecedores/modelFornecedores.h"
#include "../../pecas/modelPecas.h"

void imprimirRelatorioPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                           struct ListaOficinas *listaOficinas, char *nome, int id);

void armazenarRelatorioPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                           struct ListaOficinas *listaOficinas, char *nome, int id);

#endif //MODELRELATORIOPECA
