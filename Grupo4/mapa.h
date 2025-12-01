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
    Recurso^ flores;
    Keys t;
    Random^ aleatorio;
    bool colisionMurcielago,ColisionConFlor, colisionCocodrilo;//Tambien en GameManger y agregar enColisionConDiamante
    //int contadorDiamantes; Esto tambien iria en GameManager
    int contadorFlores;//tambien en GameManager
    int contadorDaño;//variable que debe usar Anjali en GameManager para mostrar numero de colisiones de daño
public:

   
    Mapa(int x, int y, String^ rutaFondo,PersonajePrincipal^ protagonista)
        : x(x), y(y), rutaFondo(rutaFondo),contadorDaño(0),contadorFlores(0), colisionMurcielago(false), colisionCocodrilo(false), ColisionConFlor(false)
    {
        aleatorio = gcnew Random();
        this->protagonista = protagonista;
        fondo = gcnew Bitmap(rutaFondo);
        W = fondo->Width;
        H = fondo->Height;
        antagonista = gcnew Villano(50, 20, "imagenes/Enemigo.png", W, H, 5, 4); 
        cocodrilo = gcnew Villano(60, 60, "imagenes/cocodrilo.png", W, H, 3, 4);
        flores = gcnew Recurso(aleatorio->Next(1, W-50),aleatorio->Next(1, H-50),"imagenes/flores.png",3,1);
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
        flores->mostrarFlor(gr);
        cocodrilo->seleccionSprite(gr);
    }
    int Daño() { //esto deberia adaptarse al metodo verificarDerrota de Anjali
        
        bool col1 = protagonista->colision(antagonista);
        bool col2 = protagonista->colision(cocodrilo);

        if (col1 && !colisionMurcielago)
            contadorDaño++;

        colisionMurcielago = col1;

        if (col2 && !colisionCocodrilo)
            contadorDaño++;

        colisionCocodrilo = col2;

        return contadorDaño;
    }
    int Recolectar() {//esto tambien deberia adaptarse al metodo verificarDerrota 
        bool estaColisionandoflor = protagonista->colision(flores);
        if (estaColisionandoflor && !ColisionConFlor) {
            contadorFlores++;
        }
        ColisionConFlor = estaColisionandoflor;
        return contadorFlores;
        ////
        //bool estaColisionandoDiamante = protagonista->colision(diamantes);
        /*if (estaColisionandoDiamante && !enColisionConDiamante) {
            contadorDiamante++;
        }*/
        /*enColisionConDiamante = estaColisionandoDiamante;
        return contadorDiamantes;*/
    }

};

