#include <stdio.h>

/*
Esse script e uma resolução possível para o problema "Bibi e a Arvore" proposto na
fase 1 do nivel 1 da OBI feminina de 2024.

Feito por Vinicius Justino Cardoso em 18/09/2024 para fins educativos.
*/

int main(void) {
    /* Os tamanhos da arvore nos primeiros 5 meses nao seguem uma sequencia logica e,
    portanto, devemos guardar esses valores num array pois eles não podem ser calculados */
    int tamanhos[5] = {1, 2, 4, 5, 7};

    // Recebemos a entrada (em mes de vida)
    int mes;
    scanf("%d", &mes);

    int tamanho;
    if (mes > 5) {
        /* A partir do sexto mes de vida, a altura da abratibum pode ser expressada como:
        altura no quinto mes de vida + (altura no sexto mes - altura no quinto mes) * quantidade de meses após o quinto
        
        altura no sexto mes = 13
        altura no quinto mes = tamanhos[4] = 7
        (altura no sexto mes - altura no quinto mes) = 6
        quantidade de meses após o quinto = mes - 5 */

        tamanho = tamanhos[4] + 6 * (mes - 5);
    } else {
        // Se o mes de vida for menor que 6, precisamos retornar um dos valores previamente armazenados
        tamanho = tamanhos[mes - 1];
    }

    // Nao esqueca de terminar a saida com o caractere de fim de linha: \n
    printf("%d\n", tamanho);
    return 0;
};