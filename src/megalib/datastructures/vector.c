//
// Created by rtmba on 15.11.2023.
//

#include "vector.h"

void ml__vector_reallocate(vector_t* vector, size_t new_size);

ML_API vector_t* ml_create_vector(size_t element_size) {
    vector_t* vector = (vector_t*) ML_MALLOC(sizeof(vector_t));
    vector->size = 0;
    vector->element_size = element_size;
    vector->ptr = ML_MALLOC(2 * element_size);
    vector->capacity = 2;
    vector->deleter = NULL;
    return vector;
}

ML_API void ml_destroy_vector(vector_t* vector) {
    free(vector->ptr);
    free(vector);
}

ML_API void ml_vector_push(vector_t* vector, void* element) {
    // If size is, for some reason bigger then the actual capacity, then it will reallocate the double of the size, if that is not enough for the vector
    if (vector->size >= vector->capacity) {
        ml__vector_reallocate(vector,
                              vector->capacity * 2 > vector->size ? vector->capacity * 2 : vector->size * 2
                              );
    }

    memcpy(vector->ptr + (vector->size * vector->element_size), element, vector->element_size);
    vector->size++;
}

ML_API void* ml_vector_get(vector_t* vector, size_t index) {
    ML_ASSERT(vector->size > index && "Cannot get a vector that is out of size");
    return (void*)(vector->ptr + (index * vector->element_size));
}

ML_API void ml_vector_pop(vector_t* vector) {
    ML_ASSERT(vector->size > 0 && "Can not pop a empty vector");

    if (vector->deleter != NULL) {
        vector->deleter(ml_vector_back(vector));
    }

    vector->size--;
}

ML_API void* ml_vector_back(vector_t* vector) {
    return vector->ptr + (vector->size - 1) * vector->element_size;
}

void ml__vector_reallocate(vector_t* vector, size_t new_size) {
    vector->ptr = ml_realloc_or_fail(
            vector->ptr,
            new_size,
            "Could not reallocate the internal dynamic array from the Vector"
    );
    vector->capacity = new_size;
}

