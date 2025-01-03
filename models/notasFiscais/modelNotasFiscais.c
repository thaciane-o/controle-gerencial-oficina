#include "modelNotasFiscais.h"
#include "..\..\models\estoques\modelEstoques.h"
#include "..\..\models\pecas\modelPecas.h"
#include "..\..\models\fornecedores\modelFornecedores.h"
#include "..\..\models\oficina\modelOficina.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das pecas no arquivo
void buscarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,  int opcaoArmazenamento) {
    int i = 0;
    char linha[sizeof(struct notasFiscais) * sizeof(int)];

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
                char *token2, *token3;

                if (token != NULL) {
                    lista->listaNotas[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    token2 = token;
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    token3 = token;
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaNotas[i].tamListaPecas = atoi(token);
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
                    lista->listaNotas[i].precoVendaTotal = atof(token);
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

                lista->listaNotas[i].idPecas = malloc(sizeof(int));
                lista->listaNotas[i].qtdPecas = malloc(sizeof(int));

                int j = 0;
                token2 = strtok(token2, ",");
                while (token2 != NULL) {
                    lista->listaNotas[i].idPecas = realloc(lista->listaNotas[i].idPecas,sizeof(int)*(j+1));
                    lista->listaNotas[i].idPecas[j] = atoi(token2);
                    token2 = strtok(NULL, ",");
                    j++;
                }
                token3 = strtok(token3, ",");
                j=0;
                while (token3 != NULL) {
                    lista->listaNotas[i].qtdPecas = realloc(lista->listaNotas[i].qtdPecas,sizeof(int)*(j+1));
                    lista->listaNotas[i].qtdPecas[j] = atoi(token3);
                    token3 = strtok(NULL, ",");
                    j++;
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
                fprintf(dadosNotas, "%d;%s;%s;%d;%f;%f;%f;%d;%d;%d\n",
                        lista->listaNotas[i].id,
                        ordenarListaPecas(lista, lista->listaNotas[i].tamListaPecas, i, 0),
                        ordenarListaPecas(lista, lista->listaNotas[i].tamListaPecas, i, 1),
                        lista->listaNotas[i].tamListaPecas,
                        lista->listaNotas[i].frete,
                        lista->listaNotas[i].imposto,
                        lista->listaNotas[i].precoVendaTotal,
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
                fwrite(&lista->listaNotas[i], sizeof(struct notasFiscais) + sizeof(lista->listaNotas[i].idPecas) + sizeof(lista->listaNotas[i].qtdPecas), 1, dadosNotas);
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

    lista->listaNotas[lista->qtdNotas-1].idPecas = malloc(qtdPecas * sizeof(int));
    lista->listaNotas[lista->qtdNotas-1].qtdPecas = malloc(qtdPecas * sizeof(int));

    // Verifica se a alocação deu certo
    if (lista->listaNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova peca
void cadastrarNotasFiscaisModel(struct ListaNotasFiscais *lista, struct notasFiscais *novaNotaFiscal, struct ListaPecas *listaPecas, struct ListaOficinas *listaOficinas, int qtdPecas) {
    int resultAlocacao = 0, totalPecas = 0;
    float fretePorPeca, impostoPorPeca;

    for (int i = 0; i < novaNotaFiscal->tamListaPecas; i++) {
        totalPecas += novaNotaFiscal->qtdPecas[i];
    }

    impostoPorPeca = novaNotaFiscal->imposto/totalPecas;

    fretePorPeca = novaNotaFiscal->frete/totalPecas;

    for (int i = 0; i < listaPecas->qtdPecas; i++) {
        for (int j = 0; j < listaOficinas->qtdOficinas; j++) {
            for (int k = 0; k < novaNotaFiscal->tamListaPecas; k++) {
                if (listaPecas->listaPecas[i].id == novaNotaFiscal->idPecas[k] && listaOficinas->listaOficinas[j].id == novaNotaFiscal->idOficina) {

                    listaPecas->listaPecas[i].qtdEstoque += novaNotaFiscal->qtdPecas[k];
                    listaPecas->listaPecas[i].precoVenda = listaPecas->listaPecas[i].precoCusto + impostoPorPeca + fretePorPeca;
                    listaPecas->listaPecas[i].precoVenda += listaPecas->listaPecas[i].precoVenda * listaOficinas->
                            listaOficinas[j].porcentagemLucro / 100;
                    novaNotaFiscal->precoVendaTotal += listaPecas->listaPecas[i].precoVenda * novaNotaFiscal->qtdPecas[k];
                }
            }
        }
    }
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

int verificarRelacaoFornecedorModel(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                                    struct notasFiscais *notaFiscal, int idPeca) {
    for (int i = 0; i < listaPecas->qtdPecas; i++) {

        if (idPeca == listaPecas->listaPecas[i].id && listaPecas->listaPecas[i].idFornecedor == notaFiscal->idFornecedor) {
            return 1;
        }

    }
    printf("Esta peça não é fornecida pelo fornecedor digitado\n\n");
    return 0;
}

void listarTodasNotasFiscaisModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,
    struct ListaFornecedores *listaFornecedores) {
    int listado = 0, *encontraPecas, encontraFornecedor, aux = 0;

    // Verifica se há pelo menos um cadastro
    if (lista->qtdNotas > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdNotas; i++) {
            // Verifica se o índice atual existe
            if (lista->listaNotas[i].deletado == 0) {
                listado = 1;
                for (int j = 0; j < listaFornecedores->qtdFornecedores; j++) {
                    if (lista->listaNotas[i].idFornecedor == listaFornecedores->listaFornecedores[j].id) {

                        encontraPecas = malloc(sizeof(int) * lista->listaNotas[i].tamListaPecas);

                        int k = 0;
                        aux = 0;
                        while (aux != lista->listaNotas[i].tamListaPecas) {
                            if (lista->listaNotas[i].idPecas[aux] == listaPecas->listaPecas[k].id) {
                                encontraPecas[aux] = k;
                                k = 0;
                                aux++;
                            }
                            k++;
                        }
                        encontraFornecedor = j;
                        break;
                        }
                }
                printf("\n====================\n"
                   "| NOTA FISCAL %d    |\n"
                   "====================\n"
                   "FORNECEDOR: %s\n"
                   "CNPJ: %s\n"
                   "FRETE: $%.2f  |  IMPOSTO $%.2f\n"
                   "|                  PRODUTOS                 |",
                   lista->listaNotas[i].id,
                   listaFornecedores->listaFornecedores[encontraFornecedor].nomeFantasia,
                   listaFornecedores->listaFornecedores[encontraFornecedor].cnpj,
                   lista->listaNotas[i].frete,
                   lista->listaNotas[i].imposto);
                for (int j = 0; j < lista->listaNotas[i].tamListaPecas; j++) {
                    printf("\n%s\n"
                        "PREÇO CUSTO: $%.2f\n"
                        "QUANTIDADE: %d\n"
                        "TOTAL DA PEÇA: $%.2f\n\n",
                        listaPecas->listaPecas[encontraPecas[j]].descricao,
                        listaPecas->listaPecas[encontraPecas[j]].precoCusto,
                        lista->listaNotas[i].qtdPecas[j],
                        lista->listaNotas[i].qtdPecas[j] * listaPecas->listaPecas[encontraPecas[j]].precoCusto);
                }
                printf("PREÇO TOTAL: $%2.f\n\n", lista->listaNotas[i].precoVendaTotal);
                free(encontraPecas);
            }
        }
    }

    // Se não houver, avisa que não há cadastros
    if (listado == 0) {
        printf("Nenhuma peça cadastrado\n\n");
    }
}

void listarNotaFiscalModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,
    struct ListaFornecedores *listaFornecedores, int id) {

    // Verifica se há pelo menos um cadastro
    if (lista->qtdNotas > 0) {
        // Se há um ou mais cadastros, procura pela peça com o id desejado
        int encontrado = -1, encontraFornecedor, *encontraPecas, aux;

        for (int i = 0; i < lista->qtdNotas; i++) {
            for (int j = 0; j < listaFornecedores->qtdFornecedores; j++) {
                if (lista->listaNotas[i].id == id && lista->listaNotas[i].deletado == 0 && lista->listaNotas[i].
                    idFornecedor == listaFornecedores->listaFornecedores[j].id) {

                    encontraPecas = malloc(sizeof(int) * lista->listaNotas[i].tamListaPecas);

                    int k = 0;
                    aux = 0;
                    while (aux != lista->listaNotas[i].tamListaPecas) {
                        if (lista->listaNotas[i].idPecas[aux] == listaPecas->listaPecas[k].id) {
                            encontraPecas[aux] = k;
                            k = 0;
                            aux++;
                        }
                        k++;
                    }
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
                   "FRETE: $%.2f  |  IMPOSTO $%.2f\n"
                   "|                  PRODUTOS                 |",
                   lista->listaNotas[encontrado].id,
                   listaFornecedores->listaFornecedores[encontraFornecedor].nomeFantasia,
                   listaFornecedores->listaFornecedores[encontraFornecedor].cnpj,
                   lista->listaNotas[encontrado].frete,
                   lista->listaNotas[encontrado].imposto);
            for (int i = 0; i < lista->listaNotas[encontrado].tamListaPecas; i++) {
                printf("\n%s\n"
                    "PREÇO CUSTO: $%.2f\n"
                    "QUANTIDADE: %d\n"
                    "TOTAL DA PEÇA: $%.2f\n\n",
                    listaPecas->listaPecas[encontraPecas[i]].descricao,
                    listaPecas->listaPecas[encontraPecas[i]].precoCusto,
                    lista->listaNotas[encontrado].qtdPecas[i],
                    lista->listaNotas[encontrado].qtdPecas[i] * listaPecas->listaPecas[encontraPecas[i]].precoCusto);
            }
            printf("PREÇO TOTAL: $%2.f\n\n", lista->listaNotas[encontrado].precoVendaTotal);
            free(encontraPecas);
        } else {
            printf("Nenhuma nota encontrada.\n\n");
            free(encontraPecas);
        }
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhuma nota foi cadastrada.\n\n");
    }
}

void buscarNotasFiscaisPorFornecedorModel(struct ListaNotasFiscais *lista, struct ListaPecas *listaPecas,
    struct ListaFornecedores *listaFornecedores, int idFornecedor) {
    int *encontraPecas, aux = 0, encontraFornecedor;
    // Verifica se há pelo menos um cadastro
    if (lista->qtdNotas > 0) {
        // Se há um ou mais cadastros, procura pela peça com o id desejado
        int encontrado = 0;
        for (int i = 0; i < lista->qtdNotas; i++) {
            for (int j = 0; j < listaFornecedores->qtdFornecedores; j++) {
                if (lista->listaNotas[i].idFornecedor == idFornecedor && lista->listaNotas[i].deletado == 0 && idFornecedor == listaFornecedores->listaFornecedores[j].id) {

                    encontraPecas = malloc(sizeof(int) * lista->listaNotas[i].tamListaPecas);

                    int k = 0;
                    aux = 0;
                    while (aux != lista->listaNotas[i].tamListaPecas) {
                        if (lista->listaNotas[i].idPecas[aux] == listaPecas->listaPecas[k].id) {
                            encontraPecas[aux] = k;
                            k = 0;
                            aux++;
                        }
                        k++;
                    }
                    encontraFornecedor = j;
                    break;
                }
            }
            if (lista->listaNotas[i].idFornecedor == idFornecedor && lista->listaNotas[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================\n"
                       "| NOTA FISCAL %d    |\n"
                       "====================\n"
                       "FORNECEDOR: %s\n"
                       "CNPJ: %s\n"
                       "FRETE: $%.2f  |  IMPOSTO $%.2f\n"
                       "|                  PRODUTOS                 |",
                       lista->listaNotas[i].id,
                       listaFornecedores->listaFornecedores[encontraFornecedor].nomeFantasia,
                       listaFornecedores->listaFornecedores[encontraFornecedor].cnpj,
                       lista->listaNotas[i].frete,
                       lista->listaNotas[i].imposto);
                for (int j = 0; j < lista->listaNotas[i].tamListaPecas; j++) {
                    printf("\n%s\n"
                        "PREÇO CUSTO: $%.2f\n"
                        "QUANTIDADE: %d\n"
                        "TOTAL DA PEÇA: $%.2f\n\n",
                        listaPecas->listaPecas[encontraPecas[j]].descricao,
                        listaPecas->listaPecas[encontraPecas[j]].precoCusto,
                        lista->listaNotas[i].qtdPecas[j],
                        lista->listaNotas[i].qtdPecas[j] * listaPecas->listaPecas[encontraPecas[j]].precoCusto);
                }
                printf("PREÇO TOTAL: $%2.f\n\n", lista->listaNotas[i].precoVendaTotal);
                free(encontraPecas);
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


