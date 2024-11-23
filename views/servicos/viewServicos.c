#include "../../models/servicos/modelServicos.h"
#include "../../models/oficina/modelOficina.h"
#include "viewServicos.h"
#include <stdio.h>
#include <stdlib.h>

void gerenciarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas, int opcaoArmazenamento) {
    int opcaoSubmenus;

    if (opcaoArmazenamento != 3) {
        if (lista->qtdServicos == 0) {
            buscarDadosServicoModel(lista, opcaoArmazenamento);
        }

        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }

    }

    do {
        printf("\n================================\n"
            "|     SUBMENU DE SERVIÇOS      |\n"
            "================================\n"
            "|  1  | Cadastrar              |\n"
            "|  2  | Atualizar              |\n"
            "|  3  | Deletar                |\n"
            "|  4  | Listar                 |\n"
            "|  5  | Voltar                 |\n"
            "================================\n"
            "Escolha uma opção: \n");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarServico(lista, listaOficinas);
            break;
            case 2:
                atualizarServico(lista, listaOficinas);
            break;
            case 3:
                deletarServico(lista);
            break;
            case 4:
                listarServico(lista);
            break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (lista->qtdServicos > 0) {
                        armazenarDadosServicoModel(lista, opcaoArmazenamento);
                    }

                    if (listaOficinas->qtdOficinas > 0) {
                        free(listaOficinas->listaOficinas);
                        listaOficinas->listaOficinas = NULL;
                        listaOficinas->qtdOficinas = 0;
                    }
                }
            break;
            default: printf("Opção inválida!\n\n");
            break;
        };
    } while (opcaoSubmenus != 5);
}

void cadastrarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas) {
    struct Servicos servico;
    int idOficina;

    printf("\n================================\n"
        "|     CADASTRO DE SERVIÇO     |\n"
        "================================\n");

    printf("Insira o ID da oficina que fornece o serviço: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    servico.idOficina = idOficina;


    printf("Insira a descrição do serviço: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", servico.descricao);

    printf("Insira o preço do serviço: ");
    setbuf(stdin, NULL);
    scanf(" %f", &servico.preco);

    printf("Insira a comissão do serviço: ");
    setbuf(stdin, NULL);
    scanf(" %f", &servico.comissao);


    cadastrarServicoModel(lista, &servico);
}

void deletarServico(struct ListaServicos *lista) {
    int id;

    printf("\n==============================\n"
        "|    DELEÇÃO DE SERVIÇO      |\n"
        "==============================\n");
    printf("Insira o ID do serviço que deseja deletar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);
    deletarServicoModel(lista, id);
}

void listarServico(struct ListaServicos *lista) {
    int opcao, id;

    printf("\n==================================\n"
        "|     LISTAGEM DE SERVIÇOS       |\n"
        "==================================\n"
        "| 1 | Busca por ID               |\n"
        "| 2 | Busca por ID da oficina    |\n"
        "| 3 | Listar todos               |\n"
        "| 4 | Voltar                     |\n"
        "==================================\n"
        "Escolha uma opção: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Insira o ID do serviço que deseja listar: ");
        setbuf(stdin, NULL);
        scanf("%d", &id);
        listarServicoModel(lista, id);
        break;
        case 2:
            printf("Insira o ID da oficina desejado para a busca: ");
        setbuf(stdin, NULL);
        scanf("%d", &id);
        buscarServicosPorOficinaModel(lista, id);
        break;
        case 3:
            listarTodosServicoModel(lista);
        break;
        case 4:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

void atualizarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas) {
    int id, idOficina;
    struct Servicos servico;

    printf("\n==================================\n"
        "|     ATUALIZAÇÃO DE SERVIÇO     |\n"
        "==================================\n"
        "Insira o ID do serviço que deseja atualizar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    int encontrado = verificarIDServicoModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o ID da oficina que possui este serviço: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    servico.idOficina = idOficina;


    printf("Insira a descrição do serviço: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", servico.descricao);

    printf("Insira o preço do serviço: ");
    setbuf(stdin, NULL);
    scanf(" %f", &servico.preco);

    printf("Insira a comissão do serviço: ");
    setbuf(stdin, NULL);
    scanf(" %f", &servico.comissao);

    atualizarServicoModel(lista, id, &servico);
}