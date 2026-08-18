#include <stdio.h>
#include <stdlib.h> //Biblioteca que possui o system("cls") que limpa o prompt de comando
#include <unistd.h> //Biblioteca que possui o usleep/delay
#include <string.h>
#include <time.h>

struct strSessao{
    int sessaoAtiva;
    char user[13];
    int tipo;
}sessao;

typedef struct {
    int cod;
    char user[13];
    char password[9];
    int tipo;
}usuarios;

typedef struct {
    int cod;
    char nome[50];
    char nomeS[50];
    char cpf[11];
    char rua[80];
    char bairro[20];
    char tel[20];
}cliente;

typedef struct {
    int cod;
    char descricao[40];
    char categoria[21];
    float precoCompra;
    int margemLucro;
    float precoVenda;
    int estoque;
    int estoqueMinimo;
}produto;

typedef struct {
    int numVenda;
    char nome[50];
    int dia;
    int mes;
    int ano;
    int quantidade;
    float total;
    char pagamento;
}vendas;

typedef struct {
    int numVenda;
    int cod;
    char descricao[40];
    float precoUn;
    int quantidade;
    float precoTotal;
}itensVendas;

typedef struct {
    int cod;
    char descricao[40];
    char categoria[21];
    int quantidade;
    float precoUn;
    float precoTotal;
}carrinho;

typedef struct {
    int numVenda;
    int dia;
    int mes;
    int ano;
    float dinheiro;
    float cartao;
    char tipoPago[3];
}pagamentos;

//Prototipos de funcao
int verificarArquivos();
void iniciarSessao(void);
void menu(void);
int cadastroUsuarios(void);
int cadastroClientes(void);
int cadastroProdutos(void);
int cadastroCategoria(void);
int registrarVenda(char clienteNome[], int quantidade, float valor, char pagamento);
void registrarItensVendas(int numVenda);
int novaVenda(void);
void addCarrinho(int codigo, int quantidade);
int sangriaCaixa(void);
int pagamento(void);
int finalizarVenda(int numVenda, float total);
int cancelarVenda(int numVenda);
int registrarPagamento(int numVenda, float d, float c);
int carregarProdutos(void);
int carregarClientes(void);
int carregarVendas(void);
int carregarItensVendas(void);
int carregarCategorias(void);
int carregarPagamentos(void);
int listarClientes(void);
int listarProdutos(int tipoListagem);
int listarVendas(void);
int listarVendasAbertas(void);
int listarItensVendas(int numVenda);
int listarCarrinho(void);
int listarCategorias(void);
int listarPagamentos(void);
int atualizarEstoque(void);
void relatorioClientes(void);
void relatorioProdutos(void);
void relatorioVendas(void);
void relatorioPagamentos(void);
int contarRegistros(char *endereco);
void aberturaCaixa(void);
void fechamentoCaixa(void);
void printSessao(void);
void atualizarData(void);
void texto(int t);

// novas funções
void ordenarClientesPorNome(void);
void clientesQueCompraramNoPeriodo(void);
void ordenarProdutosPorDescricao(void);
void listarProdutosComEstoqueCritico(void);
void listarProdutosMaisVendidosPeriodo(void);
void listarVendasPorPeriodo(void);
void faturamentoConsolidadoPorPeriodo(void);
int dataDentroDoPeriodo(int d, int m, int a,int di, int mi, int ai, int df, int mf, int af);
void ordenarProdutosComEstoqueCritico(void);

//Diretório de arquivos
const char diretorioUsuarios[] = "usuarios.txt";
const char diretorioClientes[] = "clientes.txt";
const char diretorioProdutos[] = "produtos.txt";
const char diretorioVendas[] = "vendas.txt";
const char diretorioItensVendas[] = "itensvendas.txt";
const char diretorioPagamentos[] = "pagamentos.txt";
const char diretorioCategorias[] = "categorias.txt";

char categorias[4][20] = {"zero", "Alimentos", "Material de Limpeza", "Panificacao"};
char tipoUsuario[3][25] = {"zero", "Administrador do sistema", "Usuario"};
char tipoPagamento[5][3] = {"zero", "d", "c"};

produto *ptrProdutos;
cliente *ptrClientes;
vendas *ptrVendas;
itensVendas *ptrItensVendas;
carrinho *ptrCarrinho;
pagamentos *ptrPagamentos;
char categoria[21][20];

int sistema = 1, tamanhoMallocClientes = 0, tamanhoMallocProdutos = 0, tamanhoMallocVendas = 0, tamanhoMallocItensVendas = 0, tamanhoMallocPagamentos = 0, quantidadeCategorias = 0, estadoCaixa = 0, quantidadeVendas = 0, quantidadeProdutosDia = 0, contadorCarrinho = 0, dia = 0, mes = 0, ano = 0;
float valorAberturaCaixa = 0, valorEmCaixa = 0;

int main() {
    verificarArquivos();
    carregarCategorias();
    atualizarData();

    while (sistema == 1) {
        if(sessao.sessaoAtiva == 1){
            menu();        
        }
        else {
            iniciarSessao();
        }
    }
    return 0;
}

