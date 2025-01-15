#include "modelFuncionarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../agendamentos/modelAgendamentos.h"

// Busca os dados de funcionários nos arquivos
void buscarDadosFuncionariosModel(struct ListaFuncionarios *lista, int opcaoArmazenamento) {
    int i = 0;
    FILE *dadosFuncionarios;
    char linha[sizeof(struct Funcionarios)];

    switch (opcaoArmazenamento) {
        case 1:
            dadosFuncionarios = fopen("DadosFuncionarios.txt", "r");

            if (dadosFuncionarios == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosFuncionarios)) {
                lista->qtdFuncionarios++;
            }

            if (lista->qtdFuncionarios > 0) {
                lista->listaFuncionarios = malloc(lista->qtdFuncionarios * sizeof(struct Funcionarios));
            } else {
                fclose(dadosFuncionarios);
                return;
            }

            if (lista->listaFuncionarios == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosFuncionarios);
                return;
            }

            fseek(dadosFuncionarios, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosFuncionarios)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaFuncionarios[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFuncionarios[i].nome, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFuncionarios[i].cpf, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFuncionarios[i].cargo, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaFuncionarios[i].salario = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaFuncionarios[i].idOficina = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaFuncionarios[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosFuncionarios = fopen("DadosFuncionarios.bin", "rb");

            if (dadosFuncionarios == NULL) {
                return;
            }

            struct Funcionarios linhaFuncionario;

            while (fread(&linhaFuncionario, sizeof(linhaFuncionario), 1, dadosFuncionarios)) {
                lista->qtdFuncionarios++;
            }

            if (lista->qtdFuncionarios > 0) {
                lista->listaFuncionarios = malloc(lista->qtdFuncionarios * sizeof(struct Funcionarios));
            } else {
                fclose(dadosFuncionarios);
                return;
            }

            if (lista->listaFuncionarios == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosFuncionarios);
                return;
            }

            fseek(dadosFuncionarios, 0, SEEK_SET);

            while (fread(&linhaFuncionario, sizeof(linhaFuncionario), 1, dadosFuncionarios)) {
                lista->listaFuncionarios[i] = linhaFuncionario;
                i++;
            }
            break;
    }

    fclose(dadosFuncionarios);
}

// Armazena os dados de funcionários nos arquivos
void armazenarDadosFuncionariosModel(struct ListaFuncionarios *lista, int opcaoArmazenamento) {
    FILE *dadosFuncionarios;

    switch (opcaoArmazenamento) {
        case 1:
            dadosFuncionarios = fopen("DadosFuncionarios.txt", "w");

            if (dadosFuncionarios == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdFuncionarios; i++) {
                fprintf(dadosFuncionarios, "%d;%s;%s;%s;%.2f;%d;%d\n",
                        lista->listaFuncionarios[i].id,
                        lista->listaFuncionarios[i].nome,
                        lista->listaFuncionarios[i].cpf,
                        lista->listaFuncionarios[i].cargo,
                        lista->listaFuncionarios[i].salario,
                        lista->listaFuncionarios[i].idOficina,
                        lista->listaFuncionarios[i].deletado);
            }

            break;
        case 2:
            dadosFuncionarios = fopen("DadosFuncionarios.bin", "wb");

            if (dadosFuncionarios == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdFuncionarios; i++) {
                fwrite(&lista->listaFuncionarios[i], sizeof(struct Funcionarios), 1, dadosFuncionarios);
            }
            break;
    }

    fclose(dadosFuncionarios);
    free(lista->listaFuncionarios);
    lista->qtdFuncionarios = 0;
}

