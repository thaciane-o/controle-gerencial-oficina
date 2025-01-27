#include <stdio.h>
#include <stdlib.h>

#include "./viewRelatorios.h"
#include "../../models/relatorios/modelRelatorioCliente.h"
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
                // Limpa ponteiros dos cadastros básicos
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

        switch (opcaoSubmenus) {
            case 1:

                break;
            case 2:
                filtroRelatorioBasico(listaClientes, listaOficinas, opcaoSubmenus);
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                return;
            default: printf("Opção inválida!\n\n");
                break;
        }
    }
}

void filtroRelatorioBasico(struct ListaClientes *listaClientes, struct ListaOficinas *listaOficinas,
                           int tipoRelatorio) {
    int id = 0, opcaoFiltro = 0;
    char nome[255];

    while (opcaoFiltro != 3) {
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

                        break;
                    case 2:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        }
                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    case 5:

                        break;
                    case 6:

                        break;
                    case 7:

                        break;
                    case 8:

                        return;
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

                        break;
                    case 2:
                        if (formaDeImprimir() == 1) {
                            imprimirRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        } else {
                            armazenarRelatorioCliente(listaClientes, listaOficinas, nome, id);
                        }
                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    case 5:

                        break;
                    case 6:

                        break;
                    case 7:

                        break;
                    case 8:

                        return;
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
