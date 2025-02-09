#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Includes dos .h dos relatorios
#include "./viewRelatorios.h"
#include "../../models/relatorios/clientes/modelRelatorioCliente.h"
#include "../../models/relatorios/oficinas/modelRelatorioOficina.h"
#include "../../models/relatorios/veiculos/modelRelatorioVeiculo.h"
#include "../../models/relatorios/funcionarios/modelRelatorioFuncionario.h"
#include "../../models/relatorios/servicos/modelRelatorioServico.h"
#include "../../models/relatorios/fornecedores/modelRelatorioFornecedores.h"
#include "../../models/relatorios/pecas/modelRelatorioPeca.h"
#include "../../models/relatorios/estoques/modelRelatorioEstoque.h"
#include "../../models/relatorios/produtividade/modelRelatorioProdutividade.h"
#include "../../models/relatorios/servicosRealizados/modelRelatorioServicosRealizados.h"
#include "../../models/relatorios/financeiro/modelRelatorioFinanceiro.h"

// Includes dos .h das tabelas
#include "../../models/oficina/modelOficina.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pecasNotas/modelPecasNotas.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"


// Gerenciamento de relatorios
void gerenciarRelatorios(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                         struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                         struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                         struct ListaPecas *listaPecas, struct ListaOrdensServico *listaOrdensServicos,
                         struct ListaAgendamentos *listaAgendamentos, struct ListaCaixas *listaCaixas,
                         struct ListaPagamentosCliente *listaPagamentosCliente,
                         struct ListaPagamentosFornecedor *listaPagamentosFornecedor, int opcaoArmazenamento) {
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
        if (listaAgendamentos->qtdAgendamentos == 0) {
            buscarDadosAgendamentosModel(listaAgendamentos, opcaoArmazenamento);
        }

        if (listaOrdensServicos->qtdOrdensServico == 0) {
            buscarDadosOrdensServicoModel(listaOrdensServicos, opcaoArmazenamento);
        }
        if (listaPagamentosFornecedor->qtdPagamentosFornecedor == 0) {
            buscarDadosPagamentosFornecedorModel(listaPagamentosFornecedor, opcaoArmazenamento);
        }
        if (listaPagamentosCliente->qtdPagamentosCliente == 0) {
            buscarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
        }

        if (listaPagamentosCliente->qtdPagamentosCliente == 0) {
            buscarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
        }

        if (listaPagamentosFornecedor->qtdPagamentosFornecedor == 0) {
            buscarDadosPagamentosFornecedorModel(listaPagamentosFornecedor, opcaoArmazenamento);
        }

        if (listaCaixas->qtdCaixas == 0) {
            buscarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
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
                filtroRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos);
                break;
            case 3:
                filtroRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServicos,
                              listaFuncionarios, listaVeiculos);
                break;
            case 4:
                filtroRelatorioProdutividade(listaOrdensServicos, listaAgendamentos, listaFuncionarios);
                break;
            case 5:
                filtroRelatorioFinanceiro(listaCaixas, listaOficinas, listaPagamentosCliente,
                                            listaPagamentosFornecedor, listaClientes, listaFornecedores);
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

                if (listaAgendamentos->qtdAgendamentos > 0) {
                    free(listaAgendamentos->listaAgendamentos);
                    listaAgendamentos->listaAgendamentos = NULL;
                    listaAgendamentos->qtdAgendamentos = 0;
                }

                if (listaOrdensServicos->qtdOrdensServico > 0) {
                    free(listaOrdensServicos->listaOrdensServico);
                    listaOrdensServicos->listaOrdensServico = NULL;
                    listaOrdensServicos->qtdOrdensServico = 0;
                }

                if (listaPagamentosFornecedor->qtdPagamentosFornecedor > 0) {
                    free(listaPagamentosFornecedor->listaPagamentosFornecedor);
                    listaPagamentosFornecedor->listaPagamentosFornecedor = NULL;
                    listaPagamentosFornecedor->qtdPagamentosFornecedor = 0;
                }

                if (listaPagamentosCliente->qtdPagamentosCliente > 0) {
                    free(listaPagamentosCliente->listaPagamentosCliente);
                    listaPagamentosCliente->listaPagamentosCliente = NULL;
                    listaPagamentosCliente->qtdPagamentosCliente = 0;
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

                if (listaCaixas->qtdCaixas > 0) {
                    free(listaCaixas->listaCaixas);
                    listaCaixas->listaCaixas = NULL;
                    listaCaixas->qtdCaixas = 0;
                }
                return;
            default: printf("Opção inválida!\n\n");
                break;
        }
    }
}


