#include "RotorDeMapeo.h"

static NodoRotor* crearNodo(char c) {
    NodoRotor* n = (NodoRotor*)malloc(sizeof(NodoRotor));
    if (!n) return NULL;
    n->c = c;
    n->prev = n->next = NULL;
    return n;
}

RotorDeMapeo::RotorDeMapeo() : head(NULL) {
    // crear anillo A-Z
    NodoRotor* first = NULL;
    NodoRotor* prev = NULL;
    for (int i = 0; i < 26; ++i) {
        char ch = (char)('A' + i);
        NodoRotor* n = crearNodo(ch);
        if (!first) first = n;
        if (prev) {
            prev->next = n;
            n->prev = prev;
        }
        prev = n;
    }
    // cerrar el anillo
    if (first && prev) {
        prev->next = first;
        first->prev = prev;
    }
    head = first; // cabeza apunta a 'A'
}

RotorDeMapeo::~RotorDeMapeo() {
    if (!head) return;
    // romper el ciclo para liberar
    NodoRotor* cur = head->next;
    head->next = NULL;
    while (cur) {
        NodoRotor* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(head);
    head = NULL;
}

void RotorDeMapeo::rotar(int n) {
    if (!head) return;
    int steps = n % 26;
    if (steps < 0) steps += 26;
    for (int i = 0; i < steps; ++i) {
        head = head->next;
    }
}

char RotorDeMapeo::getMapeo(char in) {
    if (in >= 'A' && in <= 'Z') {
        int offset = (int)(in - 'A');
        NodoRotor* cur = head;
        for (int i = 0; i < offset; ++i) cur = cur->next;
        return cur->c;
    }
    if (in >= 'a' && in <= 'z') {
        int offset = (int)(in - 'a');
        NodoRotor* cur = head;
        for (int i = 0; i < offset; ++i) cur = cur->next;
        char up = cur->c;
        // devolver minúscula equivalente
        return (char)(up - 'A' + 'a');
    }
    // espacio u otros: devolver tal cual
    return in;
}
