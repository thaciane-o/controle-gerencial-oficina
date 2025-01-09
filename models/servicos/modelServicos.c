#include "modelServicos.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca os dados de serviços nos arquivos
void buscarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento) {
    int i = 0;
    char linha[sizeof(struct Servicos)];

    FILE *dadosServicos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosServicos = fopen("DadosServicos.txt", "r");

            if (dadosServicos == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosServicos)) {
                lista->qtdServicos++;
            }

            if (lista->qtdServicos > 0) {
                lista->listaServicos = malloc(lista->qtdServicos * sizeof(struct Servicos));
            } else {
                fclose(dadosServicos);
                return;
            }

            if (lista->listaServicos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosServicos);
                return;
            }

            fseek(dadosServicos, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosServicos)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaServicos[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaServicos[i].descricao, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaServicos[i].preco = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaServicos[i].comissao = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaServicos[i].idOficina = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaServicos[i].deletado = atoi(token);
                }

                i++;
            }
            break;

        case 2:
            dadosServicos = fopen("DadosServicos.bin", "rb");

            if (dadosServicos == NULL) {
                return;
            }

            struct Servicos linhaServico;

            while (fread(&linhaServico, sizeof(linhaServico), 1, dadosServicos)) {
                lista->qtdServicos++;
            }

            if (lista->qtdServicos > 0) {
                lista->listaServicos = malloc(lista->qtdServicos * sizeof(struct Servicos));
            } else {
                fclose(dadosServicos);
                return;
            }

            if (lista->listaServicos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosServicos);
                return;
            }

            fseek(dadosServicos, 0, SEEK_SET);

            while (fread(&linhaServico, sizeof(linhaServico), 1, dadosServicos)) {
                lista->listaServicos[i] = linhaServico;
                i++;
            }
            break;
    }

    fclose(dadosServicos);
}

// Armazena os dados dos serviços nos arquivos
void armazenarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento) {
    FILE *dadosServicos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosServicos = fopen("DadosServicos.txt", "w");

            if (dadosServicos == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdServicos; i++) {
                fprintf(dadosServicos, "%d;%s;%.2f;%.2f;%d;%d;\n",
                        lista->listaServicos[i].id,
                        lista->listaServicos[i].descricao,
                        lista->listaServicos[i].preco,
                        lista->listaServicos[i].comissao,
                        lista->listaServicos[i].idOficina,
                        lista->listaServicos[i].deletado);
            }
            break;

        case 2:
            dadosServicos = fopen("DadosServicos.bin", "wb");

            if (dadosServicos == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdServicos; i++) {
                fwrite(&lista->listaServicos[i], sizeof(struct Servicos), 1, dadosServicos);
            }
            break;
    }

    fclose(dadosServicos);

    free(lista->listaServicos);
    lista->listaServicos = NULL;

    lista->qtdServicos = 0;
}

