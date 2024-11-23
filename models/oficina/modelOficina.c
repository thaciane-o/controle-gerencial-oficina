#include "modelOficina.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das oficinas no arquivo
void buscarDadosOficinaModel(struct ListaOficinas *lista, int opcaoArmazenamento) {
    int i = 0;
    char linha[sizeof(struct Oficinas)];

    FILE *dadosOficinas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosOficinas = fopen("DadosOficinas.txt", "r");

            if (dadosOficinas == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosOficinas)) {
                lista->qtdOficinas++;
            }

            if (lista->qtdOficinas > 0) {
                lista->listaOficinas = malloc(lista->qtdOficinas * sizeof(struct Oficinas));
            } else {
                return;
            }

            if (lista->listaOficinas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosOficinas, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosOficinas)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaOficinas[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaOficinas[i].nome, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaOficinas[i].endereco, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaOficinas[i].ddd, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaOficinas[i].telefone, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    strcpy(lista->listaOficinas[i].email, token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOficinas[i].porcentagemLucro = atof(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaOficinas[i].deletado = atoi(token);
                }

                i++;
            }
            break;

        case 2:
            dadosOficinas = fopen("DadosOficinas.bin", "rb");

            if (dadosOficinas == NULL) {
                return;
            }

            struct Oficinas linhaOficina;

            while (fread(&linhaOficina, sizeof(linhaOficina), 1, dadosOficinas)) {
                lista->qtdOficinas++;
            }

            if (lista->qtdOficinas > 0) {
                lista->listaOficinas = malloc(lista->qtdOficinas * sizeof(struct Oficinas));
            } else {
                return;
            }

            if (lista->listaOficinas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                return;
            }

            fseek(dadosOficinas, 0, SEEK_SET);

            while (fread(&linhaOficina, sizeof(linhaOficina), 1, dadosOficinas)) {
                lista->listaOficinas[i] = linhaOficina;
                i++;
            }
            break;
    }

    fclose(dadosOficinas);
}

// Armazena os dados das oficinas no arquivo
void armazenarDadosOficinaModel(struct ListaOficinas *lista, int opcaoArmazenamento) {
    FILE *dadosOficinas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosOficinas = fopen("DadosOficinas.txt", "w");

            if (dadosOficinas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdOficinas; i++) {
                fprintf(dadosOficinas, "%d;%s;%s;%s;%s;%s;%f;%d\n",
                        lista->listaOficinas[i].id,
                        lista->listaOficinas[i].nome,
                        lista->listaOficinas[i].endereco,
                        lista->listaOficinas[i].ddd,
                        lista->listaOficinas[i].telefone,
                        lista->listaOficinas[i].email,
                        lista->listaOficinas[i].porcentagemLucro,
                        lista->listaOficinas[i].deletado);
            }
            break;

        case 2:
            dadosOficinas = fopen("DadosOficinas.bin", "wb");

            if (dadosOficinas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdOficinas; i++) {
                fwrite(&lista->listaOficinas[i], sizeof(struct Oficinas), 1, dadosOficinas);
            }
            break;
    }

    fclose(dadosOficinas);

    free(lista->listaOficinas);
    lista->listaOficinas = NULL;

    lista->qtdOficinas = 0;
}

