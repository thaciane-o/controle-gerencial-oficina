#include "viewExportacaoImportacao.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/pecasNotas/modelPecasNotas.h"
#include "../../models/exportacaoImportacao/modelExportacaoImportacao.h"

// Tela de escolha de importação e exportação
void gerenciarExportacaoImportacao(struct ListaClientes *listaClientes,
                                   struct ListaVeiculos *listaVeiculos,
                                   struct ListaOficinas *listaOficinas,
                                   struct ListaPecas *listaPecas,
                                   struct ListaFornecedores *listaFornecedores,
                                   struct ListaServicos *listaServicos,
                                   struct ListaFuncionarios *listaFuncionarios,
                                   struct ListaCaixas *listaCaixas,
                                   struct ListaPagamentosCliente *listaPagamentosCliente,
                                   struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                                   struct ListaAgendamentos *listaAgendamentos,
                                   struct ListaOrdensServico *listaOrdensServico,
                                   struct ListaNotasFiscais *listaNotasFiscais,
                                   struct ListaPecasNotas *listaPecasNotas,
                                   int opcaoArmazenamento) {
    // Abre os arquivos de todos os dados
    if (opcaoArmazenamento != 3) {
        if (listaClientes->qtdClientes == 0) {
            buscarDadosClientesModel(listaClientes, opcaoArmazenamento);
        }
        if (listaVeiculos->qtdVeiculos == 0) {
            buscarDadosVeiculosModel(listaVeiculos, opcaoArmazenamento);
        }
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }
        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }
        if (listaFornecedores->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(listaFornecedores, opcaoArmazenamento);
        }
        if (listaServicos->qtdServicos == 0) {
            buscarDadosServicoModel(listaServicos, opcaoArmazenamento);
        }
        if (listaFuncionarios->qtdFuncionarios == 0) {
            buscarDadosFuncionariosModel(listaFuncionarios, opcaoArmazenamento);
        }
        if (listaCaixas->qtdCaixas == 0) {
            buscarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
        }
        if (listaPagamentosCliente->qtdPagamentosCliente == 0) {
            buscarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
        }
        if (listaPagamentosFornecedor->qtdPagamentosFornecedor == 0) {
            buscarDadosPagamentosFornecedorModel(listaPagamentosFornecedor, opcaoArmazenamento);
        }
        if (listaAgendamentos->qtdAgendamentos == 0) {
            buscarDadosAgendamentosModel(listaAgendamentos, opcaoArmazenamento);
        }
        if (listaOrdensServico->qtdOrdensServico == 0) {
            buscarDadosOrdensServicoModel(listaOrdensServico, opcaoArmazenamento);
        }
        if (listaNotasFiscais->qtdNotas == 0) {
            buscarDadosNotasFiscaisModel(listaNotasFiscais, opcaoArmazenamento);
        }
        if (listaPecasNotas->qtdPecasNotas == 0) {
            buscarDadosPecaNotaModel(listaPecasNotas, opcaoArmazenamento);
        }
    }

    int opcaoSubmenus;
    do {
        printf("\n======================================\n"
            "|  IMPORTAÇÃO E EXPORTAÇÃO DE DADOS  |\n"
            "======================================\n"
            "|  1  | Importar dados               |\n"
            "|  2  | Exportar dados               |\n"
            "|  3  | Voltar                       |\n"
            "======================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                break;
            case 2:
                gerenciarExportacao(listaClientes,
                                    listaVeiculos,
                                    listaOficinas,
                                    listaPecas,
                                    listaFornecedores,
                                    listaServicos,
                                    listaFuncionarios,
                                    listaCaixas,
                                    listaPagamentosCliente,
                                    listaPagamentosFornecedor,
                                    listaAgendamentos,
                                    listaOrdensServico,
                                    listaNotasFiscais,
                                    listaPecasNotas);
                break;
            case 3:
                // Desaloca os ponteiros, caso armazenamento em arquivos.
                if (opcaoArmazenamento != 3) {
                    if (listaClientes->qtdClientes > 0) {
                        free(listaClientes->listaClientes);
                        listaClientes->listaClientes = NULL;
                        listaClientes->qtdClientes = 0;
                    }
                    if (listaVeiculos->qtdVeiculos > 0) {
                        free(listaVeiculos->listaVeiculos);
                        listaVeiculos->listaVeiculos = NULL;
                        listaVeiculos->qtdVeiculos > 0;
                    }
                    if (listaOficinas->qtdOficinas > 0) {
                        free(listaOficinas->listaOficinas);
                        listaOficinas->listaOficinas = NULL;
                        listaOficinas->qtdOficinas = 0;
                    }
                    if (listaPecas->qtdPecas > 0) {
                        free(listaPecas->listaPecas);
                        listaPecas->listaPecas = NULL;
                        listaPecas->qtdPecas = 0;
                    }
                    if (listaFornecedores->qtdFornecedores > 0) {
                        free(listaFornecedores->listaFornecedores);
                        listaFornecedores->listaFornecedores = NULL;
                        listaFornecedores->qtdFornecedores = 0;
                    }
                    if (listaServicos->qtdServicos > 0) {
                        free(listaServicos->listaServicos);
                        listaServicos->listaServicos = NULL;
                        listaServicos->qtdServicos = 0;
                    }
                    if (listaFuncionarios->qtdFuncionarios > 0) {
                        free(listaFuncionarios->listaFuncionarios);
                        listaFuncionarios->listaFuncionarios = NULL;
                        listaFuncionarios->qtdFuncionarios = 0;
                    }
                    if (listaCaixas->qtdCaixas > 0) {
                        free(listaCaixas->listaCaixas);
                        listaCaixas->listaCaixas = NULL;
                        listaCaixas->qtdCaixas = 0;
                    }
                    if (listaPagamentosCliente->qtdPagamentosCliente > 0) {
                        free(listaPagamentosCliente->listaPagamentosCliente);
                        listaPagamentosCliente->listaPagamentosCliente = NULL;
                        listaPagamentosCliente->qtdPagamentosCliente = 0;
                    }
                    if (listaPagamentosFornecedor->qtdPagamentosFornecedor > 0) {
                        free(listaPagamentosFornecedor->listaPagamentosFornecedor);
                        listaPagamentosFornecedor->listaPagamentosFornecedor = NULL;
                        listaPagamentosFornecedor->qtdPagamentosFornecedor = 0;
                    }
                    if (listaAgendamentos->qtdAgendamentos > 0) {
                        free(listaAgendamentos->listaAgendamentos);
                        listaAgendamentos->listaAgendamentos = NULL;
                        listaAgendamentos->qtdAgendamentos = 0;
                    }
                    if (listaOrdensServico->qtdOrdensServico > 0) {
                        free(listaOrdensServico->listaOrdensServico);
                        listaOrdensServico->listaOrdensServico = NULL;
                        listaOrdensServico->qtdOrdensServico = 0;
                    }
                    if (listaNotasFiscais->qtdNotas > 0) {
                        free(listaNotasFiscais->listaNotas);
                        listaNotasFiscais->listaNotas = NULL;
                        listaNotasFiscais->qtdNotas = 0;
                    }
                    if (listaPecasNotas->listaPecasNotas > 0) {
                        free(listaPecasNotas->listaPecasNotas);
                        listaPecasNotas->listaPecasNotas = NULL;
                        listaPecasNotas->listaPecasNotas = 0;
                    }
                }
                return;
                break;
            default:
                printf("Opção inválida.\n\n");
                break;
        }
    } while (opcaoSubmenus != 3);
}

