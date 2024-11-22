// Include de bibliotecas do C
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Include de models e views

#include "models/clientes/modelClientes.h"
#include "views/clientes/viewClientes.h"

#include "views/veiculos/viewVeiculos.h"
#include "models/veiculos/modelVeiculos.h"

#include "views/oficina/viewOficina.h"
#include "models/oficina/modelOficina.h"

#include "views/pecas/viewPecas.h"
#include "models/pecas/modelPecas.h"

#include "views/fornecedores/viewFornecedores.h"
#include "models/fornecedores/modelFornecedores.h"

#include "./views/funcionarios/viewFuncionarios.h"
#include "./models/funcionarios/modelFuncionarios.h"

#include "./views/servicos/viewServicos.h"
#include "./models/servicos/modelServicos.h"

int main() {
    // Configuração para caracteres especiais
    system("chcp 65001");
    system("cls");
    setlocale(LC_ALL, "PT-BR");

    // Declaração de variáveis dos dados do sistema
    struct ListaClientes listaClientes;
    listaClientes.qtdClientes = 0;

    struct ListaVeiculos listaVeiculos;
    listaVeiculos.listaVeiculos = NULL;
    listaVeiculos.qtdVeiculos = 0;

    struct ListaOficinas listaOficinas;
    listaOficinas.qtdOficinas = 0;

    struct ListaPecas listaPecas;
    listaPecas.qtdPecas = 0;

    struct ListaFornecedores listaFornecedores;
    listaFornecedores.qtdFornecedores = 0;

    struct ListaServicos listaServicos;
    listaServicos.qtdServicos = 0;

    struct ListaFuncionarios listaFuncionarios;
    listaFuncionarios.qtdFuncionarios = 0;

    // Variáveis de controle do sistema
    int opcaoMenu, opcaoArmazenamento = 0;

    // Configuração de armazenamento inicial
    do {
        printf("Como deseja armazenar?\n"
            "1. Texto\n"
            "2. Binário\n"
            "3. Memória\n"
            "Escolha uma opção: ");
        scanf("%d", &opcaoArmazenamento);
    } while (opcaoArmazenamento < 1 || opcaoArmazenamento > 3);

    // Menu principal do sistema
    do {
        printf("\n=================================\n"
            "|         MENU PRINCIPAL        |\n"
            "=================================\n"
            "|  1  | Oficina                 |\n"
            "|  2  | Clientes                |\n"
            "|  3  | Veículos                |\n"
            "|  4  | Peças                   |\n"
            "|  5  | Fornecedores            |\n"
            "|  6  | Serviços                |\n"
            "|  7  | Funcionários            |\n"
            "|  8  | Sair                    |\n"
            "=================================\n"
            "Escolha uma opção:\n");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {
            case 1:
                gerenciarOficina(&listaOficinas, &listaFuncionarios, opcaoArmazenamento);
                break;
            case 2:
                gerenciarClientes(&listaClientes, &listaVeiculos, &listaOficinas, opcaoArmazenamento);
                break;
            case 3:
                gerenciarVeiculos(&listaClientes, &listaVeiculos, opcaoArmazenamento);
                break;
            case 4:
                gerenciarPeca(&listaPecas, &listaFornecedores, opcaoArmazenamento);
                break;
            case 5:
                gerenciarFornecedor(&listaFornecedores, &listaPecas, opcaoArmazenamento);
                break;
            case 6:
                gerenciarServico(&listaServicos, &listaOficinas, opcaoArmazenamento);
                break;
            case 7:
                gerenciarFuncionario(&listaFuncionarios, &listaOficinas, opcaoArmazenamento);
                break;
            case 8:
                if (listaClientes.qtdClientes > 0) {
                    free(listaClientes.listaClientes);
                    listaClientes.listaClientes = NULL;
                }

                if (listaPecas.qtdPecas > 0) {
                    free(listaPecas.listaPecas);
                    listaPecas.listaPecas = NULL;
                }

                if (listaOficinas.qtdOficinas > 0) {
                    free(listaOficinas.listaOficinas);
                    listaOficinas.listaOficinas = NULL;
                }

                if (listaPecas.qtdPecas > 0) {
                    free(listaPecas.listaPecas);
                    listaPecas.listaPecas = NULL;
                }

                if (listaFornecedores.qtdFornecedores > 0) {
                    free(listaFornecedores.listaFornecedores);
                    listaFornecedores.listaFornecedores = NULL;
                }

                if (listaServicos.qtdServicos > 0) {
                    free(listaServicos.listaServicos);
                    listaServicos.listaServicos = NULL;
                }

                if (listaFuncionarios.qtdFuncionarios > 0) {
                    free(listaFuncionarios.listaFuncionarios);
                    listaFuncionarios.listaFuncionarios = NULL;
                }
                break;
            default: printf("Opção inválida!\n\n");
                break;
        }
    } while (opcaoMenu != 8);

    return 0;
}
