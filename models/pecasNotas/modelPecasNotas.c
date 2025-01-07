#include "modelPecasNotas.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das relações no arquivo
void buscarDadosPecaNotaModel(struct ListaPecasNotas *lista, int opcaoArmazenamento) {
    int i = 0;

    FILE *dadosPecas;
    char linha[sizeof(struct PecasNotas)];

    switch (opcaoArmazenamento) {
        case 1:

            dadosPecas = fopen("DadosPecasNotas.txt", "r");

            if (dadosPecas == NULL) {
                return;
            }

            while (fgets(linha, sizeof(linha), dadosPecas)) {
                lista->qtdPecasNotas++;
            }

            if (lista->qtdPecasNotas > 0) {
                lista->listaPecasNotas = malloc(lista->qtdPecasNotas * sizeof(struct PecasNotas));
            } else {
                fclose(dadosPecas);
                return;
            }

            if (lista->listaPecasNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPecas);
                return;
            }

            fseek(dadosPecas, 0, SEEK_SET);

            while (fgets(linha, sizeof(linha), dadosPecas)) {
                char *token = strtok(linha, ";");

                if (token != NULL) {
                    lista->listaPecasNotas[i].id = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].idNota = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].idPeca = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].qtdPecas = atoi(token);
                    token = strtok(NULL, ";");
                }
                if (token != NULL) {
                    lista->listaPecasNotas[i].deletado = atoi(token);
                }

                i++;
            }
            break;

        case 2:
            dadosPecas = fopen("DadosPecasNotas.bin", "rb");

            if (dadosPecas == NULL) {
                return;
            }

            struct PecasNotas linhaPeca;

            while (fread(&linhaPeca, sizeof(linhaPeca), 1, dadosPecas)) {
                lista->qtdPecasNotas++;
            }

            if (lista->qtdPecasNotas > 0) {
                lista->listaPecasNotas = malloc(lista->qtdPecasNotas * sizeof(struct PecasNotas));
            } else {
                fclose(dadosPecas);
                return;
            }

            if (lista->listaPecasNotas == NULL) {
                printf("Erro: Memória insuficiente. Cancelando abertura de arquivo.\n\n");
                fclose(dadosPecas);
                return;
            }

            fseek(dadosPecas, 0, SEEK_SET);

            while (fread(&linhaPeca, sizeof(linhaPeca), 1, dadosPecas)) {
                lista->listaPecasNotas[i] = linhaPeca;
                i++;
            }
            break;
    }

    fclose(dadosPecas);
}

// Armazena os dados das relações no arquivo
void armazenarDadosPecaNotaModel(struct ListaPecasNotas *lista, int opcaoArmazenamento) {
    FILE *dadosPecas;

    switch (opcaoArmazenamento) {
        case 1:
            dadosPecas = fopen("DadosPecasNotas.txt", "w");

            if (dadosPecas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPecasNotas; i++) {
                fprintf(dadosPecas, "%d;%d;%d;%d;%d\n",
                        lista->listaPecasNotas[i].id,
                        lista->listaPecasNotas[i].idNota,
                        lista->listaPecasNotas[i].idPeca,
                        lista->listaPecasNotas[i].qtdPecas,
                        lista->listaPecasNotas[i].deletado);
            }
            break;

        case 2:
            dadosPecas = fopen("DadosPecasNotas.bin", "wb");

            if (dadosPecas == NULL) {
                printf("Erro: Não foi possível abrir o arquivo binário.\n\n");
                return;
            }

            for (int i = 0; i < lista->qtdPecasNotas; i++) {
                fwrite(&lista->listaPecasNotas[i], sizeof(struct PecasNotas), 1, dadosPecas);
            }
            break;
    }

    fclose(dadosPecas);

    free(lista->listaPecasNotas);
    lista->listaPecasNotas = NULL;

    lista->qtdPecasNotas = 0;
}

