/**
 * @file Tramas.h
 * @brief Definiciones de la jerarquía de tramas PRT-7.
 */
#pragma once

#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @brief Clase base abstracta para cualquier trama recibida.
 */
class TramaBase {
public:
    virtual ~TramaBase() {}
    /**
     * @brief Procesa la trama y actualiza estructuras.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

/**
 * @brief Trama de carga L,X
 */
class TramaLoad : public TramaBase {
    char m_ch;
public:
    explicit TramaLoad(char ch) : m_ch(ch) {}
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

/**
 * @brief Trama de rotación/mapa M,N
 */
class TramaMap : public TramaBase {
    int m_n;
public:
    explicit TramaMap(int n) : m_n(n) {}
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};
