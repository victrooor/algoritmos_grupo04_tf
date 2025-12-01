#pragma once
#include <String>
using namespace System;
using namespace System::Drawing;
using namespace Windows::Forms;
ref class Recurso {
private:

	int posicionX, posicionY;
	String^ r;
	Bitmap^ recursos;
	int columnas, filas, escalaFrame;
	Random^ selector;
	int wFrame, hFrame;
public:
	Recurso(int posicionX, int posicionY, String^ r,int columnas, int filas):posicionX(posicionX), posicionY(posicionY),r(r),columnas(columnas),filas(filas) {
		selector = gcnew Random();
		recursos = gcnew Bitmap(r);
	}
	~Recurso() {
	}
	void mostrarFlor(Graphics^ gr) {
		escalaFrame = 64;
		wFrame = recursos->Width / columnas;
		hFrame = recursos->Height / filas;

		Rectangle destino(posicionX, posicionY, escalaFrame, escalaFrame);
		Rectangle origen(1 * wFrame, 0 * hFrame, wFrame, hFrame);
		gr->DrawImage(recursos, destino, origen, GraphicsUnit::Pixel);
	}
	void mostrarDiamante(Graphics^ gr){}

	Rectangle getBoundRecurso() {
		return Rectangle(posicionX, posicionY, wFrame, hFrame);
	}
}; 