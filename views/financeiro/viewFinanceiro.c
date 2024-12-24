#include "../../models/caixas/modelCaixa.h"
#include "../../models/oficina/modelOficina.h"

#include "viewFinanceiro.h"
#include <stdio.h>
#include <stdlib.h>

// Menu de funcionalidades do módulo financeiro
void gerenciarFinanceiro(struct ListaCaixas *lista, struct ListaOficinas *listaOficinas, int opcaoArmazenamento) {
    int opcaoSubmenus;

    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdCaixas == 0) {
            buscarDadosCaixasModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }
    }

    do {
        printf("\n==========================================\n"
            "|               FINANCEIRO               |\n"
            "==========================================\n"
            "|  1  | Consultar valor de caixa         |\n"
            "|  2  | Consultar contas a receber       |\n"
            "|  3  | Consultar contas a pagar         |\n"
            "|  4  | Registrar recebimento de cliente |\n"
            "|  5  | Efetuar pagamento a fornecedor   |\n"
            "|  6  | Voltar                           |\n"
            "==========================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                consultarValorCaixa(lista);
                break;
            case 2:
                printf("Consultando contas a receber");
                break;
            case 3:
                printf("Consultando contas a pagar");
                break;
            case 4:
                printf("Registrar recebimento de cliente");
                break;
            case 5:
                printf("Efetuar pagamento a fornecedor");
                break;
            case 6:
                if (opcaoArmazenamento != 3 && lista->listaCaixas != NULL) {
                    if (lista->qtdCaixas > 0) {
                        armazenarDadosCaixasModel(lista, opcaoArmazenamento);
                    }
                    if (listaOficinas->qtdOficinas > 0) {
                        free(listaOficinas->listaOficinas);
                        listaOficinas->listaOficinas = NULL;
                        listaOficinas->qtdOficinas = 0;
                    }
                }
                return;
            default:
                printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoSubmenus != 5);
}

// Busca de valor de caixa de oficina
void consultarValorCaixa(struct ListaCaixas *lista) {

    int idOficina;
    printf("Insira o ID da oficina que deseja consultar: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);
    mostrarCaixasModel(lista, idOficina);

}
