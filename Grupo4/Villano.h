	#pragma once
	#include "Personaje.h"
	ref class Villano :public Personaje {
	private:
		int limiteAncho,limiteAlto;
		int dx, dy;
		int anchoForm, altoForm;
		Random^ randomPos;
	public:
		Villano( int posx, int posy, String^ sprite, int anchoForm, int altoForm,int columnas,int filas) :Personaje(sprite, posx, posy,columnas,filas),dx(5),dy(5),anchoForm(anchoForm),altoForm(altoForm) {
			limiteAncho = anchoForm;
			limiteAlto = altoForm;
			randomPos = gcnew Random();
			
		}
		~Villano() {

		}
		Rectangle getBoundVillano() {
			return Rectangle(x, y, W, H);
		}
		virtual void moverMurcielago(int anchoEspacio,int altoEspacio) override{
			x += dx;
			y += dy;	
			
			if (x < 0 || x + 64 > limiteAncho) {
				
				dx *= -1;
			}
			indiceH = (indiceH + 1) % columnas;
			
			if (y < 0 || y + 64 > limiteAlto/2) {
				dy *= -1;
			}
			indiceV = (indiceV + 1) % filas;
		}
		virtual void moverCocodrilo(int anchoEspacio, int altoEspacio) override {

			x += dx;
			y = 400;

		
			indiceH = (indiceH + 1) % columnas; 

			
			if (x + W >= limiteAncho) {
				dx = -5;
				indiceV = 1; 
				indiceH = 0; 
			}

			if (x <= 0) {
				dx = 5;
				indiceV = 2; 
				indiceH = 0;
			}
		}

	};