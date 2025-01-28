#include <stdio.h>
#include <stdlib.h>

#include "./viewRelatorios.h"
#include "../../models/relatorios/clientes/modelRelatorioCliente.h"
#include "../../models/relatorios/oficinas/modelRelatorioOficina.h"
#include "../../models/relatorios/veiculos/modelRelatorioVeiculo.h"
#include "../../models/relatorios/funcionarios/modelRelatorioFuncionario.h"
#include "../../models/relatorios/servicos/modelRelatorioServico.h"
#include "../../models/relatorios/fornecedores/modelRelatorioFornecedores.h"
#include "../../models/relatorios/pecas/modelRelatorioPeca.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/pecas/modelPecas.h"

void gerenciarRelatorios(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                         struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                         struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                         struct ListaPecas *listaPecas, int opcaoArmazenamento) {
    int opcaoSubmenus = 0;

    // Verifica tipo de armazenamento para buscar dados
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }

        if (listaClientes->qtdClientes == 0) {
            buscarDadosClientesModel(listaClientes, opcaoArmazenamento);
        }

        if (listaVeiculos->qtdVeiculos == 0) {
            buscarDadosVeiculosModel(listaVeiculos, opcaoArmazenamento);
        }

        if (listaFuncionarios->qtdFuncionarios == 0) {
            buscarDadosFuncionariosModel(listaFuncionarios, opcaoArmazenamento);
        }

        if (listaServicos->qtdServicos == 0) {
            buscarDadosServicoModel(listaServicos, opcaoArmazenamento);
        }

        if (listaFornecedores->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(listaFornecedores, opcaoArmazenamento);
        }

        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }
    }

    while (opcaoSubmenus != 6) {
        printf("\n======================================\n"
            "|         MENU DE RELATÓRIOS         |\n"
            "======================================\n"
            "|  1  | Cadastros básicos            |\n"
            "|  2  | Serviços realizados          |\n"
            "|  3  | Estoque                      |\n"
            "|  4  | Produtividade                |\n"
            "|  5  | Financeiro                   |\n"
            "|  6  | Voltar                       |\n"
            "======================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                gerenciarCadastrosBasicos(listaOficinas, listaClientes, listaVeiculos, listaFuncionarios, listaServicos,
                                          listaFornecedores, listaPecas);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                // Limpa os ponteiros
                if (listaOficinas->qtdOficinas > 0) {
                    free(listaOficinas->listaOficinas);
                    listaOficinas->listaOficinas = NULL;
                    listaOficinas->qtdOficinas = 0;
                }

                if (listaClientes->qtdClientes > 0) {
                    free(listaClientes->listaClientes);
                    listaClientes->listaClientes = NULL;
                    listaClientes->qtdClientes = 0;
                }

                if (listaVeiculos->qtdVeiculos > 0) {
                    free(listaVeiculos->listaVeiculos);
                    listaVeiculos->listaVeiculos = NULL;
                    listaVeiculos->qtdVeiculos = 0;
                }

                if (listaFuncionarios->qtdFuncionarios > 0) {
                    free(listaFuncionarios->listaFuncionarios);
                    listaFuncionarios->listaFuncionarios = NULL;
                    listaFuncionarios->qtdFuncionarios = 0;
                }

                if (listaServicos->qtdServicos > 0) {
                    free(listaServicos->listaServicos);
                    listaServicos->listaServicos = NULL;
                    listaServicos->qtdServicos = 0;
                }

                if (listaFornecedores->qtdFornecedores > 0) {
                    free(listaFornecedores->listaFornecedores);
                    listaFornecedores->listaFornecedores = NULL;
                    listaFornecedores->qtdFornecedores = 0;
                }

                if (listaPecas->qtdPecas > 0) {
                    free(listaPecas->listaPecas);
                    listaPecas->listaPecas = NULL;
                    listaPecas->qtdPecas = 0;
                }
                return;
            default: printf("Opção inválida!\n\n");
                break;
        }
    }
}

