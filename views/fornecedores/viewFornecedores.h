#ifndef FORNECEDORES_H
#define FORNECEDORES_H
#include "../../models/fornecedores/modelFornecedores.h"

void gerenciarFornecedor(struct ListaFornecedores *lista, int opcaoArmazenamento);

void cadastrarFornecedor(struct ListaFornecedores *lista);

void deletarFornecedor(struct ListaFornecedores *lista);

void listarFornecedor(struct ListaFornecedores *lista);

void atualizarFornecedor(struct ListaFornecedores *lista);

#endif //FORNECEDORES_H
