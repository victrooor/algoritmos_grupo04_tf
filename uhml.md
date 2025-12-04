# Informe del Trabajo final 

## Diagrama de clases 

```mermaid

classDiagram
    class Mapa {
        -x : int
        -y : int
        -W : int
        -H : int
        -fondo : Bitmap
        -rutaFondo : String
        -murcielago : Villano
        -cocodrilo : Villano
        -protagonista : PersonajePrincipal
        -t : System::Windows::Keys
        -aletorio: Random
        +ventanaH: int
        +ventanaW: int

        +mostrarMapa(Graphics* gr, Keys t) : void
        +Recolectar() : bool
        +moverJugador(array<bool>^ teclas) : void
        +colisionMurcielago() : bool
        +colisionCocodrilo() : bool
        +colisionFlor() : bool
        +getWidthMapa() : int
        +getHeightMapa() : int
    }

    class Recursos {
        -posicionX : int
        -posicionY : int
        -r : String
        -recursos : Bitmap
        -columnas : int
        -filas : int
        -escalaFrame : int
        -selector : Random
        -wFrame : int
        -hFrame : int
        -activo : bool

        +mostrarFlor(Graphics* gr) : void
        +mostrarDiamante(Graphics* gr) : void
        +getBoundRecurso() : Rectangle
        +moverA(int nuevaX, int nuevaY) : void
    }

    class Personaje {
        -x : int
        -y : int
        -indiceH : int
        -indiceV : int
        -sprite : string
        -filas : int
        -columnas : int
        -personaje : Bitmap
        -W : int
        -H : int

        +mover(Keys t) : void {virtual}
        +seleccionSprite(Graphics^ gr) : void
    }

    class PersonajePrincipal {
        +mover(Keys t) : void {override}
        +colision(Villano* otroVillano) : bool
        +colision(Recurso* otroRecurso) : bool
    }

    class Villano {
        -limiteAlto : int
        -limiteAncho : int
        -anchoForm : int
        -altoForm : int
        -randomPos : Random

        +getBoundVillano() : Rectangle
        +moverMurcielago(int anchoEspacio, int altoEspacio) : void {override}
        +moverCocodrilo(int anchoEspacio, int altoEspacio) : void {override}
    }

    class Aliado {
        +ayudar() : void
    }

    class Menu {
        -titulo : string
        -opcionSeleccionada : int
        -gm : GameManager

        +mostrarOpciones() : void
        +seleccionarOpcion(int opc) : void
        +iniciarJuego() : void
        +mostrarInstrucciones() : void
        +salirJuego() : void
    }

    class GameManager {
        -tiempoRestante : int
        -vidas : int
        -objetivoAgua : int = 50
        -objetivoMadera : int = 50
        -objetivoRoca : int = 5

        +iniciarJuego() : void
        +actualizarTiempo() : void
        +verificarVictoria(int diamante, int flor) : bool
        +verificarTiempo() : bool
        +verificarDerrota() : bool
        +recolectar() : void
        +DanoCocodrilo(bool murcielago) : bool
        +getInfo() : string
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
