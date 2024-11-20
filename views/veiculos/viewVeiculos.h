#ifndef VEICULOS_H
#define VEICULOS_H


void cadastrarVeiculo(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento);
void atualizarVeiculo(struct ListaVeiculos *lista);
void listarVeiculo(struct ListaVeiculos *lista);
void deletarVeiculo(struct ListaVeiculos *lista);
void gerenciarVeiculos(struct ListaClientes *listaProprietarios, struct ListaVeiculos *lista, int opcaoArmazenamento);

#endif //VEICULOS_H
