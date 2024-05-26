#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// linha de compilação:

/* declarar tarefas aqui e lançar no main */
/* cada bloco na figura deverá ser representado por um print com sua letra */

typedef struct {
    sem_t *barrier1;
    sem_t *barrier2;
} thread_arg;

void *thread1(void *_arg) {
    thread_arg *arg = _arg;

    printf("A\n");
    sem_post(arg->barrier1);

    sem_wait(arg->barrier1); // espera a thread 1 liberar na barreira 1
    sem_wait(arg->barrier1); // espera a thread 2 liberar na barreira 1

    printf("C\n");

    return NULL;
}

void *thread2(void *_arg) {
    thread_arg *arg = _arg;

    printf("B\n");
    sem_post(arg->barrier1); // sinaliza para a barreira 1
    sem_post(arg->barrier2); // sinaliza para a barreira 2

    sem_wait(arg->barrier1); // espera a thread 1 liberar na barreira 1
    sem_wait(arg->barrier1); // espera a thread 2 liberar na barreira 1
    sem_wait(arg->barrier2); // espera a thread 2 liberar na barreira 2
    sem_wait(arg->barrier2); // espera a thread 3 liberar na barreira 2
    sem_wait(arg->barrier2); // espera a thread 4 liberar na barreira 2

    printf("D\n");

    return NULL;
}

void *thread3(void *_arg) {
    thread_arg *arg = _arg;

    printf("E\n");
    sem_post(arg->barrier2); // sinaliza para a barreira 2

    sem_wait(arg->barrier2); // espera a thread 2 liberar na barreira 2
    sem_wait(arg->barrier2); // espera a thread 3 liberar na barreira 2
    sem_wait(arg->barrier2); // espera a thread 4 liberar na barreira 2

    printf("F\n");

    return NULL;
}

void *thread4(void *_arg) {
    thread_arg *arg = _arg;

    printf("G\n");
    sem_post(arg->barrier2); // sinaliza para a barreira 2

    sem_wait(arg->barrier2); // espera a thread 2 liberar na barreira 2
    sem_wait(arg->barrier2); // espera a thread 3 liberar na barreira 2
    sem_wait(arg->barrier2); // espera a thread 4 liberar na barreira 2

    printf("H\n");

    return NULL;
}

int main() {
    pthread_t *threads = malloc(4 * sizeof(pthread_t));
    thread_arg *arg = malloc(sizeof(thread_arg));

    sem_t *barrier1 = malloc(sizeof(sem_t));
    sem_t *barrier2 = malloc(sizeof(sem_t));

    sem_init(barrier1, 0, 0);
    sem_init(barrier2, 0, 0);

    arg->barrier1 = barrier1;
    arg->barrier2 = barrier2;

    pthread_create(&threads[0], NULL, thread1, arg);
    pthread_create(&threads[1], NULL, thread2, arg);
    pthread_create(&threads[2], NULL, thread3, arg);
    pthread_create(&threads[3], NULL, thread4, arg);

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(barrier1);
    sem_destroy(barrier2);

    free(threads);
    free(arg);
    free(barrier1);
    free(barrier2);

    return 0;
}