// Gerenciamento de cadastros basicos
void gerenciarCadastrosBasicos(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                               struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                               struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                               struct ListaPecas *listaPecas) {
    int opcaoSubmenus = 0;

    while (opcaoSubmenus != 8) {
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

// Filtro de cadastros basicos
void filtroRelatorioBasico(struct ListaOficinas *listaOficinas, struct ListaClientes *listaClientes,
                           struct ListaVeiculos *listaVeiculos, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaFornecedores *listaFornecedores,
                           struct ListaPecas *listaPecas, int tipoRelatorio) {
    int opcaoFiltro = 0, id = 0;
    char nome[255] = {0};

    while (opcaoFiltro != 3) {
        printf("\n=================\n"
            "|    FILTRAR    |\n"
            "=================\n"
            "|  1  | ID      |\n"
            "|  2  | Nome    |\n"
            "|  3  | Voltar  |\n"
            "=================\n"
            "Escolha uma forma de filtrar: ");
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
                        imprimirRelatorioPeca(listaPecas, listaFornecedores, listaOficinas, nome, id);
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
                        imprimirRelatorioPeca(listaPecas, listaFornecedores, listaOficinas, nome, id);
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

// Filtro do relatorio de produtividade
void filtroRelatorioProdutividade(struct ListaOrdensServico *listaOrdensServicos,
                                  struct ListaAgendamentos *listaAgendamentos,
                                  struct ListaFuncionarios *listaFuncionarios) {
    int opcaoFiltro = 0, funcionario = 0, servico = 0, diaInicio = 0, mesInicio = 0, anoInicio = 0, horaInicio = 0,
            minInicio = 0, diaFim = 0, mesFim = 0, anoFim = 0, horaFim = 0, minFim = 0;
    struct tm dataHoraInicial = {0};
    struct tm dataHoraFinal = {0};

    while (opcaoFiltro != 4) {
        printf("\n=============================\n"
            "|          FILTRAR          |\n"
            "=============================\n"
            "|  1  | Funcionário         |\n"
            "|  2  | Serviço             |\n"
            "|  3  | Intervalos de datas |\n"
            "|  4  | Voltar              |\n"
            "=============================\n"
            "Escolha uma forma de filtrar: ");
        scanf("%d", &opcaoFiltro);

        switch (opcaoFiltro) {
            case 1:
                // Inserindo id do funcionario
                    printf("Insira o ID do funcionário:");
            scanf("%d", &funcionario);
            break;
            case 2:
                // Inserindo id do serviço
                    printf("Insira o ID do serviço:");
            scanf("%d", &servico);
            break;
            case 3:

                // Recebendo data inicial
                    printf("Insira a data inicial (DD/MM/AAAA): ");
            setbuf(stdin, NULL);
            scanf("%d/%d/%d", &diaInicio, &mesInicio, &anoInicio);

            printf("Insira a hora inicial (HH:MM): ");
            setbuf(stdin, NULL);
            scanf("%d:%d", &horaInicio, &minInicio);

            dataHoraInicial.tm_mday = diaInicio;
            dataHoraInicial.tm_mon = mesInicio - 1;
            dataHoraInicial.tm_year = anoInicio - 1900;
            dataHoraInicial.tm_hour = horaInicio;
            dataHoraInicial.tm_min = minInicio;
            dataHoraInicial.tm_sec = 0;

            time_t tempoInicio = mktime(&dataHoraInicial);

            // Verificando conversão
            if (tempoInicio == -1) {
                printf("Erro ao converter a data e hora.\n");
                return;
            }

            // Recebendo data final
            printf("Insira a data final (DD/MM/AAAA): ");
            setbuf(stdin, NULL);
            scanf("%d/%d/%d", &diaFim, &mesFim, &anoFim);

            printf("Insira a hora final (HH:MM): ");
            setbuf(stdin, NULL);
            scanf("%d:%d", &horaFim, &minFim);

            dataHoraFinal.tm_mday = diaFim;
            dataHoraFinal.tm_mon = mesFim - 1;
            dataHoraFinal.tm_year = anoFim - 1900;
            dataHoraFinal.tm_hour = horaFim;
            dataHoraFinal.tm_min = minFim;
            dataHoraFinal.tm_sec = 0;

            time_t tempoFim = mktime(&dataHoraFinal);

            // Verificando conversão
            if (tempoFim == -1) {
                printf("Erro ao converter a data e hora.\n");
                return;
            }
            break;
            case 4:
                return;
            break;
            default:
                printf("Opção inválida!\n\n");
        }

        if (formaDeImprimir() == 1) {
            imprimirRelatorioProdutividade(listaOrdensServicos, listaAgendamentos, listaFuncionarios, funcionario,
                                           servico, dataHoraInicial, dataHoraFinal);
        } else {
            armazenarRelatorioProdutividade(listaOrdensServicos, listaAgendamentos, listaFuncionarios, funcionario,
                                            servico, dataHoraInicial, dataHoraFinal);
        }
    }
}


// Filtro de relatorio fincanceiro
void filtroRelatorioFinanceiro(struct ListaCaixas *listaCaixas, struct ListaOficinas *listaOficinas,
                               struct ListaPagamentosCliente *listaPagamentosCliente,
                               struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                               struct ListaClientes *listaClientes,
                               struct ListaFornecedores *listaFornecedores) {
    int opcaoFiltro = 0, tipoConta = 0, cliente = 0, fornecedor = 0;
    struct tm dataHoraInicial = {0};
    struct tm dataHoraFinal = {0};

    while (opcaoFiltro != 4) {
        printf("\n=============================\n"
            "|          FILTRAR          |\n"
            "=============================\n"
            "|  1  | Cliente             |\n"
            "|  2  | Fornecedor          |\n"
            "|  3  | Intervalo de Datas  |\n"
            "|  4  | Voltar              |\n"
            "=============================\n"
            "Escolha uma forma de filtrar: ");
        scanf("%d", &opcaoFiltro);


        switch (opcaoFiltro) {
            case 1:

                // Recebendo o id do cliente
                    printf("Insira o ID do cliente a pagar:");
            scanf("%d", &cliente);

            if (formaDeImprimir() == 1) {
                imprimirRelatorioFinanceiro(listaCaixas, listaOficinas, listaPagamentosCliente,
                                            listaPagamentosFornecedor, listaClientes, listaFornecedores, cliente,
                                            tipoConta, opcaoFiltro, dataHoraInicial, dataHoraFinal);
            } else {
                armazenarRelatorioFinanceiro(listaCaixas, listaOficinas, listaPagamentosCliente,
                                            listaPagamentosFornecedor, listaClientes, listaFornecedores, cliente,
                                            tipoConta, opcaoFiltro, dataHoraInicial, dataHoraFinal);
            }
            break;
            case 2:

                // Recebendo id do fornecedor
                    printf("Insira o ID do fornecedor a ser pago:");
            scanf("%d", &fornecedor);

            if (formaDeImprimir() == 1) {
                imprimirRelatorioFinanceiro(listaCaixas, listaOficinas, listaPagamentosCliente,
                                            listaPagamentosFornecedor, listaClientes, listaFornecedores, fornecedor,
                                            tipoConta, opcaoFiltro, dataHoraInicial, dataHoraFinal);
            } else {
                armazenarRelatorioFinanceiro(listaCaixas, listaOficinas, listaPagamentosCliente,
                                            listaPagamentosFornecedor, listaClientes, listaFornecedores, fornecedor,
                                            tipoConta, opcaoFiltro, dataHoraInicial, dataHoraFinal);
            }
            break;
            case 3:

                // Decidindo o tipo de conta do relatório
                    printf("\n============================\n"
                    "|       TIPO DE CONTA       |\n"
                    "=============================\n"
                    "|  1  | Contas a receber    |\n"
                    "|  2  | Contas a pagar      |\n"
                    "=============================\n"
                    "Escolha uma forma de filtrar: ");
            scanf("%d", &tipoConta);

            // Impedindo opções invalidas
            if (tipoConta != 1 && tipoConta != 2) {
                printf("Digite uma opção valida!\n\n");
                return;
            }

            // Inserindo a data inicial
            printf("Insira a data inicial (DD/MM/AAAA): ");
            setbuf(stdin, NULL);
            scanf("%d/%d/%d", &dataHoraInicial.tm_mday, &dataHoraInicial.tm_mon, &dataHoraInicial.tm_year);


            dataHoraInicial.tm_mon -= 1;
            dataHoraInicial.tm_year -= 1900;
            dataHoraInicial.tm_sec = 0;
            dataHoraInicial.tm_min = 0;
            dataHoraInicial.tm_hour = 0;

            time_t tempoInicio = mktime(&dataHoraInicial);

            // Verificando conversão
            if (tempoInicio == -1) {
                printf("Erro ao converter a data e hora.\n");
                return;
            }

            // Inserindo a data final
            printf("Insira a data final (DD/MM/AAAA): ");
            setbuf(stdin, NULL);
            scanf("%d/%d/%d", &dataHoraFinal.tm_mday, &dataHoraFinal.tm_mon, &dataHoraFinal.tm_year);


            dataHoraFinal.tm_mon -= 1;
            dataHoraFinal.tm_year -= 1900;
            dataHoraFinal.tm_sec = 0;
            dataHoraFinal.tm_sec = 0;
            dataHoraFinal.tm_min = 0;
            dataHoraFinal.tm_hour = 0;

            time_t tempoFim = mktime(&dataHoraFinal);


            // Verificando conversão
            if (tempoFim == -1) {
                printf("Erro ao converter a data e hora.\n");
                return;
            }

            if (formaDeImprimir() == 1) {
                imprimirRelatorioFinanceiro(listaCaixas, listaOficinas, listaPagamentosCliente,
                                            listaPagamentosFornecedor, listaClientes, listaFornecedores, fornecedor,
                                            tipoConta, opcaoFiltro, dataHoraInicial, dataHoraFinal);
            } else {
                armazenarRelatorioFinanceiro(listaCaixas, listaOficinas, listaPagamentosCliente,
                                            listaPagamentosFornecedor, listaClientes, listaFornecedores, fornecedor,
                                            tipoConta, opcaoFiltro, dataHoraInicial, dataHoraFinal);
            }
            break;
            case 4:
                return;
            default:
                printf("Opção inválida!\n\n");
            break;
        }
    }
}


void filtroRelatorioEstoque(struct ListaPecas *listaPecas, struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaOrdensServico *listaOrdensServico,
                              struct ListaFuncionarios *listaFuncionarios, struct ListaVeiculos *listaVeiculos) {
    int opcaoFiltro;

    while (opcaoFiltro != 6) {
        opcaoFiltro = 0;
        int idServico = 0, idCliente = 0, idFuncionario = 0;
        struct tm dataInicial = {0}, dataFinal = {0};

        printf("\n====================================\n"
            "|              FILTRAR             |\n"
            "====================================\n"
            "|  1  | Serviço                    |\n"
            "|  2  | Cliente                    |\n"
            "|  3  | Funcionário                |\n"
            "|  4  | Intervalo de datas         |\n"
            "|  5  | Produtos em estoque mínimo |\n"
            "|  6  | Voltar                     |\n"
            "====================================\n"
            "Escolha uma forma de filtrar: ");
        scanf("%d", &opcaoFiltro);

        switch (opcaoFiltro) {
            case 1:
                // Recebe o ID do serviço
                printf("Insira o ID do serviço:");
                setbuf(stdin, NULL);
                scanf(" %d", &idServico);

                if (formaDeImprimir() == 1) {
                    imprimirRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idServico);
                } else {
                    armazenarRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idServico);
                }

                break;
            case 2:
                // Recebe o ID do cliente
                printf("Insira o ID do cliente:");
                setbuf(stdin, NULL);
                scanf(" %d", &idCliente);

                if (formaDeImprimir() == 1) {
                    imprimirRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idCliente);
                } else {
                    armazenarRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idCliente);
                }

            break;
            case 3:
                // Recebe o ID do funcionário
                printf("Insira o ID do funcionário:");
                setbuf(stdin, NULL);
                scanf(" %d", &idFuncionario);

                if (formaDeImprimir() == 1) {
                    imprimirRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idFuncionario);
                } else {
                    armazenarRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idFuncionario);
                }

            break;
            case 4:

                // Recebe a data inicial
                printf("Insira a data inicial (DD/MM/AAAA): ");
                setbuf(stdin, NULL);
                scanf("%d/%d/%d", &dataInicial.tm_mday, &dataInicial.tm_mon, &dataInicial.tm_year);

                printf("Insira o horario inicial (HH:MM): ");
                setbuf(stdin, NULL);
                scanf("%d:%d", &dataInicial.tm_hour, &dataInicial.tm_min);

                dataInicial.tm_mon -= 1;
                dataInicial.tm_year -= 1900;
                dataFinal.tm_sec = 0;

                // Recebe a data final
                printf("Insira a data final (DD/MM/AAAA): ");
                setbuf(stdin, NULL);
                scanf("%d/%d/%d", &dataFinal.tm_mday, &dataFinal.tm_mon, &dataFinal.tm_year);

                printf("Insira o horario final (HH:MM): ");
                setbuf(stdin, NULL);
                scanf("%d:%d", &dataFinal.tm_hour, &dataFinal.tm_min);


                dataFinal.tm_mon -= 1;
                dataFinal.tm_year -= 1900;
                dataInicial.tm_sec = 0;


                if (formaDeImprimir() == 1) {
                    imprimirRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idServico);
                } else {
                    armazenarRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idServico);
                }

            break;
            case 5:

                if (formaDeImprimir() == 1) {
                    imprimirRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idServico);
                } else {
                    armazenarRelatorioEstoque(listaPecas, listaClientes, listaServicos, listaAgendamentos,
                              listaOrdensServico, listaFuncionarios, listaVeiculos,
                              dataInicial, dataFinal, opcaoFiltro, idServico);
                }


            break;
            case 6:
                return;
            default: printf("Opção inválida!\n\n");
                break;
        }
    }
}