void gerenciarCadastrosBasicos(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                               struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                               struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                               struct ListaPecas *listaPecas) {
    int opcaoSubmenus = 0;

    while (opcaoSubmenus != 6) {
        printf("\n======================================\n"
            "|    RELATÓRIO DE CADASTRO BÁSICO    |\n"
            "======================================\n"
            "|  1  | Oficina                      |\n"
            "|  2  | Clientes                     |\n"
            "|  3  | Veículos                     |\n"
            "|  4  | Funcionários                 |\n"
            "|  5  | Serviços                     |\n"
            "|  6  | Fornecedores                 |\n"
            "|  7  | Peças                        |\n"
            "|  8  | Voltar                       |\n"
            "======================================\n"
            "Escolha uma opção para imprimir o relatório: ");
        scanf("%d", &opcaoSubmenus);

        if (opcaoSubmenus == 8) {
            return;
        }

        filtroRelatorioBasico(listaOficinas, listaClientes, listaVeiculos, listaFuncionarios, listaServicos,
                              listaFornecedores, listaPecas, opcaoSubmenus);
    }
}

void filtroRelatorioBasico(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                           struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                           struct ListaPecas *listaPecas, int tipoRelatorio) {
    int opcaoFiltro = 0;

    while (opcaoFiltro != 3) {
        int id = 0;
        char nome[255] = {0};

        printf("\n=================\n"
            "|    FILTRAR    |\n"
            "=================\n"
            "|  1  | ID      |\n"
            "|  2  | Nome    |\n"
            "|  3  | Voltar  |\n"
            "=================\n"
            "Escolha uma forma de filtar: ");
        scanf("%d", &opcaoFiltro);

        switch (opcaoFiltro) {
            case 1:
                printf("Insira o ID:");
                scanf("%d", &id);

                switch (tipoRelatorio) {
                    case 1:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioOficina(listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioOficina(listaOficinas, nome, id);
                        }
                        break;
                    case 2:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        }
                        break;
                    case 3:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioVeiculo(listaVeiculos, listaClientes, nome, id);
                        } else {
                            armazenarRelatorioVeiculo(listaVeiculos, listaClientes, nome, id);
                        }
                        break;
                    case 4:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioFuncionario(listaFuncionarios, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioFuncionario(listaFuncionarios, listaOficinas, nome, id);
                        }
                        break;
                    case 5:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioServico(listaServicos, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioServico(listaServicos, listaOficinas, nome, id);
                        }
                        break;
                    case 6:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioFornecedor(listaFornecedores, nome, id);
                        } else {
                            armazenarRelatorioFornecedor(listaFornecedores, nome, id);
                        }
                        break;
                    case 7:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioPecas(listaPecas, listaFornecedores, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioPeca(listaPecas, listaFornecedores, listaOficinas, nome, id);
                        }
                        break;
                    default: printf("Opção inválida!\n\n");
                        break;
                }

                break;
            case 2:
                printf("Insira o nome:");
                setbuf(stdin, NULL);
                scanf(" %[^\n]s", nome);

                switch (tipoRelatorio) {
                    case 1:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioOficina(listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioOficina(listaOficinas, nome, id);
                        }
                        break;
                    case 2:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        }
                        break;
                    case 3:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioVeiculo(listaVeiculos, listaClientes, nome, id);
                        } else {
                            armazenarRelatorioVeiculo(listaVeiculos, listaClientes, nome, id);
                        }
                        break;
                    case 4:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioFuncionario(listaFuncionarios, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioFuncionario(listaFuncionarios, listaOficinas, nome, id);
                        }
                        break;
                    case 5:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioServico(listaServicos, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioServico(listaServicos, listaOficinas, nome, id);
                        }
                        break;
                    case 6:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioFornecedor(listaFornecedores, nome, id);
                        } else {
                            armazenarRelatorioFornecedor(listaFornecedores, nome, id);
                        }
                        break;
                    case 7:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioPecas(listaPecas, listaFornecedores, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioPeca(listaPecas, listaFornecedores, listaOficinas, nome, id);
                        }
                        break;
                    default: printf("Opção inválida!\n\n");
                        break;
                }
                break;
            case 3:
                return;
            default: printf("Opção inválida!\n\n");
                break;
        }
    }
}

int formaDeImprimir() {
    int opcaoImprime = 0;

    printf("\n===================================\n"
        "|        FORMA DE IMPRIMIR        |\n"
        "===================================\n"
        "| 1 | Tela                        |\n"
        "| 2 | Arquivo                     |\n"
        "===================================\n"
        "Como deseja imprimir?  ");
    scanf("%d", &opcaoImprime);

    return opcaoImprime;
}
