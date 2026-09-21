#include "OperacionesArreglos.h"

#include <iostream>
#include <omp.h>
#include <random>
#include <ctime>

using namespace std;


// =====================================================
// CREAR ARREGLO
// =====================================================

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

    int hilo = omp_get_thread_num();


    unsigned int semilla =
        (unsigned int)time(NULL)
        +
        procesoMPI * 10000
        +
        posicionInicial
        +
        hilo;


    mt19937 generador(semilla);


    uniform_int_distribution<int> distribucion(1,1000);



#pragma omp for
    for(int i = 0; i < cantidad; i++)
    {

        arreglo[i] = distribucion(generador);



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
                << posicionInicial+i
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



// =====================================================
// SUMA
// =====================================================

void OperacionesArreglos::sumar(
    int* A,
    int* B,
    long long* resultado,
    int cantidad,
    const string& equipo,
    int procesoMPI
)
{


#pragma omp parallel for
for(int i=0;i<cantidad;i++)
{

    resultado[i] =
        (long long)A[i]+B[i];

}


}



// =====================================================
// RESTA
// =====================================================

void OperacionesArreglos::restar(
    int* A,
    int* B,
    long long* resultado,
    int cantidad,
    const string& equipo,
    int procesoMPI
)
{


#pragma omp parallel for
for(int i=0;i<cantidad;i++)
{

    resultado[i] =
        (long long)A[i]-B[i];

}


}



// =====================================================
// MULTIPLICACION
// =====================================================

void OperacionesArreglos::multiplicar(
    int* A,
    int* B,
    long long* resultado,
    int cantidad,
    const string& equipo,
    int procesoMPI
)
{


#pragma omp parallel for
for(int i=0;i<cantidad;i++)
{

    resultado[i] =
        (long long)A[i]*B[i];

}


}




// =====================================================
// CUADRADO
// =====================================================

void OperacionesArreglos::cuadrado(
    int* A,
    long long* resultado,
    int cantidad,
    const string& equipo,
    int procesoMPI
)
{


#pragma omp parallel for
for(int i=0;i<cantidad;i++)
{

    resultado[i] =
        (long long)A[i]*A[i];

}


}
