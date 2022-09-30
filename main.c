#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
struct Produto{
    int cod;
    char descricao[50];
    float preco;
    int quantidade;
    float percentual;
    float lucro;
};

int ProcuraProduto(int tamanho, int codigo, struct Produto *produtos){
    int posicao;
    for (int i = 0; i < tamanho; ++i) {
        if (codigo == produtos[i].cod){
            posicao = i;
            break;
        } else{
            posicao = -1;
        }
    }
    return posicao;
}


void EntradaDeDados(int i, struct Produto *produtos){
    printf("====INCLUSÃO DE PRODUTO====\n");
    printf("digite o código do produto:\n");
    scanf("%d", &produtos[i].cod);
    printf("Digite a descrição do produto:\n");
    scanf("%s", produtos[i].descricao);
    printf("Digite o preço de venda do produto\n");
    scanf("%f", &produtos[i].preco);
    printf("Digite a quantidade de produtos vendidos:\n");
    scanf("%d", &produtos[i].quantidade);
    printf("Digite digite o percentual de lucro obtido com o produto:");
    scanf("%f", &produtos[i].percentual);
    printf("Digite o lucro obtido:");
    scanf("%f", &produtos[i].lucro);
}


void MostraDados(int posicao, struct Produto *produto){
        printf("Descrição: %s\n", produto[posicao].descricao);
        printf("Preço: %.2f\n", produto[posicao].preco);
}

void troca(int posicao, struct Produto *produto) {
    struct Produto *aux;
    aux = (struct Produto *) malloc(sizeof(struct Produto));
    //salvando os valores na variável auxiliar
    aux[0].cod = produto[posicao + 1].cod;
    strcpy(aux[0].descricao, produto[posicao + 1].descricao);
    aux[0].preco = produto[posicao + 1].preco;
    aux[0].quantidade = produto[posicao + 1].quantidade;
    aux[0].percentual = produto[posicao + 1].percentual;
    aux[0].lucro = produto[posicao + 1].lucro;

    //
    produto[posicao + 1].cod = produto[posicao].cod;
    strcpy(produto[posicao + 1].descricao, produto[posicao].descricao);
    produto[posicao + 1].preco = produto[posicao].preco;
    produto[posicao + 1].quantidade = produto[posicao].quantidade;
    produto[posicao + 1].percentual = produto[posicao].percentual;
    produto[posicao + 1].lucro = produto[posicao].lucro;

    produto[posicao].cod = aux[0].cod;
    strcpy(produto[posicao].descricao, aux[0].descricao);
    produto[posicao].preco = aux[0].preco;
    produto[posicao].quantidade = aux[0].quantidade;
    produto[posicao].percentual = aux[0].percentual;
    produto[posicao].lucro = aux[0].lucro;
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
void Ordenar (int tam, struct Produto *produto)
{
    int i;
    if (tam > 1)
    {
        for (i=0; i<tam-1; i++)
        {
            if (produto[i].lucro < produto[i + 1].lucro )
            {
                troca(i,produto);
            }
        }
        Ordenar(tam-1, produto);
    }
}

void Registra(int tamanho, struct Produto *produto){
    int cod;
    int quantVendida;
    printf("Digite o Código do produto vendido:");
    scanf("%d", &cod);

    int posicao = ProcuraProduto(tamanho,cod,produto);

    if (posicao < 0){
        printf("código inválido!");
    } else{
        printf("Produto Encontrado!");
        printf("Digite a quantidade Vendida:");
        scanf("%d", &quantVendida);
        produto[posicao].quantidade += quantVendida;

    }
}

void lucratividade(int tamanho, struct Produto *produto){
    for (int i = 0; i < tamanho; ++i) {
        produto[i].lucro += produto[i].preco * produto[i].quantidade * (produto[i].percentual / 100);
    }
    Ordenar(tamanho, produto);
    printf("\n---lucratividade---\n");
    for (int i = 0; i < tamanho; ++i) {
        printf("produto: %d: \n", i+1);
        MostraDados(i,produto);
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    struct Produto *produtos;
    produtos = (struct Produto*) malloc(sizeof (struct Produto));
    int tamanho = 0;
    int opcao;
    do {
        printf("digite a opção desejada:\n");
        printf("1 - Incluir produto\n");
        printf("2 - Registrar venda\n");
        printf("3 - Emitir lucratividade\n");
        printf("9 - Encerrar programa\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                tamanho = Inclusao(tamanho, produtos);
                break;
            case 2:
                Registra(tamanho,produtos);
                break;
            case 3:
                lucratividade(tamanho, produtos);
                break;
            case 9:
                printf("Programa encerrado com sucesso!\n");
                break;
            default:
                printf("Opção inválida!");
                break;
        }

    }while(opcao != 9);
    return 0;
}


