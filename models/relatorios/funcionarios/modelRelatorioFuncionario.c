#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../oficina/modelOficina.h"
#include "../../funcionarios/modelFuncionarios.h"

// Imprime o relatório na tela
void imprimirRelatorioFuncionario(struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                                  char *nome, int id) {
    int existeFuncionarios = 0;

    // Verifica se há pelo menos um registro
    if (listaFuncionarios->qtdFuncionarios > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaFuncionarios->qtdFuncionarios; i++) {
            // Verifica se não está deletado e aplica os filtros
            if (listaFuncionarios->listaFuncionarios[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaFuncionarios->listaFuncionarios[i].nome, nome) != NULL) ||
                 (id != 0 && listaFuncionarios->listaFuncionarios[i].id == id))) {
                existeFuncionarios = 1;
                printf("\n======================="
                       "\n| FUNCIONÁRIO %d       |"
                       "\n======================="
                       "\nNOME: %s"
                       "\nCPF: %s"
                       "\nCARGO: %s"
                       "\nSALÁRIO: %.2f"
                       "\nOFICINA: %s\n",
                       listaFuncionarios->listaFuncionarios[i].id,
                       listaFuncionarios->listaFuncionarios[i].nome,
                       listaFuncionarios->listaFuncionarios[i].cpf,
                       listaFuncionarios->listaFuncionarios[i].cargo,
                       listaFuncionarios->listaFuncionarios[i].salario,
                       listaOficinas->listaOficinas[listaFuncionarios->listaFuncionarios[i].idOficina - 1].nome);
            }
        }
    }

    // Verifica se não há registros
    if (!existeFuncionarios) {
        printf("Nenhum funcionário foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioFuncionario(struct ListaFuncionarios *listaFuncionarios, struct ListaOficinas *listaOficinas,
                                   char *nome, int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioFuncionario;

    // Abrindo o arquivo de texto para escrita
    relatorioFuncionario = fopen("RelatorioFuncionario.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioFuncionario == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }


    // Verifica se há pelo menos um registro
    if (listaFuncionarios->qtdFuncionarios > 0) {
        // Inserindo os dados no arquivo de relatório
        for (int i = 0; i < listaFuncionarios->qtdFuncionarios; i++) {
            if (listaFuncionarios->listaFuncionarios[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaFuncionarios->listaFuncionarios[i].nome, nome) != NULL) ||
                 (id != 0 && listaFuncionarios->listaFuncionarios[i].id == id))) {
                fprintf(relatorioFuncionario, "%d;%s;%s;%s;%.2f;%s\n",
                        listaFuncionarios->listaFuncionarios[i].id,
                        listaFuncionarios->listaFuncionarios[i].nome,
                        listaFuncionarios->listaFuncionarios[i].cpf,
                        listaFuncionarios->listaFuncionarios[i].cargo,
                        listaFuncionarios->listaFuncionarios[i].salario,
                        listaOficinas->listaOficinas[listaFuncionarios->listaFuncionarios[i].idOficina - 1].nome);
            }
        }
        printf("Relatório de funcionários realizado com sucesso!\n\n");
    } else {
        printf("Nenhum funcionário foi cadastrado.\n\n");
    }

    // Fechando o arquivo
    fclose(relatorioFuncionario);
}
