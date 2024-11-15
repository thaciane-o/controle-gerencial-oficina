#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

void gerenciarFuncionario(struct ListaFuncionarios *lista, int opcaoArmazenamento);
void cadastrarFuncionario(struct ListaFuncionarios *lista);
void deletarFuncionario(struct ListaFuncionarios *lista);
void listarFuncionario(struct ListaFuncionarios *lista);
void atualizarFuncionario(struct ListaFuncionarios *lista);

#endif //FUNCIONARIOS_H