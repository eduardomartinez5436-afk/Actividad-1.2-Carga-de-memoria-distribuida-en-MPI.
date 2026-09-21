#include "OperacionesArreglos.h"

#include <iostream>
#include <omp.h>

using namespace std;


// =========================================
// CREAR ARREGLO
// =========================================

void OperacionesArreglos::crearArregloMPI(
    int* arreglo,
    int cantidad,
    int posicionInicial,
    int valorInicial,
    const string& equipo,
    int procesoMPI,
    bool detallado
)
{
    #pragma omp parallel for
    for (int i = 0; i < cantidad; i++)
    {
        int hilo = omp_get_thread_num();

        arreglo[i] =
            valorInicial +
            posicionInicial +
            i;

        if (detallado)
        {
            #pragma omp critical
            {
                cout
                    << "[Equipo: " << equipo << "] "
                    << "[Proceso MPI: " << procesoMPI << "] "
                    << "[Hilo OpenMP: " << hilo << "] "
                    << "[Posicion: " << posicionInicial + i << "] "
                    << "[Valor generado: " << arreglo[i] << "]"
                    << endl;
            }
        }
    }
}


// =========================================
// SUMA
// =========================================

void OperacionesArreglos::sumar(
    int* arregloA,
    int* arregloB,
    long long* resultado,
    int cantidad,
    int posicionInicial,
    const string& equipo,
    int procesoMPI,
    bool detallado
)
{
    #pragma omp parallel for
    for (int i = 0; i < cantidad; i++)
    {
        int hilo = omp_get_thread_num();

        resultado[i] =
            static_cast<long long>(arregloA[i]) +
            arregloB[i];

        if (detallado)
        {
            #pragma omp critical
            {
                cout
                    << "[Equipo: " << equipo << "] "
                    << "[Proceso MPI: " << procesoMPI << "] "
                    << "[Hilo OpenMP: " << hilo << "] "
                    << "[Posicion: " << posicionInicial + i << "] "
                    << "[Operacion: Suma] "
                    << arregloA[i]
                    << " + "
                    << arregloB[i]
                    << " = "
                    << resultado[i]
                    << endl;
            }
        }
    }
}


// =========================================
// RESTA
// =========================================

void OperacionesArreglos::restar(
    int* arregloA,
    int* arregloB,
    long long* resultado,
    int cantidad,
    int posicionInicial,
    const string& equipo,
    int procesoMPI,
    bool detallado
)
{
    #pragma omp parallel for
    for (int i = 0; i < cantidad; i++)
    {
        int hilo = omp_get_thread_num();

        resultado[i] =
            static_cast<long long>(arregloA[i]) -
            arregloB[i];

        if (detallado)
        {
            #pragma omp critical
            {
                cout
                    << "[Equipo: " << equipo << "] "
                    << "[Proceso MPI: " << procesoMPI << "] "
                    << "[Hilo OpenMP: " << hilo << "] "
                    << "[Posicion: " << posicionInicial + i << "] "
                    << "[Operacion: Resta] "
                    << arregloA[i]
                    << " - "
                    << arregloB[i]
                    << " = "
                    << resultado[i]
                    << endl;
            }
        }
    }
}


// =========================================
// MULTIPLICACION
// =========================================

void OperacionesArreglos::multiplicar(
    int* arregloA,
    int* arregloB,
    long long* resultado,
    int cantidad,
    int posicionInicial,
    const string& equipo,
    int procesoMPI,
    bool detallado
)
{
    #pragma omp parallel for
    for (int i = 0; i < cantidad; i++)
    {
        int hilo = omp_get_thread_num();

        resultado[i] =
            static_cast<long long>(arregloA[i]) *
            arregloB[i];

        if (detallado)
        {
            #pragma omp critical
            {
                cout
                    << "[Equipo: " << equipo << "] "
                    << "[Proceso MPI: " << procesoMPI << "] "
                    << "[Hilo OpenMP: " << hilo << "] "
                    << "[Posicion: " << posicionInicial + i << "] "
                    << "[Operacion: Multiplicacion] "
                    << arregloA[i]
                    << " * "
                    << arregloB[i]
                    << " = "
                    << resultado[i]
                    << endl;
            }
        }
    }
}


// =========================================
// CUADRADO
// =========================================

void OperacionesArreglos::cuadrado(
    int* arregloA,
    long long* resultado,
    int cantidad,
    int posicionInicial,
    const string& equipo,
    int procesoMPI,
    bool detallado
)
{
    #pragma omp parallel for
    for (int i = 0; i < cantidad; i++)
    {
        int hilo = omp_get_thread_num();

        resultado[i] =
            static_cast<long long>(arregloA[i]) *
            arregloA[i];

        if (detallado)
        {
            #pragma omp critical
            {
                cout
                    << "[Equipo: " << equipo << "] "
                    << "[Proceso MPI: " << procesoMPI << "] "
                    << "[Hilo OpenMP: " << hilo << "] "
                    << "[Posicion: " << posicionInicial + i << "] "
                    << "[Operacion: Cuadrado] "
                    << arregloA[i]
                    << "^2 = "
                    << resultado[i]
                    << endl;
            }
        }
    }
}