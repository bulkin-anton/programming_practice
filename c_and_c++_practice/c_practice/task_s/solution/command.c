#include "command.h"
#include <stdlib.h>

int
init_empty_command(Command *cmd){
    *cmd = (Command) {0};
    return 0;
}

int
init_sequence_command(Command *cmd, int kind){
    int r = init_empty_command(cmd);
    if (r == 0){
        (*cmd).kind = kind;
    }
    return r;
}

int
append_command_to_sequence(Command *cmd, Command *c_append){
    if (((*cmd).seq_commands = realloc((*cmd).seq_commands,
    ((*cmd).seq_size + 1) * sizeof(*cmd)))){
        (*cmd).seq_commands[(*cmd).seq_size] = *c_append;
        (*cmd).seq_size++;
        return 0;
    }
    return -1;
}

int
append_operation_to_sequence(Command *cmd, int op_kind){
    if (((*cmd).seq_operations = realloc((*cmd).seq_operations,
    ((*cmd).seq_size) * sizeof(op_kind)))){
        (*cmd).seq_operations[(*cmd).seq_size - 1] = op_kind;
        return 0;
    }
    return -1;
}

int
init_pipeline_command(Command *cmd){
    int r = init_empty_command(cmd);
    if (r == 0){
        (*cmd).kind = KIND_PIPELINE;
    }
    return r;
}

int
append_to_pipeline(Command *cmd, Command *c_append){
    if (((*cmd).pipeline_commands = realloc((*cmd).pipeline_commands,
    ((*cmd).pipeline_size + 1) * sizeof(*cmd)))){
        (*cmd).pipeline_commands[(*cmd).pipeline_size] = *c_append;
        (*cmd).pipeline_size++;
        return 0;
    }
    return -1;
}

int
init_redirect_command(Command *cmd){
    int r = init_empty_command(cmd);
    if (r == 0){
        (*cmd).kind = KIND_REDIRECT;
    }
    return r;
}

int
set_rd_command(Command *cmd, Command *c_set){
    if ((*cmd).rd_command == NULL){
        if (((*cmd).rd_command = malloc(sizeof(*cmd)))){
            *((*cmd).rd_command) = *c_set;
            return 0;
        }
    }
    return -1;
}

int
init_simple_command(Command *cmd){
    if (init_empty_command(cmd) == 0){
        if (((*cmd).argv = malloc(sizeof(char *)))){
            (*cmd).argv[0] = NULL;
            (*cmd).kind = KIND_SIMPLE;
            return 0;
        }
    }
    return -1;
}

int
append_word_simple_command(Command *cmd, char *word){
    (*cmd).argc++;
    if (((*cmd).argv = realloc((*cmd).argv,
    ((*cmd).argc + 1) * sizeof(word)))){
        (*cmd).argv[(*cmd).argc - 1] = word;
        (*cmd).argv[(*cmd).argc] = NULL;
        return 0;
    }
    (*cmd).argc--;
    return -1;
}

void
free_command(Command *cmd){
    switch ((*cmd).kind){
        case KIND_SIMPLE:
            for (int i = 0; i < (*cmd).argc; i++){
                free((*cmd).argv[i]);
            }
            free((*cmd).argv);
            break;
        case KIND_SEQ1:
        case KIND_SEQ2:
            for (int i = 0; i < (*cmd).seq_size; i++){
                free_command(&(*cmd).seq_commands[i]);
            }
            free((*cmd).seq_operations);
            free((*cmd).seq_commands);
            break;
        case KIND_PIPELINE:
            for (int i = 0; i < (*cmd).pipeline_size; i++){
                free_command(&(*cmd).pipeline_commands[i]);
            }
            free((*cmd).pipeline_commands);
            break;
        case KIND_REDIRECT:
            free_command((*cmd).rd_command);
            free((*cmd).rd_command);
            free((*cmd).rd_path);
            break;
        default: break;
    }
}
