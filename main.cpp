#include <iostream>
#include <vector>
#include "jugador.h"
#include "mazo.h"
#include "ronda.h"

using namespace std;

int main() {
    int numJugadores;
    cout << "Bienvenido a Coloretto. Ingresa el numero de jugadores (3-5): ";
    cin >> numJugadores;
    cin.ignore();

    if (numJugadores < 3 || numJugadores > 5) {
        cout << "Número de jugadores no válido. Debe ser entre 3 y 5." << endl;
        return 1;
    }

    vector<Jugador> jugadores(numJugadores);
    Mazo mazo;
    int turno = 0;
    int ronda = 0;

    while (!mazo.estaVacio()) {
        ronda += 1;
        cout << "Iniciamos la ronda #" << ronda << endl;

        Ronda ronda(numJugadores);
        vector<bool> jugadoresActivos(numJugadores, true); // Para verificar quién puede jugar

        while (!ronda.todasFilasInactiva()) {
            // Buscar al siguiente jugador activo
            while (!jugadoresActivos[turno]) {
                turno = (turno + 1) % numJugadores; // Pasar al siguiente jugador
            }

            Jugador& jugadorActual = jugadores[turno];
            cout << "Turno de " << jugadorActual.getNombre() << endl;
            ronda.mostrarFilas();

            // Verificación de cartas restantes para la notificación
            if (mazo.getNumeroCartas() <= 16 && mazo.getNumeroCartas() > 0) {
                cout << "¡Atención! Solo quedan " << mazo.getNumeroCartas() << " cartas en el mazo. ¡Esta es la última ronda! Prepárense para jugar sus últimas cartas." << endl;
            }

            // Verificar si el mazo ya está vacío
            if (mazo.getNumeroCartas() == 0) {
                cout << "\nNo quedan más cartas en el mazo." << endl;
                break; // Salimos del ciclo interno
            }

            if (ronda.todasFilasLlenas()) {
                cout << "Todas las filas están llenas. " << jugadorActual.getNombre() << " debe tomar una fila." << endl;
                int filaSeleccionada;
                do {
                    cout << "Selecciona una fila para tomar (1-" << numJugadores << "): ";
                    cin >> filaSeleccionada;
                } while (filaSeleccionada < 1 || filaSeleccionada > numJugadores || ronda.estaFilaTomada(filaSeleccionada - 1));

                // Tomar la fila seleccionada y marcarla como inactiva
                jugadorActual.tomarFila(ronda.obtenerFila(filaSeleccionada - 1));
                ronda.tomarFila(filaSeleccionada - 1); // Marca la fila como inactiva
                jugadoresActivos[turno] = false; // Desactiva al jugador que tomó la fila

            } else {
                int accion;
                cout << "Acción a realizar: (1) Jalar y colocar una carta, (2) Tomar una fila: ";
                cin >> accion;

                if (accion == 1) {
                    Carta carta = mazo.tomarCarta();
                    cout << "Has robado: " << carta.toString() << endl;

                    // Verifica si quedan 16 cartas después de robar
                    if (mazo.getNumeroCartas() <= 16 && mazo.getNumeroCartas() > 0) {
                        cout << "¡Atención! Solo quedan " << mazo.getNumeroCartas() << " cartas en el mazo. ¡Esta es la última ronda! Prepárense para jugar sus últimas cartas." << endl;
                    }

                    int filaSeleccionada;
                    do {
                        cout << "Selecciona una fila para colocar la carta (1-" << numJugadores << "): ";
                        cin >> filaSeleccionada;
                    } while (filaSeleccionada < 1 || filaSeleccionada > numJugadores || !ronda.agregarCartaAFila(filaSeleccionada - 1, carta));

                } else if (accion == 2) { // Acción para tomar una fila existente
                    if (ronda.todasFilasVacias()) { // Verifica si todas las filas están vacías
                        cout << "Todas las filas están vacías. Debes robar una carta primero." << endl;
                        Carta carta = mazo.tomarCarta();
                        cout << "Has robado: " << carta.toString() << endl;

                        // Verifica si quedan 16 cartas después de robar
                        if (mazo.getNumeroCartas() <= 16 && mazo.getNumeroCartas() > 0) {
                            cout << "¡Atención! Solo quedan " << mazo.getNumeroCartas() << " cartas en el mazo. ¡Esta es la última ronda! Prepárense para jugar sus últimas cartas." << endl;
                        }

                        int filaSeleccionada;
                        do {
                            cout << "Selecciona una fila para colocar la carta (1-" << numJugadores << "): ";
                            cin >> filaSeleccionada;
                        } while (filaSeleccionada < 1 || filaSeleccionada > numJugadores || !ronda.agregarCartaAFila(filaSeleccionada - 1, carta));

                    } else {
                        int filaSeleccionada;
                        bool filaTomada = false;

                        do {
                            cout << "Selecciona una fila para tomar (1-" << numJugadores << "): ";
                            cin >> filaSeleccionada;

                            // Verifica si la fila está vacía o ya ha sido tomada
                            if (filaSeleccionada < 1 || filaSeleccionada > numJugadores || ronda.estaFilaTomada(filaSeleccionada - 1)) {
                                std::cout << "La fila seleccionada está vacía o ya ha sido tomada. ¿Quieres jalar y colocar una carta en vez de tomar la fila? (1: Sí, 2: No): ";
                                int decision;
                                std::cin >> decision;
                                if (decision == 1) {
                                    Carta carta = mazo.tomarCarta();
                                    cout << "Has robado: " << carta.toString() << endl;

                                    // Verifica si quedan 16 cartas después de robar
                                    if (mazo.getNumeroCartas() <= 16 && mazo.getNumeroCartas() > 0) {
                                        cout << "¡Atención! Solo quedan " << mazo.getNumeroCartas() << " cartas en el mazo. ¡Esta es la última ronda! Prepárense para jugar sus últimas cartas." << endl;
                                    }

                                    do {
                                        cout << "Selecciona una fila para colocar la carta (1-" << numJugadores << "): ";
                                        cin >> filaSeleccionada;
                                    } while (filaSeleccionada < 1 || filaSeleccionada > numJugadores || !ronda.agregarCartaAFila(filaSeleccionada - 1, carta));

                                    filaTomada = true;
                                }
                            } else {
                                // Toma la fila seleccionada y marca como inactiva
                                jugadorActual.tomarFila(ronda.obtenerFila(filaSeleccionada - 1));
                                ronda.tomarFila(filaSeleccionada - 1); // Marca la fila como inactiva
                                jugadoresActivos[turno] = false; // Desactiva al jugador que tomó la fila
                                filaTomada = true;
                            }
                        } while (!filaTomada);
                    }
                }
            }

            // Pasar al siguiente jugador
            turno = (turno + 1) % numJugadores;
        }

        // Reiniciar el estado de jugadores para la siguiente ronda
        fill(jugadoresActivos.begin(), jugadoresActivos.end(), true);
    }

    // Muestra un mensaje de fin del mazo y pregunta si se desea ver la puntuación final
    cout << "\nNo quedan más cartas en el mazo. ¿Deseas ver la puntuación final? (1: Sí, 2: No): ";
    int verPuntuacion;
    cin >> verPuntuacion;

    if (verPuntuacion == 1) {
        // Calcular y mostrar la puntuación final de cada jugador
        cout << "\nCalculando puntuaciones..." << endl;
        for (auto& jugador : jugadores) {
            bool ladoPuntuacion;
            cout << "¿Deseas usar el lado café (1) o el lado violeta (0) para puntuar, " << jugador.getNombre() << "? ";
            cin >> ladoPuntuacion;

            int puntos = jugador.calcularPuntuacion(ladoPuntuacion);
            cout << "Puntos de " << jugador.getNombre() << ": " << puntos << endl;

            // Mostrar el mazo del jugador
            cout << "Cartas en la mano de " << jugador.getNombre() << ": " << endl;
            jugador.mostrarMano(); // Llamada para mostrar las cartas que tiene el jugador
        }
    } else {
        cout << "Juego terminado. ¡Gracias por jugar Coloretto!" << endl;
    }

    return 0;
}
