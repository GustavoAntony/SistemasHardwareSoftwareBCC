#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
    pthread_mutex_t *mutex_soma;
};

double soma = 0;
void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        pthread_mutex_lock(spa->mutex_soma);
        soma += spa->vetor[i];
        pthread_mutex_unlock(spa->mutex_soma);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_t mutex_soma = PTHREAD_MUTEX_INITIALIZER;
    double *vetor = NULL;
    int n;
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }


    /* TODO: criar thread_t e soma_parcial_args aqui */
    pthread_t tids[4];
    struct soma_parcial_args args[4];
    
    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        args[i].vetor = vetor;
        args[i].start = i *n/4;
        args[i].end = (i+1)*n /4;
        args[i].mutex_soma = &mutex_soma;
        if (i==3) args[i].end = n;

        pthread_create(&tids[n],NULL, soma_parcial,&args[i]);
    }

    /* TODO: esperar pela conclusão*/

    printf("Paralela: %lf\n", soma);

    soma = 0;
    struct soma_parcial_args aa;
    aa.vetor = vetor;
    aa.start = 0;
    aa.end = n;
    aa.mutex_soma = &mutex_soma;
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", soma);

    return 0;
}
