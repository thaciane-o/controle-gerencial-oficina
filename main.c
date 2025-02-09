// Include de bibliotecas do C
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Include de models e views
#include "models/clientes/modelClientes.h"
#include "views/clientes/viewClientes.h"

#include "views/veiculos/viewVeiculos.h"
#include "models/veiculos/modelVeiculos.h"

#include "views/oficina/viewOficina.h"
#include "models/oficina/modelOficina.h"

#include "views/pecas/viewPecas.h"
#include "models/pecas/modelPecas.h"

#include "views/fornecedores/viewFornecedores.h"
#include "models/fornecedores/modelFornecedores.h"

#include "./views/funcionarios/viewFuncionarios.h"
#include "./models/funcionarios/modelFuncionarios.h"

#include "./views/servicos/viewServicos.h"
#include "./models/servicos/modelServicos.h"

#include "./views/agendamentos/viewAgendamentos.h"
#include "./models/agendamentos/modelAgendamentos.h"

#include "./models/ordensServico/modelOrdensServico.h"

#include "./views/financeiro/viewFinanceiro.h"
#include "./models/caixas/modelCaixa.h"
#include "./models/pagamentoCliente/modelPagamentoCliente.h"
#include "./models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "./views/financeiro/viewFinanceiro.h"

#include "./views/agendamentos/viewAgendamentos.h"
#include "./models/agendamentos/modelAgendamentos.h"

#include "./models/ordensServico/modelOrdensServico.h"

#include "./views/estoques/viewEstoques.h"

#include "./models/notasFiscais/modelNotasFiscais.h"
#include "./models/pecasNotas/modelPecasNotas.h"
#include "views/exportacaoImportacao/viewExportacaoImportacao.h"

#include "./views/relatorios/viewRelatorios.h"

