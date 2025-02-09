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
#include <string.h>

// Escreve o arquivo XML com os dados escolhidos
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
                        "\t\t\t<qtdPecas>%d</qtdPecas>\n"
                        "\t\t\t<idAgendamento>%d</idAgendamento>\n"
                        "\t\t\t<valorTotal>%.2f</valorTotal>\n"
                        "\t\t\t<tempoGasto>%.2f</tempoGasto>\n"
                        "\t\t\t<datahoraFinal>%s</datahoraFinal>\n"
                        "\t\t\t<deletado>%d</deletado>\n"
                        "\t\t</registro>\n",
                        listaOrdensServico->listaOrdensServico[i].descricao,
                        listaOrdensServico->listaOrdensServico[i].idPecas,
                        listaOrdensServico->listaOrdensServico[i].qtdPecas,
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

// Pega strings entre tags
void extraiValorTagsModel(char *entrada, char *saida, char *tagAbre, char *tagFecha) {
    char *inicio = strstr(entrada, tagAbre);
    char *fim = strstr(entrada, tagFecha);

    if (inicio && fim && inicio < fim) {
        inicio += strlen(tagAbre); // Avança para depois da tag de abertura
        size_t tamanho = fim - inicio;

        if (tamanho >= 512) {
            tamanho = 512 - 1; // Evita estouro do buffer
        }

        strncpy(saida, inicio, tamanho);
        saida[tamanho] = '\0'; // Adiciona o terminador nulo
    } else {
        strcpy(saida, ""); // Se não encontrar, retorna string vazia
    }
}

