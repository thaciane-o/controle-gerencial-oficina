#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/clientes/modelClientes.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pecasNotas/modelPecasNotas.h"
#include "viewAgendamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Menu de funcionalidades de agentamentos
void gerenciarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas,
                           struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                           struct ListaPagamentosCliente *listaPagamentosCliente, int opcaoArmazenamento) {
    int opcaoSubmenus;
    // Verifica tipo de armazenamento para buscar dados
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdAgendamentos == 0) {
            buscarDadosAgendamentosModel(lista, opcaoArmazenamento);
        }

        // Busca os dados em arquivos das tabelas relacionadas
        if (listaVeiculos->qtdVeiculos == 0) {
            buscarDadosVeiculosModel(listaVeiculos, opcaoArmazenamento);
        }
        if (listaFuncionarios->qtdFuncionarios == 0) {
            buscarDadosFuncionariosModel(listaFuncionarios, opcaoArmazenamento);
        }
        if (listaServicos->qtdServicos == 0) {
            buscarDadosServicoModel(listaServicos, opcaoArmazenamento);
        }
        if (listaOrdensServico->qtdOrdensServico == 0) {
            buscarDadosOrdensServicoModel(listaOrdensServico, opcaoArmazenamento);
        }
        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }
        if (listaClientes->qtdClientes == 0) {
            buscarDadosClientesModel(listaClientes, opcaoArmazenamento);
        }
        if (listaCaixas->qtdCaixas == 0) {
            buscarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
        }
        if (listaPagamentosCliente->qtdPagamentosCliente == 0) {
            buscarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
        }
    }

    // Chama uma função para verificar os estoques em necessidade
    verificarEstoqueMinimo(listaPecas);
    do {
        printf("\n==================================\n"
            "|      MENU DE AGENDAMENTOS      |\n"
            "==================================\n"
            "|  1  | Agendar                  |\n"
            "|  2  | Cancelar agendamento     |\n"
            "|  3  | Listar agendamento       |\n"
            "|  4  | Finalizar serviço        |\n"
            "|  5  | Voltar                   |\n"
            "==================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarAgendamentos(lista, listaFuncionarios, listaServicos, listaVeiculos, listaOrdensServico,
                                      listaPecas, listaClientes, listaCaixas, listaPagamentosCliente);
                break;
            case 2:
                deletarAgendamento(lista, listaOrdensServico);
                break;
            case 3:
                listarAgendamentos(lista, listaOrdensServico);
                break;
            case 4:
                finalizarOrdemServico(lista, listaOrdensServico);
                break;
            case 5:
                // Armazena dados no tipo de armazenamento desejado e limpa ponteiros
                if (opcaoArmazenamento != 3) {
                    // Armazena dados alterados (Os ponteiros também são limpos)
                    if (lista->qtdAgendamentos > 0) {
                        armazenarDadosAgendamentosModel(lista, opcaoArmazenamento);
                    }
                    if (listaCaixas->qtdCaixas > 0) {
                        armazenarDadosCaixasModel(listaCaixas, opcaoArmazenamento);
                    }
                    if (listaPagamentosCliente->qtdPagamentosCliente > 0) {
                        armazenarDadosPagamentosClienteModel(listaPagamentosCliente, opcaoArmazenamento);
                    }
                    if (listaPecas->qtdPecas > 0) {
                        armazenarDadosPecaModel(listaPecas, opcaoArmazenamento);
                    }
                    if (listaOrdensServico->qtdOrdensServico > 0) {
                        armazenarDadosOrdensServicoModel(listaOrdensServico, opcaoArmazenamento);
                    }

                    // Limpa ponteiros restantes
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
                    if (listaVeiculos->qtdVeiculos > 0) {
                        free(listaVeiculos->listaVeiculos);
                        listaVeiculos->listaVeiculos = NULL;
                        listaVeiculos->qtdVeiculos = 0;
                    }
                    if (listaClientes->qtdClientes > 0) {
                        free(listaClientes->listaClientes);
                        listaClientes->listaClientes = NULL;
                        listaClientes->qtdClientes = 0;
                    }
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 5);
}

