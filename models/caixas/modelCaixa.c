#include "modelCaixa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca os dados dos caixas nos arquivos
void buscarDadosCaixasModel(struct ListaCaixas *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosCaixas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosCaixas = fopen("DadosCaixas.txt", "r");

            if (dadosCaixas == NULL) {
                return;
            }

            char linha[sizeof(struct Caixas)];

            while (fgets(linha, sizeof(linha), dadosCaixas)) {
                lista->qtdCaixas++;
            }

            if (lista->qtdCaixas > 0) {
                lista->listaCaixas = malloc(lista->qtdCaixas * sizeof(struct Caixas));
            } else {
                fclose(dadosCaixas);
                return;
            }

            if (lista->listaCaixas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosCaixas);
                return;
            }

            fseek(dadosCaixas, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosCaixas)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaCaixas[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaCaixas[i].valorCaixa = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaCaixas[i].idOficina = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaCaixas[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosCaixas = fopen("DadosCaixas.bin", "rb");

            if (dadosCaixas == NULL) {
                return;
            }

            struct Caixas linhaCaixa;

            while (fread(&linhaCaixa, sizeof(linhaCaixa), 1, dadosCaixas)) {
                lista->qtdCaixas++;
            }

            if (lista->qtdCaixas > 0) {
                lista->listaCaixas = malloc(lista->qtdCaixas * sizeof(struct Caixas));
            } else {
                fclose(dadosCaixas);
                return;
            }

            if (lista->listaCaixas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosCaixas);
                return;
            }

            fseek(dadosCaixas, 0, SEEK_SET);

            while (fread(&linhaCaixa, sizeof(linhaCaixa), 1, dadosCaixas)) {
                lista->listaCaixas[i] = linhaCaixa;
                i++;
            }

            break;
    }
    fclose(dadosCaixas);
}

// Armazena os dados dos caixas nos arquivos
void armazenarDadosCaixasModel(struct ListaCaixas *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosCaixas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosCaixas = fopen("DadosCaixas.txt", "w");

            if (dadosCaixas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdCaixas; i++) {
                fprintf(dadosCaixas, "%d;%f;%d;%d\n",
                        lista->listaCaixas[i].id,
                        lista->listaCaixas[i].valorCaixa,
                        lista->listaCaixas[i].idOficina,
                        lista->listaCaixas[i].deletado);
            }
            break;
        case 2:
            dadosCaixas = fopen("DadosCaixas.bin", "wb");

            if (dadosCaixas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdCaixas; i++) {
                fwrite(&lista->listaCaixas[i], sizeof(struct Caixas), 1, dadosCaixas);
            }
            break;
    }
    fclose(dadosCaixas);

    free(lista->listaCaixas);
    lista->listaCaixas = NULL;

    lista->qtdCaixas = 0;
}

// Aloca memória inicial na lista de caixas
int alocarCaixasModel(struct ListaCaixas *lista) {
    lista->qtdCaixas = 1;
    lista->listaCaixas = malloc(sizeof(struct Caixas));

    if (lista->listaCaixas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de caixas conforme a necessidade em qtdAlocada
int realocarCaixasModel(struct ListaCaixas *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdCaixas += qtdAlocada;
    lista->listaCaixas = realloc(lista->listaCaixas, lista->qtdCaixas * sizeof(struct Caixas));

    if (lista->listaCaixas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Inicia caixa zerado ao criar uma oficina
void iniciarCaixasModel(struct ListaCaixas *lista, int idOficina) {
    int resultAlocacao = 0;

    if (lista->qtdCaixas == 0) {
        lista->qtdCaixas++;
        resultAlocacao = alocarCaixasModel(lista);
    } else {
        resultAlocacao = realocarCaixasModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o Caixa.\n\n");
        return;
    }

    // Cadastrando o caixa zerado na memória
    struct Caixas novoCaixa;
    novoCaixa.id = lista->qtdCaixas;
    novoCaixa.valorCaixa = 0;
    novoCaixa.idOficina = idOficina;
    novoCaixa.deletado = 0;

    lista->listaCaixas[lista->qtdCaixas - 1] = novoCaixa;

    printf("Caixa cadastrado com sucesso!\n\n");
}

// Deleta caixa ao deletar uma oficina
void deletarCaixasModel(struct ListaCaixas *lista, int idOficina) {
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdCaixas == 0) {
        printf("Nenhum caixa foi cadastrado!\n\n");
        return;
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdCaixas; i++) {
        if (lista->listaCaixas[i].idOficina == idOficina && lista->listaCaixas[i].deletado == 0) {
            encontrado = 1;

            lista->listaCaixas[i].deletado = 1;

            printf("Caixa deletado com sucesso!\n\n");

            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Caixa não encontrado!\n\n");
    }
}

// Mostra valor de caixa de uma oficina em específico
void mostrarCaixasModel(struct ListaCaixas *lista, int idOficina) {
    int encontrado = 0;

    if (lista->qtdCaixas > 0) {
        for (int i = 0; i < lista->qtdCaixas; i++) {
            if (lista->listaCaixas[i].idOficina == idOficina && lista->listaCaixas[i].deletado == 0) {
                encontrado = 1;
                printf("\n========================="
                       "\n| CAIXA DA OFICINA %d   |"
                       "\n========================="
                       "\nVALOR DO CAIXA: R$%.2f\n\n",
                       idOficina,
                       lista->listaCaixas[i].valorCaixa);
                break;

            }
        }

        if (encontrado == 0) {
            printf("Nenhum caixa encontrado.\n\n");
        }

    } else {
        printf("Nenhum caixa foi cadastrado.\n\n");
    }
}

// Pega ID do caixa de uma oficina desejada
int getIdCaixaPorOficinaModel(struct ListaCaixas *lista, int idOficina) {
    if (lista->qtdCaixas > 0) {
        for (int i = 0; i < lista->qtdCaixas; i++) {
            if (lista->listaCaixas[i].idOficina == idOficina && lista->listaCaixas[i].deletado == 0) {
                return lista->listaCaixas[i].id;
            }
        }
        printf("Nenhum caixa encontrado.\n\n");
    } else {
        printf("Nenhum caixa foi cadastrado.\n\n");
    }

    return -1;
}

// Pega ID da oficina pelo ID do caixa
int getIdOficinaPorCaixaModel(struct ListaCaixas *lista, int idCaixa) {
    if (lista->qtdCaixas > 0) {
        for (int i = 0; i < lista->qtdCaixas; i++) {
            if (lista->listaCaixas[i].id == idCaixa && lista->listaCaixas[i].deletado == 0) {
                return lista->listaCaixas[i].idOficina;
            }
        }
        printf("Nenhuma oficina encontrada.\n\n");
    } else {
        printf("Nenhum caixa foi cadastrado.\n\n");
    }

    return -1;
}
