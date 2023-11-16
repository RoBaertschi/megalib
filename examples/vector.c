//
// Created by rtmba on 14.11.2023.
//
#define ML_VECTOR_IMPLEMENTATION
#include "megalib/datastructures/vector.h"

int main(void) {
    vector_t* vec = ml_create_vector(sizeof(long));
    long new_var = 33;
    long delete = 23;

    ml_vector_push(vec, &new_var);
    printf("%ld\n",  *(long*)ml_vector_get(vec, 0));

    ml_vector_push(vec, &delete);
    printf("%ld\n", *(long*) ml_vector_get(vec, 1));

    ml_vector_pop(vec);
    // Should fail
    // printf("%ld\n", *(long*) ml_vector_get(vec, 1));

    ml_destroy_vector(vec);
}