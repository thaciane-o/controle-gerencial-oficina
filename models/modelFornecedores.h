#ifndef MODELCLIENTES_H
#define MODELCLIENTES_H

struct Fornecedores {
    int id;
    char nomeFantasia[255];
    char razaoSocial[255];
    char inscricaoEstadual[10];
    char cnpj[15];
    char endereco[255];
    char telefone[10];
    char email[255];
    char relatorio[255];
};

int gerarIdUnico();

void cadastrar(struct Fornecedores *fornecedor);

#endif //MODELCLIENTES_H