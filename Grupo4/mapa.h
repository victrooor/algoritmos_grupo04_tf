#pragma once
#include <string>
#include <map>
#include <vector>
#include "Recurso.h"
#include "Personaje.h"
#include "Aliado.h"
#include "Villano.h"

const int ANCHO_MAPA = 80;
const int ALTO_MAPA = 25;

enum tipoMundo { IA, Humano, Colaborativo };
enum tipoObjetos { arbol, fabricas, microprocesador };

static std::map<tipoObjetos, std::vector<std::string>> formas = { //la variable es formas y el tipo de dato es std::map<tipoObjetos, std::vector<std::string>>. Esa lina indica que formas es un mapa asociativo (std::map) que realciona claves de tipo tipoObjetos con valores de tipo std::vector <std::string>
	{ arbol, {
		"  &&  ",
		" &&&& ",
		"&&&&&&",
		"  ||"
	}},
	{ fabricas, {
		" ~~~ ",
		"~~~~~",
		" | |",
		" | |",
	}},
	{ microprocesador, {
		"|--------------|",
		"│ 10010101010  │",
		"│ 10101010101  │",
		"|--------------|"
	}}
};



class Mapa {
private:
	std::string descripcion;
	std::vector <Recurso*>recursos;
	std::vector <Villano*>villanos;
	tipoObjetos objetotipo;
	tipoMundo tipo;
	std::string casa;

	bool ocupado[ANCHO_MAPA][ALTO_MAPA] = { false }; //me indica ocupacion

public:
	Mapa(tipoMundo tipomundo) :tipo(tipomundo) {
		srand(time(NULL));
		generarMapa();
	}
	~Mapa() { //esto se ejecuta automatico si el mapa se destruye (funciona al finalizar todo el juego), pero no a mitad del juego
		for (auto r : recursos)
			delete r;//liberas la memoria del objeto Recurso (desaparece del juego/pantalla si lo dibujabas).
		for (auto v : villanos)
			delete v;
	}
	void generarMapa() {
		int objetosPorZona = 2;
		switch (tipo) {
		case tipoMundo::Humano:
			for (int i = 0; i <= 10; i++) {
				// Generar árboles, animales, etc.
				descripcion = "Bosque verde y frondoso";
				objetotipo = arbol;
				dibujarObjeto(objetotipo, rand() % 40, rand() % 5);
			}
			break;

		case tipoMundo::IA:
			for (int i = 0; i <= 10; i++) {
				descripcion = "Ciudad gris y ruidosa";
				objetotipo = fabricas;
				dibujarObjeto(objetotipo, rand() % 40, rand() % 5);
			}
			break;

		case tipoMundo::Colaborativo:
			for (int i = 0; i <= 10; i++) {
				descripcion = "Desierto inmenso y árido";
				objetotipo = microprocesador;
				dibujarObjeto(objetotipo, rand() % 40, rand() % 5);
			}
			break;
		}

		// 🔹 Dividimos la pantalla en 4 cuadrantes
		int mitadAncho = ANCHO_MAPA / 2;
		int mitadAlto = ALTO_MAPA / 2;

		for (int zona = 0; zona < 4; zona++) {
			int xInicio = (zona % 2 == 0) ? 0 : mitadAncho;
			int yInicio = (zona < 2) ? 0 : mitadAlto;

			for (int i = 0; i < objetosPorZona; i++) {
				int x = xInicio + rand() % mitadAncho;
				int y = yInicio + rand() % mitadAlto;
				dibujarObjeto(objetotipo, x, y);
			}
		}
	}

	void dibujarObjeto(tipoObjetos tipo, int x, int y) {
		auto it = formas.find(tipo);
		if (it != formas.end()) {
			switch (tipo) {
			case tipoObjetos::arbol:
				Console::ForegroundColor = ConsoleColor::Green;
				break;
			case tipoObjetos::fabricas:
				Console::ForegroundColor = ConsoleColor::DarkGray;
				break;
			case tipoObjetos::microprocesador:
				Console::ForegroundColor = ConsoleColor::Yellow;
				break;
			default:
				Console::ForegroundColor = ConsoleColor::White;
				break;
			}

			int dy = 0;
			for (const auto& linea : it->second) {
				Console::SetCursorPosition(x, y + dy);
				std::cout << linea;

				for (int dx = 0; dx < (int)linea.size(); dx++) {
					int posX = x + dx;
					int posY = y + dy;
					if (posX >= 0 && posX < ANCHO_MAPA && posY >= 0 && posY < ALTO_MAPA) {
						ocupado[posX][posY] = true;
					}
				}
				dy++;
			}
		}
	}
	bool posicionLibre(int x, int y) {
		if (x < 0 || x >= ANCHO_MAPA || y < 0 || y >= ALTO_MAPA)
			return false;
		return !ocupado[x][y];
	}
	void colocarRecursos() {
		bool jugando = true;

		while (jugando) {
			int n = rand() % 5 + 1;
			int x, y;

			// Buscar posición libre
			do {
				x = rand() % ANCHO_MAPA;
				y = rand() % ALTO_MAPA;
			} while (!posicionLibre(x, y));/*genera coordenas dentro del mapa y vuelve a generar mientras la posion no esté  libre*/

			// Marcar posición como ocupada
			ocupado[x][y] = true;

			// Crear recurso y dibujarlo
			recursos.push_back(new Recurso(x, y, rand() % 3 + 1));
			for (auto r : recursos)
				r->dibujarRecurso();

			Threading::Thread::Sleep(1000);

			if (recursos.size() > 5) {
				Recurso* viejo = recursos.front();
				viejo->desaparecer();
				delete viejo;
				recursos.erase(recursos.begin());
			}
		}
	}
	void establecerPersonaje() {

	}
};

