#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

enum {
    KIND_SIMPLE = 1,
    KIND_PIPELINE,
    KIND_REDIRECT,
    KIND_SEQ1,
    KIND_SEQ2,
    RD_INPUT = 1,
    RD_OUTPUT,
    RD_APPEND,
    OP_CONJUNCT = 1,
    OP_DISJUNCT,
    OP_BACKGROUND = 1,
    OP_SEQ
};

typedef struct Command{
    int kind;
    union{
        struct {
            int argc;
            char **argv;
        };
        struct {
            int pipeline_size;
            struct Command *pipeline_commands;
        };
        struct {
            int rd_mode;
            char *rd_path;
            struct Command *rd_command;
        };
        struct {
            int seq_size;
            struct Command *seq_commands;
            int *seq_operations;
        };
    };
} Command;

int run_command(Command *);
int run_simple(Command*);
int run_redirect(Command*);

int run_pipeline(Command* seq){
    return -1;
}

int
run_seq1_cmd(Command* seq){
    return -1;
}

int
run_seq2_cmd(Command *seq){
    return -1;
}

int
run_simple(Command* cmd){
    pid_t pid;
    if ((pid = fork()) == 0){
        execvp((*cmd).argv[0], (*cmd).argv);
        exit(1);
    }
    return pid;
}

int
run_redirect(Command* cmd){
    int fd, red_stream;
    int pid;
    switch((*cmd).rd_mode){
        case RD_INPUT:
            fd = open((*cmd).rd_path, O_RDONLY, 0666);
            red_stream = dup(0);
            dup2(fd, 0);
            close(fd);
            pid = run_command((*cmd).rd_command);
            dup2(red_stream, 0);
            break;
        case RD_APPEND:
            fd = open((*cmd).rd_path, O_WRONLY | O_CREAT | O_APPEND, 0666);
            red_stream = dup(1);
            dup2(fd, 1);
            close(fd);
            pid = run_command((*cmd).rd_command);
            dup2(red_stream, 1);
            break;
        case RD_OUTPUT:
            fd = open((*cmd).rd_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            red_stream = dup(1);
            dup2(fd, 1);
            close(fd);
            pid = run_command((*cmd).rd_command);
            dup2(red_stream, 1);
            break;
        default: return -1; break;
    }
    close(red_stream);
    return pid;
}

int
run_command(Command *cmd){
    int pid = -1;
    switch ((*cmd).kind){
        case KIND_SIMPLE:
            pid = run_simple(cmd);
            break;
        case KIND_REDIRECT:
            pid = run_redirect(cmd);
            break;
        case KIND_PIPELINE:
            pid = run_pipeline(cmd);
            break;
        case KIND_SEQ1:
            pid = run_seq1_cmd(cmd);
            break;
        case KIND_SEQ2:
            pid = run_seq2_cmd(cmd);
            break;
        default: break;
    }
    return pid;
};

int
main(void){
    return 0;
}
