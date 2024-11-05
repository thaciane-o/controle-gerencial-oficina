#include <stdio.h>
#include "./views/fornecedores/viewFornecedores.h"
#include "./models/fornecedores/modelFornecedores.h"
#include "models/clientes/modelClientes.h"
#include "views/clientes/viewClientes.h"
#include <locale.h>
#include <stdlib.h>

int main() {
    system("chcp 65001");
    system("cls");
    setlocale(LC_ALL, "PT-BR");

    struct ListaFornecedores listaFornecedores;
    listaFornecedores.qtdFornecedores = 0;
    int opcaoMenu, opcaoSubmenus;

    do {
        printf("=================================\n"
           "|        MENU PRINCIPAL         |\n"
           "=================================\n"
           "|  1  | Cadastrar               |\n"
           "|  2  | Atualizar               |\n"
           "|  3  | Deletar                 |\n"
           "|  4  | Listar                  |\n"
           "|  5  | Sair                    |\n"
           "=================================\n"
           "Escolha uma opção: ");
        scanf("%d", &opcaoMenu);

         switch (opcaoMenu) {
            case 1:
                printf("\n=================================\n"
                   "|       MENU DE CADASTROS       |\n"
                   "=================================\n"
                   "|  1  | Oficina                 |\n"
                   "|  2  | Clientes                |\n"
                   "|  3  | Veículos               |\n"
                   "|  4  | Peças                  |\n"
                   "|  5  | Fornecedores            |\n"
                   "|  6  | Serviços               |\n"
                   "|  7  | Funcionários           |\n"
                   "|  8  | Voltar                  |\n"
                   "=================================\n"
                    "Escolha uma opção: ");
                scanf("%d", &opcaoSubmenus);

                switch (opcaoSubmenus) {
                    case 1:
                        break;
                    case 2:
                        cadastrarCliente();
                    break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        cadastrarFornecedor(&listaFornecedores);
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                        break;
                    default: printf("Opção inválida!\n\n");
                };
                break;
            case 2:
                printf("\n=================================\n"
                   "|     MENU DE ATUALIZAÇÕES    |\n"
                   "=================================\n"
                   "|  1  | Oficina                 |\n"
                   "|  2  | Clientes                |\n"
                   "|  3  | Veículos               |\n"
                   "|  4  | Peças                  |\n"
                   "|  5  | Fornecedores            |\n"
                   "|  6  | Serviços               |\n"
                   "|  7  | Funcionários           |\n"
                   "|  8  | Voltar                  |\n"
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
                        atualizarFornecedor(&listaFornecedores);
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                        break;
                    default: printf("Opção inválida!\n\n");
                };

                break;
            case 3:
                printf("\n=================================\n"
                    "|      MENU DE DELEÇÕES       |\n"
                    "=================================\n"
                    "|  1  | Oficina                 |\n"
                   "|  2  | Clientes                |\n"
                   "|  3  | Veículos               |\n"
                   "|  4  | Peças                  |\n"
                   "|  5  | Fornecedores            |\n"
                   "|  6  | Serviços               |\n"
                   "|  7  | Funcionários           |\n"
                   "|  8  | Voltar                  |\n"
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
                         deletarFornecedor(&listaFornecedores);
                         break;
                     case 6:
                         break;
                     case 7:
                         break;
                     case 8:
                         break;
                     default: printf("Opção inválida!\n\n");
                };
                break;
            case 4:
                printf("\n=================================\n"
                    "|       MENU DE LISTAGEM        |\n"
                    "=================================\n"
                    "|  1  | Oficina                 |\n"
                   "|  2  | Clientes                |\n"
                   "|  3  | Veículos               |\n"
                   "|  4  | Peças                  |\n"
                   "|  5  | Fornecedores            |\n"
                   "|  6  | Serviços               |\n"
                   "|  7  | Funcionários           |\n"
                   "|  8  | Voltar                  |\n"
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
                         listarFornecedor(&listaFornecedores);
                         break;
                     case 6:
                         break;
                     case 7:
                         break;
                     case 8:
                         break;
                default: printf("Opção inválida!\n\n");
                };

                break;
            case 5:
                return 0;
            default: printf("Opção inválida!\n\n");
        }
    } while(opcaoMenu != 5);

}