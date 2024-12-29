#include "viewEstoques.h"

#include <stdio.h>

#include "..\..\models\estoques\modelEstoques.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\fornecedores\modelFornecedores.h"

void gerenciarEstoques(struct ListaEstoques *lista, struct ListaPecas *listaPecas, int opcaoArmazenamento) {
int opcaoSubmenus;

    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdEstoques == 0) {
            buscarDadosEstoqueModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (listaPecas->qtdPecas == 0) {
            buscarDadosPecaModel(listaPecas, opcaoArmazenamento);
        }
    }

    do {
        printf("\n==========================================\n"
            "|          CONTROLE DE ESTOQUE           |\n"
            "==========================================\n"
            "|  1  | Registrar entrega ao estoque     |\n"
            "|  2  | Registrar retirada do estoque    |\n"
            "|  3  |  |\n"
            "|  4  | Listar estoques                  |\n"
            "|  5  | Deletar estoque                  |\n"
            "|  6  | Voltar                           |\n"
            "==========================================\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
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
                if (opcaoArmazenamento != 3 && lista->listaEstoques != NULL) {
                    if (lista->qtdEstoques > 0) {
                        armazenarDadosEstoquesModel(lista, opcaoArmazenamento);
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

void entradaEstoque(struct ListaEstoques *lista, struct ListaPecas *listaPecas) {



}

void vendaEstoque(struct ListaEstoques *lista, struct ListaPecas *listaPecas) {



}

void listarEstoques(struct ListaEstoques *lista, struct ListaPecas listaPecas, struct ListaFornecedores *listaFornecedores) {


}