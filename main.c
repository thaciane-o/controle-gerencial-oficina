#include <stdio.h>
#include "./models/clientes/modelClientes.h"
#include "./views/clientes/viewClientes.h"
#include "./views/fornecedores/viewFornecedores.h"
#include "./models/fornecedores/modelFornecedores.h"
#include <locale.h>
#include <stdlib.h>



int main() {
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
       "|  3  | Veículos                |\n"
       "|  4  | Veículos                |\n"
       "|  5  | Peças                   |\n"
       "|  6  | Fornecedores            |\n"
       "|  7  | Serviços                |\n"
       "|  8  | Funcionários            |\n"
       "|  9  | Sair                    |\n"
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
            break;
            case 6:
            break;
            case 7:
            break;
            case 8:
            break;
            case 9:
                return 0;
            default: printf("\nOpção inválida!");
             break;
        }
    } while(opcaoMenu != 9);

}
