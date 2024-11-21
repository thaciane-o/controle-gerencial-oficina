#ifndef FORNECEDORES_H
#define FORNECEDORES_H
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/pecas/modelPecas.h"

void gerenciarFornecedor(struct ListaFornecedores *lista, struct ListaPecas *pecasRelacionadas, int opcaoArmazenamento);

void cadastrarFornecedor(struct ListaFornecedores *lista);

void deletarFornecedor(struct ListaFornecedores *lista, struct ListaPecas *pecasRelacionadas);

void listarFornecedor(struct ListaFornecedores *lista);

void atualizarFornecedor(struct ListaFornecedores *lista);

#endif //FORNECEDORES_H
