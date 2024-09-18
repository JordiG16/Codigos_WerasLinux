//Ejemplo 1:

            //En este modelo, varios hilos de usuario se mapean a un n�mero menor de hilos del sistema operativo, permitiendo una implementaci�n m�s eficiente y adaptativa de hilos.

        #include <stdio.h>
        #include <pthread.h>

        // Funci�n que ser� ejecutada por cada hilo
        void *funcion_hilo(void *arg) {
            printf("Hilo ejecutado: %d\n", *((int *) arg));                                         // Imprimir el ID del hilo
            pthread_exit(NULL);                                                                     // Terminar el hilo
        }

        int main() {
            pthread_t hilos[4];                                                                     // Array para almacenar los identificadores de los hilos
            int ids[] = {1, 2, 3, 4};                                                               // Array de IDs de los hilos

            // Crear hilos
            for (int i = 0; i < 4; i++) {
                pthread_create(&hilos[i], NULL, funcion_hilo, (void *) &ids[i]);                    // Crear un nuevo hilo
            }

            // Esperar la finalizaci�n de los hilos
            for (int i = 0; i < 4; i++) {
                pthread_join(hilos[i], NULL);                                                       // Esperar a que el hilo con el ID correspondiente termine
            }

            return 0;
        }
