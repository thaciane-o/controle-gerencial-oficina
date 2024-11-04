
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
          return;
     } else {
          // Se já tiver, aumenta a alocação em 1
          realocarMemoriaOficina(lista, 1);
          lista->listaOficinas[lista->qtdOficinas-1] = *oficinaCadastrando;
     }

     printf("Oficina cadastrada com sucesso!\n");
     printf("Id: %d \nNome: %s \nEndereço: %s \nDDD: %s \nTelefone: %s \nEmail: %s",
            lista->listaOficinas[lista->qtdOficinas-1].id,
            lista->listaOficinas[lista->qtdOficinas-1].nome,
            lista->listaOficinas[lista->qtdOficinas-1].endereco,
            lista->listaOficinas[lista->qtdOficinas-1].ddd,
            lista->listaOficinas[lista->qtdOficinas-1].telefone,
            lista->listaOficinas[lista->qtdOficinas-1].email);



}