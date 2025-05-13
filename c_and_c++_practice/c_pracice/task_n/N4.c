#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

enum {
    KEY_1 = 1,
    KEY_2 = 2
};

struct msgbuf {
    long msgtype;
    char msgtext;
};

struct msgbuf_num{
    long msgtype;
    int msgtext;
};

void
son_proc(int n, char *parm){
    struct msgbuf msg_text;
    struct msgbuf_num msg_num_rec;
    key_t msg_k, msg_num_k;
    msg_k = ftok(parm, KEY_1);
    msg_num_k = ftok(parm, KEY_2);
    int msgid = msgget(msg_k, 0666 | IPC_CREAT);
    int msgid_num = msgget(msg_num_k, 0666 | IPC_CREAT);
    msg_text.msgtype = 1;
    msg_text.msgtext = 'i';
    for (int i = 0; i < n; i++){
        msgsnd(msgid, &msg_text, sizeof(char), 0);
    }
    msg_text.msgtype = 2;
    msg_text.msgtext = 'n';
    msgsnd(msgid, &msg_text, sizeof(char), 0);
    msgrcv(msgid_num, &msg_num_rec, sizeof(int), 0, 0);
    printf("%d\n", msg_num_rec.msgtext);
    msg_text.msgtype = 3;
    msg_text.msgtext = 'e';
    msgsnd(msgid, &msg_text, sizeof(char), 0);
    exit(0);
}

int msgid, msgid_num;

void
sig_hndlr(int s){
    msgctl(msgid, IPC_RMID, NULL);
    msgctl(msgid_num, IPC_RMID, NULL);
    exit(0);
}

int
main(int parc, char *parms[]){
    int n, num = 0;
    signal(SIGINT, sig_hndlr);
    scanf("%d", &n);
    key_t msg_k, msg_num_k;
    msg_k = ftok(parms[0], KEY_1);
    msg_num_k = ftok(parms[0], KEY_2);

    /*
        Creation of message queue for requests
    */
    msgid = msgget(msg_k, 0666 | IPC_CREAT);
    msgid_num = msgget(msg_num_k, 0666 | IPC_CREAT);
    if (fork() == 0){
        signal(SIGINT, SIG_DFL);
        son_proc(n, parms[0]);
    }
    int end_work = 0;
    struct msgbuf msg_text;
    struct msgbuf_num msg_num_send;
    msg_num_send.msgtype = 1;
    while(end_work == 0){
        msgrcv(msgid, &msg_text, sizeof(int), 0, 0);
        switch(msg_text.msgtext){
            case 'i': num++; break;
            case 'e': end_work++; break;
            case 'n':
                msg_num_send.msgtext = num;
                msgsnd(msgid_num, &msg_num_send, sizeof(int), 0);
                break;
            default: break;
        }
    }
    wait(NULL);
    msgctl(msgid, IPC_RMID, NULL);
    msgctl(msgid_num, IPC_RMID, NULL);
    return 0;
}
