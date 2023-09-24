#ifndef MENU_H
#define MENU_H

#include "tetris.hpp"

#ifndef TETRISMASMAS_H
#include "tetrisMasMas.hpp"
#endif

class MenuPrincipal
{
public:
    Tetris *tetris_padre;

private:
    MatrizDePixeles pantalla_inicial;
    MatrizDePixeles pantalla_menu;
    Cursor cursor;
    ListaDeOpciones opciones;

public:
    MenuPrincipal(Tetris *tetris_p);
    ~MenuPrincipal();
    int cicloMenu();

private:
    void actualizarPantallaMenu();
    void moverCursor(int direccion);
    void cargarPantallaInicial();
};

class Pausa
{
public:
    Tetris *tetris_padre;

private:
    MatrizDePixeles pantalla_inicial;
    MatrizDePixeles pantalla_menu;
    Cursor cursor;
    ListaDeOpciones opciones;

public:
    Pausa(Tetris *tetris_p);
    ~Pausa();
    int cicloMenu();

private:
    void actualizarPantallaMenu();
    void moverCursor(int direccion);
    void cargarPantallaInicial();
};

class Fin
{
public:
    Tetris *tetris_padre;

private:
    MatrizDePixeles pantalla_inicial;
    MatrizDePixeles pantalla_menu;
    Cursor cursor;
    ListaDeOpciones opciones;

public:
    Fin(Tetris *tetris_p);
    ~Fin();
    int cicloMenu(int puntos);

private:
    void actualizarPantallaMenu();
    void moverCursor(int direccion);
    void cargarPantallaInicial();
};

#endif
