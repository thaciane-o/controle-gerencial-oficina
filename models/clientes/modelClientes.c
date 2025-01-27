#include "modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca os dados de clientes nos arquivos
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
                fclose(dadosClientes);
                return;
            }

            if (lista->listaClientes == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosClientes);
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
                fclose(dadosClientes);
                return;
            }

            if (lista->listaClientes == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosClientes);
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

// Armazena os dados de clientes nos arquivos
void armazenarDadosClienteModel(struct ListaClientes *lista, int opcaoArmazenamento) {
    // Abrindo ou criando arquivo para adicionar cadastros
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

// Aloca memória inicial na lista de clientes
int alocarClientesModel(struct ListaClientes *lista) {
    lista->qtdClientes = 1;
    lista->listaClientes = malloc(sizeof(struct Clientes));

    if (lista->listaClientes == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória na lista de clientes conforme a necessidade em qtdAlocada
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

// Cadastra um novo cliente
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

    //Cadastrando cliente na memória
    cliente->id = lista->qtdClientes;
    cliente->deletado = 0;

    lista->listaClientes[lista->qtdClientes - 1] = *cliente;

    printf("Cliente cadastrado com sucesso!\n\n");
}

// Verifica a existência do id requisitado
int verificarIDClienteModel(struct ListaClientes *lista, int id) {
    // Procura o cliente com o id inserido
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

// Atualiza o cadastro de um cliente
void atualizarClientesModel(struct ListaClientes *lista, int id, struct Clientes *cliente) {
    // Busca pelo id para fazer a alteração
    for (int i = 0; i < lista->qtdClientes; i++) {
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].deletado == 0) {
            cliente->id = lista->listaClientes[i].id;
            cliente->deletado = lista->listaClientes[i].deletado;
            lista->listaClientes[i] = *cliente;
            break;
        }
    }
}

// Lista todos os clientes
void listarTodosClientesModel(struct ListaClientes *lista) {
    // Variável para verificação de listagem
    int listado = 0;

    // Verifica se há pelo menos um cadastro
    if (lista->qtdClientes > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdClientes; i++) {
            //Verifica se o cliente esta deletado
            if (lista->listaClientes[i].deletado == 0) {
                listado = 1;
                printf("\n====================="
                       "\n| CLIENTE %d         |"
                       "\n====================="
                       "\nNOME: %s"
                       "\nCPF/CNPJ: %s"
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
        printf("Nenhum cliente cadastrado.\n\n");
    }
}

// Lista um cliente pelo Id
void listarClienteModel(struct ListaClientes *lista, int id) {
    // Variável para verificar que cliente foi encontrado
    int encontrado = 0;

    if (lista->qtdClientes == 0) {
        printf("Nenhum cliente foi cadastrado!\n\n");
        return;
    }
    // Se há um ou mais cadastros, procura pelo cliente com o id desejado
    for (int i = 0; i < lista->qtdClientes; i++) {
        // Verifica se o cliente está ou não deletado
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].deletado == 0) {
            printf("\n====================="
                   "\n| CLIENTE %d         |"
                   "\n====================="
                   "\nNOME: %s"
                   "\nCPF/CNPJ: %s"
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

// Lista os clientes relacionados a uma oficina, buscando pelo idOficina
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
                       "\nCPF/CNPJ: %s"
                       "\nTELEFONE: (%s)%s"
                       "\nEMAIL: %s"
                       "\nENDEREÇO: %s\n\n",
                       lista->listaClientes[i].id,
                       lista->listaClientes[i].nome,
                       lista->listaClientes[i].cpf_cnpj,
                       lista->listaClientes[i].ddd,
                       lista->listaClientes[i].telefone,
                       lista->listaClientes[i].email,
                       lista->listaClientes[i].endereco);
            }
        }

        if (encontrado == 0) {
            printf("Nenhum cliente encontrado.\n\n");
        }
    } else {
        printf("Nenhum cliente foi cadastrado.\n\n");
    }
}

// Deleta um cliente cadastrado
void deletarClientesModel(struct ListaClientes *lista, struct ListaVeiculos *listaVeiculos, int id) {
    int encontrado = 0;

    // Verifica se há algum cadastro
    if (lista->qtdClientes == 0) {
        printf("Nenhum cliente foi cadastrado!\n\n");
        return;
    }

    // Verifica relação com veículo
    if (listaVeiculos->qtdVeiculos > 0) {
        for (int i = 0; i < listaVeiculos->qtdVeiculos; i++) {
            if (listaVeiculos->listaVeiculos[i].idProprietario == id && listaVeiculos->listaVeiculos[i].deletado == 0) {
                printf(
                    "Não foi possível deletar o cliente, pois os seus dados estão sendo utilizados em um veículo que já está cadastrado.\n\n");
                return;
            }
        }
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdClientes; i++) {
        if (lista->listaClientes[i].id == id && lista->listaClientes[i].deletado == 0) {
            encontrado = 1;

            lista->listaClientes[i].deletado = 1;

            printf("Cliente deletado com sucesso!\n\n");

            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário
    if (!encontrado) {
        printf("Cliente não encontrado!\n\n");
    }
}

// Pega ID da oficina de um cliente desejado
int getIdOficinaClientesModel(struct ListaClientes *lista, int idCliente) {
    int encontrado = 0;

    if (lista->qtdClientes > 0) {
        for (int i = 0; i < lista->qtdClientes; i++) {
            if (lista->listaClientes[i].deletado == 0 && lista->listaClientes[i].id == idCliente) {
                return lista->listaClientes[i].idOficina;
            }
        }
        printf("Nenhum cliente encontrado.\n\n");
    } else {
        printf("Nenhum cliente foi cadastrado.\n\n");
    }

    return -1;
}

// Verifica se existe uma relação entre o cliente fornecido e alguma oficina
int verificarRelacaoClienteComOficinaModel(struct ListaClientes *listaClientes,
                                 int idOficina, int idCliente) {
    for (int i = 0; i < listaClientes->qtdClientes; i++) {
        if (idCliente == listaClientes->listaClientes[i].id && listaClientes->listaClientes[i].idOficina == idOficina) {
            return 1;
        }
    }
    printf("A oficina não presta serviços para este cliente!\n\n");
    return 0;
}