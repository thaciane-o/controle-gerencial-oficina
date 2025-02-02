#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../oficina/modelOficina.h"
#include "../../servicos/modelServicos.h"

// Imprime o relatório na tela
void imprimirRelatorioServico(struct ListaServicos *listaServicos, struct ListaOficinas *listaOficinas, char *nome,
                              int id) {
    int existeServicos = 0;

    // Verifica se há pelo menos um registro
    if (listaServicos->qtdServicos > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaServicos->qtdServicos; i++) {
            // Verifica se não está deletado e aplica os filtros
            if (listaServicos->listaServicos[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaServicos->listaServicos[i].descricao, nome) != NULL) ||
                 (id != 0 && listaServicos->listaServicos[i].id == id))) {
                existeServicos = 1;
                printf("\n====================\n"
                       "| SERVIÇO %d        |\n"
                       "====================\n"
                       "DESCRIÇÃO: %s\n"
                       "PREÇO: $%.2f\n"
                       "COMISSÃO: $%.2f\n"
                       "OFICINA: %s\n",
                       listaServicos->listaServicos[i].id,
                       listaServicos->listaServicos[i].descricao,
                       listaServicos->listaServicos[i].preco,
                       listaServicos->listaServicos[i].comissao,
                       listaOficinas->listaOficinas[listaServicos->listaServicos[i].idOficina - 1].nome);
            }
        }
    }

    // Verifica se não há registros
    if (!existeServicos) {
        printf("Nenhum serviço foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioServico(struct ListaServicos *listaServicos, struct ListaOficinas *listaOficinas, char *nome,
                               int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioServico;

    // Abrindo o arquivo de texto para escrita
    relatorioServico = fopen("RelatorioServico.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioServico == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Inserindo os dados no arquivo de relatório
    for (int i = 0; i < listaServicos->qtdServicos; i++) {
        if (listaServicos->listaServicos[i].deletado == 0 &&
            ((strlen(nome) > 0 && strstr(listaServicos->listaServicos[i].descricao, nome) != NULL) ||
             (id != 0 && listaServicos->listaServicos[i].id == id))) {
            fprintf(relatorioServico, "%d;%s;%.2f;%.2f;%s\n",
                    listaServicos->listaServicos[i].id,
                    listaServicos->listaServicos[i].descricao,
                    listaServicos->listaServicos[i].preco,
                    listaServicos->listaServicos[i].comissao,
                    listaOficinas->listaOficinas[listaServicos->listaServicos[i].idOficina - 1].nome);
        }
    }

    printf("Relatório de serviços realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioServico);
}
