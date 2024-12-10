#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/oficina/modelOficina.h"
#include "viewFuncionarios.h"
#include <stdio.h>
#include <stdlib.h>

// Menu de funcionalidades de funcionários
void gerenciarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas,
                          int opcaoArmazenamento) {
    int opcaoSubmenus;
    //Verifica se o programa esta rodando apenas em memória
    if (opcaoArmazenamento != 3) {
        // Busca os dados armazenados em arquivos
        if (lista->qtdFuncionarios == 0) {
            buscarDadosFuncionariosModel(lista, opcaoArmazenamento);
        }
        // Busca os dados em arquivos das tabelas relacionadas
        if (listaOficinas->qtdOficinas == 0) {
            buscarDadosOficinaModel(listaOficinas, opcaoArmazenamento);
        }
    }

    do {
        printf("\n================================\n"
            "|     MENU DE FUNCIONÁRIOS     |\n"
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

// Formulário de cadastro de funcionários
void cadastrarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas) {
    struct Funcionarios funcionario;
    int idOficina;

    printf("\n================================\n"
        "|    CADASTRO DE FUNCIONÁRIO   |\n"
        "================================\n");

    printf("Insira o ID da oficina onde o funcionário trabalha: ");
    setbuf(stdin, NULL);
    scanf("%d", &idOficina);

    // Verificando existência do item relacionado
    if (verificarIDOficinaModel(listaOficinas, idOficina) == 0) {
        return;
    }

    funcionario.idOficina = idOficina;

    // Preenchimento dos dados
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

// Formulário de atualização de funcionários
void atualizarFuncionario(struct ListaFuncionarios *lista, struct ListaOficinas *listaOficinas) {
    int id, idOficina;
    struct Funcionarios funcionario;

    // Pede o Id do funcionário que será atualizado
    printf("\n=====================================\n"
        "|     ATUALIZAÇÃO DE FUNCIONÁRIO    |\n"
        "=====================================\n"
        "Insira o ID do funcionário que deseja atualizar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);

    // Verifica se o ID inserido existe
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

    //Preenchimento dos dados
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

// Listagem de funcionários
void listarFuncionario(struct ListaFuncionarios *lista) {
    int opcao, id;
    // Pergunta o tipo de listagem
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

    // Verifica a opção de listagem
    switch (opcao) {
        // Listagem de um único fornecedor
        case 1:
            printf("Insira o ID do funcionário que deseja listar: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            listarFuncionariosModel(lista, id);
            break;
        // Listagem por relação
        case 2:
            printf("Insira o ID da oficina desejada para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarFuncionarioPorOficinaModel(lista, id);
            break;
        // Listagem de todos os funcionários
        case 3:
            listarTodosFuncionariosModel(lista);
            break;
        case 4:
            break;
        default: printf("Opção inválida!\n\n");
    }
}

// Formulário de deleção de funcionários
void deletarFuncionario(struct ListaFuncionarios *lista) {
    int id;

    // Pede o Id do funcionário que será deletada
    printf("\n===============================\n"
        "|    DELEÇÃO DE FUNCIONÁRIO   |\n"
        "===============================\n");
    printf("Insira o ID do funcionário que deseja deletar:\n");
    setbuf(stdin, NULL);
    scanf("%d", &id);
    deletarFuncionariosModel(lista, id);
}
