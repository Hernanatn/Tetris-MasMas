
// Constructor y Destructor.

#include "tetris.cpp"

#ifndef JUEGO_H
#include "juego.hpp"
#endif

Juego::Juego(Tetris *tetris_p) 
{
    tetris_padre = tetris_p;
    pausa = new Pausa(tetris_padre);

    cargarPantallaInicial();

    nivel = 1;
    puntos = 0;
    filas_limpiadas = 0;

    actual = nullptr;
    proxima = nullptr;
    poblarColaDeFichas(10);
    avanzarCola();
    avanzarCola();

    actualizarPantallaTablero();
}

Juego::~Juego()
{
    while (!cola.empty())
    {
        delete actual;
        avanzarCola();
    }
    delete proxima;
    delete pausa;
}


// Ciclo de Juego
int Juego::cicloJuego()
{
    int retorno;
    actualizarPantallaJuego();
    tetris_padre->asignarPantalla(pantalla_juego);
    tetris_padre->mostrarPantalla();

    

    bool perdio = false;
    time_t tiempo_previo = time(NULL);

ciclo_de_juego:
    while (!perdio)
    {
        time_t tiempo = time(NULL);
        time_t tiempo_transcurrido = tiempo - tiempo_previo;
        tiempo_previo = tiempo;
        bool actual_llego_al_final = false;        
        
    ciclo_de_actual:
        while (!actual_llego_al_final)
        {
            while (!_kbhit())
            {

                actualizarPantallaTablero();
                actualizarPantallaJuego();
                tetris_padre->asignarPantalla(pantalla_juego);
                tetris_padre->mostrarPantalla();
                Sleep(400 / nivel - tiempo_transcurrido);
                if (actual->moverFicha(0, pantalla_tablero))
                {
                    congelarActual();
                    //avanzarCola();
                    actual_llego_al_final = true;
                    goto actual_choco;
                }
            }


            int tecla = getch();
            if (tecla == 224) // Si esa tecla es una flecja...
            {
                switch (getch())
                {
                case 72: // Arriba
                    actual->rotarFicha(pantalla_tablero);
                    break;
                case 80: // Abajo
                    if (actual->moverFicha(0, pantalla_tablero))
                    {
                        congelarActual();
                        actual_llego_al_final = true;
                        goto actual_choco;
                    }
                    break;
                case 75: // Izquierda
                    actual->moverFicha(1, pantalla_tablero);
                    break;

                case 77: // Derecha
                    actual->moverFicha(2, pantalla_tablero);
                    break;
                default:
                    break;
                }
            }
            else if (tecla == 32) // Si esa tecla es Espacio...
            {
                int contador_de_casillas_salteadas = 0;
                while (!actual->moverFicha(0, pantalla_tablero))
                {
                    contador_de_casillas_salteadas++;
                }
                sumarPuntos(2*contador_de_casillas_salteadas);
                congelarActual();
                actual_llego_al_final = true;
                goto actual_choco;
            }
            else if (tecla == 27) // Si esa tecla es ESC...
            {
                switch (pausa->cicloMenu())
                {
                case 0: // Volver
                    break;
                
                case 1: // Menu
                    return 1;
                    break;

                case 2: // Salir
                    return 2;
                    break;
                }
                
            }

        }
        actual_choco:
        limpiarFilas();
        poblarColaDeFichas(1);
        avanzarCola();

        for (int i = PRIMERA_COLUMNA_CANCHA; i <= ULTIMA_COLUMNA_CANCHA; i++)
        {
            char pixel = pantalla_tablero[PRIMERA_FILA_CANCHA][i];
            if (pixel == '#')
            {
                perdio = true;
            }
        }
    }
    
    return 0; 
    //std::system("PAUSE"); // DEBUG


}

// Cola de Fichas.

void Juego::poblarColaDeFichas(int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        srand(time(NULL)+i*i);
        int tipo_de_ficha = 1 + rand() % (8 - 1);
        Ficha *ficha = new Ficha(tipo_de_ficha);
        cola.push(ficha);
        Sleep(i*2);
    }
}

void Juego::avanzarCola()
{
    actual = proxima;
    proxima = cola.front();
    cola.pop();
}

// Pantallas.

void Juego::cargarPantallaInicial()
{
    
    std::ifstream archivo;
    std::string linea;

    archivo.open(ARCHIVO_PANTALLA_JUEGO);

    if (archivo.fail())
    {
        std::cout << "[ERROR] No se pudo cargar el archivo "
                  << ARCHIVO_PANTALLA_JUEGO
                  << "\n";
        std::cout << "Presione cualquier tecla para salir."
                  << "\n";
        std::system("PAUSE>NUL");
        exit(1);
    }

    while (getline(archivo, linea))
    {
        pantalla_tablero.push_back(linea);
    }

    pantalla_juego = pantalla_tablero;
}