void filtroRelatorioServicosRealizados(struct ListaClientes *listaClientes,
                              struct ListaServicos *listaServicos,
                              struct ListaOrdensServico *listaOrdensServicos,
                              struct ListaAgendamentos *listaAgendamentos,
                              struct ListaFuncionarios *listaFuncionarios,
                              struct ListaVeiculos *listaVeiculos) {
    int opcaoFiltro;

    while (opcaoFiltro != 5) {
        opcaoFiltro = 0;
        int idServico = 0, idCliente = 0, idFuncionario = 0;
        struct tm dataInicial = {0}, dataFinal = {0};

        printf("\n====================================\n"
            "|              FILTRAR             |\n"
            "====================================\n"
            "|  1  | Serviço                    |\n"
            "|  2  | Cliente                    |\n"
            "|  3  | Funcionário                |\n"
            "|  4  | Intervalo de datas         |\n"
            "|  5  | Voltar                     |\n"
            "====================================\n"
            "Escolha uma forma de filtrar: ");
        scanf("%d", &opcaoFiltro);

        switch (opcaoFiltro) {
            case 1:

                // Inserindo ID do serviço
                printf("Insira o ID do serviço:");
                setbuf(stdin, NULL);
                scanf(" %d", &idServico);

                if (formaDeImprimir() == 1) {
                    imprimirRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idServico);
                } else {
                    armazenarRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idServico);
                }

                break;
            case 2:

                // Inserindo ID do cliente
                printf("Insira o ID do cliente:");
                setbuf(stdin, NULL);
                scanf(" %d", &idCliente);

                if (formaDeImprimir() == 1) {
                    imprimirRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idCliente);
                } else {
                    armazenarRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idCliente);
                }

            break;
            case 3:

                // Inserindo ID do funcionario
                printf("Insira o ID do funcionário:");
                setbuf(stdin, NULL);
                scanf(" %d", &idFuncionario);

                if (formaDeImprimir() == 1) {
                    imprimirRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idFuncionario);
                } else {
                    armazenarRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idFuncionario);
                }

            break;
            case 4:

                // Inserindo data inicial
                printf("Insira a data inicial (DD/MM/AAAA):");
                setbuf(stdin, NULL);
                scanf("%d/%d/%d", &dataInicial.tm_mday, &dataInicial.tm_mon, &dataInicial.tm_year);

                printf("Insira o horario inicial (HH:MM): ");
                setbuf(stdin, NULL);
                scanf("%d:%d", &dataInicial.tm_min, &dataInicial.tm_sec);

                dataInicial.tm_mon -= 1;
                dataInicial.tm_year -= 1900;
                dataInicial.tm_sec = 0;


                // Inserindo data final
                printf("Insira a data final (DD/MM/AAAA):");
                setbuf(stdin, NULL);
                scanf("%d/%d/%d", &dataFinal.tm_mday, &dataFinal.tm_mon, &dataFinal.tm_year);

                printf("Insira o horario final (HH:MM): ");
                setbuf(stdin, NULL);
                scanf("%d:%d", &dataFinal.tm_min, &dataFinal.tm_sec);


                dataFinal.tm_mon -= 1;
                dataFinal.tm_year -= 1900;
                dataFinal.tm_sec = 0;


                if (formaDeImprimir() == 1) {
                    imprimirRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idFuncionario);
                } else {
                    armazenarRelatorioServicosRealizados(listaClientes, listaServicos, listaOrdensServicos, listaAgendamentos,
                                                        listaFuncionarios, listaVeiculos,
                                                        dataInicial, dataFinal, opcaoFiltro, idFuncionario);
                }

            break;
            case 5:

                return;
            default: printf("Opção inválida!\n\n");
                break;

        }
    }
}

// Recebendo forma de impressão dos dados
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
