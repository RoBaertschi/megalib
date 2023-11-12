#ifndef MEGALIB_MEGALIB_H
#define MEGALIB_MEGALIB_H


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
