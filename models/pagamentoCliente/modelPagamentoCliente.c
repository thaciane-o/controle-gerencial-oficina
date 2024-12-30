#include "modelPagamentoCliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../caixas/modelCaixa.h"

// Busca os dados dos pagamentos de cliente nos arquivos
void buscarDadosPagamentosClienteModel(struct ListaPagamentosCliente *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosPagamentosCliente;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPagamentosCliente = fopen("DadosPagamentosCliente.txt", "r");

            if (dadosPagamentosCliente == NULL) {
                return;
            }

            char linha[sizeof(struct PagamentosCliente)];

            while (fgets(linha, sizeof(linha), dadosPagamentosCliente)) {
                lista->qtdPagamentosCliente++;
            }

            if (lista->qtdPagamentosCliente > 0) {
                lista->listaPagamentosCliente = malloc(lista->qtdPagamentosCliente * sizeof(struct PagamentosCliente));
            } else {
                fclose(dadosPagamentosCliente);
                return;
            }

            if (lista->listaPagamentosCliente == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPagamentosCliente);
                return;
            }

            fseek(dadosPagamentosCliente, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosPagamentosCliente)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaPagamentosCliente[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosCliente[i].tipoPagamento = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosCliente[i].valor = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaPagamentosCliente[i].dataPagamento, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaPagamentosCliente[i].dataAReceber, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaPagamentosCliente[i].dataRecebimento, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosCliente[i].idCaixa = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosCliente[i].idCliente = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPagamentosCliente[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosPagamentosCliente = fopen("DadosPagamentosCliente.bin", "rb");

            if (dadosPagamentosCliente == NULL) {
                return;
            }

            struct PagamentosCliente linhaPagamentosCliente;

            while (fread(&linhaPagamentosCliente, sizeof(linhaPagamentosCliente), 1, dadosPagamentosCliente)) {
                lista->qtdPagamentosCliente++;
            }

            if (lista->qtdPagamentosCliente > 0) {
                lista->listaPagamentosCliente = malloc(lista->qtdPagamentosCliente * sizeof(struct PagamentosCliente));
            } else {
                fclose(dadosPagamentosCliente);
                return;
            }

            if (lista->listaPagamentosCliente == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPagamentosCliente);
                return;
            }

            fseek(dadosPagamentosCliente, 0, SEEK_SET);

            while (fread(&linhaPagamentosCliente, sizeof(linhaPagamentosCliente), 1, dadosPagamentosCliente)) {
                lista->listaPagamentosCliente[i] = linhaPagamentosCliente;
                i++;
            }

            break;
    }
    fclose(dadosPagamentosCliente);
}

// Armazena os dados dos pagamentos de cliente nos arquivos
void armazenarDadosPagamentosClienteModel(struct ListaPagamentosCliente *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosPagamentosCliente;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPagamentosCliente = fopen("DadosPagamentosCliente.txt", "w");

            if (dadosPagamentosCliente == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPagamentosCliente; i++) {
                fprintf(dadosPagamentosCliente, "%d;%d;%f;%s;%s;%s;%d;%d;%d\n",
                        lista->listaPagamentosCliente[i].id,
                        lista->listaPagamentosCliente[i].tipoPagamento,
                        lista->listaPagamentosCliente[i].valor,
                        lista->listaPagamentosCliente[i].dataPagamento,
                        lista->listaPagamentosCliente[i].dataAReceber,
                        lista->listaPagamentosCliente[i].dataRecebimento,
                        lista->listaPagamentosCliente[i].idCaixa,
                        lista->listaPagamentosCliente[i].idCliente,
                        lista->listaPagamentosCliente[i].deletado);
            }
            break;
        case 2:
            dadosPagamentosCliente = fopen("DadosPagamentosCliente.bin", "wb");

            if (dadosPagamentosCliente == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPagamentosCliente; i++) {
                fwrite(&lista->listaPagamentosCliente[i], sizeof(struct PagamentosCliente), 1, dadosPagamentosCliente);
            }
            break;
    }
    fclose(dadosPagamentosCliente);

    free(lista->listaPagamentosCliente);
    lista->listaPagamentosCliente = NULL;

    lista->qtdPagamentosCliente = 0;
}

