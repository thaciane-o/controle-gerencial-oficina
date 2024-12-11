#include "modelPecas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das pecas no arquivo
void buscarDadosPecaModel(struct ListaPecas *lista, int opcaoArmazenamento) {
    int i = 0;
    char linha[sizeof(struct Pecas)];

    FILE *dadosPecas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPecas = fopen("DadosPecas.txt", "r");

            if (dadosPecas == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosPecas)) {
                lista->qtdPecas++;
            }

            if (lista->qtdPecas > 0) {
                lista->listaPecas = malloc(lista->qtdPecas * sizeof(struct Pecas));
            } else {
                return;
            }

            if (lista->listaPecas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosPecas, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosPecas)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaPecas[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaPecas[i].descricao, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaPecas[i].fabricante, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecas[i].precoCusto = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecas[i].precoVenda = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecas[i].qtdEstoque = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecas[i].estoqueMinimo = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecas[i].idFornecedor = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecas[i].deletado = atoi(token);
                }

                i++;
            }
            break;

        case 2:
            dadosPecas = fopen("DadosPecas.bin", "rb");

            if (dadosPecas == NULL) {
                return;
            }

            struct Pecas linhaPeca;

            while (fread(&linhaPeca, sizeof(linhaPeca), 1, dadosPecas)) {
                lista->qtdPecas++;
            }

            if (lista->qtdPecas > 0) {
                lista->listaPecas = malloc(lista->qtdPecas * sizeof(struct Pecas));
            } else {
                return;
            }

            if (lista->listaPecas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosPecas, 0, SEEK_SET);

            while (fread(&linhaPeca, sizeof(linhaPeca), 1, dadosPecas)) {
                lista->listaPecas[i] = linhaPeca;
                i++;
            }
            break;
    }

    fclose(dadosPecas);
}

// Armazena os dados das pecas no arquivo
void armazenarDadosPecaModel(struct ListaPecas *lista, int opcaoArmazenamento) {
    FILE *dadosPecas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPecas = fopen("DadosPecas.txt", "w");

            if (dadosPecas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPecas; i++) {
                fprintf(dadosPecas, "%d;%s;%s;%f;%f;%d;%d;%d;%d\n",
                        lista->listaPecas[i].id,
                        lista->listaPecas[i].descricao,
                        lista->listaPecas[i].fabricante,
                        lista->listaPecas[i].precoCusto,
                        lista->listaPecas[i].precoVenda,
                        lista->listaPecas[i].qtdEstoque,
                        lista->listaPecas[i].estoqueMinimo,
                        lista->listaPecas[i].idFornecedor,
                        lista->listaPecas[i].deletado);
            }
            break;

        case 2:
            dadosPecas = fopen("DadosPecas.bin", "wb");

            if (dadosPecas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPecas; i++) {
                fwrite(&lista->listaPecas[i], sizeof(struct Pecas), 1, dadosPecas);
            }
            break;
    }

    fclose(dadosPecas);

    free(lista->listaPecas);
    lista->listaPecas = NULL;

    lista->qtdPecas = 0;
}

