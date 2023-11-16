//
// Created by rtmba on 14.11.2023.
//

#ifndef MEGALIB_VECTOR_H
#define MEGALIB_VECTOR_H

#include "megalib/megalib.h"
#include <stdlib.h>
#include <string.h>

typedef void (ml_vector_deleter)(void *);

/**
 * Please don't change any of these fields, as they are private.
 * */
typedef struct vector_t {
    size_t size;
    size_t capacity;
    size_t element_size;
    unsigned char* ptr;
    ml_vector_deleter* deleter;
} vector_t;


ML_API vector_t* ml_create_vector(size_t element_size);
ML_API void ml_destroy_vector(vector_t* vector);
ML_API void ml_vector_push(vector_t * vector, void* element);
// ML_API vector_t ml_create_vector_from_array(size_t element_size, void* existing_data, size_t length);
ML_API void* ml_vector_get(vector_t* vector, size_t index);
ML_API void ml_vector_pop(vector_t* vector);
ML_API void* ml_vector_back(vector_t* vector);

#endif //MEGALIB_VECTOR_H
