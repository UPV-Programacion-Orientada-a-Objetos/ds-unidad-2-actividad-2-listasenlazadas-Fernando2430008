#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SerialPortWin32.h"
#include "Tramas.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

static void trim(char* s) {
    if (!s) return;
    // quitar espacios finales y CR/LF
    int len = (int)strlen(s);
    while (len > 0 && (s[len-1] == '\r' || s[len-1] == '\n' || s[len-1] == ' ' || s[len-1] == '\t')) {
        s[--len] = '\0';
    }
}

static TramaBase* parseLine(const char* line) {
    if (!line || !line[0]) return NULL;
    // Copia mutable pequeña
    char buf[64];
    size_t n = strlen(line);
    if (n >= sizeof(buf)) n = sizeof(buf)-1;
    memcpy(buf, line, n); buf[n] = '\0';

    // Buscar coma
    char* type = buf;
    char* rest = NULL;
    for (size_t i = 0; i < n; ++i) {
        if (buf[i] == ',') { buf[i] = '\0'; rest = &buf[i+1]; break; }
    }

    if (!type || !type[0]) return NULL;
    char T = type[0];

    if (T == 'L' || T == 'l') {
        if (!rest) return NULL;
        // Interpretar Space o un solo char
        if ((rest[0] == 'S' || rest[0] == 's') && (rest[1] == 'p' || rest[1] == 'P')) {
            return new TramaLoad(' ');
        }
        // si viene comillas o similares, tomar primer caracter legible
        return new TramaLoad(rest[0]);
    }
    if (T == 'M' || T == 'm') {
        if (!rest) return NULL;
        int sign = 1; int i = 0; int val = 0;
        if (rest[0] == '-') { sign = -1; i = 1; }
        for (; rest[i]; ++i) {
            if (rest[i] < '0' || rest[i] > '9') break;
            val = val * 10 + (rest[i]-'0');
        }
        return new TramaMap(sign * val);
    }
    return NULL;
}

int main(int argc, char** argv) {
    const char* port = (argc > 1) ? argv[1] : "COM3"; // ejemplo
    unsigned long baud = (argc > 2) ? (unsigned long)atoi(argv[2]) : 9600UL;

    printf("Iniciando Decodificador PRT-7. Conectando a puerto COM...\n");

    SerialPortWin32 sp;
    if (!sp.open(port, baud)) {
        printf("No se pudo abrir el puerto %s. Verifique conexiones y permisos.\n", port);
        return 1;
    }
    printf("Conexi\xC3\xB3n establecida. Esperando tramas...\n\n");

    ListaDeCarga lista;
    RotorDeMapeo rotor;

    printf("(Presiona Ctrl+C para detener)\n\n");
    char line[64];
    while (1) {
        if (!sp.readLine(line, sizeof(line), 0)) {
            // sin timeout: solo retorna false ante error del puerto
            break;
        }
        trim(line);
        if (line[0] == '\0') continue;

        printf("Trama recibida: [%s] -> Procesando... ", line);

        TramaBase* trama = parseLine(line);
        if (!trama) {
            printf("Formato inv\xC3\xA1lido. Ignorando.\n");
            continue;
        }

        // Para logging: si es L,X o M,N mostrar efecto
        if (line[0] == 'M' || line[0] == 'm') {
            // extraer N de la línea para el log
            char* comma = strchr(line, ',');
            int n = 0;
            if (comma) n = atoi(comma+1);
            printf("-> ROTANDO ROTOR %s%d.\n\n", (n>=0?"+":""), n);
            trama->procesar(&lista, &rotor);
        } else {
            // LOAD
            char ch = ' ';
            char* comma = strchr(line, ',');
            if (comma) {
                if (comma[1] == 'S' || comma[1] == 's') ch = ' ';
                else ch = comma[1];
            }
            char dec = rotor.getMapeo(ch);
            printf("-> Fragmento '%c' decodificado como '%c'. Mensaje: ", ch, dec);
            trama->procesar(&lista, &rotor);
            lista.imprimirMensajeEnBrackets();
            printf("\n\n");
        }

        delete trama;
    }

    printf("---\nFlujo de datos terminado.\nMENSAJE OCULTO ENSAMBLADO:\n");
    lista.imprimirMensajePlano();
    printf("\n---\nLiberando memoria... Sistema apagado.\n");

    return 0;
}
