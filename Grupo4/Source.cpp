#include "conio.h"
#include "Jugador.h"
#include "Aliado.h"
#include "Villano.h"
#include "Recurso.h"
#include "Mapa.h"//tal vez reemplace con menu
#include <ctime>
using namespace std;


tipoMundo seleccion = Humano;
int main() {

    Mapa* mapa = new Mapa(seleccion);

    // mover aleatoirement :
    srand(time(NULL));

    Threading::Thread::Sleep(1000);
    // creacion de recursos :


    Console::CursorVisible = false;
    mapa->colocarRecursos();

    Jugador jugador(30, 30, "(^_^)");
    Aliado aliado(15, 10);
    Villano villano(30, 8, "{Xx}");


    int villanoAncho = villano.getSprite().size();

    Recurso diamante(rand() % 40, rand() % 15, 1);   // tipo 1 = aprender
    Recurso humanidad(rand() % 40, rand() % 15, 2);  // tipo 2 = humanidad
    Recurso luz(rand() % 40, rand() % 15, 3);        // tipo 3 = estabilidad


    bool jugando = true;
    while (jugando) {

        aliado.borrar();
        villano.borrar();

        aliado.moverAleatorio();
        villano.moverAleatorio();

        // dibujar los personajes
        jugador.dibujar();
        aliado.dibujar();
        villano.dibujar();

        // dibujar los recursos 
        if (diamante.estaActivo()) diamante.dibujarRecurso();
        if (humanidad.estaActivo()) humanidad.dibujarRecurso();
        if (luz.estaActivo()) luz.dibujarRecurso();

        // JUGADOR X RECURSO : -----------------------------------------------------
        // x Agua
        if (jugador.getX() == diamante.getX() && jugador.getY() == diamante.getY() && diamante.estaActivo()) {
            jugador.recoger("Agua");
            diamante.desaparecer();
        }

        // x Roca
        if (jugador.getX() == humanidad.getX() && jugador.getY() == humanidad.getY() && humanidad.estaActivo()) {
            jugador.recoger("Roca");
            humanidad.desaparecer();
        }

        // x Madera
        if (jugador.getX() == luz.getX() && jugador.getY() == luz.getY() && luz.estaActivo()) {
            jugador.recoger("Madera");
            luz.desaparecer();
        }

        if (jugador.getX() >= villano.getX() && jugador.getX() <= villano.getX() + villanoAncho && jugador.getY() == villano.getY()) {
            jugador.perdida_de_objetos();
        }

        // aparicion aleatoire de los recursos :
        if (!diamante.estaActivo() && rand() % 100 == 0) {
            diamante=Recurso(rand() % 40, rand() % 15, 1);
        }

        if (!humanidad.estaActivo() && rand() % 100 == 0) {
            humanidad= Recurso(rand() % 40, rand() % 15, 2);
        }

        if (!luz.estaActivo() && rand() % 100 == 0) {
            luz = Recurso(rand() % 40, rand() % 15, 3);
        }

        // CLAVIER = TECLADO -----------------------------------------------
        if (_kbhit()) {
            char c = _getch();
            jugador.borrar();
            if (c == 72) jugador.mover("arriba"); // flecha arriba
            if (c == 80) jugador.mover("abajo"); // flecha abajo
            if (c == 75) jugador.mover("izquierda"); // flecha izquierda
            if (c == 77) jugador.mover("derecha");// flecha derrecha
            if (c == 27) jugando = false; // salir : ESCAPE
        }

        jugador.mostrarInventario();
        _sleep(50);

    }
    return 0;
}



