#include <stdio.h>
#include <stdlib.h>
#include "./views/fornecedores/viewFornecedores.h"
#include "./models/fornecedores/modelFornecedores.h"

int main() {
    struct ListaFornecedores listaFornecedores;
    listaFornecedores.qtdFornecedores = 0;
    int opcaoMenu, opcaoSubmenus, opcaoArmazenamento;

    do {
        printf("Como deseja armazenar?\n"
           "1. Texto\n"
           "2. Binário\n"
           "3. Memória\n"
            "Escolha uma opção: \n");
        scanf("%d", &opcaoArmazenamento);
    } while (opcaoArmazenamento < 1 || opcaoArmazenamento > 3);

    do {
        printf("\n=================================\n"
            "|         MENU PRINCIPAL        |\n"
            "=================================\n"
            "|  1  | Oficina                 |\n"
            "|  2  | Clientes                |\n"
            "|  3  | Veículos               |\n"
            "|  4  | Peças                  |\n"
            "|  5  | Fornecedores            |\n"
            "|  6  | Serviços               |\n"
            "|  7  | Funcionários           |\n"
            "|  8  | Sair                    |\n"
            "=================================\n"
        "Escolha uma opção:\n");
        scanf("%d", &opcaoMenu);

         switch (opcaoMenu) {
            case 1:

            break;
            case 2:

            break;
            case 3:

            break;
            case 4:

            break;
            case 5:
                gerenciarFornecedor(&listaFornecedores, opcaoArmazenamento);
            break;
            case 6:

            break;
            case 7:

            break;
            case 8:
                if (listaFornecedores.qtdFornecedores > 0) {
                    free(listaFornecedores.listaFornecedores);
                    listaFornecedores.listaFornecedores = NULL;
                }
            break;
            default: printf("Opção inválida!\n\n");
        }
    } while(opcaoMenu != 8);

    return 0;

}