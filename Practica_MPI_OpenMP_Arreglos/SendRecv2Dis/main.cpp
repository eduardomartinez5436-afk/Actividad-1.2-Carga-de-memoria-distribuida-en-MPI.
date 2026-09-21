#include <iostream>
#include <mpi.h>
#include <omp.h>

#include "OperacionesArreglos.h"

using namespace std;


// ============================================================
// MOSTRAR PRIMEROS Y ULTIMOS ELEMENTOS DE UN INT
// ============================================================

void mostrarArregloInt(
    int* arreglo,
    int cantidad
)
{
    const int MOSTRAR = 20;

    cout << "Primeros "
        << MOSTRAR
        << " elementos: ";

    for (int i = 0; i < MOSTRAR; i++)
    {
        cout << arreglo[i] << " ";
    }

    cout << endl;

    cout << "Ultimos "
        << MOSTRAR
        << " elementos: ";

    for (
        int i = cantidad - MOSTRAR;
        i < cantidad;
        i++
        )
    {
        cout << arreglo[i] << " ";
    }

    cout << endl;
}


// ============================================================
// MOSTRAR PRIMEROS Y ULTIMOS ELEMENTOS LONG LONG
// ============================================================

void mostrarResultado(
    long long* arreglo,
    int cantidad
)
{
    const int MOSTRAR = 20;

    cout << "Primeros "
        << MOSTRAR
        << " elementos: ";

    for (int i = 0; i < MOSTRAR; i++)
    {
        cout << arreglo[i] << " ";
    }

    cout << endl;

    cout << "Ultimos "
        << MOSTRAR
        << " elementos: ";

    for (
        int i = cantidad - MOSTRAR;
        i < cantidad;
        i++
        )
    {
        cout << arreglo[i] << " ";
    }

    cout << endl;
}


// ============================================================
// MOSTRAR INFORMACION DEL TRABAJADOR
// ============================================================

void mostrarInformacionTrabajador(
    const char* nombreEquipo,
    int procesoMPI,
    int inicio,
    int fin,
    const char* operacion
)
{
    cout << endl;

    cout << "------------------------------------------------------------"
        << endl;

    cout << "EQUIPO: "
        << nombreEquipo
        << endl;

    cout << "PROCESO MPI: "
        << procesoMPI
        << endl;

    cout << "OPERACION: "
        << operacion
        << endl;

    cout << "SECCION DEL ARREGLO: "
        << inicio
        << " - "
        << fin
        << endl;

    cout << "ELEMENTOS PROCESADOS: "
        << fin - inicio + 1
        << endl;

    cout << "HILOS OPENMP DISPONIBLES: "
        << omp_get_max_threads()
        << endl;

    cout << "------------------------------------------------------------"
        << endl;
}


// ============================================================
// MAIN
// ============================================================

