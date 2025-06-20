#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct {
    long TIMESTAMP;
    char VALOR[64];
} Leitura;

Leitura leitura_mais_proxima(FILE *f, long alvo){
    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    int linhas = tamanho / 100;

    Leitura melhor, atual;
    melhor.TIMESTAMP = LONG_MAX;

    long ini = 0, final = tamanho;
    while (ini < final) {
        long meio = (ini + final) / 2;

        fseek(f, meio, SEEK_SET);
        fgets((char[128]){}, 128, f);
        if (fscanf(f, "%ld %*s %s", &atual.TIMESTAMP, atual.VALOR) == 2) {
            long diff = labs(atual.TIMESTAMP - alvo);
            long best_diff = labs(melhor.TIMESTAMP - alvo);
            if (diff < best_diff)
            melhor = atual;
            if (atual.TIMESTAMP > alvo)
            ini = meio + 1;
            else
            final = meio;
        } else break;
    }
    return melhor;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <sensor> <timestamp>\n", argv[0]);
        return 1;
    }

    char nome_do_arquivo[64];
    sprintf(nome_do_arquivo, "%s.txt", argv[1]);
    FILE *f = fopen(nome_do_arquivo, "r");
    if (!f) {
        perror("Abrindo o arquivo do sensor: \n.\n.\n.\n.\n.\nERROR!");
        return 1;
    }

    long alvo = atol(argv[2]);
    Leitura resultado = leitura_mais_proxima(f, alvo);
    printf("A leitura mais proxima eh: %ld %s\n", resultado.TIMESTAMP, resultado.VALOR);
    fclose(f);
    return 0;
}