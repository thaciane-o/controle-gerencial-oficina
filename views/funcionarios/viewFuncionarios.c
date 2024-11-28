#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/oficina/modelOficina.h"
#include "viewFuncionarios.h"
#include <stdio.h>
#include <stdlib.h>

void gerenciarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas,
                          int opcaoArmazenamento) {
    int opcaoSubmenus;

    if (opcaoArmazenamento != 3) {
        if (lista->qtdFuncionarios == 0) {
            buscarDadosFuncionariosModel(lista, opcaoArmazenamento);
        }

        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }
    }

    do {
        printf("\n===============================\n"
            "|     MENU DE FUNCIONÁRIO     |\n"
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
                cadastrarFuncionario(lista, listaOficinas);
                break;
            case 2:
                atualizarFuncionario(lista, listaOficinas);
                break;
            case 3:
                deletarFuncionario(lista);
                break;
            case 4:
                listarFuncionario(lista);
                break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    if (lista->qtdFuncionarios > 0) {
                        armazenarDadosFuncionariosModel(lista, opcaoArmazenamento);
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

void cadastrarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas) {
    struct Funcionarios funcionario;
    int idOficina;

    printf("\n================================\n"
        "|    CADASTRO DE FUNCIONÁRIO   |\n"
        "================================\n");

    printf("Insira o ID da oficina onde o funcionário trabalha: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    funcionario.idOficina = idOficina;

    printf("Insira o nome do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.nome);

    printf("Insira o CPF do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cpf);

    printf("Insira o cargo do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cargo);

    printf("Insira o salário do funcionário: R$");
    setbuf(stdin, NULL);
    scanf("%f", &funcionario.salario);

    cadastrarFuncionariosModel(lista, &funcionario);
}

void atualizarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas) {
    int id, idOficina;
    struct Funcionarios funcionario;

    printf("\n=====================================\n"
        "|     ATUALIZAÇÃO DE FUNCIONÁRIO    |\n"
        "=====================================\n"
        "Insira o ID do funcionário que deseja atualizar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    int encontrado = verificarIDFuncionariosModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o ID da oficina onde o funcionário trabalha: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    funcionario.idOficina = idOficina;

    printf("Insira o nome do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.nome);

    printf("Insira o CPF do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cpf);

    printf("Insira o cargo do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cargo);

    printf("Insira o salário do funcionário: R$");
    setbuf(stdin, NULL);
    scanf("%f", &funcionario.salario);

    atualizarFuncionariosModel(lista, id, &funcionario);
}

void listarFuncionario(struct ListaFuncionarios *lista) {
    int opcao, id;

    printf("\n=================================\n"
        "|    LISTAGEM DE FUNCIONÁRIO    |\n"
        "=================================\n"
        "| 1 | Busca por ID              |\n"
        "| 2 | Busca por ID da oficina   |\n"
        "| 3 | Listar todos              |\n"
        "| 4 | Voltar                    |\n"
        "=================================\n"
        "Escolha uma opção: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Insira o ID do funcionário que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarFuncionariosModel(lista, id);
            break;
        case 2:
            printf("Insira o ID da oficina desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarFuncionarioPorOficinaModel(lista, id);
            break;
        case 3:
            listarTodosFuncionariosModel(lista);
            break;
        case 4:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

void deletarFuncionario(struct ListaFuncionarios *lista) {
    int id;

    printf("\n===============================\n"
        "|    DELEÇÃO DE FUNCIONÁRIO   |\n"
        "===============================\n");
    printf("Insira o ID do funcionário que deseja deletar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);
    deletarFuncionariosModel(lista, id);
}
