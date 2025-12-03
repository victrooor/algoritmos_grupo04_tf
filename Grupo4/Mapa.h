#pragma once
#include "Villano.h"
#include "PersonajePrincipal.h"
#include "Recurso.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class Mapa {
private:
    int x, y, W, H;
    Bitmap^ fondo;
    String^ rutaFondo;
    Villano^ antagonista;
    Villano^ cocodrilo;
    PersonajePrincipal^ protagonista;
    Keys t;
  
    
public:

    int ventanaW = 800;
    int ventanaH = 500;
    array<Recurso^>^ flores; //tener mas flores que aparecen
    Random^ aleatorio;

    int getWidthMapa() { return W; }
    int getHeightMapa() { return H; }
   
    Mapa(int x, int y, String^ rutaFondo,PersonajePrincipal^ protagonista)
        : x(x), y(y), rutaFondo(rutaFondo)
    {
        aleatorio = gcnew Random();
        this->protagonista = protagonista;
        fondo = gcnew Bitmap(rutaFondo);
        W = fondo->Width;
        H = fondo->Height;
        antagonista = gcnew Villano(50, 20, "sprites and backgrounds/Enemigo.png", W, H, 5, 4); 
        cocodrilo = gcnew Villano(60, 60, "sprites and backgrounds/cocodrilo.png", W, H, 3, 4);
        //flores = gcnew Recurso(aleatorio->Next(1, W-50),aleatorio->Next(1, H-50),"sprites and backgrounds/flores.png",3,1);
        flores = gcnew array<Recurso^>(3);
        for (int i = 0; i < flores->Length; i++) {
            int fx, fy;
            do {
                fx = aleatorio->Next(10, W - 60);
                fy = aleatorio->Next(10, H - 60);
                //verifier qu'aucune fleur ne spawn sur le joueur
            } while (Math::Abs(fx - protagonista->getX()) < 50 && Math::Abs(fy - protagonista->getY()) < 50);

            flores[i] = gcnew Recurso(fx, fy, "sprites and backgrounds/flores.png", 3, 1);
        }
        
        //diamantes=gcnew Recurso(int posicionX, int posicionY, String^ r,int columnas, int filas);
    }

    ~Mapa() {}

   
    void mostrarMapa(Graphics^ gr, Keys t) {
        antagonista->moverMurcielago(W, H);
        cocodrilo->moverCocodrilo(W, H);
        protagonista->mover(t);

        gr->DrawImage(fondo, x, y, W, H);
        antagonista->seleccionSprite(gr);
        protagonista->seleccionSprite(gr);
        for (int i = 0; i < flores->Length; i++)
            flores[i]->mostrarFlor(gr);
        cocodrilo->seleccionSprite(gr);
    }
    /*int Daño() { //esto deberia adaptarse al metodo verificarDerrota de Anjali
        
        bool col1 = protagonista->colision(antagonista);
        bool col2 = protagonista->colision(cocodrilo);

        if (col1 && !colisionMurcielago)
            contadorDaño++;

        colisionMurcielago = col1;

        if (col2 && !colisionCocodrilo)
            contadorDaño++;

        colisionCocodrilo = col2;

        return contadorDaño;
    }*/

    /*int Recolectar() {//esto tambien deberia adaptarse al metodo verificarDerrota 
        bool estaColisionandoflor = protagonista->colision(flores);
        if (estaColisionandoflor && !ColisionConFlor) {
            contadorFlores++;
        }
        ColisionConFlor = estaColisionandoflor;
        return contadorFlores;*/
        ////
        //bool estaColisionandoDiamante = protagonista->colision(diamantes);
        /*if (estaColisionandoDiamante && !enColisionConDiamante) {
            contadorDiamante++;
        }*/
        /*enColisionConDiamante = estaColisionandoDiamante;
        return contadorDiamantes;*/


    array<bool>^ Daño() {

        bool col1 = protagonista->colision(antagonista);
        bool col2 = protagonista->colision(cocodrilo);

        array<bool>^ resultado = gcnew array<bool>(2);
        resultado[0] = col1;
        resultado[1] = col2;

        return resultado;
    }

    bool Recolectar(int% indiceFlor) {
        for (int i = 0; i < flores->Length; i++) {
            if (protagonista->colision(flores[i])) {
                indiceFlor = i;
                return true;
            }
        }
        return false;
    }

    void moverEnemigos() {
        antagonista->moverMurcielago(W, H);
        cocodrilo->moverCocodrilo(W, H);
    }

    void moverJugador(array<bool>^ teclas) {

        if (teclas == nullptr) return;

        // 0=Haut, 1=Bas, 2=Gauche, 3=Droite
        if (teclas[0]) protagonista->mover(Keys::Up);
        if (teclas[1]) protagonista->mover(Keys::Down);
        if (teclas[2]) protagonista->mover(Keys::Left);
        if (teclas[3]) protagonista->mover(Keys::Right);
    }

    bool colisionMurcielago() {
        return protagonista->colision(antagonista);
    }

    bool colisionCocodrilo() {
        return protagonista->colision(cocodrilo);
    }

    int colisionFlor() {
        for (int i = 0; i < flores->Length; i++) {
            if (flores[i]->activo && protagonista->colision(flores[i])) {
                return i; 
            }
        }
        return -1; 
    }

    
};