// Aloca a memoria inicial da lista
int alocarMemoriaServicoModel(struct ListaServicos *lista) {
    lista->qtdServicos = 1;
    lista->listaServicos = malloc(sizeof(struct Servicos));

    if (lista->listaServicos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca a quantidade de serviços conforme o aumento da lista
int realocarMemoriaServicoModel(struct ListaServicos *lista, int qtdAloca) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada\n");
        return 0;
    }

    lista->qtdServicos += qtdAloca;
    lista->listaServicos = realloc(lista->listaServicos, lista->qtdServicos * sizeof(struct Servicos));

    if (lista->listaServicos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra um novo serviço
void cadastrarServicoModel(struct ListaServicos *lista, struct Servicos *servicoCadastrando) {
    int resultAlocacao = 0;

    if (lista->qtdServicos == 0) {
        lista->qtdServicos++;
        resultAlocacao = alocarMemoriaServicoModel(lista);
    } else {
        // Se já tiver, aumenta a alocação em 1
        resultAlocacao = realocarMemoriaServicoModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o serviço.\n\n");
        return;
    }

    servicoCadastrando->id = lista->qtdServicos;
    servicoCadastrando->deletado = 0;

    lista->listaServicos[lista->qtdServicos - 1] = *servicoCadastrando;

    printf("Serviço cadastrado com sucesso!\n");
}

// Verifica a existência do id requisitado
int verificarIDServicoModel(struct ListaServicos *lista, int id) {
    // Procura o serviço com o id inserido
    if (lista->qtdServicos > 0) {
        for (int i = 0; i < lista->qtdServicos; i++) {
            if (lista->listaServicos[i].id == id && lista->listaServicos[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhum serviço foi cadastrado!\n");
        return 0;
    }

    printf("Serviço não encontrado!\n");
    return 0;
}

// Atualiza serviço ja cadastrado
void atualizarServicoModel(struct ListaServicos *lista, int id, struct Servicos *servicoAlterando) {
    // Busca pelo id para fazer a alteração.
    for (int i = 0; i < lista->qtdServicos; i++) {
        if (lista->listaServicos[i].id == id && lista->listaServicos[i].deletado == 0) {
            lista->listaServicos[i] = *servicoAlterando;
            lista->listaServicos[i].id = id;
            lista->listaServicos[i].deletado = 0;
            break;
        }
    }
}

// Lista todos os serviços cadastrados
void listarTodosServicoModel(struct ListaServicos *lista) {
    // Variável para verificação de listagem
    int listado = -1;

    // Verifica se há pelo menos um cadastro
    if (lista->qtdServicos > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdServicos; i++) {
            // Verifica se o índice atual existe
            if (lista->listaServicos[i].deletado == 0) {
                listado = 1;
                printf("\n====================\n"
                       "| SERVIÇO %d        |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "PREÇO: $%.2f\n"
                       "COMISSÃO: $%.2f\n"
                       "OFICINA: %d\n",
                       lista->listaServicos[i].id,
                       lista->listaServicos[i].descricao,
                       lista->listaServicos[i].preco,
                       lista->listaServicos[i].comissao,
                       lista->listaServicos[i].idOficina);
            }
        }
    }
    if (listado == -1) {
        // Caso todos estejam deletados
        printf("Nenhum serviço foi cadastrado.\n");
    }
}

// Lista um serviço pelo id
void listarServicoModel(struct ListaServicos *lista, int id) {
    // Se há um ou mais cadastros, procura pelo serviço com o id desejado
    int encontrado = -1;
    for (int i = 0; i < lista->qtdServicos; i++) {
        if (lista->listaServicos[i].id == id && lista->listaServicos[i].deletado == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("\n====================\n"
               "| SERVIÇO %d        |\n"
               "====================\n"
               "DESCRIÇÃO: %s\n"
               "PREÇO: $%.2f\n"
               "COMISSÃO: $%.2f\n"
               "OFICINA: %d\n",
               lista->listaServicos[encontrado].id,
               lista->listaServicos[encontrado].descricao,
               lista->listaServicos[encontrado].preco,
               lista->listaServicos[encontrado].comissao,
               lista->listaServicos[encontrado].idOficina);
    } else {
        printf("Nenhum serviço encontrado.\n");
    }
}

// Lista os serviços relacionados a uma oficina, buscando pelo idOficina
void buscarServicosPorOficinaModel(struct ListaServicos *lista, int idOficina) {
    int encontrado = 0;

    if (lista->qtdServicos > 0) {
        for (int i = 0; i < lista->qtdServicos; i++) {
            if (lista->listaServicos[i].idOficina == idOficina && lista->listaServicos[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================\n"
                       "| SERVIÇO %d        |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "PREÇO: $%.2f\n"
                       "COMISSÃO: $%.2f\n"
                       "OFICINA: %d\n",
                       lista->listaServicos[i].id,
                       lista->listaServicos[i].descricao,
                       lista->listaServicos[i].preco,
                       lista->listaServicos[i].comissao,
                       lista->listaServicos[i].idOficina);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum serviço encontrado.\n\n");
        }
    } else {
        printf("Nenhum serviço foi cadastrado.\n\n");
    }
}

// Deleta um serviço
void deletarServicoModel(struct ListaServicos *lista, struct ListaAgendamentos *listaAgendamentos, int id) {
    // Auxiliar para saber se encontrou o id.
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdServicos == 0) {
        printf("Nenhum serviço foi cadastrado.\n");
        return;
    }

    // Verifica relação com agendamento
    if (listaAgendamentos->qtdAgendamentos > 0) {
        for (int i = 0; i < listaAgendamentos->qtdAgendamentos; i++) {
            if (listaAgendamentos->listaAgendamentos[i].idServico == id && listaAgendamentos->listaAgendamentos[i].deletado == 0) {
                printf(
                    "Não foi possível deletar o serviço, pois os seus dados estão sendo utilizados em um agendamento que será realizado.\n\n");
                return;
            }
        }
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdServicos; i++) {
        if (lista->listaServicos[i].id == id && lista->listaServicos[i].deletado == 0) {
            encontrado = 1;
            lista->listaServicos[i].deletado = 1;
            printf("Serviço deletado com sucesso!\n");
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa ao usuário
    if (!encontrado) {
        printf("Serviço não encontrado.\n");
    }
}

// Pega valor do serviço pelo seu id
float getValorServicoPorIdModel(struct ListaServicos *lista, int id) {

    if (lista->qtdServicos > 0) {
        for (int i = 0; i < lista->qtdServicos; i++) {
            if (lista->listaServicos[i].id == id && lista->listaServicos[i].deletado == 0) {
                return lista->listaServicos[i].preco;
            }
        }
        printf("Serviço não encontrado.\n\n");
    } else {
        printf("Não há serviços cadastrados.\n\n");
    }

    return -1;
}
