#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../fornecedores/modelFornecedores.h"

// Imprime o relatório na tela
void imprimirRelatorioFornecedor(struct ListaFornecedores *listaFornecedores, char *nome, int id) {
    int existeFornecedor = 0;

    // Verifica se há pelo menos um registro
    if (listaFornecedores->qtdFornecedores > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaFornecedores->qtdFornecedores; i++) {
            // Verifica se não está deletado e aplica os filtros
            if (listaFornecedores->listaFornecedores[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaFornecedores->listaFornecedores[i].nomeFantasia, nome) != NULL) ||
                 (id != 0 && listaFornecedores->listaFornecedores[i].id == id))) {
                existeFornecedor = 1;
                printf("\n====================="
                       "\n| FORNECEDOR %d      |"
                       "\n====================="
                       "\nNOME FANTASIA: %s"
                       "\nRAZÃO SOCIAL: %s"
                       "\nINSCRIÇÃO ESTADUAL: %s"
                       "\nCNPJ: %s"
                       "\nENDEREÇO COMPLETO: %s"
                       "\nTELEFONE: (%s) %s"
                       "\nEMAIL: %s\n",
                       listaFornecedores->listaFornecedores[i].id,
                       listaFornecedores->listaFornecedores[i].nomeFantasia,
                       listaFornecedores->listaFornecedores[i].razaoSocial,
                       listaFornecedores->listaFornecedores[i].inscricaoEstadual,
                       listaFornecedores->listaFornecedores[i].cnpj,
                       listaFornecedores->listaFornecedores[i].endereco,
                       listaFornecedores->listaFornecedores[i].ddd,
                       listaFornecedores->listaFornecedores[i].telefone,
                       listaFornecedores->listaFornecedores[i].email);
            }
        }
    }

    // Verifica se não há registros
    if (!existeFornecedor) {
        printf("Nenhum fornecedor foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioFornecedor(struct ListaFornecedores *listaFornecedores, char *nome, int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioFornecedor;

    // Abrindo o arquivo de texto para escrita
    relatorioFornecedor = fopen("RelatorioFornecedor.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioFornecedor == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Verifica se há pelo menos um registro
    if (listaFornecedores->qtdFornecedores > 0) {
        // Inserindo os dados no arquivo de relatório
        for (int i = 0; i < listaFornecedores->qtdFornecedores; i++) {
            if (listaFornecedores->listaFornecedores[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaFornecedores->listaFornecedores[i].nomeFantasia, nome) != NULL) ||
                 (id != 0 && listaFornecedores->listaFornecedores[i].id == id))) {
                fprintf(relatorioFornecedor, "%d;%s;%s;%s;%s;%s;%s;%s;%s\n",
                        listaFornecedores->listaFornecedores[i].id,
                        listaFornecedores->listaFornecedores[i].nomeFantasia,
                        listaFornecedores->listaFornecedores[i].razaoSocial,
                        listaFornecedores->listaFornecedores[i].inscricaoEstadual,
                        listaFornecedores->listaFornecedores[i].cnpj,
                        listaFornecedores->listaFornecedores[i].endereco,
                        listaFornecedores->listaFornecedores[i].ddd,
                        listaFornecedores->listaFornecedores[i].telefone,
                        listaFornecedores->listaFornecedores[i].email);
            }
        }
        printf("Relatório de fornecedores realizado com sucesso!\n\n");
    } else {
        printf("Nenhum fornecedor foi cadastrado.\n\n");
    }

    // Fechando o arquivo
    fclose(relatorioFornecedor);
}
