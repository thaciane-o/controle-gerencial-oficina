#ifndef VIEWPECAS_H
#define VIEWPECAS_H
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/oficina/modelOficina.h"

void gerenciarPeca(struct ListaPecas *listaPecas, struct ListaOficinas *listaOficinas, struct ListaFornecedores *listaFornecedores, struct ListaOrdensServico *listaOrdensServico, int opcaoArmazenamento);

void cadastrarPeca(struct ListaPecas *listaPecas, struct ListaOficinas *listaOficinas, struct ListaFornecedores *listaFornecedores);

void deletarPeca(struct ListaPecas *listaPecas, struct ListaOrdensServico *listaOrdensServico);

void atualizarPeca(struct ListaPecas *listaPecas, struct ListaOficinas *listaOficinas, struct ListaFornecedores *listaFornecedores);

void listarPeca(struct ListaPecas *listaPecas);

#endif //VIEWPECAS_H
