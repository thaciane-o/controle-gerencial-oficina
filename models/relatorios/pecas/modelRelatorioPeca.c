#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../oficina/modelOficina.h"
#include "../../fornecedores/modelFornecedores.h"
#include "../../pecas/modelPecas.h"

// Imprime o relatório na tela
void imprimirRelatorioPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                            struct ListaOficinas *listaOficinas, char *nome, int id) {
    int existePecas = 0;

    // Verifica se há pelo menos um registro
    if (listaPecas->qtdPecas > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaPecas->qtdPecas; i++) {
            // Verifica se não está deletado e aplica os filtros
            if (listaPecas->listaPecas[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaPecas->listaPecas[i].descricao, nome) != NULL) ||
                 (id != 0 && listaPecas->listaPecas[i].id == id))) {
                existePecas = 1;
                printf("\n====================\n"
                       "| PEÇA %d           |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "FABRICANTE: %s\n"
                       "PREÇO DE CUSTO: $%.2f\n"
                       "PREÇO DE VENDA: $%.2f\n"
                       "QUANTIDADE EM ESTOQUE: %d\n"
                       "ESTOQUE MÍNIMO: %d\n"
                       "OFICINA: %s\n"
                       "FORNECEDOR: %s\n",
                       listaPecas->listaPecas[i].id,
                       listaPecas->listaPecas[i].descricao,
                       listaPecas->listaPecas[i].fabricante,
                       listaPecas->listaPecas[i].precoCusto,
                       listaPecas->listaPecas[i].precoVenda,
                       listaPecas->listaPecas[i].qtdEstoque,
                       listaPecas->listaPecas[i].estoqueMinimo,
                       listaOficinas->listaOficinas[listaPecas->listaPecas[i].idOficina - 1].nome,
                       listaFornecedores->listaFornecedores[listaPecas->listaPecas[i].idFornecedor - 1].nomeFantasia);
            }
        }
    }

    // Verifica se não há registros
    if (!existePecas) {
        printf("Nenhuma peça foi cadastrada.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioPeca(struct ListaPecas *listaPecas, struct ListaFornecedores *listaFornecedores,
                            struct ListaOficinas *listaOficinas, char *nome, int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioPeca;

    // Abrindo o arquivo de texto para escrita
    relatorioPeca = fopen("RelatorioPeca.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioPeca == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Inserindo os dados no arquivo de relatório
    for (int i = 0; i < listaPecas->qtdPecas; i++) {
        if (listaPecas->listaPecas[i].deletado == 0 &&
            ((strlen(nome) > 0 && strstr(listaPecas->listaPecas[i].descricao, nome) != NULL) ||
             (id != 0 && listaPecas->listaPecas[i].id == id))) {
            fprintf(relatorioPeca, "%d;%s;%s;%.2f;%.2f;%d;%d;%s;%s\n",
                    listaPecas->listaPecas[i].id,
                    listaPecas->listaPecas[i].descricao,
                    listaPecas->listaPecas[i].fabricante,
                    listaPecas->listaPecas[i].precoCusto,
                    listaPecas->listaPecas[i].precoVenda,
                    listaPecas->listaPecas[i].qtdEstoque,
                    listaPecas->listaPecas[i].estoqueMinimo,
                    listaOficinas->listaOficinas[listaPecas->listaPecas[i].idOficina - 1].nome,
                    listaFornecedores->listaFornecedores[listaPecas->listaPecas[i].idFornecedor - 1].nomeFantasia);
        }
    }

    printf("Relatório de peças realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioPeca);
}
