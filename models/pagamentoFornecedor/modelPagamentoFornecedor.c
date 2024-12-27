#include "modelPagamentoFornecedor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Busca os dados dos pagamentos de fornecedor nos arquivos
void buscarDadosPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, int opcaoArmazenamento) {
        int i = 0;

    FILE *dadosPagamentosFornecedor;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPagamentosFornecedor = fopen("DadosPagamentosFornecedor.txt", "r");

            if (dadosPagamentosFornecedor == NULL) {
                return;
            }

            char linha[sizeof(struct PagamentosFornecedor)];

            while (fgets(linha, sizeof(linha), dadosPagamentosFornecedor)) {
                lista->qtdPagamentosFornecedor++;
            }

            if (lista->qtdPagamentosFornecedor > 0) {
                lista->listaPagamentosFornecedor = malloc(lista->qtdPagamentosFornecedor * sizeof(struct PagamentosFornecedor));
            } else {
                fclose(dadosPagamentosFornecedor);
                return;
            }

            if (lista->listaPagamentosFornecedor == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPagamentosFornecedor);
                return;
            }

            fseek(dadosPagamentosFornecedor, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosPagamentosFornecedor)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaPagamentosFornecedor[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosFornecedor[i].tipoPagamento = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosFornecedor[i].valor = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaPagamentosFornecedor[i].dataPagamento, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosFornecedor[i].idCaixa = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosFornecedor[i].idFornecedor = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosFornecedor[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosPagamentosFornecedor = fopen("DadosPagamentosFornecedor.bin", "rb");

            if (dadosPagamentosFornecedor == NULL) {
                return;
            }

            struct PagamentosFornecedor linhaPagamentosFornecedor;

            while (fread(&linhaPagamentosFornecedor, sizeof(linhaPagamentosFornecedor), 1, dadosPagamentosFornecedor)) {
                lista->qtdPagamentosFornecedor++;
            }

            if (lista->qtdPagamentosFornecedor > 0) {
                lista->listaPagamentosFornecedor = malloc(lista->qtdPagamentosFornecedor * sizeof(struct PagamentosFornecedor));
            } else {
                fclose(dadosPagamentosFornecedor);
                return;
            }

            if (lista->listaPagamentosFornecedor == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPagamentosFornecedor);
                return;
            }

            fseek(dadosPagamentosFornecedor, 0, SEEK_SET);

            while (fread(&linhaPagamentosFornecedor, sizeof(linhaPagamentosFornecedor), 1, dadosPagamentosFornecedor)) {
                lista->listaPagamentosFornecedor[i] = linhaPagamentosFornecedor;
                i++;
            }

            break;
    }
    fclose(dadosPagamentosFornecedor);
}

// Armazena os dados dos pagamentos de fornecedor nos arquivos
void armazenarDadosPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosPagamentosFornecedor;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPagamentosFornecedor = fopen("DadosPagamentosFornecedor.txt", "w");

        if (dadosPagamentosFornecedor == NULL) {
            printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdPagamentosFornecedor; i++) {
            fprintf(dadosPagamentosFornecedor, "%d;%d;%f;%s;%d;%d;%d\n",
                    lista->listaPagamentosFornecedor[i].id,
                    lista->listaPagamentosFornecedor[i].tipoPagamento,
                    lista->listaPagamentosFornecedor[i].valor,
                    lista->listaPagamentosFornecedor[i].dataPagamento,
                    lista->listaPagamentosFornecedor[i].idCaixa,
                    lista->listaPagamentosFornecedor[i].idFornecedor,
                    lista->listaPagamentosFornecedor[i].deletado);
        }
        break;
        case 2:
            dadosPagamentosFornecedor = fopen("DadosPagamentosFornecedor.bin", "wb");

        if (dadosPagamentosFornecedor == NULL) {
            printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdPagamentosFornecedor; i++) {
            fwrite(&lista->listaPagamentosFornecedor[i], sizeof(struct PagamentosFornecedor), 1, dadosPagamentosFornecedor);
        }
        break;
    }
    fclose(dadosPagamentosFornecedor);

    free(lista->listaPagamentosFornecedor);
    lista->listaPagamentosFornecedor = NULL;

    lista->qtdPagamentosFornecedor = 0;
}

// Aloca memória inicial na lista de pagamentos de fornecedor
int alocarPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista) {
    lista->qtdPagamentosFornecedor = 1;
    lista->listaPagamentosFornecedor = malloc(sizeof(struct PagamentosFornecedor));

    if (lista->listaPagamentosFornecedor == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de pagamentos de fornecedor conforme a necessidade em qtdAlocada
int realocarPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdPagamentosFornecedor += qtdAlocada;
    lista->listaPagamentosFornecedor = realloc(lista->listaPagamentosFornecedor,
                                               lista->qtdPagamentosFornecedor * sizeof(struct PagamentosFornecedor));

    if (lista->listaPagamentosFornecedor == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}
