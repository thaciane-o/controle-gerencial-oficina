#include "modelNotasFiscais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das pecas no arquivo
void buscarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, int opcaoArmazenamento) {
    int i = 0;
    char linha[sizeof(struct notasFiscais)];

    FILE *dadosNotasFiscais;

    switch (opcaoArmazenamento) {
        case 1:
            dadosNotasFiscais = fopen("DadosNotasFiscais.txt", "r");

            if (dadosNotasFiscais == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosNotasFiscais)) {
                lista->qtdNotas++;
            }

            if (lista->qtdNotas > 0) {
                lista->listaNotas = malloc(lista->qtdNotas * sizeof(struct notasFiscais));
            } else {
                fclose(dadosNotasFiscais);
                return;
            }

            if (lista->listaNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosNotasFiscais);
                return;
            }

            fseek(dadosNotasFiscais, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosNotasFiscais)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaNotas[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    char *token2 = strtok(token, ",");
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaNotas[i].qtdPecas, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaNotas[i].frete = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaNotas[i].imposto = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaNotas[i].idFornecedor = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaNotas[i].deletado = atoi(token);
                }

                i++;
            }
            break;

        case 2:
            dadosNotasFiscais = fopen("DadosNotasFiscais.bin", "rb");

            if (dadosNotasFiscais == NULL) {
                return;
            }

            struct notasFiscais linhaNota;

            while (fread(&linhaNota, sizeof(linhaNota), 1, dadosNotasFiscais)) {
                lista->qtdNotas++;
            }

            if (lista->qtdNotas > 0) {
                lista->listaNotas = malloc(lista->qtdNotas * sizeof(struct notasFiscais));
            } else {
                fclose(dadosNotasFiscais);
                return;
            }

            if (lista->listaNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosNotasFiscais);
                return;
            }

            fseek(dadosNotasFiscais, 0, SEEK_SET);

            while (fread(&linhaNota, sizeof(linhaNota), 1, dadosNotasFiscais)) {
                lista->listaNotas[i] = linhaNota;
                i++;
            }
            break;
    }

    fclose(dadosNotasFiscais);
}

// Armazena os dados das pecas no arquivo
void armazenarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, int opcaoArmazenamento) {
    FILE *dadosNotas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosNotas = fopen("DadosNotasFiscais.txt", "w");

            if (dadosNotas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdNotas; i++) {
                char *token2, *token3;
                token2 = (char *) malloc(
                    (*(&lista->listaNotas[i].idPecas + 1) - lista->listaNotas[i].idPecas) * sizeof(char));
                token3 = (char *) malloc(
                    (*(&lista->listaNotas[i].qtdPecas + 1) - lista->listaNotas[i].qtdPecas) * sizeof(char));

                for (int j = 0; j < *(&lista->listaNotas[i].idPecas + 1) - lista->listaNotas->idPecas; j++) {
                    token2 += lista->listaNotas[i].idPecas[j];
                    token2 += (char)",";
                    token3 += lista->listaNotas[i].qtdPecas[j];
                    token3 += (char)",";
                }
                fprintf(dadosNotas, "%d;%s;%s;%f;%f;%d;%d\n",
                        lista->listaNotas[i].id,
                        token2,
                        token3,
                        lista->listaNotas[i].frete,
                        lista->listaNotas[i].imposto,
                        lista->listaNotas[i].idFornecedor,
                        lista->listaNotas[i].deletado);
            }
            break;

        case 2:
            dadosNotas = fopen("DadosNotasFiscais.bin", "wb");

            if (dadosNotas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdNotas; i++) {
                fwrite(&lista->listaNotas[i], sizeof(struct notasFiscais), 1, dadosNotas);
            }
            break;
    }

    fclose(dadosNotas);

    free(lista->listaNotas);
    lista->listaNotas = NULL;

    lista->qtdNotas = 0;
}

// Aloca a memória inicial para a lista de peças
int alocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdPecas) {
    lista->qtdNotas = 1;
    lista->listaNotas = malloc(sizeof(struct notasFiscais));

    lista->listaNotas[lista->qtdNotas-1].idPecas = malloc(qtdPecas * sizeof(int));
    lista->listaNotas[lista->qtdNotas-1].qtdPecas = malloc( qtdPecas * sizeof(int));

    if (lista->listaNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória da peca conforme a quantidade que deseja alocar (qtdAloca)
int realocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdAloca, int qtdPecas) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada.\n\n");
        return 0;
    }

    lista->qtdNotas += qtdAloca;
    lista->listaNotas = realloc(lista->listaNotas, lista->qtdNotas * sizeof(struct notasFiscais));
    lista->listaNotas[lista->qtdNotas-1].idPecas = realloc(lista->listaNotas[lista->qtdNotas-1].idPecas, qtdPecas * sizeof(int));
    lista->listaNotas[lista->qtdNotas-1].qtdPecas = realloc(lista->listaNotas[lista->qtdNotas-1].qtdPecas, qtdPecas * sizeof(int));

    // Verifica se a alocação deu certo
    if (lista->listaNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova peca
void cadastrarNotasFiscaisModel(struct ListaNotasFiscais *lista, struct notasFiscais *novaNotaFiscal, int qtdPecas) {
    int resultAlocacao = 0;

    if (lista->qtdNotas == 0) {
        lista->qtdNotas++;
        resultAlocacao = alocarMemoriaNotasFiscaisModel(lista, qtdPecas);
    } else {
        // Se já tiver, aumenta a alocação em 1
        resultAlocacao = realocarMemoriaNotasFiscaisModel(lista, 1, qtdPecas);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar a peça.\n\n");
        return;
    }

    novaNotaFiscal->id = lista->qtdNotas;
    novaNotaFiscal->deletado = 0;

    lista->listaNotas[lista->qtdNotas - 1] = *novaNotaFiscal;

    printf("Nota cadastrada com sucesso!\n\n");
}