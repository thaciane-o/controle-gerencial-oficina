#ifndef MODELVEICULOS_H
#define MODELVEICULOS_H


struct Veiculos {
    int id;
    int idProprietario;
    char modelo[255];
    char marca[255];
    char chassi[18];
    char placa[8];
    int anoFabricacao;
    int deletado;
};

struct ListaVeiculos {
    int qtdVeiculos;
    struct Veiculos *listaVeiculos;
};

void buscarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento);

void armazenarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento);

int alocarVeiculosModel(struct ListaVeiculos *lista);

int realocarVeiculosModel(struct ListaVeiculos *lista, int qtdAlocada);

void cadastrarVeiculosModel(struct ListaVeiculos *lista, struct Veiculos *veiculo);

void deletarVeiculosModel(struct ListaVeiculos *lista, int id);

void atualizarVeiculosModel(struct ListaVeiculos *lista, int id, struct Veiculos *veiculo);

int verificarIDVeiculoModel(struct ListaVeiculos *lista, int id);

void listarTodosVeiculosModel(struct ListaVeiculos *lista);

void buscarIdClienteModel(struct ListaVeiculos *lista, int id);

void listarVeiculosPorClienteModel(struct ListaVeiculos *lista, int id);

#endif //MODELVEICULOS_H
