//
// Created by rtmba on 13.11.2023.
//

#ifndef MEGALIB_ARGVPARSE_H
#define MEGALIB_ARGVPARSE_H

#define ENUM_NAMESPACE(enum_name, name) ML_##enum_name##_TYPE_##name

#define ENS(name) ENUM_NAMESPACE(PARAMETER, name)
typedef enum parameter_type_t {
    ENS(NONE),
    ENS(STRING),
    ENS(FILE),
    ENS(FLAG),
} parameter_type_t;
#undef ENS

#define ENS(name) ENUM_NAMESPACE(ARG_DEF, name)
typedef enum arg_def_type_t {
    ENS(FLAG),
} arg_def_type_t;
#undef ENS

typedef struct arg_flag_t {
    bool required;
    parameter_type_t type;

} arg_flag_t;

typedef union arg_def_t {
    arg_flag_t flag;

} arg_def_t;

typedef struct args_t {
    size_t size;
    arg_def_t arg_defs[];
} args_t;


#endif //MEGALIB_ARGVPARSE_H
