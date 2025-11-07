#include "Tramas.h"
#include <stdio.h>

void TramaMap::procesar(ListaDeCarga* /*carga*/, RotorDeMapeo* rotor) {
    if (rotor) rotor->rotar(m_n);
}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char dec = m_ch;
    if (rotor) dec = rotor->getMapeo(m_ch);
    if (carga) carga->insertarAlFinal(dec);
}
