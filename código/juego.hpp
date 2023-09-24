#ifndef JUEGO_H
#define JUEGO_H

#include "ficha.hpp"
#include "tetris.hpp"
#include "menu.hpp" 

#ifndef TETRISMASMAS_H
#include "tetrisMasMas.hpp"
#endif

class tmm::Juego
{
public:
    Tetris *tetris_padre;

private:
    ColaDeFichas cola;
    Ficha *actual;
    Ficha *proxima;

    MatrizDePixeles pantalla_juego;
    MatrizDePixeles pantalla_tablero;

    int nivel;
    int puntos;
    int filas_limpiadas;

    Pausa *pausa;

public:
    Juego(Tetris *tetris_p);
    ~Juego();

    // Ciclo principal del juego.
    int cicloJuego();

    int devolverPuntos();

private:
    // Carga el ARCHIVO_PANTALLA_JUEGO en pantalla_tablero y pantalla_juego.
    void cargarPantallaInicial();
    // Actualiza pantalla_juego a partir de del estado de pantalla_tablero y la ficha actual.
    void actualizarPantallaJuego();
    // Actualiza pantalla_tablero con las fichas ya "congeladas", la ficha próxima, el nivel y los puntos.
    void actualizarPantallaTablero();



    // Crea una cantidad determinada de nuevas fichas pseudoaleatorias y las agrega a la cola de fichas.
    void poblarColaDeFichas(int cantidad);
    // Cambia el puntero de actual por el de proxima, el de proxima por el de la primera ficha de la cola y la elimina de la cola.
    void avanzarCola();

    // Incorpora la matriz de la ficha actual a pantalla_tablero, la elimina. Llama a avanzarCola().
    void congelarActual();
    // Limpia las filas completas y hace "caer" a las filas superiores.
    void limpiarFilas();


    void sumarPuntos(int cantidad);
    void subirNivel();

    MatrizDePixeles devolverPantallaJuego();

};

#endif

