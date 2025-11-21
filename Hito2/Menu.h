#pragma once
#include "GameManager.h"

using namespace System;

ref class Menu {
public:
    String^ titulo;
    int opcionSeleccionada;
    GameManager^ gm;

    Menu(String^ t) {
        titulo = t;
        opcionSeleccionada = -1;
        gm = nullptr;
    }

    void mostrarOpciones() {
        Console::WriteLine("-------- " + titulo + " --------");
        Console::WriteLine("1 - Start");
        Console::WriteLine("2 - Mostrar");
        Console::WriteLine("3 - Salir");
    }

    void seleccionarOpcion(int opc) {
        opcionSeleccionada = opc;
        switch (opc) {
        case 1: iniciarJuego(); break;
        case 2: mostrarInstrucciones(); break;
        case 3: salirJuego(); break;
        default:
            Console::WriteLine("Opción inválida");
            break;
        }
    }

    void iniciarJuego() {
        if (gm != nullptr)
            delete gm;

        gm = gcnew GameManager();
        gm->iniciarJuego();

        Console::WriteLine("Menu: juego iniciado.");
    }

    void mostrarInstrucciones() {
        Console::WriteLine("INFOS JUEGO : ");

        if (gm != nullptr) {
            // directement écrire la String^ :
            Console::WriteLine(gm->getInfo());
        }
        else {
            Console::WriteLine("Juego no iniciado todavía.");
        }
    }

    void salirJuego() {
        Console::WriteLine("Saliendo del juego...");
    }
};
