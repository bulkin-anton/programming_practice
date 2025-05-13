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
    return -1;
}

int
run_redirect(Command* cmd){
    return -1;
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
