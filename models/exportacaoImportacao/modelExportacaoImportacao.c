#include "modelExportacaoImportacao.h"

#include "../../models/clientes/modelClientes.h"
#include "../../models/veiculos/modelVeiculos.h"
#include "../../models/oficina/modelOficina.h"
#include "../../models/pecas/modelPecas.h"
#include "../../models/fornecedores/modelFornecedores.h"
#include "../../models/funcionarios/modelFuncionarios.h"
#include "../../models/servicos/modelServicos.h"
#include "../../models/agendamentos/modelAgendamentos.h"
#include "../../models/ordensServico/modelOrdensServico.h"
#include "../../models/caixas/modelCaixa.h"
#include "../../models/pagamentoCliente/modelPagamentoCliente.h"
#include "../../models/pagamentoFornecedor/modelPagamentoFornecedor.h"
#include "../../models/notasFiscais/modelNotasFiscais.h"
#include "../../models/pecasNotas/modelPecasNotas.h"

#include <stdio.h>
#include <stdlib.h>

// Armazena os dados das relações no arquivo
void exportaDadosModel(struct ListaClientes *listaClientes,
                       struct ListaVeiculos *listaVeiculos,
                       struct ListaOficinas *listaOficinas,
                       struct ListaPecas *listaPecas,
                       struct ListaFornecedores *listaFornecedores,
                       struct ListaServicos *listaServicos,
                       struct ListaFuncionarios *listaFuncionarios,
                       struct ListaCaixas *listaCaixas,
                       struct ListaPagamentosCliente *listaPagamentosCliente,
                       struct ListaPagamentosFornecedor *listaPagamentosFornecedor,
                       struct ListaAgendamentos *listaAgendamentos,
                       struct ListaOrdensServico *listaOrdensServico,
                       struct ListaNotasFiscais *listaNotasFiscais,
                       struct ListaPecasNotas *listaPecasNotas,
                       int *opcoesExportacao) {
    // Inicia a abertura de arquivo
    FILE *exportacao = fopen("DadosExportados.xml", "w");

    if (exportacao == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de exportação.\n\n");
        return;
    }

    // Inicia o arquivo XML
    fprintf(exportacao, "<dados>\n");

    // Verifica exportação de Clientes
    if (opcoesExportacao[0] == 1) {
        fprintf(exportacao, "\t<tabela=cliente>\n");
        if (listaClientes->qtdClientes > 0) {
            for (int i = 0; i < listaClientes->qtdClientes; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<ddd>%s</ddd>\n"
                        "\t\t\t<telefone>%s</telefone>\n"
                        "\t\t\t<cpf_cnpj>%s</cpf_cnpj>\n"
                        "\t\t\t<nome>%s</nome>\n"
                        "\t\t\t<email>%s</email>\n"
                        "\t\t\t<endereco>%s</endereco>\n"
                        "\t\t\t<idOficina>%d</idOficina>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaClientes->listaClientes[i].id,
                        listaClientes->listaClientes[i].ddd,
                        listaClientes->listaClientes[i].telefone,
                        listaClientes->listaClientes[i].cpf_cnpj,
                        listaClientes->listaClientes[i].nome,
                        listaClientes->listaClientes[i].email,
                        listaClientes->listaClientes[i].endereco,
                        listaClientes->listaClientes[i].idOficina,
                        listaClientes->listaClientes[i].deletado);
            }
        } else {
            fprintf(exportacao, "<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Veículos
    if (opcoesExportacao[1] == 1) {
        fprintf(exportacao, "\t<tabela=veiculo>\n");
        if (listaVeiculos->qtdVeiculos > 0) {
            for (int i = 0; i < listaVeiculos->qtdVeiculos; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<idProprietario>%d</idProprietario>\n"
                        "\t\t\t<modelo>%s</modelo>\n"
                        "\t\t\t<marca>%s</marca>\n"
                        "\t\t\t<chassi>%s</chassi>\n"
                        "\t\t\t<placa>%s</placa>\n"
                        "\t\t\t<anoFabricacao>%d</anoFabricacao>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaVeiculos->listaVeiculos[i].id,
                        listaVeiculos->listaVeiculos[i].idProprietario,
                        listaVeiculos->listaVeiculos[i].modelo,
                        listaVeiculos->listaVeiculos[i].marca,
                        listaVeiculos->listaVeiculos[i].chassi,
                        listaVeiculos->listaVeiculos[i].placa,
                        listaVeiculos->listaVeiculos[i].anoFabricacao,
                        listaVeiculos->listaVeiculos[i].deletado);
            }
        } else {
            fprintf(exportacao, "<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Oficinas
    if (opcoesExportacao[2] == 1) {
        fprintf(exportacao, "\t<tabela=oficina>\n");
        if (listaOficinas->qtdOficinas > 0) {
            for (int i = 0; i < listaOficinas->qtdOficinas; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<nome>%s</nome>\n"
                        "\t\t\t<endereco>%s</endereco>\n"
                        "\t\t\t<ddd>%s</ddd>\n"
                        "\t\t\t<telefone>%s</telefone>\n"
                        "\t\t\t<email>%s</email>\n"
                        "\t\t\t<porcentagemLucro>%.2f</porcentagemLucro>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaOficinas->listaOficinas[i].id,
                        listaOficinas->listaOficinas[i].nome,
                        listaOficinas->listaOficinas[i].endereco,
                        listaOficinas->listaOficinas[i].ddd,
                        listaOficinas->listaOficinas[i].telefone,
                        listaOficinas->listaOficinas[i].email,
                        listaOficinas->listaOficinas[i].porcentagemLucro,
                        listaOficinas->listaOficinas[i].deletado);
            }
        } else {
            fprintf(exportacao, "<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Peças
    if (opcoesExportacao[3] == 1) {
        fprintf(exportacao, "\t<tabela=peca>\n");
        if (listaPecas->qtdPecas > 0) {
            for (int i = 0; i < listaPecas->qtdPecas; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<descricao>%s</descricao>\n"
                        "\t\t\t<fabricante>%s</fabricante>\n"
                        "\t\t\t<precoCusto>%.2f</precoCusto>\n"
                        "\t\t\t<precoVenda>%.2f</precoVenda>\n"
                        "\t\t\t<qtdEstoque>%d</qtdEstoque>\n"
                        "\t\t\t<estoqueMinimo>%d</estoqueMinimo>\n"
                        "\t\t\t<idOficina>%d</idOficina>\n"
                        "\t\t\t<idFornecedor>%d</idFornecedor>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaPecas->listaPecas[i].id,
                        listaPecas->listaPecas[i].descricao,
                        listaPecas->listaPecas[i].fabricante,
                        listaPecas->listaPecas[i].precoCusto,
                        listaPecas->listaPecas[i].precoVenda,
                        listaPecas->listaPecas[i].qtdEstoque,
                        listaPecas->listaPecas[i].estoqueMinimo,
                        listaPecas->listaPecas[i].idOficina,
                        listaPecas->listaPecas[i].idFornecedor,
                        listaPecas->listaPecas[i].deletado);
            }
        } else {
            fprintf(exportacao, "<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Fornecedores
    if (opcoesExportacao[4] == 1) {
        fprintf(exportacao, "\t<tabela=fornecedor>\n");
        if (listaFornecedores->qtdFornecedores > 0) {
            for (int i = 0; i < listaFornecedores->qtdFornecedores; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<nomeFantasia>%s</nomeFantasia>\n"
                        "\t\t\t<razaoSocial>%s</razaoSocial>\n"
                        "\t\t\t<inscricaoEstadual>%s</inscricaoEstadual>\n"
                        "\t\t\t<cnpj>%s</cnpj>\n"
                        "\t\t\t<endereco>%s</endereco>\n"
                        "\t\t\t<ddd>%s</ddd>\n"
                        "\t\t\t<telefone>%s</telefone>\n"
                        "\t\t\t<email>%s</email>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaFornecedores->listaFornecedores[i].id,
                        listaFornecedores->listaFornecedores[i].nomeFantasia,
                        listaFornecedores->listaFornecedores[i].razaoSocial,
                        listaFornecedores->listaFornecedores[i].inscricaoEstadual,
                        listaFornecedores->listaFornecedores[i].cnpj,
                        listaFornecedores->listaFornecedores[i].endereco,
                        listaFornecedores->listaFornecedores[i].ddd,
                        listaFornecedores->listaFornecedores[i].telefone,
                        listaFornecedores->listaFornecedores[i].email,
                        listaFornecedores->listaFornecedores[i].deletado);
            }
        } else {
            fprintf(exportacao, "<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Finaliza o arquivo XML
    fprintf(exportacao, "</dados>\n");

    // Fehca o arquivo e confirma a exportação
    fclose(exportacao);
    printf("Dados exportados com sucesso!\n\n");
}
