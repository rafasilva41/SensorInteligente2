#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TIPO_INT,
    TIPO_BOOL,
    TIPO_FLOAT,
    TIPO_STRING
} TiposDeDados;

typedef struct {
    long TIMESTAMP;
    char VALOR[64];
} Leitura;

typedef struct {
    char ID_SENSOR[32];
    TiposDeDados tipo;
    Leitura *leituras;
    int tamanho;
    int capacidade;
} Sensor;

Sensor sensores[100];
int quantidade_de_sensores = 0;

int comparar_leitura(const void *a, const void *b) {
    Leitura *la = (Leitura *)a, *lb = (Leitura *)b;
    return (lb->TIMESTAMP - la->TIMESTAMP);
}

int encontrar_sensor(const char *ID_SENSOR) {
    for (int i = 0; i < quantidade_de_sensores; i++) {
        if (strcmp(sensores[i].ID_SENSOR, ID_SENSOR) == 0)
            return i;
    }
    return -1;
}

TiposDeDados checar_qual_tipo(const char *VALOR) {
    if (strcmp(VALOR, "true") == 0 || strcmp(VALOR, "false") == 0)
    return TIPO_BOOL;

    if(strspn(VALOR, "0123456789") == strlen(VALOR))
    return TIPO_INT;

    if(strchr(VALOR, '.') != NULL)
    return TIPO_FLOAT;

    return TIPO_STRING;
}

void adicionar_leitura(const char *ID_SENSOR, long TIMESTAMP, const char *VALOR) {
    int idx = encontrar_sensor(ID_SENSOR);
    if (idx == -1) {
        idx = quantidade_de_sensores++;
        strcpy(sensores[idx].ID_SENSOR, ID_SENSOR);
        sensores[idx].tipo = checar_qual_tipo(VALOR);
        sensores[idx].leituras = malloc(sizeof(Leitura) * 2000);
        sensores[idx].tamanho = 0;
        sensores[idx].capacidade = 2000;
    }

    Sensor *s = &sensores[idx];
    if (s->tamanho >= s->capacidade) {
        s->capacidade *= 2;
        s->leituras = realloc(s->leituras, s->capacidade * sizeof(Leitura));
    }
    s->leituras[s->tamanho].TIMESTAMP = TIMESTAMP;
    strcpy(s->leituras[s->tamanho].VALOR, VALOR);
    s->tamanho++;

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        perror("Abrindo arquivo: \n.\n.\n.\n.\n.\nERROR!");
        return 1;
    }

    char linha[256];
    while (fgets(linha, 256, arquivo)) {
        long TIMESTAMP;
        char ID_SENSOR[32], VALOR[64];
        if (sscanf(linha, "%ld %s %s", &TIMESTAMP, ID_SENSOR, VALOR) == 3) {
            adicionar_leitura(ID_SENSOR, TIMESTAMP, VALOR);
        }
    }
    fclose(arquivo);

    for (int i = 0; i < quantidade_de_sensores; i++) {
        Sensor *s = &sensores[i];
        qsort(s->leituras, s->tamanho, sizeof(Leitura), comparar_leitura);

        char nome_do_arquivo[64];
        sprintf(nome_do_arquivo, "%s.txt", s->ID_SENSOR);
        FILE *out = fopen(nome_do_arquivo, "w");
        for (int j = 0; j < s->tamanho; j++)
        fprintf(out, "%ld %s %s\n", s->leituras[j].TIMESTAMP, s->ID_SENSOR, s->leituras->VALOR);
        fclose(out);
        free(s->leituras);
    }

    return 0;
}
