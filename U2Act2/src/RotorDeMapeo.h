/**
 * @file RotorDeMapeo.h
 * @brief Lista circular doblemente enlazada que implementa un rotor tipo César.
 */
#pragma once

#include <stdlib.h>
#include <ctype.h>

struct NodoRotor {
    char c;
    NodoRotor* prev;
    NodoRotor* next;
};

/**
 * @brief Rotor circular que rota la cabeza y mapea letras A-Z.
 */
class RotorDeMapeo {
    NodoRotor* head; // posición cero actual
public:
    RotorDeMapeo();
    ~RotorDeMapeo();

    void rotar(int n);

    /**
     * @brief Devuelve el carácter mapeado según el estado actual del rotor.
     * - Solo mapea A-Z. Otros (espacio, etc.) se devuelven tal cual.
     */
    char getMapeo(char in);
};
