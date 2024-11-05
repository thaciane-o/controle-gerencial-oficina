#include "modelClientes.h"
#include "../../views/clientes/viewClientes.h"
#include <stdio.h>
#include <stdlib.h>

void cadastrar(struct clientes *cliente) {

    //Abrindo ou criando arquivo para adicionar cadastros
    FILE *dados;
    dados = fopen("DadosClientes.bin", "ab");

    if (dados == NULL) {
        printf("Erro ao cadastrar cliente\n");
        exit(1);
    }

    //Considerando o ID como a ultima posição do ponteiro do Arquivo
    cliente->id = ftell(dados);

    //Adicionando ";" ao armazenar os dados e um "\n" no final, teremos maior controle sobre o acesso aos dados posteriormente
    fprintf(dados, "%d;%s;%s;%s;%s;%s\n", cliente->id, cliente->nome, cliente->telefone, cliente->CPF_CNPJ, cliente->email,
            cliente->endereco);

    /***Após isso, os dados devem estar no seguinte formato dentro do arquivo***

        id;nome;telefone;CPF_CNPJ;email;endereço\n
     */

    printf("Cliente cadastrado com sucesso!\n");
    fclose(dados);
}