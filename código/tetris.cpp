// tetris.cpp

#include "tetris.hpp"

Tetris::Tetris(){}
Tetris::~Tetris()
{
    delete juego;
    delete menu;
    delete fin;

}

void Tetris::iniciarTetris()
{
    cargarPantallaInicial();
    mostrarPantalla();

    juego = new Juego(this); 

    menu = new MenuPrincipal(this); 
    fin = new Fin(this); 
    std::system("PAUSE>NUL");
}

void Tetris::jugarTetris()
{
    int pts_juego;

    goto menu_principal;

    menu_principal:
        switch(menu->cicloMenu())
        {
            case 0: // Jugar
                goto ciclo_juego;
                break;
            case 1: // Salir
                goto salir;
                break;
        }


    ciclo_juego:
        switch(juego->cicloJuego())
        {
            case 0: // Fin
                goto final;
                break;
            case 1: // Menu
                goto reiniciar;
                break;
            case 2: // Salir
                goto salir;
                break;
        }
        

    final:
        pts_juego = juego->devolverPuntos();
        switch(fin->cicloMenu(pts_juego))
        {
            case 0: // Menu
                goto reiniciar;
                break;
            case 1: // Salir
                goto salir;
                break;
        }    
    
    reiniciar:
        delete juego;
        juego = new Juego(this);
        goto menu_principal; 

    salir:
        return;

}

void Tetris::cargarPantallaInicial()
{
    std::ifstream archivo;
    std::string linea;

    archivo.open(ARCHIVO_PANTALLA_INICIAL);

    if (archivo.fail())
    {
        std::cout << "[ERROR] No se pudo cargar el archivo "
                  << ARCHIVO_PANTALLA_INICIAL
                  << "\n";
        std::cout << "Presione cualquier tecla para salir."
                  << "\n";
        std::system("PAUSE>NUL");
        exit(1);
    }

    while (getline(archivo, linea))
    {
        pantalla_renderizada.push_back(linea);
    }

}

void Tetris::asignarPantalla(MatrizDePixeles pantalla_recibida)
{
    pantalla_renderizada = pantalla_recibida;
}


void Tetris::mostrarPantalla()
{
    std::system("CLS");
    for (int fila = 0; fila < pantalla_renderizada.size(); fila++)
    {
        std::cout << pantalla_renderizada[fila]
                  << "\n";
    }

}