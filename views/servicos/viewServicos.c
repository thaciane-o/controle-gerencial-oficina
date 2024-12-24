#include "../../models/servicos/modelServicos.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "viewServicos.h"
#include <stdio.h>
#include <stdlib.h>

// Menu de funcionalidades de serviços
void gerenciarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas,
                      struct ListaAgendamentos *listaAgendamentos, int opcaoArmazenamento) {
    int opcaoSubmenus;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdServicos == 0) {
            buscarDadosServicoModel(lista, opcaoArmazenamento);
        }

        // Busca os dados em arquivos das tabelas relacionadas
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }

        if (lista->qtdServicos > 0) {
            buscarDadosAgendamentosModel(listaAgendamentos, opcaoArmazenamento);
        }
    }

    do {
        printf("\n===============================\n"
            "|      MENU DE SERVIÇOS       |\n"
            "===============================\n"
            "|  1  | Cadastrar             |\n"
            "|  2  | Atualizar             |\n"
            "|  3  | Deletar               |\n"
            "|  4  | Listar                |\n"
            "|  5  | Voltar                |\n"
            "===============================\n"
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
                deletarServico(lista, listaAgendamentos);
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

// Formulário de cadastro de serviços
void cadastrarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas) {
    struct Servicos servico;
    int idOficina;

    printf("\n================================\n"
        "|     CADASTRO DE SERVIÇO     |\n"
        "================================\n");

    printf("Insira o ID da oficina que fornece o serviço: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    // Verificando existência do item relacionado
    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    servico.idOficina = idOficina;

    // Preenchimento dos dados
    printf("Insira a descrição do serviço: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", servico.descricao);

    printf("Insira o preço do serviço: R$");
    setbuf(stdin, NULL);
    scanf(" %f", &servico.preco);

    printf("Insira a comissão do serviço: R$");
    setbuf(stdin, NULL);
    scanf(" %f", &servico.comissao);


    cadastrarServicoModel(lista, &servico);
}

// Formulário de atualização de serviços
void atualizarServico(struct ListaServicos *lista, struct ListaOficinas *listaOficinas) {
    int id, idOficina;
    struct Servicos servico;

    // Pede o Id do serviço que será atualizado
    printf("\n==================================\n"
        "|     ATUALIZAÇÃO DE SERVIÇO     |\n"
        "==================================\n"
        "Insira o ID do serviço que deseja atualizar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    // Verifica se o ID inserido existe
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

    //Preenchimento dos dados
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

// Listagem de serviços
void listarServico(struct ListaServicos *lista) {
    int opcao, id;
    // Pergunta o tipo de listagem
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

    // Verifica a opção de listagem
    switch (opcao) {
        // Listagem de um único serviço
        case 1:
            printf("Insira o ID do serviço que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarServicoModel(lista, id);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID da oficina desejada para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarServicosPorOficinaModel(lista, id);
            break;
        // Listagem de todos os serviços
        case 3:
            listarTodosServicoModel(lista);
            break;
        case 4:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

// Formulário de deleção de serviços
void deletarServico(struct ListaServicos *lista, struct ListaAgendamentos *listaAgendamentos) {
    int id;

    // Pede o Id do serviço que será deletada
    printf("\n==============================\n"
        "|    DELEÇÃO DE SERVIÇO      |\n"
        "==============================\n");
    printf("Insira o ID do serviço que deseja deletar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);
    deletarServicoModel(lista, listaAgendamentos, id);
}
