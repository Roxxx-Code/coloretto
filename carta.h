#ifndef CARTA_H
#define CARTA_H
#include "colors.h"
#include <string>

using namespace std;

class Carta {
private:
    string color;
    string tipo; // Puede ser "color", "comodin", "+2", "ultimaRonda"

public:
    Carta(string c, string t = "color") : color(c), tipo(t) {}

    string obtenerColor() const {
        return color;
    }

    string obtenerTipo() const {
        return tipo;
    }

    string colorize(const string& text, const string& colorCode) const {
        return colorCode + text + RESET;
    }

    string toString() const {
        string resultado;
        if (tipo == "color") {
            if (color == "rojo") {
                resultado = colorize("Color (" + color + ")", RED); 
            } else if (color == "verde") {
                resultado = colorize("Color (" + color + ")", LGREEN); 
            } else if (color == "amarillo") {
                resultado = colorize("Color (" + color + ")", YELLOW); 
            } else if (color == "azul") {
                resultado = colorize("Color (" + color + ")", LBLUE); 
            } else if (color == "morado") {
                resultado = colorize("Color (" + color + ")", MAGENTA); 
            } else if (color == "marron") {
                resultado = colorize("Color (" + color + ")", BROWN); 
            } else if (color == "Naranjado") {
                resultado = colorize("Color (" + color + ")", ORANGE); 
            } else {
                resultado = "Color (" + color + ")";
            }
        } else if (tipo == "+2") {
            resultado = colorize("+2", BG_CYAN); 
        } else if (tipo == "comodin") {
            resultado = colorize("Comodín", BG_YELLOW); 
        } else if (tipo == "ultimaRonda") {
            resultado = colorize("Última Ronda", BG_RED); 
        }
        return resultado;
    }
};

#endif
