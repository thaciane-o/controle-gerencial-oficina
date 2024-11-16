#include "../../models/funcionarios/modelFuncionarios.h"
#include "viewFuncionarios.h"
#include <stdio.h>

void gerenciarFuncionario(struct ListaFuncionarios *lista, int opcaoArmazenamento) {
    int opcaoSubmenus;

    if (lista->qtdFuncionarios == 0 && opcaoArmazenamento != 3) {
        buscarDadosFuncionariosModel(lista, opcaoArmazenamento);
    }

    do {
        printf("================================\n"
            "|    SUBMENU DE FUNCIONÁRIO    |\n"
            "================================\n"
            "|  1  | Cadastrar              |\n"
            "|  2  | Atualizar              |\n"
            "|  3  | Deletar                |\n"
            "|  4  | Listar                 |\n"
            "|  5  | Voltar                 |\n"
            "=================================\n"
            "Escolha uma opção: \n");
        scanf("%d", &opcaoSubmenus);

        switch (opcaoSubmenus) {
            case 1:
                cadastrarFuncionario(lista);
            break;
            case 2:
                atualizarFuncionario(lista);
            break;
            case 3:
                deletarFuncionario(lista);
            break;
            case 4:
                listarFuncionario(lista);
            break;
            case 5:
                if (opcaoArmazenamento != 3) {
                    armazenarDadosFuncionariosModel(lista, opcaoArmazenamento);
                }
                return;
            default: printf("Opção inválida!\n\n");
            break;
        };
    } while (opcaoSubmenus != 5);
}

void cadastrarFuncionario(struct ListaFuncionarios *lista) {
    struct Funcionarios funcionario;

    printf("\n================================\n"
             "|    CADASTRO DE FUNCIONÁRIO   |\n"
             "================================\n");

    printf("Insira o nome do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.nome);

    printf("Insira o CPF do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cpf);

    printf("Insira o cargo do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cargo);

    printf("Insira o salário do funcionário: ");
    setbuf(stdin, NULL);
    scanf("%f", &funcionario.salario);

    cadastrarFuncionariosModel(lista, &funcionario);
}

void atualizarFuncionario(struct ListaFuncionarios *lista) {
    int id;
    struct Funcionarios funcionario;

    printf("\n======================================\n"
          "|     ATUALIZAÇÃO DE FUNCIONÁRIO    |\n"
          "======================================\n"
          "Insira o ID do funcionário que deseja atualizar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    int encontrado = verificarIDFuncionariosModel(lista, id);
    if (encontrado == 0) {
        return;
    }

    printf("Insira o nome do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.nome);

    printf("Insira o CPF do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cpf);

    printf("Insira o cargo do funcionário: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", funcionario.cargo);

    printf("Insira o salário do funcionário: ");
    setbuf(stdin, NULL);
    scanf("%f", &funcionario.salario);

    atualizarFuncionariosModel(lista, id, &funcionario);
}

void listarFuncionario(struct ListaFuncionarios *lista) {
    int opcao, id;

    printf("\n=================================\n"
            "|     LISTAGEM DE FUNCIONÁRIO    |\n"
            "=================================\n"
            "1. Listar um único funcionário"
            "\n2. Listar todos"
            "\n3. Voltar\n");
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
            listarTodosFuncionariosModel(lista);
            break;
        case 3:
            return;
            break;
        default: printf("Opção inválida!\n\n");
    }
    
}

void deletarFuncionario(struct ListaFuncionarios *lista) {
    int id;

    printf("\n================================\n"
             "|    DELEÇÃO DE FUNCIONÁRIO   |\n"
             "================================\n");
    printf("Insira o ID do funcionário que deseja deletar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);
    deletarFuncionariosModel(lista, id);
}