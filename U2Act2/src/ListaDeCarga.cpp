#include "ListaDeCarga.h"

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* cur = head;
    while (cur) {
        NodoCarga* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
}

void ListaDeCarga::insertarAlFinal(char c) {
    NodoCarga* n = (NodoCarga*)malloc(sizeof(NodoCarga));
    if (!n) return; // fallo silencioso
    n->dato = c;
    n->prev = tail;
    n->next = NULL;
    if (!head) head = n;
    if (tail) tail->next = n;
    tail = n;
    size_++;
}

void ListaDeCarga::imprimirMensajeEnBrackets() {
    NodoCarga* cur = head;
    while (cur) {
        putchar('[');
        putchar(cur->dato);
        putchar(']');
        cur = cur->next;
    }
}

void ListaDeCarga::imprimirMensajePlano() {
    NodoCarga* cur = head;
    while (cur) {
        putchar(cur->dato);
        cur = cur->next;
    }
}
