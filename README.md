# SensorInteligente2
3 sensores atualizados (primeira vez postando código-fonte com 3 programas, sou iniciante do git)
Por que atualizados? Devido às mudanças como:
4 tipos de dados (int, float, bool e string); e
a criação de 2000 leituras aleatórias com valores numéricos aleatórios e timestamps sorteados.

Programa 1: 

typedef enum {
    TIPO_INT,
    TIPO_BOOL,
    TIPO_FLOAT,
    TIPO_STRING
} TiposDeDados; //Enumerar 4 tipos de dados (int, bool, float e string)

typedef struct {
    long TIMESTAMP;
    char VALOR[64];
} Leitura; //Ordena as leituras se será em ordem crescente ou decrescente, com TIMESTAMP e VALOR.

typedef struct {
    char ID_SENSOR[32];
    TiposDeDados tipo;
    Leitura *leituras;
    int tamanho;
    int capacidade;
} Sensor; //Estrutura sobre o sensor, com ID_SENSOR.

Linha 28, "int comparar_leitura" é pra ordenar a leitura em ordem decrescente.
Linha 41, "TiposDeDados checar_qual_tipo", pra checar os tipos bool, int, float e string.
Linha 100, qsort serve como suporte, dentro do int main

Detalhe: se não digitar corretamente o nome do arquivo que você queira abrir, aparecerá por essa mensagem: Abrindo arquivo: ..... ERROR! (Mesma coisa no segundo, se digitar sensor errado ou o timestamp idêntico ou algo parecido, e no terceiro programa, caso não digitasse corretamente a data, o nome e o tipo de dado)
____________________________________________________

Programa 2: Busca qual a leitura mais próxima na hora de digitar TEMP, VIBR, PRES, ou outras e TIMESTAMP em ordem decrescente.
Usa-se a busca binária com um benefício mais importante: garantir melhor desempenho quando se procura em número enorme de dados.

________________________________________________________________________________

Programa 3:
Nesse programa, você digita a data (Ano, mês e dia, nessa ordem) e a hora do início do intervalo de amostras que foram geradas aleatoriamente. Isso vale também no fim do intervalo das amostras. Depois de colocado, digite o sensor e, em seguida, o tipo de dado da amostra que é informada para sensor.

Esse programa PODE conter:
Argumento válido
Data inválida

____________________________________________________________

O que recomendo na hora da execução?
Programa 3
Programa 1
Programa 2
