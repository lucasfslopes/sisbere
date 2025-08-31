/*
Trabalho Semestral 1 periodo - Entrega 21-09-2025.
Curso: Analise e desenvolvimento de sistemas.
Tema: Sistema de gestao de uma mercearia "Bere".
Docente: Wesley Marchi.
Discentes: Breno Almeida, Joao Manoel, Lucas Lopes, Rafael Ribeiro e Yago.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sistema = 1, seletor = 0, quantidade = 0, cancelar = 0, quantidadeLimpeza = 0, quantidadeAlimentos = 0, quantidadePadaria = 0, estadoCaixa = 0, quantidadeVendas = 0, quantidadeProdutosDia = 0, descontoManual = 0;
float subTotalLimpeza = 0, subTotalAlimentos = 0, subTotalPadaria = 0, totalLimpeza = 0, totalAlimentos = 0, totalPadaria = 0, subTotal = 0, descontos = 0, total = 0, dinheiro = 0, pix = 0, cartao = 0, saldoDevedor = 0, valorEntrada = 0, troco = 0, valorAbertura = 0, faturamentoTotal = 0, faturamentoLimpeza = 0, faturamentoAlimentos = 0, faturamentoPadaria = 0;
    
void bemVindo();
void volteSempre();

int estoque[39];

int main()
{

    system("cls"); //Limpa o prompt de comando antes de exibir novas infos
    bemVindo(); //Chama a função para imprimir o cabeçalho com bem vindo
    printf("\n\n\nO sistema esta sendo iniciado...\n");

    for(int i = 0; i < 98; i++) {
        printf(">");
        usleep(25000);
    }
    
    printf(" 100%%\nSistema iniciado!");
    usleep(1000000);

    estoque[11] = 50;
    estoque[12] = 30;
    estoque[13] = 0;
    estoque[14] = 20;
    estoque[15] = 100;
    estoque[16] = 15;
    estoque[17] = 60;
    estoque[21] = 10;
    estoque[22] = 15;
    estoque[23] = 10;
    estoque[24] = 5;
    estoque[25] = 20;
    estoque[26] = 6;
    estoque[27] = 15;

    while (sistema)
    {

        cancelar = 0; 

        system("cls"); //Limpa o prompt de comando antes de exibir novas infos
        bemVindo(); //Chama a função para imprimir o cabeçalho com bem vindo

        printf("-------------------------------------------------------------------------------------------------------\n                                              Tela Inicial\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
        printf("1. Material de Limpeza\n2. Venda de Alimentos\n3. Padaria\n4. Pagamento\n5. Abertura de Caixa\n6. Fechamento de Caixa\n7. Sair\n"); // listagem do menu inicial

        scanf("%d", &seletor);
        getchar();

        switch (seletor)
        {

            case 1: // Material de Limpeza

                if(estadoCaixa == 0) {
                    printf("Voce precisa abrir o caixa primeiro!!!\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                    break;
                }

                while (seletor != 0)
                {

                    system("cls");
                    bemVindo();
                    
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                          Produtos de Limpeza\n");
                    printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu material de limpeza
                    printf("Item   Produto                            Valor do Item        Estoque\n");
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("11.    Detergente                         R$ 1.99              %d\n", estoque[11]);
                    printf("12.    Sabao em Po (1kg)                  R$ 8.99              %d\n", estoque[12]);
                    printf("13.    Esponja                            R$ 1.50              %d\n", estoque[13]);
                    printf("14.    Amaciante(1Lt)                     R$ 15.00             %d\n", estoque[14]);
                    printf("15.    Bucha de Pia (kit c/3)             R$ 4.99              %d\n", estoque[15]);
                    printf("16.    Desinfetante(1Lt)                  R$ 7.99              %d\n", estoque[16]);
                    printf("17.    Sabao em Barra(Un)                 R$ 1.00              %d\n\n", estoque[17]);
                    printf("0. Voltar ao Menu Principal\n\n");

                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("Sub total Limpeza: R$ %.2f    Quantidade de Produtos de Limpeza: %d\n", subTotalLimpeza, quantidadeLimpeza);
                    printf("-------------------------------------------------------------------------------------------------------\n");

                    scanf("%d", &seletor);
                    getchar();

                    if(seletor !=0) {
                        printf("Digite a quantidade:\n");
                        scanf("%d", &quantidade);
                        getchar();
                    }

                    switch (seletor)
                    {
                        case 11:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalLimpeza += (quantidade * 1.99);
                                quantidadeLimpeza += quantidade;
                            }   
                            break;

                        case 12:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalLimpeza += (quantidade * 8.99);
                                quantidadeLimpeza += quantidade;
                            }
                            break;

                        case 13:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalLimpeza += (quantidade * 1.50);
                                quantidadeLimpeza += quantidade;
                            }
                            break;

                        case 14:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalLimpeza += (quantidade * 15.00);
                                quantidadeLimpeza += quantidade;
                            }
                            break;

                        case 15:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalLimpeza += (quantidade * 4.99);
                                quantidadeLimpeza += quantidade;
                            }
                            break;

                        case 16:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalLimpeza += (quantidade * 7.99);
                                quantidadeLimpeza += quantidade;
                            }
                            break;

                        case 17:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalLimpeza += (quantidade * 1.00);
                                quantidadeLimpeza += quantidade;
                            }
                            break;

                        case 0:
                            break;
                        
                        default:
                            printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n");
                            getchar();
                            break;
                    }                
                }
                break;

            case 2: // Venda de Alimentos

                if(estadoCaixa == 0) {
                    printf("Voce precisa abrir o caixa primeiro!!!\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                    break;
                }

                while (seletor != 0)
                {

                    system("cls");
                    bemVindo();

                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                          Produtos de Limpeza\n");
                    printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu material de limpeza
                    printf("Item   Produto                            Valor do Item        Estoque\n");
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("21.    Cafe                               R$ 19.99             %d\n", estoque[21]);
                    printf("22.    Leite (cx)                         R$ 5.90              %d\n", estoque[22]);
                    printf("23.    Arroz (1kg)                        R$ 4.50              %d\n", estoque[23]);
                    printf("24.    Feijao Preto (1kg)                 R$ 8.00              %d\n", estoque[24]);
                    printf("25.    Acucar (1kg)                       R$ 5.00              %d\n", estoque[25]);
                    printf("26.    Sal (1kg)                          R$ 2.00              %d\n", estoque[26]);
                    printf("27.    Farinha de Trigo (1kg)             R$ 5.00              %d\n\n", estoque[27]);
                    printf("0. Voltar ao Menu Principal\n\n");

                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("Sub total Alimentos: R$ %.2f    Quantidade de Produtos de Alimentos: %d\n", subTotalAlimentos, quantidadeAlimentos);
                    printf("-------------------------------------------------------------------------------------------------------\n");

                    scanf("%d", &seletor);
                    getchar();

                    if(seletor !=0) {
                        printf("Digite a quantidade:\n");
                        scanf("%d", &quantidade);
                        getchar();
                    }

                    switch (seletor)
                    {
                        case 21:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalAlimentos += (quantidade * 19.99);
                                quantidadeAlimentos += quantidade;
                            }
                            break;

                        case 22:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalAlimentos += (quantidade * 5.90);
                                quantidadeAlimentos += quantidade;
                            }
                            break;

                        case 23:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalAlimentos += (quantidade * 4.50);
                                quantidadeAlimentos += quantidade;
                            }
                            break;

                        case 24:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalAlimentos += (quantidade * 8.00);
                                quantidadeAlimentos += quantidade;
                            }
                            break;

                        case 25:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalAlimentos += (quantidade * 5.00);
                                quantidadeAlimentos += quantidade;
                            }
                            break;

                        case 26:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalAlimentos += (quantidade * 2.00);
                                quantidadeAlimentos += quantidade;
                            }
                            break;

                        case 27:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalAlimentos += (quantidade * 5.00);
                                quantidadeAlimentos += quantidade;
                            }
                            break;

                        case 0:
                            break;
                        
                        default:
                            printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n");
                            getchar();
                            break;
                    }

                }

                break;

            case 3: // Padaria

                if(estadoCaixa == 0) {
                    printf("Voce precisa abrir o caixa primeiro!!!\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                    break;
                }

                while (seletor != 0)
                {

                    system("cls");
                    bemVindo();

                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                                Padaria\n");
                    printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu Padaria
                    printf("Item   Produto                            Valor do Item        Estoque\n");
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("31. Pao de Forma                          R$ 9.50              %d\n", estoque[31]);
                    printf("32. Pao de Integral                       R$ 12.50             %d\n", estoque[32]);
                    printf("33. Pao Frances (Unid)                    R$ 1.90              %d\n", estoque[33]);
                    printf("34. Sonho                                 R$ 8.50              %d\n", estoque[34]);
                    printf("35. Biscoito(kg)                          R$ 12.50             %d\n", estoque[35]);
                    printf("36. Pao Doce (Un)                         R$ 2.50              %d\n", estoque[36]);
                    printf("37. Salgado (Un)                          R$ 17.50             %d\n\n", estoque[37]);
                    printf("0. Voltar ao Menu Principal\n\n");

                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("Sub total Padaria: R$ %.2f    Quantidade de Produtos de Padaria: %d\n", subTotalPadaria, quantidadePadaria);
                    printf("-------------------------------------------------------------------------------------------------------\n");

                    scanf("%d", &seletor);
                    getchar();

                    if(seletor !=0) {
                        printf("Digite a quantidade:\n");
                        scanf("%d", &quantidade);
                        getchar();
                    }

                    switch (seletor)
                    {
                        case 31:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalPadaria += (quantidade * 9.50);
                                quantidadePadaria += quantidade;
                            }
                            break;
                        
                        case 32:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalPadaria += (quantidade * 12.50);
                                quantidadePadaria += quantidade;
                            }
                            break;
                        
                        case 33:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalPadaria += (quantidade * 1.90);
                                quantidadePadaria += quantidade;
                            }
                            break;

                        case 34:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalPadaria += (quantidade * 8.50);
                                quantidadePadaria += quantidade;
                            }
                            break;

                        case 35:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalPadaria += (quantidade * 12.50);
                                quantidadePadaria += quantidade;
                            }
                            break;

                        case 36:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalPadaria += (quantidade * 2.50);
                                quantidadePadaria += quantidade;
                            }
                            break;

                        case 37:
                            if(estoque[seletor] < quantidade){
                                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                            }
                            else {
                                estoque[seletor] -= quantidade;
                                subTotalPadaria += (quantidade * 17.50);
                                quantidadePadaria += quantidade;
                            }
                            break;

                        case 0:
                            break;
                            
                        default:
                            printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n");
                            getchar();
                            break;
                    }                    
                }

                break;

            case 4: // Pagamento

                if (subTotalLimpeza + subTotalAlimentos + subTotalPadaria == 0)
                {
                    printf("Adicione produtos ao carrinho antes de prosseguir para pagamento!!!\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                    break;
                }

                while (cancelar == 0)
                {

                    if(dinheiro < 50){
                        descontos = (dinheiro * 5 / 100);
                    }
                    else if(dinheiro < 200) {
                        descontos = (dinheiro * 10 / 100);
                    }
                    else if(dinheiro >= 200){
                        descontos = (dinheiro * descontoManual / 100);
                    }
                    
                    subTotal = subTotalLimpeza + subTotalAlimentos + subTotalPadaria;
                    totalLimpeza = subTotalLimpeza - (subTotalLimpeza * (descontos*100/subTotal) / 100);
                    totalAlimentos = subTotalAlimentos - (subTotalAlimentos * (descontos*100/subTotal) / 100);
                    totalPadaria = subTotalPadaria - (subTotalPadaria * (descontos*100/subTotal) / 100);
                    total = totalLimpeza + totalAlimentos + totalPadaria;
                    saldoDevedor = total - (dinheiro + cartao);

                    if (saldoDevedor < 0)
                    {
                        troco = (dinheiro + cartao) - total;
                        saldoDevedor = 0;                        
                    }

                    system("cls");
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                               Pagamento\n");
                    printf("-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu Pagamento

                    printf("1. Dinheiro A Vista (5%% / 10%% ou mais %% de Desconto)\n");
                    printf("2. Cartao\n");
                    printf("3. Finalizar\n");
                    printf("4. Cancelar\n\n");
                    printf("Digite uma opcao do Menu\n\n");

                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("Quantidade de Produtos:   Limpeza %d   |   Alimentos %d   |   Padaria %d   |     Qtde Total %d\n", quantidadeLimpeza, quantidadeAlimentos, quantidadePadaria, (quantidadeLimpeza + quantidadeAlimentos + quantidadePadaria));
                    printf("-------------------------------------------------------------------------------------------------------\n\n");
                    printf("                                                      Subtotal em Limpeza:                 R$ %.2f\n", subTotalLimpeza);
                    printf("                                                      Subtotal em Alimentos:               R$ %.2f\n", subTotalAlimentos);
                    printf("                                                      Subtotal em Padaria:                 R$ %.2f\n", subTotalPadaria);
                    printf("                                                      -------------------------------------------------\n");
                    printf("                                                      Sub Total:                           R$ %.2f\n", subTotal);
                    printf("                                                      -------------------------------------------------\n");
                    printf("                                                      Descontos totais:                    R$ %.2f\n", descontos);
                    printf("                                                      -------------------------------------------------\n");
                    printf("                                                      Total em Limpeza:                    R$ %.2f\n", totalLimpeza);
                    printf("                                                      Total em Alimentos:                  R$ %.2f\n", totalAlimentos);
                    printf("                                                      Total em Padaria:                    R$ %.2f\n", totalPadaria);
                    printf("                                                      =================================================\n");
                    printf("                                                      Total:                               R$ %.2f\n", total);
                    printf("                                                      =================================================\n");
                    printf("                                                                          Dinheiro:        R$ %.2f\n", dinheiro);
                    printf("                                                                          Cartao:          R$ %.2f\n\n", cartao);
                    printf("                                                                          Saldo Devedor:   R$ %.2f\n\n", saldoDevedor);
                    printf("                                                      -------------------------------------------------\n");
                    
                    if(troco > 0){
                        printf("                                                                          Troco:           R$ %.2f\n", troco);
                    }

                    scanf("%d", &seletor);
                    getchar();

                    
                    switch (seletor)
                    {
                        case 1: //Sub menu Pagamento - Opcao 1 Dinheiro
                            
                            if(saldoDevedor <= 0) {
                                printf("Nao possui saldo devedor!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                                break;
                            }
                            
                            printf("Digite o valor em Dinheiro:\n");
                            scanf("%f", &valorEntrada);
                            getchar();

                            dinheiro += valorEntrada;

                            if(dinheiro >= 200) {
                                printf("Qual a porcentagem (%%) de Desconto?\n");
                                scanf("%d", &descontoManual);
                                getchar();
                            }

                            break;

                        case 2: //Sub menu Pagamento - Opcao 2 Cartao
                            
                            if(saldoDevedor <= 0) {
                                printf("Nao possui saldo devedor!\nAperte qualquer tecla para continuar...\n");
                                getchar();
                                break;
                            }
                        
                            printf("Digite o valor em Cartao:\n");
                            scanf("%f", &valorEntrada);
                            getchar();

                            if(valorEntrada <= saldoDevedor){
                                printf("Processando Pagamento:\n");

                                for(int i = 0; i < 98; i++) {
                                    printf(">");
                                    usleep(25000);
                                }
                                
                                printf(" 100%%\nPagamento OK\n");                            
                                cartao += valorEntrada;
                                usleep(2000000);
                                break;
                            }
                            
                            printf("O valor digitado para cartao nao pode ser maior que o saldo devedor!\nAperte qualquer tecla para continuar...\n");
                            getchar();                         
                            break;

                        case 3: //Sub menu Pagamento - Opcao 3 Finalizar
                            if (saldoDevedor == 0)
                            {

                                printf("Tem certeza que deseja Finalizar?\n0 = Nao / 1 = Sim\n");
                                scanf("%d", &seletor);
                                getchar();

                                if (seletor == 1)
                                {

                                    faturamentoTotal += total;
                                    faturamentoLimpeza += totalLimpeza;
                                    faturamentoAlimentos += totalAlimentos;
                                    faturamentoPadaria += totalPadaria;
                                    quantidadeVendas++;
                                    quantidadeProdutosDia += quantidadeLimpeza + quantidadeAlimentos + quantidadePadaria;

                                    quantidadeLimpeza = 0;
                                    quantidadeAlimentos = 0;
                                    quantidadePadaria = 0;
                                    subTotalLimpeza = 0;
                                    subTotalAlimentos = 0;
                                    subTotalPadaria = 0;
                                    totalLimpeza = 0;
                                    totalAlimentos = 0;
                                    totalPadaria = 0;
                                    subTotal = 0;
                                    descontos = 0;
                                    total = 0;
                                    dinheiro = 0;
                                    pix = 0;
                                    cartao = 0;
                                    saldoDevedor = 0;
                                    valorEntrada = 0;
                                    troco = 0;
                                    
                                    system("cls");

                                    volteSempre();

                                    usleep(3000000);
                                    cancelar = 1;
                                    break;
                                }

                                else if(seletor == 0) {
                                    continue;
                                }

                                else
                                {
                                    printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n");
                                    getchar();
                                }
                            }
                            break;

                        case 4: //Sub menu Pagamento - Opcao 4 Cancelar
                            printf("Tem certeza que deseja Cancelar?\n0 = Nao / 1 = Sim\n");
                            scanf("%d", &cancelar);
                            getchar();

                            if (cancelar == 1)
                            {
                                quantidadeLimpeza = 0;
                                quantidadeAlimentos = 0;
                                quantidadePadaria = 0;
                                subTotalLimpeza = 0;
                                subTotalAlimentos = 0;
                                subTotalPadaria = 0;
                                totalLimpeza = 0;
                                totalAlimentos = 0;
                                totalPadaria = 0;
                                subTotal = 0;
                                descontos = 0;
                                total = 0;
                                dinheiro = 0;
                                pix = 0;
                                cartao = 0;
                                saldoDevedor = 0;
                                valorEntrada = 0;
                                troco = 0;
                                break;
                            }
                            break;
                    
                    default:
                        printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n");
                        getchar();
                        break;
                    }
                  
            
                    
                }

                break;
            
            case 5: // Abertura de Caixa

                if(estadoCaixa == 1){
                    system("cls"); //Limpa o prompt de comando antes de exibir novas infos
                    bemVindo();
                    
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                           Abertura de Caixa\n");
                    printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu Abertura de Caixa
                    printf("O caixa ja esta aberto!              Valor de Abertura: R$ %.2f\nAperte qualquer tecla para continuar...", valorAbertura);
                    getchar();
                }
                
                else {
                    
                    system("cls"); //Limpa o prompt de comando antes de exibir novas infos
                    bemVindo();
                    
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                           Abertura de Caixa\n");
                    printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu Abertura de Caixa
                    printf("Digite o valor que deseja abrir o caixa:\nR$ ");
                    scanf("%f", &valorAbertura);
                    getchar();

                    printf("\nVoce precisa definir o estoque do dia para Padaria!\n\n");

                    printf("31. Pao de Forma - Digite a quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();
                    estoque[31] = quantidade;

                    printf("32. Pao de Integral - Digite a quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();
                    estoque[32] = quantidade;

                    printf("33. Pao Frances (Unid) - Digite a quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();
                    estoque[33] = quantidade;

                    printf("34. Sonho - Digite a quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();
                    estoque[34] = quantidade;

                    printf("35. Biscoito(kg) - Digite a quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();
                    estoque[35] = quantidade;

                    printf("36. Pao Doce (Un) - Digite a quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();
                    estoque[36] = quantidade;

                    printf("37. Salgado (Un) - Digite a quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();
                    estoque[37] = quantidade;

                    printf("\nAbertura Concluida!\nAperte qualquer tecla para continuar...");
                    getchar();

                    estadoCaixa = 1;
                }

            break;

            case 6: // Fechamento de Caixa

                if(estadoCaixa == 0) {
                    printf("Voce precisa abrir o caixa primeiro!!!\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    getchar();
                    break;
                }

                while (seletor != 0)
                {        
                    system("cls"); //Limpa o prompt de comando antes de exibir novas infos
                    bemVindo();
                    
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                          Fechamento de Caixa\n");
                    printf("-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu Fechamento de Caixa

                    printf("Valor de Abertura:  R$ %.2f                                        Dinheiro em Caixa:  R$ %.2f\n", valorAbertura, (faturamentoTotal + valorAbertura));
                    printf("Faturamento Total:  R$ %.2f\n\n", faturamentoTotal);
                    printf("Vendas realizadas no dia: %d\n", quantidadeVendas);
                    printf("Produtos vendidos no dia: %d\n\n", quantidadeProdutosDia);
                    
                    printf("-------------------------------------------------------------------------------------------------------\n");
                    printf("                                        Faturamento por Categoria\n");
                    printf("-------------------------------------------------------------------------------------------------------\n\n");

                    printf("Faturamento Total em Limpeza:    R$ %.2f\n\n", faturamentoLimpeza);
                    printf("Faturamento Total em Alimentos:  R$ %.2f\n\n", faturamentoAlimentos);
                    printf("Faturamento Total em Padaria:    R$ %.2f\n\n", faturamentoPadaria);

                    printf("-------------------------------------------------------------------------------------------------------\n\n");
                    printf("Deseja Fechar o Caixa?\n0 = Nao / 1 = Sim\n");
                    scanf("%d", &seletor);
                    getchar();

                    if(seletor == 1){

                        valorAbertura = 0;
                        faturamentoTotal = 0;
                        faturamentoLimpeza = 0;
                        faturamentoAlimentos = 0;
                        faturamentoPadaria = 0;

                        quantidadeVendas = 0;
                        quantidadeProdutosDia = 0;
                        

                        estadoCaixa = 0;

                        printf("\nFechamento Concluido!\nAperte qualquer tecla para continuar...");
                        getchar();

                        break;

                    }
                }

            break;
            

            case 7: // Encerra o sistema
                sistema = 0;
                break;

            default:

                printf("Opcao invalida\n\n");
                getchar();

                break;
        }
    }

    return 0;
}

void bemVindo() {
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@                                                                                                     @\n");
    printf("@                Sistema de gestao Magos do Dev 1.0                                                   @\n");
    printf("@                                                                                                     @\n");
    printf("@                @@@@@   @@@@@  @@@    @@@     @@    @@  @@  @@@    @@  @@@@@     @@@@@               @\n");
    printf("@                @@  @@  @@     @@ @  @ @@     @@    @@  @@  @@ @   @@  @@  @@   @@   @@              @\n");
    printf("@                @@@@    @@@@@  @@  @@  @@      @@  @@   @@  @@  @  @@  @@   @@  @@   @@              @\n");
    printf("@                @@  @@  @@     @@      @@       @@@@    @@  @@   @ @@  @@  @@   @@   @@              @\n");
    printf("@                @@@@@   @@@@@  @@      @@        @@     @@  @@    @@@  @@@@@     @@@@@               @\n");
    printf("@                                                                                                     @\n");
    printf("@                Autores: Breno, Joao M, Lucas, Rafael e Yago.                                        @\n"); // Cabecario apresentacao sistema
    printf("@                                                                                                     @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
}

void volteSempre() {
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    usleep(100000);
    printf("@                                                                                                     @\n");
    usleep(100000);
    printf("@    Sistema de gestao Magos do Dev 1.0                                                               @\n");
    usleep(100000);
    printf("@                                                                                                     @\n");
    usleep(100000);
    printf("@    @@    @@    @@@@@   @@    @@@@@@  @@@@@       @@@@@   @@@@@  @@@    @@@  @@@@@   @@@@@   @@@@@   @\n");
    usleep(100000);
    printf("@    @@    @@   @@   @@  @@      @@    @@         @@       @@     @@ @  @ @@  @@  @@  @@  @@  @@      @\n");
    usleep(100000);
    printf("@     @@  @@    @@   @@  @@      @@    @@@@@       @@@@@   @@@@@  @@  @@  @@  @@@@@   @@@@@   @@@@@   @\n");
    usleep(100000);
    printf("@      @@@@     @@   @@  @@      @@    @@              @@  @@     @@      @@  @@      @@  @   @@      @\n");
    usleep(100000);
    printf("@       @@       @@@@@   @@@@@   @@    @@@@@       @@@@@   @@@@@  @@      @@  @@      @@   @  @@@@@   @\n");
    usleep(100000);
    printf("@                                                                                                     @\n");
    usleep(100000);
    printf("@    Autores: Breno, Joao M, Lucas, Rafael e Yago.                                                    @\n"); // Cabecario apresentacao sistema
    usleep(100000);
    printf("@                                                                                                     @\n");
    usleep(100000);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
    usleep(100000);
    printf("-------------------------------------------------------------------------------------------------------\n");
}