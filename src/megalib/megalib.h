#ifndef MEGALIB_MEGALIB_H
#define MEGALIB_MEGALIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#ifndef ML_MALLOC
#   define ML_MALLOC(size) malloc(size)
#endif

#ifndef ML_FREE
#   define ML_FREE(ptr) free(ptr)
#endif

#ifndef ML_REALLOC
#   define ML_REALLOC(ptr, newsize) realloc(ptr, newsize)
#endif

/**
 * @brief Reallocates ptr and sets it to the new buffer. If the operation fails, it will assert with the specified message.
 */
// #define ML_REALLOC_OR_FAIL(ptr, newsize, message, type_t) type_t * temp = ( type_t *) ML_REALLOC(ptr, newsize); \
//                                                if(temp == NULL) { ML_FREE(ptr);  ML_ASSERT(false && message); } else { printf("ptr: %x, temp: %x\n", ptr, temp);ptr = temp; printf("ptr: %x\n", ptr); }
#ifndef ML_ASSERT
#   define ML_ASSERT(exp) assert(exp)
#endif

inline void* ml_realloc_or_fail(void* ptr, size_t newsize, const char* message) {
    void* temp = ML_REALLOC(ptr, newsize);
    if (temp == NULL) {
        ML_FREE(ptr);
        ML_ASSERT(false && message);
        return NULL;
    } else {
        return temp;
    }
}

#ifdef _WIN32
#    ifdef BUILD_LIBTYPE_SHARED
#        define ML_API __declspec(dllexport)
#    elif defined(USE_LIBTYPE_SHARED)
#        define ML_API __declspec(dllimport)
#    endif
#endif

#ifndef ML_API
#    define ML_API
#endif


#endif //MEGALIB_MEGALIB_H