// Lê o arquivo de importação e trás os dados escolhidos
void importaDadosModel(struct ListaClientes *listaClientes,
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
                       FILE *arquivo,
                       int *opcoesImportacao,
                       int opcaoArmazenamento) {
    // Variáveis para leitura
    char linha[512];
    int idTabela = -1;

    // Variáveis de armazenamento
    struct Clientes importaCliente;
    struct Veiculos importaVeiculos;
    struct Oficinas importaOficinas;
    struct Pecas importaPecas;
    struct Fornecedores importaFornecedores;
    struct Servicos importaServicos;
    struct Funcionarios importaFuncionarios;
    struct Caixas importaCaixas;
    struct PagamentosCliente importaPagamentosCliente;
    struct PagamentosFornecedor importaPagamentosFornecedor;
    struct Agendamentos importaAgendamentos;
    struct OrdensServico importaOrdensServico;
    struct NotasFiscais importaNotasFiscais;
    struct PecasNotas importaPecasNotas;

    // while (fgets(linha, 512, arquivo) != NULL) {
    //     printf("%s", linha);
    // }
    //
    // fseek(arquivo, 0, SEEK_SET);

    // Lê todas as linhas do arquivo
    while (fgets(linha, 512, arquivo) != NULL) {
        // Ignora linha de inicialização
        if (strcmp(linha, "<dados>\n") == 0) {
            continue;
        }

        // Ajusta o id da tabela que está sendo lida
        if (strcmp(linha, "\t<tabela=cliente>\n") == 0) {
            idTabela = 0;
            continue;
        }
        if (strcmp(linha, "\t<tabela=veiculo>\n") == 0) {
            idTabela = 1;
            continue;
        }
        if (strcmp(linha, "\t<tabela=oficina>\n") == 0) {
            idTabela = 2;
            continue;
        }
        if (strcmp(linha, "\t<tabela=peca>\n") == 0) {
            idTabela = 3;
            continue;
        }
        if (strcmp(linha, "\t<tabela=fornecedor>\n") == 0) {
            idTabela = 4;
            continue;
        }
        if (strcmp(linha, "\t<tabela=servico>\n") == 0) {
            idTabela = 5;
            continue;
        }
        if (strcmp(linha, "\t<tabela=funcionario>\n") == 0) {
            idTabela = 6;
            continue;
        }
        if (strcmp(linha, "\t<tabela=caixa>\n") == 0) {
            idTabela = 7;
            continue;
        }
        if (strcmp(linha, "\t<tabela=pagamentoCliente>\n") == 0) {
            idTabela = 8;
            continue;
        }
        if (strcmp(linha, "\t<tabela=pagamentoFornecedor>\n") == 0) {
            idTabela = 9;
            continue;
        }
        if (strcmp(linha, "\t<tabela=agendamento>\n") == 0) {
            idTabela = 10;
            continue;
        }
        if (strcmp(linha, "\t<tabela=ordemServico>\n") == 0) {
            idTabela = 11;
            continue;
        }
        if (strcmp(linha, "\t<tabela=notaFiscal>\n") == 0) {
            idTabela = 12;
            continue;
        }
        if (strcmp(linha, "\t<tabela=pecaNota>\n") == 0) {
            idTabela = 13;
            continue;
        }

        // Reinicia structs
        if (strcmp(linha, "\t\t<registro>\n") == 0) {
            importaCliente.deletado = -1;
            importaVeiculos.deletado = -1;
            importaOficinas.deletado = -1;
            importaPecas.deletado = -1;
            importaFornecedores.deletado = -1;
            importaServicos.deletado = -1;
            importaFuncionarios.deletado = -1;
            importaCaixas.deletado = -1;
            importaPagamentosCliente.deletado = -1;
            importaPagamentosFornecedor.deletado = -1;
            importaAgendamentos.deletado = -1;
            importaOrdensServico.deletado = -1;
            importaNotasFiscais.deletado = -1;
            importaPecasNotas.deletado = -1;
            continue;
        }

        // Armazena o dado que acabamos de ler
        if (strcmp(linha, "\t\t</registro>\n") == 0) {
            if (opcoesImportacao[idTabela] == 1) {
                switch (idTabela) {
                    case 0:
                        if (importaCliente.deletado != -1) {
                            cadastrarClientesModel(listaClientes, &importaCliente, 0);
                        }
                        break;
                    case 1:
                        if (importaVeiculos.deletado != -1) {
                            cadastrarVeiculosModel(listaVeiculos, &importaVeiculos, 0);
                        }
                        break;
                    case 2:
                        if (importaOficinas.deletado != -1) {
                            cadastrarOficinaModel(listaOficinas, &importaOficinas, listaCaixas, 0);
                        }
                        break;
                    case 3:
                        if (importaPecas.deletado != -1) {
                            cadastrarPecaModel(listaPecas, &importaPecas, 0);
                        }
                        break;
                    case 4:
                        if (importaFornecedores.deletado != -1) {
                            cadastrarFornecedoresModel(listaFornecedores, &importaFornecedores, 0);
                        }
                        break;
                    case 5:
                        if (importaServicos.deletado != -1) {
                            cadastrarServicoModel(listaServicos, &importaServicos, 0);
                        }
                        break;
                    case 6:
                        if (importaFuncionarios.deletado != -1) {
                            cadastrarFuncionariosModel(listaFuncionarios, &importaFuncionarios, 0);
                        }
                        break;
                    case 7:
                        if (importaCaixas.deletado != -1) {
                            cadastrarCaixasModel(listaCaixas, &importaCaixas);
                        }
                        break;
                    case 8:
                        if (importaPagamentosCliente.deletado != -1) {
                            cadastrarPagamentosClienteModel(listaPagamentosCliente, &importaPagamentosCliente,
                                                            listaCaixas, 0);
                        }
                        break;
                    case 9:
                        if (importaPagamentosFornecedor.deletado != -1) {
                            cadastrarPagamentosFornecedorModel(listaPagamentosFornecedor, &importaPagamentosFornecedor,
                                                               listaCaixas, 0);
                        }
                        break;
                    case 10:
                        if (importaAgendamentos.deletado != -1) {
                            cadastrarAgendamentosModel(listaAgendamentos, &importaAgendamentos, 0);
                        }
                        break;
                    case 11:
                        if (importaOrdensServico.deletado != -1) {
                            cadastrarOrdensServicoModel(listaOrdensServico, &importaOrdensServico, 0);
                        }
                        break;
                    case 12:
                        if (importaNotasFiscais.deletado != -1) {
                            cadastrarNotasFiscaisModel(listaNotasFiscais, &importaNotasFiscais, listaPecas,
                                                       listaOficinas, listaPecasNotas, 0, 0);
                        }
                        break;
                    case 13:
                        if (importaPecasNotas.deletado != -1) {
                            cadastrarPecaNotaModel(listaPecasNotas, &importaPecasNotas, 0);
                        }
                        break;
                }
            }
            continue;
        }

        // Reinicia o id da tabela que estamos lendo
        if (strcmp(linha, "\t</tabela>\n") == 0) {
            idTabela = -1;
            continue;
        }

        // Finaliza a leitura do arquivo
        if (strcmp(linha, "</dados>\n") == 0) {
            break;
        }

        // Verifica se vai buscar os dados da tabela atual
        if (idTabela != -1) {
            if (opcoesImportacao[idTabela] == 0) {
                continue;
            }
        }

        // Lê campo de id
        if (strncmp(linha, "\t\t\t<id>", 7) == 0) {
            int id;
            sscanf(linha, "\t\t\t<id>%d</id>\n", &id);

            switch (idTabela) {
                default:
                    break;
                case 0:
                    importaCliente.id = id;
                    break;
                case 1:
                    importaVeiculos.id = id;
                    break;
                case 2:
                    importaOficinas.id = id;
                    break;
                case 3:
                    importaPecas.id = id;
                    break;
                case 4:
                    importaFornecedores.id = id;
                    break;
                case 5:
                    importaServicos.id = id;
                    break;
                case 6:
                    importaFuncionarios.id = id;
                    break;
                case 7:
                    importaCaixas.id = id;
                    break;
                case 8:
                    importaPagamentosCliente.id = id;
                    break;
                case 9:
                    importaPagamentosFornecedor.id = id;
                    break;
                case 10:
                    importaAgendamentos.id = id;
                    break;
                case 12:
                    importaNotasFiscais.id = id;
                    break;
                case 13:
                    importaPecasNotas.id = id;
                    break;
            }
            continue;
        }

        // Lê campo de ddd
        if (strncmp(linha, "\t\t\t<ddd>", 8) == 0) {
            char ddd[3];
            extraiValorTagsModel(linha, ddd, "<ddd>", "</ddd>");
            switch (idTabela) {
                default:
                    break;
                case 0:
                    strcpy(importaCliente.ddd, ddd);
                    break;
                case 2:
                    strcpy(importaOficinas.ddd, ddd);
                    break;
                case 4:
                    strcpy(importaFornecedores.ddd, ddd);
                    break;
            }
            continue;
        }

        // Lê campo de telefone
        if (strncmp(linha, "\t\t\t<telefone>", 13) == 0) {
            char telefone[11];
            extraiValorTagsModel(linha, telefone, "<telefone>", "</telefone>");

            switch (idTabela) {
                default:
                    break;
                case 0:
                    strcpy(importaCliente.telefone, telefone);
                    break;
                case 2:
                    strcpy(importaOficinas.telefone, telefone);
                    break;
                case 4:
                    strcpy(importaFornecedores.telefone, telefone);
                    break;
            }
            continue;
        }

        // Lê campo de cpf_cnpj
        if (strncmp(linha, "\t\t\t<cpf_cnpj>", 13) == 0) {
            char cpf_cnpj[15];
            extraiValorTagsModel(linha, cpf_cnpj, "<cpf_cnpj>", "</cpf_cnpj>");

            switch (idTabela) {
                default:
                    break;
                case 0:
                    strcpy(importaCliente.cpf_cnpj, cpf_cnpj);
                    break;
            }
            continue;
        }

        // Lê campo de nome
        if (strncmp(linha, "\t\t\t<nome>", 9) == 0) {
            char nome[255];
            extraiValorTagsModel(linha, nome, "<nome>", "</nome>");

            switch (idTabela) {
                default:
                    break;
                case 0:
                    strcpy(importaCliente.nome, nome);
                    break;
                case 2:
                    strcpy(importaCliente.nome, nome);
                    break;
                case 6:
                    strcpy(importaFuncionarios.nome, nome);
                    break;
            }
            continue;
        }

        // Lê campo de email
        if (strncmp(linha, "\t\t\t<email>", 10) == 0) {
            char email[255];
            extraiValorTagsModel(linha, email, "<email>", "</email>");

            switch (idTabela) {
                default:
                    break;
                case 0:
                    strcpy(importaCliente.email, email);
                    break;
                case 2:
                    strcpy(importaOficinas.email, email);
                    break;
                case 4:
                    strcpy(importaFornecedores.email, email);
                    break;
            }
            continue;
        }

        // Lê campo de endereço
        if (strncmp(linha, "\t\t\t<endereco>", 13) == 0) {
            char endereco[255];
            extraiValorTagsModel(linha, endereco, "<endereco>", "</endereco>");

            switch (idTabela) {
                default:
                    break;
                case 0:
                    strcpy(importaCliente.endereco, endereco);
                    break;
                case 2:
                    strcpy(importaOficinas.endereco, endereco);
                    break;
                case 4:
                    strcpy(importaFornecedores.endereco, endereco);
                    break;
            }
            continue;
        }

        // Lê campo de modelo
        if (strncmp(linha, "\t\t\t<modelo>", 11) == 0) {
            char modelo[255];
            extraiValorTagsModel(linha, modelo, "<modelo>", "</modelo>");

            switch (idTabela) {
                default:
                    break;
                case 1:
                    strcpy(importaVeiculos.modelo, modelo);
                    break;
            }
            continue;
        }

        // Lê campo de marca
        if (strncmp(linha, "\t\t\t<marca>", 10) == 0) {
            char marca[255];
            extraiValorTagsModel(linha, marca, "<marca>", "</marca>");

            switch (idTabela) {
                default:
                    break;
                case 1:
                    strcpy(importaVeiculos.marca, marca);
                    break;
            }
            continue;
        }

        // Lê campo de chassi
        if (strncmp(linha, "\t\t\t<chassi>", 11) == 0) {
            char chassi[255];
            extraiValorTagsModel(linha, chassi, "<chassi>", "</chassi>");

            switch (idTabela) {
                default:
                    break;
                case 1:
                    strcpy(importaVeiculos.chassi, chassi);
                    break;
            }
            continue;
        }

        // Lê campo de placa
        if (strncmp(linha, "\t\t\t<placa>", 10) == 0) {
            char placa[255];
            extraiValorTagsModel(linha, placa, "<placa>", "</placa>");

            switch (idTabela) {
                default:
                    break;
                case 1:
                    strcpy(importaVeiculos.placa, placa);
                    break;
            }
            continue;
        }

        // Lê campo de ano fabricacao
        if (strncmp(linha, "\t\t\t<anoFabricacao>", 18) == 0) {
            int anoFabricacao;
            sscanf(linha, "\t\t\t<anoFabricacao>%d</anoFabricacao>\n", &anoFabricacao);

            switch (idTabela) {
                default:
                    break;
                case 1:
                    importaVeiculos.anoFabricacao = anoFabricacao;
                    break;
            }
            continue;
        }

        // Lê campo de porcentagem lucro
        if (strncmp(linha, "\t\t\t<porcentagemLucro>", 21) == 0) {
            float porcentagemLucro[255];
            extraiValorTagsModel(linha, porcentagemLucro, "<porcentagemLucro>", "</porcentagemLucro>");

            switch (idTabela) {
                default:
                    break;
                case 2:
                    importaOficinas.porcentagemLucro = atof(porcentagemLucro);
                    break;
            }
            continue;
        }

        // Lê campo de descricao
        if (strncmp(linha, "\t\t\t<descricao>", 14) == 0) {
            char descricao[255];
            extraiValorTagsModel(linha, descricao, "<descricao>", "</descricao>");

            switch (idTabela) {
                default:
                    break;
                case 3:
                    strcpy(importaPecas.descricao, descricao);
                    break;
                case 5:
                    strcpy(importaServicos.descricao, descricao);
                    break;
                case 11:
                    strcpy(importaOrdensServico.descricao, descricao);
                    break;
            }
            continue;
        }

        // Lê campo de fabricante
        if (strncmp(linha, "\t\t\t<fabricante>", 15) == 0) {
            char fabricante[255];
            extraiValorTagsModel(linha, fabricante, "<fabricante>", "</fabricante>");

            switch (idTabela) {
                default:
                    break;
                case 3:
                    strcpy(importaPecas.fabricante, fabricante);
                    break;
            }
            continue;
        }

        // Lê campo de preco custo
        if (strncmp(linha, "\t\t\t<precoCusto>", 15) == 0) {
            char precoCusto[255];
            extraiValorTagsModel(linha, precoCusto, "<precoCusto>", "</precoCusto>");

            switch (idTabela) {
                default:
                    break;
                case 3:
                    importaPecas.precoCusto = atof(precoCusto);
                    break;
            }
            continue;
        }

        // Lê campo de preco venda
        if (strncmp(linha, "\t\t\t<precoVenda>", 15) == 0) {
            char precoVenda[255];
            extraiValorTagsModel(linha, precoVenda, "<precoVenda>", "</precoVenda>");

            switch (idTabela) {
                default:
                    break;
                case 3:
                    importaPecas.precoVenda = atof(precoVenda);
                    break;
            }
            continue;
        }

        // Lê campo de quantidade em estoque
        if (strncmp(linha, "\t\t\t<qtdEstoque>", 15) == 0) {
            int qtdEstoque;
            sscanf(linha, "\t\t\t<qtdEstoque>%d</qtdEstoque>\n", &qtdEstoque);

            switch (idTabela) {
                default:
                    break;
                case 3:
                    importaPecas.qtdEstoque = qtdEstoque;
                    break;
            }
            continue;
        }

        // Lê campo de quantidade minima em estoque
        if (strncmp(linha, "\t\t\t<estoqueMinimo>", 18) == 0) {
            int estoqueMinimo;
            sscanf(linha, "\t\t\t<estoqueMinimo>%d</estoqueMinimo>\n", &estoqueMinimo);

            switch (idTabela) {
                default:
                    break;
                case 3:
                    importaPecas.estoqueMinimo = estoqueMinimo;
                    break;
            }
            continue;
        }

        // Lê campo de nome fantasia
        if (strncmp(linha, "\t\t\t<nomeFantasia>", 17) == 0) {
            char nomeFantasia[255];
            extraiValorTagsModel(linha, nomeFantasia, "<nomeFantasia>", "</nomeFantasia>");

            switch (idTabela) {
                default:
                    break;
                case 4:
                    strcpy(importaFornecedores.nomeFantasia, nomeFantasia);
                    break;
            }
            continue;
        }

        // Lê campo de razao social
        if (strncmp(linha, "\t\t\t<razaoSocial>", 16) == 0) {
            char razaoSocial[255];
            extraiValorTagsModel(linha, razaoSocial, "<razaoSocial>", "</razaoSocial>");

            switch (idTabela) {
                default:
                    break;
                case 4:
                    strcpy(importaFornecedores.razaoSocial, razaoSocial);
                    break;
            }
            continue;
        }

        // Lê campo de inscricao estadual
        if (strncmp(linha, "\t\t\t<inscricaoEstadual>", 16) == 0) {
            char inscricaoEstadual[255];
            extraiValorTagsModel(linha, inscricaoEstadual, "<inscricaoEstadual>", "</inscricaoEstadual>");

            switch (idTabela) {
                default:
                    break;
                case 4:
                    strcpy(importaFornecedores.inscricaoEstadual, inscricaoEstadual);
                    break;
            }
            continue;
        }

        // Lê campo de cnpj
        if (strncmp(linha, "\t\t\t<cnpj>", 9) == 0) {
            char cnpj[15];
            extraiValorTagsModel(linha, cnpj, "<cnpj>", "</cnpj>");

            switch (idTabela) {
                default:
                    break;
                case 4:
                    strcpy(importaFornecedores.cnpj, cnpj);
                    break;
            }
            continue;
        }

        // Lê campo de preco
        if (strncmp(linha, "\t\t\t<preco>", 10) == 0) {
            char preco[255];
            extraiValorTagsModel(linha, preco, "<preco>", "</preco>");

            switch (idTabela) {
                default:
                    break;
                case 5:
                    importaServicos.preco = atof(preco);
                    break;
            }
            continue;
        }

        // Lê campo de comissao
        if (strncmp(linha, "\t\t\t<comissao>", 13) == 0) {
            char comissao[255];
            extraiValorTagsModel(linha, comissao, "<comissao>", "</comissao>");

            switch (idTabela) {
                default:
                    break;
                case 5:
                    importaServicos.comissao = atof(comissao);
                    break;
            }
            continue;
        }

        // Lê campo de cpf
        if (strncmp(linha, "\t\t\t<cpf>", 8) == 0) {
            char cpf[12];
            extraiValorTagsModel(linha, cpf, "<cpf>", "</cpf>");

            switch (idTabela) {
                default:
                    break;
                case 6:
                    strcpy(importaFuncionarios.cpf, cpf);
                    break;
            }
            continue;
        }

        // Lê campo de cargo
        if (strncmp(linha, "\t\t\t<cargo>", 10) == 0) {
            char cargo[255];
            extraiValorTagsModel(linha, cargo, "<cargo>", "</cargo>");

            switch (idTabela) {
                default:
                    break;
                case 6:
                    strcpy(importaFuncionarios.cargo, cargo);
                    break;
            }
            continue;
        }

        // Lê campo de salario
        if (strncmp(linha, "\t\t\t<salario>", 12) == 0) {
            char salario[255];
            extraiValorTagsModel(linha, salario, "<salario>", "</salario>");

            switch (idTabela) {
                default:
                    break;
                case 6:
                    importaFuncionarios.salario = atof(salario);
                    break;
            }
            continue;
        }

        // Lê campo de valor caixa
        if (strncmp(linha, "\t\t\t<valorCaixa>", 15) == 0) {
            char valorCaixa[255];
            extraiValorTagsModel(linha, valorCaixa, "<valorCaixa>", "</valorCaixa>");

            switch (idTabela) {
                default:
                    break;
                case 7:
                    importaCaixas.valorCaixa = atof(valorCaixa);
                    break;
            }
            continue;
        }

        // Lê campo de tipo pagamento
        if (strncmp(linha, "\t\t\t<tipoPagamento>", 18) == 0) {
            int tipoPagamento;
            sscanf(linha, "\t\t\t<tipoPagamento>%d</tipoPagamento>\n", &tipoPagamento);

            switch (idTabela) {
                default:
                    break;
                case 8:
                    importaPagamentosCliente.tipoPagamento = tipoPagamento;
                    break;
                case 9:
                    importaPagamentosFornecedor.tipoPagamento = tipoPagamento;
                    break;
            }
            continue;
        }

        // Lê campo de valor
        if (strncmp(linha, "\t\t\t<valor>", 10) == 0) {
            char valor[255];
            extraiValorTagsModel(linha, valor, "<valor>", "</valor>");

            switch (idTabela) {
                default:
                    break;
                case 8:
                    importaPagamentosCliente.valor = atof(valor);
                    break;
                case 9:
                    importaPagamentosFornecedor.valor = atof(valor);
                    break;
            }
            continue;
        }

        // Lê campo de data pagamento
        if (strncmp(linha, "\t\t\t<dataPagamento>", 18) == 0) {
            char dataPagamento[11];
            extraiValorTagsModel(linha, dataPagamento, "<dataPagamento>", "</dataPagamento>");

            switch (idTabela) {
                default:
                    break;
                case 8:
                    strcpy(importaPagamentosCliente.dataPagamento, dataPagamento);
                    break;
                case 9:
                    strcpy(importaPagamentosFornecedor.dataPagamento, dataPagamento);
                    break;
            }
            continue;
        }

        // Lê campo de data a receber
        if (strncmp(linha, "\t\t\t<dataAReceber>", 17) == 0) {
            char dataAReceber[11];
            extraiValorTagsModel(linha, dataAReceber, "<dataAReceber>", "</dataAReceber>");

            switch (idTabela) {
                default:
                    break;
                case 8:
                    strcpy(importaPagamentosCliente.dataAReceber, dataAReceber);
                    break;
            }
            continue;
        }

        // Lê campo de data recebimento
        if (strncmp(linha, "\t\t\t<dataRecebimento>", 20) == 0) {
            char dataRecebimento[11];
            extraiValorTagsModel(linha, dataRecebimento, "<dataRecebimento>", "</dataRecebimento>");

            switch (idTabela) {
                default:
                    break;
                case 8:
                    strcpy(importaPagamentosCliente.dataRecebimento, dataRecebimento);
                    break;
            }
            continue;
        }

        // Lê campo de data hora inicial
        if (strncmp(linha, "\t\t\t<datahoraInicial>", 20) == 0) {
            char datahoraInicial[17];
            extraiValorTagsModel(linha, datahoraInicial, "<datahoraInicial>", "</datahoraInicial>");

            switch (idTabela) {
                default:
                    break;
                case 10:
                    strcpy(importaAgendamentos.datahoraInicial, datahoraInicial);
                    break;
            }
            continue;
        }

        // Lê campo de data hora final
        if (strncmp(linha, "\t\t\t<datahoraFinal>", 18) == 0) {
            char datahoraFinal[17];
            extraiValorTagsModel(linha, datahoraFinal, "<datahoraFinal>", "</datahoraFinal>");

            switch (idTabela) {
                default:
                    break;
                case 11:
                    strcpy(importaOrdensServico.datahoraFinal, datahoraFinal);
                    break;
            }
            continue;
        }

        // Lê campo de finalizado
        if (strncmp(linha, "\t\t\t<finalizado>", 15) == 0) {
            int finalizado;
            sscanf(linha, "\t\t\t<finalizado>%d</finalizado>\n", &finalizado);

            switch (idTabela) {
                default:
                    break;
                case 10:
                    importaAgendamentos.finalizado = finalizado;
                    break;
            }
            continue;
        }

        // Lê campo de valor total
        if (strncmp(linha, "\t\t\t<valorTotal>", 15) == 0) {
            char valorTotal[255];
            extraiValorTagsModel(linha, valorTotal, "<valorTotal>", "</valorTotal>");

            switch (idTabela) {
                default:
                    break;
                case 11:
                    importaOrdensServico.valorTotal = atof(valorTotal);
                    break;
            }
            continue;
        }

        // Lê campo de tempo gasto
        if (strncmp(linha, "\t\t\t<tempoGasto>", 15) == 0) {
            char tempoGasto[255];
            extraiValorTagsModel(linha, tempoGasto, "<tempoGasto>", "</tempoGasto>");

            switch (idTabela) {
                default:
                    break;
                case 11:
                    importaOrdensServico.tempoGasto = atof(tempoGasto);
                    break;
            }
            continue;
        }

        // Lê campo de frete
        if (strncmp(linha, "\t\t\t<frete>", 10) == 0) {
            char frete[255];
            extraiValorTagsModel(linha, frete, "<frete>", "</frete>");

            switch (idTabela) {
                default:
                    break;
                case 12:
                    importaNotasFiscais.frete = atof(frete);
                    break;
            }
            continue;
        }

        // Lê campo de imposto
        if (strncmp(linha, "\t\t\t<imposto>", 12) == 0) {
            char imposto[255];
            extraiValorTagsModel(linha, imposto, "<imposto>", "</imposto>");

            switch (idTabela) {
                default:
                    break;
                case 12:
                    importaNotasFiscais.imposto = atof(imposto);
                    break;
            }
            continue;
        }

        // Lê campo de total nota
        if (strncmp(linha, "\t\t\t<totalNota>", 14) == 0) {
            char totalNota[255];
            extraiValorTagsModel(linha, totalNota, "<totalNota>", "</totalNota>");

            switch (idTabela) {
                default:
                    break;
                case 12:
                    importaNotasFiscais.totalNota = atof(totalNota);
                    break;
            }
            continue;
        }

        // Lê campo de qtd pecas
        if (strncmp(linha, "\t\t\t<qtdPecas>", 13) == 0) {
            int qtdPecas;
            sscanf(linha, "\t\t\t<qtdPecas>%d</qtdPecas>\n", &qtdPecas);

            switch (idTabela) {
                default:
                    break;
                case 11:
                    importaOrdensServico.qtdPecas = qtdPecas;
                case 13:
                    importaPecasNotas.qtdPecas = qtdPecas;
                    break;
            }
            continue;
        }

        // Lê campo de id oficina
        if (strncmp(linha, "\t\t\t<idOficina>", 14) == 0) {
            int idOficina;
            sscanf(linha, "\t\t\t<idOficina>%d</idOficina>\n", &idOficina);

            switch (idTabela) {
                default:
                    break;
                case 0:
                    importaCliente.idOficina = idOficina;
                    break;
                case 3:
                    importaPecas.idOficina = idOficina;
                    break;
                case 5:
                    importaServicos.idOficina = idOficina;
                    break;
                case 6:
                    importaFuncionarios.idOficina = idOficina;
                    break;
                case 7:
                    importaCaixas.idOficina = idOficina;
                    break;
                case 12:
                    importaNotasFiscais.idOficina = idOficina;
                    break;
            }
            continue;
        }

        // Lê campo de id proprietario
        if (strncmp(linha, "\t\t\t<idProprietario>", 19) == 0) {
            int idProprietario;
            sscanf(linha, "\t\t\t<idProprietario>%d</idProprietario>\n", &idProprietario);

            switch (idTabela) {
                default:
                    break;
                case 1:
                    importaVeiculos.idProprietario = idProprietario;
                    break;
            }
            continue;
        }

        // Lê campo de id fornecedor
        if (strncmp(linha, "\t\t\t<idFornecedor>", 17) == 0) {
            int idFornecedor;
            sscanf(linha, "\t\t\t<idFornecedor>%d</idFornecedor>\n", &idFornecedor);

            switch (idTabela) {
                default:
                    break;
                case 3:
                    importaPecas.idFornecedor = idFornecedor;
                    break;
                case 9:
                    importaPagamentosFornecedor.idFornecedor = idFornecedor;
                    break;
                case 12:
                    importaNotasFiscais.idFornecedor = idFornecedor;
                    break;
            }
            continue;
        }

        // Lê campo de id caixa
        if (strncmp(linha, "\t\t\t<idCaixa>", 12) == 0) {
            int idCaixa;
            sscanf(linha, "\t\t\t<idCaixa>%d</idCaixa>\n", &idCaixa);

            switch (idTabela) {
                default:
                    break;
                case 8:
                    importaPagamentosCliente.idCaixa = idCaixa;
                    break;
                case 9:
                    importaPagamentosFornecedor.idCaixa = idCaixa;
                    break;
            }
            continue;
        }

        // Lê campo de id cliente
        if (strncmp(linha, "\t\t\t<idCliente>", 14) == 0) {
            int idCliente;
            sscanf(linha, "\t\t\t<idCliente>%d</idCliente>\n", &idCliente);

            switch (idTabela) {
                default:
                    break;
                case 8:
                    importaPagamentosCliente.idCliente = idCliente;
                    break;
            }
            continue;
        }

        // Lê campo de id veiculo
        if (strncmp(linha, "\t\t\t<idVeiculo>", 14) == 0) {
            int idVeiculo;
            sscanf(linha, "\t\t\t<idVeiculo>%d</idVeiculo>\n", &idVeiculo);

            switch (idTabela) {
                default:
                    break;
                case 10:
                    importaAgendamentos.idVeiculo = idVeiculo;
                    break;
            }
            continue;
        }

        // Lê campo de id servico
        if (strncmp(linha, "\t\t\t<idServico>", 14) == 0) {
            int idServico;
            sscanf(linha, "\t\t\t<idServico>%d</idServico>\n", &idServico);

            switch (idTabela) {
                default:
                    break;
                case 10:
                    importaAgendamentos.idServico = idServico;
                    break;
            }
            continue;
        }

        // Lê campo de id funcionario
        if (strncmp(linha, "\t\t\t<idFuncionario>", 18) == 0) {
            int idFuncionario;
            sscanf(linha, "\t\t\t<idFuncionario>%d</idFuncionario>\n", &idFuncionario);

            switch (idTabela) {
                default:
                    break;
                case 10:
                    importaAgendamentos.idFuncionario = idFuncionario;
                    break;
            }
            continue;
        }

        // Lê campo de id pecas
        if (strncmp(linha, "\t\t\t<idPecas>", 12) == 0) {
            int idPecas;
            sscanf(linha, "\t\t\t<idPecas>%d</idPecas>\n", &idPecas);

            switch (idTabela) {
                default:
                    break;
                case 11:
                    importaOrdensServico.idPecas = idPecas;
                    break;
                    continue;
            }
        }

        // Lê campo de id agendamentos
        if (strncmp(linha, "\t\t\t<idAgendamento>", 18) == 0) {
            int idAgendamento;
            sscanf(linha, "\t\t\t<idAgendamento>%d</idAgendamento>\n", &idAgendamento);

            switch (idTabela) {
                default:
                    break;
                case 11:
                    importaOrdensServico.idAgendamento = idAgendamento;
                    break;
            }
            continue;
        }

        // Lê campo de id nota
        if (strncmp(linha, "\t\t\t<idNota>", 11) == 0) {
            int idNota;
            sscanf(linha, "\t\t\t<idNota>%d</idNota>\n", &idNota);

            switch (idTabela) {
                default:
                    break;
                case 13:
                    importaPecasNotas.idNota = idNota;
                    break;
            }
            continue;
        }

        // Lê campo de id pecas em notas
        if (strncmp(linha, "\t\t\t<idPeca>", 11) == 0) {
            int idPeca;
            sscanf(linha, "\t\t\t<idPeca>%d</idPeca>\n", &idPeca);

            switch (idTabela) {
                default:
                    break;
                case 13:
                    importaPecasNotas.idPeca = idPeca;
                    break;
            }
            continue;
        }

        // Lê campo de deletado
        if (strncmp(linha, "\t\t\t<deletado>", 13) == 0) {
            int deletado;
            sscanf(linha, "\t\t\t<deletado>%d</deletado>\n", &deletado);

            switch (idTabela) {
                default:
                    break;
                case 0:
                    importaCliente.deletado = deletado;
                    break;
                case 1:
                    importaVeiculos.deletado = deletado;
                    break;
                case 2:
                    importaOficinas.deletado = deletado;
                    break;
                case 3:
                    importaPecas.deletado = deletado;
                    break;
                case 4:
                    importaFornecedores.deletado = deletado;
                    break;
                case 5:
                    importaServicos.deletado = deletado;
                    break;
                case 6:
                    importaFuncionarios.deletado = deletado;
                    break;
                case 7:
                    importaCaixas.deletado = deletado;
                    break;
                case 8:
                    importaPagamentosCliente.deletado = deletado;
                    break;
                case 9:
                    importaPagamentosFornecedor.deletado = deletado;
                    break;
                case 10:
                    importaAgendamentos.deletado = deletado;
                    break;
                case 11:
                    importaOrdensServico.deletado = deletado;
                    break;
                case 12:
                    importaNotasFiscais.deletado = deletado;
                    break;
                case 13:
                    importaPecasNotas.deletado = deletado;
                    break;
            }
            continue;
        }
    }

    fclose(arquivo);
}