// Aloca memória inicial na lista de pagamentos de cliente
int alocarPagamentosClienteModel(struct ListaPagamentosCliente *lista) {
    lista->qtdPagamentosCliente = 1;
    lista->listaPagamentosCliente = malloc(sizeof(struct PagamentosCliente));

    if (lista->listaPagamentosCliente == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de pagamentos de cliente conforme a necessidade em qtdAlocada
int realocarPagamentosClienteModel(struct ListaPagamentosCliente *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdPagamentosCliente += qtdAlocada;
    lista->listaPagamentosCliente = realloc(lista->listaPagamentosCliente,
                                            lista->qtdPagamentosCliente * sizeof(struct PagamentosCliente));

    if (lista->listaPagamentosCliente == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastro de pagamento de cliente
void cadastrarPagamentosClienteModel(struct ListaPagamentosCliente *lista, struct PagamentosCliente *pagamento,
                                     struct ListaCaixas *listaCaixas) {
    int resultAlocacao = 0;

    if (lista->qtdPagamentosCliente == 0) {
        lista->qtdPagamentosCliente++;
        resultAlocacao = alocarPagamentosClienteModel(lista);
    } else {
        resultAlocacao = realocarPagamentosClienteModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o Pagamento do Cliente.\n\n");
        return;
    }

    // Cadastrando pagamento na memória
    pagamento->id = lista->qtdPagamentosCliente;
    pagamento->deletado = 0;

    lista->listaPagamentosCliente[lista->qtdPagamentosCliente - 1] = *pagamento;

    printf("Pagamento cadastrado com sucesso!\n\n");

    // Se pagamento com dinheiro, credita no caixa na hora
    if (pagamento->tipoPagamento == 1) {
        creditarDinheiroCaixaPorCaixaModel(listaCaixas, pagamento->idCaixa, pagamento->valor);
    }
}

// Lista todas os pagamentos de um cliente desejado
void listarPagamentosDeClienteModel(struct ListaPagamentosCliente *lista, int idCliente) {
    // Verifica se há pelo menos um cadastro
    if (lista->qtdPagamentosCliente > 0) {
        int encontrado = 0;
        char tiposPagamento[3][20] = {"Dinheiro", "Cartão de crédito", "Cartão de débito"};
        for (int i = 0; i < lista->qtdPagamentosCliente; i++) {
            if (lista->listaPagamentosCliente[i].idCliente == idCliente && lista->listaPagamentosCliente[i].deletado ==
                0) {
                encontrado = 1;
                printf("\n============================\n"
                       "| PAGAMENTO %d\n"
                       "============================\n"
                       "TIPO PAGAMENTO: %s\n"
                       "DATA PAGAMENTO: %s\n"
                       "DATA A RECEBER: %s\n"
                       "DATA RECEBIMENTO: %s\n"
                       "CLIENTE: %d\n",
                       lista->listaPagamentosCliente[i].id,
                       tiposPagamento[lista->listaPagamentosCliente[i].tipoPagamento - 1],
                       lista->listaPagamentosCliente[i].dataPagamento,
                       lista->listaPagamentosCliente[i].dataAReceber,
                       lista->listaPagamentosCliente[i].dataRecebimento,
                       lista->listaPagamentosCliente[i].idCliente);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum pagamento encontrado\n\n");
        }
    } else {
        printf("Nenhum pagamento foi cadastrado\n\n");
    }
}

// Lista todas as contas de uma oficina
void listarTodosPagamentosClienteDeOficinaModel(struct ListaPagamentosCliente *lista, struct ListaCaixas *listaCaixas,
                                                int idOficina) {
    int idCaixa = getIdCaixaPorOficinaModel(listaCaixas, idOficina);
    if (idCaixa == -1) {
        return;
    }

    // Verifica se há pelo menos um cadastro
    if (lista->qtdPagamentosCliente > 0) {
        int encontrado = 0;
        char tiposPagamento[3][20] = {"Dinheiro", "Cartão de crédito", "Cartão de débito"};
        for (int i = 0; i < lista->qtdPagamentosCliente; i++) {
            if (lista->listaPagamentosCliente[i].idCaixa == idCaixa && lista->listaPagamentosCliente[i].deletado ==
                0) {
                encontrado = 1;
                printf("\n============================\n"
                       "| PAGAMENTO %d\n"
                       "============================\n"
                       "TIPO PAGAMENTO: %s\n"
                       "DATA PAGAMENTO: %s\n"
                       "DATA A RECEBER: %s\n"
                       "DATA RECEBIMENTO: %s\n"
                       "CLIENTE: %d\n",
                       lista->listaPagamentosCliente[i].id,
                       tiposPagamento[lista->listaPagamentosCliente[i].tipoPagamento - 1],
                       lista->listaPagamentosCliente[i].dataPagamento,
                       lista->listaPagamentosCliente[i].dataAReceber,
                       lista->listaPagamentosCliente[i].dataRecebimento,
                       lista->listaPagamentosCliente[i].idCliente);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum pagamento encontrado\n\n");
        }
    } else {
        printf("Nenhum pagamento foi cadastrado\n\n");
    }
}

// Listar todas as contas já recebidas de uma oficina
void listaPagamentosRecebidosClienteModel(struct ListaPagamentosCliente *lista, struct ListaCaixas *listaCaixas,
                                          int idOficina) {
    int idCaixa = getIdCaixaPorOficinaModel(listaCaixas, idOficina);
    if (idCaixa == -1) {
        return;
    }

    // Verifica se há pelo menos um cadastro
    if (lista->qtdPagamentosCliente > 0) {
        int encontrado = 0;
        char tiposPagamento[3][20] = {"Dinheiro", "Cartão de crédito", "Cartão de débito"};
        for (int i = 0; i < lista->qtdPagamentosCliente; i++) {
            if (lista->listaPagamentosCliente[i].idCaixa == idCaixa && lista->listaPagamentosCliente[i].deletado ==
                0 && strcmp(lista->listaPagamentosCliente[i].dataRecebimento, "Não pago") != 0) {
                encontrado = 1;
                printf("\n============================\n"
                       "| PAGAMENTO %d\n"
                       "============================\n"
                       "TIPO PAGAMENTO: %s\n"
                       "DATA PAGAMENTO: %s\n"
                       "DATA A RECEBER: %s\n"
                       "DATA RECEBIMENTO: %s\n"
                       "CLIENTE: %d\n",
                       lista->listaPagamentosCliente[i].id,
                       tiposPagamento[lista->listaPagamentosCliente[i].tipoPagamento - 1],
                       lista->listaPagamentosCliente[i].dataPagamento,
                       lista->listaPagamentosCliente[i].dataAReceber,
                       lista->listaPagamentosCliente[i].dataRecebimento,
                       lista->listaPagamentosCliente[i].idCliente);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum pagamento encontrado\n\n");
        }
    } else {
        printf("Nenhum pagamento foi cadastrado\n\n");
    }
}

// Listar todas as contas não recebidas de uma oficina
void listaPagamentosNaoRecebidosClienteModel(struct ListaPagamentosCliente *lista, struct ListaCaixas *listaCaixas,
                                             int idOficina) {
    int idCaixa = getIdCaixaPorOficinaModel(listaCaixas, idOficina);
    if (idCaixa == -1) {
        return;
    }

    // Verifica se há pelo menos um cadastro
    if (lista->qtdPagamentosCliente > 0) {
        int encontrado = 0;
        char tiposPagamento[3][20] = {"Dinheiro", "Cartão de crédito", "Cartão de débito"};
        for (int i = 0; i < lista->qtdPagamentosCliente; i++) {
            if (lista->listaPagamentosCliente[i].idCaixa == idCaixa && lista->listaPagamentosCliente[i].deletado ==
                0 && strcmp(lista->listaPagamentosCliente[i].dataRecebimento, "Não pago") == 0) {
                encontrado = 1;
                printf("\n============================\n"
                       "| PAGAMENTO %d\n"
                       "============================\n"
                       "TIPO PAGAMENTO: %s\n"
                       "DATA PAGAMENTO: %s\n"
                       "DATA A RECEBER: %s\n"
                       "DATA RECEBIMENTO: %s\n"
                       "CLIENTE: %d\n",
                       lista->listaPagamentosCliente[i].id,
                       tiposPagamento[lista->listaPagamentosCliente[i].tipoPagamento - 1],
                       lista->listaPagamentosCliente[i].dataPagamento,
                       lista->listaPagamentosCliente[i].dataAReceber,
                       lista->listaPagamentosCliente[i].dataRecebimento,
                       lista->listaPagamentosCliente[i].idCliente);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum pagamento encontrado\n\n");
        }
    } else {
        printf("Nenhum pagamento foi cadastrado\n\n");
    }
}
