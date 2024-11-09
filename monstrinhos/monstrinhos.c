#include <stdio.h>

/*
Esse script e uma resolução possível para o problema "Fadas versus Monstros" proposto
na fase 1 do nivel 1 da OBI feminina de 2024.

Feito por Vinicius Justino Cardoso em 19/09/2024 para fins educativos.
*/

int main(void) {
    int quantidade_monstros, quantidade_fadas;

    // Primeiro, recebemos a quantidade de monstros
    scanf("%d", &quantidade_monstros);

    // Depois, recebemos a quantidade de fadas
    scanf("%d", &quantidade_fadas);

    // Guardaremos os poderes de todos os monstros em um array
    int monstros[quantidade_monstros];
    for (int i = 0; i < quantidade_monstros; i++) {
        int poder_monstro;
        scanf("%d", &poder_monstro);

        monstros[i] = poder_monstro;
    }

    /* Guardaremos todas os poderes e bonus de cada fada como pares ordenados (poder, bonus)
    em um array */
    int fadas[quantidade_fadas][2];

    // Recebemos primeiro o poder de cada fada
    for (int i = 0; i < quantidade_fadas; i++) {
        int poder_fada;
        scanf("%d", &poder_fada);

        fadas[i][0] = poder_fada;
    }

    // Depois, recebemos o bonus de cada fada
    for (int i = 0; i < quantidade_fadas; i++) {
    	int bonus_fada;
        scanf("%d", &bonus_fada);

        fadas[i][1] = bonus_fada;
    }

    /* Antes de comecar as batalhas,precisamos nos atentar a este trecho do ultimo paragrafo
    do enunciado: "[...], sua tarefa e descobrir quantos monstrinhos Fefe ira derrotar SE ELA 
    JOGAR DA MELHOR FORMA POSSIVEL."

    O que seria jogar da melhor forma possivel? Supondo que:
    monstros[2] = {3, 5}
    fadas[2][2] = {{4, 1}, {6, 1}}

    Neste exemplo, temos 2 monstros, com forcas 3 e 5. Ja as 2 fadas tem forcas 4 e 6 e ambas
    conseguem lutar com apenas 1 monstro. Se a fada de poder 6 derrotar o monstro de poder 3,
    sobra o monstro de poder 5 para lutar contra a fada de poder 4. Nesse caso, Fefe derrotaria
    apenas 1 monstrinho.
    Porem, se a fada de poder 6 derrotar o monstro de poder 5, a fada de poder 4 consegue
    derrotar o monstro de poder 3, e entao Fefe tera derrotado 2 monstrinhos.

    Jogar da melhor maneira possivel significa que cada fada vai lutar contra os monstros mais
    fortes que conseguir. Portanto, para cada fada representada pelo par ordenado (poder, bonus)
    {P, B} no array fadas, precisamos encontrar ate B monstros M no array monstros tal que estes M
    sao os maiores valores possiveis que satisfazem a condicao P > M. 
    */

	int monstros_derrotados = 0;
   
	for (int fada_atual = 0; fada_atual < quantidade_fadas; fada_atual++) {
		/* Para cada fada, iremos procurar bonus_fada_atual vezes o maior poder_monstro que satisfaz
		a condicao poder_fada_atual > poder_monstro. Desta forma, estaremos lutando da melhor
		maneira possivel */
		int poder_fada_atual = fadas[fada_atual][0];
		int bonus_fada_atual = fadas[fada_atual][1];

		for (int contador_batalhas = 0; contador_batalhas < bonus_fada_atual; contador_batalhas++) {
			/* Vamos acompanhar tanto o poder do monstro mais forte como sua posicao no array
			monstros em um par ordenado (poder, posicao). Assim, poderemos usar a segunda informacao
			para remover o monstro do array depois que ele for derrotado */
			int monstro_mais_forte_derrotavel[2] = {0, -1};

			for (int posicao_monstro = 0; posicao_monstro < quantidade_monstros; posicao_monstro++) {
				int poder_monstro = monstros[posicao_monstro];

				/* Se o monstro for derrotavel e mais forte do que o mais forte derrotavel ate entao,
				ele vira o novo monstro mais forte derrotavel */
				if (poder_fada_atual > poder_monstro && poder_monstro > monstro_mais_forte_derrotavel[0]) {
					monstro_mais_forte_derrotavel[0] = poder_monstro;
					monstro_mais_forte_derrotavel[1] = posicao_monstro;
				}
			}

			if (monstro_mais_forte_derrotavel[1] == -1) {
				/* Se a posicao do monstro mais forte continuar sendo nosso valor padrao pre-definido,
				a fada nao consegue derrotar nenhum monstro e, portanto, nao precisamos continuar
				lutando com ela */
				break;
			} else {
				/* Se a posicao do monstro mais forte for um indice valido do array monstros,
				derrotamos esse monstro e adicionamos 1 no contador de monstros derrotados.
				Mudar o valor do poder do monstro derrotador para 0 garante que ele nao sera
				mais considerado como monstro mais forte em nenhuma batalha futura */
				monstros[monstro_mais_forte_derrotavel[1]] = 0;
				monstros_derrotados++;
			}
		}
   	}

	printf("%d\n", monstros_derrotados);

    return 0;
};