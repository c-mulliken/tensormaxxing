#include <stdbool.h>

typedef struct {
    int **indices;
    int count;
} ArrayIndices;

typedef struct {
    int *indices;
    int count;
} LinearIndices;

typedef struct {
    int* data;  
    int* shape;
    int* strides;
    int* backstrides;

    int ndim;
    int itemsize;
    int size;

    ArrayIndices *idxs;
    LinearIndices *lidxs;
} Array;
