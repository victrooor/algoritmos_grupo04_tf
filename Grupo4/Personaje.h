#pragma once
#include <iostream>
using namespace System;

class Personaje {
protected:
    int x, y;
    std::string sprite;

public:
    Personaje(int px, int py, std::string spr) {
        x = px;
        y = py;
        sprite = spr; // el dibujo en ASCII
    }

    void mover(std::string direccion) {
        if (direccion == "arriba" && y > 0) y--;
        else if (direccion == "abajo" && y < 19) y++;
        else if (direccion == "izquierda" && x > 0) x--;
        else if (direccion == "derecha" && x < Console::WindowWidth - sprite.size()) x++; // para que sea alto de el inventario
    }

    void moverAleatorio() { // villano y aliado
        int dir = rand() % 4;
        if (dir == 0 && y > 0) y--;
        else if (dir == 1 && y < 19) y++;
        else if (dir == 2 && x > 0) x--;
        else if (dir == 3 && x < Console::WindowWidth - sprite.size()) x++; // alto del inventorio
    }


    void dibujar() {
        Console::SetCursorPosition(x, y);
        std::cout << sprite;
    }

    void borrar() {
        Console::SetCursorPosition(x, y);
        for (int i = 0; i < sprite.size(); i++) std::cout << " ";
    }

    int getX() { return x; }
    int getY() { return y; }
    std::string getSprite() { return sprite; }
};