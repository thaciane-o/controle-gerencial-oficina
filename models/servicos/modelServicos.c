#include "modelServicos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Busca os dados de serviços nos arquivos
void buscarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento) {
    int i = 0;
    char linha[sizeof(struct Servicos)];

    FILE *dadosServicos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosServicos = fopen("DadosServicos.txt", "r");

            if (dadosServicos == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return;
            }

            while (fgets(linha, sizeof(linha), dadosServicos)) {
                lista->qtdServicos++;
            }

            if (lista->qtdServicos > 0) {
                lista->listaServicos = malloc(lista->qtdServicos * sizeof(struct Servicos));
            } else {
                return;
            }

            if (lista->listaServicos == NULL) {
                printf("Erro ao alocar memória!\n");
                exit(1);
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
                printf("Nenhum serviço armazenado!\n");
                return;
            }

            struct Servicos linhaServico;

            while (fread(&linhaServico, sizeof(linhaServico), 1, dadosServicos)) {
                lista->qtdServicos++;
            }

            if (lista->qtdServicos > 0) {
                lista->listaServicos = malloc(lista->qtdServicos * sizeof(struct Servicos));
            } else {
                return;
            }

            if (lista->listaServicos == NULL) {
                printf("Erro ao alocar memória!\n");
                exit(1);
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

//Armazena os dados dos serviços nos arquivos
void armazenarDadosServicoModel(struct ListaServicos *lista, int opcaoArmazenamento) {
    FILE *dadosServicos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosServicos = fopen("DadosServicos.txt", "w");

            if (dadosServicos == NULL) {
                printf("Erro ao armazenar serviços!\n");
                exit(1);
            }

            for (int i = 0; i < lista->qtdServicos; i++) {
                fprintf(dadosServicos, "%d;%s;%f;%f;%d;%d;\n",
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
                printf("Erro ao armazenar Serviços!\n");
                exit(1);
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

//Aloca a memoria inicial da lista
void alocarMemoriaServicoModel(struct ListaServicos *lista) {
    // Aloca a memória inicial para a lista de serviços
    lista->qtdServicos = 1;
    lista->listaServicos = malloc(sizeof(struct Servicos));

    // Verifica se a alocação deu certo
    if (lista->listaServicos == NULL) {
        printf("Erro: Memória insuficiente\n");
        exit(EXIT_FAILURE);
    }
}

//Realoca a quantidade de serviços conforme o aumento da lista
void realocarMemoriaServicoModel(struct ListaServicos *lista, int qtdAloca) {
    // Verifica o tamando da alocação que pretende fazer
    if (qtdAloca == 0) {
        // Nenhuma alocação
        printf("Nenhuma alocação foi realizada\n");
        return;
    }

    lista->qtdServicos += qtdAloca;
    lista->listaServicos = realloc(lista->listaServicos, lista->qtdServicos * sizeof(struct Servicos));

    // Verifica se a alocação deu certo
    if (lista->listaServicos == NULL) {
        printf("Erro: Memória insuficiente\n");
        exit(EXIT_FAILURE);
    }
}

//Cadastra um novo serviço
void cadastrarServicoModel(struct ListaServicos *lista, struct Servicos *servicoCadastrando) {
    // Se nenhum serviço cadastrado, inicia a alocação
    if (lista->qtdServicos == 0) {
        lista->qtdServicos++;
        alocarMemoriaServicoModel(lista);
    } else {
        // Se já tiver, aumenta a alocação em 1
        realocarMemoriaServicoModel(lista, 1);
    }

    servicoCadastrando->id = lista->qtdServicos;
    servicoCadastrando->deletado = 0;

    lista->listaServicos[lista->qtdServicos - 1] = *servicoCadastrando;

    printf("Serviço cadastrado com sucesso!\n");
}

//Deleta um serviço
void deletarServicoModel(struct ListaServicos *lista, int id) {
    // Auxiliar para saber se encontrou o id.
    int encontrado = 0;

    // Verifica se há algum serviço cadastrada.
    if (lista->qtdServicos == 0) {
        printf("Nenhum serviço foi cadastrado.\n");
        return;
    }

    // Busca pelo id para fazer a deleção.
    for (int i = 0; i < lista->qtdServicos; i++) {
        if (lista->listaServicos[i].id == id && lista->listaServicos[i].deletado == 0) {
            encontrado = 1;
            lista->listaServicos[i].deletado = 1;
            printf("Serviço deletado com sucesso!\n");
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa ao usuário.
    if (!encontrado) {
        printf("Serviço não encontrado.\n");
    }
}

//Atualiza serviço ja cadastrado
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

//Verifica a existencia de um ID de serviço
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

//Lista todos os serviços cadastrados
void listarTodosServicoModel(struct ListaServicos *lista) {
    // Verifica se há pelo menos um cadastro
    int encontrado = -1;

    if (lista->qtdServicos > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdServicos; i++) {
            // Verifica se o índice atual existe
            if (lista->listaServicos[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================\n"
                       "| SERVIÇO %d        |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "PREÇO: $%.2f\n"
                       "COMISSÃO: $%.2f\n"
                       "OFICINA: %d\n\n",
                       lista->listaServicos[i].id,
                       lista->listaServicos[i].descricao,
                       lista->listaServicos[i].preco,
                       lista->listaServicos[i].comissao,
                       lista->listaServicos[i].idOficina);
            }
        }
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhum serviço foi cadastrada\n");
    }
    if (encontrado == -1) {
        // Caso todos estejam deletados
        printf("Nenhum serviço foi cadastrada\n");
    }
}

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
                       "OFICINA: %d\n\n",
                       lista->listaServicos[encontrado].id,
                       lista->listaServicos[encontrado].descricao,
                       lista->listaServicos[encontrado].preco,
                       lista->listaServicos[encontrado].comissao,
                       lista->listaServicos[encontrado].idOficina);
    } else {
        printf("Nenhum serviço encontrada.\n");
    }
}


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
                       "OFICINA: %d\n\n",
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
