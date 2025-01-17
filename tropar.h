#include <stdbool.h>

typedef struct {
    int* data;  
    int* shape;
    int* strides;

    int ndim;
    int entrysize;
    int size;
} Array;
