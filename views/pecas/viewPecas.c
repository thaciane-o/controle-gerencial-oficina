#include "viewPecas.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include <stdio.h>
#include <stdlib.h>

// Menu de funcionalidades de peças
void gerenciarPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores, struct ListaOrdensServico *listaOrdensServico, int opcaoArmazenamento) {
    int opcaoSubmenus = 0;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (listaFornecedores->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(listaFornecedores, opcaoArmazenamento);
        }

        if (listaPecas->qtdPecas > 0) {
            buscarDadosOrdensServicoModel(listaOrdensServico, opcaoArmazenamento);
        }
    }

    while (opcaoSubmenus != 5) {
        printf("\n=================================\n"
            "|         MENU DE PEÇAS         |\n"
            "=================================\n"
            "|  1  | Cadastrar               |\n"
            "|  2  | Atualizar               |\n"
            "|  3  | Deletar                 |\n"
            "|  4  | Listar                  |\n"
            "|  5  | Voltar                  |\n"
            "=================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarPeca(listaPecas, listaFornecedores);
                break;
            case 2:
                atualizarPeca(listaPecas, listaFornecedores);
                break;
            case 3:
                deletarPeca(listaPecas, listaOrdensServico);
                break;
            case 4:
                listarPeca(listaPecas);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (listaPecas->qtdPecas > 0) {
                        armazenarDadosPecaModel(listaPecas, opcaoArmazenamento);
                    }

                    if (listaFornecedores->qtdFornecedores > 0) {
                        free(listaFornecedores->listaFornecedores);
                        listaFornecedores->listaFornecedores = NULL;
                        listaFornecedores->qtdFornecedores = 0;
                    }
                }
                break;
            default: printf("Opção inválida!\n\n");
                break;
        }
    }
}

// Formulário de cadastro de peças
void cadastrarPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores) {
    struct Pecas pecaCadastrando;
    int idFornecedor;

    printf("\n===============================\n"
        "|      CADASTRO DE PEÇA       |\n"
        "===============================\n");

    printf("Insira o Id do fornecedor da peça: ");
    setbuf(stdin, NULL);
    scanf("%d", &idFornecedor);

    // Verificando existência do item relacionado
    if (verificarIDFornecedoresModel(listaFornecedores, idFornecedor) == 0) {
        return;
    }

    pecaCadastrando.idFornecedor = idFornecedor;

    // Preenchimento dos dados
    printf("Insira a descrição da peça: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", pecaCadastrando.descricao);

    printf("Insira o fabricante da peça: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", pecaCadastrando.fabricante);

    printf("Insira o preço de custo da peça: R$");
    setbuf(stdin, NULL);
    scanf("%f", &pecaCadastrando.precoCusto);

    printf("Insira o preço de venda da peça: R$");
    setbuf(stdin, NULL);
    scanf("%f", &pecaCadastrando.precoVenda);

    printf("Insira a quantidade de peças no estoque: ");
    setbuf(stdin, NULL);
    scanf("%d", &pecaCadastrando.qtdEstoque);

    printf("Insira a quantidade de peças mínimas no estoque: ");
    setbuf(stdin, NULL);
    scanf("%d", &pecaCadastrando.estoqueMinimo);

    cadastrarPecaModel(listaPecas, &pecaCadastrando);
}

// Formulário de atualização de peças
void atualizarPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores) {
    struct Pecas pecaAtualizando;
    int idFornecedor, idPeca;

    // Pede o Id da peça que será atualizada
    printf("\n===============================\n"
        "|     ATUALIZAÇÃO DE PEÇA     |\n"
        "===============================\n");

    printf("Insira o Id da peça a ser atualizada: ");
    setbuf(stdin, NULL);
    scanf("%d", &idPeca);

    // Verifica se o ID inserido existe
    if (verificarIDPecaModel(listaPecas, idPeca) == 0) {
        return;
    }

    printf("Insira o Id do fornecedor da peça: ");
    setbuf(stdin, NULL);
    scanf("%d", &idFornecedor);

    if (verificarIDFornecedoresModel(listaFornecedores, idFornecedor) == 0) {
        return;
    }

    pecaAtualizando.idFornecedor = idFornecedor;

    //Preenchimento dos dados
    printf("Insira a descrição da peça: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", pecaAtualizando.descricao);

    printf("Insira o fabricante da peça: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", pecaAtualizando.fabricante);

    printf("Insira o preço de custo da peça: R$");
    setbuf(stdin, NULL);
    scanf("%f", &pecaAtualizando.precoCusto);

    printf("Insira o preço de venda da peça: R$");
    setbuf(stdin, NULL);
    scanf("%f", &pecaAtualizando.precoVenda);

    printf("Insira a quantidade de peças no estoque: ");
    setbuf(stdin, NULL);
    scanf("%d", &pecaAtualizando.qtdEstoque);

    printf("Insira a quantidade de peças mínimas no estoque: ");
    setbuf(stdin, NULL);
    scanf("%d", &pecaAtualizando.estoqueMinimo);

    atualizarPecaModel(listaPecas, idPeca, &pecaAtualizando);
}

// Listagem de peças
void listarPeca(struct ListaPecas *listaPecas) {
    int resp;
    // Pergunta o tipo de listagem
    printf("\n==================================\n"
        "|     LISTAGEM DE FORNECEDOR     |\n"
        "==================================\n"
        "| 1 | Busca por ID               |\n"
        "| 2 | Busca por ID do Fornecedor |\n"
        "| 3 | Listar todos               |\n"
        "| 4 | Voltar                     |\n"
        "==================================\n"
        "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &resp);

    // Verifica a opção de listagem
    int id = 0;
    switch (resp) {
        // Listagem de uma única peça
        case 1:
            printf("Insira o ID desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarPecaModel(listaPecas, id);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID do fornecedor desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarPecasPorFornecedorModel(listaPecas, id);
            break;
        // Listagem de todas as peças
        case 3:
            listarTodosPecaModel(listaPecas);
            break;
        case 4:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n\n");
            break;
    }
}

// Formulário de deleção de peças
void deletarPeca(struct ListaPecas *lista, struct ListaOrdensServico *listaOrdensServico) {
    int id;

    // Pede o Id da peça que será deletada
    printf("\n==============================\n"
        "|      DELEÇÃO DE PEÇA       |\n"
        "==============================\n");
    printf("Insira o ID da peça que deseja deletar: ");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    deletarPecaModel(lista, id, listaOrdensServico);
}
