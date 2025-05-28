#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/wait.h>

enum {KEY = 'Q'};

struct msgbuf{
    long msgtype;
    int msgtext;
};

void
son_proc(int fd, long msg_get, long msg_send, char *parm){
    int num;
    key_t msg_k;
    struct msgbuf msg;
    msg_k = ftok(parm, KEY);
    int msgid = msgget(msg_k, IPC_CREAT | 0666);
    while (1){
        msgrcv(msgid, &msg, sizeof(int), msg_get, 0);
        fflush(stdout);
        lseek(fd, -sizeof(num), SEEK_CUR);
        read(fd, &num, sizeof(num));
        if (num == 0){
            msg.msgtype = msg_send;
            msgsnd(msgid, &msg, sizeof(int), 0);
            break;
        } else{
            num--;
            write(fd, &num, sizeof(num));
            msg.msgtype = msg_send;
            msgsnd(msgid, &msg, sizeof(int), 0);
        }
    }
    close(fd);
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
    signal(SIGINT, sig_hndlr);
    int n, k, num;
    char template[] = "mflXXXXXX";
    int fd = mkstemp(template);
    unlink(template);
    key_t msg_k;
    struct msgbuf msg_send;
    msg_send.msgtype = 1;
    msg_send.msgtext = 0;
    msg_k = ftok(parms[0], KEY);
    msgid = msgget(msg_k, IPC_CREAT | 0666);
    msgsnd(msgid, &msg_send, sizeof(int), 0);
    scanf("%d", &n);
    scanf("%d", &k);
    write(fd, &k, sizeof(k));
    for(int i = 0; i < n; i++){
        if (fork() == 0){
            signal(SIGINT, SIG_DFL);
            son_proc(fd, i + 1, (i + 1) % n + 1, parms[0]);
        }
    }
    while(wait(NULL) != -1){
    }
    lseek(fd, 0, SEEK_SET);
    while(read(fd, &num, sizeof(num)) > 0){
        printf("%d\n", num);
    }
    close(fd);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
