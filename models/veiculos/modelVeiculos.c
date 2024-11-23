#include "modelVeiculos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void armazenarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosVeiculos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosVeiculos = fopen("DadosVeiculos.txt", "w");

            if (dadosVeiculos == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdVeiculos; i++) {
                //Adicionando ";" ao armazenar os dados e um "\n" no final, teremos maior controle sobre o acesso aos dados posteriormente
                fprintf(dadosVeiculos, "%d;%d;%s;%s;%s;%s;%d;%d\n",
                        lista->listaVeiculos[i].id,
                        lista->listaVeiculos[i].idProprietario,
                        lista->listaVeiculos[i].modelo,
                        lista->listaVeiculos[i].marca,
                        lista->listaVeiculos[i].placa,
                        lista->listaVeiculos[i].chassi,
                        lista->listaVeiculos[i].anoFabricacao,
                        lista->listaVeiculos[i].deletado);
            }
            break;
        case 2:
            dadosVeiculos = fopen("DadosVeiculos.bin", "wb");

            if (dadosVeiculos == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdVeiculos; i++) {
                fwrite(&lista->listaVeiculos[i], sizeof(struct Veiculos), 1, dadosVeiculos);
            }
            break;
    }
    fclose(dadosVeiculos);

    free(lista->listaVeiculos);
    lista->listaVeiculos = NULL;

    lista->qtdVeiculos = 0;
}

void buscarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosVeiculos;

    switch (opcaoArmazenamento) {
        case 1:
            dadosVeiculos = fopen("DadosVeiculos.txt", "r");

            if (dadosVeiculos == NULL) {
                return;
            }

            char linha[sizeof(struct Veiculos)];

            while (fgets(linha, sizeof(linha), dadosVeiculos)) {
                lista->qtdVeiculos++;
            }


            if (lista->qtdVeiculos > 0) {
                lista->listaVeiculos = malloc(lista->qtdVeiculos * sizeof(struct Veiculos));
            } else {
                return;
            }

            if (lista->listaVeiculos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosVeiculos, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosVeiculos)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaVeiculos[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaVeiculos[i].idProprietario = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaVeiculos[i].modelo, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaVeiculos[i].marca, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaVeiculos[i].placa, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaVeiculos[i].chassi, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaVeiculos[i].anoFabricacao = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaVeiculos[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosVeiculos = fopen("DadosVeiculos.bin", "rb");

            if (dadosVeiculos == NULL) {
                return;
            }

            struct Veiculos linhaVeiculo;

            while (fread(&linhaVeiculo, sizeof(linhaVeiculo), 1, dadosVeiculos)) {
                lista->qtdVeiculos++;
            }

            if (lista->qtdVeiculos > 0) {
                lista->listaVeiculos = malloc(lista->qtdVeiculos * sizeof(struct Veiculos));
            } else {
                return;
            }

            if (lista->listaVeiculos == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosVeiculos, 0, SEEK_SET);

            while (fread(&linhaVeiculo, sizeof(linhaVeiculo), 1, dadosVeiculos)) {
                lista->listaVeiculos[i] = linhaVeiculo;
                i++;
            }


            break;
    }
    fclose(dadosVeiculos);
}

int alocarVeiculosModel(struct ListaVeiculos *lista) {
    lista->qtdVeiculos = 1;
    lista->listaVeiculos = malloc(sizeof(struct Veiculos));

    if (lista->listaVeiculos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

int realocarVeiculosModel(struct ListaVeiculos *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdVeiculos += qtdAlocada;
    lista->listaVeiculos = realloc(lista->listaVeiculos, lista->qtdVeiculos * sizeof(struct Veiculos));

    if (lista->listaVeiculos == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

void cadastrarVeiculosModel(struct ListaVeiculos *lista, struct Veiculos *cliente) {
    int resultAlocacao = 0;

    if (lista->qtdVeiculos == 0) {
        lista->qtdVeiculos++;
        resultAlocacao = alocarVeiculosModel(lista);
    } else {
        resultAlocacao = realocarVeiculosModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o veículo.\n\n");
        return;
    }

    //Cadastrando veiculo na memoria
    cliente->id = lista->qtdVeiculos;
    cliente->deletado = 0;

    lista->listaVeiculos[lista->qtdVeiculos - 1] = *cliente;

    printf("Veículo cadastrado com sucesso!\n\n");
}

void atualizarVeiculosModel(struct ListaVeiculos *lista, int id, struct Veiculos *veiculo) {
    for (int i = 0; i < lista->qtdVeiculos; i++) {
        if (lista->listaVeiculos[i].id == id && lista->listaVeiculos[i].deletado == 0) {
            veiculo->id = lista->listaVeiculos[i].id;
            veiculo->deletado = lista->listaVeiculos[i].deletado;
            lista->listaVeiculos[i] = *veiculo;
            break;
        }
    }
}

// Verifica se o ID que deseja atualizar existe
int verificarIDVeiculoModel(struct ListaVeiculos *lista, int id) {
    if (lista->qtdVeiculos > 0) {
        for (int i = 0; i < lista->qtdVeiculos; i++) {
            if (lista->listaVeiculos[i].id == id && lista->listaVeiculos[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhum veículo foi cadastrado!\n\n");
        return 0;
    }

    printf("Veículo não encontrado!\n\n");
    return 0;
}

void listarTodosVeiculosModel(struct ListaVeiculos *lista) {
    //variavel para verificar se algum veiculo foi listado
    int listado = 0;

    if (lista->qtdVeiculos > 0) {
        for (int i = 0; i < lista->qtdVeiculos; i++) {
            //Verifica se o cliente esta deletado
            if (lista->listaVeiculos[i].deletado == 0) {
                listado = 1;
                printf("\n===================\n"
                       "| VEÍCULO %d       |\n"
                       "==================="
                       "\nPROPRIETÁRIO: %d"
                       "\nMODELO: %s"
                       "\nMARCA: %s"
                       "\nANO DE FABRICAÇÃO: %d"
                       "\nPLACA: %s"
                       "\nCHASSI: %s\n\n",
                       lista->listaVeiculos[i].id, lista->listaVeiculos[i].idProprietario,
                       lista->listaVeiculos[i].modelo, lista->listaVeiculos[i].marca,
                       lista->listaVeiculos[i].anoFabricacao, lista->listaVeiculos[i].placa,
                       lista->listaVeiculos[i].chassi);
            }
        }
    }

    /*
     Caso nenhum veiculo seja listado, será considerado que nenhum veiculo foi cadastrado
     mesmo se a quantidade for maior que 0
    */
    if (listado == 0) {
        printf("Nenhum veículo cadastrado.\n\n");
    }
}

void buscarIdClienteModel(struct ListaVeiculos *lista, int id) {
    int encontrado = 0;

    if (lista->qtdVeiculos == 0) {
        printf("Nenhum veículo foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdVeiculos; i++) {
        //Verifica se o cliente está ou não deletado, e encontrando o cliente no ARRAY
        if (lista->listaVeiculos[i].id == id && lista->listaVeiculos[i].deletado == 0) {
            printf("\n===================\n"
                   "| VEÍCULO %d       |\n"
                   "==================="
                   "\nPROPRIETÁRIO: %d"
                   "\nMODELO: %s"
                   "\nMARCA: %s"
                   "\nANO DE FABRICAÇÃO: %d"
                   "\nPLACA: %s"
                   "\nCHASSI: %s\n\n",
                   lista->listaVeiculos[i].id, lista->listaVeiculos[i].idProprietario,
                   lista->listaVeiculos[i].modelo, lista->listaVeiculos[i].marca,
                   lista->listaVeiculos[i].anoFabricacao, lista->listaVeiculos[i].placa,
                   lista->listaVeiculos[i].chassi);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Veículo não encontrado!\n\n");
    }
}

void listarVeiculosPorClienteModel(struct ListaVeiculos *lista, int id) {
    int encontrado = 0;

    if (lista->qtdVeiculos == 0) {
        printf("Nenhum veículo foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdVeiculos; i++) {
        //Verifica se o cliente está ou não deletado, e encontrando o cliente no ARRAY
        if (lista->listaVeiculos[i].idProprietario == id && lista->listaVeiculos[i].deletado == 0) {
            printf("\n===================\n"
                   "| VEÍCULO %d       |\n"
                   "==================="
                   "\nPROPRIETÁRIO: %d"
                   "\nMODELO: %s"
                   "\nMARCA: %s"
                   "\nANO DE FABRICAÇÃO: %d"
                   "\nPLACA: %s"
                   "\nCHASSI: %s\n\n",
                   lista->listaVeiculos[i].id, lista->listaVeiculos[i].idProprietario,
                   lista->listaVeiculos[i].modelo, lista->listaVeiculos[i].marca,
                   lista->listaVeiculos[i].anoFabricacao, lista->listaVeiculos[i].placa,
                   lista->listaVeiculos[i].chassi);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Proprietário não encontrado!\n\n");
    }
}


//Utilizei um modelo de deleção logica
void deletarVeiculosModel(struct ListaVeiculos *lista, int id) {
    int encontrado = 0;

    if (lista->qtdVeiculos == 0) {
        printf("Nenhum veículo foi cadastrado!\n\n");
        return;
    }

    /*
     Caso o ID do Veiculo seja encontrado, ele tera armazenado uma variavel para sinaliza-lo como "Deletado"
     "isDeleted" = 1
     */
    for (int i = 0; i < lista->qtdVeiculos; i++) {
        if (lista->listaVeiculos[i].id == id) {
            encontrado = 1;

            lista->listaVeiculos[i].deletado = 1;

            printf("Veículo deletado com sucesso!\n\n");

            break;
        }
    }

    if (!encontrado) {
        printf("Veículo não encontrado!\n\n");
    }
}
