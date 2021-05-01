//
//  rwthreads.c
//  
//
//  Created by Patrick Charlton on 4/30/19.
//

#include <sys/types.h>     /* for pid_t */
#include <unistd.h>        /* for fork */
#include <stdio.h>         /* for printf */
#include <sys/mman.h>      /* for mmap */
#include <sys/wait.h>      /* for waitpid */
#include <stdlib.h>        /* for exit */
#include <sys/sem.h>       /* for semaphore processing */

/* struct for semaphore-like thread operations */
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int value;
} sem_like_struct_t;

void thread_sem_int (sem_like_struct_t * sem_struct, int value)
{  /* procedure to initialize sem_like_thread_structure */
    pthread_mutex_init (&(sem_struct->mutex), NULL);
    /* cast needed in the following line to handle
     what turns out to be a C macro PTHREAD_COND_INITIALIZER */
    sem_struct->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    sem_struct->value = value;
}

void P(sem_like_struct_t * sem_struct)
{/* procedure to simulate a P or wait operation using mutex and values */
    pthread_mutex_lock (&(sem_struct->mutex));
    sem_struct->value--;
    
    while (sem_struct->value < 0)
    {
        pthread_cond_wait(&(sem_struct->cond), &(sem_struct->mutex));
    }
    pthread_mutex_unlock (&(sem_struct->mutex));
}

void V(sem_like_struct_t * sem_struct)
{/* procedure to simulate a V or signal operation using mutex and values */
    pthread_mutex_lock (&(sem_struct->mutex));
    sem_struct->value++;
    pthread_cond_signal(&(sem_struct->cond));
    pthread_mutex_unlock (&(sem_struct->mutex));
}
