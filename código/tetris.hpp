#ifndef TETRIS_H
#define TETRIS_H

//#include "ficha.hpp"
//#include "menu.hpp"
#include "juego.hpp"

#ifndef MENU_H
#include "menu.hpp"
#endif

#ifndef TETRISMASMAS_H
#include "tetrisMasMas.hpp"
#endif


class tmm::Tetris
{
    public:
    private:
    Juego * juego;
    MenuPrincipal * menu;
    Fin * fin;
    MatrizDePixeles pantalla_renderizada;


    public:
    Tetris();
    ~Tetris();

    void iniciarTetris();
    void jugarTetris();

    void mostrarPantalla();

    void asignarPantalla(MatrizDePixeles pantalla_recibida);


    private:
    void cargarPantallaInicial();
    void cerrarTetris();
};

#endif

