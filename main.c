#include <stdio.h>
#include "./models/clientes/modelClientes.h"
#include "./views/clientes/viewClientes.h"
#include "./views/fornecedores/viewFornecedores.h"
#include "./models/fornecedores/modelFornecedores.h"
#include <locale.h>
#include <stdlib.h>



int main() {
    struct ListaFornecedores listaFornecedores;
    listaFornecedores.qtdFornecedores = 0;
    system("chcp 65001");
    system("cls");
    setlocale(LC_ALL, "PT-BR");

    struct ListaClientes listaClientes;

    int opcaoMenu, opcaoSubmenus;

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
        "Escolha uma opção: ");
        scanf("%d", &opcaoMenu);

         switch (opcaoMenu) {
            case 1:
            break;
            case 2:
                gerenciarClientes(&listaClientes);
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
                gerenciarFornecedor(&listaFornecedores);
            break;
            case 6:
            break;
            case 7:
            break;
            case 8:
            return 0;
            default: printf("Opção inválida!\n\n");
             break;
        }
    } while(opcaoMenu != 8);

    return 0;

}