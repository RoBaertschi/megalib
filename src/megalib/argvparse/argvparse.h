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
ML_API void ml_argvparser_add_flag(arg_def_t **defs, size_t *size, parameter_type_t type, bool required, const char *description,
                       size_t desc_size);

ML_API void ml_argvparser_add_subcommand(arg_def_t **defs, size_t *size, char* name, size_t  name_size, char *description,
                                         size_t desc_size);
#endif //MEGALIB_ARGVPARSE_H

