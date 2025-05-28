#ifndef COMMAND_H
#define COMMAND_H

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

int init_empty_command(Command *);

int init_sequence_command(Command *, int);

int append_command_to_sequence(Command *, Command *);

int append_operation_to_sequence(Command *, int);

int init_pipeline_command(Command *);

int append_to_pipeline(Command *, Command *);

int init_redirect_command(Command *);

int set_rd_command(Command *, Command *);

int init_simple_command(Command *);

int append_word_simple_command(Command *, char *);

void free_command(Command *);

#endif
