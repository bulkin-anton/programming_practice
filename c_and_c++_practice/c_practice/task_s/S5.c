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
    int pid = -1;
    int cnt = (*seq).pipeline_size;
    int fd[2], prev = -1;
    for (int i = 0; i < cnt; i++){
        pipe(fd);
        if ((pid = fork()) == 0){
            if (i != 0){
                dup2(prev, 0);
                close(prev);
            }
            if ((i + 1) != cnt){
                dup2(fd[1], 1);
            }
            close(fd[0]);
            close(fd[1]);
            run_command(&((*seq).pipeline_commands[i]));
            exit(0);
        }
        if (i != 0){
            close(prev);
        }
        prev = fd[0];
        close(fd[1]);
    }
    close(prev);
    return pid;
}

int
run_seq1_cmd(Command* seq){
    int pid = -1;
    for (int i = 0; i < (*seq).seq_size; i++){
        pid = run_command(&((*seq).seq_commands[i]));
        switch((*seq).seq_operations[i]){
            case OP_SEQ:
                waitpid(pid, NULL, 0);
                break;
            default: break;
        }
    }
    return pid;
}

int
run_seq2_cmd(Command *seq){
    int pid = -1, status, op_flag = 0;
    if ((*seq).seq_size <= 0){
        return -1;
    }
    pid = run_command(&((*seq).seq_commands[0]));
    waitpid(pid, &status, 0);
    op_flag = (!(WIFEXITED(status) &&
    (WEXITSTATUS(status) == 0)));
    for (int i = 1; i < (*seq).seq_size; i++){
        switch (op_flag){
            case 0:
                if ((*seq).seq_operations[i - 1] == OP_CONJUNCT){
                    pid = run_command(&((*seq).seq_commands[i]));
                    waitpid(pid, &status, 0);
                    op_flag = (!(WIFEXITED(status) &&
                    (WEXITSTATUS(status) == 0)));
                }
                break;
            case 1:
                if ((*seq).seq_operations[i - 1] == OP_DISJUNCT){
                    pid = run_command(&((*seq).seq_commands[i]));
                    waitpid(pid, &status, 0);
                    op_flag = (!(WIFEXITED(status) &&
                    (WEXITSTATUS(status) == 0)));
                } else{
                    op_flag = 0;
                }
                break;
            default: break;
        }
    }
    while(wait(NULL) != -1){
    }
    return pid;
}

int
run_simple(Command* cmd){
    execvp((*cmd).argv[0], (*cmd).argv);
    exit(1);
    return 0;
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
