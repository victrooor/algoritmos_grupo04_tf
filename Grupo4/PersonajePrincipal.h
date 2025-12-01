#pragma once
#include "Personaje.h"
#include "Villano.h"
#include "Recurso.h"
ref class PersonajePrincipal:public Personaje {
private:
	
    
public:
	PersonajePrincipal( int posx, int posy, String^ sprite,int columnas,int filas):Personaje (sprite, posx, posy, columnas, filas){// envio valores pox y posy a x e y que aun no existen y no funciona por eso
	}
	~PersonajePrincipal(){}
	void mostrar() {

	}


    // ---- Agregar GETTERS para evitar el error en MyForm ----
    int getX() { return this->x; }
    int getY() { return this->y; }
    void setY(int nuevoY) { y = nuevoY; }


    virtual void mover(Keys t)override {
        switch (t) {

        case Keys::Up:
            y -= 5;
            indiceV = 3;
            indiceH = (indiceH + 1) % columnas;
            break;

        case Keys::Down:
            y += 5;
            indiceV = 0;
            indiceH = (indiceH + 1) % columnas;
            break;

        case Keys::Left:
            x -= 5;
            indiceV = 1;
            indiceH = (indiceH + 1) % columnas;
            break;

        case Keys::Right:
            x += 5;
            indiceV = 2;
            indiceH = (indiceH + 1) % columnas;
            break;

        }
    }
    Rectangle getBoundProtagonista() {
        return Rectangle(x, y, W, H);
    }
    bool colision(Villano^ otroVillano) {
        return this->getBoundProtagonista().IntersectsWith(otroVillano->getBoundVillano());
    }
    bool colision(Recurso^ otroRecurso) {
        return this->getBoundProtagonista().IntersectsWith(otroRecurso->getBoundRecurso());
    }
  
};