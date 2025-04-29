#include <stdio.h>
#include <string.h>

#define CARRINHO_MAX 100 // Criando constantes
#define ITEM_TAMANHO 100

int main(void) {
    FILE *pont_arq;
    int categoria, tipo, numero, opcao, continuar = 1;
    
    char nome[30], cpf[12], cep[10], cidade[40], logradouro[40], complemento[40], pagamento[10];

    // Menu principal
    char *menu[] = {
        "Pizzas Tradicionais",
        "Pizzas Doces",
        "Bebidas",
        "Sobremesas"
    };
    
    int total_menu = sizeof(menu) / sizeof(menu[0]); // Obtendo o tamanho do array

    // Submenus de produtos
    char *pizzas_trad[] = {
        "Pizza de Calabresa",
        "Pizza de Mussarela",
        "Pizza de Frango",
        "Pizza Portuguesa",
        "Pizza Marguerita",
        "Pizza Napolitana"
    };
    
    char *pizzas_doces[] = {
        "Pizza de Chocolate",
        "Pizza Prestígio",
        "Pizza Romeu e Julieta",
        "Pizza de Brigadeiro"
    };
    
    char *bebidas[] = {
        "Coca-Cola",
        "Fanta",
        "Pepsi Twist",
        "Água",
        "H2OH",
        "Suco de Uva"
    };
    
    char *sobremesas[] = {
        "Petit Gateau",
        "Napolitano",
        "Brownie",
        "Açaí"
    };

    int total_trad = sizeof(pizzas_trad) / sizeof(pizzas_trad[0]);
    int total_doces = sizeof(pizzas_doces) / sizeof(pizzas_doces[0]);
    int total_bebidas = sizeof(bebidas) / sizeof(bebidas[0]);
    int total_sobremesas = sizeof(sobremesas) / sizeof(sobremesas[0]);

    // Arrays de preços correspondentes a cada categoria
    float preco_pizzas_trad[] = { 
        50.00, // Valor da Pizza de Calabresa
        50.00, // Valor da Pizza de Mussarela 
        50.00, // Valor da Pizza de Frango
        50.00, // Valor da Pizza Portuguesa
        50.00,  // Valor da Pizza Marguerita
        50.00  // Valor da Pizza Napolitana
    };
    
    float preco_pizzas_doces[] = { 
        50.00, // Valor da Pizza de Chocolate
        55.00, // Valor da Pizza Prestígio
        55.00, // Valor da Pizza Romeu e Julieta
        50.00 // Valor da Pizza Brigadeiro
    };
    
    float preco_bebidas[] = {
        9.00, // Valor da Coca-Cola
        8.00, // Valor da Fanta
        9.00, // Valor da Pepsi Twist
        3.00, // Valor da Água
        4.00, // Valor da H20H
        5.00 // Valor do Suco de Uva
    };
    
    float preco_sobremesas[] = {
        15.00, // Valor do Petit Gateau
        20.00, // Valor do Napolitano
        10.00, // Valor do Brownie
        12.00 // Valor do Açaí
    };

    // Carrinho para armazenar os itens escolhidos (descrição com preço)
    char carrinho[CARRINHO_MAX][ITEM_TAMANHO];
    // Array para armazenar os preços correspondentes a cada item do carrinho
    float carrinhoPrecos[CARRINHO_MAX];
    int countCarrinho = 0;

    printf("Bem-Vindo(a) à PizzaControl! \n");
    printf("Deseja comer no restaurante ou que o pedido seja entregue? (1-Entrega / 0-Restaurante): ");
    scanf("%d", &tipo);
    getchar(); // Limpa o espaço (\n) do buffer

    // Processa os dados do cliente conforme o tipo de pedido
    switch (tipo) {
        case 0:
            printf("\nOpção escolhida: Comer no restaurante\n");
            printf("Digite seu nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite seu CPF (apenas números): ");
            scanf("%s", cpf);

            pont_arq = fopen("pedidos.txt", "a");
            if (pont_arq == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }
            fprintf(pont_arq, "\nOpção: Comer no Restaurante \nCliente: %s \nCPF: %s\n", nome, cpf);
            fclose(pont_arq);
            break;
        case 1:
            printf("\nOpção escolhida: Pedido para Entrega\n");
            printf("Digite seu nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite seu CPF (apenas números): ");
            scanf("%s", cpf);

            printf("Digite seu CEP: ");
            scanf("%s", cep);

            printf("Digite sua Cidade: ");
            scanf("%s", cidade);

            printf("Digite o Logradouro: ");
            scanf("%s", logradouro);

            printf("Número da Residência: ");
            scanf("%d", &numero);

            printf("Digite o Complemento: ");
            scanf("%s", complemento);

            pont_arq = fopen("pedidos.txt", "a");
            if (pont_arq == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }
            fprintf(pont_arq,
                    "\nOpção: Pedido para Entrega \nCliente: %s \nCPF: %s \nCEP: %s \nCidade: %s \nLogradouro: %s \nNúmero: %d \nComplemento: %s \n",
                    nome, cpf, cep, cidade, logradouro, numero, complemento);
            fclose(pont_arq);
            break;
        default:
            printf("Opção inválida!\n");
            return 1;
    }

    // Loop principal para os pedidos
    while (continuar) {
        printf("\nEscolha uma categoria:\n");
        for (int i = 0; i < total_menu; i++) {
            printf("%d - %s\n", i + 1, menu[i]);
        }
        printf("Digite o número da categoria desejada: ");
        scanf("%d", &categoria);
        if (categoria < 1 || categoria > total_menu) {
            printf("Categoria inválida!\n");
            continue;
        }

        // Seleciona o array de produtos e preços conforme a categoria escolhida
        char **sabores;
        float *precos;
        int total_sabores;

        switch (categoria) {
            case 1:
                sabores = pizzas_trad;
                precos = preco_pizzas_trad;
                total_sabores = total_trad;
                break;
            case 2:
                sabores = pizzas_doces;
                precos = preco_pizzas_doces;
                total_sabores = total_doces;
                break;
            case 3:
                sabores = bebidas;
                precos = preco_bebidas;
                total_sabores = total_bebidas;
                break;
            case 4:
                sabores = sobremesas;
                precos = preco_sobremesas;
                total_sabores = total_sobremesas;
                break;
        }

        printf("\nVocê escolheu: %s\n", menu[categoria - 1]);
        printf("Escolha um item:\n");
        for (int i = 0; i < total_sabores; i++) {
            printf("%d - %s - R$%.2f\n", i + 1, sabores[i], precos[i]);
        }
        printf("Digite o número do item desejado: ");
        scanf("%d", &opcao);
        if (opcao < 1 || opcao > total_sabores) {
            printf("Opção inválida!\n");
            continue;
        }

        // Grava o item escolhido no arquivo
        pont_arq = fopen("pedidos.txt", "a");
        if (pont_arq == NULL) {
            printf("Não foi possível abrir o arquivo!\n");
            return 1;
        }
        
        fprintf(pont_arq, "Categoria: %s \nItem: %s - R$%.2f\n",
                menu[categoria - 1], sabores[opcao - 1], precos[opcao - 1]);
        fclose(pont_arq);

        // Adiciona o item com preço ao carrinho
        char Descricao[ITEM_TAMANHO];
        snprintf(Descricao, sizeof(Descricao), "%s - %s - R$%.2f",
                 menu[categoria - 1], sabores[opcao - 1], precos[opcao - 1]);
        strcpy(carrinho[countCarrinho], Descricao);
        
        // Armazena o preço no array já declarado no início
        carrinhoPrecos[countCarrinho] = precos[opcao - 1];
        countCarrinho++;

        printf("\nProduto adicionado ao carrinho! \nItem: %s \nPreço: R$%.2f\n", sabores[opcao - 1], precos[opcao - 1]);

        // Pergunta se o usuário deseja visualizar os itens do carrinho
        int verCarrinho;
        
        do {
            printf("\nDeseja visualizar os itens do carrinho? (1-Sim / 0-Não): ");
            scanf("%d", &verCarrinho);
        } while (verCarrinho != 1 && verCarrinho != 0);
        
        if (verCarrinho == 1) {
            if (countCarrinho > 0) {
                printf("\n%s, seu pedido contém:\n", nome);
                for (int i = 0; i < countCarrinho; i++) {
                    printf("%d - %s\n", i + 1, carrinho[i]);
                }
            } else {
                printf("\nCarrinho vazio!\n");
            }
        }
        
        do { // Looping para não permitir respostas além de Sim ou Não
            printf("\nDeseja adicionar mais pedidos ao carrinho? (1-Sim / 0-Não): ");
            scanf("%d", &continuar);
        } while (continuar != 1 && continuar != 0);
    }
    
    // Quando o usuário finalizar, exibimos o resumo do pedido com os itens e o total
    if (continuar == 0) {
        printf("\nResumo do pedido:\n");
        if (countCarrinho > 0) {
            float totalFinal = 0.0;
            printf("\nItens do Carrinho:\n");
            for (int i = 0; i < countCarrinho; i++) {
                printf("%d - %s\n", i + 1, carrinho[i]);
                totalFinal += carrinhoPrecos[i];
            }
            printf("\nTotal do pedido: R$%.2f\n", totalFinal);
        } else {
            printf("\nCarrinho vazio!\n");
        }
        
        printf("\nComo deseja realizar o pagamento? ");
        scanf("%s", pagamento);
        
        // Reabre o arquivo para acrescentar a forma de pagamento
        pont_arq = fopen("pedidos.txt", "a");
        if (pont_arq == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 1;
        }
        
        fprintf(pont_arq, "Forma de pagamento: %s", pagamento);
        fclose(pont_arq);
    }
    
    printf("\nPedido registrado. Obrigado por comprar na PizzaControl!\n");
    return 0;
}