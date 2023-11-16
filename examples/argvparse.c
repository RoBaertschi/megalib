//
// Created by rtmba on 13.11.2023.
//
#define ML_ARGVPARSE_IMPLEMENTATION
#include "megalib/argvparse/argvparse.h"

int main(void) {
    args_t* args = ml_create_argvparser("Test", 5);

    char desc[] = "Hello world!";
    ml_argvparser_add_global_flag(
            args,
            ML_PARAMETER_TYPE_NONE,
            true,
            desc,
            strlen(desc) + 1
            );
    char tdesc[] = "Test World!";
    ml_argvparser_add_global_flag(
            args,
            ML_PARAMETER_TYPE_NONE,
            true,
            tdesc,
            strlen(tdesc) + 1
    );
    char name[] = "new";
    char description[] = "New stuff";

    ml_argvparser_add_global_subcommand(
            args,
            name,
            strlen(name) + 1,
            description,
            10
            );

    char testDesc[] = "testDesc";

    ml_argvparser_add_flag(
            &args->arg_defs[2].command->args,
            &args->arg_defs[2].command->size,
            ML_PARAMETER_TYPE_NONE,
            true,
            testDesc,
            strlen(testDesc) + 1
            );

    printf("%s, %s, %s, %s, %s",
           args->arg_defs[0].flag->description,
           args->arg_defs[1].flag->description,
           args->arg_defs[2].command->name, args->arg_defs[2].command->description,
           args->arg_defs[2].command->args[0].flag->description
           );
    ml_destroy_argvparser(args);
}