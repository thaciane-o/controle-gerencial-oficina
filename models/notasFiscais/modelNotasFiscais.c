#include "modelNotasFiscais.h"
#include "../../models/pecasNotas/modelPecasNotas.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/oficina/modelOficina.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das notas no arquivo
void buscarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosNotas;
    char linha[sizeof(struct NotasFiscais) * 10];

    switch (opcaoArmazenamento) {
        case 1:

            dadosNotas = fopen("DadosNotasFiscais.txt", "r");

            if (dadosNotas == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosNotas)) {
                lista->qtdNotas++;
            }

            if (lista->qtdNotas > 0) {
                lista->listaNotas = malloc(lista->qtdNotas * sizeof(struct NotasFiscais));
            } else {
                fclose(dadosNotas);
                return;
            }

            if (lista->listaNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosNotas);
                return;
            }

            fseek(dadosNotas, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosNotas)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaNotas[i].id = atoi(token);
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
                    lista->listaNotas[i].totalNota = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaNotas[i].idOficina = atoi(token);
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
            dadosNotas = fopen("DadosNotasFiscais.bin", "rb");

            if (dadosNotas == NULL) {
                return;
            }

            struct NotasFiscais linhaNota;


            while (fread(&linhaNota, sizeof(linhaNota), 1, dadosNotas)) {
                lista->qtdNotas++;
            }

            if (lista->qtdNotas > 0) {
                lista->listaNotas = malloc(lista->qtdNotas * sizeof(struct NotasFiscais));
            } else {
                fclose(dadosNotas);
                return;
            }

            if (lista->listaNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosNotas);
                return;
            }

            fseek(dadosNotas, 0, SEEK_SET);


            while (fread(&linhaNota, sizeof(linhaNota), 1, dadosNotas)) {
                lista->listaNotas[i] = linhaNota;
                i++;
            }
            break;
    }

    fclose(dadosNotas);
}

// Armazena os dados das notas no arquivo
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
                fprintf(dadosNotas, "%d;%.2f;%.2f;%.2f;%d;%d;%d\n",
                        lista->listaNotas[i].id,
                        lista->listaNotas[i].frete,
                        lista->listaNotas[i].imposto,
                        lista->listaNotas[i].totalNota,
                        lista->listaNotas[i].idOficina,
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
                fwrite(&lista->listaNotas[i], sizeof(struct NotasFiscais), 1, dadosNotas);
            }
            break;
    }

    fclose(dadosNotas);

    free(lista->listaNotas);
    lista->listaNotas = NULL;

    lista->qtdNotas = 0;
}

