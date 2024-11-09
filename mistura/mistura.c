#include <stdio.h>
#include <math.h>

/*
Esse script e uma resolução possível para o problema "Mistura de Poçoes" proposto
na fase 1 do nivel 1 da OBI feminina de 2024.

Feito por Vinicius Justino Cardoso em 19/09/2024 para fins educativos.
*/

int main(void) {
    // Primeiro, recebemos a quantidade de pocoes e o minimo que precisamos deixar na preteleira
    int quantidade_pocoes, minimo_pocoes_diferentes;
    scanf("%d %d", &quantidade_pocoes, &minimo_pocoes_diferentes);

    /* Segundo as restricoes do enunciado, a quantidade N de pocoes esta entre 1 e 100000, portanto 
    cada numero pode ter ate 6 digitos e sera seguido de 1 espaco em branco. Sendo assim, precisamos
    alocar 7 bytes para cada numero mais 1 para o caractere de fim de string '\0' */
    char entrada_bruta[quantidade_pocoes * 7 + 1];

    /* O tipo de cada pocao na prateleira vai entrar no programa como uma unica linha com numeros
    separados por espaco. Devido as funcionalidades de interpretacao de entrada da funcao scanf(),
    nao podemos receber essa entrada escrevendo:
        scanf("%s", &entrada_bruta);
    Pois a funcao considera espacos em branco como a separacao entre valores diferentes. Isso quer
    dizer que se a entrada fosse, por exemplo "1 2 3 4 5", apenas "1" seria armazenado na variavel
    entrada_bruta, o resto da entrada seria considerado como 4 strings diferentes e seria ignorado
    pela funcao.

    Para receber uma entrada bruta, sem nenhuma interpretacao, podemos utilizar a funcao fgets():
    */
    getchar();
    fgets(entrada_bruta, sizeof entrada_bruta, stdin);
    /* Os argumentos significam:
        entrada_bruta: a variavel que vai armazenar a string,
        sizeof entrada_bruta: "sizeof" e um comando do C que retorna o tamanho em bytes alguma
                             estrutura. "sizeof entrada_bruta" passa o tamanho de entrada_bruta
                             como a quantidade de caracteres que a funcao vai ler antes de
                             retornar;
        stdin: o arquivo que vai ser lido pela funcao. stdin representa a entrada padrao. Isso
               significa que a funcao vai ler os caracteres digitados pelo teclado.
    */

    /* Como fgets() nao interpreta a entrada, os numeros recebidos ainda estao em formato de string
    e precisam ser convertidos em int para resolvermos a questao */
    int prateleira[quantidade_pocoes];

    int caractere_atual = 0;
    for (int pocao_atual = 0; pocao_atual < quantidade_pocoes; pocao_atual++) {
        /* declaramos tipo_pocao como um double pois iremos utilizar uma funcao do header <math.h>,
        que so trabalha com numeros do tipo double para atingir o maximo de precisao decimal nas
        operacoes */
        double tipo_pocao = 0.0;

        /* Precisamos saber em qual casa do numero cada digito vai para montarmos o numero tipo_pocao
        sem embaralhar o numero. Repare que o primeiro digito que aparecer na string sera  o que esta
        na maior casa (supondo que o numero tenha 6 digitos, o primeiro estara na casa 6) e o digito
        que aparecer antes do espaço em branco estara na casa 1 */
        double casa = 6.0;

        /* Vamos avancar caractere por caractere na string de entrada e adicionar cada digito ao tipo da 
        mesma pocao ate encontrarmos um caractere de espaco em branco. A cada vez que avancamos um
        caractere, estamos diminuindo a magnitude da casa decimal do proximo digito, por isso,
        conforme incrementamos caractere_atual, estamos decrementando casa */
        for (; entrada_bruta[caractere_atual] != ' ' && entrada_bruta[caractere_atual] != '\n'; casa--, caractere_atual++) {
            /* Para converter um char de digito para o int correspondente, e necessario entender que
            o C codifica cada caractere na mesma sequencia da tabela ASCII. Nela, os digitos de 0 a 9
            aparecem na ordem crescente entre as posicoes 48 e 57. Quando convertemos um char para int,
            o valor retornado e a posicao daquele caractere na tabela ASCII, por exemplo:
                (int)('1') == 49
            Basta subtrair 48 da posicao, e convertemos '1' em 1 com sucesso!
            
            Apos converter o char para int, basta posicionar o digito na casa correta. Para colocar
            um digito na casa 2, basta multiplicar ele por 10; para colocar na casa 3, multiplique
            por 100 e assim por diante. Para colocar um digito em uma casa qualquer, basta multiplicar
            ele por 10**(casa - 1). Para fazer essa exponenciacao, utilizaremos a funcao pow()
            fornecida pelo header <math.h> (incluido na linha 2 do codigo). Repare que passamos 10
            escrito como um double (10.0), lembre-se que todas as funcoes de <math.h> trabalham
            com doubles!
            */
            tipo_pocao += ((int)(entrada_bruta[caractere_atual]) - 48) * pow(10.0, (casa - 1));
        }

        /* Se o numero do tipo da pocao realmente tiver 6 casa, decrementamos a variavel casa 6
        vezes no for acima e, portanto, ela valera 0. Caso o numero tenha menos casas, casa tera um
        valor maior, que representa a ordem de magnitude do erro (em outras palavras, quantos zeros
        tipo_pocao tem a mais). Precisamos descer tipo_pocao em "casa" ordens de magnitude para
        garantir que todos os digitos estao nas casas corretas */
        tipo_pocao /= pow(10.0, casa);
        caractere_atual++;

        prateleira[pocao_atual] = (int)(tipo_pocao);
    }

    /* Agora que conseguimos organizar a prateleira de Lulu, vamos calcular de quantas maneiras ela
    pode se livrar de uma parte de sua colecao. Desde que uma sequencia de pocoes seja continua,
    tenha no minimo minimo_pocoes_diferentes pocoes de tipos diferentes, sabemos que podemos tirar
    todas as outras pocoes da prateleira e deixar so essa sequencia. Precisamos entao calcular a
    quantidade de sequencias que satisfazem essas condicoes */
    int sequencias_possiveis = 0;

    // Vamos contar todas as sequencias validas de tamanhos entre o minimo e o maior possivel
    for (int tamanho_sequencia = minimo_pocoes_diferentes; tamanho_sequencia <= quantidade_pocoes; tamanho_sequencia++) {
        // Vamos testar a sequencia de pocoes 1, 2, 3, ..., depois 2, 3, 4, ..., e assim por diante
        for (int comeco_sequencia = 0; comeco_sequencia + tamanho_sequencia <= quantidade_pocoes; comeco_sequencia++) {
            // Inicializamos o array que guardara as pocoes diferentes na sequencia
            int pocoes_diferentes[minimo_pocoes_diferentes];
            for (int i = 0; i < minimo_pocoes_diferentes; i++) {
                pocoes_diferentes[i] = 0;
            }

            pocoes_diferentes[0] = prateleira[comeco_sequencia];
            int contador_pocoes_diferentes = 1;

            // Vamos pegando pocoes da prateleira ate a sequencia chegar no tamanho apropriado ou no minimo de pocoes diferentes
            for (int posicao_sequencia = 0; posicao_sequencia < tamanho_sequencia && contador_pocoes_diferentes < minimo_pocoes_diferentes; posicao_sequencia++) {
                int pocao_atual = prateleira[comeco_sequencia + posicao_sequencia];
                int tipo_diferente = 1;

                // E vamos verificando se o tipo dessa pocao e unico
                for (int pocao = 0; pocao < contador_pocoes_diferentes && tipo_diferente; pocao++) {
                    tipo_diferente = (pocoes_diferentes[pocao] != pocao_atual);
                }

                /* Se o tipo da pocao for unico, adicionamos ela no array de pocoes diferentes e incrementamos o contador 
                de pocoes diferentes */
                if (tipo_diferente) {
                    pocoes_diferentes[contador_pocoes_diferentes] = pocao_atual;
                    contador_pocoes_diferentes++;
                }
            }

            /* Se acharmos a quantidade minima de pocoes diferentes dentro de uma sequencia, nao precisamos
            mais continuar contando e ja podemos considerar ela como uma possibilidade */
            if (contador_pocoes_diferentes == minimo_pocoes_diferentes) {
                sequencias_possiveis++;
            }
        }
    }

    printf("%d\n", sequencias_possiveis);

    return 0;
};