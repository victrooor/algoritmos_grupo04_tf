	#pragma once
	#include <string>
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;



	ref class Personaje {
	protected:
		int x, y;
		String^ sprite;
		int columnas,filas;
		int indiceH;
		int indiceV;
		Bitmap^ personaje;
		int W;     
		int H;
	
	public:
		Graphics^ gr;
		Personaje(String^ sprite, int x, int y,int columnas, int filas):sprite(sprite), x(x), y(y), columnas(columnas), filas(filas), indiceH(0), indiceV(0) {
			personaje = gcnew Bitmap(sprite);
			W = personaje->Width / columnas;
			H = personaje->Height / filas;
		}
		~Personaje() {
		}

		virtual void mover(Keys t) {
			// Se implementa en clases derivadas
		}	

		void seleccionSprite(Graphics^ gr) { 
		

			int escala = 64;

			Rectangle destino(x, y, escala, escala);
			Rectangle origen(indiceH * W, indiceV * H, W, H);
		
			gr->DrawImage(personaje, destino, origen, GraphicsUnit::Pixel);
		}
	
		

	};
