
#ifndef MODELNOTASFISCAIS_H
#define MODELNOTASFISCAIS_H

struct notasFiscais {
    int id;
    int *idPecas;
    int *qtdPecas;
    float frete;
    float imposto;
    int idFornecedor;
    int deletado;
};

struct ListaNotasFiscais {
    int qtdNotas;
    struct notasFiscais *listaNotas;
};

void buscarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, int opcaoArmazenamento);

void armazenarDadosNotasFiscaisModel(struct ListaNotasFiscais *lista, int opcaoArmazenamento);

int alocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdPecas);

int realocarMemoriaNotasFiscaisModel(struct ListaNotasFiscais *lista, int qtdAloca, int qtdPecas);

void cadastrarNotasFiscaisModel(struct ListaNotasFiscais *lista, struct notasFiscais *novaNotaFiscal, int qtdPecas);

#endif //MODELNOTASFISCAIS_H
