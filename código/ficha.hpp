#ifndef FICHA_H
#define FICHA_H

#ifndef TETRISMASMAS_H
#include "tetrisMasMas.hpp"
#endif


class tmm::Ficha
{
    public:
    private:
        Posicion posicion;
        MatrizDePixeles matriz;
        char tipo;

    public:
        Ficha(int tipo_de_ficha);
        ~Ficha();

        // Métodos de manipulación de la Ficha.

        bool chequearColision(int direccion, MatrizDePixeles tablero); // direccion : 0 = abajo, 1 = izquierda, 2 = derecha
        bool moverFicha(int direccion, MatrizDePixeles tablero);
        void rotarFicha(MatrizDePixeles tablero);

        // Métodos asignar_().

        void asignarPosicion(Posicion posicion_nueva);
        void asignarMatriz(std::vector<std::string> matriz_nueva);

        // Métodos devolver_().

        Posicion devolverPosicion();
        MatrizDePixeles devolverMatriz();
        char devolverTipo();


        //private: 
        void imprimirFicha(); // Método que imprime la ficha a consola. Sólo para proósitos de [DEBUG].

};

#endif