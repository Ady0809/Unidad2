#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CANTIDAD_ALUMNOS 3
#define CANTIDAD_MATERIAS 3
#define MAXIMA_CALIFICACION 100
#define MINIMA_CALIFICACION 0
#define MAXIMA_LONGITUD_CADENA 100

int aleatorio_en_rango(int minimo, int maximo)
{
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void llenarMatriz(float matriz[CANTIDAD_ALUMNOS][CANTIDAD_MATERIAS + 1])
{
    int y, x;
    for (y = 0; y < CANTIDAD_ALUMNOS; y++)
    {
        float suma = 0;
        for (x = 0; x < CANTIDAD_MATERIAS; x++)
        {
            int calificacion = aleatorio_en_rango(MINIMA_CALIFICACION, MAXIMA_CALIFICACION);
            suma += (float)calificacion;
            matriz[y][x] = calificacion;
        }
        // Agregar promedio
        float promedio = suma / CANTIDAD_MATERIAS;
        matriz[y][CANTIDAD_MATERIAS] = promedio;
    }
}

void imprimirLinea()
{
    int x;
    printf("+----------");
    for (x = 0; x < CANTIDAD_MATERIAS + 1; x++)
    {
        printf("+--------");
    }
    printf("+\n");
}

void imprimir(float matriz[CANTIDAD_ALUMNOS][CANTIDAD_MATERIAS + 1], char alumnos[CANTIDAD_ALUMNOS][MAXIMA_LONGITUD_CADENA])
{
    int y, x;
    float promedioMayor = matriz[0][CANTIDAD_MATERIAS];
    float promedioMenor = matriz[0][CANTIDAD_MATERIAS];
    char alumnoPromedioMayor[MAXIMA_LONGITUD_CADENA];
    char alumnoPromedioMenor[MAXIMA_LONGITUD_CADENA];
    memcpy(alumnoPromedioMayor, alumnos[0], MAXIMA_LONGITUD_CADENA);
    memcpy(alumnoPromedioMenor, alumnos[0], MAXIMA_LONGITUD_CADENA);

    imprimirLinea();
    printf("|  Alumno  |");
    for (x = 0; x < CANTIDAD_MATERIAS; x++)
    {
        printf("Cal %d   |", x + 1);
    }
    printf("Promedio|\n");
    imprimirLinea();
    for (y = 0; y < CANTIDAD_ALUMNOS; y++)
    {
        printf("|%-10s|", alumnos[y]);
        float suma = 0;
        for (x = 0; x < CANTIDAD_MATERIAS; x++)
        {
            int calificacion = matriz[y][x];
            printf("%-7d |", calificacion);
        }
        float promedio = matriz[y][CANTIDAD_MATERIAS];
        if (promedio > promedioMayor)
        {
            promedioMayor = promedio;
            memcpy(alumnoPromedioMayor, alumnos[y], MAXIMA_LONGITUD_CADENA);
        }
        if (promedio < promedioMenor)
        {
            promedioMenor = promedio;
            memcpy(alumnoPromedioMenor, alumnos[y], MAXIMA_LONGITUD_CADENA);
        }
        printf("%0.2f   |\n", promedio);
        imprimirLinea();
    }
    printf("Promedio mayor: %s con %0.2f\n", alumnoPromedioMayor, promedioMayor);
    printf("Promedio menor: %s con %0.2f\n", alumnoPromedioMenor, promedioMenor);
}

int main()
{
    srand(getpid());
    float matriz[CANTIDAD_ALUMNOS][CANTIDAD_MATERIAS + 1];
    char alumnos[CANTIDAD_ALUMNOS][MAXIMA_LONGITUD_CADENA] = {
        "Luis",
        "Pedro",
        "Maria",
    };
    llenarMatriz(matriz);
    imprimir(matriz, alumnos);
}