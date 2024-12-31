#include "viewEstoques.h"

#include <stdio.h>
#include <stdlib.h>

#include "..\..\models\estoques\modelEstoques.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\fornecedores\modelFornecedores.h"
#include "..\..\models\notasFiscais\modelNotasFiscais.h"


void gerenciarEstoques(struct ListaPecas *lista, struct ListaFornecedores *listaFornecedores, struct ListaNotasFiscais *listaNotas, int opcaoArmazenamento) {
int opcaoSubmenus;

    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdPecas == 0) {
            buscarDadosPecaModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (lista->qtdPecas > 0) {
            buscarDadosNotasFiscaisModel(listaNotas, opcaoArmazenamento);
        }
        if (listaFornecedores->qtdFornecedores == 0) {
            buscarDadosFornecedoresModel(listaFornecedores, opcaoArmazenamento);
        }
    }
    verificarEstoqueMinimo(lista);
    do {
        printf("\n==========================================\n"
            "|          CONTROLE DE ESTOQUE           |\n"
            "==========================================\n"
            "|  1  | Realizar pedido de peças         |\n"
            "|  2  | Atualizar estoque                |\n"
            "|  3  | Listar pedidos                   |\n"
            "|  4  | Voltar                           |\n"
            "==========================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                realizarPedidoEstoque(lista, listaFornecedores, listaNotas);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                if (opcaoArmazenamento != 3 && lista->listaPecas != NULL) {
                    if (lista->qtdPecas > 0) {
                        armazenarDadosPecaModel(lista, opcaoArmazenamento);
                    }
                    if (listaNotas->qtdNotas > 0) {
                        armazenarDadosNotasFiscaisModel(listaNotas, opcaoArmazenamento);
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
    } while (opcaoSubmenus != 4);


}

void realizarPedidoEstoque(struct ListaPecas *lista, struct ListaFornecedores *listaFornecedores, struct ListaNotasFiscais *listaNotas) {
    struct notasFiscais notaFiscal;
    notaFiscal.tamListaPecas = 0;
    int varControleIdPecas;

    printf("Digite o fornecedor das peças: ");
    scanf("%d", &notaFiscal.idFornecedor);

    if(!verificarIDFornecedoresModel(listaFornecedores, notaFiscal.idFornecedor)) {
        return;
    }

    do {
        printf("\nInsira o ID de uma peça para o pedido (0 para finalizar): ");
        scanf("%d", &varControleIdPecas);

        if (varControleIdPecas != 0) {

            if (!verificarIDPecaModel(lista, varControleIdPecas)) {
                return;
            }

            notaFiscal.tamListaPecas++;

            if (notaFiscal.tamListaPecas == 1) {
                notaFiscal.idPecas = malloc(sizeof (int) * (notaFiscal.tamListaPecas));
                if (notaFiscal.idPecas == NULL) {
                    printf("Erro alocando memoria\n");
                    return;
                }
                notaFiscal.qtdPecas = malloc(sizeof (int) * (notaFiscal.tamListaPecas));
                if (notaFiscal.qtdPecas == NULL) {
                    printf("Erro alocando memoria\n");
                    return;
                }
            }else {
                notaFiscal.idPecas = realloc(notaFiscal.idPecas,sizeof (int) * (notaFiscal.tamListaPecas));
                if (notaFiscal.idPecas == NULL) {
                    printf("Erro alocando memoria\n");
                    return;
                }
                notaFiscal.qtdPecas = realloc(notaFiscal.idPecas, sizeof (int) * (notaFiscal.tamListaPecas));
                if (notaFiscal.qtdPecas == NULL) {
                    printf("Erro alocando memoria\n");
                    return;
                }
            }

            printf("\nInsira a quantidade a ser pedida: ");
            scanf("%d", &notaFiscal.qtdPecas[notaFiscal.tamListaPecas - 1]);

            notaFiscal.idPecas[notaFiscal.tamListaPecas - 1] = varControleIdPecas;

            for (int i = 0; i < lista->qtdPecas; i++) {
                if (lista->listaPecas[i].id == varControleIdPecas) {
                    lista->listaPecas->qtdEstoque += notaFiscal.qtdPecas[notaFiscal.tamListaPecas - 1];
                }
            }
        }

    }while (varControleIdPecas != 0);

    printf("\nInsira o valor do frete: ");
    scanf("%f", &notaFiscal.frete);

    printf("\nInsira o valor do imposto: ");
    scanf("%f", &notaFiscal.imposto);

    cadastrarNotasFiscaisModel(listaNotas, &notaFiscal, notaFiscal.tamListaPecas);
}

// void atualizarEstoques(struct ListaEstoques *lista, struct ListaPecas listaPecas, struct ListaFornecedores *listaFornecedores) {
//
// }
//
// void listarNotasFiscais(struct ListaEstoques *lista, struct ListaPecas listaPecas, struct ListaFornecedores *listaFornecedores) {
//
//
// }