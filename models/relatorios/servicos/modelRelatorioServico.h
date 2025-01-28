#ifndef MODELRELATORIOSERVICO.H
#define MODELRELATORIOSERVICO

#include "../../oficina/modelOficina.h"
#include "../../servicos/modelServicos.h"

void imprimirRelatorioServico(struct ListaServicos *listaServicos, struct ListaOficinas *listaOficinas, char *nome,
                              int id);

void armazenarRelatorioServico(struct ListaServicos *listaServicos, struct ListaOficinas *listaOficinas, char *nome,
                               int id);

#endif //MODELRELATORIOSERVICO
