#include "modelFornecedores.h"
#include "../pecas/modelPecas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca os dados de fornecedores nos arquivos
void buscarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento) {
    int i = 0;
    FILE *dadosFornecedores;
    char linha[sizeof(struct Fornecedores)];

    switch (opcaoArmazenamento) {
        case 1:
            dadosFornecedores = fopen("DadosFornecedores.txt", "r");

            if (dadosFornecedores == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosFornecedores)) {
                lista->qtdFornecedores++;
            }

            if (lista->qtdFornecedores > 0) {
                lista->listaFornecedores = malloc(lista->qtdFornecedores * sizeof(struct Fornecedores));
            } else {
                fclose(dadosFornecedores);
                return;
            }

            if (lista->listaFornecedores == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosFornecedores);
                return;
            }

            fseek(dadosFornecedores, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosFornecedores)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaFornecedores[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].nomeFantasia, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].razaoSocial, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].inscricaoEstadual, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].cnpj, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].endereco, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].ddd, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].telefone, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaFornecedores[i].email, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaFornecedores[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosFornecedores = fopen("DadosFornecedores.bin", "rb");

            if (dadosFornecedores == NULL) {
                return;
            }

            struct Fornecedores linhaFornecedor;

            while (fread(&linhaFornecedor, sizeof(linhaFornecedor), 1, dadosFornecedores)) {
                lista->qtdFornecedores++;
            }

            if (lista->qtdFornecedores > 0) {
                lista->listaFornecedores = malloc(lista->qtdFornecedores * sizeof(struct Fornecedores));
            } else {
                fclose(dadosFornecedores);
                return;
            }

            if (lista->listaFornecedores == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosFornecedores);
                return;
            }

            fseek(dadosFornecedores, 0, SEEK_SET);

            while (fread(&linhaFornecedor, sizeof(linhaFornecedor), 1, dadosFornecedores)) {
                lista->listaFornecedores[i] = linhaFornecedor;
                i++;
            }
            break;
    }

    fclose(dadosFornecedores);
}

// Armazena os dados de fornecedores nos arquivos
void armazenarDadosFornecedoresModel(struct ListaFornecedores *lista, int opcaoArmazenamento) {
    FILE *dadosFornecedores;

    switch (opcaoArmazenamento) {
        case 1:
            dadosFornecedores = fopen("DadosFornecedores.txt", "w");

        if (dadosFornecedores == NULL) {
            printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdFornecedores; i++) {
            fprintf(dadosFornecedores, "%d;%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                    lista->listaFornecedores[i].id,
                    lista->listaFornecedores[i].nomeFantasia,
                    lista->listaFornecedores[i].razaoSocial,
                    lista->listaFornecedores[i].inscricaoEstadual,
                    lista->listaFornecedores[i].cnpj,
                    lista->listaFornecedores[i].endereco,
                    lista->listaFornecedores[i].ddd,
                    lista->listaFornecedores[i].telefone,
                    lista->listaFornecedores[i].email,
                    lista->listaFornecedores[i].deletado);
        }

        break;
        case 2:
            dadosFornecedores = fopen("DadosFornecedores.bin", "wb");

        if (dadosFornecedores == NULL) {
            printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
            return;
        }

        for (int i = 0; i < lista->qtdFornecedores; i++) {
            fwrite(&lista->listaFornecedores[i], sizeof(struct Fornecedores), 1, dadosFornecedores);
        }
        break;
    }

    fclose(dadosFornecedores);

    free(lista->listaFornecedores);
    lista->listaFornecedores = NULL;
    lista->qtdFornecedores = 0;
}

