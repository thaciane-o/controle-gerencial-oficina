#ifndef VIEWSERVICOS_H
#define VIEWSERVICOS_H
#include "../../models/servicos/modelServicos.h"
#include "../../models/oficina/modelOficina.h"

void gerenciarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas, int opcaoArmazenamento);

void cadastrarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas);

void deletarServico(struct ListaServicos *lista);

void listarServico(struct ListaServicos *lista);

void atualizarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas);


#endif //VIEWSERVICOS_H
