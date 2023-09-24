
// #include "tetris.cpp"

#ifndef MENU_H
#include "menu.hpp"
#endif

#ifndef TETRISMASMAS_H
#include "tetrisMasMas.hpp"
#endif

// Menu Principal.

MenuPrincipal::MenuPrincipal(Tetris *tetris_p)
{
    tetris_padre = tetris_p;
    cargarPantallaInicial();
    cursor.posicion.fila = FILA_PRIMERA_OPCION;
    cursor.posicion.columna = COLUMNA_CURSOR;
    cursor.pixel = PIXEL_CURSOR;
    actualizarPantallaMenu();
    opciones = {{{14, 20}, "Jugar"}, {{15, 20}, "Salir"}};
}

MenuPrincipal::~MenuPrincipal(){}

int MenuPrincipal::cicloMenu()
{
    int retorno;

    while (true)
    {
        actualizarPantallaMenu();
        tetris_padre->asignarPantalla(pantalla_menu);
        tetris_padre->mostrarPantalla();

        int tecla = getch();
        switch (tecla)
        {

        case 72: // Arriba
            moverCursor(3);
            break;

        case 80: // Abajo
            moverCursor(0);
            break;
        case 32: // Espacio
        case 13: // Enter
            switch (cursor.posicion.fila)
            {
            case 14: // Jugar
                retorno = 0;
                break;
            case 15: // Salir
                retorno = 1;
                break;
            }
            return retorno;
            break;
        }
    }
}

void MenuPrincipal::actualizarPantallaMenu()
{

    pantalla_menu = pantalla_inicial;

    pantalla_menu
        [cursor.posicion.fila]
        [cursor.posicion.columna] 
    =
    cursor.pixel;
}

void MenuPrincipal::moverCursor(int direccion)
{
    switch (direccion)
    {
    case 0: // Abajo
        if (cursor.posicion.fila < opciones[opciones.size() - 1].posicion.fila)
        {
            cursor.posicion.fila += 1;
        }
        else
        {
            cursor.posicion.fila = opciones[0].posicion.fila;
        }
        break;
    case 3: // Arriba

        if (cursor.posicion.fila > opciones[0].posicion.fila)
        {
            cursor.posicion.fila -= 1;
        }
        else
        {
            cursor.posicion.fila = opciones[opciones.size() - 1].posicion.fila;
        }
        break;
    }
}

void MenuPrincipal::cargarPantallaInicial()
{

    std::ifstream archivo;
    std::string linea;

    archivo.open(ARCHIVO_PANTALLA_MENU);

    if (archivo.fail())
    {
        std::cout << "[ERROR] No se pudo cargar el archivo "
                  << ARCHIVO_PANTALLA_MENU
                  << "\n";
        std::cout << "Presione cualquier tecla para salir."
                  << "\n";
        std::system("PAUSE>NUL");
        exit(1);
    }

    while (getline(archivo, linea))
    {
        pantalla_inicial.push_back(linea);
    }
}

// Pausa.

Pausa::Pausa(Tetris *tetris_p)
{
    tetris_padre = tetris_p;
    cargarPantallaInicial();
    cursor.posicion.fila = FILA_PRIMERA_OPCION;
    cursor.posicion.columna = COLUMNA_CURSOR;
    cursor.pixel = PIXEL_CURSOR;
    actualizarPantallaMenu();
    opciones = {{{14, 20}, "Volver"}, {{15, 20}, "Menu"}, {{16, 20}, "Salir"}};
}

Pausa::~Pausa(){}

void Pausa::actualizarPantallaMenu()
{

    pantalla_menu = pantalla_inicial;

    pantalla_menu
        [cursor.posicion.fila]
        [cursor.posicion.columna] 
    =
    cursor.pixel;
}

void Pausa::moverCursor(int direccion)
{
    switch (direccion)
    {
    case 0: // Abajo
        if (cursor.posicion.fila < opciones[opciones.size() - 1].posicion.fila)
        {
            cursor.posicion.fila += 1;
        }
        else
        {
            cursor.posicion.fila = opciones[0].posicion.fila;
        }
        break;
    case 3: // Arriba

        if (cursor.posicion.fila > opciones[0].posicion.fila)
        {
            cursor.posicion.fila -= 1;
        }
        else
        {
            cursor.posicion.fila = opciones[opciones.size() - 1].posicion.fila;
        }
        break;
    }
}

int Pausa::cicloMenu()
{

    int retorno;

    while (true)
    {
        actualizarPantallaMenu();
        tetris_padre->asignarPantalla(pantalla_menu);
        tetris_padre->mostrarPantalla();

        int tecla = getch();
        switch (tecla)
        {

        case 72: // Arriba
            moverCursor(3);
            break;

        case 80: // Abajo
            moverCursor(0);
            break;

        case 32: // Espacio    
        case 13: // Enter
            switch (cursor.posicion.fila)
            {
            case 14: // Volver
                retorno = 0;
                break;
            case 15: // Menu
                retorno = 1;
                break;
            case 16: // Salir
                retorno = 2;
                break;
            }
            return retorno;
            break;
        }
    }
}