// Aloca a memória inicial para a lista de notas
int alocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista) {
    lista->qtdNotas = 1;
    lista->listaNotas = malloc(sizeof(struct NotasFiscais));


    if (lista->listaNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória da nota conforme a quantidade que deseja alocar (qtdAloca)
int realocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdAloca) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada.\n\n");
        return 0;
    }

    lista->qtdNotas += qtdAloca;

    lista->listaNotas = realloc(lista->listaNotas, lista->qtdNotas * sizeof(struct NotasFiscais));


    // Verifica se a alocação deu certo
    if (lista->listaNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova nota
void cadastrarNotasFiscaisModel(struct ListaNotasFiscais *lista, struct NotasFiscais *novaNotaFiscal,
                                struct ListaPecas *listaPecas, struct ListaOficinas *listaOficinas,
                                struct ListaPecasNotas *listaPecasNotas, int totalPecas) {
    int resultAlocacao = 0;
    float fretePorPeca, impostoPorPeca;


    impostoPorPeca = novaNotaFiscal->imposto / totalPecas;

    fretePorPeca = novaNotaFiscal->frete / totalPecas;


    // Buscando peça na lista de peças para atualizações
    for (int i = 0; i < listaPecas->qtdPecas; i++) {
        for (int j = 0; j < listaOficinas->qtdOficinas; j++) {
            for (int k = 0; k < listaPecasNotas->qtdPecasNotas; k++) {
                if (listaPecas->listaPecas[i].id == listaPecasNotas->listaPecasNotas[k].idPeca && listaPecasNotas->
                    listaPecasNotas[k].idNota == lista->qtdNotas + 1 && listaOficinas->listaOficinas[j].id ==
                    novaNotaFiscal->idOficina) {
                    // Atualizando quantidade em estoque
                    listaPecas->listaPecas[i].qtdEstoque += listaPecasNotas->listaPecasNotas[k].qtdPecas;

                    // Atualizando preço venda da peça
                    listaPecas->listaPecas[i].precoVenda =
                            listaPecas->listaPecas[i].precoCusto + impostoPorPeca + fretePorPeca;
                    listaPecas->listaPecas[i].precoVenda += listaPecas->listaPecas[i].precoVenda * listaOficinas->
                            listaOficinas[j].porcentagemLucro / 100;


                    novaNotaFiscal->totalNota += listaPecas->listaPecas[i].precoCusto * listaPecasNotas->listaPecasNotas
                            [k].qtdPecas;
                }
            }
        }
    }

    novaNotaFiscal->totalNota += novaNotaFiscal->imposto + novaNotaFiscal->frete;

    if (lista->qtdNotas == 0) {
        lista->qtdNotas++;
        resultAlocacao = alocarMemoriaNotasFiscaisModel(lista);
    } else {
        // Se já tiver, aumenta a alocação em 1
        resultAlocacao = realocarMemoriaNotasFiscaisModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar a nota.\n\n");
        return;
    }

    novaNotaFiscal->id = lista->qtdNotas;
    novaNotaFiscal->deletado = 0;

    lista->listaNotas[lista->qtdNotas - 1] = *novaNotaFiscal;

    printf("Nota cadastrada com sucesso!\n\n");
}

// Listagem de todas as notas
void listarTodasNotasFiscaisModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                                  struct ListaPecas *listaPecas,
                                  struct ListaFornecedores *listaFornecedores) {
    int listado = 0, encontraFornecedor;

    // Verifica se há pelo menos um cadastro
    if (lista->qtdNotas > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdNotas; i++) {
            // Encontra fornecedor relacionado a nota atual
            for (int j = 0; j < listaFornecedores->qtdFornecedores; j++) {
                if (lista->listaNotas[i].deletado == 0 && lista->listaNotas[i].idFornecedor == listaFornecedores->
                    listaFornecedores[j].id) {
                    encontraFornecedor = j;
                    break;
                }
            }

            // Verifica se o índice atual existe
            if (lista->listaNotas[i].deletado == 0) {
                listado = 1;
                printf("\n====================\n"
                       "| NOTA FISCAL %d    |\n"
                       "====================\n"
                       "FORNECEDOR: %s\n"
                       "CNPJ: %s\n"
                       "FRETE: $%.2f  |  IMPOSTO $%.2f\n"
                       "|          PRODUTOS           |",
                       lista->listaNotas[i].id,
                       listaFornecedores->listaFornecedores[encontraFornecedor].nomeFantasia,
                       listaFornecedores->listaFornecedores[encontraFornecedor].cnpj,
                       lista->listaNotas[i].frete,
                       lista->listaNotas[i].imposto);

                // Inicia listagem de todas as peças relacionadas a nota
                for (int j = 0; j < listaPecasNotas->qtdPecasNotas; j++) {
                    for (int k = 0; k < listaPecas->qtdPecas; k++) {
                        if (listaPecasNotas->listaPecasNotas[j].idPeca == listaPecas->listaPecas[k].id &&
                            listaPecasNotas->listaPecasNotas[j].idNota == lista->listaNotas[i].id &&
                            listaPecasNotas->listaPecasNotas[j].deletado == 0) {
                            printf("\nPEÇA: %s\n"
                                   "ID: %d\n"
                                   "PREÇO CUSTO: $%.2f\n"
                                   "QUANTIDADE: %d\n"
                                   "TOTAL DA PEÇA: $%.2f\n\n",
                                   listaPecas->listaPecas[k].descricao,
                                   listaPecas->listaPecas[k].id,
                                   listaPecas->listaPecas[k].precoCusto,
                                   listaPecasNotas->listaPecasNotas[j].qtdPecas,
                                   listaPecasNotas->listaPecasNotas[j].qtdPecas * listaPecas->listaPecas[k].precoCusto);
                        }
                    }
                }
                printf("PREÇO TOTAL: $%.2f\n\n", lista->listaNotas[i].totalNota);
            }
        }
    }

    // Se não houver, avisa que não há cadastros
    if (listado == 0) {
        printf("Nenhuma Nota cadastrado\n\n");
    }
}

