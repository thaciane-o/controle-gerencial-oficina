#include "modelEstoques.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados dos estoques no arquivo
void buscarDadosEstoquesModel(struct ListaEstoques *lista, int opcaoArmazenamento) {
    int i = 0;
    char linha[sizeof(struct Estoques)];

    FILE *dadosEstoques;

    switch (opcaoArmazenamento) {
        case 1:
            dadosEstoques = fopen("DadosEstoques.txt", "r");

            if (dadosEstoques == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosEstoques)) {
                lista->qtdEstoques++;
            }

            if (lista->qtdEstoques > 0) {
                lista->listaEstoques = malloc(lista->qtdEstoques * sizeof(struct Estoques));
            } else {
                return;
            }

            if (lista->listaEstoques == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosEstoques, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosEstoques)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaEstoques[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaEstoques[i].idPecas = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaEstoques[i].deletado = atoi(token);
                }
                i++;
            }
            break;

        case 2:
            dadosEstoques = fopen("DadosEstoques.bin", "rb");

            if (dadosEstoques == NULL) {
                return;
            }

            struct Estoques linhaEstoque;

            while (fread(&linhaEstoque, sizeof(linhaEstoque), 1, dadosEstoques)) {
                lista->qtdEstoques++;
            }

            if (lista->qtdEstoques > 0) {
                lista->listaEstoques = malloc(lista->qtdEstoques * sizeof(struct Estoques));
            } else {
                return;
            }

            if (lista->listaEstoques == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosEstoques, 0, SEEK_SET);

            while (fread(&linhaEstoque, sizeof(linhaEstoque), 1, dadosEstoques)) {
                lista->listaEstoques[i] = linhaEstoque;
                i++;
            }
            break;
    }

    fclose(dadosEstoques);
}

// Armazena os dados dos estoques no arquivo
void armazenarDadosEstoquesModel(struct ListaEstoques *lista, int opcaoArmazenamento) {
    FILE *dadosEstoques;

    switch (opcaoArmazenamento) {
        case 1:
            dadosEstoques = fopen("DadosEstoques.txt", "w");

        if (dadosEstoques == NULL) {
            printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdEstoques; i++) {
            fprintf(dadosEstoques, "%d;%d;%d;%d\n",
                    lista->listaEstoques[i].id,
                    lista->listaEstoques[i].idPecas,
                    lista->listaEstoques[i].idFornecedor,
                    lista->listaEstoques[i].deletado);
        }
        break;

        case 2:
            dadosEstoques = fopen("DadosEstoques.bin", "wb");

        if (dadosEstoques == NULL) {
            printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdEstoques; i++) {
            fwrite(&lista->listaEstoques[i], sizeof(struct Estoques), 1, dadosEstoques);
        }
        break;
    }

    fclose(dadosEstoques);

    free(lista->listaEstoques);
    lista->listaEstoques = NULL;

    lista->qtdEstoques = 0;
}

// Aloca a memória inicial para a lista de estoques
int alocarMemoriaEstoqueModel(struct ListaEstoques *lista) {
    lista->qtdEstoques = 1;
    lista->listaEstoques = malloc(sizeof(struct Estoques));

    if (lista->listaEstoques == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória do estoque conforme a quantidade que deseja alocar (qtdAloca)
int realocarMemoriaEstoqueModel(struct ListaEstoques *lista, int qtdAloca) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada.\n\n");
        return 0;
    }

    lista->qtdEstoques += qtdAloca;
    lista->listaEstoques = realloc(lista->listaEstoques, lista->qtdEstoques * sizeof(struct Estoques));

    // Verifica se a alocação deu certo
    if (lista->listaEstoques == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

void listarEstoquesModel(struct Estoques *lista) {


}

// Deleta um estoque cadastrado
void deletarEstoqueModel(struct ListaEstoques *lista, int id) {
    // Auxiliar para saber se encontrou o id.
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdEstoques == 0) {
        printf("Nenhum estoque foi cadastrado.\n");
        return;
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdEstoques; i++) {
        if (lista->listaEstoques[i].id == id && lista->listaEstoques[i].deletado == 0) {
            encontrado = 1;
            lista->listaEstoques[i].deletado = 1;
            printf("Estoque deletado com sucesso!\n");
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Estoque não encontrado.\n");
    }
}