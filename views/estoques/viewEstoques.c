#include "viewEstoques.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../models/oficina/modelOficina.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/pecasNotas/modelPecasNotas.h"


void gerenciarEstoques(struct ListaPecas *listaPecas, struct ListaPecasNotas *listaPecasNotas,
                       struct ListaFornecedores *listaFornecedores,
                       struct ListaNotasFiscais *listaNotas, struct ListaOficinas *listaOficinas, int opcaoArmazenamento) {
int opcaoSubmenus;

    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (listaPecas->qtdPecas > 0) {
            buscarDadosNotasFiscaisModel(listaNotas, opcaoArmazenamento);
        }

        if (listaNotas->qtdNotas > 0) {
            buscarDadosPecaNotaModel(listaPecasNotas, opcaoArmazenamento);
        }

        if (listaFornecedores->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(listaFornecedores, opcaoArmazenamento);
        }
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }
    }

    // Chama uma função para verificar os estoques em necessidade
    verificarEstoqueMinimo(listaPecas);
    do {
        printf("\n==========================================\n"
            "|          CONTROLE DE ESTOQUE           |\n"
            "==========================================\n"
            "|  1  | Realizar pedido de peças         |\n"
            "|  2  | Listar Notas Fiscais             |\n"
            "|  3  | Deletar Nota Fiscal              |\n"
            "|  4  | Voltar                           |\n"
            "==========================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                realizarPedidoEstoque(listaNotas, listaPecasNotas, listaPecas, listaFornecedores, listaOficinas);
                break;
            case 2:
                listarNotasFiscais(listaPecas, listaPecasNotas, listaNotas, listaFornecedores);
                break;
            case 3:
                deletarNotaFiscal(listaNotas, listaPecasNotas);
                break;
            case 4:
                if (opcaoArmazenamento != 3 && listaPecas->listaPecas != NULL) {
                    if (listaPecas->qtdPecas > 0) {
                        armazenarDadosPecaModel(listaPecas, opcaoArmazenamento);
                    }
                    if (listaNotas->qtdNotas > 0) {
                        armazenarDadosNotasFiscaisModel(listaNotas, opcaoArmazenamento);
                    }
                    if (listaPecasNotas->qtdPecasNotas > 0) {
                        armazenarDadosPecaNotaModel(listaPecasNotas, opcaoArmazenamento);
                    }
                    if (listaFornecedores->qtdFornecedores > 0) {
                        free(listaFornecedores->listaFornecedores);
                        listaFornecedores->listaFornecedores = NULL;
                        listaFornecedores->qtdFornecedores = 0;
                    }
                    if (listaNotas->qtdNotas > 0) {
                        free(listaNotas->listaNotas);
                        listaNotas->listaNotas = NULL;
                        listaNotas->qtdNotas = 0;
                    }
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 5);


}

// Realiza pedido de novas peças
void realizarPedidoEstoque(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                           struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                           struct ListaOficinas *listaOficinas) {
    struct NotasFiscais notaFiscal;
    struct PecasNotas pecaNota;

    int totalPecas = 0, cadastrouPeca = 0;

    notaFiscal.totalNota = 0;

    printf("Digite a Oficina que esta fazendo o pedido: ");
    scanf("%d", &notaFiscal.idOficina);

    // verifica existência da oficina
    if (!verificarIDOficinaModel(listaOficinas, notaFiscal.idOficina)) {
        return;
    }

    printf("Digite o fornecedor das peças: ");
    scanf("%d", &notaFiscal.idFornecedor);

    // verifica se o fornecedor existe
    if(!verificarIDFornecedoresModel(listaFornecedores, notaFiscal.idFornecedor)) {
        return;
    }

    printf("\nInsira o valor do frete: ");
    scanf("%f", &notaFiscal.frete);

    printf("\nInsira o valor do imposto: ");
    scanf("%f", &notaFiscal.imposto);

    do {
        printf("\nInsira o ID de uma peça para o pedido (0 para finalizar): ");
        scanf("%d", &pecaNota.idPeca);

        pecaNota.idNota = lista->qtdNotas + 1;

        if (pecaNota.idPeca != 0) {

            // verifica se peça existe
            if (!verificarIDPecaModel(listaPecas, pecaNota.idPeca)) {
                // Se não, cadastra-se uma nova peça
                struct Pecas novaPeca;

                novaPeca.idFornecedor = notaFiscal.idFornecedor;

                printf("Insira a descrição da peça: ");
                setbuf(stdin, NULL);
                scanf(" %[^\n]s", novaPeca.descricao);

                printf("Insira o fabricante da peça: ");
                setbuf(stdin, NULL);
                scanf(" %[^\n]s", novaPeca.fabricante);

                printf("Insira o preço de custo da peça: R$");
                setbuf(stdin, NULL);
                scanf("%f", &novaPeca.precoCusto);

                novaPeca.precoVenda = 0;
                novaPeca.qtdEstoque = 0;

                printf("Insira a quantidade de peças mínimas no estoque: ");
                setbuf(stdin, NULL);
                scanf("%d", &novaPeca.estoqueMinimo);

                pecaNota.idPeca = listaPecas->qtdPecas + 1;

                cadastrarPecaModel(listaPecas, &novaPeca);
            }
            // verifica se a peça possuí relação com o fornecedor
            if (!verificarRelacaoFornecedorModel(listaPecas, &notaFiscal, pecaNota.idPeca)) {
                deletarPecaNotaModel(listaPecasNotas, lista->qtdNotas+1);
                return;
            }


            printf("\nInsira a quantidade a ser pedida: ");
            scanf("%d", &pecaNota.qtdPecas);

            // Soma a quantidade de peças que foi pedida
            totalPecas += pecaNota.qtdPecas;

            cadastrarPecaNotaModel(listaPecasNotas, &pecaNota);
            cadastrouPeca = 1;
        }
    }while (pecaNota.idPeca != 0);

    // Verifica se pelo menos uma peça foi cadastrada
    if(cadastrouPeca != 0) {
        cadastrarNotasFiscaisModel(lista, &notaFiscal, listaPecas, listaOficinas, listaPecasNotas, totalPecas);
    } else {
        printf("\nPor favor, informe as peças que serão compradas\n");
    }
}


void listarNotasFiscais(struct ListaPecas *lista, struct ListaPecasNotas *listaPecasNotas,
                        struct ListaNotasFiscais *listaNotasFiscais, struct ListaFornecedores *listaFornecedores) {
    int resp;
    // Pergunta o tipo de listagem
    printf("\n==================================\n"
        "|   LISTAGEM DE NOTAS FISCAIS    |\n"
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
        listarNotaFiscalModel(listaNotasFiscais, listaPecasNotas, lista, listaFornecedores, id);
        break;
        // Listagem por relação
        case 2:
            printf("Insira o ID do fornecedor desejado para a busca: ");
        setbuf(stdin, NULL);
        scanf("%d", &id);
        buscarNotasFiscaisPorFornecedorModel(listaNotasFiscais, listaPecasNotas, lista, listaFornecedores, id);
        break;
        // Listagem de todas as peças
        case 3:
            listarTodasNotasFiscaisModel(listaNotasFiscais, listaPecasNotas, lista, listaFornecedores);
        break;
        case 4:
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n\n");
        break;
    }
}

void deletarNotaFiscal(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas) {
    int id;

    // Pede o Id da peça que será deletada
    printf("\n==============================\n"
        "|   DELEÇÃO DE NOTA FISCAL    |\n"
        "==============================\n");
    printf("Insira o ID da nota que deseja deletar: ");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    deletarNotaModel(lista, listaPecasNotas, id);
}