int verificarArquivos(){
    FILE *arquivo;

    if ((arquivo = fopen(diretorioUsuarios, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }
    fclose(arquivo); //fecha o arquivo

    if ((arquivo = fopen(diretorioClientes, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }
    fclose(arquivo); //fecha o arquivo

    if ((arquivo = fopen(diretorioProdutos, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }
    fclose(arquivo); //fecha o arquivo

    if ((arquivo = fopen(diretorioVendas, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }
    fclose(arquivo); //fecha o arquivo

    if ((arquivo = fopen(diretorioPagamentos, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }
    fclose(arquivo); //fecha o arquivo

    carregarProdutos();
}

void iniciarSessao(){
    char inputUser[13];
    char inputPassword[10];
    int i = 0, mallocUserTemp;
    usuarios *ptrUserTemp;
    FILE *arquivo;

    mallocUserTemp = contarRegistros(diretorioUsuarios);

    ptrUserTemp = malloc(mallocUserTemp * sizeof(usuarios));

    if ((arquivo = fopen(diretorioUsuarios, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        //return 1;
    }
    else {
        while(fscanf(arquivo, "%d;%[^;];%[^;];%d\n",
            &(ptrUserTemp + i)->cod,
            (ptrUserTemp + i)->user,
            (ptrUserTemp + i)->password,
            &(ptrUserTemp + i)->tipo) == 4) {
            i++;
        }
    }
    fclose(arquivo); //fecha o arquivo

    while(sessao.sessaoAtiva != 1){
        system("cls"); //Limpa o prompt de comando
        texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
        printf("-------------------------------------------------------------------------------------------------------\n                                            INICIAR SESSAO\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
        
        printf("Usuario: ");
        scanf("%s", &inputUser);
        printf("Senha: ");
        scanf("%s", &inputPassword);

        for(int i=0; i < mallocUserTemp; i++){
            if(strcmp(inputUser, (ptrUserTemp + i)->user) == 0){
                if(strcmp(inputPassword, (ptrUserTemp + i)->password) == 0){
                    sessao.sessaoAtiva = 1;
                    strcpy(sessao.user, (ptrUserTemp + i)->user);
                    sessao.tipo = (ptrUserTemp + i)->tipo;

                    printf("Login com sucesso!\n");
                    usleep(1000000);
                }
            }
        }
        if(sessao.sessaoAtiva != 1){
            printf("Usuario ou senha incorretos!\n");
            usleep(2000000);
        }
    }    
}

void menu(void){
    int seletor;

    system("cls"); //Limpa o prompt de comando
    texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
    printSessao();
    printf("-------------------------------------------------------------------------------------------------------\n                                            MENU PRINCIPAL\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
    printf("1.  Cadastros\n2.  Vendas\n3.  Abertura de Caixa\n4.  Fechamento de Caixa\n5.  Relatorios\n\n0.  Sair\n\nDigite uma Opcao:\n");

        scanf("%d", &seletor);

        switch (seletor)
        {
        case 1: //1. Cadastros
            
            system("cls"); //Limpa o prompt de comando
            texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
            printSessao();
            printf("-------------------------------------------------------------------------------------------------------\n                                              CADASTROS\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
            printf("1.  Cadastro de Usuarios\n2.  Cadastro de Clientes\n3.  Cadastro de Produtos\n4.  Cadastro de Categoria\n\n0.  Sair\n\nDigite uma Opcao:\n");
            scanf("%d", &seletor);

            switch (seletor)
            {
            case 1: cadastroUsuarios(); break;
            case 2: cadastroClientes(); break; //1.1 Cadastro de Clientes
            case 3: cadastroProdutos(); break; //1.2 Cadastro de Produtos
            case 4: cadastroCategoria(); break;
            default: break;
            }
            break;

        case 2: //2. Vendas 
            
            system("cls"); //Limpa o prompt de comando
            texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
            printSessao();
            printf("-------------------------------------------------------------------------------------------------------\n                                                VENDAS\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
            printf("1.  Nova venda\n2.  Retirada de Caixa (Sangria)\n3.  Pagamento\n\n0.  Sair\n\nDigite uma Opcao:\n");
            scanf("%d", &seletor);

            switch (seletor)
            {
            case 1: novaVenda(); break; //2.1 Nova venda      
            case 2: sangriaCaixa(); break; //2.2 Retirada de Caixa (Sangria)
            case 3: pagamento(); break; //2.3 Pagamento
            default: break;
            }
            break;

        case 3: //3. Abertura de Caixa
            
            system("cls"); //Limpa o prompt de comando
            texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
            printSessao();
            printf("-------------------------------------------------------------------------------------------------------\n                                           ABERTURA DE CAIXA\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
            printf("1.  Abrir o Caixa\n\n0.  Sair\n\nDigite uma Opcao:\n");
            scanf("%d", &seletor);

            switch (seletor)
            {
            case 1: aberturaCaixa(); break; //3.1 Abrir o Caixa
            default: break;
            }
            break;

        case 4: //4. Fechamento de Caixa
            
            system("cls"); //Limpa o prompt de comando
            texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
            printSessao();
            printf("-------------------------------------------------------------------------------------------------------\n                                          FECHAMENTO DO CAIXA\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
            printf("1.  Fechar o Caixa\n\n0.  Sair\n\nDigite uma Opcao:\n");
            scanf("%d", &seletor);

            switch (seletor)
            {
            case 1: fechamentoCaixa(); break; //4.1 Fechar o Caixa
            default: break;
            }
            break;

        case 5: //5.Relatórios
            
            system("cls"); //Limpa o prompt de comando
            texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
            printSessao();
            printf("-------------------------------------------------------------------------------------------------------\n                                              RELATORIOS\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
            printf("1.  Listagem dos Clientes\n2.  Listagem dos Produtos\n3.  Listagem das Vendas\n4.  Listagem dos Pagamentos\n\n0.  Sair\n\nDigite uma Opcao:\n");
            scanf("%d", &seletor);

            switch (seletor)
            {
            case 1: relatorioClientes(); break; //5.1 Listagem dos Clientes
            case 2: relatorioProdutos(); break; //5.2 Listagem dos Produtos
            case 3: relatorioVendas(); break; //5.3 Listagem das Vendas
            case 4: relatorioPagamentos(); break;
            default: break;
            }
            break;

        case 0:        
        sistema = 0; break;//0.Sair
        default: break;
        }
}

int cadastroUsuarios(){
    
    if (sessao.tipo != 1) {
        printf("Voce precisa estar logado como Administrador pra acessar esta opcao!\n");
        usleep(3000000);
    }
    else{
        int c, seletor, ultimoCadastroUsuario = 0, proximoCadastroUsuario = 0;
        char temp[13];
        usuarios *uTemp;
        FILE *arquivo;

        uTemp = malloc(sizeof(usuarios));

        if(contarRegistros(diretorioUsuarios) < 1){
            proximoCadastroUsuario = 1;
        }
        else{
            //Abre o arquivo com a unica finalidade de saber qual o ultimo codigo de cliente salvo
            if ((arquivo = fopen(diretorioUsuarios, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
                printf("O arquivo nao pode ser aberto.\n");
                return 1;
            }
            else {        
                while(fscanf(arquivo, "%d;%13[^;];%d;%d\n]\n",&ultimoCadastroUsuario, temp, &c, &c) == 4) {
                    //o que salva em temp ou c é irrelevante, serve apenas para percorrer o arquivo.
                } 
                proximoCadastroUsuario = ultimoCadastroUsuario + 1;            
            }
            fclose(arquivo); //fecha o arquivo
        }

        uTemp->cod = proximoCadastroUsuario;

        system("cls"); //Limpa o prompt de comando
        texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                        CADASTRO DE CLIENTES\n-------------------------------------------------------------------------------------------------------\n"); // titulo do menu inicial
        
        printf("Codigo: %d\n\n", uTemp->cod);
        getchar();

        printf("Usuario: \n");
        fgets(uTemp->user, sizeof(uTemp->user), stdin);
        uTemp->user[strcspn(uTemp->user, "\n")] = '\0';  // remove o \n
        while ((c = getchar()) != '\n'){
            //limpa os caracteres restantes no buffer.
        }

        do {
            printf("Password: minimo 6 e maximo 8 caracteres.\n");
            scanf("%8s", uTemp->password); // limita entrada a 8 caracteres
        } while(strlen(uTemp->password) < 6 || strlen(uTemp->password) > 8);   

        printf("Tipo de Usuario:\n1- Administrador do sistema, 2- Usuario\n");
        while(uTemp->tipo < 1 || uTemp->tipo > 2){
            scanf("%d", &uTemp->tipo);
            getchar();
        }

        printf("\nCodigo: %d\nUsuario: %s\nSenha: %s\nTipo de Usuario: %s\n\n", uTemp->cod, uTemp->user, uTemp->password, tipoUsuario[uTemp->tipo]);

        printf("\nSalvar Usuario?\n0 = Nao / 1 = Sim\n");
        scanf("%d", &seletor); getchar();

        //abre o arquivo para salvar os dados da struct temporaria de Usuarios na ultima linha do arquivo.
        if (seletor == 1){
            if ((arquivo = fopen(diretorioUsuarios, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
            printf("Erro no arquivo Database.\n");
            return 1;
            }
            else {        
                fprintf(arquivo, "%d;%s;%s;%d\n", uTemp->cod, uTemp->user, uTemp->password, uTemp->tipo);   // Recebe um ponteiro para arq, escreve os dados formatados
            }
                
        }        
            fclose(arquivo);
            free(uTemp); //libera a memoria alocada.
    }
}

int cadastroClientes(){
    int c, seletor, ultimoCadastroCliente = 0, proximoCadastroCliente = 0;
    char temp[51];
    cliente *cTemp;
    FILE *arquivo;

    cTemp = malloc(sizeof(cliente));

    if(contarRegistros(diretorioClientes) < 1){
        proximoCadastroCliente = 1;
    }
    else{
        //Abre o arquivo com a unica finalidade de saber qual o ultimo codigo de cliente salvo
        if ((arquivo = fopen(diretorioClientes, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
            printf("O arquivo nao pode ser aberto.\n");
            return 1;
        }
        else {        
            while(fscanf(arquivo, "%d;%50[^;];%50[^;];%11[^;];%80[^;];%20[^;];%20[^\n]\n",&ultimoCadastroCliente, temp, temp, temp, temp, temp, temp) == 7) {
                //o que salva em temp é irrelevante, serve apenas para percorrer o arquivo.
            } 
            proximoCadastroCliente = ultimoCadastroCliente + 1;            
        }
        fclose(arquivo); //fecha o arquivo
    }

    cTemp->cod = proximoCadastroCliente;
    
    system("cls"); //Limpa o prompt de comando
    texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
    printSessao();
    printf("-------------------------------------------------------------------------------------------------------\n                                        CADASTRO DE CLIENTES\n-------------------------------------------------------------------------------------------------------\n"); // titulo do menu inicial
    
    printf("Codigo: %d\n\n", cTemp->cod);
    getchar();

    printf("Digite o Nome: \n");
    fgets(cTemp->nome, sizeof(cTemp->nome), stdin);
    cTemp->nome[strcspn(cTemp->nome, "\n")] = '\0';  // remove o \n
    while ((c = getchar()) != '\n'){
        //limpa os caracteres restantes no buffer.
    }

    printf("Digite o Nome Social: : \n");
    fgets(cTemp->nomeS, sizeof(cTemp->nomeS), stdin);
    cTemp->nomeS[strcspn(cTemp->nomeS, "\n")] = '\0';    
    while ((c = getchar()) != '\n'){
        //limpa os caracteres restantes no buffer.
    }

    printf("Digite o cpf: \n");
    fgets(cTemp->cpf, sizeof(cTemp->cpf), stdin);
    cTemp->cpf[strcspn(cTemp->cpf, "\n")] = '\0';    
    while ((c = getchar()) != '\n'){
        //limpa os caracteres restantes no buffer.
    }

    printf("Digite a Rua e o Numero: \n");
    fgets(cTemp->rua, sizeof(cTemp->rua), stdin);
    cTemp->rua[strcspn(cTemp->rua, "\n")] = '\0';    
    while ((c = getchar()) != '\n'){
        //limpa os caracteres restantes no buffer.
    }

    printf("Digite o Bairro: \n");
    fgets(cTemp->bairro, sizeof(cTemp->bairro), stdin);
    cTemp->bairro[strcspn(cTemp->bairro, "\n")] = '\0';    
    while ((c = getchar()) != '\n'){
        //limpa os caracteres restantes no buffer.
    }

    printf("Digite o Telefone/ WhatsApp: \n");
    fgets(cTemp->tel, sizeof(cTemp->tel), stdin);
    cTemp->tel[strcspn(cTemp->tel, "\n")] = '\0';    
    while ((c = getchar()) != '\n'){
        //limpa os caracteres restantes no buffer.
    }

    printf("\nCodigo: %d\nNome: %s\nNome Social: %s\nCPF: %s\nRua: %s\nBairro: %s\nTelefone/ WhatsApp: %s\n", cTemp->cod, cTemp->nome, cTemp->nomeS, cTemp->cpf, cTemp->rua, cTemp->bairro, cTemp->tel);

    printf("\nSalvar Cliente?\n0 = Nao / 1 = Sim\n");
    scanf("%d", &seletor); getchar();
    
    //abre o arquivo para salvar os dados da struct temporaria de clientes na ultima linha do arquivo.
    if (seletor == 1){
        if ((arquivo = fopen(diretorioClientes, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("Erro no arquivo Database.\n");
        return 1;
        }
        else {        
            fprintf(arquivo, "%d;%s;%s;%s;%s;%s;%s\n", cTemp->cod, cTemp->nome, cTemp->nomeS, cTemp->cpf, cTemp->rua, cTemp->bairro, cTemp->tel);   // Recebe um ponteiro para arq, escreve os dados formatados
        }
            
    }        
        fclose(arquivo);
        free(cTemp); //libera a memoria alocada.
        
}

int cadastroProdutos(){
    int c, seletor = -1, ultimoCadastro = 0, proximoCadastro = 0, tempInt;
    char temp[51];
    float tempF;
    produto *pTemp;
    FILE *arquivo;

    pTemp = malloc(sizeof(produto));

    if(contarRegistros(diretorioProdutos) < 1){
        proximoCadastro = 1000;
    }
    else{
        //Abre o arquivo com a unica finalidade de saber qual o ultimo codigo de cliente salvo
        if ((arquivo = fopen(diretorioProdutos, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
            printf("O arquivo nao pode ser aberto.\n");
            return 1;
        }
        else {        
            while(fscanf(arquivo, "%d;%40[^;];%d;%f;%d;%f;%d;%d\n", &ultimoCadastro, temp, &tempInt, &tempF, &tempInt, &tempF, &tempInt, &tempInt) == 8) {
                //o que salva em temp é irrelevante, serve apenas para percorrer o arquivo.
            }
            proximoCadastro = ultimoCadastro +1;      
        }
        fclose(arquivo); //fecha o arquivo
    }

    pTemp->cod = proximoCadastro;

    system("cls"); //Limpa o prompt de comando
    texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
    printSessao();
    printf("-------------------------------------------------------------------------------------------------------\n                                       CADASTRO DE PRODUTOS\n-------------------------------------------------------------------------------------------------------\n"); // titulo do menu inicial
    
    printf("Codigo: %d\n", pTemp->cod);

    getchar();

    printf("Digite a descricao: \n");
    fgets(pTemp->descricao, sizeof(pTemp->descricao), stdin);
    pTemp->descricao[strcspn(pTemp->descricao, "\n")] = '\0';    
    while ((c = getchar()) != '\n'){
        //limpa os caracteres restantes no buffer.
    }

    printf("Digite a categoria:\n");
    listarCategorias();
    while(seletor < 1 || seletor > quantidadeCategorias){
        scanf("%d", &seletor);
        getchar();
    }
    strcpy(pTemp->categoria, categoria[seletor]);

    printf("\nDigite o preco de Compra: \nR$ "); scanf("%f", &pTemp->precoCompra); getchar();

    printf("\nDigite a margem de Lucro %%: \n"); scanf("%d", &pTemp->margemLucro); getchar();

    pTemp->precoVenda = ((pTemp->precoCompra / 100) * pTemp->margemLucro) + pTemp->precoCompra;

    printf("\nPreco de Venda: R$ %.2f\n", pTemp->precoVenda);

    printf("\nDigite o Estoque: \n"); scanf("%d", &pTemp->estoque); getchar();

    printf("\nDigite o Estoque Minimo: \n"); scanf("%d", &pTemp->estoqueMinimo); getchar();

    system("cls"); //Limpa o prompt de comando
    texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
    printf("-------------------------------------------------------------------------------------------------------\n                                       CADASTRO DE PRODUTOS\n-------------------------------------------------------------------------------------------------------\n"); // titulo do menu inicial
    
    printf("\nCodigo: %d\nDescricao: %s\nCategoria: %s\nPreco de Compra: %.2f\nMargem de Lucro: %d %%\nPreco de Venda: %.2f\nEstoque: %d\nEstoque Minimo: %d\n", pTemp->cod, pTemp->descricao, pTemp->categoria, pTemp->precoCompra,  pTemp->margemLucro,  pTemp->precoVenda,  pTemp->estoque,  pTemp->estoqueMinimo);

    printf("\nSalvar Produto?\n0 = Nao / 1 = Sim\n");
    scanf("%d", &seletor); getchar();
    
    if (seletor == 1){
        if ((arquivo = fopen(diretorioProdutos, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("Erro no arquivo Database.\n");
        return 1;
        }
        else {        
            fprintf(arquivo, "%d;%s;%s;%.2f;%d;%.2f;%d;%d\n", pTemp->cod, pTemp->descricao, pTemp->categoria, pTemp->precoCompra,  pTemp->margemLucro,  pTemp->precoVenda,  pTemp->estoque,  pTemp->estoqueMinimo);   // Recebe um ponteiro para arq, escreve os dados formatados
        }
        fclose(arquivo);
        free(pTemp);

        carregarProdutos();
    }
}

int cadastroCategoria(){
    int c, seletor = -1;
    produto *catTemp;
    FILE *arquivo;

    catTemp = malloc(sizeof(produto));

     //LIMPA BUFFER    
    while ((c = getchar()) != '\n' && c != EOF); 
    
    printf("Digite o nome da nova Categoria:\n");
    fgets(catTemp->categoria, sizeof(catTemp->categoria), stdin);
    catTemp->categoria[strcspn(catTemp->categoria, "\n")] = '\0';    
    

    printf("Categoria: %s\n", catTemp->categoria);

    printf("\nSalvar Categoria?\n0 = Nao / 1 = Sim\n");
    scanf("%d", &seletor); getchar();

    //abre o arquivo para salvar os dados da struct temporaria de Usuarios na ultima linha do arquivo.
    if (seletor == 1){
        if ((arquivo = fopen(diretorioCategorias, "a")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("Erro no arquivo Database.\n");
        return 1;
        }
        else {        
            fprintf(arquivo, "%s\n", catTemp->categoria);   // Recebe um ponteiro para arq, escreve os dados formatados
        }
        fclose(arquivo);          
    }        
}

int novaVenda(){
    int seletor = -1, quantidade = 0, indiceDoRegistro = 0, quantidadeTotalProdutosCarrinho = 0;
    char clienteNome[] = "Nao informado";
    float total = 0;
    
    if(ptrCarrinho == NULL){
        ptrCarrinho = malloc((100 * sizeof(carrinho)) + 1);
    }

    system("cls"); //Limpa o prompt de comando
    texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
    printSessao();
    printf("-------------------------------------------------------------------------------------------------------\n                                              NOVA VENDA\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
    
    printf("Informar Cliente?\n0 = Nao / 1 = Sim\n");
    scanf("%d", &seletor);
    getchar();

    if(seletor == 1) {
        listarClientes();

        printf("Digite o codigo do cliente:\n");
        scanf("%d", &seletor); getchar();

        if(seletor < 1 || seletor > 1 + tamanhoMallocClientes){
            texto(4);
            getchar();
        }
        else{
            for(int i = 0; (ptrClientes + i)->cod <= seletor; i++){
                if((ptrClientes + i)->cod == seletor){
                    indiceDoRegistro = i;
                }                    
            }
            strcpy(clienteNome, (ptrClientes + indiceDoRegistro)->nome);
        }
    }
    
    seletor = -1;
    contadorCarrinho = 0;

    while(seletor != 0){
        system("cls"); //Limpa o prompt de comando
        texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                              NOVA VENDA\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial
        
        listarProdutos(0);
        
        printf("\nDigite o codigo do produto ou 0 para retornar:\n");
        scanf("%d", &seletor); getchar();

        if(seletor != 0){
            printf("Digite a quantidade:\n");
            scanf("%d", &quantidade);
            getchar();
        }
        else{
            break;
        }

        if(seletor < 1000 || seletor > 1000 + tamanhoMallocProdutos){
            texto(4);
            getchar();
        }
        else{            
            addCarrinho(seletor, quantidade);
        }
    }

    for(int i = 0; i < contadorCarrinho; i++){
        quantidadeTotalProdutosCarrinho += (ptrCarrinho + i)->quantidade;
    }

    for(int i = 0; i < contadorCarrinho; i++){
        total += (ptrCarrinho + i)->precoTotal;
    }

    registrarVenda(clienteNome, quantidadeTotalProdutosCarrinho, total, 'a');
    atualizarEstoque();
    contadorCarrinho=0;
    
}

int registrarVenda(char clienteNome[], int quantidade, float valor, char pagamento){
    int ultimoCadastro = 0, proximoCadastro = 0, tempInt;
    float tempFloat;
    char strTemp[51];
    char charTemp;
    FILE *arquivo;

    atualizarData();

    //ultimoCadastro = contarRegistros(diretorioVendas);

    //Abre o arquivo com a unica finalidade de saber qual o ultimo codigo de vendas salvo
    if ((arquivo = fopen(diretorioVendas, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }
    else {        
        while(fscanf(arquivo, "%d;%[^;];%d;%d;%d;%d;%f;%c\n", &ultimoCadastro, strTemp, &tempInt, &tempInt, &tempInt, &tempInt, &tempFloat, &charTemp) == 8) {
            //o que salva em temp é irrelevante, serve apenas para percorrer o arquivo.
        }        
    }
    fclose(arquivo); //fecha o arquivo

    proximoCadastro = ultimoCadastro + 1;

    if ((arquivo = fopen(diretorioVendas, "a")) == NULL) {  //fopen(): nome do arquivo, e modo de abertura
        printf("Erro no arquivo Database.\n");
        return 1;
        }
        else {       
            fprintf(arquivo, "%d;%s;%d;%d;%d;%d;%.2f;%c\n",
                proximoCadastro,
                clienteNome,
                dia,
                mes,
                ano,
                quantidade,
                valor,
                pagamento);// Recebe um ponteiro para arq, escreve os dados formatados
        }
        fclose(arquivo);

        registrarItensVendas(proximoCadastro);
}

void registrarItensVendas(int numVenda){
    FILE *arquivo;
    
    if ((arquivo = fopen(diretorioItensVendas, "a")) == NULL) {  //fopen(): nome do arquivo, e modo de abertura
        printf("Erro no arquivo Database.\n");
        //return 1;
    }
    else {
        for(int i = 0; i < contadorCarrinho; i++){

            fprintf(arquivo, "%d;%d;%s;%.2f;%d;%.2f\n",
                numVenda,
                (ptrCarrinho + i)->cod,
                (ptrCarrinho + i)->descricao,
                (ptrCarrinho + i)->precoUn,
                (ptrCarrinho + i)->quantidade,
                (ptrCarrinho + i)->precoTotal);// Recebe um ponteiro para arq, escreve os dados formatados
        }
    }
    fclose(arquivo);
}

int listarProdutos(int tipoListagem){
    
    //carregarProdutos();

    if(tipoListagem == 0){
        printf("Cod  |  Produto                                   |  Categoria             |  Preco Un    |  Estoque\n-------------------------------------------------------------------------------------------------------\n");
        for(int i=0; i < tamanhoMallocProdutos; i++){
            printf("%-5d| %-40s   | %-20s   | R$ %9.2f |   %5d\n",
            (ptrProdutos + i)->cod,
            (ptrProdutos + i)->descricao,
            (ptrProdutos + i)->categoria,
            (ptrProdutos + i)->precoVenda,
            (ptrProdutos + i)->estoque);
        }
    }
    else if(tipoListagem == 1){
        printf("Cod  | Produto                          |Categoria            | Custo |Margem| Preco |Estoque|Est. Min\n-------------------------------------------------------------------------------------------------------\n");
        for(int i=0; i < tamanhoMallocProdutos; i++){
            printf("%-5d| %-33s| %-20s| %6.2f|%4d%% |%6.2f | %5d | %5d\n",
            (ptrProdutos + i)->cod,
            (ptrProdutos + i)->descricao,
            (ptrProdutos + i)->categoria,
            (ptrProdutos + i)->precoCompra,
            (ptrProdutos + i)->margemLucro,
            (ptrProdutos + i)->precoVenda,
            (ptrProdutos + i)->estoque,
            (ptrProdutos + i)->estoqueMinimo);
        }
    }
    printf("\n-------------------------------------------------------------------------------------------------------\n                                                              Total de Registros encontrados: %6d\n-------------------------------------------------------------------------------------------------------\n", tamanhoMallocProdutos);
}

int listarClientes(){
    
    carregarClientes();
    
    printf("Cod | Cliente                         | CPF        | Endereco               | Bairro      |Tel./ Whats\n-------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < tamanhoMallocClientes; i++){
        printf("%-4d| %-32s| %-10s | %-23s| %-12s|%12s\n",
        (ptrClientes + i)->cod,
        (ptrClientes + i)->nome,
        (ptrClientes + i)->cpf,
        (ptrClientes + i)->rua,
        (ptrClientes + i)->bairro,
        (ptrClientes + i)->tel);
    }
    printf("\n-------------------------------------------------------------------------------------------------------\n                                                              Total de Registros encontrados: %6d\n-------------------------------------------------------------------------------------------------------\n", tamanhoMallocClientes); // titulo do menu inicial
}

int listarVendas(){
    int k=0;
    float valor=0;

    carregarVendas();

    printf("Cod. Venda |           Cliente            |   Dia   |   Mes   |   Ano   | Qtde | Total da Venda |Status\n-------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < tamanhoMallocVendas; i++){
        printf("%-11d| %-29s|  %4d   |  %4d   | %6d  |%5d | R$ %11.2f |%4c\n",
        (ptrVendas + i)->numVenda,
        (ptrVendas + i)->nome,
        (ptrVendas + i)->dia,
        (ptrVendas + i)->mes,
        (ptrVendas + i)->ano,
        (ptrVendas + i)->quantidade,
        (ptrVendas + i)->total,
        (ptrVendas + i)->pagamento);
        k++;
        valor+=(ptrVendas + i)->total;
    }
    printf("\n-------------------------------------------------------------------------------------------------------\na - Aberta  C - Cancelada  f - Finalizada         Registros: %6d  |  Total em Vendas: R$ %10.2f\n-------------------------------------------------------------------------------------------------------\n", k, valor);
}

int listarVendasAbertas(){
    int k=0;
    float valor=0;
    
    carregarVendas();

    printf("Cod. Venda |           Cliente            |   Dia   |   Mes   |   Ano   | Qtde | Total da Venda |Status\n-------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < tamanhoMallocVendas; i++){
        if((ptrVendas + i)->pagamento == 'a'){
            printf("%-11d| %-29s|  %4d   |  %4d   | %6d  |%5d | R$ %11.2f |%4c\n",
            (ptrVendas + i)->numVenda,
            (ptrVendas + i)->nome,
            (ptrVendas + i)->dia,
            (ptrVendas + i)->mes,
            (ptrVendas + i)->ano,
            (ptrVendas + i)->quantidade,
            (ptrVendas + i)->total,
            (ptrVendas + i)->pagamento);
            valor+=(ptrVendas + i)->total;
            k++;
        }
    }
    printf("\n-------------------------------------------------------------------------------------------------------\n                                                  Registros: %6d  |  Total em Vendas: R$ %10.2f\n-------------------------------------------------------------------------------------------------------\n", k, valor);
    if(k > 0){
        return 1;
    }
    else {
        return 0;
    }
}

int listarItensVendas(int numVenda){
    int k=0;
    float valor=0;

    carregarItensVendas();

    printf("Cod. Venda | Cod. Produto |         Descricao         |   Valor Un.   | Quantidade |    Valor Total\n-------------------------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < tamanhoMallocItensVendas; i++){
        
        if((ptrItensVendas + i)->numVenda == numVenda){
            printf("  %-9d|    %-10d| %-26s| R$ %10.2f |  %8d  | R$ %10.2f\n",
            (ptrItensVendas + i)->numVenda,
            (ptrItensVendas + i)->cod,
            (ptrItensVendas + i)->descricao,
            (ptrItensVendas + i)->precoUn,
            (ptrItensVendas + i)->quantidade,
            (ptrItensVendas + i)->precoTotal);
            
            valor += (ptrItensVendas + i)->precoTotal;
            k++;
        }
    }

    printf("\n-------------------------------------------------------------------------------------------------------\n                                     Total de Registros: %6d  |  Total da Vendas: R$ %10.2f\n-------------------------------------------------------------------------------------------------------\n", k, valor);
}

int listarCarrinho(void){
    for(int i = 0; i < contadorCarrinho; i++){
        printf("Contador carrinho: %d - %d  -  %s  -  %d  -  %d  -  %.2f  -  %.2f\n",
            contadorCarrinho,
            (ptrCarrinho + i)->cod,
            (ptrCarrinho + i)->descricao,
            (ptrCarrinho + i)->categoria,
            (ptrCarrinho + i)->quantidade,
            (ptrCarrinho + i)->precoUn,
            (ptrCarrinho + i)->precoTotal);
    }
}

int listarCategorias(){
    
    carregarCategorias();
    
    for(int i = 1; i <= quantidadeCategorias; i++){
        printf("%d  -  %s\n", i, categoria[i]);
    }
}

int listarPagamentos(){
    int k = 0;

    carregarPagamentos();
    
    printf("Cod. Venda |   dia   |   mes   |   ano   | Pago em Dinheiro | Pago em Cartao | Tipo de Pagamento\n-------------------------------------------------------------------------------------------------------\n");
 
    for(int i = 0; i < tamanhoMallocPagamentos; i++){
        printf("  %-8d |   %-4d  |    %-4d |  %-6d | R$ %13.2f | R$ %11.2f |        %s\n",
        (ptrPagamentos + i)->numVenda,
        (ptrPagamentos + i)->dia,
        (ptrPagamentos + i)->mes,
        (ptrPagamentos + i)->ano,
        (ptrPagamentos + i)->dinheiro,
        (ptrPagamentos + i)->cartao,
        (ptrPagamentos + i)->tipoPago);
        k++;
    }
    printf("\n-------------------------------------------------------------------------------------------------------\n                                                                     Total de Registros: %6d\n-------------------------------------------------------------------------------------------------------\n", k);

}

void addCarrinho(int codigo, int quantidade){
    
    for(int i=0; i < tamanhoMallocProdutos; i++){
        if((ptrProdutos + i)->cod == codigo){
            if(quantidade > (ptrProdutos + i)->estoque){
                printf("Estoque insuficiente para a quantidade digitada!\nAperte qualquer tecla para continuar...\n");
                getchar();
            }
            else{
                (ptrProdutos + i)->estoque = (ptrProdutos + i)->estoque - quantidade;

                (ptrCarrinho + contadorCarrinho)->cod = (ptrProdutos + i)->cod;
                strcpy((ptrCarrinho + contadorCarrinho)->descricao, (ptrProdutos + i)->descricao);
                strcpy((ptrCarrinho + contadorCarrinho)->categoria, (ptrProdutos + i)->categoria);
                (ptrCarrinho + contadorCarrinho)->quantidade = quantidade;
                (ptrCarrinho + contadorCarrinho)->precoUn = (ptrProdutos + i)->precoVenda;
                (ptrCarrinho + contadorCarrinho)->precoTotal = ((ptrCarrinho + contadorCarrinho)->precoUn * quantidade);
                contadorCarrinho++;
            }
        }
    }
}

int sangriaCaixa(void){
    
    if (sessao.tipo != 1) {
        printf("Voce precisa estar logado como Administrador pra acessar esta opcao!\n");
        usleep(3000000);
    }
    else{
        float valor;
        
        system("cls"); //Limpa o prompt de comando antes de exibir novas infos
        texto(1);
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("                                    Retirada de Caixa (Sangria)\n");
        printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu Abertura de Caixa
        printf("Digite o valor que retirar do caixa:\nR$ ");
        scanf("%f", &valor); getchar();

        if(valorAberturaCaixa - valor < 50){
            printf("\nO valor e superior ao dinheiro em Caixa ou Sobra menor que R$ 50!\nAperte qualquer tecla para continuar..."); getchar();                
        }
        else{
            valorAberturaCaixa -= valor;
            printf("\nRetirada Concluida!\nAperte qualquer tecla para continuar..."); getchar();  
        }
    }    
}

int pagamento(){
    
    if (listarVendasAbertas() == 0) {
        system("cls"); //Limpa o prompt de comando
        texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                               Pagamento\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu Pagamento
        printf("Nao foram encontradas vendas abertas!\n");
        usleep(3000000);
    }
    else{

        int cancelar = -1, seletor = -1, indiceDoRegistro;        
        int dia, mes, ano, quantidadeProdutos = 0, descontoManual=0, numVenda = 0;
        float subTotal = 0, descontos = 0, total = 0, dinheiro = 0, pagoDinheiro = 0, pix = 0, cartao = 0, saldoDevedor = 0, troco = 0, valorEntrada = 0;
        char clienteNome[] = "Nao informado";

        system("cls");
        texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                           Vendas Abertas\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu Pagamento

        listarVendasAbertas();

        printf("\nDigite o codigo da Venda ou 0 para retornar:\n");
        scanf("%d", &seletor);
        getchar();
        
        while(seletor != 0){
            
            if((ptrVendas + (seletor - 1))->pagamento == 'a'){
                numVenda = seletor;
                strcpy(clienteNome, (ptrVendas + (seletor - 1))->nome);
                dia = (ptrVendas + (seletor - 1))->dia;
                mes = (ptrVendas + (seletor - 1))->mes;
                ano = (ptrVendas + (seletor - 1))->ano;

                carregarItensVendas();

                for(int i = 0; i < tamanhoMallocItensVendas; i++){    
                    if((ptrItensVendas + i)->numVenda == seletor){                        
                        quantidadeProdutos += (ptrItensVendas + i)->quantidade;
                        subTotal += (ptrItensVendas + i)->precoTotal;
                    }
                }

                while (cancelar != 0) {
            
                    descontos = pagoDinheiro * descontoManual / 100;
                    total = subTotal - descontos; //(subTotal * (descontos*100/subTotal) / 100);
                    saldoDevedor = total - (pagoDinheiro + cartao);

                    //pagoDinheiro = pagoDinheiro - descontos; //valor pago em dinheiro pos desconto

                    if (saldoDevedor < 0) { troco = dinheiro - total; saldoDevedor = 0; }

                    system("cls");
                    texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
                    printSessao();
                    printf("-------------------------------------------------------------------------------------------------------\n                                               Pagamento\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu Pagamento
                    printf("Cliente: %-25s | Num. Venda: %-4d |  Data Venda: %d/%d/%d  |  Qtde Produtos: %d\n", clienteNome, numVenda, dia, mes, ano, quantidadeProdutos);
                    printf("-------------------------------------------------------------------------------------------------------\n\n");
                    printf("1. Dinheiro                                         | Sub Total:                           R$ %.2f\n", subTotal);
                    printf("2. Cartao                                           | -------------------------------------------------\n");
                    printf("3. Finalizar a Venda                                | Descontos totais:                    R$ %.2f\n", descontos);
                    printf("4. Cancelar a Venda                                 | =================================================\n");
                    printf("                                                    | Total:                               R$ %.2f\n", total);
                    printf("0. Retornar                                         | =================================================\n");
                    printf("                                                                        Pago em Dinheiro:  R$ %.2f\n", pagoDinheiro);
                    printf("Digite uma opcao do Menu                                                Pago em Cartao:    R$ %.2f\n\n", cartao);
                    printf("                                                                        Dinheiro:          R$ %.2f\n", dinheiro);
                    printf("                                                                        Saldo Devedor:     R$ %.2f\n\n", saldoDevedor);
                    printf("                                                      -------------------------------------------------\n");
                    
                    if(troco > 0){ printf("                                                                          Troco:           R$ %.2f\n", troco); }

                    scanf("%d", &seletor); getchar();
                    
                    switch (seletor) {
                        case 0:
                            cancelar = 0;
                        break;
                        
                        case 1: //Sub menu Pagamento - Opcao 1 Dinheiro
                            
                            if(saldoDevedor <= 0) { printf("Nao possui saldo devedor!\nAperte qualquer tecla para continuar...\n"); getchar(); break; }
                            
                            else {
                                printf("Digite o valor em Dinheiro:\n");
                                scanf("%f", &dinheiro);
                                getchar();

                                if(dinheiro > saldoDevedor){
                                    pagoDinheiro = saldoDevedor;
                                    //troco = dinheiro - pagoDinheiro;
                                }
                                else{
                                    pagoDinheiro = dinheiro;
                                }
                            
                                printf("Digite a (%%) de desconto:\n");
                                scanf("%d", &descontoManual);
                                getchar();
                            }
                            break;

                        case 2: //Sub menu Pagamento - Opcao 2 Cartao
                            
                            if(saldoDevedor <= 0) { printf("Nao possui saldo devedor!\nAperte qualquer tecla para continuar...\n"); getchar(); break; }
                        
                            else {
                                printf("Digite o valor em Cartao:\n");
                                scanf("%f", &valorEntrada); getchar();
                                
                                if(valorEntrada > saldoDevedor){
                                    printf("Tente novamente ou escolha outro método de pagamento\n");
                                    usleep(500000);
                                    break;
                                }
                                else {
                                    printf("Pagamento aprovado?\n0 = Nao / 1 = Sim\n");
                                    scanf("%d", &seletor);
                                    getchar();

                                    if(seletor == 1) {
                                        printf("Pagamento OK\n");                            
                                        cartao = valorEntrada;
                                        usleep(500000);
                                        break;
                                    }
                                    else{
                                        printf("Tente novamente ou escolha outro método de pagamento\n");
                                        usleep(500000);
                                        break;
                                    }
                                }
                            }                        
                            break;

                        case 3: //Sub menu Pagamento - Opcao 3 Finalizar Pedido
                            
                            if (saldoDevedor <= 0) {

                                printf("Tem certeza que deseja Finalizar o Pedido?\n0 = Nao / 1 = Sim\n");
                                scanf("%d", &seletor); getchar();

                                if (seletor == 1){
                                    
                                    if(finalizarVenda(numVenda, total) == 1){
                                        printf("Erro ao finalizar venda!\nAperte qualquer tecla para continuar...\n");
                                        getchar();
                                    }
                                    else{
                                        registrarPagamento(numVenda, pagoDinheiro, cartao);
                                        printf("Finalizada com sucesso!\n");
                                        usleep(1500000);
                                        system("cls");
                                        texto(2);
                                        usleep(2000000);
                                        seletor = 0;
                                        cancelar = 0;
                                        break;
                                    }
                                }

                                else if(seletor == 0) { continue; }
                                else { printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n"); getchar(); }
                            }
                            break;

                        case 4: //Sub menu Pagamento - Opcao 4 Cancelar

                            printf("Tem certeza que deseja Cancelar essa venda?\n0 = Nao / 1 = Sim\n");
                            scanf("%d", &cancelar); getchar();

                            if (cancelar == 1){
                                
                                if(cancelarVenda(numVenda) == 1){
                                    printf("Erro ao cancelar venda!\nAperte qualquer tecla para continuar...\n");
                                    getchar();
                                }
                                else{
                                    printf("Finalizada com sucesso!\n");
                                    usleep(1500000);
                                    usleep(2000000);
                                    cancelar = 0;
                                    break;
                                }
                            }
                            break;
                    
                        default: printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n"); getchar(); break;
                    } 
                }              
            }
            else {
                printf("Opcao Invalida!\n");
                usleep(3000000);
            }              
        }

    }
}

int finalizarVenda(int numVenda, float total){
    FILE *arquivo;

    for(int i=0; i < tamanhoMallocVendas; i++){
        if((ptrVendas + i)->numVenda == numVenda){
            (ptrVendas + i)->total = total;
            (ptrVendas + i)->pagamento = 'f';
        }    
    }

    if ((arquivo = fopen(diretorioVendas, "w")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    } else{
        
        for(int i = 0; i < tamanhoMallocVendas; i++){
            
            fprintf(arquivo, "%d;%s;%d;%d;%d;%d;%.2f;%c\n",
                (ptrVendas + i)->numVenda,
                (ptrVendas + i)->nome,
                (ptrVendas + i)->dia,
                (ptrVendas + i)->mes,
                (ptrVendas + i)->ano,
                (ptrVendas + i)->quantidade,
                (ptrVendas + i)->total,
                (ptrVendas + i)->pagamento);// Recebe um ponteiro para arq, escreve os dados formatados
        }
    }
    fclose(arquivo);
}

int cancelarVenda(int numVenda){
    FILE *arquivo;

    for(int i=0; i < tamanhoMallocVendas; i++){
        if((ptrVendas + i)->numVenda == numVenda){
            (ptrVendas + i)->pagamento = 'c';
        }    
    }

    for(int i=0; i < tamanhoMallocItensVendas; i++){
        if((ptrItensVendas + i)->numVenda == numVenda){
            
            for(int k=0; k < tamanhoMallocProdutos; k++){
                if((ptrProdutos + k)->cod == (ptrItensVendas + i)->cod){
                    (ptrProdutos + k)->estoque += (ptrItensVendas + i)->quantidade;
                    break;
                }
            }
        }    
    }

    atualizarEstoque();

    if ((arquivo = fopen(diretorioVendas, "w")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    } else{
        
        for(int i = 0; i < tamanhoMallocVendas; i++){
            
            fprintf(arquivo, "%d;%s;%d;%d;%d;%d;%.2f;%c\n",
                (ptrVendas + i)->numVenda,
                (ptrVendas + i)->nome,
                (ptrVendas + i)->dia,
                (ptrVendas + i)->mes,
                (ptrVendas + i)->ano,
                (ptrVendas + i)->quantidade,
                (ptrVendas + i)->total,
                (ptrVendas + i)->pagamento);// Recebe um ponteiro para arq, escreve os dados formatados
        }
    }
    fclose(arquivo);
}

int registrarPagamento(int numVenda, float d, float c){    
    char tipoPago[3];
    FILE *arquivo;

    if(d > 0 && c == 0){
        strcpy(tipoPago, "d");
    }
    else if(d == 0 && c > 0){
        strcpy(tipoPago, "c");
    }
    else if(d > c){
        strcpy(tipoPago, "md");
    }
    else if(c > d){
        strcpy(tipoPago, "mc");
    }
    
    if ((arquivo = fopen(diretorioPagamentos, "a")) == NULL) {  //fopen(): nome do arquivo, e modo de abertura
        printf("Erro no arquivo Database.\n");
        return 1;
    }
    else {
        fprintf(arquivo, "%d;%d;%d;%d;%.2f;%.2f;%s\n", numVenda, dia, mes, ano, d, c, tipoPago);// Recebe um ponteiro para arquivo, escreve os dados formatados
    }
    fclose(arquivo);
    
    //Num. Venda , valor pago, tipo (d-Dinheiro, c-Cartão , md – Misto parcial em Dinheiro, md– Misto parcial em Cartão)
}

void relatorioClientes(){
    int seletor = -1;

    while(seletor != 0){
        system("cls");
        texto(1);
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                       RELATORIO DE CLIENTES\n-------------------------------------------------------------------------------------------------------\n\n");
        printf("1 - Listar Clientes (A-z)\n");
        printf("2 - Clientes que compraram (em um determinado periodo)\n\n");
        printf("0 - voltar\n\n");

        scanf("%d", &seletor); 
        getchar();

        switch(seletor){
            case 1 :
                ordenarClientesPorNome();
                listarClientes();
                carregarClientes();
                getchar();
                break;

            case 2:
                clientesQueCompraramNoPeriodo();
                break;

            case 0:
                break;
            
            default:
                printf("Digite uma opcao valida!\n");
                getchar();
        }
    }
}

void ordenarClientesPorNome(){
    cliente temp;

    for(int i = 0; i < tamanhoMallocClientes - 1; i++){
        for(int j = 0; j < tamanhoMallocClientes - i - 1; j++){
            if(strcmp(ptrClientes[j].nome, ptrClientes[j+1].nome) > 0){
                temp = ptrClientes[j];
                ptrClientes[j] = ptrClientes[j+1];
                ptrClientes[j+1]= temp;
            }
        }
    }
}

void clientesQueCompraramNoPeriodo() {
    int diaInicio, mesInicio, anoInicio;
    int diaFim, mesFim, anoFim;

    carregarVendas();

    system("cls");
    texto(1);
    printSessao();

    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                           RELATORIO DE CLIENTES QUE COMPRARAM EM UM PERIODO\n");
    printf("-------------------------------------------------------------------------------------------------------\n\n");

    printf("Digite a data inicio (dd mm aaaa): ");
    scanf("%d %d %d", &diaInicio, &mesInicio, &anoInicio);

    printf("Digite a data final (dd mm aaaa): ");
    scanf("%d %d %d", &diaFim, &mesFim , &anoFim);

    printf("\nClientes que compraram entre %02d/%02d/%04d e %02d/%02d/%04d:\n\n",diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim);

    for(int i = 0; i < tamanhoMallocVendas; i++){
        if (dataDentroDoPeriodo(ptrVendas[i].dia, ptrVendas[i].mes, ptrVendas[i].ano,
                                diaInicio, mesInicio, anoInicio,
                                diaFim, mesFim, anoFim)){
            printf("%s\n", ptrVendas[i].nome);
        }
    }

    printf("\nDigite ENTER pra voltar...");
    getchar();
    getchar();
}

void relatorioProdutos(){
    int seletor = -1;

    while(seletor != 0){
        system("cls");
        texto(1);
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                      RELATORIO DE PRODUTOS\n-------------------------------------------------------------------------------------------------------\n\n");
        printf("1 - Listar Produtos (ordenados de A-z)\n");
        printf("2 - Listar Produtos com Estoque zero ou Minimo(A-z)\n");
        printf("3 - Listar Produtos mais Vendidos (em um determinado periodo)\n\n");
        printf("0 - voltar\n\n");

        scanf("%d", &seletor);
        getchar();

        switch(seletor){

            case 1:
                ordenarProdutosPorDescricao(); 
                listarProdutos(1);
                carregarProdutos();
                getchar();
                break;

            case 2:
                listarProdutosComEstoqueCritico();
                getchar();
                break;

            case 3:
                listarProdutosMaisVendidosPeriodo();
                getchar();
                break;

            case 0:
                break;

            default:
                printf("Digite uma opcao valida!\n");
                getchar();
        }
    }
}

void ordenarProdutosPorDescricao(){
    produto temp;
    for (int i = 0; i < tamanhoMallocProdutos - 1; i++){
        for (int j = 0; j < tamanhoMallocProdutos - i - 1; j++){
            if (strcmp(ptrProdutos[j].descricao, ptrProdutos[j+1].descricao) > 0){
                temp = ptrProdutos[j];
                ptrProdutos[j] = ptrProdutos[j+1];
                ptrProdutos[j+1] = temp;
            }
        }
    }
}

void ordenarProdutosComEstoqueCritico(){
    produto temp;
    for (int i = 0; i < tamanhoMallocProdutos - 1; i++){
        for (int j = 0; j < tamanhoMallocProdutos - i - 1; j++){
            if (ptrProdutos[j].estoque > ptrProdutos[j+1].estoque){
                temp = ptrProdutos[j];
                ptrProdutos[j] = ptrProdutos[j+1];
                ptrProdutos[j+1] = temp;
            }
        }
    }
}

void listarProdutosComEstoqueCritico(){
    ordenarProdutosComEstoqueCritico();

    printf("Produtos com Estoque zero ou Minimo:\n\n");
    for (int i = 0; i < tamanhoMallocProdutos; i++) {
        if ((ptrProdutos + i)->estoque <= (ptrProdutos + i)->estoqueMinimo){

            printf("Codigo: %d\n", (ptrProdutos + i)->cod);
            printf("Descricao: %s\n", (ptrProdutos + i)->descricao);
            printf("Estoque Atual: %d\n", (ptrProdutos + i)->estoque);
            printf("Estoque Minimo: %d\n", (ptrProdutos + i)->estoqueMinimo);
            printf("---------------------------------------\n");
        }
    }

    printf("Aperte ENTER para continuar...");
    getchar();
}

void listarProdutosMaisVendidosPeriodo(){
    int diaInicio, mesInicio, anoInicio;
    int diaFim, mesFim, anoFim;

    carregarProdutos();
    carregarVendas();
    carregarItensVendas();

    printf("Data inicial (dd mm aaaa): ");
    scanf("%d %d %d", &diaInicio, &mesInicio, &anoInicio);
    printf("Data final (dd mm aaaa): ");
    scanf("%d %d %d", &diaFim, &mesFim, &anoFim);

    int totalVendidos[tamanhoMallocProdutos];
    for(int i = 0; i < tamanhoMallocProdutos; i++)
        totalVendidos[i] = 0;

    for(int i = 0; i < tamanhoMallocItensVendas; i++){
        int numVenda = ptrItensVendas[i].numVenda;
        int idxVenda = -1;
        for(int j = 0; j < tamanhoMallocVendas; j++){
            if(ptrVendas[j].numVenda == numVenda){
                idxVenda = j;
                break;
            }
        }
        if(idxVenda == -1) continue;

        if (dataDentroDoPeriodo(ptrVendas[idxVenda].dia, ptrVendas[idxVenda].mes, ptrVendas[idxVenda].ano,
                                diaInicio, mesInicio, anoInicio,
                                diaFim, mesFim, anoFim)){
            int codP = ptrItensVendas[i].cod;
            for(int k = 0; k < tamanhoMallocProdutos; k++){
                if(ptrProdutos[k].cod == codP){
                    totalVendidos[k] += ptrItensVendas[i].quantidade;
                    break;
                }
            }
        }
    }

    printf("\n---- Produtos mais vendidos no período %02d/%02d/%04d a %02d/%02d/%04d ----\n",
           diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim);

    for(int i = 0; i < tamanhoMallocProdutos; i++){
        printf("Produto %d (%s): %d unidades vendidas\n",
               ptrProdutos[i].cod, ptrProdutos[i].descricao, totalVendidos[i]);
    }
}

void relatorioVendas(){
    int seletor = -1;

    while(seletor != 0){
        system("cls");
        texto(1);
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                          RELATORIO DE VENDAS\n-------------------------------------------------------------------------------------------------------\n\n");
        printf("1 - Listar todas as vendas\n");
        printf("2 - Listar vendas por periodo\n");
        printf("3 - Faturamento consolidado (dinheiro e cartao)\n\n");
        printf("0 - Voltar\n\n");
        
        scanf("%d", &seletor);
        getchar();

        switch(seletor){
            case 1:
                listarVendas();

                printf("\nDigite o codigo da Venda ou 0 para retornar:\n");
                scanf("%d", &seletor);
                getchar();

                while(seletor != 0){
                    system("cls");
                    texto(1);
                    printSessao();
                    printf("-------------------------------------------------------------------------------------------------------\n                                          RELATORIO DE VENDAS\n-------------------------------------------------------------------------------------------------------\n\n");

                    listarItensVendas(seletor);

                    printf("\nDigite 0 para retornar:\n");
                    scanf("%d", &seletor);
                    getchar();
                }
                break;

            case 2:
                listarVendasPorPeriodo();
                break;

            case 3:
                faturamentoConsolidadoPorPeriodo();
                break;

            case 0:
                break;

            default:
                printf("Digite uma opcao valida!\n");
                getchar();
        }

    }
}

void listarVendasPorPeriodo(){
    int diaInicio, mesInicio, anoInicio;
    int diaFim, mesFim, anoFim;

    carregarVendas();

    printf("Digite a data inicial (dd mm aaaa): ");
    scanf("%d %d %d", &diaInicio, &mesInicio, &anoInicio);

    printf("Digite a data final (dd mm aaaa): ");
    scanf("%d %d %d", &diaFim, &mesFim, &anoFim);

    system("cls");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                                     RELATORIO DE VENDAS POR PERIODO\n");
    printf("-------------------------------------------------------------------------------------------------------\n");

    printf("Cod. Venda |           Cliente            |   Dia   |   Mes   |   Ano   | Qtde | Total da Venda |Status\n-------------------------------------------------------------------------------------------------------\n");
   
    for (int i = 0; i < tamanhoMallocVendas; i++) {
        vendas v = ptrVendas[i];

        if (dataDentroDoPeriodo(v.dia, v.mes, v.ano, diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim)) {
            printf("%-11d| %-29s|  %4d   |  %4d   | %6d  |%5d | R$ %11.2f |%4c\n", v.numVenda, v.nome, v.dia, v.mes, v.ano, v.quantidade, v.total, v.pagamento);
        }
    }
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void faturamentoConsolidadoPorPeriodo() {
    int diaInicio, mesInicio, anoInicio;
    int diaFim, mesFim, anoFim;

    float totalDinheiro = 0;
    float totalCartao = 0;

    carregarVendas();

    printf("Digite a data inicial (dd mm aaaa): ");
    scanf("%d %d %d", &diaInicio, &mesInicio, &anoInicio);

    printf("Digite a data final (dd mm aaaa): ");
    scanf("%d %d %d", &diaFim, &mesFim, &anoFim);

    system("cls");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                     FATURAMENTO CONSOLIDADO POR PERIODO\n");
    printf("-------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < tamanhoMallocVendas; i++) {
        vendas v = ptrVendas[i];

        if (dataDentroDoPeriodo(v.dia, v.mes, v.ano,
                                diaInicio, mesInicio, anoInicio,
                                diaFim, mesFim, anoFim)) {
            totalDinheiro += v.total;
        }
    }

    printf("Total recebido em DINHEIRO: R$ %.2f\n", totalDinheiro);
    printf("Total recebido em CARTAO:   R$ %.2f\n", totalCartao);
    printf("Total GERAL:                R$ %.2f\n", totalDinheiro + totalCartao);

    printf("\nPressione Enter para continuar...");
    getchar(); getchar();
}

int dataDentroDoPeriodo(int d, int m, int a,int di, int mi, int ai, int df, int mf, int af) {
    
    if (a < ai) return 0;
    if (a == ai && m < mi) return 0;
    if (a == ai && m == mi && d < di) return 0;

    if (a > af) return 0;
    if (a == af && m > mf) return 0;
    if (a == af && m == mf && d > df) return 0;

    return 1;
}

void relatorioPagamentos(){
    int seletor = -1;

    while(seletor != 0){
        system("cls"); //Limpa o prompt de comando
        texto(1); //Chama a função para imprimir o cabeçalho com bem vindo
        printSessao();
        printf("-------------------------------------------------------------------------------------------------------\n                                      RELATORIO PAGAMENTOS\n-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu inicial

        listarPagamentos();

        printf("\nDigite 0 para retornar:\n");
        scanf("%d", &seletor);
        getchar();        
    }
}

int carregarClientes(){
    int i = 0;
    FILE *arquivo;

    tamanhoMallocClientes = contarRegistros(diretorioClientes);

    ptrClientes = malloc((tamanhoMallocClientes + 1) * sizeof(cliente));

    if ((arquivo = fopen(diretorioClientes, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }

    else {
        while(fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
        &(ptrClientes + i)->cod,
        (ptrClientes + i)->nome,
        (ptrClientes + i)->nomeS,
        (ptrClientes + i)->cpf,
        (ptrClientes + i)->rua,
        (ptrClientes + i)->bairro,
        (ptrClientes + i)->tel) == 7) { 
        i++;
        }
    }
    fclose(arquivo); //fecha o arquivo
}

int carregarProdutos(){
    int i = 0;
    FILE *arquivo;

    tamanhoMallocProdutos = contarRegistros(diretorioProdutos);

    ptrProdutos = malloc((tamanhoMallocProdutos + 1) * sizeof(produto));

    if ((arquivo = fopen(diretorioProdutos, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }

    else {
        while(fscanf(arquivo, "%d;%[^;];%[^;];%f;%d;%f;%d;%d\n",
        &(ptrProdutos + i)->cod,
        (ptrProdutos + i)->descricao,
        (ptrProdutos + i)->categoria,
        &(ptrProdutos + i)->precoCompra,
        &(ptrProdutos + i)->margemLucro,
        &(ptrProdutos + i)->precoVenda,
        &(ptrProdutos + i)->estoque,
        &(ptrProdutos + i)->estoqueMinimo) == 8) { 
        i++;
        }
    }
    fclose(arquivo); //fecha o arquivo
}

int carregarItensVendas(){
    int i = 0;
    FILE *arquivo;

    tamanhoMallocItensVendas = contarRegistros(diretorioItensVendas);

    ptrItensVendas = malloc((tamanhoMallocItensVendas + 1) * sizeof(itensVendas));

    if ((arquivo = fopen(diretorioItensVendas, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }

    else {
        while(fscanf(arquivo, "%d;%d;%[^;];%f;%d;%f\n",
        &(ptrItensVendas + i)->numVenda,
        &(ptrItensVendas + i)->cod,
        (ptrItensVendas + i)->descricao,
        &(ptrItensVendas + i)->precoUn,
        &(ptrItensVendas + i)->quantidade,
        &(ptrItensVendas + i)->precoTotal) == 6) { 
        i++;

        }
    }
    fclose(arquivo); //fecha o arquivo


}

int carregarCategorias(){
    int i = 1;
    FILE *arquivo;

    if ((arquivo = fopen(diretorioCategorias, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }

    else {
        while(fscanf(arquivo, "%s\n",
        categoria[i]) == 1) { 
        i++;
        }
    }
    fclose(arquivo); //fecha o arquivo
    quantidadeCategorias = i - 1;
}

int carregarVendas(){
    int i = 0;
    FILE *arquivo;

    tamanhoMallocVendas = contarRegistros(diretorioVendas);

    ptrVendas = malloc((tamanhoMallocVendas + 1) * sizeof(vendas));

    if ((arquivo = fopen(diretorioVendas, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }

    else {
        while(fscanf(arquivo, "%d;%[^;];%d;%d;%d;%d;%f;%c\n",
        &(ptrVendas + i)->numVenda,
        (ptrVendas + i)->nome,
        &(ptrVendas + i)->dia,
        &(ptrVendas + i)->mes,
        &(ptrVendas + i)->ano,
        &(ptrVendas + i)->quantidade,
        &(ptrVendas + i)->total,
        &(ptrVendas + i)->pagamento) == 8) { 
        i++;
        }
    }
    fclose(arquivo); //fecha o arquivo
}

int carregarPagamentos(){
    int i = 0;
    FILE *arquivo;

    tamanhoMallocPagamentos = contarRegistros(diretorioPagamentos);

    ptrPagamentos = malloc((tamanhoMallocPagamentos + 1) * sizeof(pagamentos));

    if ((arquivo = fopen(diretorioPagamentos, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }

    else {
        while(fscanf(arquivo, "%d;%d;%d;%d;%f;%f;%s\n",
        &(ptrPagamentos + i)->numVenda,
        &(ptrPagamentos + i)->dia,
        &(ptrPagamentos + i)->mes,
        &(ptrPagamentos + i)->ano,
        &(ptrPagamentos + i)->dinheiro,
        &(ptrPagamentos + i)->cartao,
        (ptrPagamentos + i)->tipoPago) == 7) { 
        i++;
        }
    }
    fclose(arquivo); //fecha o arquivo
}

int atualizarEstoque(){
    FILE *arquivo;

    if ((arquivo = fopen(diretorioProdutos, "w")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    } else{
        
        for(int i = 0; i < tamanhoMallocProdutos; i++){
            fprintf(arquivo, "%d;%s;%s;%.2f;%d;%.2f;%d;%d\n", (ptrProdutos + i)->cod, (ptrProdutos + i)->descricao, (ptrProdutos + i)->categoria, (ptrProdutos + i)->precoCompra,  (ptrProdutos + i)->margemLucro,  (ptrProdutos + i)->precoVenda,  (ptrProdutos + i)->estoque,  (ptrProdutos + i)->estoqueMinimo);
        }
    }
    fclose(arquivo);
}

int contarRegistros(char *endereco){
    int i=0;
    char linha[200];
    FILE *arquivo;

    if ((arquivo = fopen(endereco, "r")) == NULL) {  // fopen(): nome do arquivo, e modo de abertura
        printf("O arquivo nao pode ser aberto.\n");
        return 1;
    }
    else {
        while(fgets(linha, sizeof(linha), arquivo) != NULL) { 
        i++;
        }
    }
    fclose(arquivo); //fecha o arquivo
    return i;
}

void aberturaCaixa(){
    int seletor = 0;

    if (sessao.tipo != 1) {
        printf("Voce precisa estar logado como Administrador pra acessar esta opcao!\n");
        
        printf("Deseja logar?\n0 = Nao / 1 = Sim\n");
                
        scanf("%d", &seletor);
        getchar();

        if(seletor == 1){
            sessao.sessaoAtiva = 0;
            iniciarSessao();
        }
        
    }
    else{
        if(estadoCaixa == 1) {
            system("cls"); //Limpa o prompt de comando antes de exibir novas infos
            texto(1);
            printSessao();
            
            printf("-------------------------------------------------------------------------------------------------------\n");
            printf("                                           Abertura de Caixa\n");
            printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu Abertura de Caixa
            printf("O caixa ja esta aberto!              Valor de Abertura: R$ %.2f\nAperte qualquer tecla para continuar...", valorAberturaCaixa);
            getchar();
            getchar();
        }                
        else {                    
            system("cls"); //Limpa o prompt de comando antes de exibir novas infos
            texto(1);
            printSessao();              
            printf("-------------------------------------------------------------------------------------------------------\n");
            printf("                                           Abertura de Caixa\n");
            printf("-------------------------------------------------------------------------------------------------------\n"); // titulo do menu Abertura de Caixa
            printf("Digite o valor que deseja abrir o caixa:\nR$ ");
            scanf("%f", &valorAberturaCaixa);
            getchar();

            /*
            printf("\nVoce precisa definir o estoque do dia para Padaria!\n\n");

            for(int i = 31; i <= 37; i++){
                printf("%d. %s - Digite a quantidade: ", i, produtos[i]);
                scanf("%d", &quantidade); getchar();
                estoque[i] = quantidade;
            }
            */

            printf("\nAbertura Concluida!\nAperte qualquer tecla para continuar..."); getchar();
            estadoCaixa = 1;
        }
    }
}

void fechamentoCaixa(){
    
    if (sessao.tipo != 1) {
        printf("Voce precisa estar logado como Administrador pra acessar esta opcao!\n");
        usleep(3000000);
    }
    else{
        int seletor = -1;

        while(seletor != 0){

            if(estadoCaixa == 0){ texto(3); getchar(); break; }
                            
            else {
                
                float pagoDinheiro = 0;
                float pagoCartao = 0;
                float mistoDinheiro = 0;
                float mistoCartao = 0;
                float vendasAbertas = 0;
                float faturamentoTotal = 0;

                carregarVendas();
                carregarPagamentos();

                for(int i = 0; i < tamanhoMallocVendas; i++){
                    if((ptrVendas + i)->dia == dia){
                        
                        if((ptrVendas + i)->pagamento == 'f' || (ptrVendas + i)->pagamento == 'a'){
                            quantidadeVendas++;
                            faturamentoTotal += (ptrVendas + i)->total;
                            quantidadeProdutosDia += (ptrVendas + i)->quantidade;
                        }
                        
                        if((ptrVendas + i)->pagamento == 'a'){
                            vendasAbertas += (ptrVendas + i)->total;
                        }
                    }
                }

                for(int i = 0; i < tamanhoMallocPagamentos; i++){
                    if((ptrPagamentos + i)->dia == dia && (ptrPagamentos + i)->mes == mes && (ptrPagamentos + i)->ano == ano){
                        if(strcmp((ptrPagamentos + i)->tipoPago, "d") == 0){
                            pagoDinheiro += (ptrPagamentos + i)->dinheiro;
                        }
                        else if(strcmp((ptrPagamentos + i)->tipoPago, "c") == 0){
                            pagoCartao += (ptrPagamentos + i)->cartao;
                        }
                        else if(strcmp((ptrPagamentos + i)->tipoPago, "md") == 0){
                            mistoDinheiro += (ptrPagamentos + i)->dinheiro + (ptrPagamentos + i)->cartao;
                            pagoDinheiro += (ptrPagamentos + i)->dinheiro;
                            pagoCartao += (ptrPagamentos + i)->cartao;
                        }
                        else if(strcmp((ptrPagamentos + i)->tipoPago, "mc") == 0){
                            mistoCartao += (ptrPagamentos + i)->dinheiro + (ptrPagamentos + i)->cartao;
                            pagoDinheiro += (ptrPagamentos + i)->dinheiro;
                            pagoCartao += (ptrPagamentos + i)->cartao;
                        }
                    } 
                }
                
                system("cls"); //Limpa o prompt de comando antes de exibir novas infos
                texto(1);
                printSessao();                  
                printf("-------------------------------------------------------------------------------------------------------\n");
                printf("                                         Fechamento de Caixa\n");
                printf("-------------------------------------------------------------------------------------------------------\n\n"); // titulo do menu Fechamento de Caixa
                printf("Valor de Abertura:          R$ %.2f                                  Dinheiro em Caixa:  R$ %.2f\n", valorAberturaCaixa, (pagoDinheiro + valorAberturaCaixa));
                printf("Valor em Vendas Total:      R$ %.2f\n", faturamentoTotal);
                printf("Valor em Vendas a Receber:  R$ %.2f\n\n", vendasAbertas);
                printf("Vendas realizadas no dia: %d\n", quantidadeVendas);
                printf("Produtos vendidos no dia: %d\n\n", quantidadeProdutosDia);                 
                printf("-------------------------------------------------------------------------------------------------------\n");
                printf("                                               Entradas\n");
                printf("-------------------------------------------------------------------------------------------------------\n\n");
                printf("Valor Pago em Dinheiro (d):     R$ %.2f\n", pagoDinheiro);
                printf("Valor Pago em Cartao (c):       R$ %.2f\n", pagoCartao);
                printf("Pagamento misto Dinheiro (md):  R$ %.2f\n", mistoDinheiro);
                printf("Pagamento misto Cartao (mc):    R$ %.2f\n\n", mistoCartao);
                printf("Deseja Fechar o Caixa?\n0 = Nao / 1 = Sim\n");
                
                scanf("%d", &seletor);
                getchar();

                if(seletor == 1){
                    //zerarCarrinho();
                    valorAberturaCaixa = 0;
                    faturamentoTotal = 0;
                    quantidadeVendas = 0;
                    quantidadeProdutosDia = 0;
                    estadoCaixa = 0;
                    printf("\nFechamento Concluido!\nAperte qualquer tecla para continuar..."); getchar();
                    break;
                }
            }
        }
    }
}

void printSessao(void){
    printf("Data: %d/%d/%-30d Sessao: %-24s  |  Usuario: %-14s\n", dia, mes, ano, tipoUsuario[sessao.tipo], sessao.user);
}

void atualizarData(void){
    // Variável para armazenar o tempo atual
    time_t segundos;

    // Variável para armazenar a estrutura de tempo local
    struct tm *data_hora_atual;

    // Obtém o tempo em segundos desde a época (epoch)
    time(&segundos);

    // Converte o tempo em segundos para a estrutura de tempo local
    data_hora_atual = localtime(&segundos);

    // Acessa os membros da struct tm
    // tm_mday: dia do mês (1 a 31)
    // tm_mon: mês do ano (0 a 11, onde 0 = Janeiro)
    // tm_year: anos desde 1900
    dia = (data_hora_atual->tm_mday);
    mes = (data_hora_atual->tm_mon + 1); // Adiciona 1 pois o mês começa em 0
    ano = (data_hora_atual->tm_year + 1900); // Adiciona 1900 pois o ano é contado a partir de 1900
}

//Função com as impressões e textos, chamados via passagem de valor dentro de parenteses.
void texto(int t){
    
    switch (t) {
        case 1: //Print: Bem vindo
            printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
            printf("@                                                                                                     @\n");
            printf("@                     Sistema de gestao 4.0                                                           @\n");
            printf("@                                                                                                     @\n");
            printf("@                      @@@@@  @@@@@@    @@@@@      @@@@@   @@@@@  @@@@@   @@@@@                       @\n");
            printf("@                     @@        @@     @@          @@  @@  @@     @@  @@  @@                          @\n");
            printf("@                      @@@@     @@      @@@@       @@ @@   @@@@@  @@@@@   @@@@@                       @\n");
            printf("@                         @@    @@         @@      @@  @@  @@     @@  @   @@                          @\n");
            printf("@                     @@@@@   @@@@@@   @@@@@       @@@@@   @@@@@  @@   @  @@@@@                       @\n");
            printf("@                                                                                                     @\n");
            printf("@                                                                                                     @\n");
            printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
            break;        
        case 2: //Print: Volte Sempre
            printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
            usleep(100000);
            printf("@                                                                                                     @\n");
            usleep(100000);
            printf("@    Sistema de gestao 4.0                                                                            @\n");
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
            printf("@                                                                                                     @\n");
            usleep(100000);
            printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
            usleep(100000);
            break;
        case 3:
            printf("Voce precisa abrir o caixa primeiro!\nAperte qualquer tecla para continuar...\n");
            break;
        case 4:
            printf("Opcao invalida!\nAperte qualquer tecla para continuar...\n");
            break;
    }    
}
