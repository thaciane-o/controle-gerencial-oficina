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
    listaClientes.qtdClientes = 0;

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
                do {
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                } while (opcaoSubmenus != 5);
            break;
            case 2:
                do {
                    if (listaClientes.qtdClientes == 0) {
                        buscarDadosClientesModel(&listaClientes);
                    }
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            cadastrarCliente(&listaClientes);
                        break;
                        case 2:
                            atualizarCliente(&listaClientes);
                        break;
                        case 3:
                            deletarCliente(&listaClientes);
                        break;
                        case 4:
                            listarClientes(&listaClientes);
                        break;
                        case 5:
                            armazenarDadosClienteModel(&listaClientes);
                        break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                }while (opcaoSubmenus != 5);
            break;
            case 3:
                do{
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                }while (opcaoSubmenus != 5);
            break;
            case 4:
                do{
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                }while (opcaoSubmenus != 5);
            break;
            case 5:
                do{
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                }while (opcaoSubmenus != 5);
            break;
            case 6:
                do{
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                }while (opcaoSubmenus != 5);
            break;
            case 7:
                do{
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                }while (opcaoSubmenus != 5);
            break;
            case 8:
                do{
                    printf("=================================\n"
                        "|        MENU PRINCIPAL         |\n"
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
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        default: printf("\nOpção inválida!");
                        break;
                    }
                }while (opcaoSubmenus != 5);
            break;
            case 9:
                return 0;
            default: printf("\nOpção inválida!");
             break;
        }
    } while(opcaoMenu != 9);

}
