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

int
run_command(Command *){
    return 0;
};

int
main(void)
{
    // command "uname"

    Command c1_1_1 = {
        .kind = KIND_SIMPLE,
        .argc = 1,
        .argv = (char *[]){"uname", 0}
    };
    Command c1_1 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c1_1_1,
    };
    run_command(&c1_1);

    // command "echo 1 2 3 > file && wc < file &"

    Command c2_1_1_1 = {
        .kind = KIND_SIMPLE,
        .argc = 4,
        .argv = (char *[]) {"echo", "1", "2", "3", 0}
    };
    Command c2_1_1 = {
        .kind = KIND_REDIRECT,
        .rd_mode = RD_OUTPUT,
        .rd_path = "file",
        .rd_command = &c2_1_1_1
    };
    Command c2_1 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c2_1_1,
    };
    Command c2_2_1_1 = {
        .kind = KIND_SIMPLE,
        .argc = 1,
        .argv = (char *[]) {"wc", 0},
    };
    Command c2_2_1 = {
        .kind = KIND_REDIRECT,
        .rd_mode = RD_INPUT,
        .rd_path = "file",
        .rd_command = &c2_2_1_1,
    };
    Command c2_2 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c2_2_1,
    };
    Command c2 = {
        .kind = KIND_SEQ2,
        .seq_size = 2,
        .seq_commands = (Command []){c2_1, c2_2},
        .seq_operations = (int []){OP_CONJUNCT},
    };
    Command c2_0 = {
        .kind = KIND_SEQ1,
        .seq_size = 1,
        .seq_commands = &c2,
        .seq_operations = (int []){OP_BACKGROUND},
    };
    run_command(&c2_0);

    // command "echo 1 2 3 | wc"

    Command c3 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 2,
        .pipeline_commands = (Command []) {c2_1_1_1, c2_2_1_1}
    };
    run_command(&c3);

    // command "echo 1 >> file || echo 2 >> file && cat file"
    Command c4_1_1_1 = {
        .kind = KIND_SIMPLE,
        .argc = 2,
        .argv = (char *[]){"echo", "1", 0},
    };
    Command c4_1_1 = {
        .kind = KIND_REDIRECT,
        .rd_mode = RD_APPEND,
        .rd_path = "file",
        .rd_command = &c4_1_1_1,
    };
    Command c4_1 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c4_1_1,
    };
    Command c4_2_1_1 = {
        .kind = KIND_SIMPLE,
        .argc = 2,
        .argv = (char *[]){"echo", "2", 0},
    };
    Command c4_2_1 = {
        .kind = KIND_REDIRECT,
        .rd_mode = RD_APPEND,
        .rd_path = "file",
        .rd_command = &c4_2_1_1,
    };
    Command c4_2 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c4_2_1,
    };
    Command c4_3_1 = {
        .kind = KIND_SIMPLE,
        .argc = 2,
        .argv = (char *[]){"cat", "file", 0},
    };
    Command c4_3 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c4_3_1,
    };
    Command c4 = {
        .kind = KIND_SEQ2,
        .seq_size = 3,
        .seq_commands = (Command []) {c4_1, c4_2, c4_3},
        .seq_operations = (int []){OP_DISJUNCT, OP_CONJUNCT},
    };
    run_command(&c4);

    // command "echo 1 2 3 | wc > file; cat file"
    Command c5_1_1 = {
        .kind = KIND_REDIRECT,
        .rd_mode = RD_OUTPUT,
        .rd_path = "file",
        .rd_command = &c2_2_1_1,
    };
    Command c5_1 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 2,
        .pipeline_commands = (Command []) {c2_1_1_1, c5_1_1},
    };
    Command c5 = {
        .kind = KIND_SEQ1,
        .seq_size = 2,
        .seq_commands = (Command []) {c5_1, c4_3},
        .seq_operations = (int []){OP_SEQ, OP_SEQ},
    };
    run_command(&c5);

    // command "echo 1 || (echo 2 && echo 3)"
    Command c6_1 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c4_1_1_1,
    };
    Command c6_2_1_1 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c4_2_1_1,
    };
    Command c6_2_1_2_1 = {
        .kind = KIND_SIMPLE,
        .argc = 2,
        .argv = (char *[]) {"echo", "3", 0},
    };
    Command c6_2_1_2 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c6_2_1_2_1,
    };
    Command c6_2_1 = {
        .kind = KIND_SEQ2,
        .seq_size = 2,
        .seq_commands = (Command []) {c6_2_1_1, c6_2_1_2},
        .seq_operations = (int []) {OP_CONJUNCT},
    };
    Command c6_2 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 1,
        .pipeline_commands = &c6_2_1,   
    };
    Command c6 = {
        .kind = KIND_SEQ2,
        .seq_size = 2,
        .seq_commands = (Command []) {c6_1, c6_2},
        .seq_operations = (int []) {OP_DISJUNCT},
    };
    run_command(&c6);

    // command "yes | head"
    Command c7_1 = {
        .kind = KIND_SIMPLE,
        .argc = 1,
        .argv = (char *[]) {"yes", 0},
    };
    Command c7_2 = {
        .kind = KIND_SIMPLE,
        .argc = 1,
        .argv = (char *[]) {"head", 0},
    };
    Command c7 = {
        .kind = KIND_PIPELINE,
        .pipeline_size = 2,
        .pipeline_commands = (Command []) {c7_1, c7_2},
    };
    run_command(&c7);
}