// Formulário de cadastro de agendamentos
void cadastrarAgendamentos(struct ListaAgendamentos *lista, struct ListaFuncionarios *listaFuncionarios,
                           struct ListaServicos *listaServicos, struct ListaVeiculos *listaVeiculos,
                           struct ListaOrdensServico *listaOrdensServico, struct ListaPecas *listaPecas,
                           struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                           struct ListaPagamentosCliente *listaPagamentosCliente) {
    struct Agendamentos agendamento;
    struct OrdensServico ordensServico;
    int idFuncionario, idVeiculo, qtdServicos = 0, idInputServico, qtdPecas = 0, idInputPecas, dia, mes, ano, hora,
            minuto;
    int *idServicos = malloc(sizeof(int));
    int *idPecas = malloc(sizeof(int));
    int *idPecaDoServico = malloc(sizeof(int));
    int *qtdPecasRequisitadas = malloc(sizeof(int));
    struct PagamentosCliente pagamento;
    pagamento.valor = 0;
    struct tm dataHora = {0};
    float valorAgendamento = 0;

    printf("\n======================\n"
        "|     AGENDAMENTO    |\n"
        "======================\n");

    do {
        // Agendando 1 ou mais serviços
        if (qtdServicos > 1) {
            idServicos = realloc(idServicos, qtdServicos * sizeof(int));
        }
        qtdServicos++;
        printf("Insira o ID do serviço que será agendado (0 para finalizar): ");
        setbuf(stdin, NULL);
        scanf("%d", &idInputServico);

        // Verificando existência do item relacionado
        if (idInputServico != 0) {
            idServicos[qtdServicos - 1] = idInputServico;
            verificarIDServicoModel(listaServicos, idServicos[qtdServicos - 1]);

            valorAgendamento += getValorServicoPorIdModel(listaServicos, idInputServico);

            do {
                // Inserindo 1 ou mais peças por serviço
                if (qtdPecas > 1) {
                    idPecas = realloc(idPecas, qtdPecas * sizeof(int));
                    idPecaDoServico = realloc(idPecaDoServico, qtdPecas * sizeof(int));
                    qtdPecasRequisitadas = realloc(qtdPecasRequisitadas, qtdPecas * sizeof(int));
                }
                qtdPecas++;

                printf("Insira o ID da peça que será necessária para realizar esse serviço (0 para finalizar): ");
                setbuf(stdin, NULL);
                scanf("%d", &idInputPecas);

                // Verificando existência do item relacionado
                if (idInputPecas != 0) {
                    idPecas[qtdPecas - 1] = idInputPecas;
                    verificarIDPecaModel(listaPecas, idPecas[qtdPecas - 1]);
                    idPecaDoServico[qtdPecas - 1] = idInputServico;
                } else {
                    qtdPecas--;
                }

                if (idInputPecas != 0) {
                    printf("Insira a quantidade necessária dessa peça: ");
                    setbuf(stdin, NULL);
                    scanf("%d", &qtdPecasRequisitadas[qtdPecas - 1]);
                    // Verificando se há peças suficientes no estoque
                    int qtdPecasEstoque = getQtdEstoquePecaModel(listaPecas, idInputPecas);
                    int qtdPecasEstoqueMin = getQtdEstoqueMinimoPecaModel(listaPecas, idInputPecas);
                    if (qtdPecasEstoque >= qtdPecasEstoqueMin && qtdPecasEstoque != -1 && qtdPecasEstoqueMin != -1) {
                        valorAgendamento += getValorPecaPorIdModel(listaPecas, idInputPecas) * qtdPecasRequisitadas[
                            qtdPecas - 1];
                    } else {
                        qtdPecas--;
                    }
                }
            } while (idInputPecas != 0);
        } else {
            qtdServicos--;
        }
    } while (idInputServico != 0);

    if (qtdServicos >= 1 && qtdPecas >= 1) {
        printf("Insira o ID do funcionário que fará o serviço: ");
        setbuf(stdin, NULL);
        scanf("%d", &idFuncionario);

        printf("Insira o ID do veículo a receber o serviço: ");
        setbuf(stdin, NULL);
        scanf("%d", &idVeiculo);

        // Verificando existência do item relacionado
        if (verificarIDFuncionariosModel(listaFuncionarios, idFuncionario) == 0) {
            // Limpando os ponteiros
            idPecas = NULL;
            idPecaDoServico = NULL;
            qtdPecasRequisitadas = NULL;
            free(idPecas);
            free(idPecaDoServico);
            free(qtdPecasRequisitadas);

            idServicos = NULL;
            free(idServicos);
            return;
        }

        if (verificarIDVeiculoModel(listaVeiculos, idVeiculo) == 0) {
            // Limpando os ponteiros
            idPecas = NULL;
            idPecaDoServico = NULL;
            qtdPecasRequisitadas = NULL;
            free(idPecas);
            free(idPecaDoServico);
            free(qtdPecasRequisitadas);

            idServicos = NULL;
            free(idServicos);
            return;
        }

        agendamento.idFuncionario = idFuncionario;
        agendamento.idVeiculo = idVeiculo;

        // Preenchimento dos dados
        printf("Insira a data desejada para realizar o serviço (DD/MM/AAAA): ");
        setbuf(stdin, NULL);
        scanf("%d/%d/%d", &dia, &mes, &ano);

        printf("Insira a hora desejada para realizar o serviço (HH:MM): ");
        setbuf(stdin, NULL);
        scanf("%d:%d", &hora, &minuto);

        dataHora.tm_mday = dia;
        dataHora.tm_mon = mes - 1;
        dataHora.tm_year = ano - 1900;
        dataHora.tm_hour = hora;
        dataHora.tm_min = minuto;
        dataHora.tm_sec = 0;

        time_t tempo = mktime(&dataHora);

        if (tempo == -1) {
            printf("Erro ao converter a data e hora.\n");
            // Limpando os ponteiros
            idPecas = NULL;
            idPecaDoServico = NULL;
            qtdPecasRequisitadas = NULL;
            free(idPecas);
            free(idPecaDoServico);
            free(qtdPecasRequisitadas);

            idServicos = NULL;
            free(idServicos);
            return;
        }

        // Verificando se um funcionário já possui um serviço na data e hora inserida
        if (lista->qtdAgendamentos > 1) {
            for (int i = 0; i < lista->qtdAgendamentos; i++) {
                sscanf(lista->listaAgendamentos[i].datahoraInicial, "%d/%d/%d %d:%d",
                       &dataHora.tm_mday, &dataHora.tm_mon, &dataHora.tm_year,
                       &dataHora.tm_hour, &dataHora.tm_min);

                dataHora.tm_year -= 1900;
                dataHora.tm_mon -= 1;
                time_t tempoExistente = mktime(&dataHora);

                if (tempoExistente == -1) {
                    printf("Erro ao converter a data e hora.\n");
                    // Limpando os ponteiros
                    idPecas = NULL;
                    idPecaDoServico = NULL;
                    qtdPecasRequisitadas = NULL;
                    free(idPecas);
                    free(idPecaDoServico);
                    free(qtdPecasRequisitadas);

                    idServicos = NULL;
                    free(idServicos);
                    return;
                }

                if (lista->listaAgendamentos[i].idFuncionario == idFuncionario && tempoExistente == tempo) {
                    printf("Não é possível agendar um serviço com esse funcionário.\n\n");

                    // Limpando os ponteiros
                    idPecas = NULL;
                    idPecaDoServico = NULL;
                    qtdPecasRequisitadas = NULL;
                    free(idPecas);
                    free(idPecaDoServico);
                    free(qtdPecasRequisitadas);

                    idServicos = NULL;
                    free(idServicos);
                    return;
                }
            }
        }

        strftime(agendamento.datahoraInicial, sizeof(agendamento.datahoraInicial), "%d/%m/%Y %H:%M", localtime(&tempo));

        // Cadastrando pagamento, se "-1" então teve erro
        if (cadastrarPagamentoClienteAgendamento(listaPecas, listaVeiculos, listaClientes, listaCaixas,
                                                 listaPagamentosCliente, listaServicos, qtdServicos, qtdPecas,
                                                 idPecas, idServicos, idVeiculo, valorAgendamento) == -1) {
            // Limpando os ponteiros
            idPecas = NULL;
            idPecaDoServico = NULL;
            qtdPecasRequisitadas = NULL;
            free(idPecas);
            free(idPecaDoServico);
            free(qtdPecasRequisitadas);

            idServicos = NULL;
            free(idServicos);
            free(idServicos);
            return;
        }

        // Debitando peças utilizadas
        for (int i = 0; i < qtdPecas; i++) {
            if (!debitarPecaEstoqueModel(listaPecas, idPecas[i], qtdPecasRequisitadas[i])) {
                // Limpando os ponteiros, caso algo dê errado
                idPecas = NULL;
                idPecaDoServico = NULL;
                qtdPecasRequisitadas = NULL;
                free(idPecas);
                free(idPecaDoServico);
                free(qtdPecasRequisitadas);
                idServicos = NULL;
                free(idServicos);
                return;
            }
        }

        // Cadastrando agendamentos de cada serviço inserido
        for (int i = 0; i < qtdServicos; i++) {
            int indiceServico = getIndiceVetorPorIdServicoModel(listaServicos, idServicos[i]);

            agendamento.idServico = idServicos[i];
            cadastrarAgendamentosModel(lista, &agendamento, 1);
            strcpy(ordensServico.descricao, listaServicos->listaServicos[indiceServico].descricao);
            ordensServico.idAgendamento = lista->qtdAgendamentos;
            ordensServico.valorTotal = listaServicos->listaServicos[indiceServico].preco;

            // Cadastrando ordens de serviço de cada peça inserida
            for (int j = 0; j < qtdPecas; j++) {
                if (idPecaDoServico[j] == idServicos[i]) {
                    int indicePeca = getIndiceVetorPorIdPecaModel(listaPecas, idPecas[j]);

                    ordensServico.valorTotal += listaPecas->listaPecas[indicePeca].precoVenda * qtdPecasRequisitadas[j];
                    ordensServico.idPecas = idPecas[j];
                    cadastrarOrdensServicoModel(listaOrdensServico, &ordensServico, 1);
                }
            }
        }

        printf("Agendamento realizado com sucesso para a data %s!\n\n", agendamento.datahoraInicial);
        printf("Ordem de serviço emitida com sucesso!\n\n");
    } else {
        printf("Nenhum serviço agendado!\n\n");
    }

    // Limpando os ponteiros
    idPecas = NULL;
    idPecaDoServico = NULL;
    qtdPecasRequisitadas = NULL;
    free(idPecas);
    free(idPecaDoServico);
    free(qtdPecasRequisitadas);

    idServicos = NULL;
    free(idServicos);
}

