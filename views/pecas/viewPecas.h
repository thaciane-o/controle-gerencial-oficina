
#ifndef VIEWPECAS_H
#define VIEWPECAS_H

#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"

void gerenciarPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores, int opcaoArmazenamento);
void cadastrarPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores);
void deletarPeca(struct ListaPecas *listaPecas);
void atualizarPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores);
void listarPeca(struct ListaPecas *listaPecas);

#endif //VIEWPECAS_H
