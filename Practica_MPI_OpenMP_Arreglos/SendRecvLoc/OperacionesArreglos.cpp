#include "OperacionesArreglos.h"

#include <iostream>
#include <omp.h>
#include <random>
#include <ctime>


using namespace std;



// ==================================================
// CREAR ARREGLO ALEATORIO
// ==================================================

void OperacionesArreglos::crearArregloMPI(
    int* arreglo,
    int cantidad,
    int posicionInicial,
    const string& equipo,
    int procesoMPI,
    bool detallado
)
{

    #pragma omp parallel
    {

        int hilo =
            omp_get_thread_num();


        /*
            La semilla cambia dependiendo de:
            - proceso MPI
            - hilo OpenMP
            - posicion inicial

            Esto evita que A y B sean iguales.
        */

        unsigned int semilla =
            (unsigned int)
            time(NULL)
            +
            procesoMPI * 10000
            +
            posicionInicial * 100
            +
            hilo;



        mt19937 generador(
            semilla
        );



        uniform_int_distribution<int> distribucion(
            1,
            1000000
        );



        #pragma omp for
        for(int i = 0; i < cantidad; i++)
        {

            arreglo[i] =
                distribucion(generador);



            if(detallado)
            {

                #pragma omp critical
                {

                    cout
                    << "[Equipo: "
                    << equipo
                    << "] "
                    << "[MPI: "
                    << procesoMPI
                    << "] "
                    << "[Hilo: "
                    << hilo
                    << "] "
                    << "[Posicion: "
                    << posicionInicial + i
                    << "] "
                    << "[Valor: "
                    << arreglo[i]
                    << "]"
                    << endl;

                }

            }

        }

    }

}



// ==================================================
// SUMA
// ==================================================

void OperacionesArreglos::sumar(
    int* arregloA,
    int* arregloB,
    long long* resultado,
    int cantidad
)
{

    #pragma omp parallel for
    for(int i=0;i<cantidad;i++)
    {

        resultado[i] =
            (long long)arregloA[i]
            +
            arregloB[i];

    }

}



// ==================================================
// RESTA
// ==================================================

void OperacionesArreglos::restar(
    int* arregloA,
    int* arregloB,
    long long* resultado,
    int cantidad
)
{

    #pragma omp parallel for
    for(int i=0;i<cantidad;i++)
    {

        resultado[i] =
            (long long)arregloA[i]
            -
            arregloB[i];

    }

}



// ==================================================
// MULTIPLICACION
// ==================================================

void OperacionesArreglos::multiplicar(
    int* arregloA,
    int* arregloB,
    long long* resultado,
    int cantidad
)
{

    #pragma omp parallel for
    for(int i=0;i<cantidad;i++)
    {

        resultado[i] =
            (long long)arregloA[i]
            *
            arregloB[i];

    }

}



// ==================================================
// CUADRADO
// ==================================================

void OperacionesArreglos::cuadrado(
    int* arregloA,
    long long* resultado,
    int cantidad
)
{

    #pragma omp parallel for
    for(int i=0;i<cantidad;i++)
    {

        resultado[i] =
            (long long)arregloA[i]
            *
            arregloA[i];

    }

}