#include <stdio.h>
#include <math.h>

/*
Esse script e uma resolução possível para o problema "A Fabrica de Tesouras" proposto
na fase 1 do nivel 1 da OBI feminina de 2024.

Feito por Vinicius Justino Cardoso em 19/09/2024 para fins educativos.
*/

#define MAXIMO_TINTA 1000000007

int main(void) {
    // Recebemos a altura da arvore de tesouras
    int altura;
    scanf("%d", &altura);

    unsigned long long int quantidade_laminas = 0;
    for (double i = 0.0; i < altura; i++) {
        /* A cada 2 incrementos de altura, exceto na transicao da altura 1 para a altura 2, a
        quantidade de laminas na ponta da arvore dobra. Compare essa expressao com diversas
        alturas diferentes para comprovar como que ela descreve perfeitamente a quantidade
        de laminas em qualquer altura de arvore */
        quantidade_laminas += (unsigned long long int)(pow(2.0, ceil(i / 2.0)));
    }

    /* Todas as laminas sao pintadas 2 vezes exceto as laminas que formam o menor caminho entre 
    o inicio da arvore e uma das pontas. O quantidade de laminas desse caminho e sempre igual a
    altura da arvore */
    int tinta_gasta = (2 * quantidade_laminas - altura) % MAXIMO_TINTA;
    printf("%d\n", tinta_gasta);
    return 0;
}

/* E importante pontuar que essa nao e uma solucao plena para o exercicio. Os tipos 
unsigned long long int e double conseguem armazenar numeros positivos de ate 8 bytes ou 64 bits. Porem,
como o maior valor de entrada segundo as restricoes do enunciado pode ser 50000, ate 3126 bytes
podem ser necessarios para armazenar a quantidade de laminas em uma arvore.
Nao e possivel calcular corretamente a resposta para casos onde a quantidade de tinta gasta excede 8
bytes de tamanho usando os tipos e funcoes padroes do C e, portanto, essa solucao marcaria 87 pontos. 
Mas e possivel conseguir os outros 13 pontos da subtarefa 9 usando alocacao dinamica de memoria e
definindo tipos personalizados com tamanhos maiores.*/
