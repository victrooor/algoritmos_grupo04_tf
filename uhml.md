# Informe del Trabajo final 

## Diagrama de clases 

```mermaid

classDiagram
    class Mapa {
        int x
        int y
        int W
        int H
        Bitmap fondo
        String rutaFondo
        Villano murcielago
        Villano cocodrilo
        PersonajePrincipal protagonista
        System::Windows::Keys t
        Random aleatorio
        int ventanaH
        int ventanaW

        void mostrarMapa(Graphics* gr, Keys t)
        bool Recolectar()
        void moverJugador(array~bool~ teclas)
        bool colisionMurcielago()
        bool colisionCocodrilo()
        bool colisionFlor()
        int getWidthMapa()
        int getHeightMapa()
    }

    class Recursos {
        int posicionX
        int posicionY
        String r
        Bitmap recursos
        int columnas
        int filas
        int escalaFrame
        Random selector
        int wFrame
        int hFrame
        bool activo

        void mostrarFlor(Graphics* gr)
        void mostrarDiamante(Graphics* gr)
        Rectangle getBoundRecurso()
        void moverA(int nuevaX, int nuevaY)
    }

    class Personaje {
        int x
        int y
        int indiceH
        int indiceV
        string sprite
        int filas
        int columnas
        Bitmap personaje
        int W
        int H

        void mover(Keys t) ~virtual~
        void seleccionSprite(Graphics gr)
    }

    class PersonajePrincipal {
        void mover(Keys t) ~override~
        bool colision(Villano otroVillano)
        bool colision(Recurso otroRecurso)
    }

    class Villano {
        int limiteAlto
        int limiteAncho
        int anchoForm
        int altoForm
        Random randomPos

        Rectangle getBoundVillano()
        void moverMurcielago(int anchoEspacio, int altoEspacio) ~override~
        void moverCocodrilo(int anchoEspacio, int altoEspacio) ~override~
    }

    class Aliado {
        void ayudar()
    }

    class Menu {
        string titulo
        int opcionSeleccionada
        GameManager gm

        void mostrarOpciones()
        void seleccionarOpcion(int opc)
        void iniciarJuego()
        void mostrarInstrucciones()
        void salirJuego()
    }

    class GameManager {
        int tiempoRestante
        int vidas
        int objetivoAgua = 50
        int objetivoMadera = 50
        int objetivoRoca = 5

        void iniciarJuego()
        void actualizarTiempo()
        bool verificarVictoria(int diamante, int flor)
        bool verificarTiempo()
        bool verificarDerrota()
        void recolectar()
        bool DanoCocodrilo(bool murcielago)
        string getInfo()
    }

    %% Relaciones
    Mapa "1" *-- "*" Recursos
    PersonajePrincipal "1" o-- "*" Recursos
    Mapa "1" *-- "*" Personaje
    Personaje <|-- PersonajePrincipal
    Personaje <|-- Villano
    Personaje <|-- Aliado
    Menu "1" *-- "1" GameManager
    GameManager "1" *-- "3" Mapa
    
    note for PersonajePrincipal "El diamante representa aprender, las flores representan humanidad y las fuentes de luz la estabilidad (IA y humano)"
