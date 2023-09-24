#include "ficha.hpp"

Ficha::Ficha(int tipo_de_ficha)
{

    std::map<int, char>::iterator nombre_ficha;
    std::stringstream nombre_archivo_ss;
    std::string nombre_archivo;
    std::ifstream archivo;
    std::string linea;

    matriz.clear();

    // Asignación del tmm::Ficha::tipo a partir del tipo_de_ficha usando tmm::diccionario_de_fichas.
    nombre_ficha = DICCIONARIO_DE_FICHAS.find(tipo_de_ficha);
    tipo = nombre_ficha->second;

    // Definición del nombre de archivo a buscar para el tipo de ficha.
    nombre_archivo_ss << RUTA_FICHAS << tipo << SUFIJO_FICHAS;
    nombre_archivo = nombre_archivo_ss.str();
    
    // Manipulación del archivo en cuestión. 
    archivo.open(nombre_archivo);
    if (archivo.fail()) // Error de lectura.
    {
        std::cout << "[ERROR] No se pudo cargar el archivo: "
                  << nombre_archivo
                  << ".\n";
        std::cout << "Presione cualquier tecla para salir."
                  << "\n";
        std::system("PAUSE>NUL");

        exit(1);
    }

    
    while (std::getline(archivo, linea)) // Leer cada linea del archivo
    {
        matriz.push_back(linea); // Agregar cada línea a la matriz de la Ficha.
    }
    archivo.close();

    switch (tipo)
        {
        case 'Z':
        case 'T':
        case 'S':
        case 'O':
            posicion = {1, 10};
            break;
        case 'L':
        case 'J':
            posicion = {2, 10};
            break;

        case 'I':
            posicion = {3, 10};
            break;
        }
}

Ficha::~Ficha()
{
}

bool Ficha::moverFicha(int direccion, MatrizDePixeles tablero)
{
    Posicion posicion_vieja = this->devolverPosicion();
    Posicion posicion_nueva;
    bool ficha_llego_al_final;

    if(!(chequearColision(direccion,tablero)))
    {
        ficha_llego_al_final = false;

        switch (direccion)
        {
        case 0: // Abajo
            posicion_nueva = {posicion_vieja.fila + 1, posicion_vieja.columna};
            break;
        case 1: // Izquierda
            posicion_nueva = {posicion_vieja.fila, posicion_vieja.columna - 1};
            break;
        case 2: // Derecha
            posicion_nueva = {posicion_vieja.fila, posicion_vieja.columna + 1};
            break;
        default:
            posicion_nueva = posicion_vieja;
            break;
        }
        asignarPosicion(posicion_nueva);
    }
    else if (direccion == 0)
    {
        ficha_llego_al_final = true;
    }
    else
    {
        ficha_llego_al_final = false;
    }

    return ficha_llego_al_final;

}

bool Ficha::chequearColision(int direccion, MatrizDePixeles tablero)
{

    Posicion posicion_a_chequear;
    char pixel_ficha;
    char pixel_a_chequear;

    int contador_de_colisiones = 0;
    for (int i = 0; i < matriz.size(); i++)
    {
        for (int j = 0; j < matriz[i].size(); j++)
        {
            pixel_ficha = matriz[i][j];
            if (pixel_ficha == '#')
            {
                switch (direccion)
                {
                case 0: // Abajo    
                    posicion_a_chequear = {posicion.fila + i + 1, posicion.columna + j};
                    break;

                case 1: // Izquierda
                    posicion_a_chequear = {posicion.fila + i, posicion.columna + j - 1};
                    break;

                case 2: // Derecha
                    posicion_a_chequear = {posicion.fila + i, posicion.columna + j + 1};
                    break;

                case 3: // Rotacion
                    posicion_a_chequear = {posicion.fila + (4-1-j), posicion.columna + i}; // VER DE REEMPLAZAR NUMEROS MAGICOS
                    break;
                }

                pixel_a_chequear = tablero[posicion_a_chequear.fila][posicion_a_chequear.columna];

                if (pixel_a_chequear == '#' || pixel_a_chequear == '|' || pixel_a_chequear == '+')
                {
                    contador_de_colisiones++;
                }
            }
        }
    }

    return contador_de_colisiones > 0;
}

void Ficha::rotarFicha(MatrizDePixeles tablero)
{

    if (!chequearColision(3, tablero))
    {
        MatrizDePixeles matriz_nueva = matriz;
        int n = matriz.size();
        char pixel_temp;

        // Rotar Matriz
        for (int i = 0; i < n / 2; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                pixel_temp = matriz[i][j];
                matriz_nueva[i][j] = matriz[j][n - i - 1];
                matriz_nueva[j][n - i - 1] = matriz[n - i - 1][n - j - 1];
                matriz_nueva[n - i - 1][n - j - 1] = matriz[n - j - 1][i];
                matriz_nueva[n - j - 1][i] = pixel_temp;
            }
        }

        matriz = matriz_nueva;
    }
}


void Ficha::imprimirFicha()
{
    for (int fila = 0; fila < matriz.size(); fila++)
    {
        std::cout << matriz[fila]
                  << "\n";
    }

}



// Métodos asignar_()

void Ficha::asignarMatriz(MatrizDePixeles matriz_nueva)
{
    matriz = matriz_nueva;
}

void Ficha::asignarPosicion(Posicion posicion_nueva)
{
    posicion = posicion_nueva;
}


// Métodos devolver_()

Posicion Ficha::devolverPosicion()
{
    return posicion;
}

MatrizDePixeles Ficha::devolverMatriz()
{
    return matriz;
}

char Ficha::devolverTipo()
{
    return tipo;
}

