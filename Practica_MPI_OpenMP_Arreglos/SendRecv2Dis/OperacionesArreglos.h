#ifndef OPERACIONES_ARREGLOS_H
#define OPERACIONES_ARREGLOS_H

#include <string>

using namespace std;

class OperacionesArreglos
{
public:

    void crearArregloMPI(
        int* arreglo,
        int cantidad,
        int posicionInicial,
        const string& nombreEquipo,
        int procesoMPI,
        bool detallado
    );

    void sumar(
        int* arregloA,
        int* arregloB,
        long long* resultado,
        int cantidad,
        const string& nombreEquipo,
        int procesoMPI
    );

    void restar(
        int* arregloA,
        int* arregloB,
        long long* resultado,
        int cantidad,
        const string& nombreEquipo,
        int procesoMPI
    );

    void multiplicar(
        int* arregloA,
        int* arregloB,
        long long* resultado,
        int cantidad,
        const string& nombreEquipo,
        int procesoMPI
    );

    void cuadrado(
        int* arregloA,
        long long* resultado,
        int cantidad,
        const string& nombreEquipo,
        int procesoMPI
    );
};

#endif
