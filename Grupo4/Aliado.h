#pragma once
#include "Personaje.h"
#include "Jugador.h"

class Aliado : public Personaje {
public:
    Aliado(int px, int py, std::string spr = "{_}") : Personaje(px, py, spr) {

    }

    void ayudar(Jugador* jugador) {
        jugador->recoger("Madera");
        Console::SetCursorPosition(0, 22);
        std::cout << "El aliado te dio 1 de madera!";
    }
};