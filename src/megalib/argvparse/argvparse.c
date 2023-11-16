//
// Created by rtmba on 15.11.2023.
//

#include "argvparse.h"

void ml__free_flag_recursive(arg_flag_t* flag);
void ml__free_args_recursive(args_t* args);
void ml__argvparser_init_global_flag(args_t* args, parameter_type_t type, bool required, const char* description, size_t desc_size);
void ml__argvparser_init_global_subcommand(args_t* args, char* name, size_t name_size, char* description, size_t desc_size);
void ml__argvparser_init_flag(arg_def_t* defs, size_t size, parameter_type_t type, bool required, const char* description, size_t desc_size);
void ml__argvparser_init_subcommand(arg_def_t* defs, size_t  size, char* name, size_t name_size, char* description, size_t desc_size);

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
        ml__argvparser_init_global_flag(args, type, required, description, desc_size);
        args->size = 1;
    } else {
        args->arg_defs = ml_realloc_or_fail(args->arg_defs, (args->size + 1) * sizeof(arg_def_t), "Failed to realloc required space for a global flag def");
        ml__argvparser_init_global_flag(args, type, required, description, desc_size);
        args->size += 1;
    }
}

ML_API void ml_argvparser_add_global_subcommand(/** [in,out] */ args_t* args, char* name, size_t name_size, char* description, size_t desc_size) {
    if (args->arg_defs == NULL) {
        args->arg_defs = (arg_def_t*) ML_MALLOC(sizeof(arg_def_t));
        ML_ASSERT(args->arg_defs != NULL && "Failed to malloc required space for a global subcommand def");
        ml__argvparser_init_global_subcommand(args, name, name_size, description, desc_size);
        args->size = 1;
    } else {
        args->arg_defs = ml_realloc_or_fail(args->arg_defs, (args->size + 1) * sizeof (arg_def_t), "Failed to realloc required space for a global subcommand def");
        ml__argvparser_init_global_subcommand(args, name, name_size, description, desc_size);
        args->size += 1;
    }
}

/**
 * Adds a flag to a @ref arg_def_t, will allocate memory.
 * @param defs The arg_def_t array to add a new flag
 * @param size The size of the arg_def_t array. Get updated with the new size, so please take that in the Picture!
 * @param required
 * @param description
 * @param desc_size
 */

ML_API void
ml_argvparser_add_flag(arg_def_t **defs, size_t *size, parameter_type_t type, bool required, const char *description,
                       size_t desc_size) {
    if (*defs == NULL) {
        *defs = (arg_def_t*) ML_MALLOC(sizeof(arg_def_t));
        ML_ASSERT(*defs != NULL && "Failed to malloc required space for a flag def");
        ml__argvparser_init_flag(*defs, *size, type, required, description, desc_size);
        *size = 1;
    } else {
        *defs = ml_realloc_or_fail(*defs, (*size + 1) * sizeof(arg_def_t), "Failed to realloc required space for flag def");
        ml__argvparser_init_flag(*defs, *size, type, required, description, desc_size);
        *size += 1;
    }
}
ML_API void ml_argvparser_add_subcommand(arg_def_t **defs, size_t *size, char* name, size_t  name_size, char *description,
                                         size_t desc_size) {
    if (*defs == NULL) {
        *defs = (arg_def_t*) ML_MALLOC(sizeof(arg_def_t));
        ML_ASSERT(*defs != NULL && "Failed to malloc required space for a subcommand def");
        ml__argvparser_init_subcommand(*defs, *size, name, name_size, description, desc_size);
        *size = 1;
    } else {
        *defs = ml_realloc_or_fail(*defs, (*size + 1) * sizeof(arg_def_t), "Failed to realloc required space for flag def");
        ml__argvparser_init_subcommand(*defs, *size, name, name_size, description, desc_size);
        *size += 1;
    }
}

void ml__argvparser_init_global_subcommand(args_t* args, char* name, size_t name_size, char* description, size_t desc_size) {
    ml__argvparser_init_subcommand(args->arg_defs, args->size, name, name_size, description, desc_size);
}

void ml__argvparser_init_subcommand(arg_def_t* defs, size_t size, char* name, size_t name_size, char* description, size_t desc_size) {
    defs[size].type = ML_ARG_DEF_TYPE_COMMAND;
    defs[size].command = ML_MALLOC(sizeof(arg_command_t));
    ML_ASSERT(defs[size].command && "Failed to malloc required space for a global subcommand");
    defs[size].command->args = NULL;
    defs[size].command->size = 0;
    defs[size].command->name = ML_MALLOC(name_size * sizeof (char));
    memcpy(defs[size].command->name, name, name_size);
    defs[size].command->description = ML_MALLOC(desc_size * sizeof (char));
    memcpy(defs[size].command->description, description, desc_size);
}

void ml__argvparser_init_flag(arg_def_t* defs, size_t size, parameter_type_t type, bool required, const char* description, size_t desc_size) {
    defs[size].type = ML_ARG_DEF_TYPE_FLAG;
    defs[size].flag = ML_MALLOC(sizeof(arg_flag_t));
    ML_ASSERT(defs[size].flag != NULL && "Failed to malloc required space for a global flag");
    defs[size].flag->type = type;
    defs[size].flag->required = required;
    defs[size].flag->description = ML_MALLOC(desc_size + sizeof(char));
    memcpy(defs[size].flag->description, description, desc_size);
}

void ml__argvparser_init_global_flag(args_t* args, parameter_type_t type, bool required, const char* description, size_t desc_size) {
    ml__argvparser_init_flag(args->arg_defs, args->size, type, required, description, desc_size);
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