// Aloca a memória inicial para a lista de oficinas
int alocarMemoriaOficinaModel(struct ListaOficinas *lista) {
    lista->qtdOficinas = 1;
    lista->listaOficinas = malloc(sizeof(struct Oficinas));

    if (lista->listaOficinas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória da oficina de acordo com a quantidade que deseja alocar (qtdAloca)
int realocarMemoriaOficinaModel(struct ListaOficinas *lista, int qtdAloca) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada\n\n");
        return 0;
    }

    lista->qtdOficinas += qtdAloca;
    lista->listaOficinas = realloc(lista->listaOficinas, lista->qtdOficinas * sizeof(struct Oficinas));

    if (lista->listaOficinas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova oficina
void cadastrarOficinaModel(struct ListaOficinas *lista, struct Oficinas *oficinaCadastrando) {
    int resultAlocacao = 0;

    if (lista->qtdOficinas == 0) {
        lista->qtdOficinas++;
        resultAlocacao = alocarMemoriaOficinaModel(lista);
    } else {
        // Se já tiver, aumenta a alocação em 1
        resultAlocacao = realocarMemoriaOficinaModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar a oficina.\n\n");
        return;
    }

    oficinaCadastrando->id = lista->qtdOficinas;
    oficinaCadastrando->deletado = 0;

    lista->listaOficinas[lista->qtdOficinas - 1] = *oficinaCadastrando;

    printf("Oficina cadastrada com sucesso!\n\n");
}

// Deleta uma oficina cadastrada
void deletarOficinaModel(struct ListaOficinas *lista, struct ListaFuncionarios *listaFuncionarios, struct ListaServicos *listaServicos,
                         struct ListaClientes *listaClientes, int id) {
    // Auxiliar para saber se encontrou o id.
    int encontrado = 0;

    // Verifica se há alguma oficina cadastrada.
    if (lista->qtdOficinas == 0) {
        printf("Nenhuma oficina foi cadastrada.\n");
        return;
    }

    if (listaFuncionarios->qtdFuncionarios > 0) {
        for (int i = 0; i < listaFuncionarios->qtdFuncionarios; i++) {
            if (listaFuncionarios->listaFuncionarios[i].idOficina == id && listaFuncionarios->listaFuncionarios[i].
                deletado == 0) {
                printf(
                    "Não foi possível deletar a oficina, pois os seus dados estão sendo utilizados em um funcionário que já está cadastrado.\n\n");
                return;
            }
        }
    }

    if (listaClientes->qtdClientes > 0) {
        for (int i = 0; i < listaClientes->qtdClientes; i++) {
            if (listaClientes->listaClientes[i].idOficina == id && listaClientes->listaClientes[i].deletado == 0) {
                printf(
                    "Não foi possível deletar a oficina, pois os seus dados estão sendo utilizados em um cliente que já está cadastrado.\n\n");
                return;
            }
        }
    }

    if (listaServicos->qtdServicos > 0) {
        for (int i = 0; i < listaServicos->qtdServicos; i++) {
            if (listaServicos->listaServicos[i].idOficina == id && listaServicos->listaServicos->deletado == 0) {
                printf("Não foi possível deletar a oficina, pois os seus dados estão sendo utilizados em um serviço que já está cadastrado.\n\n");
                return;
            }
        }
    }

    // Busca pelo id para fazer a deleção.
    for (int i = 0; i < lista->qtdOficinas; i++) {
        if (lista->listaOficinas[i].id == id && lista->listaOficinas[i].deletado == 0) {
            encontrado = 1;
            lista->listaOficinas[i].deletado = 1;
            printf("Oficina deletada com sucesso!\n\n");
            break;
        }
    }

    // Se não encontrar o id para deleção, avisa o usuário.
    if (!encontrado) {
        printf("Oficina não encontrada.\n\n");
    }
}

// Atualiza uma oficina cadastrada
void atualizarOficinaModel(struct ListaOficinas *lista, int id, struct Oficinas *oficinaAlterando) {
    // Busca pelo id para fazer a alteração.
    for (int i = 0; i < lista->qtdOficinas; i++) {
        if (lista->listaOficinas[i].id == id && lista->listaOficinas[i].deletado == 0) {
            lista->listaOficinas[i] = *oficinaAlterando;
            lista->listaOficinas[i].id = id;
            lista->listaOficinas[i].deletado = 0;
            break;
        }
    }
}

// Verifica se o ID que deseja atualizar existe
int verificarIDOficinaModel(struct ListaOficinas *lista, int id) {
    // Procura a oficina com o id inserido
    if (lista->qtdOficinas > 0) {
        for (int i = 0; i < lista->qtdOficinas; i++) {
            if (lista->listaOficinas[i].id == id && lista->listaOficinas[i].deletado == 0) {
                return 1;
            }
        }
    } else {
        printf("Nenhuma oficina foi cadastrada!\n\n");
        return 0;
    }

    printf("Oficina não encontrada!\n\n");
    return 0;
}

// Lista todas as oficinas cadastradas
void listarTodosOficinaModel(struct ListaOficinas *lista) {
    // Verifica se há pelo menos um cadastro
    if (lista->qtdOficinas > 0) {
        // Se há um ou mais cadastros, exibe todos
        for (int i = 0; i < lista->qtdOficinas; i++) {
            // Verifica se o índice atual existe
            if (lista->listaOficinas[i].deletado == 0) {
                printf("\n====================\n"
                       "| OFICINA %d         |\n"
                       "===================\n"
                       "NOME: %s\n"
                       "ENDEREÇO: %s\n"
                       "TELEFONE: (%s) %s\n"
                       "Email: %s\n"
                       "Porcentagem de Lucro: %.2f\n",
                       lista->listaOficinas[i].id,
                       lista->listaOficinas[i].nome,
                       lista->listaOficinas[i].endereco,
                       lista->listaOficinas[i].ddd,
                       lista->listaOficinas[i].telefone,
                       lista->listaOficinas[i].email,
                       lista->listaOficinas[i].porcentagemLucro);
            }
        }
        printf("====================\n");
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhuma oficina foi cadastrada\n\n");
    }
}

// Busca uma oficina cadastrada pelo seu id
void buscarIdOficinaModel(struct ListaOficinas *lista, int id) {
    // Verifica se há pelo menos um cadastro
    if (lista->qtdOficinas > 0) {
        // Se há um ou mais cadastros, procura pela oficina com o id desejado
        int encontrado = -1;
        for (int i = 0; i < lista->qtdOficinas; i++) {
            if (lista->listaOficinas[i].id == id && lista->listaOficinas[i].deletado == 0) {
                encontrado = i;
                break;
            }
        }

        if (encontrado != -1) {
            printf("\n====================\n"
                   "| OFICINA %d         |\n"
                   "===================\n"
                   "NOME: %s\n"
                   "ENDEREÇO: %s\n"
                   "TELEFONE: (%s) %s\n"
                   "Email: %s\n"
                   "Porcentagem de Lucro: %.2f",
                   lista->listaOficinas[encontrado].id,
                   lista->listaOficinas[encontrado].nome,
                   lista->listaOficinas[encontrado].endereco,
                   lista->listaOficinas[encontrado].ddd,
                   lista->listaOficinas[encontrado].telefone,
                   lista->listaOficinas[encontrado].email,
                   lista->listaOficinas[encontrado].porcentagemLucro);
        } else {
            printf("Nenhuma oficina encontrada.\n\n");
        }
    } else {
        // Se não houver, avisa que não há cadastros
        printf("Nenhuma oficina foi cadastrada\n\n");
    }
}
