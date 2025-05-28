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
    KEY_SEM = 1,
    SEM_CNT = 1
};

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

void
son_proc(int son_type, int n, char *parm){
    key_t sem_k;
    int semid;
    struct sembuf semoprtn;
    semoprtn.sem_num = 0;
    semoprtn.sem_flg = 0;
    sem_k = ftok(parm, KEY_SEM);
    semid = semget(sem_k, SEM_CNT, 0666 | IPC_CREAT);
    for (int i = 0; i < n; i++){
        if ((i % 2) == son_type){
            /*
                first operation is decreasing to enter critical zone.
                for son - 0 it is 0 - he will be waiting for semapthore
                to become 0;
                for son - 1 it is -1 - he will be waiting for semapthore
                to become more than 1;
                so son-1 works with semapthore values > 0
                and son-0 - with semapthore values = 0;
                initially it is semapthore equals to 0;
            */
            semoprtn.sem_op = 0 - son_type;
            semop(semid, &semoprtn, 1);
            printf("%d\n", i);
            fflush(stdout);
            /*
                second operation is increasing after critical zone.
                son-o makes semapthore from 0 to 2
                son-1 makes semapthore to 0 from 1
            */
            semoprtn.sem_op = 2 - 3 * son_type;
            semop(semid, &semoprtn, 1);
        }
    }
    exit(0);
}

int semid;

void
sig_hndlr(int s){
    semctl(semid, 0, IPC_RMID, (int) 0);
    exit(0);
}

int
main(int parc, char *parms[]){
    signal(SIGINT, sig_hndlr);
    int num;
    union semun arg;
    static ushort val[1] = {};
    arg.array = val;
    key_t sem_k;
    sem_k = ftok(parms[0], KEY_SEM);
    /*
        Creation of 1 semaphore
    */
    semid = semget(sem_k, SEM_CNT, 0666 | IPC_CREAT);
    semctl(semid, 0, SETALL, arg);
    scanf("%d", &num);
    if (fork() == 0){
        signal(SIGINT, SIG_DFL);
        son_proc(1, num, parms[0]);
    }
    if (fork() == 0){
        signal(SIGINT, SIG_DFL);
        son_proc(0, num, parms[0]);
    }
    wait(NULL);
    wait(NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    return 0;
}
