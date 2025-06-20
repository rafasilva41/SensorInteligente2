#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char* mapear_tipo(const char* tipo_de_usuario) {
    if (strcmp(tipo_de_usuario, "CONJ_Z") == 0) return "int";
    if (strcmp(tipo_de_usuario, "CONJ_Q") == 0) return "float";
    if (strcmp(tipo_de_usuario, "TEXTO") == 0) return "string";
    if (strcmp(tipo_de_usuario, "BINARIO") == 0) return "bool";
    return NULL;
}

void gerar_valor(char *dest, const char *tipo) {
    if (strcmp(tipo, "int") == 0)
    sprintf(dest, "%d", rand() % 1000);
    else if (strcmp(tipo, "bool") == 0)
    strcpy(dest, rand() % 2 ? "true" : "false");
    else if (strcmp(tipo, "float") == 0)
    sprintf(dest, "%.2f", (rand() % 10000) / 100.0);
    else {
        for (int i = 0; i < 8; i++)
        dest[i] = 'A' + rand() % 26;
        dest[8] = '\0';
    }
}


time_t parse_datahora(const char *str) {
    struct tm t = {0};
    sscanf(str, "%d/%d/%d-%d:%d:%d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec);
       
    t.tm_year -= 1900;
    t.tm_mon -= 1;
    return mktime(&t);
}

int main(int argc, char *argv[]) {
    if (argc < 5 || (argc - 3) % 2 != 0) {
        fprintf(stderr, "Uso: %s <inicio> <fim> <sensor1> <tipo1> [...]\n", argv[0]);
        return 1;
    }

    time_t comeco = parse_datahora(argv[1]);
    time_t final = parse_datahora(argv[2]);

    FILE *saida = fopen("leituras.txt", "w");
    if (!saida) {
        perror("Abrindo o arquivo de saida: \n.\n.\n.\n.\n.\nERROR!!!!!!!!");
        return 1;
    }
    srand(time(NULL));
    
    for (int i = 3; i < argc; i += 2) {
        char *sensor = argv[i];
        const char *tipo_mapeado = mapear_tipo(argv[i+1]);
        if (!tipo_mapeado) {
            fprintf(stderr, "Nao esta valido para esse sensor %s: %s\n", sensor, argv[i + 1]);
            continue;
        }
        for (int j = 0; j < 2000; j++) {
            time_t t = comeco + rand() % (final - comeco + 1);
            char VALOR[64];
            gerar_valor(VALOR, tipo_mapeado);
            fprintf(saida, "%ld %s %s\n", t, sensor, VALOR);
        }
    }
        
    fclose(saida);
    return 0; 
}