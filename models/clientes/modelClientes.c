#include "modelClientes.h"
#include "../../views/clientes/viewClientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void armazenarDadosClienteModel(struct ListaClientes *lista) {

    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dadosClientes;
    int opcaoArquivo;

    printf("Qual arquivo deseja abrir?\n"
        "1: TEXTO\n"
        "2: BINARIO\n"
    );

    scanf("%d", &opcaoArquivo);
    switch (opcaoArquivo) {
        case 1:
            dadosClientes = fopen("DadosClientes.txt", "w");

            if (dadosClientes == NULL) {
                printf("Erro ao armazenar clientes (TXT)\n");
                exit(1);
            }


            for (int i = 0; i < lista->qtdClientes;i++) {

                //Adicionando ";" ao armazenar os dados e um "\n" no final, teremos maior controle sobre o acesso aos dados posteriormente
                fprintf(dadosClientes, "%d;%s;%s;%s;%s;%s;%s;%d\n", lista->listaClientes[i].id, lista->listaClientes[i].nome, lista->listaClientes[i].DDD,
                        lista->listaClientes[i].telefone, lista->listaClientes[i].CPF, lista->listaClientes[i].email,
                        lista->listaClientes[i].endereco, lista->listaClientes[i].Deletado);


                /***Após isso, os dados devem estar no seguinte formato dentro do arquivo***

                    isDeleted;id;nome;telefone;CPF_CNPJ;email;endereço\n
                 */
            }
            fclose(dadosClientes);
            break;
        case 2:
            dadosClientes = fopen("DadosClientes.bin", "wb");

            if (dadosClientes == NULL) {
                printf("Erro ao armazenar clientes (BIN)\n");
                exit(1);
            }


            for (int i = 0; i < lista->qtdClientes;i++) {

                fwrite(&lista->listaClientes[i], sizeof(struct Clientes), 1, dadosClientes);

            }
            fclose(dadosClientes);
            break;
        default:
            break;

    }
    free(lista->listaClientes);
}

void buscarDadosClientesModel(struct ListaClientes *lista) {

    int i = 0;

    FILE *dadosClientes;
    int opcaoArquivo;
    printf("Qual arquivo deseja abrir?\n"
        "1: TEXTO\n"
        "2: BINARIO\n"
    );
    scanf("%d", &opcaoArquivo);

    switch (opcaoArquivo) {
        case 1:
            dadosClientes = fopen("DadosClientes.txt", "r");

            if (dadosClientes == NULL) {
                printf("Nenhum cliente armazenado (TXT)\n");
                return;
            }

            char linha[sizeof(struct Clientes)];

            while (fgets(linha, sizeof(linha), dadosClientes)) {
                lista->qtdClientes++;
            }


            //Alocando memoria para receber o arquivo
            lista->listaClientes = malloc(lista->qtdClientes * sizeof(struct Clientes));

            if (lista->listaClientes == NULL) {
                printf("Erro ao alocar memoria\n");
                exit(1);
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
                    strcpy(lista->listaClientes[i].DDD, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].telefone, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaClientes[i].CPF, token);
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
                    lista->listaClientes[i].Deletado = atoi(token);
                }

                i++;
            }
            fclose(dadosClientes);
            break;
        case 2:
            dadosClientes = fopen("DadosClientes.bin", "rb");

            if (dadosClientes == NULL) {
                printf("Nenhum cliente armazenado (BIN)\n");
                return;
            }

            struct Clientes linhaCliente;

            while (fread(&linhaCliente, sizeof(linhaCliente), 1, dadosClientes)) {
                lista->qtdClientes++;
            }

            lista->listaClientes = malloc(lista->qtdClientes * sizeof(struct Clientes));
            if (lista->listaClientes == NULL) {
                printf("Erro ao alocar memoria\n");
                exit(1);
            }

            fseek(dadosClientes, 0, SEEK_SET);

            while (fread(&linhaCliente, sizeof(linhaCliente), 1, dadosClientes)) {
                lista->listaClientes[i] = linhaCliente;
                i++;
            }


            fclose(dadosClientes);
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }
}

void alocarClientesModel(struct ListaClientes *lista) {
    lista->listaClientes = malloc(sizeof(struct  Clientes));

    if (lista->listaClientes == NULL) {
        printf("Erro: Memória insuficiente!\n\n");
        exit(1);
    }
}

