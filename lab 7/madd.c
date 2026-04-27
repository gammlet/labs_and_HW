#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define NUM_THREADS 2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{
    thread_arg_t *arg = (thread_arg_t *)p_arg;

    TMatrix *m = arg->m;
    TMatrix *n = arg->n;
    TMatrix *t = arg->t;

    int start, end;
    int rows = m->nrows;

    // Split work based on thread id
    if (arg->id == 0) {
        start = 0;
        end = rows / 2;
    } else {
        start = rows / 2;
        end = rows;
    }

    // Perform matrix addition for assigned rows
    for (int i = start; i < end; i++) {
        for (int j = 0; j < m->ncols; j++) {
            t->data[i][j] = m->data[i][j] + n->data[i][j];
        }
    }

    return NULL;
}

/* Return the sum of two matrices using 2 threads */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (m == NULL || n == NULL ||
        m->nrows != n->nrows || m->ncols != n->ncols)
        return NULL;

    TMatrix *t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return NULL;

    pthread_t threads[NUM_THREADS];
    thread_arg_t args[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].m = m;
        args[i].n = n;
        args[i].t = t;

        if (pthread_create(&threads[i], NULL, thread_main, &args[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    return t;
}