// Listagem de nota por ID
void listarNotaFiscalModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                           struct ListaPecas *listaPecas,
                           struct ListaFornecedores *listaFornecedores, int id) {
    // Verifica se há pelo menos um cadastro
    if (lista->qtdNotas > 0) {
        // Se há um ou mais cadastros, procura pela peça com o id desejado
        int encontrado = -1, encontraFornecedor;

        // Encontra o fornecedor relacionado a nota atual
        for (int i = 0; i < lista->qtdNotas; i++) {
            for (int j = 0; j < listaFornecedores->qtdFornecedores; j++) {
                if (lista->listaNotas[i].id == id && lista->listaNotas[i].deletado == 0 && lista->listaNotas[i].
                    idFornecedor == listaFornecedores->listaFornecedores[j].id) {
                    encontrado = i;
                    encontraFornecedor = j;
                    break;
                }
            }
        }

        if (encontrado != -1) {
            printf("\n====================\n"
                   "| NOTA FISCAL %d    |\n"
                   "====================\n"
                   "FORNECEDOR: %s\n"
                   "CNPJ: %s\n"
                   "FRETE: $%.2f\n"
                   "IMPOSTO $%.2f\n"
                   "\n====================\n"
                     "|     PRODUTOS     |\n"
                     "====================\n",
                   lista->listaNotas[encontrado].id,
                   listaFornecedores->listaFornecedores[encontraFornecedor].nomeFantasia,
                   listaFornecedores->listaFornecedores[encontraFornecedor].cnpj,
                   lista->listaNotas[encontrado].frete,
                   lista->listaNotas[encontrado].imposto);

            // Inicia listagem de todas as peças relacionadas a nota
            for (int i = 0; i < listaPecasNotas->qtdPecasNotas; i++) {
                for (int j = 0; j < listaPecas->qtdPecas; j++) {
                    if (listaPecasNotas->listaPecasNotas[j].idPeca == listaPecas->listaPecas[j].id &&
                        listaPecasNotas->listaPecasNotas[j].idNota == lista->listaNotas[encontrado].id &&
                        listaPecasNotas->listaPecasNotas[j].deletado == 0) {
                        printf("\nPEÇA: %s\n"
                               "ID: %d\n"
                               "PREÇO CUSTO: $%.2f\n"
                               "QUANTIDADE: %d\n"
                               "TOTAL DA PEÇA: $%.2f\n\n",
                               listaPecas->listaPecas[j].descricao,
                               listaPecas->listaPecas[j].id,
                               listaPecas->listaPecas[j].precoCusto,
                               listaPecasNotas->listaPecasNotas[i].qtdPecas,
                               listaPecasNotas->listaPecasNotas[i].qtdPecas * listaPecas->listaPecas[j].precoCusto);
                    }
                }
            }
            printf("PREÇO TOTAL: $%2.f\n\n", lista->listaNotas[encontrado].totalNota);
        } else {
            printf("Nenhuma nota encontrada.\n\n");
        }
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhuma nota foi cadastrada.\n\n");
    }
}

