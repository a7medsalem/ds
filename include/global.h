#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifndef NDEBUG
    #define _DEBUG_
    #define DEBUG
    #define DEBUG_MEM
#endif

#ifndef _G_TYPES_
    #define _G_TYPES_
    #include <stdint.h>
    //
    #ifndef BYTE
    #define BYTE    int8_t
    #endif
    #define SHORT   int16_t
    #define INT     int32_t
    #ifndef LONG
    #define LONG    int64_t
    #endif
    #ifndef FLOAT
    #define FLOAT   float
    #endif
    //
    #ifndef BOOLEAN
    #define BOOLEAN int8_t
    #endif
    #define TRUE    1
    #define FALSE   0
#endif

#endif //!_GLOBAL_H_