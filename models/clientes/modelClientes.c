#include "modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void armazenarDadosClienteModel(struct ListaClientes *lista, int opcaoArmazenamento) {
    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosClientes;

    switch (opcaoArmazenamento) {
        case 1:
            dadosClientes = fopen("DadosClientes.txt", "w");

            if (dadosClientes == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdClientes; i++) {
                fprintf(dadosClientes, "%d;%s;%s;%s;%s;%s;%s;%d;%d\n",
                        lista->listaClientes[i].id,
                        lista->listaClientes[i].nome,
                        lista->listaClientes[i].ddd,
                        lista->listaClientes[i].telefone,
                        lista->listaClientes[i].cpf_cnpj,
                        lista->listaClientes[i].email,
                        lista->listaClientes[i].endereco,
                        lista->listaClientes[i].idOficina,
                        lista->listaClientes[i].deletado);
            }
            break;
        case 2:
            dadosClientes = fopen("DadosClientes.bin", "wb");

            if (dadosClientes == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdClientes; i++) {
                fwrite(&lista->listaClientes[i], sizeof(struct Clientes), 1, dadosClientes);
            }
            break;
    }
    fclose(dadosClientes);

    free(lista->listaClientes);
    lista->listaClientes = NULL;

    lista->qtdClientes = 0;
}

void buscarDadosClientesModel(struct ListaClientes *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosClientes;

    switch (opcaoArmazenamento) {
        case 1:
            dadosClientes = fopen("DadosClientes.txt", "r");

            if (dadosClientes == NULL) {
                return;
            }

            char linha[sizeof(struct Clientes)];

            while (fgets(linha, sizeof(linha), dadosClientes)) {
                lista->qtdClientes++;
            }

            if (lista->qtdClientes > 0) {
                lista->listaClientes = malloc(lista->qtdClientes * sizeof(struct Clientes));
            } else {
                return;
            }

            if (lista->listaClientes == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosClientes, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosClientes)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaClientes[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].nome, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].ddd, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].telefone, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].cpf_cnpj, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].email, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].endereco, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaClientes[i].idOficina = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaClientes[i].deletado = atoi(token);
                }

                i++;
            }
            break;
        case 2:
            dadosClientes = fopen("DadosClientes.bin", "rb");

            if (dadosClientes == NULL) {
                return;
            }

            struct Clientes linhaCliente;

            while (fread(&linhaCliente, sizeof(linhaCliente), 1, dadosClientes)) {
                lista->qtdClientes++;
            }

            if (lista->qtdClientes > 0) {
                lista->listaClientes = malloc(lista->qtdClientes * sizeof(struct Clientes));
            } else {
                return;
            }

            if (lista->listaClientes == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosClientes, 0, SEEK_SET);

            while (fread(&linhaCliente, sizeof(linhaCliente), 1, dadosClientes)) {
                lista->listaClientes[i] = linhaCliente;
                i++;
            }

            break;
    }
    fclose(dadosClientes);
}