// Aloca memória inicial na lista de fornecedores
int alocarFornecedoresModel(struct ListaFornecedores *lista) {
    lista->qtdFornecedores = 1;
    lista->listaFornecedores = malloc(sizeof(struct Fornecedores));

    if (lista->listaFornecedores == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de fornecedores conforme a necessidade em qtdAlocada
int realocarFornecedoresModel(struct ListaFornecedores *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhuma alocação foi realizada\n\n");
        return 0;
    }

    lista->qtdFornecedores += qtdAlocada;
    lista->listaFornecedores = realloc(lista->listaFornecedores, lista->qtdFornecedores * sizeof(struct Fornecedores));

    if (lista->listaFornecedores == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra um novo fornecedor
void cadastrarFornecedoresModel(struct ListaFornecedores *lista, struct Fornecedores *fornecedor) {
    int resultAlocacao = 0;
    if (lista->qtdFornecedores == 0) {
        lista->qtdFornecedores++;
        resultAlocacao = alocarFornecedoresModel(lista);
    } else {
        resultAlocacao = realocarFornecedoresModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o fornecedor.\n\n");
        return;
    }

    fornecedor->id = lista->qtdFornecedores;
    fornecedor->deletado = 0;

    lista->listaFornecedores[lista->qtdFornecedores - 1] = *fornecedor;

    printf("Fornecedor cadastrado com sucesso!\n\n");
}

// Verifica a existência do id requisitado
int verificarIDFornecedoresModel(struct ListaFornecedores *lista, int id) {
    if (lista->qtdFornecedores > 0) {
        for (int i = 0; i < lista->qtdFornecedores; i++) {
            if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return 0;
    }

    printf("Fornecedor não encontrado.\n\n");
    return 0;
}

// Atualiza o cadastro de um fornecedor
void atualizarFornecedoresModel(struct ListaFornecedores *lista, int id, struct Fornecedores *fornecedor) {
    // Busca pelo id para fazer a alteração
    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
            lista->listaFornecedores[i] = *fornecedor;
            lista->listaFornecedores[i].id = id;
            lista->listaFornecedores[i].deletado = 0;
            break;
        }
    }
}

// Lista todos os fornecedores
void listarTodosFornecedoresModel(struct ListaFornecedores *lista) {
    // Variável para verificação de listagem
    int listado = 0;

    // Verifica se há pelo menos um cadastro
    if (lista->qtdFornecedores > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdFornecedores; i++) {
            // Verifica se o índice atual existe
            if (lista->listaFornecedores[i].deletado == 0) {
                listado = 1;
                printf("\n====================="
                       "\n| FORNECEDOR %d      |"
                       "\n====================="
                       "\nNOME FANTASIA: %s"
                       "\nRAZÃO SOCIAL: %s"
                       "\nINSCRIÇÃO ESTADUAL: %s"
                       "\nCNPJ: %s"
                       "\nENDEREÇO COMPLETO: %s"
                       "\nTELEFONE: (%s) %s"
                       "\nEMAIL: %s\n",
                       lista->listaFornecedores[i].id,
                       lista->listaFornecedores[i].nomeFantasia,
                       lista->listaFornecedores[i].razaoSocial,
                       lista->listaFornecedores[i].inscricaoEstadual,
                       lista->listaFornecedores[i].cnpj,
                       lista->listaFornecedores[i].endereco,
                       lista->listaFornecedores[i].ddd,
                       lista->listaFornecedores[i].telefone,
                       lista->listaFornecedores[i].email);
            }
        }
    }

    // Se não houver, avisa que não há cadastros
    if (listado == 0) {
        printf("Nenhum fornecedor cadastrado\n\n");
    }
}

// Lista um fornecedor pelo Id
void listarFornecedoresModel(struct ListaFornecedores *lista, int id) {
    // Variável para verificar que fornecedor foi encontrado
    int encontrado = 0;

    if (lista->qtdFornecedores == 0) {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return;
    }

    // Se há um ou mais cadastros, procura pelo fornecedor com o id desejado
    for (int i = 0; i < lista->qtdFornecedores; i++) {
        // Verifica se o fornecedor está ou não deletado
        if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
            encontrado = 1;
            if (lista->listaFornecedores[i].deletado == 0) {
                printf("\n====================="
                       "\n| FORNECEDOR %d      |"
                       "\n====================="
                       "\nNOME FANTASIA: %s"
                       "\nRAZÃO SOCIAL: %s"
                       "\nINSCRIÇÃO ESTADUAL: %s"
                       "\nCNPJ: %s"
                       "\nENDEREÇO COMPLETO: %s"
                       "\nTELEFONE: (%s) %s"
                       "\nEMAIL: %s\n",
                       lista->listaFornecedores[i].id,
                       lista->listaFornecedores[i].nomeFantasia,
                       lista->listaFornecedores[i].razaoSocial,
                       lista->listaFornecedores[i].inscricaoEstadual,
                       lista->listaFornecedores[i].cnpj,
                       lista->listaFornecedores[i].endereco,
                       lista->listaFornecedores[i].ddd,
                       lista->listaFornecedores[i].telefone,
                       lista->listaFornecedores[i].email);
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Fornecedor não encontrado!\n\n");
    }
}

// Deleta um fornecedor cadastrado
void deletarFornecedoresModel(struct ListaFornecedores *lista, struct ListaPecas *pecasRelacionadas, int id) {
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdFornecedores == 0) {
        printf("Nenhum fornecedor foi cadastrado!\n\n");
        return;
    }

    // Verifica relações com peças
    if (pecasRelacionadas->qtdPecas > 0) {
        for (int i = 0; i < pecasRelacionadas->qtdPecas; i++) {
            if (pecasRelacionadas->listaPecas[i].idFornecedor == id && pecasRelacionadas->listaPecas[i].deletado == 0) {
                printf(
                    "Não foi possível deletar o fornecedor, pois os seus dados estão sendo utilizados em uma peça que já está cadastrada.\n\n");
                return;
            }
        }
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdFornecedores; i++) {
        if (lista->listaFornecedores[i].id == id && lista->listaFornecedores[i].deletado == 0) {
            encontrado = 1;
            lista->listaFornecedores[i].deletado = 1;
            printf("Fornecedor deletado com sucesso!\n\n");
            return;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Fornecedor não encontrado!\n\n");
    }
}
