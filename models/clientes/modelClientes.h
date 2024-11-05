#ifndef MODELCLIENTES_H
#define MODELCLIENTES_H



struct clientes {
    int id;
    char telefone[15];
    char CPF_CNPJ[15];
    char nome[255];
    char email[255];
    char endereco[255];
};

void cadastrar(struct clientes *cliente);

#endif //MODELCLIENTES_H
