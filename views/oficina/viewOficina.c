
#include "viewOficina.h"
#include "../../models/oficina/modelOficina.h"
#include <stdio.h>
#include <stdlib.h>

void cadastrarOficinaView(struct ListaOficinas *lista) {
    struct Oficinas oficinaCadastrando;

    printf("\n==============================\n"
           "|     CADASTRO DE OFICINAS     |\n"
           "================================\n");

    oficinaCadastrando.id = gerarIdUnicoOficina();

    printf("Insira o nome da oficina: ");
    setbuf(stdin, NULL);
    fgets(oficinaCadastrando.nome, sizeof(oficinaCadastrando.nome), stdin);

    printf("Insira o endereço da oficina: ");
    setbuf(stdin, NULL);
    fgets(oficinaCadastrando.endereco, sizeof(oficinaCadastrando.endereco), stdin);

    printf("Insira o DDD do telefone da oficina: ");
    scanf("%d", &oficinaCadastrando.ddd);

    printf("Insira o telefone da oficina: ");
    setbuf(stdin, NULL);
    fgets(oficinaCadastrando.telefone, sizeof(oficinaCadastrando.telefone), stdin);

    printf("Insira o email da oficina: ");
    setbuf(stdin, NULL);
    fgets(oficinaCadastrando.email, sizeof(oficinaCadastrando.email), stdin);

    cadastrarOficinaModel(lista, &oficinaCadastrando);
}