int alocarClientesModel(struct ListaClientes *lista) {
    lista->qtdClientes = 1;
    lista->listaClientes = malloc(sizeof(struct Clientes));

    if (lista->listaClientes == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

int realocarClientesModel(struct ListaClientes *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return 0;
    }

    lista->qtdClientes += qtdAlocada;
    lista->listaClientes = realloc(lista->listaClientes, lista->qtdClientes * sizeof(struct Clientes));

    if (lista->listaClientes == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

void cadastrarClientesModel(struct ListaClientes *lista, struct Clientes *cliente) {

    int resultAlocacao = 0;

    if (lista->qtdClientes == 0) {
        lista->qtdClientes++;
        resultAlocacao = alocarClientesModel(lista);
    } else {
        resultAlocacao = realocarClientesModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar o Cliente.\n\n");
        return;
    }

    //Cadastrando cliente na memoria
    cliente->id = lista->qtdClientes;
    cliente->deletado = 0;

    lista->listaClientes[lista->qtdClientes - 1] = *cliente;

    printf("Cliente cadastrado com sucesso!\n\n");
}

void atualizarClientesModel(struct ListaClientes *lista, int id, struct Clientes *cliente) {
    for (int i = 0; i < lista->qtdClientes; i++) {
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].deletado == 0) {
            cliente->id = lista->listaClientes[i].id;
            cliente->deletado = lista->listaClientes[i].deletado;
            lista->listaClientes[i] = *cliente;
            break;
        }
    }
}

// Verifica se o ID que deseja atualizar existe
int verificarIDClienteModel(struct ListaClientes *lista, int id) {
    if (lista->qtdClientes > 0) {
        for (int i = 0; i < lista->qtdClientes; i++) {
            if (lista->listaClientes[i].id == id && lista->listaClientes[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhum cliente foi cadastrado!\n\n");
        return 0;
    }

    printf("Cliente não encontrado!\n\n");
    return 0;
}

void listarTodosClientesModel(struct ListaClientes *lista) {
    //variavel para verificação de listagem
    int listado = 0;

    if (lista->qtdClientes > 0) {
        for (int i = 0; i < lista->qtdClientes; i++) {
            //Verifica se o cliente esta deletado
            if (lista->listaClientes[i].deletado == 0) {
                listado = 1;
                printf("\n====================="
                       "\n| CLIENTE %d         |"
                       "\n====================="
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nTELEFONE: (%s) %s"
                       "\nEMAIL: %s"
                       "\nENDEREÇO: %s"
                       "\nID DA OFICINA: %d\n\n",
                       lista->listaClientes[i].id,
                       lista->listaClientes[i].nome,
                       lista->listaClientes[i].cpf_cnpj,
                       lista->listaClientes[i].ddd,
                       lista->listaClientes[i].telefone,
                       lista->listaClientes[i].email,
                       lista->listaClientes[i].endereco,
                       lista->listaClientes[i].idOficina);
            }
        }
    }

    // Se não houver, avisa que não há cadastros
    if (listado == 0) {
        printf("Nenhum cliente cadastrado\n\n");
    }
}

void listarClienteModel(struct ListaClientes *lista, int id) {
    int encontrado = 0;

    if (lista->qtdClientes == 0) {
        printf("Nenhum cliente foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdClientes; i++) {
        //Verifica se o cliente está ou não deletado, e encontrando o cliente no ARRAY
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].deletado == 0) {
            printf("\n====================="
                   "\n| CLIENTE %d         |"
                   "\n====================="
                   "\nNOME: %s"
                   "\nCPF: %s"
                   "\nTELEFONE: (%s) %s"
                   "\nEMAIL: %s"
                   "\nENDEREÇO: %s"
                   "\nID DA OFICINA: %d\n\n",
                   lista->listaClientes[i].id,
                   lista->listaClientes[i].nome,
                   lista->listaClientes[i].cpf_cnpj,
                   lista->listaClientes[i].ddd,
                   lista->listaClientes[i].telefone,
                   lista->listaClientes[i].email,
                   lista->listaClientes[i].endereco,
                   lista->listaClientes[i].idOficina);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado!\n\n");
    }
}

void buscarClientesPorOficinaModel(struct ListaClientes *lista, int idOficina) {
    int encontrado = 0;

    if (lista->qtdClientes > 0) {
        for (int i = 0; i < lista->qtdClientes; i++) {
            if (lista->listaClientes[i].idOficina == idOficina && lista->listaClientes[i].deletado == 0) {
                encontrado = 1;
                printf("\n====================="
                       "\n| CLIENTE %d         |"
                       "\n====================="
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nTELEFONE: (%s)%s"
                       "\nEMAIL: %s"
                       "\nENDEREÇO: %s"
                       "\nID DA OFICINA: %d\n\n",
                       lista->listaClientes[i].id,
                       lista->listaClientes[i].nome,
                       lista->listaClientes[i].cpf_cnpj,
                       lista->listaClientes[i].ddd,
                       lista->listaClientes[i].telefone,
                       lista->listaClientes[i].email,
                       lista->listaClientes[i].endereco,
                       lista->listaClientes[i].idOficina);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum cliente encontrado.\n\n");
        }
    } else {
        printf("Nenhum cliente foi cadastrado.\n\n");
    }
}


//Utilizei um modelo de deleção logica
void deletarClientesModel(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, int id) {
    int encontrado = 0;

    if (lista->qtdClientes == 0) {
        printf("Nenhum cliente foi cadastrado!\n\n");
        return;
    }



    if (listaVeiculos->qtdVeiculos > 0) {
        for (int i = 0; i < listaVeiculos->qtdVeiculos; i++) {
            if (listaVeiculos->listaVeiculos[i].idProprietario == id && listaVeiculos->listaVeiculos[i].deletado == 0) {
                printf(
                    "Não foi possível deletar o cliente, pois os seus dados estão sendo utilizados em um veículo que já está cadastrado.\n\n");
                return;
            }
        }
    }

    /*
     Caso o ID do cliente seja encontrado, ele tera armazenado uma variavel para sinaliza-lo como "Deletado"
     "isDeleted" = 1
     */
    for (int i = 0; i < lista->qtdClientes; i++) {
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].deletado == 0) {
            encontrado = 1;

            lista->listaClientes[i].deletado = 1;

            printf("Cliente deletado com sucesso!\n\n");

            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado!\n\n");
    }
}
