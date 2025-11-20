#pragma once
#include "Personaje.h"
#include "Jugador.h"

class Villano : public Personaje {
public:
    Villano(int px, int py, std::string spr = "{Xx}") : Personaje(px, py, spr) {}

    void robar(Jugador* jugador) {
        System::Console::SetCursorPosition(0, 23);
        std::cout << "El villano te robo recursos!    ";
    }
};