void realocarClientesModel(struct ListaClientes *lista, int qtdAlocada) {
    if (qtdAlocada == 0) {
        printf("Nenhum registro salvo.\n\n");
        return;
    }

    lista->qtdClientes += qtdAlocada;

    if (lista->qtdClientes == 0) {
        free(lista->listaClientes);
    } else {
        lista->listaClientes = realloc(lista->listaClientes, lista->qtdClientes * sizeof(struct Clientes));

        if (lista->listaClientes == NULL) {
            printf("Erro: Memória insuficiente!\n\n");
            exit(1);
        }
    }
}

void cadastrarClientesModel(struct ListaClientes *lista, struct Clientes *cliente) {

    if (lista->qtdClientes == 0) {
        lista->qtdClientes++;
        alocarClientesModel(lista);
    } else {
        realocarClientesModel(lista, 1);
    }

    //Cadastrando cliente na memoria
    lista->listaClientes[lista->qtdClientes-1] = *cliente;
    lista->listaClientes[lista->qtdClientes-1].Deletado = 0;

    //Gerando ID unico para o Cliente
    int temp = 0;
    for (int i = 0; i < lista->qtdClientes; i++) {
        if (lista->listaClientes[i].id > lista->listaClientes[i-1].id) {
            temp = lista->listaClientes[i].id;
        }
    }

    lista->listaClientes[lista->qtdClientes-1].id = temp+1;


    printf("Cliente cadastrada com sucesso!\n\n");
}

void atualizarClientesModel(struct ListaClientes *lista, int id, struct Clientes *cliente) {

    int encontrado = 0;
    if (lista->qtdClientes == 0) {
        printf("Nenhum cliente foi cadastrado!\n\n");
        return;
    }

    for (int i = 0; i < lista->qtdClientes; i++) {
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].Deletado == 0) {
            encontrado = 1;
            cliente->id = lista->listaClientes[i].id;
            cliente->Deletado = lista->listaClientes[i].Deletado;

            lista->listaClientes[i] = *cliente;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado!\n\n");
    }
}

void listarTodosClientesModel(struct ListaClientes *lista) {

    if (lista->qtdClientes > 0) {
        for (int i = 0; i < lista->qtdClientes; i++) {

            //Verifica se o cliente esta deletado
            if (lista->listaClientes[i].Deletado == 0) {
                printf("ID: %d"
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nTELEFONE: (%s)%s"
                       "\nEMAIL: %s"
                       "\nENDEREÇO: %s\n\n",
                       lista->listaClientes[i].id, lista->listaClientes[i].nome,
                       lista->listaClientes[i].CPF, lista->listaClientes[i].DDD,
                       lista->listaClientes[i].telefone, lista->listaClientes[i].email,
                       lista->listaClientes[i].endereco);
            }
        }
    } else {
        printf("Nenhum cliente foi cadastrado!\n\n");
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
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].Deletado == 0) {
            printf("ID: %d"
                   "\nNOME: %s"
                   "\nCPF: %s"
                   "\nTELEFONE: (%s)%s"
                   "\nEMAIL: %s"
                   "\nENDEREÇO: %s\n\n",
                   lista->listaClientes[i].id, lista->listaClientes[i].nome,
                   lista->listaClientes[i].CPF, lista->listaClientes[i].DDD,
                   lista->listaClientes[i].telefone, lista->listaClientes[i].email,
                   lista->listaClientes[i].endereco);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado!\n\n");
    }
}


//Utilizei um modelo de deleção logica
void deletarClientesModel(struct ListaClientes *lista, int id) {
    int encontrado = 0;

    if (lista->qtdClientes == 0) {
        printf("Nenhum cliente foi cadastrado!\n\n");
        return;
    }

    /*
     Caso o ID do cliente seja encontrado, ele tera armazenado uma variavel para sinaliza-lo como "Deletado"
     "isDeleted" = 1
     */
    for (int i = 0; i < lista->qtdClientes; i++) {
        if (lista->listaClientes[i].id == id) {
            encontrado = 1;

            lista->listaClientes[i].Deletado = 1;

            printf("Cliente deletado com sucesso!\n\n");

            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado!\n\n");
    }
}