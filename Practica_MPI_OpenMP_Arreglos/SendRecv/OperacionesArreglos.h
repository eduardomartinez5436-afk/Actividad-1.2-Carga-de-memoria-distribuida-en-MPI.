#ifndef OPERACIONESARREGLOS_H
#define OPERACIONESARREGLOS_H

#include <string>

class OperacionesArreglos
{
public:

    void crearArregloMPI(
        int* arreglo,
        int cantidad,
        int posicionInicial,
        int valorInicial,
        const std::string& equipo,
        int procesoMPI,
        bool detallado
    );

    void sumar(
        int* arregloA,
        int* arregloB,
        long long* resultado,
        int cantidad,
        int posicionInicial,
        const std::string& equipo,
        int procesoMPI,
        bool detallado
    );

    void restar(
        int* arregloA,
        int* arregloB,
        long long* resultado,
        int cantidad,
        int posicionInicial,
        const std::string& equipo,
        int procesoMPI,
        bool detallado
    );

    void multiplicar(
        int* arregloA,
        int* arregloB,
        long long* resultado,
        int cantidad,
        int posicionInicial,
        const std::string& equipo,
        int procesoMPI,
        bool detallado
    );

    void cuadrado(
        int* arregloA,
        long long* resultado,
        int cantidad,
        int posicionInicial,
        const std::string& equipo,
        int procesoMPI,
        bool detallado
    );
};

#endif