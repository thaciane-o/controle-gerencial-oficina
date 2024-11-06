
#include "viewOficina.h"
#include "../../models/oficina/modelOficina.h"
#include <stdio.h>
#include <stdlib.h>

// Formulário de cadastro de oficinas
void cadastrarOficinaView(struct ListaOficinas *lista) {
    struct Oficinas oficinaCadastrando;

    printf("\n==============================\n"
           "|     CADASTRO DE OFICINAS     |\n"
           "================================\n");

    printf("Insira o ID da oficina: ");
    setbuf(stdin, NULL);
    scanf("%d", &oficinaCadastrando.id);
    // fgets(oficinaCadastrando.nome, sizeof(oficinaCadastrando.nome), stdin);

    printf("Insira o nome da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %s", oficinaCadastrando.nome);
    // fgets(oficinaCadastrando.nome, sizeof(oficinaCadastrando.nome), stdin);

    printf("Insira o endereço da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %s", oficinaCadastrando.endereco);
    // fgets(oficinaCadastrando.endereco, sizeof(oficinaCadastrando.endereco), stdin);

    printf("Insira o DDD do telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf("%d", &oficinaCadastrando.ddd);

    printf("Insira o telefone da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %s", &oficinaCadastrando.telefone);
    // fgets(oficinaCadastrando.telefone, sizeof(oficinaCadastrando.telefone), stdin);

    printf("Insira o email da oficina: ");
    setbuf(stdin, NULL);
    scanf(" %s", oficinaCadastrando.email);
    // fgets(oficinaCadastrando.email, sizeof(oficinaCadastrando.email), stdin);

    cadastrarOficinaModel(lista, &oficinaCadastrando);
}

// Listagem de oficinas (Todas)
void listarCadastrosOficinaView(struct ListaOficinas *lista) {

    // Pergunta se deseja listar todos, ou buscar por id
    int resp;
    printf("==================\n"
           "| 1 | Busca por ID\n"
           "| 2 | Listar todos\n"
           "| 3 | Voltar\n"
           "==================\n"
           "Opção desejada: ");
    setbuf(stdin, NULL);
    scanf("%d", &resp);

    // Verifica a opção de listagem
    int id = 0;
    switch (resp) {
        case 1:
            printf("Insira o ID desejado para a busca: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            buscarIdOficinaModel(lista, id);
            break;
        case 2:
            listarTodosOficinaModel(lista);
            break;
        case 3:
            return;
            break;
        default:
            printf("Opção inválida, voltando ao menu principal.\n");

    }

}