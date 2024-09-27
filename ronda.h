#ifndef RONDA_H
#define RONDA_H

#include <vector>
#include "fila.h"
#include "mazo.h"
#include <iostream>

using namespace std;

class Ronda {
private:
    vector<Fila> filas;
    int numFilas;

public:
    Ronda(int numJugadores) {
        numFilas = numJugadores;  // Número de filas igual al número de jugadores
        filas.resize(numFilas);   // Crear las filas
    }

    void mostrarFilas() const {
        for (int i = 0; i < numFilas; ++i) {
            cout << "Fila " << i + 1 << ": ";
            filas[i].mostrar();
        }
    }

    bool agregarCartaAFila(int filaIndex, const Carta& carta) {
        if (filaIndex >= 0 && filaIndex < numFilas && filas[filaIndex].estaActiva()) {
            return filas[filaIndex].agregarCarta(carta);  // Devuelve si la carta fue agregada exitosamente
        }
        return false;  // No se puede agregar carta
    }

    bool todasFilasLlenas() const {
        for (const auto& fila : filas) {
            if (!fila.estaLlena()) {
                return false;  // Si una fila no está llena, devolvemos false
            }
        }
        return true;  // Todas las filas están llenas
    }

    bool todasFilasVacias() const {
        for (const auto& fila : filas) {
            if (!fila.estaVacia()) {
                return false;  // Si una fila no está vacía, devolvemos false
            }
        }
        return true;  // Todas las filas están vacías
    }

    bool todasFilasInactiva() const {
        for (const auto& fila : filas) {
            if (fila.estaActiva()) {
                return false;  // Si una fila está activa, devolvemos falso
            }
        }
        return true;  // Todas las filas están inactivas
    }

    Fila& obtenerFila(int filaIndex) {
        return filas[filaIndex];
    }

    void tomarFila(int filaIndex) {
        if (filaIndex >= 0 && filaIndex < numFilas) {
            filas[filaIndex].tomarCartas(); // Marcar la fila como tomada
        }
    }

    bool estaFilaTomada(int filaIndex) const {
        return filaIndex >= 0 && filaIndex < numFilas && !filas[filaIndex].estaActiva();
    }
};

#endif
