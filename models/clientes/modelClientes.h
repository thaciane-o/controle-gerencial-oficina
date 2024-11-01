#ifndef MODELCLIENTES_H
#define MODELCLIENTES_H



struct clientes {
    int id;
    int telefone;
    int CPF_CNPJ;
    char nome[250];
    char email[100];
    char endereco[200];
};


int gerarIdUnico();

void cadastrar(struct clientes *cliente);

#endif //MODELCLIENTES_H
