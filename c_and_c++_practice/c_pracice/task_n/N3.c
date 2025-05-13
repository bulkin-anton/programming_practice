#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

enum {
    KEY_1 = 1,
    KEY_2 = 2,
    SEM_CNT = 1,
    MAX_EL = 50000,
    STEP = 100
};

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

void
son_proc(int son_type, long n, char *parm){
    key_t sem_k, shm_k;
    int semid, shmid;
    long *shmaddr, i, way = STEP;
    struct sembuf p = {0, 1, 0},
    v = {0, -1, 0};
    sem_k = ftok(parm, KEY_1);
    shm_k = ftok(parm, KEY_2);
    shmid = shmget(shm_k, (n + 1) * sizeof(long), 0666 | IPC_CREAT);
    semid = semget(sem_k, SEM_CNT, 0666 | IPC_CREAT);
    shmaddr = shmat(shmid, NULL, 0);
    if (son_type){
        i = 0;
    } else{
        i = n - 1;
    }
    while (shmaddr[n] != 0){
        semop(semid, &v, SEM_CNT);
        if (shmaddr[n] < way){
            way = shmaddr[n];
        }
        for (int k = 0; k < way; k++){
            shmaddr[i]++;
            if (son_type){
                i++;
            } else{
                i--;
            }
        }
        shmaddr[n] -= way;
        semop(semid, &p, SEM_CNT);
    }
    shmdt(shmaddr);
    exit(0);
}

int semid, shmid;

void
sig_hndlr(int s){
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    exit(0);
}

int
main(int parc, char *parms[]){
    signal(SIGINT, sig_hndlr);
    union semun arg;
    static ushort buf[SEM_CNT] = {1};
    arg.array = buf;
    long n;
    long *shmaddr;
    scanf("%ld", &n);
    if (n < 0){
        return 0;
    }
    key_t sem_k, shm_k;
    sem_k = ftok(parms[0], KEY_1);
    shm_k = ftok(parms[0], KEY_2);
    /*
        Creation of shared memory of size 1024 bytes
    */
    shmid = shmget(shm_k, sizeof(long) * (n + 1), 0666 | IPC_CREAT);
    /*
        Creation of 1 semaphore
    */
    semid = semget(sem_k, SEM_CNT, 0666 | IPC_CREAT);
    semctl(semid, 0, SETALL, arg);
    shmaddr = shmat(shmid, NULL, 0);
    for (long i = 0; i <= n; i++){
        shmaddr[i] = i;
    }
    if (fork() == 0){
        signal(SIGINT, SIG_DFL);
        son_proc(0, n, parms[0]);
    }
    if (fork() == 0){
        signal(SIGINT, SIG_DFL);
        son_proc(1, n, parms[0]);
    }
    wait(NULL);
    wait(NULL);
    if (n <= MAX_EL){
        for (long i = 0; i < n; i++){
            printf("%ld\n", shmaddr[i]);
            fflush(stdout);
        }
    }
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    return 0;
}
