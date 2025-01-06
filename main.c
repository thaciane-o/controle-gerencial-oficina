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


int main() {
    // Configuração para caracteres especiais
    system("chcp 65001");
    setlocale(LC_ALL, "PT_BR");

    // Declaração de variáveis dos dados do sistema
    struct ListaClientes listaClientes;
    listaClientes.qtdClientes = 0;

    struct ListaVeiculos listaVeiculos;
    listaVeiculos.qtdVeiculos = 0;

    struct ListaOficinas listaOficinas;
    listaOficinas.qtdOficinas = 0;

    struct ListaPecas listaPecas;
    listaPecas.qtdPecas = 0;

    struct ListaFornecedores listaFornecedores;
    listaFornecedores.qtdFornecedores = 0;

    struct ListaServicos listaServicos;
    listaServicos.qtdServicos = 0;

    struct ListaFuncionarios listaFuncionarios;
    listaFuncionarios.qtdFuncionarios = 0;

    struct ListaCaixas listaCaixas;
    listaCaixas.qtdCaixas = 0;

    struct ListaPagamentosCliente listaPagamentosCliente;
    listaPagamentosCliente.qtdPagamentosCliente = 0;

    struct ListaPagamentosFornecedor listaPagamentosFornecedor;
    listaPagamentosFornecedor.qtdPagamentosFornecedor = 0;


    struct ListaAgendamentos listaAgendamentos;
    listaAgendamentos.qtdAgendamentos = 0;

    struct ListaOrdensServico listaOrdensServico;
    listaOrdensServico.qtdOrdensServico = 0;

    struct ListaNotasFiscais listaNotasFiscais;
    listaNotasFiscais.qtdNotas = 0;

    struct ListaPecasNotas listaPecasNotas;
    listaPecasNotas.qtdPecasNotas = 0;

    // Variáveis de controle do sistema
    int opcaoMenu, opcaoCadastro, opcaoArmazenamento = 0;

    // Menu principal do sistema
    do {
        // Configuração de armazenamento inicial
        do {
            printf("\n===============================\n"
                "|        ARMAZENAMENTO        |\n"
                "===============================\n"
                "| 1 | Texto                   |\n"
                "| 2 | Binário                 |\n"
                "| 3 | Memória                 |\n"
                "| 4 | Sair                    |\n"
                "===============================\n"
                "Como deseja armazenar?  ");
            scanf("%d", &opcaoArmazenamento);

            if (opcaoArmazenamento == 4) {
                return 0;
            }

            printf("\n=========================================\n"
                "|             MENU PRINCIPAL            |\n"
                "=========================================\n"
                "|  1  | Cadastros                       |\n"
                "|  2  | Agendamentos                    |\n"
                "|  3  | Controle de estoque             |\n"
                "|  4  | Gestão financeira               |\n"
                "|  5  | Relatórios                      |\n"
                "|  6  | Importação/exportação de dados  |\n"
                "|  7  | Voltar                          |\n"
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
                                gerenciarOficina(&listaOficinas, &listaFuncionarios, &listaServicos, &listaClientes, &listaCaixas,
                                                 opcaoArmazenamento);
                                break;
                            case 2:
                                gerenciarClientes(&listaClientes, &listaVeiculos, &listaOficinas, opcaoArmazenamento);
                                break;
                            case 3:
                                gerenciarVeiculos(&listaClientes, &listaVeiculos, &listaAgendamentos,
                                                  opcaoArmazenamento);
                                break;
                            case 4:
                                gerenciarFuncionario(&listaFuncionarios, &listaOficinas, &listaAgendamentos,
                                                     opcaoArmazenamento);
                                break;
                            case 5:
                                gerenciarServico(&listaServicos, &listaOficinas, &listaAgendamentos,
                                                 opcaoArmazenamento);
                                break;
                            case 6:
                                gerenciarFornecedor(&listaFornecedores, &listaPecas, opcaoArmazenamento);
                                break;
                            case 7:
                                gerenciarPeca(&listaPecas, &listaFornecedores, opcaoArmazenamento);
                                break;
                            case 8:
                                if (listaClientes.qtdClientes > 0) {
                                    free(listaClientes.listaClientes);
                                    listaClientes.listaClientes = NULL;
                                }

                                if (listaPecas.qtdPecas > 0) {
                                    free(listaPecas.listaPecas);
                                    listaPecas.listaPecas = NULL;
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
                                break;
                            default: printf("Opção inválida!\n\n");
                                break;
                        }
                    } while (opcaoCadastro != 8);
                    break;
                case 2:
                    gerenciarAgendamentos(&listaAgendamentos, &listaFuncionarios, &listaServicos, &listaVeiculos,
                                          &listaOrdensServico, &listaPecas,
                                          opcaoArmazenamento);
                    break;
                case 3:
                    gerenciarEstoques(&listaPecas, &listaPecasNotas, &listaFornecedores, &listaNotasFiscais, &listaOficinas, opcaoArmazenamento);
                    break;
                case 7:
                    if (listaAgendamentos.qtdAgendamentos > 0) {
                        free(listaAgendamentos.listaAgendamentos);
                        listaAgendamentos.listaAgendamentos = NULL;
                    }

                    if (listaOrdensServico.qtdOrdensServico > 0) {
                        free(listaOrdensServico.listaOrdensServico);
                        listaOrdensServico.listaOrdensServico = NULL;
                    }
                    break;
            }
        } while (opcaoMenu != 7);
    } while (opcaoArmazenamento != 4);
    return 0;
}
