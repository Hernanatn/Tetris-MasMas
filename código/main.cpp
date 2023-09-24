
#ifndef TETRIS_H
#include "tetris.hpp"
#endif

#ifndef JUEGO_H
#include "juego.hpp"
#endif

#ifndef MENU_H
#include "menu.hpp"
#endif

#ifndef FICHA_H
#include "ficha.hpp"
#endif

#ifndef TETRISMASMAS_H
#include "tetrisMasMas.hpp"
#endif

#include "ficha.cpp"
#include "menu.cpp"
#include "juego.cpp"


int main()
{

    std::system("ECHO OFF");
    std::system("MODE 44,28");
    std::system("TITLE TETRIS++");

    Tetris tetris;
    tetris.iniciarTetris();
    tetris.jugarTetris();
    tetris.~Tetris();

    std::system("CLS");
    std::system("MODE 44,3");
    std::cout << "Ud. ha salido del juego\n"
              << "Presione cualquier tecla para salir.\n";

    std::system("PAUSE>NUL");
 
    return 0;
}