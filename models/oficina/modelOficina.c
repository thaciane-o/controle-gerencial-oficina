
#include "modelOficina.h"
#include "../../views/oficina/viewOficina.h"
#include <stdio.h>
#include <stdlib.h>

// Gera id único para as oficinas
int gerarIdUnicoOficina() {
     static int idOficina = 0;
     return ++idOficina;
}

// Aloca a memória inicial para a lista de oficinas
void alocarMemoriaOficina(struct ListaOficinas *lista) {

     // Aloca a memória inicial para a lista de oficinas
     lista->listaOficinas = malloc(sizeof(struct Oficinas));

     // Verifica se a alocação deu certo
     if (lista->listaOficinas == NULL) {
          printf("Erro: Memória insuficiente\n");
          exit(EXIT_FAILURE);
     }
}

// Realoca memória da oficina de acordo com a quantidade que deseja alocar (qtdAloca)
void realocarMemoriaOficina(struct ListaOficinas *lista, int qtdAloca) {

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
          alocarMemoriaOficina(lista);
          lista->listaOficinas[lista->qtdOficinas-1] = *oficinaCadastrando;
     } else {
          // Se já tiver, aumenta a alocação em 1
          realocarMemoriaOficina(lista, 1);
          lista->listaOficinas[lista->qtdOficinas-1] = *oficinaCadastrando;
     }

     printf("Oficina cadastrada com sucesso!\n");
}

// Lista todas as oficinas cadastradas
void listarTodosOficinaModel(struct ListaOficinas *lista) {

     // Verifica se há pelo menos um cadastro
     if (lista->qtdOficinas > 0) {
          // Se há um ou mais cadastros, exibe todos
          for (int i = 0; i < lista->qtdOficinas; i++) {

               printf("====================\n"
                      "Id: %d\n"
                      "Nome: %s\n"
                      "Endereço: %s\n"
                      "DDD + Telefone: %d %s\n"
                      "Email: %s\n",
                      lista->listaOficinas[i].id,
                      lista->listaOficinas[i].nome,
                      lista->listaOficinas[i].endereco,
                      lista->listaOficinas[i].ddd,
                      lista->listaOficinas[i].telefone,
                      lista->listaOficinas[i].email);
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
               if (lista->listaOficinas[i].id == id) {
                    encontrado = i;
                    break;
               }
          }

          if (encontrado != -1) {
               printf("====================\n"
                      "Id: %d\n"
                      "Nome: %s\n"
                      "Endereço: %s\n"
                      "DDD + Telefone: %d %s\n"
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