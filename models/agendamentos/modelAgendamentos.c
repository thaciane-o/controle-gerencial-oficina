#include "modelAgendamentos.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca os dados de agendamentos nos arquivos
void buscarDadosAgendamentosModel(struct ListaAgendamentos *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosAgendamentos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosAgendamentos = fopen("DadosAgendamentos.txt", "r");

            if (dadosAgendamentos == NULL) {
                return;
            }

            char linha[sizeof(struct Agendamentos)];

            while (fgets(linha, sizeof(linha), dadosAgendamentos)) {
                lista->qtdAgendamentos++;
            }

            if (lista->qtdAgendamentos > 0) {
                lista->listaAgendamentos = malloc(lista->qtdAgendamentos * sizeof(struct Agendamentos));
            } else {
                fclose(dadosAgendamentos);
                return;
            }

            if (lista->listaAgendamentos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosAgendamentos);
                return;
            }

            fseek(dadosAgendamentos, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosAgendamentos)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaAgendamentos[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaAgendamentos[i].datahoraInicial, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].idFuncionario = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].idServico = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].idVeiculo = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].finalizado = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaAgendamentos[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosAgendamentos = fopen("DadosAgendamentos.bin", "rb");

            if (dadosAgendamentos == NULL) {
                return;
            }

            struct Agendamentos linhaAgendamento;

            while (fread(&linhaAgendamento, sizeof(linhaAgendamento), 1, dadosAgendamentos)) {
                lista->qtdAgendamentos++;
            }

            if (lista->qtdAgendamentos > 0) {
                lista->listaAgendamentos = malloc(lista->qtdAgendamentos * sizeof(struct Agendamentos));
            } else {
                fclose(dadosAgendamentos);
                return;
            }

            if (lista->listaAgendamentos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosAgendamentos);
                return;
            }

            fseek(dadosAgendamentos, 0, SEEK_SET);

            while (fread(&linhaAgendamento, sizeof(linhaAgendamento), 1, dadosAgendamentos)) {
                lista->listaAgendamentos[i] = linhaAgendamento;
                i++;
            }

            break;
    }
    fclose(dadosAgendamentos);
}

// Armazena os dados de agendamentos nos arquivos
void armazenarDadosAgendamentosModel(struct ListaAgendamentos *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosAgendamentos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosAgendamentos = fopen("DadosAgendamentos.txt", "w");

            if (dadosAgendamentos == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdAgendamentos; i++) {
                fprintf(dadosAgendamentos, "%d;%s;%d;%d;%d;%d;%d\n",
                        lista->listaAgendamentos[i].id,
                        lista->listaAgendamentos[i].datahoraInicial,
                        lista->listaAgendamentos[i].idFuncionario,
                        lista->listaAgendamentos[i].idServico,
                        lista->listaAgendamentos[i].idVeiculo,
                        lista->listaAgendamentos[i].finalizado,
                        lista->listaAgendamentos[i].deletado);
            }
            break;
        case 2:
            dadosAgendamentos = fopen("DadosAgendamentos.bin", "wb");

            if (dadosAgendamentos == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdAgendamentos; i++) {
                fwrite(&lista->listaAgendamentos[i], sizeof(struct Agendamentos), 1, dadosAgendamentos);
            }
            break;
    }
    fclose(dadosAgendamentos);

    free(lista->listaAgendamentos);
    lista->listaAgendamentos = NULL;

    lista->qtdAgendamentos = 0;
}

