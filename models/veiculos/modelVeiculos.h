#ifndef MODELVEICULOS_H
#define MODELVEICULOS_H


struct Veiculos {
    int id;
    int idProprietario;
    char modelo[255];
    char marca[255];
    char chassi[17];
    char placa[7];
    int anoFabricacao;
    int deletado;
};

struct ListaVeiculos {
    int qtdVeiculos;
    struct Veiculos *listaVeiculos;
};

void buscarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento);

void armazenarDadosVeiculosModel(struct ListaVeiculos *lista, int opcaoArmazenamento);

void alocarVeiculosModel(struct ListaVeiculos *lista);

void realocarVeiculosModel(struct ListaVeiculos *lista, int qtdAlocada);

void cadastrarVeiculosModel(struct ListaVeiculos *lista, struct Veiculos *veiculo);

void deletarVeiculosModel(struct ListaVeiculos *lista, int id);

void atualizarVeiculosModel(struct ListaVeiculos *lista, int id, struct Veiculos *veiculo);

int verificarIDVeiculoModel(struct ListaVeiculos *lista, int id);

void listarTodosVeiculosModel(struct ListaVeiculos *lista);

void listarVeiculoModel(struct ListaVeiculos *lista, int id);

void listarVeiculosPorClienteModel(struct ListaVeiculos *lista, int id);

#endif //MODELVEICULOS_H
