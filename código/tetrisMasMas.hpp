#ifndef TETRISMASMAS_H
#define TETRISMASMAS_H

// Include de todas las librerías y tipos externos que utiliza Tetris++

#include <cstdlib>  // Librería estándar de C. Garantiza la declaración de [std::].
#include <iostream> // "Stream" de E/S estándar. [std::cout], [std::cin] | [std::endl].
#include <sstream>  // "Stream" de operación con cadenas de caracteres. [std::stringstream] | [std::str()].
#include <fstream>  // "Stream" de operación con archivos.  [std::fstream], [std::istream] | [std::open()], [std::getline()] y [std::close].
#include <iomanip>  // Librearía de manipulación de E/S. [std::setw()] y [std::setfill()].

#include <time.h> // Archivo de cabecera estándar de C de manipulación de tiempo . [time_t] [time()]

// Includes condicionados al Sistema Operativo para garantizar portabilidad.

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h> // Archivo de cabecera de Windows API. [Sleep()]
#include <conio.h>   // Archivo de cabecera de funciones de E/S por consola (WIN) . [_kbhit()],[getch()].
#else
#include <unistd.h>  // Archivo de cabecera de tipos y funciones estándar de Linux. [Sleep()],[usleep()]
#include <ncurses.h> // Archivo de cabecera de funciones de E/S por consola (UNI) . [nodelay()],[getch()]
#endif

// Plantillas de C++ utilizadas por Tetris++.

#include <vector>
#include <string>
#include <queue>
#include <map>


namespace tmm
{
    class Tetris;   // "tetris.h/cpp" 
    class Juego;    // "juego.h/cpp"
    class Ficha;    // "ficha.h/cpp"
    class Menu;     // "menu.h/cpp"


    struct Posicion // Coordenadas de posición. {int fila, int columna}.
    {
        int fila;
        int columna;
    };

    struct Cursor
    {
        Posicion posicion;
        char pixel;
    };

    struct Opcion
    {
        Posicion posicion;
        std::string accion;
    };
    
    typedef std::vector<std::string> MatrizDePixeles; // Vector de cadenas de caracteres.

    typedef std::queue<Ficha*> ColaDeFichas; // Cola FIFO de Objetos de clase tmm::Ficha.

    typedef std::vector<Opcion> ListaDeOpciones;

    

    // Definición de constantes. 
    
    //Rutas a los recursos del juego.

    const std::string ARCHIVO_PANTALLA_INICIAL  = "./recursos/pantallas/pantalla_inicial.txt" ;
    const std::string ARCHIVO_PANTALLA_JUEGO    = "./recursos/pantallas/pantalla_juego.txt"   ;
    const std::string ARCHIVO_PANTALLA_MENU     = "./recursos/pantallas/pantalla_menu.txt"    ;
    const std::string ARCHIVO_PANTALLA_PAUSA    = "./recursos/pantallas/pantalla_pausa.txt"   ;
    const std::string ARCHIVO_PANTALLA_FIN      = "./recursos/pantallas/pantalla_fin.txt"     ;
    const std::string ARCHIVO_MAX_PTS           = "./recursos/mxpt.txt"                       ;

    const std::string RUTA_FICHAS               = "./recursos/fichas/"              ;
    const std::string SUFIJO_FICHAS             = "_ficha.txt"                      ;


    // Diccionario de identificadores de tipo de ficha.
    std::map<int, char> DICCIONARIO_DE_FICHAS =            
    {
        {1, 'I'},
        {2, 'J'},
        {3, 'L'},
        {4, 'O'},
        {5, 'S'},
        {6, 'T'},
        {7, 'Z'},
    };  

    // Coordenadas del tablero.
    
    const int LARGO_CANCHA = 20;
    const int ANCHO_CANCHA = 10;

    const Posicion PRIMER_PIXEL_CANCHA  = {3,7}     ;
    const Posicion ULTIMO_PIXEL_CANCHA  = {22,16}   ;

    const Posicion PRIMER_PIXEL_PROXIMA = {9,31};

    const Posicion PRIMER_DIGITO_PUNTOS = {22,30}   ;
    const Posicion PRIMER_DIGITO_NIVEL  = {17,31}   ;

    const int PRIMERA_FILA_CANCHA       = PRIMER_PIXEL_CANCHA.fila        ;
    const int PRIMERA_COLUMNA_CANCHA    = PRIMER_PIXEL_CANCHA.columna     ;

    const int ULTIMA_FILA_CANCHA        = ULTIMO_PIXEL_CANCHA.fila        ;
    const int ULTIMA_COLUMNA_CANCHA     = ULTIMO_PIXEL_CANCHA.columna     ;

    // Coordenadas de los menús.

    const int FILA_PRIMERA_OPCION       = 14        ;
    const int COLUMNA_CURSOR            = 17        ;

    const char PIXEL_CURSOR             = '@'       ;
};

using namespace tmm;

#endif