#ifndef FILA_H
#define FILA_H

#include <vector>
#include "carta.h"
#include <iostream>

using namespace std;

class Fila {
private:
    vector<Carta> cartas;
    static const int maxCartas = 3;  // Máximo de 3 cartas por fila
    bool filaActiva = true;

public:
    bool agregarCarta(const Carta& carta) {
        if (filaActiva && cartas.size() < maxCartas) {
            cartas.push_back(carta);
            return true;  // Indica que la carta fue colocada con éxito
        }
        return false;  // La fila ya tiene 3 cartas o está inactiva
    }

    vector<Carta> tomarCartas() {
        vector<Carta> cartasTomadas = cartas;
        cartas.clear();
        filaActiva = false; // Marcar la fila como tomada
        return cartasTomadas;
    }

    bool estaLlena() const {
        return cartas.size() == maxCartas;
    }

    void mostrar() const {
        if (filaActiva) {
            cout << "Fila con " << cartas.size() << " cartas: ";
            for (const auto& carta : cartas) {
                cout << carta.toString() << " | ";
            }
            cout << endl;
        } else {
            cout << "Fila ya tomada!" << endl;
        }
    }

    bool estaVacia() const {
        return cartas.empty();
    }

    bool estaActiva() const {
        return filaActiva;
    }
};

#endif
