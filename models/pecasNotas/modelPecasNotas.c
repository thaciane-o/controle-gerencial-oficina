#include "modelPecasNotas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das pecas no arquivo
void buscarDadosPecaNotaModel(struct ListaPecasNotas *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosPecas;

    switch (opcaoArmazenamento) {
        case 1:
            char linha[sizeof(struct PecasNotas)*10];
            dadosPecas = fopen("DadosPecasNotas.txt", "r");

            if (dadosPecas == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosPecas)) {
                lista->qtdPecasNotas++;
            }

            if (lista->qtdPecasNotas > 0) {
                lista->listaPecasNotas = malloc(lista->qtdPecasNotas * sizeof(struct PecasNotas));
            } else {
                fclose(dadosPecas);
                return;
            }

            if (lista->listaPecasNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPecas);
                return;
            }

            fseek(dadosPecas, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosPecas)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaPecasNotas[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].idNota = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].idPeca = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].qtdPecas = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].deletado = atoi(token);
                }

                i++;
            }
            break;

        case 2:
            dadosPecas = fopen("DadosPecasNotas.bin", "rb");

            if (dadosPecas == NULL) {
                return;
            }

            struct PecasNotas linhaPeca;

            while (fread(&linhaPeca, sizeof(linhaPeca), 1, dadosPecas)) {
                lista->qtdPecasNotas++;
            }

            if (lista->qtdPecasNotas > 0) {
                lista->listaPecasNotas = malloc(lista->qtdPecasNotas * sizeof(struct PecasNotas));
            } else {
                fclose(dadosPecas);
                return;
            }

            if (lista->listaPecasNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPecas);
                return;
            }

            fseek(dadosPecas, 0, SEEK_SET);

            while (fread(&linhaPeca, sizeof(linhaPeca), 1, dadosPecas)) {
                lista->listaPecasNotas[i] = linhaPeca;
                i++;
            }
            break;
    }

    fclose(dadosPecas);
}

// Armazena os dados das pecas no arquivo
void armazenarDadosPecaNotaModel(struct ListaPecasNotas *lista, int opcaoArmazenamento) {
    FILE *dadosPecas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPecas = fopen("DadosPecasNotas.txt", "w");

            if (dadosPecas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPecasNotas; i++) {
                fprintf(dadosPecas, "%d;%d;%d;%d;%d\n",
                        lista->listaPecasNotas[i].id,
                        lista->listaPecasNotas[i].idNota,
                        lista->listaPecasNotas[i].idPeca,
                        lista->listaPecasNotas[i].qtdPecas,
                        lista->listaPecasNotas[i].deletado);
            }
            break;

        case 2:
            dadosPecas = fopen("DadosPecasNotas.bin", "wb");

            if (dadosPecas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPecasNotas; i++) {
                fwrite(&lista->listaPecasNotas[i], sizeof(struct PecasNotas), 1, dadosPecas);
            }
            break;
    }

    fclose(dadosPecas);

    free(lista->listaPecasNotas);
    lista->listaPecasNotas = NULL;

    lista->qtdPecasNotas = 0;
}

// Aloca a memória inicial para a lista de peças
int alocarMemoriaPecaNotaModel(struct ListaPecasNotas *lista) {
    lista->qtdPecasNotas = 1;
    lista->listaPecasNotas = malloc(sizeof(struct PecasNotas));

    if (lista->listaPecasNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória da peca conforme a quantidade que deseja alocar (qtdAloca)
int realocarMemoriaPecaNotaModel(struct ListaPecasNotas *lista, int qtdAloca) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada.\n\n");
        return 0;
    }

    lista->qtdPecasNotas += qtdAloca;
    lista->listaPecasNotas = realloc(lista->listaPecasNotas, lista->qtdPecasNotas * sizeof(struct PecasNotas));

    // Verifica se a alocação deu certo
    if (lista->listaPecasNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova peca
void cadastrarPecaNotaModel(struct ListaPecasNotas *lista, struct PecasNotas *pecaNotaCadastrando) {
    int resultAlocacao = 0;

    if (lista->qtdPecasNotas == 0) {
        lista->qtdPecasNotas++;
        resultAlocacao = alocarMemoriaPecaNotaModel(lista);
    } else {
        // Se já tiver, aumenta a alocação em 1
        resultAlocacao = realocarMemoriaPecaNotaModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar a relação Peca/Nota.\n\n");
        return;
    }

    pecaNotaCadastrando->id = lista->qtdPecasNotas;
    pecaNotaCadastrando->deletado = 0;
    lista->listaPecasNotas[lista->qtdPecasNotas - 1] = *pecaNotaCadastrando;


}

// Deleta uma relação cadastrada
void deletarPecaNotaModel(struct ListaPecasNotas *lista, int id) {
    // Auxiliar para saber se encontrou o id.

    // Verifica se há algum cadastro
    if (lista->qtdPecasNotas == 0) {
        return;
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdPecasNotas; i++) {
        if (lista->listaPecasNotas[i].idNota == id && lista->listaPecasNotas[i].deletado == 0) {
            lista->listaPecasNotas[i].deletado = 1;
        }
    }
}
