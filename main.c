
// Include de bibliotecas do C
#include <stdio.h>
#include <stdlib.h>
#include "./views/fornecedores/viewFornecedores.h"
#include "./models/fornecedores/modelFornecedores.h"
#include "./models/clientes/modelClientes.h"
#include "./views/clientes/viewClientes.h"
#include <locale.h>

// Include de models e views
#include "models/oficina/modelOficina.h"
#include "views/oficina/viewOficina.h"
#include "models/clientes/modelClientes.h"
#include "views/clientes/viewClientes.h"

int main() {
    system("chcp 65001");
    system("cls");
    setlocale(LC_ALL, "PT-BR");

    struct ListaClientes listaClientes;
    listaClientes.qtdClientes = 0;
    // Declaração de variáveis dos dados do sistema
    struct ListaOficinas listaOficinas;
    listaOficinas.qtdOficinas = 0;

    struct ListaFornecedores listaFornecedores;
    listaFornecedores.qtdFornecedores = 0;

    int opcaoMenu, opcaoArmazenamento = 0;

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
                gerenciarClientes(&listaClientes, opcaoArmazenamento);
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

                if (listaClientes.qtdClientes > 0) {
                    free(listaClientes.listaClientes);
                    listaClientes.listaClientes = NULL;
                }
            break;
            default: printf("Opção inválida!\n\n");
             break;
        }
    } while(opcaoMenu != 8);

    return 0;

}