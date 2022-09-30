#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
struct Produto{
    int cod;
    char descricao[50];
    float preco;
    int quantidade;
    float percentual;
    float lucro;
};

int ProcuraProduto(int tamanho, int codigo, struct Produto *produtos){
    int posicao = -1;
    for (int i = 0; i < tamanho; ++i) {
        if (codigo == produtos[i].cod){
            posicao = i;
        }
    }
    return posicao;
}


void EntradaDeDados(int i, struct Produto *produtos){
    printf("====INCLUS�O DE PRODUTO====\n");
    printf("digite o c�digo do produto:\n");
    scanf("%d", &produtos[i].cod);
    printf("Digite a descri��o do produto:\n");
    scanf("%s", produtos[i].descricao);
    printf("Digite o pre�o de venda do produto\n");
    scanf("%f", &produtos[i].preco);
    printf("Digite a quantidade de produtos vendidos:\n");
    scanf("%d", &produtos[i].quantidade);
    printf("Digite digite o percentual de lucro obtido com o produto:");
    scanf("%f", &produtos[i].percentual);
    printf("Digite o lucro obtido:");
    scanf("%f", produtos[i].lucro);
}


void MostraDados(int posicao, struct Produto *produto){
    if (produto[posicao].quantidade == 0){

    }else {
        printf("c�digo: %d\n", produto[posicao].cod);
        printf("Descri��o: %s\n", produto[posicao].descricao);
        printf("Pre�o: %.2f\n", produto[posicao].preco);
        printf("Quantidade: %d\n", produto[posicao].quantidade);
    }
}


int Inclusao(int tamanho, struct Produto *produtos){
    int posicao;
    if (tamanho > 0){
        produtos = ( struct Produto*) realloc(produtos, (tamanho+1)* sizeof (struct Produto));
    }
    printf("%d\n", tamanho);
    tamanho ++;
    posicao = tamanho -1;
    EntradaDeDados(posicao, produtos);
    return tamanho;
}


void Alteracao (int tamanho, struct Produto *produtos){
    int codigo;
    printf("Digite o c�digo do produto que deseja alterar:\n");
    scanf("%d", &codigo);

    int posicao = ProcuraProduto(tamanho, codigo, produtos);

    if(produtos[posicao].quantidade == 0){
        posicao = -1;
    }
    if (posicao < 0 ){
        printf("C�digo inv�lido");
    }else{
        printf("Produto encontrado com sucesso!\n");
        MostraDados(posicao,produtos);
        printf("Digite os novos dados:\n");
        EntradaDeDados(posicao, produtos);



    }
}


void Exclusao(int tamanho, struct Produto *produtos){
    int codigo;
    printf("Digite o c�digo do produto para exclus�o:\n");
    scanf("%d", &codigo);

    int posicao = ProcuraProduto(tamanho,codigo,produtos);
    if (posicao < 0){
        printf("c�digo inv�lido");
    } else{
        printf("produto encontrado com sucesso!");
        MostraDados(posicao,produtos);
        printf("deseja prosseguir com a exclus�o?\n1 - Sim\n2 - N�o\n");
        int confirmacao;
        scanf("%d", &confirmacao);
        if (confirmacao == 1){
            produtos[posicao].quantidade = 0;
            printf("Exclus�o conclu�da");
        } else{
            printf("opera��o cancelada");
        }
    }
}

void Consulta(int tamanho, struct Produto *produtos){
    int codigo;
    printf("Digite o c�digo do produto que deseja consultar:\n");
    scanf("%d", &codigo);

    int posicao = ProcuraProduto(tamanho,codigo,produtos);

    if(produtos[posicao].quantidade == 0){
        posicao = -1;
    }
    if (posicao < 0 ){
        printf("C�digo inv�lido");
    }else {
        printf("Produto encontrado com sucesso!\n");
        MostraDados(posicao, produtos);
    }
}

void Lista(int tamanho, struct Produto *produtos){
    for (int i = 0; i < tamanho; ++i) {
        if(produtos[i].quantidade == 0){

        }else {
            printf("produto: %d\n", i);
            MostraDados(i, produtos);
        }
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    struct Produto *produtos;
    produtos = (struct Produto*) malloc(sizeof (struct Produto));
    int tamanho = 0;
    int opcao;
    do {
        printf("digite a op��o desejada:\n");
        printf("1 - Incluir produto\n");
        printf("2 - Alterar produto\n");
        printf("3 - Excluir produto\n");
        printf("4 - Consultar produto\n");
        printf("5 - Listar todos os produtos\n");
        printf("9 - Encerrar programa\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                tamanho = Inclusao(tamanho, produtos);
                break;
            case 2:
                Alteracao(tamanho,produtos);
                break;
            case 3:
                Exclusao(tamanho, produtos);
                break;
            case 4:
                Consulta(tamanho, produtos);
                break;
            case 5:
                Lista(tamanho, produtos);
                break;
            case 9:
                printf("Programa encerrado com sucesso!\n");
                break;
            default:
                printf("Op��o inv�lida!");
                break;
        }

    }while(opcao != 9);
    return 0;
}