void Pausa::cargarPantallaInicial()
{

    std::ifstream archivo;
    std::string linea;

    archivo.open(ARCHIVO_PANTALLA_PAUSA);

    if (archivo.fail())
    {
        std::cout << "[ERROR] No se pudo cargar el archivo "
                  << ARCHIVO_PANTALLA_PAUSA
                  << "\n";
        std::cout << "Presione cualquier tecla para salir."
                  << "\n";
        std::system("PAUSE>NUL");
        exit(1);
    }

    while (getline(archivo, linea))
    {
        pantalla_inicial.push_back(linea);
    }
}

// Fin.

Fin::Fin(Tetris *tetris_p)
{
    tetris_padre = tetris_p;
    cargarPantallaInicial();
    cursor.posicion.fila = FILA_PRIMERA_OPCION;
    cursor.posicion.columna = COLUMNA_CURSOR;
    cursor.pixel = PIXEL_CURSOR;
    actualizarPantallaMenu();
    opciones = {{{14, 20}, "Menu"}, {{15, 20}, "Salir"}};
}

Fin::~Fin(){}

int Fin::cicloMenu(int puntos)
{

    int retorno;

    std::stringstream puntos_ss;
    std::string puntos_str;

    std::ifstream archivo_maxpts;
    std::ofstream archivo_maxpts_trunc;
    std::stringstream maxpts_ss;
    std::string maxpts_str;
    int max_pts;
    
    puntos_ss << std::setw(6) << std::setfill('0') << puntos;
    puntos_str = puntos_ss.str();

    for (int i = 0; i < puntos_str.size(); i++)
    {
        pantalla_inicial
            [11]
            [27 + i] 
        =
        puntos_str[i];
    }

    
    archivo_maxpts.open(ARCHIVO_MAX_PTS);
    getline(archivo_maxpts,maxpts_str);
    max_pts = std::stoi(maxpts_str);
    archivo_maxpts.close();
    
    if (puntos>max_pts)
    {
        max_pts = puntos;
    }

    maxpts_ss << std::setw(6) << std::setfill('0') << max_pts;
    maxpts_str = maxpts_ss.str();
    
    archivo_maxpts_trunc.open(ARCHIVO_MAX_PTS,std::ofstream::trunc);
    archivo_maxpts_trunc <<  maxpts_str;
    archivo_maxpts_trunc.close();

    for (int i = 0; i < maxpts_str.size(); i++)
    {
        pantalla_inicial
            [23]
            [25 + i] 
        =
        maxpts_str[i];
    }

    while (true)
    {
        actualizarPantallaMenu();
        tetris_padre->asignarPantalla(pantalla_menu);
        tetris_padre->mostrarPantalla();        
        int tecla = getch();
        switch (tecla)
        {

        case 72: // Arriba
            moverCursor(3);
            break;

        case 80: // Abajo
            moverCursor(0);
            break;

        case 32: // Espacio 
        case 13: // Enter
            switch (cursor.posicion.fila)
            {
            case 14: // Menu
                retorno = 0;
                break;
            case 15: // Salir
                retorno = 1;
                break;
            }
            return retorno;
            break;
        }
    }
}

void Fin::actualizarPantallaMenu()
{

    pantalla_menu = pantalla_inicial;

    pantalla_menu
        [cursor.posicion.fila]
        [cursor.posicion.columna] 
    =
    cursor.pixel;
}

void Fin::moverCursor(int direccion)
{
    switch (direccion)
    {
    case 0: // Abajo
        if (cursor.posicion.fila < opciones[opciones.size() - 1].posicion.fila)
        {
            cursor.posicion.fila += 1;
        }
        else
        {
            cursor.posicion.fila = opciones[0].posicion.fila;
        }
        break;
    case 3: // Arriba

        if (cursor.posicion.fila > opciones[0].posicion.fila)
        {
            cursor.posicion.fila -= 1;
        }
        else
        {
            cursor.posicion.fila = opciones[opciones.size() - 1].posicion.fila;
        }
        break;
    }
}

void Fin::cargarPantallaInicial()
{

    std::ifstream archivo;
    std::string linea;

    archivo.open(ARCHIVO_PANTALLA_FIN);

    if (archivo.fail())
    {
        std::cout << "[ERROR] No se pudo cargar el archivo "
                  << ARCHIVO_PANTALLA_FIN
                  << "\n";
        std::cout << "Presione cualquier tecla para salir."
                  << "\n";
        std::system("PAUSE>NUL");
        exit(1);
    }

    while (getline(archivo, linea))
    {
        pantalla_inicial.push_back(linea);
    }
}