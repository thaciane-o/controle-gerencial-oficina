#include "modelPagamentoFornecedor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../caixas/modelCaixa.h"

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
                lista->listaPagamentosFornecedor = malloc(
                    lista->qtdPagamentosFornecedor * sizeof(struct PagamentosFornecedor));
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
                lista->listaPagamentosFornecedor = malloc(
                    lista->qtdPagamentosFornecedor * sizeof(struct PagamentosFornecedor));
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
                fwrite(&lista->listaPagamentosFornecedor[i], sizeof(struct PagamentosFornecedor), 1,
                       dadosPagamentosFornecedor);
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

// Cadastro de pagamento a fornecedor
int cadastrarPagamentosFornecedorModel(struct ListaPagamentosFornecedor *lista, struct PagamentosFornecedor *pagamento,
                                        struct ListaCaixas *listaCaixas) {
    float saldoCaixa = getSaldoCaixaPorCaixaModel(listaCaixas, pagamento->idCaixa);
    if (saldoCaixa == -1) {
        return -1;
    }
    if (saldoCaixa < pagamento->valor) {
        printf("Não há saldo suficiente no caixa para realizar o pagamento!\n\n");
        return -1;
    }

    int resultAlocacao = 0;

    if (lista->qtdPagamentosFornecedor == 0) {
        lista->qtdPagamentosFornecedor++;
        resultAlocacao = alocarPagamentosFornecedorModel(lista);
    } else {
        resultAlocacao = realocarPagamentosFornecedorModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o Pagamento ao Fornecedor.\n\n");
        return -1;
    }

    // Cadastrando pagamento na memória
    pagamento->id = lista->qtdPagamentosFornecedor;
    pagamento->deletado = 0;

    lista->listaPagamentosFornecedor[lista->qtdPagamentosFornecedor - 1] = *pagamento;

    printf("Pagamento cadastrado com sucesso!\n\n");

    // Debita o valor do pagamento
    debitarDinheiroCaixaPorCaixaModel(listaCaixas, pagamento->idCaixa, pagamento->valor);

    return 0;
}

// Buscar contas pagas a fornecedor por oficina
void listaPagamentosFornecedorPorOficinaModel(struct ListaPagamentosFornecedor *lista, struct ListaCaixas *listaCaixas,
                                              int idOficina) {
    int idCaixa;
    // Busca pelo caixa da oficina
    idCaixa = getIdCaixaPorOficinaModel(listaCaixas, idOficina);
    if (idCaixa == -1) {
        return;
    }

    // Verifica se há pelo menos um cadastro
    if (lista->qtdPagamentosFornecedor > 0) {
        int encontrado = 0;
        char tiposPagamento[3][20] = {"Dinheiro", "Cartão de crédito", "Cartão de débito"};
        for (int i = 0; i < lista->qtdPagamentosFornecedor; i++) {
            if (lista->listaPagamentosFornecedor[i].idCaixa == idCaixa && lista->listaPagamentosFornecedor[i].deletado
                ==
                0) {
                encontrado = 1;
                printf("\n============================\n"
                       "| PAGAMENTO %d\n"
                       "============================\n"
                       "TIPO PAGAMENTO: %s\n"
                       "DATA PAGAMENTO: %s\n"
                       "VALOR: R$%.2f\n"
                       "PAGO AO FORNECEDOR: %d\n",
                       lista->listaPagamentosFornecedor[i].id,
                       tiposPagamento[lista->listaPagamentosFornecedor[i].tipoPagamento - 1],
                       lista->listaPagamentosFornecedor[i].dataPagamento,
                       lista->listaPagamentosFornecedor[i].valor,
                       lista->listaPagamentosFornecedor[i].idFornecedor);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum pagamento encontrado\n\n");
        }
    } else {
        printf("Nenhum pagamento foi cadastrado\n\n");
    }
}

// Buscar contas pagas a fornecedor por oficina
void listaPagamentosFornecedorPorFornecedorModel(struct ListaPagamentosFornecedor *lista,
                                                 struct ListaCaixas *listaCaixas, int idFornecedor) {
    // Verifica se há pelo menos um cadastro
    if (lista->qtdPagamentosFornecedor > 0) {
        int encontrado = 0;
        char tiposPagamento[3][20] = {"Dinheiro", "Cartão de crédito", "Cartão de débito"};
        for (int i = 0; i < lista->qtdPagamentosFornecedor; i++) {
            if (lista->listaPagamentosFornecedor[i].idFornecedor == idFornecedor && lista->listaPagamentosFornecedor[i].
                deletado ==
                0) {
                encontrado = 1;

                // Pega id da oficina que fez o pagamento
                int idOficina = getIdOficinaPorCaixaModel(listaCaixas, lista->listaPagamentosFornecedor[i].idCaixa);
                if (idOficina == -1) {
                    continue;
                }

                printf("\n============================\n"
                       "| PAGAMENTO %d\n"
                       "============================\n"
                       "TIPO PAGAMENTO: %s\n"
                       "DATA PAGAMENTO: %s\n"
                       "VALOR: R$%.2f\n"
                       "OFICINA PAGANTE: %d\n",
                       lista->listaPagamentosFornecedor[i].id,
                       tiposPagamento[lista->listaPagamentosFornecedor[i].tipoPagamento - 1],
                       lista->listaPagamentosFornecedor[i].dataPagamento,
                       lista->listaPagamentosFornecedor[i].valor,
                       idOficina);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum pagamento encontrado\n\n");
        }
    } else {
        printf("Nenhum pagamento foi cadastrado\n\n");
    }
}
