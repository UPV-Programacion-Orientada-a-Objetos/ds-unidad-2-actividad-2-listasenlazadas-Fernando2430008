/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada manual para almacenar caracteres decodificados.
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>

struct NodoCarga {
    char dato;
    NodoCarga* prev;
    NodoCarga* next;
};

/**
 * @brief Lista doblemente enlazada para los datos decodificados.
 */
class ListaDeCarga {
    NodoCarga* head;
    NodoCarga* tail;
    size_t size_;
public:
    ListaDeCarga() : head(NULL), tail(NULL), size_(0) {}
    ~ListaDeCarga();
    void insertarAlFinal(char c);
    void imprimirMensajeEnBrackets();
    void imprimirMensajePlano();
    size_t size() const { return size_; }
};
