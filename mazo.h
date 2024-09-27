#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "carta.h"

using namespace std;

class Mazo {
private:
    vector<Carta> cartas;

public:
    Mazo() {
        generarCartas();
        barajar();
    }

    void generarCartas() {
        string colores[] = {"rojo", "verde", "azul", "amarillo", "morado", "Naranjado", "marron"};
        // 63 cartas de colores, 9 de cada uno de los 7 colores
        for (const auto& color : colores) {
            for (int i = 0; i < 9; ++i) {
                cartas.push_back(Carta(color));
            }
        }

        // 10 cartas '+2'
        for (int i = 0; i < 10; ++i) {
            cartas.push_back(Carta("+2", "+2"));
        }

        // 2 comodines
        cartas.push_back(Carta("comodin", "comodin"));
        cartas.push_back(Carta("comodin dorado", "comodin"));
        
        // Eliminamos la carta de 'última ronda'
        // cartas.push_back(Carta("ultimaRonda", "ultimaRonda")); // Esta línea es eliminada
    }

    void barajar() {
        srand(unsigned(time(0)));
        random_shuffle(cartas.begin(), cartas.end());
    }

    Carta tomarCarta() {
        Carta carta = cartas.back();
        cartas.pop_back();
        return carta;
    }

    bool estaVacio() const {
        return cartas.empty();
    }

    int getNumeroCartas() const { // Método para obtener el número de cartas restantes
        return cartas.size();
    }
};

#endif
