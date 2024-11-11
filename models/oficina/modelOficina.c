
#include "modelOficina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Busca dados das oficinas no arquivo
void buscarDadosOficinaModel(struct ListaOficinas *lista) {
     int i = 0;
     char linha[sizeof(struct Oficinas)];

     FILE *dadosOficinas;
     dadosOficinas = fopen("DadosOficinas.txt", "r");

     if (dadosOficinas == NULL) {
          printf("Erro ao abrir o arquivo!\n");
          return;
     }

     while (fgets(linha, sizeof(linha), dadosOficinas)) {
          lista->qtdOficinas++;
     }

     if (lista->qtdOficinas > 0) {
          lista->listaOficinas = malloc(lista->qtdOficinas * sizeof(struct Oficinas));
     }

     if (lista->listaOficinas == NULL) {
          printf("Erro ao alocar memória!\n");
          exit(1);
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
               lista->listaOficinas[i].deletado = atoi(token);
          }

          i++;
     }

     fclose(dadosOficinas);
}

// Armazena os dados das oficinas no arquivo
void armazenarDadosOficinaModel(struct ListaOficinas *lista) {
     FILE *dadosOficinas;
     dadosOficinas = fopen("DadosOficinas.txt", "w");

     if (dadosOficinas == NULL) {
          printf("Erro ao armazenar oficinas!\n");
          exit(1);
     }

     for (int i = 0; i < lista->qtdOficinas; i++) {
          fprintf(dadosOficinas, "%d;%s;%s;%s;%s;%s;%d\n",
              lista->listaOficinas[i].id,
              lista->listaOficinas[i].nome,
              lista->listaOficinas[i].endereco,
              lista->listaOficinas[i].ddd,
              lista->listaOficinas[i].telefone,
              lista->listaOficinas[i].email,
              lista->listaOficinas[i].deletado);
     }

     fclose(dadosOficinas);

     free(lista->listaOficinas);
     lista->listaOficinas = NULL;

     lista->qtdOficinas = 0;
}

// Aloca a memória inicial para a lista de oficinas
void alocarMemoriaOficinaModel(struct ListaOficinas *lista) {

     // Aloca a memória inicial para a lista de oficinas
     lista->qtdOficinas = 1;
     lista->listaOficinas = malloc(sizeof(struct Oficinas));

     // Verifica se a alocação deu certo
     if (lista->listaOficinas == NULL) {
          printf("Erro: Memória insuficiente\n");
          exit(EXIT_FAILURE);
     }
}

// Realoca memória da oficina de acordo com a quantidade que deseja alocar (qtdAloca)
void realocarMemoriaOficinaModel(struct ListaOficinas *lista, int qtdAloca) {

     // Verifica o tamando da alocação que pretende fazer
     if (qtdAloca == 0) { // Nenhuma alocação
          printf("Nenhuma alocação foi realizada\n");
          return;
     }

     lista->qtdOficinas += qtdAloca;
     lista->listaOficinas = realloc(lista->listaOficinas, lista->qtdOficinas * sizeof(struct Oficinas));

     // Verifica se a alocação deu certo
     if (lista->listaOficinas == NULL) {
          printf("Erro: Memória insuficiente\n");
          exit(EXIT_FAILURE);
     }
}

// Cadastra uma nova oficina
void cadastrarOficinaModel(struct ListaOficinas *lista, struct Oficinas *oficinaCadastrando) {

     // Se nenhuma oficina cadastrada, inicia a alocação
     if (lista->qtdOficinas == 0) {
          lista->qtdOficinas++;
          alocarMemoriaOficinaModel(lista);
     } else {
          // Se já tiver, aumenta a alocação em 1
          realocarMemoriaOficinaModel(lista, 1);
     }

     oficinaCadastrando->id = lista->qtdOficinas;
     oficinaCadastrando->deletado = 0;

     lista->listaOficinas[lista->qtdOficinas-1] = *oficinaCadastrando;

     printf("Oficina cadastrada com sucesso!\n");
}

// Deleta uma oficina cadastrada
void deletarOficinaModel(struct ListaOficinas *lista, int id) {

     // Auxiliar para saber se encontrou o id.
     int encontrado = 0;

     // Verifica se há alguma oficina cadastrada.
     if (lista->qtdOficinas == 0) {
          printf("Nenhuma oficina foi cadastrada.\n");
          return;
     }

     // Busca pelo id para fazer a deleção.
     for (int i = 0; i < lista->qtdOficinas; i++) {
          if (lista->listaOficinas[i].id == id && lista->listaOficinas[i].deletado == 0) {

               encontrado = 1;
               lista->listaOficinas[i].deletado = 1;
               printf("Oficina deletada com sucesso!\n");

               break;
          }
     }

     // Se não encontrar o id para deleção, avisa o usuário.
     if (!encontrado) {
          printf("Oficina não encontrada.\n");
     }
}

// Atualiza uma oficina cadastrada
void atualizarOficinaModel(struct ListaOficinas *lista, int id, struct Oficinas *oficinaAlterando) {

     // Auxiliar para saber se encontrou o id.
     int encontrado = 0;

     // Verifica se há alguma oficina cadastrada.
     if (lista->qtdOficinas == 0) {
          printf("Nenhuma oficina foi cadastrada.\n");
          return;
     }

     // Busca pelo id para fazer a alteração.
     for (int i = 0; i < lista->qtdOficinas; i++) {
          if (lista->listaOficinas[i].id == id && lista->listaOficinas[i].deletado == 0) {
               encontrado = 1;

               lista->listaOficinas[i] = *oficinaAlterando;
               lista->listaOficinas[i].id = id;
               lista->listaOficinas[i].deletado = 0;

               break;
          }
     }

     if (!encontrado) {
          printf("Fornecedor não encontrado!\n\n");
     }
}

// Lista todas as oficinas cadastradas
void listarTodosOficinaModel(struct ListaOficinas *lista) {

     // Verifica se há pelo menos um cadastro
     if (lista->qtdOficinas > 0) {
          // Se há um ou mais cadastros, exibe todos
          for (int i = 0; i < lista->qtdOficinas; i++) {

               // Verifica se o índice atual existe
               if (lista->listaOficinas[i].deletado == 0) {
                    printf("====================\n"
                      "Id: %d\n"
                      "Nome: %s\n"
                      "Endereço: %s\n"
                      "DDD + Telefone: %s %s\n"
                      "Email: %s\n",
                      lista->listaOficinas[i].id,
                      lista->listaOficinas[i].nome,
                      lista->listaOficinas[i].endereco,
                      lista->listaOficinas[i].ddd,
                      lista->listaOficinas[i].telefone,
                      lista->listaOficinas[i].email);
               }
          }
          printf("====================\n");

     } else {
          // Se não houver, avisa que não há cadastros
          printf("Nenhuma oficina foi cadastrada\n");
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
               printf("====================\n"
                      "Id: %d\n"
                      "Nome: %s\n"
                      "Endereço: %s\n"
                      "DDD + Telefone: %s %s\n"
                      "Email: %s\n"
                      "====================\n",
                      lista->listaOficinas[encontrado].id,
                      lista->listaOficinas[encontrado].nome,
                      lista->listaOficinas[encontrado].endereco,
                      lista->listaOficinas[encontrado].ddd,
                      lista->listaOficinas[encontrado].telefone,
                      lista->listaOficinas[encontrado].email);
          } else {
               printf("Nenhuma oficina encontrada.\n");
          }
     } else {
          // Se não houver, avisa que não há cadastros
          printf("Nenhuma oficina foi cadastrada\n");
     }

}