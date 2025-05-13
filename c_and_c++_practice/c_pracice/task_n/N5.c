#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

enum {
    KEY = 1
};

struct msgbuf{
    long msgtype;
    long msgtext;
};

void
son_proc(int n, char *parm, long reg_msg_id){
    signal(SIGINT, SIG_DFL);
    if (n <= 0){
        exit(0);
    }
    int cnt = 0;
    struct msgbuf msg;
    key_t msg_k;
    long self = getpid(), serv;
    msg_k = ftok(parm, KEY);
    int msgid = msgget(msg_k, 0666 | IPC_CREAT);
    msg.msgtype = reg_msg_id;
    msg.msgtext = self;
    msgsnd(msgid, &msg, sizeof(long), 0);
    while (1){
        if (cnt == 20){
            exit(0);
        }
        if (msgrcv(msgid, &msg, sizeof(long), self, IPC_NOWAIT) != -1){
            break;
        } else{
            usleep(100);
            cnt++;
        }
    }
    serv = msg.msgtext;
    msg.msgtype = serv;
    for (int i = 0; i < n; i++){
        msg.msgtext = 1;
        msgsnd(msgid, &msg, sizeof(long), 0);
    }
    msg.msgtext = 2;
    msgsnd(msgid, &msg, sizeof(long), 0);
    msgrcv(msgid, &msg, sizeof(long), self, 0);
    printf("%ld\n", msg.msgtext);
    fflush(stdout);
    msg.msgtype = serv;
    msg.msgtext = 0;
    msgsnd(msgid, &msg, sizeof(long), 0);
    exit(0);
}

void
server_proc(char *parm, long klient_pid){
    signal(SIGINT, SIG_DFL);
    long num = 0;
    int end_work = 0;
    struct msgbuf msg;
    key_t msg_k;
    long self = getpid();
    msg_k = ftok(parm, KEY);
    int msgid = msgget(msg_k, 0666 | IPC_CREAT);
    while(end_work == 0){
        msgrcv(msgid, &msg, sizeof(long), self, 0);
        switch(msg.msgtext){
            case 1: num++; break;
            case 0: end_work++; break;
            case 2:
                msg.msgtype = klient_pid;
                msg.msgtext = num;
                msgsnd(msgid, &msg, sizeof(long), 0);
                break;
            default: break;
        }
    }
    exit(0);
}

void
registrator_proc(char *parm, long reg_msg_id){
    signal(SIGINT, SIG_DFL);
    struct msgbuf msg;
    pid_t pid;
    key_t msg_k;
    msg_k = ftok(parm, KEY);
    int msgid = msgget(msg_k, 0666 | IPC_CREAT);
    while (1){
        msgrcv(msgid, &msg, sizeof(long), reg_msg_id, 0);
        if (msg.msgtext == 0){
            break;
        } else{
            if ((pid = fork()) == 0){
                server_proc(parm, msg.msgtext);
            }
            if (pid > 0){
                msg.msgtype = msg.msgtext;
                msg.msgtext = pid;
                msgsnd(msgid, &msg, sizeof(long), 0);
            }
        }
    }
    while (wait(NULL) != -1){
    }
    exit(0);
}

int msgid;

void
sig_hndlr(int s){
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}

int
main(int parc, char *parms[]){
    long n, cnt = 0, cnt_creat = 0;
    long reg_type = 1;
    pid_t pid;
    signal(SIGINT, sig_hndlr);
    key_t msg_k;
    msg_k = ftok(parms[0], KEY);
    /*
        Creation of message queue for requests
    */
    msgid = msgget(msg_k, 0666 | IPC_CREAT);
    if (fork() == 0){
        registrator_proc(parms[0], reg_type);
    }
    while (scanf("%ld", &n) == 1){
        cnt_creat++;
        while ((pid = fork()) == -1){
            wait(NULL);
            cnt++;
        }
        if (pid == 0){
            son_proc(n, parms[0], reg_type);
        }
    }
    while (1){
        if (cnt_creat == cnt){
            break;
        }
        wait(NULL);
        cnt++;
    }
    struct msgbuf msg;
    msg.msgtype = reg_type;
    msg.msgtext = 0;
    msgsnd(msgid, &msg, sizeof(long), 0);
    wait(NULL);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
