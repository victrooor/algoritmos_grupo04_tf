#pragma once
class Recurso {
    // srand(time(NULL));
private:
    int posx, posy;
    int formaDelRecurso;
    bool activo;

public:
    Recurso(int posx, int posy, int formaDelRecurso) :posx(posx), posy(posy), formaDelRecurso(formaDelRecurso) {

    }
    ~Recurso() {};
    void dibujarRecurso() {//posx y posy si esta tomando los valores asignados en el constructor Recurso

        switch (formaDelRecurso) {//Si el metodo no utiliza parametros con el mismo nombre que un atributo, pero si utiliza variables con mismo nombre de su atributo en la logica. Entonces si trabaja con el valor ingresado al  constructor 
        case 1:
            //diamante(aprender)
            Console::SetCursorPosition(posx, posy);
            std::cout << "/\\ " << std::endl;
            Console::SetCursorPosition(posx, posy + 1);
            std::cout << "\\/ " << std::endl;
            break;
        case 2:
            //flores(humanidad)
            Console::SetCursorPosition(posx, posy);
            std::cout << "@@@@" << std::endl;
            Console::SetCursorPosition(posx, posy + 1);
            std::cout << "/|\\" << std::endl;
            break;
        case 3:
            //fuentes de luz (estabilidad IA y hombre)
            Console::SetCursorPosition(posx, posy);
            std::cout << "\\|//" << std::endl;
            Console::SetCursorPosition(posx, posy + 1);
            std::cout << "-o-" << std::endl;
            break;
        }
        activo = true;
    }
    void desaparecer() {
        if (!activo) {
            return;
        }
        for (int i = 0; i <= 4; i++) {
            for (int j = 0; j < 2; j++) {
                Console::SetCursorPosition(posx + j, posy + i);
                std::cout << "    ";
            }
        }
        activo = false;
    }
    bool estaActivo() { return activo; }
    int getX() {
        return posx;
    }

    int getY() {
        return posy;
    }
};

