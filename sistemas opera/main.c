#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Estructura para pasar multiples argumentos a la funcion del hilo
typedef struct {
    int thread_id;
    char message[100]; // Ajustamos el tamanio del mensaje
} ThreadArgs;

// Funcion que se ejecutara en el hilo
void* threadFunction1(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;

    pthread_exit(NULL); // Terminar el hilo
}

// Funci�n para limpiar el buffer de entrada
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // Limpiar el buffer de entrada
}

int main() {
    int elementos;

    // Pedimos al usuario la cantidad de hilos a crear
    printf("Ingresa cuantas tareas mandar a tus hilos: ");
    scanf("%d", &elementos);

    // Limpiar el buffer de entrada despues de scanf
    clearInputBuffer();

    // Asignar memoria para los hilos y sus argumentos
    pthread_t* threads = (pthread_t*)malloc(elementos * sizeof(pthread_t));
    ThreadArgs* Hilos = (ThreadArgs*)malloc(elementos * sizeof(ThreadArgs));

    // Crear los hilos y pasar los argumentos
    for (int i = 0; i < elementos; i++) {
        // Asignamos el id del hilo
        Hilos[i].thread_id = i + 1;

        // Pedimos el mensaje al usuario
        printf("Hilo %d: Di que tarea ejecutara: ", Hilos[i].thread_id);

        // Leer el mensaje con fgets
        fgets(Hilos[i].message, sizeof(Hilos[i].message), stdin);
        fflush(stdin);
        // Eliminar el salto de linea al final de la cadena si lo hubiera
        Hilos[i].message[strcspn(Hilos[i].message, "\n")] = 0;

        // Crear el hilo
        if (pthread_create(&threads[i], NULL, threadFunction1, (void*)&Hilos[i]) != 0) {
            perror("Error al crear el hilo");
            free(threads);
            free(Hilos);
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que todos los hilos terminen su ejecucion
    for (int i = 0; i < elementos; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error al unir el hilo");
            free(threads);
            free(Hilos);
            exit(EXIT_FAILURE);
        }
    }

    // Imprimir mensaje del hilo principal
    printf("Todos los hilos han terminado su ejecucion.\n");

    // Liberar memoria asignada
    free(threads);
    free(Hilos);

    return 0;
}
