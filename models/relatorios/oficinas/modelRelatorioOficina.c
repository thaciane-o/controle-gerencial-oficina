#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../oficina/modelOficina.h"

// Imprime o relatório na tela
void imprimirRelatorioOficina(struct ListaOficinas *listaOficinas, char *nome, int id) {
    int existeOficinas = 0;

    // Verifica se há pelo menos um registro
    if (listaOficinas->qtdOficinas > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaOficinas->qtdOficinas; i++) {
            // Verifica se está não está deletado e aplica os filtros
            if (listaOficinas->listaOficinas[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaOficinas->listaOficinas[i].nome, nome) != NULL) ||
                 (id != 0 && listaOficinas->listaOficinas[i].id == id))) {
                existeOficinas = 1;
                printf("\n====================\n"
                         "| OFICINA %d        |\n"
                         "====================\n"
                         "NOME: %s\n"
                         "ENDEREÇO: %s\n"
                         "TELEFONE: (%s) %s\n"
                         "EMAIL: %s\n"
                         "PORCENTAGEM DE LUCRO: %.2f\n",
                         listaOficinas->listaOficinas[i].id,
                         listaOficinas->listaOficinas[i].nome,
                         listaOficinas->listaOficinas[i].endereco,
                         listaOficinas->listaOficinas[i].ddd,
                         listaOficinas->listaOficinas[i].telefone,
                         listaOficinas->listaOficinas[i].email,
                         listaOficinas->listaOficinas[i].porcentagemLucro);
            }
        }
    }

    // Verifica se não há registros
    if (!existeOficinas) {
        printf("Nenhuma oficina foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioOficina(struct ListaOficinas *listaOficinas, char *nome, int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioOficina;

    // Abrindo o arquivo de texto para escrita
    relatorioOficina = fopen("RelatorioOficina.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioOficina == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Inserindo os dados no arquivo de relatório
    for (int i = 0; i < listaOficinas->qtdOficinas; i++) {
        if (listaOficinas->listaOficinas[i].deletado == 0 &&
            ((strlen(nome) > 0 && strstr(listaOficinas->listaOficinas[i].nome, nome) != NULL) ||
             (id != 0 && listaOficinas->listaOficinas[i].id == id))) {
            fprintf(relatorioOficina, "%d;%s;%s;%s;%s;%s;%.2f\n",
                listaOficinas->listaOficinas[i].id,
                listaOficinas->listaOficinas[i].nome,
                listaOficinas->listaOficinas[i].endereco,
                listaOficinas->listaOficinas[i].ddd,
                listaOficinas->listaOficinas[i].telefone,
                listaOficinas->listaOficinas[i].email,
                listaOficinas->listaOficinas[i].porcentagemLucro);
        }
    }

    printf("Relatório de oficinas realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioOficina);
}