// Aloca memória inicial na lista de agendamentos
int alocarAgendamentosModel(struct ListaAgendamentos *lista) {
    lista->qtdAgendamentos = 1;
    lista->listaAgendamentos = malloc(sizeof(struct Agendamentos));

    if (lista->listaAgendamentos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de agendamentos conforme a necessidade em qtdAlocada
int realocarAgendamentosModel(struct ListaAgendamentos *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdAgendamentos += qtdAlocada;
    lista->listaAgendamentos = realloc(lista->listaAgendamentos, lista->qtdAgendamentos * sizeof(struct Agendamentos));

    if (lista->listaAgendamentos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra um novo agendamento
void cadastrarAgendamentosModel(struct ListaAgendamentos *lista, struct Agendamentos *agendamento, int autoId) {
    int resultAlocacao = 0;

    if (lista->qtdAgendamentos == 0) {
        lista->qtdAgendamentos++;
        resultAlocacao = alocarAgendamentosModel(lista);
    } else {
        resultAlocacao = realocarAgendamentosModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível realizar o Agendamento.\n\n");
        return;
    }

    //Cadastrando agendamento na memória
    if (autoId == 1) {
        agendamento->id = lista->qtdAgendamentos;
        agendamento->deletado = 0;
        agendamento->finalizado = 0;
    }

    lista->listaAgendamentos[lista->qtdAgendamentos - 1] = *agendamento;
}

// Verifica a existência do id requisitado
int verificarIDAgendamentoModel(struct ListaAgendamentos *lista, int id) {
    // Procura o agendamento com o id inserido
    if (lista->qtdAgendamentos > 0) {
        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            if (lista->listaAgendamentos[i].id == id && lista->listaAgendamentos[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhum agendamento foi realizado!\n\n");
        return 0;
    }

    printf("Agendamento não encontrado!\n\n");

    return 0;
}

// Lista todos os agendamentos
void listarTodosAgendamentosModel(struct ListaAgendamentos *lista, struct ListaOrdensServico *listaOrdensServico) {
    // Variável para verificação de listagem
    int listado = 0;
    char finalizado[2][5] = {"Não", "Sim"};

    // Verifica se há pelo menos um cadastro
    if (lista->qtdAgendamentos > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            // Verifica se o agendamento esta deletado
            if (lista->listaAgendamentos[i].deletado == 0) {
                listado = 1;

                printf("\n====================="
                       "\n| AGENDAMENTO %d     |"
                       "\n====================="
                       "\nDATA E HORA INICIADA: %s"
                       "\nSERVIÇO: %d"
                       "\nVEÍCULO: %d"
                       "\nFINALIZADO: %s"
                       "\nFUNCIONÁRIO: %d\n",
                       lista->listaAgendamentos[i].id,
                       lista->listaAgendamentos[i].datahoraInicial,
                       lista->listaAgendamentos[i].idServico,
                       lista->listaAgendamentos[i].idVeiculo,
                       finalizado[lista->listaAgendamentos[i].finalizado],
                       lista->listaAgendamentos[i].idFuncionario);

                // Listando ordens de serviço
                listarOrdensServicoModel(listaOrdensServico, lista->listaAgendamentos[i].id);
            }
        }
    }

    // Se não houver, avisa que não há cadastros
    if (listado == 0) {
        printf("Nenhum agendamento realizado.\n\n");
    }
}

// Lista um agendamento pelo Id
void listarAgendamentoModel(struct ListaAgendamentos *lista, int id, struct ListaOrdensServico *listaOrdensServico) {
    // Variável para verificar que agendamento foi encontrado
    int encontrado = 0;
    char finalizado[2][5] = {"Não", "Sim"};

    if (lista->qtdAgendamentos == 0) {
        printf("Nenhum agendamento foi realizado!\n\n");
        return;
    }
    // Se há um ou mais cadastros, procura pelo agendamento com o id desejado
    for (int i = 0; i < lista->qtdAgendamentos; i++) {
        // Verifica se o agendamento está ou não deletado
        if (lista->listaAgendamentos[i].id == id && lista->listaAgendamentos[i].deletado == 0) {
            printf("\n====================="
                   "\n| AGENDAMENTO %d     |"
                   "\n====================="
                   "\nDATA E HORA INICIADA: %s"
                   "\nSERVIÇO: %d"
                   "\nVEÍCULO: %d"
                   "\nFINALIZADO: %s"
                   "\nFUNCIONÁRIO: %d\n",
                   lista->listaAgendamentos[i].id,
                   lista->listaAgendamentos[i].datahoraInicial,
                   lista->listaAgendamentos[i].idServico,
                   lista->listaAgendamentos[i].idVeiculo,
                   finalizado[lista->listaAgendamentos[i].finalizado],
                   lista->listaAgendamentos[i].idFuncionario);

            // Listando ordens de serviço
            listarOrdensServicoModel(listaOrdensServico, lista->listaAgendamentos[i].id);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Agendamento não encontrado!\n\n");
    }
}

// Lista os agendamentos relacionados a um serviço, buscando pelo idServico
void buscarAgendamentosPorServicoModel(struct ListaAgendamentos *lista, int idServico,
                                       struct ListaOrdensServico *listaOrdensServico) {
    int encontrado = 0;
    char finalizado[2][5] = {"Não", "Sim"};

    if (lista->qtdAgendamentos > 0) {
        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            if (lista->listaAgendamentos[i].idServico == idServico && lista->listaAgendamentos[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================="
                       "\n| AGENDAMENTO %d     |"
                       "\n====================="
                       "\nDATA E HORA INICIADA: %s"
                       "\nSERVIÇO: %d"
                       "\nVEÍCULO: %d"
                       "\nFINALIZADO: %s"
                       "\nFUNCIONÁRIO: %d\n",
                       lista->listaAgendamentos[i].id,
                       lista->listaAgendamentos[i].datahoraInicial,
                       lista->listaAgendamentos[i].idServico,
                       lista->listaAgendamentos[i].idVeiculo,
                       finalizado[lista->listaAgendamentos[i].finalizado],
                       lista->listaAgendamentos[i].idFuncionario);

                // Listando ordens de serviço
                listarOrdensServicoModel(listaOrdensServico, lista->listaAgendamentos[i].id);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum agendamento encontrado.\n\n");
        }
    } else {
        printf("Nenhum agendamento foi encontrado.\n\n");
    }
}

// Lista os agendamentos relacionados a um funcionário, buscando pelo idFuncionario
void buscarAgendamentosPorFuncionarioModel(struct ListaAgendamentos *lista, int idFuncionario,
                                           struct ListaOrdensServico *listaOrdensServico) {
    int encontrado = 0;
    char finalizado[2][5] = {"Não", "Sim"};

    if (lista->qtdAgendamentos > 0) {
        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            if (lista->listaAgendamentos[i].idServico == idFuncionario && lista->listaAgendamentos[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================="
                       "\n| AGENDAMENTO %d     |"
                       "\n====================="
                       "\nDATA E HORA INICIADA: %s"
                       "\nSERVIÇO: %d"
                       "\nVEÍCULO: %d"
                       "\nFINALIZADO: %s"
                       "\nFUNCIONÁRIO: %d\n",
                       lista->listaAgendamentos[i].id,
                       lista->listaAgendamentos[i].datahoraInicial,
                       lista->listaAgendamentos[i].idServico,
                       lista->listaAgendamentos[i].idVeiculo,
                       finalizado[lista->listaAgendamentos[i].finalizado],
                       lista->listaAgendamentos[i].idFuncionario);

                // Listando ordens de serviço
                listarOrdensServicoModel(listaOrdensServico, lista->listaAgendamentos[i].id);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum agendamento encontrado.\n\n");
        }
    } else {
        printf("Nenhum agendamento foi encontrado.\n\n");
    }
}

// Lista os agendamentos relacionados a um veículo, buscando pelo idVeiculo
void buscarAgendamentosPorVeiculoModel(struct ListaAgendamentos *lista, int idVeiculo,
                                       struct ListaOrdensServico *listaOrdensServico) {
    int encontrado = 0;
    char finalizado[2][5] = {"Não", "Sim"};

    if (lista->qtdAgendamentos > 0) {
        for (int i = 0; i < lista->qtdAgendamentos; i++) {
            if (lista->listaAgendamentos[i].idServico == idVeiculo && lista->listaAgendamentos[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================="
                       "\n| AGENDAMENTO %d     |"
                       "\n====================="
                       "\nDATA E HORA INICIADA: %s"
                       "\nSERVIÇO: %d"
                       "\nVEÍCULO: %d"
                       "\nFINALIZADO: %s"
                       "\nFUNCIONÁRIO: %d\n",
                       lista->listaAgendamentos[i].id,
                       lista->listaAgendamentos[i].datahoraInicial,
                       lista->listaAgendamentos[i].idServico,
                       lista->listaAgendamentos[i].idVeiculo,
                       finalizado[lista->listaAgendamentos[i].finalizado],
                       lista->listaAgendamentos[i].idFuncionario);

                // Listando ordens de serviço
                listarOrdensServicoModel(listaOrdensServico, lista->listaAgendamentos[i].id);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum agendamento encontrado.\n\n");
        }
    } else {
        printf("Nenhum agendamento foi encontrado.\n\n");
    }
}

// Deleta um agendamento cadastrado
void deletarAgendamentosModel(struct ListaAgendamentos *lista, int id, struct ListaOrdensServico *listaOrdensServico) {
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdAgendamentos == 0) {
        printf("Nenhum agendamento foi realizado!\n\n");
        return;
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdAgendamentos; i++) {
        if (lista->listaAgendamentos[i].id == id && lista->listaAgendamentos[i].deletado == 0) {
            encontrado = 1;

            lista->listaAgendamentos[i].deletado = 1;

            printf("Agendamento cancelado com sucesso!\n\n");

            // Deletando ordens de serviço relacionadas ao agendamento (cascade)
            for (int j = 0; j < listaOrdensServico->qtdOrdensServico; j++) {
                if (listaOrdensServico->listaOrdensServico[j].idAgendamento == id) {
                    deletarOrdensServicoModel(listaOrdensServico, id);
                }
            }
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Agendamento não encontrado!\n\n");
    }
}

// Atualizar o agendamento ao ser finalizado
void finalizarAgendamentoModel(struct ListaAgendamentos *lista, int id) {
    // Verifica se há algum cadastro
    if (lista->qtdAgendamentos == 0) {
        printf("Nenhum agendamento foi realizado!\n\n");
        return;
    }

    // Busca pelo id para fazer a alteração
    for (int i = 0; i < lista->qtdAgendamentos; i++) {
        if (lista->listaAgendamentos[i].id == id && lista->listaAgendamentos[i].deletado == 0 && lista->
            listaAgendamentos[i].finalizado == 0) {
            lista->listaAgendamentos[i].finalizado = 1;
            printf("Agendamento finalizado com sucesso!\n\n");

            return;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    printf("Agendamento não encontrado!\n\n");
}
