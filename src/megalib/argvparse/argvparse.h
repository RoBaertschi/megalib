//
// Created by rtmba on 13.11.2023.
//

#ifndef MEGALIB_ARGVPARSE_H
#define MEGALIB_ARGVPARSE_H

#include "megalib/megalib.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct arg_command_t arg_command_t;
typedef struct arg_def_t arg_def_t;
typedef struct args_t args_t;
typedef struct arg_flag_t arg_flag_t;

typedef enum arg_def_type_t {
    ML_ARG_DEF_TYPE_FLAG,
    ML_ARG_DEF_TYPE_COMMAND,
} arg_def_type_t;

typedef enum parameter_type_t {
    ML_PARAMETER_TYPE_NONE,
    ML_PARAMETER_TYPE_STRING,
    ML_PARAMETER_TYPE_FILE,
    ML_PARAMETER_TYPE_FLAG,
} parameter_type_t;

typedef union arg_flag_value_t {
    char* string;
    FILE* file;
    bool specified;
} arg_flag_value_t;

struct args_t {
    size_t size;
    arg_def_t* arg_defs;
    char* description;
};

struct arg_flag_t {
    bool required;
    parameter_type_t type;
    char* description;
};

struct arg_def_t {
    arg_def_type_t type;
    union {
        arg_flag_t* flag;
        arg_command_t* command;
    };
};

struct arg_command_t {
    char* name;
    size_t size;
    arg_def_t* args;
    char* description;
};

ML_API args_t* ml_create_argvparser(char* description, size_t desc_size);
ML_API void ml_destroy_argvparser(args_t* args);
ML_API void ml_argvparser_add_global_flag(args_t* args, parameter_type_t type, bool required, const char* description, size_t desc_size);
ML_API void ml_argvparser_add_global_subcommand(/** [in,out] */ args_t* args, char* name, size_t name_size, char* description, size_t desc_size);

#endif //MEGALIB_ARGVPARSE_H

#ifdef ML_ARGVPARSE_IMPLEMENTATION

void ml__free_flag_recursive(arg_flag_t* flag);
void ml__free_args_recursive(args_t* args);
void ml__argvparser_init_global_flag(args_t* args, size_t pos, parameter_type_t type, bool required, const char* description, size_t desc_size);
void ml__argvparser_init_global_subcommand(args_t* args, size_t pos, char* name, size_t name_size, char* description, size_t desc_size);

ML_API args_t* ml_create_argvparser(char *description, size_t desc_size) {
    args_t* args = ML_MALLOC(sizeof(args_t));
    args->size = 0;
    args->arg_defs = NULL;
    args->arg_defs = NULL;
    args->description = ML_MALLOC(desc_size * sizeof(char));
    memcpy(args->description, description, desc_size);

    return args;
}

ML_API void ml_destroy_argvparser(args_t* args) {
    ml__free_args_recursive(args);

    ML_FREE(args->description);
    args->description = NULL;
    ML_FREE(args);
    args = NULL;
}

ML_API void ml_argvparser_add_global_flag(args_t* /** [in,out] */ args, parameter_type_t type, bool required, const char* description, size_t desc_size) {
    if (args->arg_defs == NULL) {
        args->arg_defs = (arg_def_t*) ML_MALLOC(sizeof(arg_def_t));
        ML_ASSERT(args->arg_defs != NULL && "Failed to malloc required space for a global flag def");
        ml__argvparser_init_global_flag(args, 0, type, required, description, desc_size);
        args->size = 1;
    } else {
        args->arg_defs = ml_realloc_or_fail(args->arg_defs, (args->size + 1) * sizeof(arg_def_t), "Failed to realloc required space for a global flag def");
        ml__argvparser_init_global_flag(args, args->size, type, required, description, desc_size);
        args->size += 1;
    }
}

ML_API void ml_argvparser_add_global_subcommand(/** [in,out] */ args_t* args, char* name, size_t name_size, char* description, size_t desc_size) {
    if (args->arg_defs == NULL) {
        args->arg_defs = (arg_def_t*) ML_MALLOC(sizeof(arg_def_t));
        ML_ASSERT(args->arg_defs != NULL && "Failed to malloc required space for a global subcommand def");
        ml__argvparser_init_global_subcommand(args, 0, name, name_size, description, desc_size);
        args->size = 1;
    } else {
        args->arg_defs = ml_realloc_or_fail(args->arg_defs, (args->size + 1) * sizeof (arg_def_t), "Failed to realloc required space for a global subcommand def");
        ml__argvparser_init_global_subcommand(args, args->size, name, name_size, description, desc_size);
        args->size += 1;
    }
}

void ml__argvparser_init_global_subcommand(args_t* args, size_t pos, char* name, size_t name_size, char* description, size_t desc_size) {
    args->arg_defs[pos].type = ML_ARG_DEF_TYPE_COMMAND;
    args->arg_defs[pos].command = ML_MALLOC(sizeof(arg_command_t));
    ML_ASSERT(args->arg_defs[pos].command && "Failed to malloc required space for a global subcommand");
    args->arg_defs[pos].command->args = NULL;
    args->arg_defs[pos].command->size = 0;
    args->arg_defs[pos].command->name = ML_MALLOC(name_size * sizeof (char));
    memcpy(args->arg_defs[pos].command->name, name, name_size);
    args->arg_defs[pos].command->description = ML_MALLOC(desc_size * sizeof (char));
    memcpy(args->arg_defs[pos].command->description, description, desc_size);
}

void ml__argvparser_init_global_flag(args_t* args, size_t pos, parameter_type_t type, bool required, const char* description, size_t desc_size) {
    args->arg_defs[pos].type = ML_ARG_DEF_TYPE_FLAG;
    args->arg_defs[pos].flag = ML_MALLOC(sizeof(arg_flag_t));
    ML_ASSERT(args->arg_defs[pos].flag != NULL && "Failed to malloc required space for a global flag");
    args->arg_defs[pos].flag->type = type;
    args->arg_defs[pos].flag->required = required;
    args->arg_defs[pos].flag->description = ML_MALLOC(desc_size * sizeof (char));
    memcpy(args->arg_defs[pos].flag->description, description, desc_size);
}

void ml__free_args_recursive(args_t* args) {

    long i = (long) args->size - 1;

    while(i >= 0) {
        if (args->arg_defs[i].type == ML_ARG_DEF_TYPE_FLAG) {
            ml__free_flag_recursive(args->arg_defs[i].flag);
        } else if(args->arg_defs[i].type == ML_ARG_DEF_TYPE_COMMAND) {}
        args->size -= 1;

        i -= 1;
    }

    if (args->arg_defs) {
        ML_FREE(args->arg_defs);
        args->arg_defs = NULL;
    }
}

void ml__free_flag_recursive(arg_flag_t* flag) {
    ML_FREE(flag->description);
    flag->description = NULL;
}
#endif