// Listagem de agendamentos
void listarAgendamentos(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico) {
    int opcao, id;

    // Pergunta o tipo de listagem
    printf("\n====================================\n"
        "|    LISTAGEM DE AGENDAMENTOS      |\n"
        "====================================\n"
        "| 1 | Busca por ID                 |\n"
        "| 2 | Busca por ID do funcionário  |\n"
        "| 3 | Busca por ID do veículo      |\n"
        "| 4 | Busca por ID do serviço      |\n"
        "| 5 | Listar todos                 |\n"
        "| 6 | Voltar                       |\n"
        "====================================\n"
        "Escolha uma opção: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    // Verifica a opção de listagem
    switch (opcao) {
        // Listagem de um único agendamento
        case 1:
            printf("Insira o ID do agendamento que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarAgendamentoModel(lista, id, listaOrdensServico);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID do funcionário desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorFuncionarioModel(lista, id, listaOrdensServico);
            break;
        case 3:
            printf("Insira o ID do veículo desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorVeiculoModel(lista, id, listaOrdensServico);
            break;
        case 4:
            printf("Insira o ID do serviço desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarAgendamentosPorServicoModel(lista, id, listaOrdensServico);
            break;
        // Listagem de todos os agendamentos
        case 5:
            listarTodosAgendamentosModel(lista, listaOrdensServico);
            break;
        case 6:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

// Formulário de deleção de agendamentos
void deletarAgendamento(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico) {
    int id;

    // Pede o ID do agendamento que será deletada
    printf("\n====================================\n"
        "|     CANCELAMENTO DE AGENDAMENTO   |\n"
        "====================================\n");
    printf("Insira o ID do agendamento que deseja cancelar:");
    scanf("%d", &id);
    deletarAgendamentosModel(lista, id, listaOrdensServico);
}

void finalizarOrdemServico(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico) {
    int idAgendamento, idServico;

    printf("\n==================================\n"
        "|   FINALIZAR ORDEM DE SERVIÇO   |\n"
        "==================================\n");
    printf("Insira o ID do agendamento:");
    scanf("%d", &idAgendamento);

    printf("Qual serviço deseja finalizar:");
    scanf("%d", &idServico);

    finalizarOrdemServicoModel(listaOrdensServico, lista, idAgendamento, idServico);
}

int cadastrarPagamentoClienteAgendamento(struct ListaPecas *listaPecas, struct ListaVeiculos *listaVeiculos,
                                         struct ListaClientes *listaClientes, struct ListaCaixas *listaCaixas,
                                         struct ListaPagamentosCliente *listaPagamentosCliente,
                                         struct ListaServicos *listaServicos, int qtdServicos, int qtdPecas,
                                         int *idPecas, int *idServicos, int idVeiculos, float valorAgendamento) {
    struct PagamentosCliente pagamento;
    pagamento.valor = valorAgendamento;

    // Pegando o tipo de pagamento do cliente, e mostrando o valor total do serviço
    do {
        printf("\nValor total do serviço e peças usadas: R$%.2f", pagamento.valor);
        printf("\n========================="
            "\n| 1 | Dinheiro          |"
            "\n| 2 | Cartão de crédito |"
            "\n| 3 | Cartão de débito  |"
            "\n=========================");
        printf("\nInsira tipo de pagamento: ");
        setbuf(stdin, NULL);
        scanf("%d", &pagamento.tipoPagamento);
    } while (pagamento.tipoPagamento < 1 || pagamento.tipoPagamento > 3);

    // Pegando a data que foi realizado o pagamento
    printf("Insira a data do pagamento (DD/MM/AAAA): ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", pagamento.dataPagamento);

    // Realiza as verificações de data
    struct tm dataPagamento = {0};
    sscanf(pagamento.dataPagamento, "%d/%d/%d",
           &dataPagamento.tm_mday, &dataPagamento.tm_mon, &dataPagamento.tm_year);
    dataPagamento.tm_year -= 1900;
    dataPagamento.tm_mon -= 1;
    time_t tempoPagamento = mktime(&dataPagamento);

    if (tempoPagamento == -1) {
        printf("Erro ao converter a data de pagamento.\n");
        return -1;
    }

    // Ajustando data de recebimento, caso dinheiro, ou pedindo a data, caso cartão
    if (pagamento.tipoPagamento == 1) {
        strcpy(pagamento.dataAReceber, pagamento.dataPagamento);
        strcpy(pagamento.dataRecebimento, pagamento.dataPagamento);
    } else {
        printf("Insira a data de vencimento do cartão (DD/MM/AAAA): ");
        setbuf(stdin, NULL);
        scanf(" %[^\n]", &pagamento.dataAReceber);

        // Realiza as verificações de data
        struct tm dataAReceber = {0};
        sscanf(pagamento.dataAReceber, "%d/%d/%d",
               &dataAReceber.tm_mday, &dataAReceber.tm_mon, &dataAReceber.tm_year);
        dataAReceber.tm_year -= 1900;
        dataAReceber.tm_mon -= 1;
        time_t tempoDataReceber = mktime(&dataAReceber);

        if (tempoDataReceber == -1) {
            printf("Erro ao converter a data a receber.\n");
            return -1;
        }

        time_t tempoAgora = time(NULL);

        if (tempoDataReceber <= tempoAgora) {
            strftime(pagamento.dataRecebimento, sizeof(pagamento.dataRecebimento), "%d/%m/%Y", localtime(&tempoAgora));
        } else {
            strcpy(pagamento.dataRecebimento, "Não pago");
        }
    }

    // Pegando ID do cliente que faz o pagamento
    int idClientePagando = getIdClientePorVeiculoModel(listaVeiculos, idVeiculos);
    if (idClientePagando == -1) {
        // Não encontrou, então cancela a operação
        return -1;
    }

    // Pegando ID da oficina e do seu caixa para receber o pagamento
    int getIdOficina = getIdOficinaClientesModel(listaClientes, idClientePagando);
    int idCaixaRecebe = getIdCaixaPorOficinaModel(listaCaixas, getIdOficina);
    if (idCaixaRecebe == -1) {
        // Não encontrou, então cancela a operação
        return -1;
    }

    // Atribui os IDs ao pagamento
    pagamento.idCaixa = idCaixaRecebe;
    pagamento.idCliente = idClientePagando;

    // Cadastra o pagamento
    cadastrarPagamentosClienteModel(listaPagamentosCliente, &pagamento, listaCaixas, 1);

    // Retorna com sucesso
    return 0;
}
