#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../oficina/modelOficina.h"
#include "../../clientes/modelClientes.h"

// Imprime o relatório na tela
void imprimirRelatorioCliente(struct ListaClientes *listaClientes, struct ListaOficinas *listaOficinas, char *nome,
                              int id) {
    int existeClientes = 0;

    // Verifica se há pelo menos um registro
    if (listaClientes->qtdClientes > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaClientes->qtdClientes; i++) {
            // Verifica se está não está deletado e aplica os filtros
            if (listaClientes->listaClientes[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaClientes->listaClientes[i].nome, nome) != NULL) ||
                 (id != 0 && listaClientes->listaClientes[i].id == id))) {
                existeClientes = 1;
                printf("\n====================="
                       "\n| CLIENTE %d         |"
                       "\n====================="
                       "\nNOME: %s"
                       "\nCPF/CNPJ: %s"
                       "\nTELEFONE: (%s) %s"
                       "\nEMAIL: %s"
                       "\nENDEREÇO: %s"
                       "\nOFICINA: %s\n\n",
                       listaClientes->listaClientes[i].id,
                       listaClientes->listaClientes[i].nome,
                       listaClientes->listaClientes[i].cpf_cnpj,
                       listaClientes->listaClientes[i].ddd,
                       listaClientes->listaClientes[i].telefone,
                       listaClientes->listaClientes[i].email,
                       listaClientes->listaClientes[i].endereco,
                       listaOficinas->listaOficinas[listaClientes->listaClientes[i].idOficina - 1].nome);
            }
        }
    }

    // Verifica se não há registros
    if (!existeClientes) {
        printf("Nenhum cliente foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioCliente(struct ListaClientes *listaClientes, struct ListaOficinas *listaOficinas, char *nome,
                               int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioCliente;

    // Abrindo o arquivo de texto para escrita
    relatorioCliente = fopen("RelatorioCliente.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioCliente == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Inserindo os dados no arquivo de relatório
    for (int i = 0; i < listaClientes->qtdClientes; i++) {
        if (listaClientes->listaClientes[i].deletado == 0 &&
            ((strlen(nome) > 0 && strstr(listaClientes->listaClientes[i].nome, nome) != NULL) ||
             (id != 0 && listaClientes->listaClientes[i].id == id))) {
            fprintf(relatorioCliente, "%d;%s;%s;%s;%s;%s;%s;%s\n",
                    listaClientes->listaClientes[i].id,
                    listaClientes->listaClientes[i].nome,
                    listaClientes->listaClientes[i].ddd,
                    listaClientes->listaClientes[i].telefone,
                    listaClientes->listaClientes[i].cpf_cnpj,
                    listaClientes->listaClientes[i].email,
                    listaClientes->listaClientes[i].endereco,
                    listaOficinas->listaOficinas[listaClientes->listaClientes[i].idOficina - 1].nome);
        }
    }

    printf("Relatório de clientes realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioCliente);
}
