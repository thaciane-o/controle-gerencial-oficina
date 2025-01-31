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
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
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
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
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
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
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
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
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
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Serviços
    if (opcoesExportacao[5] == 1) {
        fprintf(exportacao, "\t<tabela=servico>\n");
        if (listaServicos->qtdServicos > 0) {
            for (int i = 0; i < listaServicos->qtdServicos; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<idOficina>%d</idOficina>\n"
                        "\t\t\t<descricao>%s</descricao>\n"
                        "\t\t\t<preco>%.2f</preco>\n"
                        "\t\t\t<comissao>%.2f</comissao>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaServicos->listaServicos[i].id,
                        listaServicos->listaServicos[i].idOficina,
                        listaServicos->listaServicos[i].descricao,
                        listaServicos->listaServicos[i].preco,
                        listaServicos->listaServicos[i].comissao,
                        listaServicos->listaServicos[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Funcionarios
    if (opcoesExportacao[6] == 1) {
        fprintf(exportacao, "\t<tabela=funcionario>\n");
        if (listaFuncionarios->qtdFuncionarios > 0) {
            for (int i = 0; i < listaFuncionarios->qtdFuncionarios; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<nome>%s</nome>\n"
                        "\t\t\t<cpf>%s</cpf>\n"
                        "\t\t\t<cargo>%s</cargo>\n"
                        "\t\t\t<salario>%.2f</salario>\n"
                        "\t\t\t<idOficina>%d</idOficina>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaFuncionarios->listaFuncionarios[i].id,
                        listaFuncionarios->listaFuncionarios[i].nome,
                        listaFuncionarios->listaFuncionarios[i].cpf,
                        listaFuncionarios->listaFuncionarios[i].cargo,
                        listaFuncionarios->listaFuncionarios[i].salario,
                        listaFuncionarios->listaFuncionarios[i].idOficina,
                        listaFuncionarios->listaFuncionarios[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Caixas
    if (opcoesExportacao[7] == 1) {
        fprintf(exportacao, "\t<tabela=caixa>\n");
        if (listaCaixas->qtdCaixas > 0) {
            for (int i = 0; i < listaCaixas->qtdCaixas; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<valorCaixa>%.2f</valorCaixa>\n"
                        "\t\t\t<idOficina>%d</idOficina>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaCaixas->listaCaixas[i].id,
                        listaCaixas->listaCaixas[i].valorCaixa,
                        listaCaixas->listaCaixas[i].idOficina,
                        listaCaixas->listaCaixas[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Pagamentos de Cliente
    if (opcoesExportacao[8] == 1) {
        fprintf(exportacao, "\t<tabela=pagamentoCliente>\n");
        if (listaPagamentosCliente->qtdPagamentosCliente > 0) {
            for (int i = 0; i < listaPagamentosCliente->qtdPagamentosCliente; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<tipoPagamento>%d</tipoPagamento>\n"
                        "\t\t\t<valor>%.2f</valor>\n"
                        "\t\t\t<dataPagamento>%s</dataPagamento>\n"
                        "\t\t\t<dataAReceber>%s</dataAReceber>\n"
                        "\t\t\t<dataRecebimento>%s</dataRecebimento>\n"
                        "\t\t\t<idCaixa>%d</idCaixa>\n"
                        "\t\t\t<idCliente>%d</idCliente>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaPagamentosCliente->listaPagamentosCliente[i].id,
                        listaPagamentosCliente->listaPagamentosCliente[i].tipoPagamento,
                        listaPagamentosCliente->listaPagamentosCliente[i].valor,
                        listaPagamentosCliente->listaPagamentosCliente[i].dataPagamento,
                        listaPagamentosCliente->listaPagamentosCliente[i].dataAReceber,
                        listaPagamentosCliente->listaPagamentosCliente[i].dataRecebimento,
                        listaPagamentosCliente->listaPagamentosCliente[i].idCaixa,
                        listaPagamentosCliente->listaPagamentosCliente[i].idCliente,
                        listaPagamentosCliente->listaPagamentosCliente[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Pagamentos a Fornecedor
    if (opcoesExportacao[9] == 1) {
        fprintf(exportacao, "\t<tabela=pagamentoFornecedor>\n");
        if (listaPagamentosFornecedor->qtdPagamentosFornecedor > 0) {
            for (int i = 0; i < listaPagamentosFornecedor->qtdPagamentosFornecedor; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<tipoPagamento>%d</tipoPagamento>\n"
                        "\t\t\t<valor>%.2f</valor>\n"
                        "\t\t\t<dataPagamento>%s</dataPagamento>\n"
                        "\t\t\t<idCaixa>%d</idCaixa>\n"
                        "\t\t\t<idFornecedor>%d</idFornecedor>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaPagamentosFornecedor->listaPagamentosFornecedor[i].id,
                        listaPagamentosFornecedor->listaPagamentosFornecedor[i].tipoPagamento,
                        listaPagamentosFornecedor->listaPagamentosFornecedor[i].valor,
                        listaPagamentosFornecedor->listaPagamentosFornecedor[i].dataPagamento,
                        listaPagamentosFornecedor->listaPagamentosFornecedor[i].idCaixa,
                        listaPagamentosFornecedor->listaPagamentosFornecedor[i].idFornecedor,
                        listaPagamentosFornecedor->listaPagamentosFornecedor[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Agendamentos
    if (opcoesExportacao[10] == 1) {
        fprintf(exportacao, "\t<tabela=agendamento>\n");
        if (listaAgendamentos->qtdAgendamentos > 0) {
            for (int i = 0; i < listaAgendamentos->qtdAgendamentos; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<datahoraInicial>%s</datahoraInicial>\n"
                        "\t\t\t<idVeiculo>%d</idVeiculo>\n"
                        "\t\t\t<idServico>%d</idServico>\n"
                        "\t\t\t<idFuncionario>%d</idFuncionario>\n"
                        "\t\t\t<finalizado>%d</finalizado>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaAgendamentos->listaAgendamentos[i].id,
                        listaAgendamentos->listaAgendamentos[i].datahoraInicial,
                        listaAgendamentos->listaAgendamentos[i].idVeiculo,
                        listaAgendamentos->listaAgendamentos[i].idServico,
                        listaAgendamentos->listaAgendamentos[i].idFuncionario,
                        listaAgendamentos->listaAgendamentos[i].finalizado,
                        listaAgendamentos->listaAgendamentos[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Ordens de Servico
    if (opcoesExportacao[11] == 1) {
        fprintf(exportacao, "\t<tabela=ordemServico>\n");
        if (listaOrdensServico->qtdOrdensServico > 0) {
            for (int i = 0; i < listaOrdensServico->qtdOrdensServico; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<descricao>%s</descricao>\n"
                        "\t\t\t<idPecas>%d</idPecas>\n"
                        "\t\t\t<idAgendamento>%d</idAgendamento>\n"
                        "\t\t\t<valorTotal>%.2f</valorTotal>\n"
                        "\t\t\t<tempoGasto>%.2f</tempoGasto>\n"
                        "\t\t\t<datahoraFinal>%s</datahoraFinal>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaOrdensServico->listaOrdensServico[i].descricao,
                        listaOrdensServico->listaOrdensServico[i].idPecas,
                        listaOrdensServico->listaOrdensServico[i].idAgendamento,
                        listaOrdensServico->listaOrdensServico[i].valorTotal,
                        listaOrdensServico->listaOrdensServico[i].tempoGasto,
                        listaOrdensServico->listaOrdensServico[i].datahoraFinal,
                        listaOrdensServico->listaOrdensServico[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Notas Fiscais
    if (opcoesExportacao[12] == 1) {
        fprintf(exportacao, "\t<tabela=notaFiscal>\n");
        if (listaNotasFiscais->qtdNotas > 0) {
            for (int i = 0; i < listaNotasFiscais->qtdNotas; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<frete>%.2f</frete>\n"
                        "\t\t\t<imposto>%.2f</imposto>\n"
                        "\t\t\t<totalNota>%.2f</totalNota>\n"
                        "\t\t\t<idOficina>%d</idOficina>\n"
                        "\t\t\t<idFornecedor>%d</idFornecedor>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaNotasFiscais->listaNotas[i].id,
                        listaNotasFiscais->listaNotas[i].frete,
                        listaNotasFiscais->listaNotas[i].imposto,
                        listaNotasFiscais->listaNotas[i].totalNota,
                        listaNotasFiscais->listaNotas[i].idOficina,
                        listaNotasFiscais->listaNotas[i].idFornecedor,
                        listaNotasFiscais->listaNotas[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Verifica exportação de Pecas em Notas
    if (opcoesExportacao[13] == 1) {
        fprintf(exportacao, "\t<tabela=pecaNota>\n");
        if (listaPecasNotas->qtdPecasNotas > 0) {
            for (int i = 0; i < listaPecasNotas->qtdPecasNotas; i++) {
                fprintf(exportacao, "\t\t<registro>\n"
                        "\t\t\t<id>%d</id>\n"
                        "\t\t\t<idNota>%d</idNota>\n"
                        "\t\t\t<idPeca>%d</idPeca>\n"
                        "\t\t\t<qtdPecas>%d</qtdPecas>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaPecasNotas->listaPecasNotas[i].id,
                        listaPecasNotas->listaPecasNotas[i].idNota,
                        listaPecasNotas->listaPecasNotas[i].idPeca,
                        listaPecasNotas->listaPecasNotas[i].qtdPecas,
                        listaPecasNotas->listaPecasNotas[i].deletado);
            }
        } else {
            fprintf(exportacao, "\t\t<!-- Não há registros -->\n");
        }
        fprintf(exportacao, "\t</tabela>\n");
    }

    // Finaliza o arquivo XML
    fprintf(exportacao, "</dados>\n");

    // Fehca o arquivo e confirma a exportação
    fclose(exportacao);
    printf("Dados exportados com sucesso!\n\n");
}
