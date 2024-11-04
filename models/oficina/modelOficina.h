
#ifndef MODELOFICINA_H
#define MODELOFICINA_H

struct Oficinas {
    int id;
    char nome[255];
    char endereco[255];
    int ddd;
    char telefone[11];
    char email[255];
};

struct ListaOficinas {
    int qtdOficinas;
    struct Oficinas *listaOficinas;
};

int gerarIdUnicoOficina();

void alocarMemoriaOficina(struct ListaOficinas *lista);
void realocarMemoriaOficina(struct ListaOficinas *oficinas, int qtdAloca);

void cadastrarOficinaModel(struct ListaOficinas *lista, struct Oficinas *oficinaCadastrando);

#endif //MODELOFICINA_H