// Aloca memória inicial na lista de funcionários
int alocarFuncionariosModel(struct ListaFuncionarios *lista) {
    lista->qtdFuncionarios = 1;
    lista->listaFuncionarios = malloc(sizeof(struct Funcionarios));

    if (lista->listaFuncionarios == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de funcionários conforme a necessidade em qtdAlocada
int realocarFuncionariosModel(struct ListaFuncionarios *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhuma alocação foi realizada\n\n");
        return 0;
    }

    lista->qtdFuncionarios += qtdAlocada;
    lista->listaFuncionarios = realloc(lista->listaFuncionarios, lista->qtdFuncionarios * sizeof(struct Funcionarios));

    if (lista->listaFuncionarios == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra um novo funcionário
void cadastrarFuncionariosModel(struct ListaFuncionarios *lista, struct Funcionarios *funcionario) {
    int resultAlocacao = 0;

    if (lista->qtdFuncionarios == 0) {
        lista->qtdFuncionarios++;
        resultAlocacao = alocarFuncionariosModel(lista);
    } else {
        resultAlocacao = realocarFuncionariosModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o funcionário.\n\n");
        return;
    }

    funcionario->id = lista->qtdFuncionarios;
    funcionario->deletado = 0;

    lista->listaFuncionarios[lista->qtdFuncionarios - 1] = *funcionario;

    printf("Funcionário cadastrado com sucesso!\n\n");
}

// Verifica a existência do id requisitado
int verificarIDFuncionariosModel(struct ListaFuncionarios *lista, int id) {
    // Procura o funcionário com o id inserido
    if (lista->qtdFuncionarios > 0) {
        for (int i = 0; i < lista->qtdFuncionarios; i++) {
            if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhuma funcionário foi cadastrado!\n\n");
        return 0;
    }

    printf("Funcionário não encontrado.\n\n");
    return 0;
}

// Atualiza o cadastro de um funcionário
void atualizarFuncionariosModel(struct ListaFuncionarios *lista, int id, struct Funcionarios *funcionario) {
    int encontrado = 0;

    if (lista->qtdFuncionarios == 0) {
        printf("Nenhum funcionário foi cadastrado!\n\n");
        return;
    }

    // Busca pelo id para fazer a alteração
    for (int i = 0; i < lista->qtdFuncionarios; i++) {
        if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
            encontrado = 1;
            lista->listaFuncionarios[i] = *funcionario;
            lista->listaFuncionarios[i].id = id;
            lista->listaFuncionarios[i].deletado = 0;

            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado!\n\n");
    }
}

// Lista todos os funcionários cadastrados
void listarTodosFuncionariosModel(struct ListaFuncionarios *lista) {
    // Variável para verificação de listagem
    int listado = 0;

    // Verifica se há pelo menos um cadastro
    if (lista->qtdFuncionarios > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdFuncionarios; i++) {
            // Verifica se o índice atual existe
            if (lista->listaFuncionarios[i].deletado == 0) {
                listado = 1;
                printf("\n======================="
                       "\n| FUNCIONÁRIO %d       |"
                       "\n======================="
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nCARGO: %s"
                       "\nSALÁRIO: %.2f"
                       "\nOFICINA: %d\n",
                       lista->listaFuncionarios[i].id,
                       lista->listaFuncionarios[i].nome,
                       lista->listaFuncionarios[i].cpf,
                       lista->listaFuncionarios[i].cargo,
                       lista->listaFuncionarios[i].salario,
                       lista->listaFuncionarios[i].idOficina);
            }
        }
    }

    // Se não houver, avisa que não há cadastros
    if (listado == 0) {
        printf("Nenhum funcionário cadastrado\n\n");
    }
}

// Lista um funcionário pelo Id
void listarFuncionariosModel(struct ListaFuncionarios *lista, int id) {
    // Variável para verificar que cliente foi encontrado
    int encontrado = 0;

    if (lista->qtdFuncionarios == 0) {
        printf("Nenhum funcionário foi cadastrado!\n\n");
        return;
    }

    // Se há um ou mais cadastros, procura pelo funcionário com o id desejado
    for (int i = 0; i < lista->qtdFuncionarios; i++) {
        // Verifica se o funcionário está ou não deletado
        if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
            encontrado = 1;
            if (lista->listaFuncionarios[i].deletado == 0) {
                printf("\n======================="
                       "\n| FUNCIONÁRIO %d       |"
                       "\n======================="
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nCARGO: %s"
                       "\nSALÁRIO: %.2f"
                       "\nOFICINA: %d\n",
                       lista->listaFuncionarios[i].id,
                       lista->listaFuncionarios[i].nome,
                       lista->listaFuncionarios[i].cpf,
                       lista->listaFuncionarios[i].cargo,
                       lista->listaFuncionarios[i].salario,
                       lista->listaFuncionarios[i].idOficina);
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado!\n\n");
    }
}

// Lista os funcionários relacionados a uma oficina, buscando pelo idOficina
void buscarFuncionarioPorOficinaModel(struct ListaFuncionarios *lista, int idOficina) {
    int encontrado = 0;

    if (lista->qtdFuncionarios > 0) {
        for (int i = 0; i < lista->qtdFuncionarios; i++) {
            if (lista->listaFuncionarios[i].idOficina == idOficina && lista->listaFuncionarios[i].deletado == 0) {
                encontrado = 1;
                printf("\n======================="
                       "\n| FUNCIONÁRIO %d       |"
                       "\n======================="
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nCARGO: %s"
                       "\nSALÁRIO: %.2f"
                       "\nOFICINA: %d\n",
                       lista->listaFuncionarios[i].id,
                       lista->listaFuncionarios[i].nome,
                       lista->listaFuncionarios[i].cpf,
                       lista->listaFuncionarios[i].cargo,
                       lista->listaFuncionarios[i].salario,
                       lista->listaFuncionarios[i].idOficina);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum funcionário encontrado.\n\n");
        }
    } else {
        printf("Nenhuma funcionário foi cadastrado.\n\n");
    }
}

// Deleta um funcionário cadastrado
void deletarFuncionariosModel(struct ListaFuncionarios *lista, struct ListaAgendamentos *listaAgendamentos, int id) {
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdFuncionarios == 0) {
        printf("Nenhum funcionário foi cadastrado!\n\n");
        return;
    }

    // Verifica relação com agendamento
    if (listaAgendamentos->qtdAgendamentos > 0) {
        for (int i = 0; i < listaAgendamentos->qtdAgendamentos; i++) {
            if (listaAgendamentos->listaAgendamentos[i].idFuncionario == id && listaAgendamentos->listaAgendamentos[i].deletado == 0) {
                printf(
                    "Não foi possível deletar o funcionário, pois os seus dados estão sendo utilizados em um agendamento que será realizado.\n\n");
                return;
            }
        }
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdFuncionarios; i++) {
        if (lista->listaFuncionarios[i].id == id && lista->listaFuncionarios[i].deletado == 0) {
            encontrado = 1;
            lista->listaFuncionarios[i].deletado = 1;
            printf("Funcionário deletado com sucesso!\n\n");
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Funcionário não encontrado!\n\n");
    }
}

// Verifica se existe uma relação entre o funcionário fornecido e alguma oficina
int verificarRelacaoFuncionarioComOficinaModel(struct ListaFuncionarios *listaFuncionarios,
                                 int idOficina, int idFuncionario) {
    for (int i = 0; i < listaFuncionarios->qtdFuncionarios; i++) {
        if (idFuncionario == listaFuncionarios->listaFuncionarios[i].id && listaFuncionarios->listaFuncionarios[i].idOficina == idOficina) {
            return 1;
        }
    }
    printf("Este funcionário não trabalha para a oficina fornecida!\n\n");
    return 0;
}