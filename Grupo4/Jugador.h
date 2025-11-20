#pragma once
#include "Personaje.h"

class Jugador : public Personaje {
private:
    int agua, madera, roca;

public:
    Jugador(int px, int py, std::string spr) : Personaje(px, py, spr) {
        agua = madera = roca = 0;
    }

    void recoger(std::string recurso) {
        if (recurso == "Agua") agua++;
        else if (recurso == "Madera") madera++;
        else if (recurso == "Roca") roca++;
    }

    void mostrarInventario() {
        Console::SetCursorPosition(0, 20);
        std::cout << "Agua: " << agua << "  Madera: " << madera << "  Roca: " << roca << "   ";
    }

    void perdida_de_objetos() {
        if (agua > 0) agua -= 1;
        if (madera > 0) madera -= 1;
        if (roca > 0) roca -= 1;
    }

    bool objetivoCumplido() {
        return (agua >= 50 && madera >= 50 && roca >= 50);
    }
};