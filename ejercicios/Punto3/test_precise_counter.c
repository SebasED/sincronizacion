#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

/* start_routine header */
void* contadorFuncion(void *);

/* Global variables */
counter_t contador;
int max;

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    if (argc != 3){
        printf ("Recuerde ingresar los dos parametros (Maximo contador y numero de hilos).\n");
        exit(0);
    }
    else {
        /* Declaration of struct timeval variables */
        struct timeval ti, tf;
        double tiempo;
        
        /* Initializing conter */
        init(&contador);

        /* get the command's line parameters */
        max = atoi(argv[1]);
        if (max <= 10000000){

            /* get the command's line parameters */
            int hilos = atoi(argv[2]);

            /* Threads handlers */
            pthread_t hilosArray[hilos - 1];
            
            /* Time starts counting */
            gettimeofday(&ti, NULL);
            for (int i = 0; i < hilos; i++)
            {
                /* Thread creation */
                pthread_create(&hilosArray[i], NULL, &contadorFuncion, NULL);
            }
            for (int i = 0; i < hilos; i++)
            {
                /* Threads joins */
                pthread_join(hilosArray[i], NULL);
            }
            /* get the end time */
            gettimeofday(&tf, NULL);

            /* get the elapset time (end_time - start_time) */
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            
            int counter = get(&contador);
            /* print the results (number threads employed, counter value, elasep time) */
            printf("Numero de hilos: %d\nValor de contador: %d\nHas tardado: %g milisegundos\n", hilos, counter, tiempo);
        }
        else {
            printf("El valor maximo del contador es 10000000\n");
        }
    }
    return 0;
}

/* start_routine definition */
void* contadorFuncion(void *unused){
    for (int i = 0; i < max; i++){
        increment(&contador);
    }
    return NULL;
}