void Juego::actualizarPantallaTablero()
{
    std::stringstream nivel_ss;
    std::stringstream puntos_ss;
    std::string nivel_str;
    std::string puntos_str;
    MatrizDePixeles matriz_proxima;

    nivel_ss << std::setw(4) << std::setfill('0') << nivel;
    nivel_str = nivel_ss.str();

    puntos_ss << std::setw(6) << std::setfill('0') << puntos;
    puntos_str = puntos_ss.str();

    matriz_proxima = proxima->devolverMatriz();

    for (int i = 0; i < nivel_str.size(); i++)
    {
        pantalla_tablero
            [PRIMER_DIGITO_NIVEL.fila]
            [PRIMER_DIGITO_NIVEL.columna + i] 
        =
        nivel_str[i];
    }

    for (int i = 0; i < puntos_str.size(); i++)
    {
        pantalla_tablero
            [PRIMER_DIGITO_PUNTOS.fila]
            [PRIMER_DIGITO_PUNTOS.columna + i] 
        =
        puntos_str[i];
    }

    for (int i = 0; i < matriz_proxima.size(); i++)
    {
        for (int j = 0; j < matriz_proxima[i].size(); j++)
        {
            pantalla_tablero
                [PRIMER_PIXEL_PROXIMA.fila + i]
                [PRIMER_PIXEL_PROXIMA.columna + j] 
            =
            matriz_proxima
                [i]
                [j];
        }
    }
}

void Juego::actualizarPantallaJuego()
{
    MatrizDePixeles matriz_actual;
    Posicion posicion_actual;
    
    char pixel;

    pantalla_juego = pantalla_tablero;

    if (!(actual == nullptr))
    {
        matriz_actual = actual->devolverMatriz();
        posicion_actual = actual->devolverPosicion();

        for (int i = 0; i < matriz_actual.size(); i++)
        {
            for (int j = 0; j < matriz_actual[i].size(); j++)
            {
                pixel = matriz_actual[i][j];

                if (pixel == '#')
                {
                    pantalla_juego
                        [posicion_actual.fila + i]
                        [posicion_actual.columna + j] 
                    =
                    matriz_actual
                        [i]
                        [j];
                }
            }
        }
    }
}


//Ficha actual.

void Juego::congelarActual()
{
    MatrizDePixeles matriz_actual;
    Posicion posicion_actual;
    char pixel;

    matriz_actual = actual->devolverMatriz();
    posicion_actual = actual->devolverPosicion();

    for (int i = 0; i < matriz_actual.size(); i++)
    {
        for (int j = 0; j < matriz_actual[i].size(); j++)
        {
            pixel = matriz_actual[i][j];

            if (pixel == '#')
            {
                pantalla_tablero
                    [posicion_actual.fila + i]
                    [posicion_actual.columna + j] 
                =
                matriz_actual
                    [i]
                    [j];
            }
        }
    }

    sumarPuntos(25);
    delete actual;

    actualizarPantallaTablero();
}

void Juego::limpiarFilas()
{
    char pixel_a_chequear;
    int contador_de_numerales;
    int contador_de_lineas = 0;

    ultima_fila:
    for (int i = (ULTIMA_FILA_CANCHA + 1); i-- > PRIMERA_FILA_CANCHA;)
    {
        contador_de_numerales = 0;
        for (int j = PRIMERA_COLUMNA_CANCHA; j <= ULTIMA_COLUMNA_CANCHA; j++)
        {
            pixel_a_chequear = pantalla_tablero[i][j];

            if (pixel_a_chequear != '#')
            {
                break;
            }
            else
            {
                contador_de_numerales++;
            }

            if (contador_de_numerales == ANCHO_CANCHA)
            {
                contador_de_lineas++;
                if (i != 3)
                {
                    for (int k = (i + 1); k-- > (PRIMERA_FILA_CANCHA + 1);)
                    {
                        for (int l = 0; l < ANCHO_CANCHA; l++)
                        {
                            pantalla_tablero[k][j-l] 
                            =
                            pantalla_tablero[k - 1][j-l];
                        }
                    }
                    goto ultima_fila;
                }
                else
                {
                    for (int m = 0; m < ANCHO_CANCHA; m++)
                    {    
                        pantalla_tablero[i][j - m] = ' ';
                    }               
                }
            }
        }
    }
    if (contador_de_lineas > 0)
    {
        int pts;
        switch(contador_de_lineas)
        {
            case 1:
                pts = 40;
                break;
            case 2:
                pts = 100;
                break;
            case 3:
                pts = 300;
                break;
            case 4:
                pts = 1200;
                break;
            default:
                pts = 40;
                break;
        }


        sumarPuntos((pts * nivel));
        filas_limpiadas += contador_de_lineas;
        if (filas_limpiadas >= nivel*10)
        {
            subirNivel();
        }
        actualizarPantallaTablero();
    }
}


// Puntos.

void Juego::sumarPuntos(int cantidad)
{
    puntos += cantidad;
}

void Juego::subirNivel()
{
    nivel++;
}

// Métodos devolver_()

MatrizDePixeles Juego::devolverPantallaJuego()
{
    return pantalla_juego;
}

int Juego::devolverPuntos()
{
    return puntos;
}