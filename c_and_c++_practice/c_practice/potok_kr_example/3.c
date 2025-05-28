#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <math.h>

enum {
    KEY = 'F'
};

void
son_proc(double x, double s, long k, long p, long pr, char *parm){
    key_t shm_k;
    int shmid;
    unsigned long size = pr * (k + 1);
    shm_k = ftok(parm, KEY);
    shmid = shmget(shm_k, size * sizeof(double), 0666 | IPC_CREAT);
    double *shmaddr = shmat(shmid, NULL, 0);
    for (int i = 0; i < (k + 1); i++){
        printf("%ld %d %ld\n", p, i, i * pr + p);
        shmaddr[i * pr + p] = sin((x + i * s) * p / pr * M_PI);
        //printf("%ld %lf\n %lf", i * pr + p - 1, sin((x + i * s) * p / pr * M_PI), (x + i * s) * p / pr);
    }
    shmdt(shmaddr);
    exit(0);
}

int shmid;

void
sig_hndlr(int s){
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}

int
main(int argc, char *argv[]){
    signal(SIGINT, sig_hndlr);
    char *eptr;
    //char *file = argv[1];
    long p = strtol(argv[2], &eptr, 10);
    double x = strtod(argv[3], &eptr);
    double s = strtod(argv[4], &eptr);
    long k = strtol(argv[5], &eptr, 10);
    key_t shm_k;
    shm_k = ftok(argv[0], KEY);
    /*
        Creation of shared memory of size 1024 bytes
    */
    shmid = shmget(shm_k, sizeof(double) * (k + 1) * p, 0666 | IPC_CREAT);
    for (long i = 0; i < p; i++){
        if (fork() == 0){
            son_proc(x, s, k, i, p, argv[0]);
        }
    }
    while (wait(NULL) != -1);
    //
    double *shmaddr = shmat(shmid, NULL, 0);
    for (long i = 0; i < (k + 1); i++){
        for (long j = 0; j < p; j++){
            printf("%ld\n", i*p + j);..
            printf("%lf ", shmaddr[i * p + j]);
        }
        printf("\n");
    }
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
