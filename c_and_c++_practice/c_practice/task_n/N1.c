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
    KEY_3 = 3,
    SIZE = 1024,
    SEM_CNT = 2
};

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

void
son_proc(char *parm){
    key_t sem_k, msg_k, shm_k;
    msg_k = ftok(parm, KEY_1);
    sem_k = ftok(parm, KEY_2);
    shm_k = ftok(parm, KEY_3);
    msgget(msg_k, 0666 | IPC_CREAT);
    shmget(shm_k, SIZE, 0666 | IPC_CREAT);
    semget(sem_k, SEM_CNT, 0666 | IPC_CREAT);
    exit(0);
}

int msgid, semid, shmid;

void
sig_hndlr(int s){
    msgctl(msgid, IPC_RMID, NULL);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    exit(0);
}

int
main(int parc, char *parms[]){
    signal(SIGINT, sig_hndlr);
    union semun arg;
    static ushort buf[2] = {};
    arg.array = buf;
    key_t sem_k, msg_k, shm_k;
    msg_k = ftok(parms[0], KEY_1);
    sem_k = ftok(parms[0], KEY_2);
    shm_k = ftok(parms[0], KEY_3);
    /*
        Creation of message queue
    */
    msgid = msgget(msg_k, 0666 | IPC_CREAT);
    /*
        Creation of shared memory of size 1024 bytes
    */
    shmid = shmget(shm_k, SIZE, 0666 | IPC_CREAT);
    /*
        Creation of array of 2 semaphores
    */
    semid = semget(sem_k, SEM_CNT, 0666 | IPC_CREAT);
    semctl(semid, 0, SETALL, arg);
    if (fork() == 0){
        signal(SIGINT, SIG_DFL);
        son_proc(parms[0]);
    }
    wait(NULL);
    msgctl(msgid, IPC_RMID, NULL);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    return 0;
}
