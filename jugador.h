#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm> // Para std::max_element
#include "carta.h"
#include "fila.h"

using namespace std;

class Jugador {
private:
    string nombre;
    vector<Carta> mano;
    int puntuacion;

    // Tabla de puntuación del lado café y violeta
    int calcularPuntuacionPorColor(int cantidad, bool ladoCafe) const {
        if (cantidad == 1) return 1;
        else if (cantidad == 2) return ladoCafe ? 3 : 4;
        else if (cantidad == 3) return ladoCafe ? 6 : 8;
        else if (cantidad == 4) return ladoCafe ? 10 : 7;
        else if (cantidad == 5) return ladoCafe ? 15 : 6;
        else if (cantidad >= 6) return ladoCafe ? 21 : 5;
        return 0;
    }

public:
    // Constructor que solicita el nombre del jugador
    Jugador() {
        cout << "Ingresa el nombre del jugador: ";
        cin >> nombre; // Obtener el nombre del jugador desde el teclado
        puntuacion = 0;
    }

    string getNombre() const {
        return nombre;
    }

    void tomarFila(Fila& fila) {
        vector<Carta> cartasFila = fila.tomarCartas();
        mano.insert(mano.end(), cartasFila.begin(), cartasFila.end());
    }

    void mostrarMano() const {
        cout << nombre << " tiene las siguientes cartas en mano: " << endl;
        for (const auto& carta : mano) {
            cout << carta.toString() << " | ";
        }
        cout << endl;
    }

    // Calcular puntuación según la tabla
    int calcularPuntuacion(bool ladoPuntuacion) {
        map<string, int> coloresContador;
        int puntosExtra = 0;

        // Contar cuántas cartas de cada color y cartas '+2'
        for (const auto& carta : mano) {
            if (carta.obtenerTipo() == "color") {
                coloresContador[carta.obtenerColor()]++;
            } else if (carta.obtenerTipo() == "+2") {
                puntosExtra += 2;
            }
        }

        // Calculamos los puntos por los colores
        vector<int> puntosColores;
        for (const auto& [color, cantidad] : coloresContador) {
            puntosColores.push_back(calcularPuntuacionPorColor(cantidad, ladoPuntuacion));
        }

        // Seleccionar los tres colores con mayor puntuación
        sort(puntosColores.rbegin(), puntosColores.rend()); // Ordenar en orden descendente

        // Sumar los mejores 3 colores (o menos si no hay 3 colores)
        int puntosColoresTotales = 0;
        for (int i = 0; i < min(3, (int)puntosColores.size()); ++i) {
            puntosColoresTotales += puntosColores[i];
        }

        puntuacion = puntosExtra + puntosColoresTotales;
        cout << "Puntuación de " << nombre << ": " << puntuacion << " puntos." << endl;
        
        return puntuacion; // Retornar la puntuación calculada
    }
};

#endif