// Listagem de nota por fornecedor
void buscarNotasFiscaisPorFornecedorModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas,
                                          struct ListaPecas *listaPecas,
                                          struct ListaFornecedores *listaFornecedores, int idFornecedor) {
    int encontraFornecedor;
    // Verifica se há pelo menos um cadastro
    if (lista->qtdNotas > 0) {
        // Se há um ou mais cadastros, procura pela peça com o id desejado
        int encontrado = 0;
        for (int i = 0; i < lista->qtdNotas; i++) {
            // Encontra o fornecedor da peça atual
            for (int j = 0; j < listaFornecedores->qtdFornecedores; j++) {
                if (lista->listaNotas[i].idFornecedor == idFornecedor && lista->listaNotas[i].deletado == 0 && lista->
                    listaNotas[i].
                    idFornecedor == listaFornecedores->listaFornecedores[j].id) {
                    encontraFornecedor = j;
                    break;
                }
            }

            if (lista->listaNotas[i].idFornecedor == idFornecedor && lista->listaNotas[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================\n"
                       "|  NOTA FISCAL %d  |\n"
                       "====================\n"
                       "FORNECEDOR: %s\n"
                       "CNPJ: %s\n"
                       "FRETE: $%.2f  |  IMPOSTO $%.2f\n"
                       "|          PRODUTOS           |",
                       lista->listaNotas[i].id,
                       listaFornecedores->listaFornecedores[encontraFornecedor].nomeFantasia,
                       listaFornecedores->listaFornecedores[encontraFornecedor].cnpj,
                       lista->listaNotas[i].frete,
                       lista->listaNotas[i].imposto);

                // Inicia listagem de todas as peças relacionadas a nota
                for (int j = 0; j < listaPecasNotas->qtdPecasNotas; j++) {
                    for (int k = 0; k < listaPecas->qtdPecas; k++) {
                        if (listaPecasNotas->listaPecasNotas[j].idPeca == listaPecas->listaPecas[k].id &&
                            listaPecasNotas->listaPecasNotas[j].idNota == lista->listaNotas[i].id &&
                            listaPecasNotas->listaPecasNotas[j].deletado == 0) {
                            printf("\nPEÇA: %s\n"
                                   "ID: %d\n"
                                   "PREÇO CUSTO: $%.2f\n"
                                   "QUANTIDADE: %d\n"
                                   "TOTAL DA PEÇA: $%.2f\n\n",
                                   listaPecas->listaPecas[k].descricao,
                                   listaPecas->listaPecas[k].id,
                                   listaPecas->listaPecas[k].precoCusto,
                                   listaPecasNotas->listaPecasNotas[j].qtdPecas,
                                   listaPecasNotas->listaPecasNotas[j].qtdPecas * listaPecas->listaPecas[k].precoCusto);
                        }
                    }
                }
                printf("PREÇO TOTAL: $%2.f\n\n", lista->listaNotas[i].totalNota);
            }
        }

        if (encontrado == 0) {
            printf("Nenhuma nota encontrada.\n\n");
        }
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhuma nota foi cadastrada.\n\n");
    }
}

// Deleção de nota
void deletarNotaModel(struct ListaNotasFiscais *lista, struct ListaPecasNotas *listaPecasNotas, int id) {
    // Auxiliar para saber se encontrou o id.
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdNotas == 0) {
        printf("Nenhuma nota foi cadastrada.\n\n");
        return;
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdNotas; i++) {
        if (lista->listaNotas[i].id == id && lista->listaNotas[i].deletado == 0) {
            encontrado = 1;
            lista->listaNotas[i].deletado = 1;
            deletarPecaNotaModel(listaPecasNotas, lista->listaNotas[i].id);
            printf("Nota deletada com sucesso!\n\n");
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Nota não encontrada.\n\n");
    }
}

int verificarRelacaoFornecedorModel(struct ListaPecas *listaPecas,
                                    struct NotasFiscais *notaFiscal, int idPeca) {
    for (int i = 0; i < listaPecas->qtdPecas; i++) {
        if (idPeca == listaPecas->listaPecas[i].id && listaPecas->listaPecas[i].idFornecedor == notaFiscal->
            idFornecedor) {
            return 1;
        }
    }
    printf("Esta peça não é fornecida pelo fornecedor digitado\n\n");
    return 0;
}

int verificarRelacaoOficinaModel(struct ListaPecas *listaPecas,
                                 struct NotasFiscais *notaFiscal, int idPeca) {
    for (int i = 0; i < listaPecas->qtdPecas; i++) {
        if (idPeca == listaPecas->listaPecas[i].id && listaPecas->listaPecas[i].idOficina == notaFiscal->idOficina) {
            return 1;
        }
    }
    printf("A oficina fornecida não é proprietaria desta peça\n\n");
    return 0;
}