int main() {
    // Configuração para caracteres especiais
    system("chcp 65001");
    setlocale(LC_ALL, "PT_BR");

    // Declaração de variáveis dos dados do sistema
    struct ListaClientes listaClientes = {0, NULL};
    struct ListaVeiculos listaVeiculos = {0, NULL};
    struct ListaOficinas listaOficinas = {0, NULL};
    struct ListaPecas listaPecas = {0, NULL};
    struct ListaFornecedores listaFornecedores = {0, NULL};
    struct ListaServicos listaServicos = {0, NULL};
    struct ListaFuncionarios listaFuncionarios = {0, NULL};
    struct ListaCaixas listaCaixas = {0, NULL};
    struct ListaPagamentosCliente listaPagamentosCliente = {0, NULL};
    struct ListaPagamentosFornecedor listaPagamentosFornecedor = {0, NULL};
    struct ListaAgendamentos listaAgendamentos = {0, NULL};
    struct ListaOrdensServico listaOrdensServico = {0, NULL};
    struct ListaNotasFiscais listaNotasFiscais = {0, NULL};
    struct ListaPecasNotas listaPecasNotas = {0, NULL};

    // Variáveis de controle do sistema
    int opcaoMenu, opcaoCadastro, opcaoArmazenamento = 0;

    // Configuração de armazenamento inicial
    do {
        printf("\n===============================\n"
            "|        ARMAZENAMENTO        |\n"
            "===============================\n"
            "| 1 | Texto                   |\n"
            "| 2 | Binário                 |\n"
            "| 3 | Memória                 |\n"
            "===============================\n"
            "Como deseja armazenar?  ");
        scanf("%d", &opcaoArmazenamento);
    } while (opcaoArmazenamento < 1 || opcaoArmazenamento > 3);

    // Atualiza todos os pagamentos pendentes
    if (opcaoArmazenamento != 3) {
        atualizarPagamentosRecebidosModel(&listaCaixas, &listaPagamentosCliente, opcaoArmazenamento);
    }

    // Menu principal do sistema
    do {
        printf("\n=========================================\n"
            "|             MENU PRINCIPAL            |\n"
            "=========================================\n"
            "|  1  | Cadastros                       |\n"
            "|  2  | Agendamentos                    |\n"
            "|  3  | Controle de estoque             |\n"
            "|  4  | Gestão financeira               |\n"
            "|  5  | Relatórios                      |\n"
            "|  6  | Importação/exportação de dados  |\n"
            "|  7  | Sair                            |\n"
            "=========================================\n"
            "Escolha uma opção:\n");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {
            // Menu de CRUD
            case 1:
                do {
                    printf("\n=================================\n"
                        "|        MENU DE CADASTROS      |\n"
                        "=================================\n"
                        "|  1  | Oficina                 |\n"
                        "|  2  | Clientes                |\n"
                        "|  3  | Veículos                |\n"
                        "|  4  | Funcionários            |\n"
                        "|  5  | Serviços                |\n"
                        "|  6  | Fornecedores            |\n"
                        "|  7  | Peças                   |\n"
                        "|  8  | Voltar                  |\n"
                        "=================================\n"
                        "Escolha uma opção:\n");
                    scanf("%d", &opcaoCadastro);

                    switch (opcaoCadastro) {
                        case 1:
                            gerenciarOficina(&listaOficinas, &listaFuncionarios, &listaServicos, &listaClientes,
                                             &listaCaixas, &listaPecas, &listaPagamentosCliente,
                                             &listaPagamentosFornecedor, opcaoArmazenamento);
                            break;
                        case 2:
                            gerenciarClientes(&listaClientes, &listaVeiculos, &listaOficinas, opcaoArmazenamento);
                            break;
                        case 3:
                            gerenciarVeiculos(&listaClientes, &listaVeiculos, &listaAgendamentos, opcaoArmazenamento);
                            break;
                        case 4:
                            gerenciarFuncionario(&listaFuncionarios, &listaOficinas, &listaAgendamentos,
                                                 opcaoArmazenamento);
                            break;
                        case 5:
                            gerenciarServico(&listaServicos, &listaOficinas, &listaAgendamentos, opcaoArmazenamento);
                            break;
                        case 6:
                            gerenciarFornecedor(&listaFornecedores, &listaPecas, opcaoArmazenamento);
                            break;
                        case 7:
                            gerenciarPeca(&listaPecas, &listaOficinas, &listaFornecedores, &listaOrdensServico,
                                          opcaoArmazenamento);
                            break;
                        case 8:
                            // Sai do submenu
                            break;
                        default: printf("Opção inválida!\n\n");
                            break;
                    }
                } while (opcaoCadastro != 8);
                break;

            // Menu de agendamentos
            case 2:
                gerenciarAgendamentos(&listaAgendamentos, &listaFuncionarios, &listaServicos, &listaVeiculos,
                                      &listaOrdensServico, &listaPecas, &listaClientes, &listaCaixas,
                                      &listaPagamentosCliente, opcaoArmazenamento);
                break;

            // Menu de controle de estoque
            case 3:
                gerenciarEstoques(&listaPecas, &listaPecasNotas, &listaFornecedores, &listaNotasFiscais, &listaOficinas,
                                  &listaPagamentosFornecedor, &listaCaixas, opcaoArmazenamento);
                break;

            // Menu de gestão financeira
            case 4:
                gerenciarFinanceiro(&listaCaixas, &listaOficinas, &listaClientes, &listaPagamentosCliente,
                                    &listaPagamentosFornecedor, &listaFornecedores, opcaoArmazenamento);
                break;

            // Menu de relatórios
            case 5:
                gerenciarRelatorios(&listaOficinas, &listaClientes, &listaVeiculos, &listaFuncionarios, &listaServicos, &listaFornecedores,
                                 &listaPecas, &listaOrdensServico,
                                 &listaAgendamentos, &listaCaixas, &listaPagamentosCliente, &listaPagamentosFornecedor,
                                    opcaoArmazenamento);
                break;

            // Menu de importação/exportação
            case 6:
                gerenciarExportacaoImportacao(&listaClientes,
                                              &listaVeiculos,
                                              &listaOficinas,
                                              &listaPecas,
                                              &listaFornecedores,
                                              &listaServicos,
                                              &listaFuncionarios,
                                              &listaCaixas,
                                              &listaPagamentosCliente,
                                              &listaPagamentosFornecedor,
                                              &listaAgendamentos,
                                              &listaOrdensServico,
                                              &listaNotasFiscais,
                                              &listaPecasNotas,
                                              opcaoArmazenamento);
                break;

            // Sair
            case 7:
                // Desaloca os ponteiros, caso ainda tenha algum.
                if (listaClientes.qtdClientes > 0) {
                    free(listaClientes.listaClientes);
                    listaClientes.listaClientes = NULL;
                }
                if (listaVeiculos.qtdVeiculos > 0) {
                    free(listaVeiculos.listaVeiculos);
                    listaVeiculos.listaVeiculos = NULL;
                }
                if (listaOficinas.qtdOficinas > 0) {
                    free(listaOficinas.listaOficinas);
                    listaOficinas.listaOficinas = NULL;
                }
                if (listaPecas.qtdPecas > 0) {
                    free(listaPecas.listaPecas);
                    listaPecas.listaPecas = NULL;
                }
                if (listaFornecedores.qtdFornecedores > 0) {
                    free(listaFornecedores.listaFornecedores);
                    listaFornecedores.listaFornecedores = NULL;
                }
                if (listaServicos.qtdServicos > 0) {
                    free(listaServicos.listaServicos);
                    listaServicos.listaServicos = NULL;
                }
                if (listaFuncionarios.qtdFuncionarios > 0) {
                    free(listaFuncionarios.listaFuncionarios);
                    listaFuncionarios.listaFuncionarios = NULL;
                }
                if (listaCaixas.qtdCaixas > 0) {
                    free(listaCaixas.listaCaixas);
                    listaCaixas.listaCaixas = NULL;
                }
                if (listaPagamentosCliente.qtdPagamentosCliente > 0) {
                    free(listaPagamentosCliente.listaPagamentosCliente);
                    listaPagamentosCliente.listaPagamentosCliente = NULL;
                }
                if (listaPagamentosFornecedor.qtdPagamentosFornecedor > 0) {
                    free(listaPagamentosFornecedor.listaPagamentosFornecedor);
                    listaPagamentosFornecedor.listaPagamentosFornecedor = NULL;
                }
                if (listaAgendamentos.qtdAgendamentos > 0) {
                    free(listaAgendamentos.listaAgendamentos);
                    listaAgendamentos.listaAgendamentos = NULL;
                }
                if (listaOrdensServico.qtdOrdensServico > 0) {
                    free(listaOrdensServico.listaOrdensServico);
                    listaOrdensServico.listaOrdensServico = NULL;
                }
                if (listaNotasFiscais.qtdNotas > 0) {
                    free(listaNotasFiscais.listaNotas);
                    listaNotasFiscais.listaNotas = NULL;
                }
                if (listaPecasNotas.listaPecasNotas > 0) {
                    free(listaPecasNotas.listaPecasNotas);
                    listaPecasNotas.listaPecasNotas = NULL;
                }
                break;
        }
    } while (opcaoMenu != 7);

    return 0;
}
