#pragma once

#include <iostream>
using namespace System;

ref class GameManager {
public:
    int tiempoRestante;
    int vidas;
    int objetivoAgua;
    int objetivoMadera;
    int objetivoRoca;

    GameManager() {
        tiempoRestante = 300; //5 minutos
        vidas = 3;
        objetivoAgua = 50;
        objetivoMadera = 50;
        objetivoRoca = 5;
    }

    ~GameManager() {}

    void iniciarJuego() {
        tiempoRestante = 300;
        vidas = 3;
        Console::WriteLine("GameManager: juego iniciado.");
    }

    void actualizarTiempo(int dt = 1) {
        tiempoRestante -= dt;
        if (tiempoRestante < 0) tiempoRestante = 0;
    }

    bool verificarVictoria(int aguaActual, int maderaActual, int rocaActual) {
        return (aguaActual >= objetivoAgua &&
            maderaActual >= objetivoMadera &&
            rocaActual >= objetivoRoca);
    }

    bool verificarDerrota() {
        return (vidas <= 0 || tiempoRestante <= 0);
    }

    String^ getInfo() {
        return String::Format(
            "INFOS JUEGO : Objetivos -> Agua:{0} Madera:{1} Roca:{2} | Tiempo:{3} | Vidas:{4}",
            objetivoAgua, objetivoMadera, objetivoRoca, tiempoRestante, vidas
        );
    }
};
