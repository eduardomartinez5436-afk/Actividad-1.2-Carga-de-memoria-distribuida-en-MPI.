#include <iostream>
#include <mpi.h>
#include <omp.h>

#include "OperacionesArreglos.h"

using namespace std;


int main(int argc, char* argv[])
{

    MPI_Init(&argc,&argv);


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


    char nombreEquipo[MPI_MAX_PROCESSOR_NAME];

    int longitud;


    MPI_Get_processor_name(
        nombreEquipo,
        &longitud
    );



    // =========================================
    // CONFIGURACION
    // =========================================


    const int TAMANIO = 4000000;

    const int TRABAJADORES = 4;


    const int CANTIDAD_LOCAL =
        TAMANIO / TRABAJADORES;



    bool detallado = false;



    if(totalProcesos != 5)
    {

        if(procesoMPI == 0)
        {
            cout
            << "Se necesitan 5 procesos MPI"
            << endl;
        }


        MPI_Finalize();

        return 0;
    }



    OperacionesArreglos operaciones;



    int opcion = 0;


    int arreglosCreados = 0;



    int* arregloA = nullptr;

    int* arregloB = nullptr;



    if(procesoMPI == 0)
    {

        arregloA =
            new int[TAMANIO];


        arregloB =
            new int[TAMANIO];

    }




    // =========================================
    // MENU PRINCIPAL
    // =========================================


    do
    {


        if(procesoMPI == 0)
        {


            cout << endl;

            cout
            << "========================================"
            << endl;


            cout
            << " MPI + OPENMP ARREGLOS GRANDES"
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



            cout
            << endl
            << "Opcion: ";



            cin
            >> opcion;


        }



        // Enviar opcion a todos

        MPI_Bcast(
            &opcion,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD
        );



        // =========================================
        // CREAR A Y B
        // =========================================


        if(opcion == 1)
        {


            if(procesoMPI == 0)
            {


                cout << endl;

                cout
                << "Creando arreglos..."
                << endl;



                double inicio =
                    MPI_Wtime();



                // Enviar posiciones

                for(
                    int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++
                )
                {


                    int posicionInicial =
                    (trabajador-1)
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



                // Recibir A

                for(
                    int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++
                )
                {


                    int posicionInicial =
                    (trabajador-1)
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



                // Enviar posiciones B

                for(
                    int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++
                )
                {


                    int posicionInicial =
                    (trabajador-1)
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




                // Recibir B

                for(
                    int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++
                )
                {


                    int posicionInicial =
                    (trabajador-1)
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



                cout
                << "Arreglos creados correctamente"
                << endl;



                cout
                << "Tiempo creacion: "
                << fin-inicio
                << " segundos"
                << endl;



                cout << endl;



                cout
                << "Primeros elementos A:"
                << endl;



                for(int i=0;i<10;i++)
                {
                    cout
                    << arregloA[i]
                    << " ";
                }



                cout << endl;



                cout
                << "Primeros elementos B:"
                << endl;



                for(int i=0;i<10;i++)
                {
                    cout
                    << arregloB[i]
                    << " ";
                }


                cout << endl;



                arreglosCreados = 1;


            }

            else
            {


                // Recibir sección A


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




                // Crear B


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
                    posicionInicial + 999999,
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



        MPI_Bcast(
            &arreglosCreados,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD
        );

                // =========================================
        // VALIDAR SI EXISTEN ARREGLOS
        // =========================================

        if(opcion >= 2 && opcion <= 5 && arreglosCreados == 0)
        {

            if(procesoMPI == 0)
            {
                cout << endl;
                cout
                << "Primero debes crear los arreglos con la opcion 1"
                << endl;
            }


            MPI_Barrier(
                MPI_COMM_WORLD
            );


            continue;
        }



        // =========================================
        // OPCION 2 - SUMA
        // =========================================

        if(opcion == 2)
        {


            MPI_Barrier(
                MPI_COMM_WORLD
            );


            if(procesoMPI == 0)
            {


                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();



                for(
                    int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++
                )
                {


                    int posicion =
                    (trabajador-1)
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



                for(
                    int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++
                )
                {


                    int posicion =
                    (trabajador-1)
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
                << "Resultado suma primeros elementos:"
                << endl;



                for(int i=0;i<10;i++)
                {
                    cout
                    << resultado[i]
                    << " ";
                }


                cout << endl;


                cout
                << "Tiempo suma: "
                << fin-inicio
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


                long long* localResultado =
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
                    localResultado,
                    CANTIDAD_LOCAL
                );



                MPI_Send(
                    localResultado,
                    CANTIDAD_LOCAL,
                    MPI_LONG_LONG,
                    0,
                    502,
                    MPI_COMM_WORLD
                );



                delete[] localA;
                delete[] localB;
                delete[] localResultado;

            }

        }




        // =========================================
        // OPCION 3 - RESTA
        // =========================================

        if(opcion == 3)
        {


            MPI_Barrier(
                MPI_COMM_WORLD
            );


            if(procesoMPI == 0)
            {


                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();



                for(int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++)
                {


                    int posicion =
                    (trabajador-1)
                    *
                    CANTIDAD_LOCAL;


                    MPI_Send(
                        arregloA+posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        600,
                        MPI_COMM_WORLD
                    );


                    MPI_Send(
                        arregloB+posicion,
                        CANTIDAD_LOCAL,
                        MPI_INT,
                        trabajador,
                        601,
                        MPI_COMM_WORLD
                    );

                }




                for(int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++)
                {


                    int posicion =
                    (trabajador-1)
                    *
                    CANTIDAD_LOCAL;


                    MPI_Recv(
                        resultado+posicion,
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
                << "Resultado resta primeros elementos:"
                << endl;



                for(int i=0;i<10;i++)
                {
                    cout
                    << resultado[i]
                    << " ";
                }



                cout << endl;


                cout
                << "Tiempo resta: "
                << fin-inicio
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



                operaciones.restar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL
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

                // =========================================
        // OPCION 4 - MULTIPLICACION
        // =========================================

        if(opcion == 4)
        {

            MPI_Barrier(MPI_COMM_WORLD);


            if(procesoMPI == 0)
            {

                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();



                for(int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++)
                {

                    int posicion =
                    (trabajador-1)
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



                for(int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++)
                {

                    int posicion =
                    (trabajador-1)
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
                << "Resultado multiplicacion primeros elementos:"
                << endl;



                for(int i=0;i<10;i++)
                {
                    cout
                    << resultado[i]
                    << " ";
                }


                cout << endl;



                cout
                << "Tiempo multiplicacion: "
                << fin-inicio
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



                operaciones.multiplicar(
                    localA,
                    localB,
                    resultado,
                    CANTIDAD_LOCAL
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




        // =========================================
        // OPCION 5 - CUADRADO DE A
        // =========================================

        if(opcion == 5)
        {

            MPI_Barrier(MPI_COMM_WORLD);



            if(procesoMPI == 0)
            {


                long long* resultado =
                    new long long[TAMANIO];


                double inicio =
                    MPI_Wtime();



                for(int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++)
                {


                    int posicion =
                    (trabajador-1)
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




                for(int trabajador=1;
                    trabajador<=TRABAJADORES;
                    trabajador++)
                {


                    int posicion =
                    (trabajador-1)
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
                << "Resultado cuadrado primeros elementos:"
                << endl;



                for(int i=0;i<10;i++)
                {
                    cout
                    << resultado[i]
                    << " ";
                }



                cout << endl;



                cout
                << "Tiempo cuadrado: "
                << fin-inicio
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



                operaciones.cuadrado(
                    localA,
                    resultado,
                    CANTIDAD_LOCAL
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




        // =========================================
        // OPCION INVALIDA
        // =========================================

        if(opcion < 1 || opcion > 6)
        {

            if(procesoMPI == 0)
            {
                cout
                << "Opcion incorrecta"
                << endl;
            }

        }



        MPI_Barrier(
            MPI_COMM_WORLD
        );


    }
    while(opcion != 6);





    // =========================================
    // LIBERAR MEMORIA
    // =========================================

    if(procesoMPI == 0)
    {

        delete[] arregloA;
        delete[] arregloB;

    }




    if(procesoMPI == 0)
    {
        cout << endl;
        cout
        << "Programa finalizado correctamente"
        << endl;
    }




    MPI_Finalize();


    return 0;

}

    