// Aloca a memória inicial para a lista de peças
int alocarMemoriaPecaModel(struct ListaPecas *lista) {
    lista->qtdPecas = 1;
    lista->listaPecas = malloc(sizeof(struct Pecas));

    if (lista->listaPecas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória da peca conforme a quantidade que deseja alocar (qtdAloca)
int realocarMemoriaPecaModel(struct ListaPecas *lista, int qtdAloca) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada.\n\n");
        return 0;
    }

    lista->qtdPecas += qtdAloca;
    lista->listaPecas = realloc(lista->listaPecas, lista->qtdPecas * sizeof(struct Pecas));

    // Verifica se a alocação deu certo
    if (lista->listaPecas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova peca
void cadastrarPecaModel(struct ListaPecas *lista, struct Pecas *pecaCadastrando) {

    int resultAlocacao = 0;

    if (lista->qtdPecas == 0) {
        lista->qtdPecas++;
        resultAlocacao = alocarMemoriaPecaModel(lista);
    } else {
        // Se já tiver, aumenta a alocação em 1
        resultAlocacao = realocarMemoriaPecaModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar a peça.\n\n");
        return;
    }

    pecaCadastrando->id = lista->qtdPecas;
    pecaCadastrando->deletado = 0;

    lista->listaPecas[lista->qtdPecas - 1] = *pecaCadastrando;

    printf("Peça cadastrada com sucesso!\n\n");
}

// Verifica a existência do id requisitado
int verificarIDPecaModel(struct ListaPecas *lista, int id) {
    // Procura a peça com o id inserido
    if (lista->qtdPecas > 0) {
        for (int i = 0; i < lista->qtdPecas; i++) {
            if (lista->listaPecas[i].id == id && lista->listaPecas[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhuma peça foi cadastrada!\n\n");
        return 0;
    }

    printf("Peca não encontrada!\n\n");
    return 0;
}

// Atualiza uma peça cadastrada
void atualizarPecaModel(struct ListaPecas *lista, int id, struct Pecas *pecaAlterando) {
    // Busca pelo id para fazer a alteração.
    for (int i = 0; i < lista->qtdPecas; i++) {
        if (lista->listaPecas[i].id == id && lista->listaPecas[i].deletado == 0) {
            lista->listaPecas[i] = *pecaAlterando;
            lista->listaPecas[i].id = id;
            lista->listaPecas[i].deletado = 0;
            break;
        }
    }
}

// Lista todas as peças cadastradas
void listarTodosPecaModel(struct ListaPecas *lista) {
    // Variável para verificação de listagem
    int listado = 0;

    // Verifica se há pelo menos um cadastro
    if (lista->qtdPecas > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdPecas; i++) {
            // Verifica se o índice atual existe
            if (lista->listaPecas[i].deletado == 0) {
                listado = 1;
                printf("\n====================\n"
                       "| PEÇA %d           |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "FABRICANTE: %s\n"
                       "PREÇO DE CUSTO: $%.2f\n"
                       "PREÇO DE VENDA: $%.2f\n"
                       "QUANTIDADE EM ESTOQUE: %d\n"
                       "ESTOQUE MÍNIMO: %d\n"
                       "FORNECEDOR: %d\n",
                       lista->listaPecas[i].id,
                       lista->listaPecas[i].descricao,
                       lista->listaPecas[i].fabricante,
                       lista->listaPecas[i].precoCusto,
                       lista->listaPecas[i].precoVenda,
                       lista->listaPecas[i].qtdEstoque,
                       lista->listaPecas[i].estoqueMinimo,
                       lista->listaPecas[i].idFornecedor);
            }
        }
    }

    // Se não houver, avisa que não há cadastros
    if (listado == 0) {
        printf("Nenhuma peça cadastrado\n\n");
    }
}

// Busca uma peça cadastrada pelo seu id
void listarPecaModel(struct ListaPecas *lista, int id) {
    // Verifica se há pelo menos um cadastro
    if (lista->qtdPecas > 0) {
        // Se há um ou mais cadastros, procura pela peça com o id desejado
        int encontrado = -1;
        for (int i = 0; i < lista->qtdPecas; i++) {
            if (lista->listaPecas[i].id == id && lista->listaPecas[i].deletado == 0) {
                encontrado = i;
                break;
            }
        }

        if (encontrado != -1) {
            printf("\n====================\n"
                   "| PEÇA %d           |\n"
                   "====================\n"
                   "DESCRIÇÃO: %s\n"
                   "FABRICANTE: %s\n"
                   "PREÇO DE CUSTO: $%.2f\n"
                   "PREÇO DE VENDA: $%.2f\n"
                   "QUANTIDADE EM ESTOQUE: %d\n"
                   "ESTOQUE MÍNIMO: %d\n"
                   "FORNECEDOR: %d\n",
                   lista->listaPecas[encontrado].id,
                   lista->listaPecas[encontrado].descricao,
                   lista->listaPecas[encontrado].fabricante,
                   lista->listaPecas[encontrado].precoCusto,
                   lista->listaPecas[encontrado].precoVenda,
                   lista->listaPecas[encontrado].qtdEstoque,
                   lista->listaPecas[encontrado].estoqueMinimo,
                   lista->listaPecas[encontrado].idFornecedor);
        } else {
            printf("Nenhuma peça encontrada.\n\n");
        }
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhuma peça foi cadastrada.\n\n");
    }
}

// Busca uma peça cadastrada pelo seu id
void buscarPecasPorFornecedorModel(struct ListaPecas *lista, int idFornecedor) {
    // Verifica se há pelo menos um cadastro
    if (lista->qtdPecas > 0) {
        // Se há um ou mais cadastros, procura pela peça com o id desejado
        int encontrado = 0;
        for (int i = 0; i < lista->qtdPecas; i++) {
            if (lista->listaPecas[i].idFornecedor == idFornecedor && lista->listaPecas[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================\n"
                       "| PEÇA %d           |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "FABRICANTE: %s\n"
                       "PREÇO DE CUSTO: $%.2f\n"
                       "PREÇO DE VENDA: $%.2f\n"
                       "QUANTIDADE EM ESTOQUE: %d\n"
                       "ESTOQUE MÍNIMO: %d\n"
                       "FORNECEDOR: %d\n",
                       lista->listaPecas[i].id,
                       lista->listaPecas[i].descricao,
                       lista->listaPecas[i].fabricante,
                       lista->listaPecas[i].precoCusto,
                       lista->listaPecas[i].precoVenda,
                       lista->listaPecas[i].qtdEstoque,
                       lista->listaPecas[i].estoqueMinimo,
                       lista->listaPecas[i].idFornecedor);
                break;
            }
        }

        if (encontrado == 0) {
            printf("Nenhuma peça encontrada.\n\n");
        }
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhuma peça foi cadastrada.\n\n");
    }
}

// Deleta uma peça cadastrada
void deletarPecaModel(struct ListaPecas *lista, int id) {
    // Auxiliar para saber se encontrou o id.
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdPecas == 0) {
        printf("Nenhuma peça foi cadastrada.\n");
        return;
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdPecas; i++) {
        if (lista->listaPecas[i].id == id && lista->listaPecas[i].deletado == 0) {
            encontrado = 1;
            lista->listaPecas[i].deletado = 1;
            printf("Peça deletada com sucesso!\n");
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Peça não encontrada.\n");
    }
}