// Aloca a memória inicial para a lista de relações
int alocarMemoriaPecaNotaModel(struct ListaPecasNotas *lista) {
    lista->qtdPecasNotas = 1;
    lista->listaPecasNotas = malloc(sizeof(struct PecasNotas));

    if (lista->listaPecasNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Realoca memória da relação conforme a quantidade que deseja alocar (qtdAloca)
int realocarMemoriaPecaNotaModel(struct ListaPecasNotas *lista, int qtdAloca) {
    if (qtdAloca == 0) {
        printf("Nenhuma alocação foi realizada.\n\n");
        return 0;
    }

    lista->qtdPecasNotas += qtdAloca;
    lista->listaPecasNotas = realloc(lista->listaPecasNotas, lista->qtdPecasNotas * sizeof(struct PecasNotas));

    // Verifica se a alocação deu certo
    if (lista->listaPecasNotas == NULL) {
        printf("Erro: Memória insuficiente\n\n");
        return 0;
    }
    return 1;
}

// Cadastra uma nova relação peça/nota
void cadastrarPecaNotaModel(struct ListaPecasNotas *lista, struct PecasNotas *pecaNotaCadastrando) {
    int resultAlocacao = 0;

    if (lista->qtdPecasNotas == 0) {
        lista->qtdPecasNotas++;
        resultAlocacao = alocarMemoriaPecaNotaModel(lista);
    } else {
        // Se já tiver, aumenta a alocação em 1
        resultAlocacao = realocarMemoriaPecaNotaModel(lista, 1);
    }

    if (resultAlocacao == 0) {
        printf("Erro: Não foi possível cadastrar a relação Peca/Nota.\n\n");
        return;
    }

    pecaNotaCadastrando->id = lista->qtdPecasNotas;
    pecaNotaCadastrando->deletado = 0;
    lista->listaPecasNotas[lista->qtdPecasNotas - 1] = *pecaNotaCadastrando;


}

// Deleta uma relação peça/nota cadastrada
void deletarPecaNotaModel(struct ListaPecasNotas *lista, int id) {
    // Auxiliar para saber se encontrou o id.

    // Verifica se há algum cadastro
    if (lista->qtdPecasNotas == 0) {
        return;
    }

    // Busca pelo id para fazer a deleção
    for (int i = 0; i < lista->qtdPecasNotas; i++) {
        if (lista->listaPecasNotas[i].idNota == id && lista->listaPecasNotas[i].deletado == 0) {
            lista->listaPecasNotas[i].deletado = 1;
        }
    }
}

// Retira uma certa quantidade de peças de determinado estoque
void debitarPecaEstoqueModel(struct ListaPecas *listaPecas, int idPeca, int qtdPecasRequisitadas) {

    // Inicia busca pela peça requisitada
    for (int i = 0; i < listaPecas->qtdPecas; i++) {
        if (listaPecas->listaPecas[i].id == idPeca) {
            // Verifica se há peças suficientes no estoque
            if (listaPecas->listaPecas[i].qtdEstoque < qtdPecasRequisitadas) {

                printf("A quantidade de peças no estoque é insuficiente!\n");
            }else {

                listaPecas->listaPecas[i].qtdEstoque -= qtdPecasRequisitadas;
                printf("Peças debitadas do estoque com sucesso!\n");
            }
            break;
        }
    }

}

void cadastrarNovaPecaModel(struct ListaPecas *listaPecas, struct NotasFiscais *notaFiscal, struct PecasNotas *pecaNota) {
    struct Pecas novaPeca;

    novaPeca.idFornecedor = notaFiscal->idFornecedor;
    novaPeca.idOficina = notaFiscal->idOficina;

    printf("Insira a descrição da peça: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", novaPeca.descricao);

    printf("Insira o fabricante da peça: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]s", novaPeca.fabricante);

    printf("Insira o preço de custo da peça: R$");
    setbuf(stdin, NULL);
    scanf("%f", &novaPeca.precoCusto);

    novaPeca.precoVenda = 0;
    novaPeca.qtdEstoque = 0;

    printf("Insira a quantidade de peças mínimas no estoque: ");
    setbuf(stdin, NULL);
    scanf("%d", &novaPeca.estoqueMinimo);

    pecaNota->idPeca = listaPecas->qtdPecas + 1;

    cadastrarPecaModel(listaPecas, &novaPeca);
}

// Verifica peças com estoque abaixo do mínimo
void verificarEstoqueMinimo(struct ListaPecas *lista) {

    // Percorrendo lista de peças
    for (int i = 0; i < lista->qtdPecas; i++) {
        // Listando peças cujo o estoque está abaixo do mínimo
        if (lista->listaPecas[i].qtdEstoque < lista->listaPecas[i].estoqueMinimo) {
            printf("\nESTOQUE ABAIXO DO MÍNIMO NA PEÇA: %d\n"
                   "FORNECEDOR: %d\n", lista->listaPecas[i].id, lista->listaPecas[i].idFornecedor);
        }
    }
}

