#include <iostream>
#include <mpi.h>

#include "OperacionesArreglos.h"

using namespace std;

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int totalProcesos;
    int procesoMPI;

    MPI_Comm_size(
        MPI_COMM_WORLD,
        &totalProcesos
    );

    MPI_Comm_rank(
        MPI_COMM_WORLD,
        &procesoMPI
    );

    char nombreEquipo[MPI_MAX_PROCESSOR_NAME];
    int longitudNombre;

    MPI_Get_processor_name(
        nombreEquipo,
        &longitudNombre
    );


    // =========================================
    // CONFIGURACION
    // =========================================

    const int TAMANIO = 40;
    const int TRABAJADORES = 4;

    const int CANTIDAD_LOCAL =
        TAMANIO / TRABAJADORES;

    bool detallado = true;


    // =========================================
    // VALIDAR PROCESOS
    // =========================================

    if (totalProcesos != 5)
    {
        if (procesoMPI == 0)
        {
            cout << endl;
            cout << "ERROR: Se necesitan exactamente 5 procesos MPI." << endl;
            cout << "Ejecuta: mpiexec -n 5 main.exe" << endl;
        }

        MPI_Finalize();
        return 1;
    }


    OperacionesArreglos operaciones;

    int opcion = 0;
    int arreglosCreados = 0;


    // =========================================
    // ARREGLOS DEL MAESTRO
    // =========================================

    int* arregloA = nullptr;
    int* arregloB = nullptr;


    if (procesoMPI == 0)
    {
        arregloA = new int[TAMANIO];
        arregloB = new int[TAMANIO];
    }


    // =========================================
    // CICLO DEL MENU
    // =========================================

    do
    {
        if (procesoMPI == 0)
        {
            cout << endl;
            cout << "========================================" << endl;
            cout << "      OPERACIONES CON MPI + OPENMP" << endl;
            cout << "========================================" << endl;

            cout << "Equipo maestro: " << nombreEquipo << endl;
            cout << "Proceso MPI maestro: 0" << endl;

            cout << endl;

            cout << "1. Crear arreglos A y B" << endl;
            cout << "2. Sumar arreglos" << endl;
            cout << "3. Restar arreglos" << endl;
            cout << "4. Multiplicar arreglos" << endl;
            cout << "5. Calcular cuadrado del arreglo A" << endl;
            cout << "6. Salir" << endl;

            cout << endl;
            cout << "Selecciona una opcion: ";

            cin >> opcion;
        }


        // =========================================
        // DISTRIBUIR OPCION
        // =========================================

        MPI_Bcast(
            &opcion,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD
        );


        // =========================================
        // OPCION 1 - CREAR ARREGLOS
        // =========================================

        if (opcion == 1)
        {
            if (procesoMPI == 0)
            {
                cout << endl;
                cout << "========================================" << endl;
                cout << "        CREACION DE ARREGLOS A Y B" << endl;
                cout << "========================================" << endl;

                cout << "Equipo maestro: " << nombreEquipo << endl;
                cout << "Proceso MPI maestro: 0" << endl;
                cout << "Tamano total: " << TAMANIO << endl;

                cout << endl;
                cout << "----- CREANDO ARREGLO A -----" << endl;


                // =========================================
                // ENVIAR TRABAJO PARA A
                // =========================================

                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int posicionInicial =
                        (trabajador - 1) *
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


                // =========================================
                // RECIBIR A
                // =========================================

                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int posicionInicial =
                        (trabajador - 1) *
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


                cout << endl;
                cout << "Arreglo A completo:" << endl;

                for (int i = 0; i < TAMANIO; i++)
                {
                    cout << arregloA[i] << " ";
                }

                cout << endl << endl;


                // =========================================
                // CREAR B
                // =========================================

                cout << "----- CREANDO ARREGLO B -----" << endl;


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int posicionInicial =
                        (trabajador - 1) *
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


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int posicionInicial =
                        (trabajador - 1) *
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


                cout << endl;
                cout << "Arreglo B completo:" << endl;

                for (int i = 0; i < TAMANIO; i++)
                {
                    cout << arregloB[i] << " ";
                }

                cout << endl << endl;

                arreglosCreados = 1;
            }

            else
            {
                // =========================================
                // TRABAJADOR CREA A
                // =========================================

                int posicionInicialA;

                MPI_Recv(
                    &posicionInicialA,
                    1,
                    MPI_INT,
                    0,
                    100,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int* arregloLocalA =
                    new int[CANTIDAD_LOCAL];


                cout
                    << "[Equipo: " << nombreEquipo << "] "
                    << "[Proceso MPI: " << procesoMPI << "] "
                    << "[Arreglo: A] "
                    << "[Seccion: "
                    << posicionInicialA
                    << " - "
                    << posicionInicialA + CANTIDAD_LOCAL - 1
                    << "]"
                    << endl;


                operaciones.crearArregloMPI(
                    arregloLocalA,
                    CANTIDAD_LOCAL,
                    posicionInicialA,
                    1,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    arregloLocalA,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    200,
                    MPI_COMM_WORLD
                );


                delete[] arregloLocalA;


                // =========================================
                // TRABAJADOR CREA B
                // =========================================

                int posicionInicialB;

                MPI_Recv(
                    &posicionInicialB,
                    1,
                    MPI_INT,
                    0,
                    300,
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE
                );


                int* arregloLocalB =
                    new int[CANTIDAD_LOCAL];


                cout
                    << "[Equipo: " << nombreEquipo << "] "
                    << "[Proceso MPI: " << procesoMPI << "] "
                    << "[Arreglo: B] "
                    << "[Seccion: "
                    << posicionInicialB
                    << " - "
                    << posicionInicialB + CANTIDAD_LOCAL - 1
                    << "]"
                    << endl;


                operaciones.crearArregloMPI(
                    arregloLocalB,
                    CANTIDAD_LOCAL,
                    posicionInicialB,
                    41,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    arregloLocalB,
                    CANTIDAD_LOCAL,
                    MPI_INT,
                    0,
                    400,
                    MPI_COMM_WORLD
                );


                delete[] arregloLocalB;
            }
        }


        // =========================================
        // ACTUALIZAR BANDERA EN TODOS
        // =========================================

        MPI_Bcast(
            &arreglosCreados,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD
        );


        // =========================================
        // VALIDAR QUE EXISTAN ARREGLOS
        // =========================================

        if (
            opcion >= 2 &&
            opcion <= 5 &&
            arreglosCreados == 0
        )
        {
            if (procesoMPI == 0)
            {
                cout << endl;
                cout << "ERROR: Primero debes crear los arreglos." << endl;
                cout << "Selecciona la opcion 1." << endl;
            }

            MPI_Barrier(MPI_COMM_WORLD);
            continue;
        }


        // =========================================
        // OPCION 2 - SUMA
        // =========================================

        if (opcion == 2)
        {
            MPI_Barrier(MPI_COMM_WORLD);

            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];

                double inicio =
                    MPI_Wtime();


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Send(
                        arregloA + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        500,
                        MPI_COMM_WORLD
                    );

                    MPI_Send(
                        arregloB + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        501,
                        MPI_COMM_WORLD
                    );
                }


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Recv(
                        resultado + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        502,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                MPI_Barrier(MPI_COMM_WORLD);

                double fin =
                    MPI_Wtime();


                cout << endl;
                cout << "========================================" << endl;
                cout << "          RESULTADO SUMA" << endl;
                cout << "========================================" << endl;


                for (int i = 0; i < TAMANIO; i++)
                {
                    cout << resultado[i] << " ";
                }


                cout << endl << endl;

                cout
                    << "Tiempo: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }

            else
            {
                int posicionInicial =
                    (procesoMPI - 1) *
                    CANTIDAD_LOCAL;


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


                operaciones.sumar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL,
                    posicionInicial,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    502,
                    MPI_COMM_WORLD
                );


                MPI_Barrier(MPI_COMM_WORLD);


                delete[] localA;
                delete[] localB;
                delete[] resultado;
            }
        }


        // =========================================
        // OPCION 3 - RESTA
        // =========================================

        if (opcion == 3)
        {
            MPI_Barrier(MPI_COMM_WORLD);

            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];

                double inicio =
                    MPI_Wtime();


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Send(
                        arregloA + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        600,
                        MPI_COMM_WORLD
                    );

                    MPI_Send(
                        arregloB + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        601,
                        MPI_COMM_WORLD
                    );
                }


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Recv(
                        resultado + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        602,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                MPI_Barrier(MPI_COMM_WORLD);

                double fin =
                    MPI_Wtime();


                cout << endl;
                cout << "========================================" << endl;
                cout << "          RESULTADO RESTA" << endl;
                cout << "========================================" << endl;


                for (int i = 0; i < TAMANIO; i++)
                {
                    cout << resultado[i] << " ";
                }


                cout << endl << endl;

                cout
                    << "Tiempo: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }

            else
            {
                int posicionInicial =
                    (procesoMPI - 1) *
                    CANTIDAD_LOCAL;


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


                operaciones.restar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL,
                    posicionInicial,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    602,
                    MPI_COMM_WORLD
                );


                MPI_Barrier(MPI_COMM_WORLD);


                delete[] localA;
                delete[] localB;
                delete[] resultado;
            }
        }


        // =========================================
        // OPCION 4 - MULTIPLICACION
        // =========================================

        if (opcion == 4)
        {
            MPI_Barrier(MPI_COMM_WORLD);

            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];

                double inicio =
                    MPI_Wtime();


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Send(
                        arregloA + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        700,
                        MPI_COMM_WORLD
                    );

                    MPI_Send(
                        arregloB + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        701,
                        MPI_COMM_WORLD
                    );
                }


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Recv(
                        resultado + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        702,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                MPI_Barrier(MPI_COMM_WORLD);

                double fin =
                    MPI_Wtime();


                cout << endl;
                cout << "========================================" << endl;
                cout << "      RESULTADO MULTIPLICACION" << endl;
                cout << "========================================" << endl;


                for (int i = 0; i < TAMANIO; i++)
                {
                    cout << resultado[i] << " ";
                }


                cout << endl << endl;

                cout
                    << "Tiempo: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }

            else
            {
                int posicionInicial =
                    (procesoMPI - 1) *
                    CANTIDAD_LOCAL;


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


                operaciones.multiplicar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL,
                    posicionInicial,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    702,
                    MPI_COMM_WORLD
                );


                MPI_Barrier(MPI_COMM_WORLD);


                delete[] localA;
                delete[] localB;
                delete[] resultado;
            }
        }


        // =========================================
        // OPCION 5 - CUADRADO
        // =========================================

        if (opcion == 5)
        {
            MPI_Barrier(MPI_COMM_WORLD);

            if (procesoMPI == 0)
            {
                long long* resultado =
                    new long long[TAMANIO];

                double inicio =
                    MPI_Wtime();


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Send(
                        arregloA + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        800,
                        MPI_COMM_WORLD
                    );
                }


                for (int trabajador = 1;
                     trabajador <= TRABAJADORES;
                     trabajador++)
                {
                    int inicioSeccion =
                        (trabajador - 1) *
                        CANTIDAD_LOCAL;

                    MPI_Recv(
                        resultado + inicioSeccion,
                        CANTIDAD_LOCAL,
                        MPI_LONG_LONG,
                        trabajador,
                        801,
                        MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE
                    );
                }


                MPI_Barrier(MPI_COMM_WORLD);

                double fin =
                    MPI_Wtime();


                cout << endl;
                cout << "========================================" << endl;
                cout << "       RESULTADO CUADRADO DE A" << endl;
                cout << "========================================" << endl;


                for (int i = 0; i < TAMANIO; i++)
                {
                    cout << resultado[i] << " ";
                }


                cout << endl << endl;

                cout
                    << "Tiempo: "
                    << fin - inicio
                    << " segundos"
                    << endl;


                delete[] resultado;
            }

            else
            {
                int posicionInicial =
                    (procesoMPI - 1) *
                    CANTIDAD_LOCAL;


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


                operaciones.cuadrado(
                    localA,
                    resultado,
                    CANTIDAD_LOCAL,
                    posicionInicial,
                    nombreEquipo,
                    procesoMPI,
                    detallado
                );


                MPI_Send(
                    resultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    801,
                    MPI_COMM_WORLD
                );


                MPI_Barrier(MPI_COMM_WORLD);


                delete[] localA;
                delete[] resultado;
            }
        }


        // =========================================
        // SALIR
        // =========================================

        if (opcion == 6)
        {
            if (procesoMPI == 0)
            {
                cout << endl;
                cout << "Finalizando programa..." << endl;
            }
        }


        if (opcion < 1 || opcion > 6)
        {
            if (procesoMPI == 0)
            {
                cout << endl;
                cout << "Opcion no valida." << endl;
            }
        }


        MPI_Barrier(
            MPI_COMM_WORLD
        );

    }
    while (opcion != 6);


    // =========================================
    // LIBERAR MEMORIA
    // =========================================

    if (procesoMPI == 0)
    {
        delete[] arregloA;
        delete[] arregloB;
    }


    // =========================================
    // FINALIZAR
    // =========================================

    MPI_Finalize();

    return 0;
}