void gerenciarImportacao() {
}

void gerenciarExportacao(struct ListaClientes *listaClientes,
                         struct ListaVeiculos *listaVeiculos,
                         struct ListaOficinas *listaOficinas,
                         struct ListaPecas *listaPecas,
                         struct ListaFornecedores *listaFornecedores,
                         struct ListaServicos *listaServicos,
                         struct ListaFuncionarios *listaFuncionarios,
                         struct ListaCaixas *listaCaixas,
                         struct ListaPagamentosCliente *listaPagamentosCliente,
                         struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                         struct ListaAgendamentos *listaAgendamentos,
                         struct ListaOrdensServico *listaOrdensServico,
                         struct ListaNotasFiscais *listaNotasFiscais,
                         struct ListaPecasNotas *listaPecasNotas) {
    int opcaoMenu = 0;
    int qtdSelecionados = 0;
    int exportar[14] = {0};
    char sel[2][2] = {" ", "X"};

    do {
        printf("\n\n==========================================\n"
               "|  Escolha as tabelas para a exportação  |\n"
               "==========================================\n"
               "|  1 | Clientes                      (%s) |\n"
               "|  2 | Veiculos                      (%s) |\n"
               "|  3 | Oficinas                      (%s) |\n"
               "|  4 | Pecas                         (%s) |\n"
               "|  5 | Fornecedores                  (%s) |\n"
               "|  6 | Servicos                      (%s) |\n"
               "|  7 | Funcionarios                  (%s) |\n"
               "|  8 | Caixas                        (%s) |\n"
               "|  9 | Pagamentos de cliente         (%s) |\n"
               "| 10 | Pagamentos de fornecedores    (%s) |\n"
               "| 11 | Agendamentos                  (%s) |\n"
               "| 12 | Ordens de serviços            (%s) |\n"
               "| 13 | Notas fiscais                 (%s) |\n"
               "| 14 | Peças em notas fiscais        (%s) |\n"
               "| 15 | Selecionar todas as tabelas       |\n"
               "|  0 | Confirmar                         |\n"
               "==========================================\n",
               sel[exportar[0]], sel[exportar[1]], sel[exportar[2]],
               sel[exportar[3]], sel[exportar[4]], sel[exportar[5]],
               sel[exportar[6]], sel[exportar[7]], sel[exportar[8]],
               sel[exportar[9]], sel[exportar[10]], sel[exportar[11]],
               sel[exportar[12]], sel[exportar[13]]);
        printf("Insira a opção desejada: ");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {
            case 0:
                if (qtdSelecionados > 0) {
                    exportaDadosModel(listaClientes,
                                      listaVeiculos,
                                      listaOficinas,
                                      listaPecas,
                                      listaFornecedores,
                                      listaServicos,
                                      listaFuncionarios,
                                      listaCaixas,
                                      listaPagamentosCliente,
                                      listaPagamentosFornecedor,
                                      listaAgendamentos,
                                      listaOrdensServico,
                                      listaNotasFiscais,
                                      listaPecasNotas,
                                      exportar);
                } else {
                    printf("Nenhuma tabela foi selecionada para exportação.\n\n");
                }
                break;
            case 15:
                for (int i = 0; i < 14; i++) {
                    exportar[i] = 1;
                    qtdSelecionados++;
                }
                break;
            default:
                if (opcaoMenu > 0 && opcaoMenu < 15) {
                    exportar[opcaoMenu - 1] = 1;
                    qtdSelecionados++;
                } else {
                    printf("Opção inválida.\n\n");
                }
                break;
        }
    } while (opcaoMenu != 0);
}