int main(
    int argc,
    char* argv[]
)
{
    MPI_Init(
        &argc,
        &argv
    );


    // ========================================================
    // INFORMACION MPI
    // ========================================================

    int procesoMPI;

    int totalProcesos;


    MPI_Comm_rank(
        MPI_COMM_WORLD,
        &procesoMPI
    );


    MPI_Comm_size(
        MPI_COMM_WORLD,
        &totalProcesos
    );


    // ========================================================
    // NOMBRE DEL EQUIPO
    // ========================================================

    char nombreEquipo[MPI_MAX_PROCESSOR_NAME];

    int longitud;


    MPI_Get_processor_name(
        nombreEquipo,
        &longitud
    );


    // ========================================================
    // CONFIGURACION
    // ========================================================

    const int TAMANIO =
        4000000;


    const int TRABAJADORES =
        2;


    const int CANTIDAD_LOCAL =
        TAMANIO / TRABAJADORES;


    bool detallado =
        false;


    // ========================================================
    // VALIDAR PROCESOS
    // ========================================================

    if (totalProcesos != 3)
    {
        if (procesoMPI == 0)
        {
            cout << endl;

            cout
                << "ERROR"
                << endl;

            cout
                << "Se necesitan exactamente 3 procesos MPI:"
                << endl;

            cout
                << "1 proceso maestro + 2 procesos trabajadores."
                << endl;
        }

        MPI_Finalize();

        return 0;
    }


    // ========================================================
    // OBJETO
    // ========================================================

    OperacionesArreglos operaciones;


    // ========================================================
    // INFORMACION INICIAL
    // ========================================================

    cout << endl;

    cout
        << "============================================================"
        << endl;

    cout
        << "          EJECUCION DISTRIBUIDA MPI + OPENMP"
        << endl;

    cout
        << "============================================================"
        << endl;

    cout
        << "Equipo: "
        << nombreEquipo
        << endl;

    cout
        << "Proceso MPI: "
        << procesoMPI
        << endl;


    if (procesoMPI == 0)
    {
        cout
            << "Rol: MAESTRO"
            << endl;
    }
    else
    {
        cout
            << "Rol: TRABAJADOR"
            << endl;
    }


    cout
        << "Total procesos MPI: "
        << totalProcesos
        << endl;

    cout
        << "Tamano total: "
        << TAMANIO
        << " elementos"
        << endl;

    cout
        << "Hilos OpenMP disponibles: "
        << omp_get_max_threads()
        << endl;


    if (procesoMPI != 0)
    {
        int inicio =
            (procesoMPI - 1)
            *
            CANTIDAD_LOCAL;

        int fin =
            inicio
            +
            CANTIDAD_LOCAL
            -
            1;

        cout
            << "Seccion asignada: "
            << inicio
            << " - "
            << fin
            << endl;

        cout
            << "Elementos asignados: "
            << CANTIDAD_LOCAL
            << endl;
    }


    cout
        << "============================================================"
        << endl;


    MPI_Barrier(
        MPI_COMM_WORLD
    );


    // ========================================================
    // VARIABLES
    // ========================================================

    int opcion = 0;

    int arreglosCreados = 0;


    int* arregloA =
        nullptr;

    int* arregloB =
        nullptr;


    // ========================================================
    // MEMORIA DEL MAESTRO
    // ========================================================

    if (procesoMPI == 0)
    {
        arregloA =
            new int[TAMANIO];

        arregloB =
            new int[TAMANIO];
    }


    // ========================================================
    // MENU PRINCIPAL
    // ========================================================

    do
    {
        if (procesoMPI == 0)
        {
            cout << endl;

            cout
                << "========================================"
                << endl;

            cout
                << "       MPI + OPENMP ARREGLOS GRANDES"
                << endl;

            cout
                << "========================================"
                << endl;

            cout
                << "Elementos: "
                << TAMANIO
                << endl;

            cout << endl;

            cout
                << "1. Crear arreglos A y B"
                << endl;

            cout
                << "2. Sumar"
                << endl;

            cout
                << "3. Restar"
                << endl;

            cout
                << "4. Multiplicar"
                << endl;

            cout
                << "5. Cuadrado de A"
                << endl;

            cout
                << "6. Salir"
                << endl;

            cout << endl;

            cout
                << "Opcion: ";

            cin
                >> opcion;
        }


        // ====================================================
        // ENVIAR OPCION A TODOS
        // ====================================================

        MPI_Bcast(
            &opcion,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD
        );


        // ====================================================
        // OPCION 1
        // CREAR ARREGLOS
        // ====================================================

        if (opcion == 1)
        {
            if (procesoMPI == 0)
            {
                cout << endl;

                cout
                    << "Creando arreglos..."
                    << endl;


                double inicio =
                    MPI_Wtime();


                // ------------------------------------------------
                // ENVIAR POSICIONES A
                // ------------------------------------------------

                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicionInicial =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Send(
                        &posicionInicial,
                        1,
                        MPI_INT,
                        trabajador,
                        100,
                        MPI_COMM_WORLD
                    );
                }


                // ------------------------------------------------
                // RECIBIR A
                // ------------------------------------------------

                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicionInicial =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Recv(
                        arregloA + posicionInicial,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        200,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                // ------------------------------------------------
                // ENVIAR POSICIONES B
                // ------------------------------------------------

                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicionInicial =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Send(
                        &posicionInicial,
                        1,
                        MPI_INT,
                        trabajador,
                        300,
                        MPI_COMM_WORLD
                    );
                }


                // ------------------------------------------------
                // RECIBIR B
                // ------------------------------------------------

                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicionInicial =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Recv(
                        arregloB + posicionInicial,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        400,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                double fin =
                    MPI_Wtime();


                cout << endl;

                cout
                    << "Arreglos creados correctamente."
                    << endl;


                cout
                    << "Tiempo creacion: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                cout << endl;

                cout
                    << "ARREGLO A"
                    << endl;

                mostrarArregloInt(
                    arregloA,
                    TAMANIO
                );


                cout << endl;

                cout
                    << "ARREGLO B"
                    << endl;

                mostrarArregloInt(
                    arregloB,
                    TAMANIO
                );


                arreglosCreados =
                    1;
            }
            else
            {
                // ==============================================
                // CREAR A
                // ==============================================

                int posicionInicial;


                MPI_Recv(
                    &posicionInicial,
                    1,
                    MPI_INT,
                    0,
                    100,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int* localA =
                    new int[CANTIDAD_LOCAL];


                operaciones.crearArregloMPI(
                    localA,
                    CANTIDAD_LOCAL,
                    posicionInicial,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    localA,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    200,
                    MPI_COMM_WORLD
                );


                delete[] localA;


                // ==============================================
                // CREAR B
                // ==============================================

                MPI_Recv(
                    &posicionInicial,
                    1,
                    MPI_INT,
                    0,
                    300,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int* localB =
                    new int[CANTIDAD_LOCAL];


                operaciones.crearArregloMPI(
                    localB,
                    CANTIDAD_LOCAL,
                    posicionInicial + 5000000,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    localB,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    400,
                    MPI_COMM_WORLD
                );


                delete[] localB;
            }
        }


        // ====================================================
        // SINCRONIZAR ARREGLOS CREADOS
        // ====================================================

        MPI_Bcast(
            &arreglosCreados,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD
        );


        // ====================================================
        // VALIDAR
        // ====================================================

        if (
            opcion >= 2 &&
            opcion <= 5 &&
            arreglosCreados == 0
            )
        {
            if (procesoMPI == 0)
            {
                cout << endl;

                cout
                    << "Primero debes crear los arreglos "
                    << "con la opcion 1."
                    << endl;
            }

            MPI_Barrier(
                MPI_COMM_WORLD
            );

            continue;
        }


        // ====================================================
        // OPCION 2 - SUMAR
        // ====================================================

        if (opcion == 2)
        {
            MPI_Barrier(
                MPI_COMM_WORLD
            );


            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();


                // ENVIAR

                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Send(
                        arregloA + posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        500,
                        MPI_COMM_WORLD
                    );


                    MPI_Send(
                        arregloB + posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        501,
                        MPI_COMM_WORLD
                    );
                }


                // RECIBIR

                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Recv(
                        resultado + posicion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        502,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                double fin =
                    MPI_Wtime();


                cout << endl;

                cout
                    << "Resultado suma:"
                    << endl;

                mostrarResultado(
                    resultado,
                    TAMANIO
                );


                cout
                    << "Tiempo suma: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }
            else
            {
                int* localA =
                    new int[CANTIDAD_LOCAL];

                int* localB =
                    new int[CANTIDAD_LOCAL];

                long long* resultado =
                    new long long[CANTIDAD_LOCAL];


                MPI_Recv(
                    localA,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    500,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                MPI_Recv(
                    localB,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    501,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int inicio =
                    (procesoMPI - 1)
                    *
                    CANTIDAD_LOCAL;

                int fin =
                    inicio
                    +
                    CANTIDAD_LOCAL
                    -
                    1;


                mostrarInformacionTrabajador(
                    nombreEquipo,
                    procesoMPI,
                    inicio,
                    fin,
                    "SUMA"
                );


                operaciones.sumar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL,
                    nombreEquipo,
                    procesoMPI
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    502,
                    MPI_COMM_WORLD
                );


                delete[] localA;
                delete[] localB;
                delete[] resultado;
            }
        }


        // ====================================================
        // OPCION 3 - RESTAR
        // ====================================================

        if (opcion == 3)
        {
            MPI_Barrier(
                MPI_COMM_WORLD
            );


            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();


                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Send(
                        arregloA + posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        600,
                        MPI_COMM_WORLD
                    );


                    MPI_Send(
                        arregloB + posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        601,
                        MPI_COMM_WORLD
                    );
                }


                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Recv(
                        resultado + posicion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        602,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                double fin =
                    MPI_Wtime();


                cout << endl;

                cout
                    << "Resultado resta:"
                    << endl;

                mostrarResultado(
                    resultado,
                    TAMANIO
                );


                cout
                    << "Tiempo resta: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }
            else
            {
                int* localA =
                    new int[CANTIDAD_LOCAL];

                int* localB =
                    new int[CANTIDAD_LOCAL];

                long long* resultado =
                    new long long[CANTIDAD_LOCAL];


                MPI_Recv(
                    localA,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    600,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                MPI_Recv(
                    localB,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    601,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int inicio =
                    (procesoMPI - 1)
                    *
                    CANTIDAD_LOCAL;

                int fin =
                    inicio
                    +
                    CANTIDAD_LOCAL
                    -
                    1;


                mostrarInformacionTrabajador(
                    nombreEquipo,
                    procesoMPI,
                    inicio,
                    fin,
                    "RESTA"
                );


                operaciones.restar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL,
                    nombreEquipo,
                    procesoMPI
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    602,
                    MPI_COMM_WORLD
                );


                delete[] localA;
                delete[] localB;
                delete[] resultado;
            }
        }


        // ====================================================
        // OPCION 4 - MULTIPLICACION
        // ====================================================

        if (opcion == 4)
        {
            MPI_Barrier(
                MPI_COMM_WORLD
            );


            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();


                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Send(
                        arregloA + posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        700,
                        MPI_COMM_WORLD
                    );


                    MPI_Send(
                        arregloB + posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        701,
                        MPI_COMM_WORLD
                    );
                }


                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Recv(
                        resultado + posicion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        702,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                double fin =
                    MPI_Wtime();


                cout << endl;

                cout
                    << "Resultado multiplicacion:"
                    << endl;

                mostrarResultado(
                    resultado,
                    TAMANIO
                );


                cout
                    << "Tiempo multiplicacion: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }
            else
            {
                int* localA =
                    new int[CANTIDAD_LOCAL];

                int* localB =
                    new int[CANTIDAD_LOCAL];

                long long* resultado =
                    new long long[CANTIDAD_LOCAL];


                MPI_Recv(
                    localA,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    700,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                MPI_Recv(
                    localB,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    701,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int inicio =
                    (procesoMPI - 1)
                    *
                    CANTIDAD_LOCAL;

                int fin =
                    inicio
                    +
                    CANTIDAD_LOCAL
                    -
                    1;


                mostrarInformacionTrabajador(
                    nombreEquipo,
                    procesoMPI,
                    inicio,
                    fin,
                    "MULTIPLICACION"
                );


                operaciones.multiplicar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL,
                    nombreEquipo,
                    procesoMPI
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    702,
                    MPI_COMM_WORLD
                );


                delete[] localA;
                delete[] localB;
                delete[] resultado;
            }
        }


        // ====================================================
        // OPCION 5 - CUADRADO
        // ====================================================

        if (opcion == 5)
        {
            MPI_Barrier(
                MPI_COMM_WORLD
            );


            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();


                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Send(
                        arregloA + posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        800,
                        MPI_COMM_WORLD
                    );
                }


                for (
                    int trabajador = 1;
                    trabajador <= TRABAJADORES;
                    trabajador++
                    )
                {
                    int posicion =
                        (trabajador - 1)
                        *
                        CANTIDAD_LOCAL;


                    MPI_Recv(
                        resultado + posicion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        801,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                double fin =
                    MPI_Wtime();


                cout << endl;

                cout
                    << "Resultado cuadrado de A:"
                    << endl;

                mostrarResultado(
                    resultado,
                    TAMANIO
                );


                cout
                    << "Tiempo cuadrado: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }
            else
            {
                int* localA =
                    new int[CANTIDAD_LOCAL];

                long long* resultado =
                    new long long[CANTIDAD_LOCAL];


                MPI_Recv(
                    localA,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    800,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int inicio =
                    (procesoMPI - 1)
                    *
                    CANTIDAD_LOCAL;

                int fin =
                    inicio
                    +
                    CANTIDAD_LOCAL
                    -
                    1;


                mostrarInformacionTrabajador(
                    nombreEquipo,
                    procesoMPI,
                    inicio,
                    fin,
                    "CUADRADO"
                );


                operaciones.cuadrado(
                    localA,
                    resultado,
                    CANTIDAD_LOCAL,
                    nombreEquipo,
                    procesoMPI
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    801,
                    MPI_COMM_WORLD
                );


                delete[] localA;
                delete[] resultado;
            }
        }


        // ====================================================
        // OPCION INVALIDA
        // ====================================================

        if (
            opcion < 1 ||
            opcion > 6
            )
        {
            if (procesoMPI == 0)
            {
                cout
                    << "Opcion incorrecta."
                    << endl;
            }
        }


        MPI_Barrier(
            MPI_COMM_WORLD
        );

    }
    while (
        opcion != 6
        );


    // ========================================================
    // LIBERAR MEMORIA
    // ========================================================

    if (procesoMPI == 0)
    {
        delete[] arregloA;
        delete[] arregloB;
    }


    MPI_Barrier(
        MPI_COMM_WORLD
    );


    if (procesoMPI == 0)
    {
        cout << endl;

        cout
            << "========================================"
            << endl;

        cout
            << "Programa finalizado correctamente"
            << endl;

        cout
            << "========================================"
            << endl;
    }


    MPI_Finalize();


    return 0;
}

