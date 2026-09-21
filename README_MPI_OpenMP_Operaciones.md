# Proyecto MPI + OpenMP - Operaciones con Arreglos

## Integrantes

- Gomez Enriquez Maria Fernanda
- Lozano Perez Jose Manuel
- Martinez Arias Eduardo Caleb

## Descripción

En este proyecto se desarrolló un programa en C++ utilizando MPI y OpenMP para trabajar con arreglos dinámicos.

MPI se utiliza para distribuir el trabajo entre diferentes procesos, mientras que OpenMP permite paralelizar las operaciones utilizando hilos dentro de cada proceso.

El programa permite crear arreglos dinámicos y realizar diferentes operaciones entre ellos, mostrando información del equipo, proceso MPI, hilo OpenMP y posición procesada.

## Objetivo

Implementar un programa híbrido MPI + OpenMP que permita distribuir el procesamiento de arreglos dinámicos entre procesos y utilizar hilos OpenMP para realizar las operaciones de manera paralela.

## Operaciones disponibles

El programa cuenta con un menú para realizar las siguientes operaciones:

1. Crear arreglos A y B
2. Sumar arreglos
3. Restar arreglos
4. Multiplicar arreglos
5. Calcular cuadrado del arreglo A
6. Salir

## Características

- Programación en C++.
- Uso de MPI.
- Uso de OpenMP.
- Uso de clases.
- Uso de arreglos dinámicos mediante punteros.
- Distribución de datos entre procesos MPI.
- Paralelización de operaciones con OpenMP.
- Identificación del equipo.
- Identificación del proceso MPI.
- Identificación del hilo OpenMP.
- Identificación de la posición procesada.
- No se utiliza `vector`, `std::vector` ni `ArrayList`.

## Distribución de datos

Para una ejecución con 40 elementos y 5 procesos MPI se utiliza un proceso maestro y cuatro procesos trabajadores.

La distribución esperada es:

| Proceso | Rango |
|---|---|
| MPI 1 | 0 - 9 |
| MPI 2 | 10 - 19 |
| MPI 3 | 20 - 29 |
| MPI 4 | 30 - 39 |

Cada proceso trabajador procesa una sección de 10 elementos.

## Ejemplo de mensajes

Durante el procesamiento se muestran mensajes similares a:

```text
[Equipo: Caleb19] [Proceso MPI: 2] [Hilo OpenMP: 5] [Posicion: 15] [Valor generado: 56]
```

Esto permite identificar qué equipo, proceso MPI e hilo OpenMP participaron en la generación o procesamiento de cada posición.

## Arreglos dinámicos

Los datos se almacenan utilizando memoria dinámica mediante punteros.

Ejemplo:

```cpp
int* arreglo = new int[tamanio];
```

La memoria utilizada se libera al finalizar mediante:

```cpp
delete[] arreglo;
```

No se utilizan `vector`, `std::vector`, `ArrayList` ni estructuras similares.

## Compilación

Desde una consola de Visual Studio configurada para x64:

```bat
cl /EHsc /openmp main.cpp /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib /OUT:main.exe
```

## Ejecución

Ejemplo con 5 procesos MPI:

```bat
mpiexec -n 5 .\main.exe
```

El programa mostrará el menú principal después de realizar la carga inicial de los datos.

## Ejemplo de ejecución

```text
========================================
       OPERACIONES CON MPI + OPENMP
========================================

Equipo maestro: Caleb19
Proceso MPI maestro: 0

1. Crear arreglos A y B
2. Sumar arreglos
3. Restar arreglos
4. Multiplicar arreglos
5. Calcular cuadrado del arreglo A
6. Salir

Selecciona una opcion:
```

## Prueba con 40 elementos

En la primera prueba se utiliza un arreglo de 40 elementos y 5 procesos MPI.

La distribución se realiza de manera equitativa entre los cuatro procesos trabajadores, mientras que OpenMP se utiliza para realizar el procesamiento mediante varios hilos.

Los mensajes detallados permiten comprobar el equipo, proceso MPI, hilo OpenMP, posición y valor generado.

## Resultados

El programa permite comprobar el funcionamiento conjunto de MPI y OpenMP en operaciones sobre arreglos dinámicos.

Las pruebas permiten observar cómo MPI distribuye las secciones del arreglo y cómo OpenMP participa dentro de cada proceso para realizar el trabajo.

## Conclusión

Con este proyecto se comprobó el funcionamiento de un modelo híbrido utilizando MPI y OpenMP. MPI permitió distribuir el trabajo entre procesos y OpenMP permitió utilizar diferentes hilos para procesar las secciones de los arreglos.

También se comprobó el uso de arreglos dinámicos mediante punteros y se realizaron diferentes operaciones sobre los datos generados.
