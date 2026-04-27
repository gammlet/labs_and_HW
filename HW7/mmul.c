#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *arg = (thread_arg_t *) p_arg;
    TMatrix *m = arg->m, *n = arg->n, *t = arg->t;
    int row_start = arg->id * (m->nrows / NUM_THREADS);
    int row_end = (arg->id == NUM_THREADS - 1) ? m->nrows : row_start + m->nrows / NUM_THREADS;

    for (int i = row_start; i < row_end; i++) {
        for (int j = 0; j < n->ncols; j++) {
            TElement sum = 0;
            for (int k = 0; k < m->ncols; k++)
                sum += m->data[i][k] * n->data[k][j];
            t->data[i][j] = sum;
        }
    }
    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t threads[NUM_THREADS];
    thread_arg_t args[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].m = m;
        args[i].n = n;
        args[i].t = t;
        int rv = pthread_create(&threads[i], NULL, thread_main, &args[i]);
        if (rv != 0)
            exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        int rv = pthread_join(threads[i], NULL);
        if (rv != 0)
            exit(EXIT_FAILURE);
    }
    return t;
}
