#ifndef VIEWOFICINA_H
#define VIEWOFICINA_H
#include "../../models/oficina/modelOficina.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"

void gerenciarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios,
                      struct ListaServicos *listaServicos, struct ListaClientes *listaClientes,
                      struct ListaCaixas *listaCaixas, struct ListaPecas *listaPecas,
                      struct ListaPagamentosCliente *listaPagamentosCliente,
                      struct ListaPagamentosFornecedor *listaPagamentosFornecedor, int opcaoArmazenamento);

void cadastrarOficina(struct ListaOficinas *lista, struct ListaCaixas *listaCaixas);

void deletarOficina(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios,
                    struct ListaServicos *listaServicos, struct ListaClientes *listaClientes,
                    struct ListaCaixas *listaCaixas, struct ListaPecas *listaPecas,
                    struct ListaPagamentosCliente *listaPagamentosCliente,
                    struct ListaPagamentosFornecedor *listaPagamentosFornecedor);

void atualizarOficina(struct ListaOficinas *lista);

void listarOficina(struct ListaOficinas *lista);

#endif //VIEWOFICINA_H
