#include "tropar.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// free arr from memory
void trFree(Array *arr) {
    free(arr->data);
    free(arr->strides);
    free(arr->backstrides);
    free(arr->ndim);
    free(arr->itemsize);
    free(arr->shape);
    free(arr->size);
};

void __checkNull(void *value) {
    if (value == NULL) {
        fprintf(stderr, 'Memory allocation failed');
        exit(1);
    }
};

void __recalculateStrides__(Array *arr) {
    arr->strides[arr->ndim - 1] = arr->itemsize;
    for (int i = 0; i < arr->ndim - 2; i++) {
        arr->strides[i] = arr->strides[i + 1] * arr->shape[i + 1];
    }
}

void __recalculateBackstrides__(Array *arr) {
    for (int i = arr->ndim - 1; i >= 0; i--) {
        arr->backstrides[i] = -1 * arr->strides[i] * (arr->shape[i] - 1);
    }
}

void __createArrayIndices__(Array *arr){
    if (arr->idxs != NULL) {
        for (int i = 0; i < arr->idxs->count; i++){
            free(arr->idxs->indices[i]);
        }
        free(arr->idxs->indices);
        free(arr->idxs);
    }
    arr->idxs = (ArrayIndices *)malloc(sizeof(ArrayIndices));
    _checkNull(arr->idxs);
    arr->idxs->count = arr->totalsize;
    arr->idxs->indices = (int **)malloc(arr->idxs->count * sizeof(int *));
    _checkNull(arr->idxs->indices);
    for (int i = 0; i < arr->idxs->count; i++)
    {
        arr->idxs->indices[i] = (int *)malloc(arr->ndim * sizeof(int));
        _checkNull(arr->idxs->indices[i]);
    }
}

void __setArrayMetadata__ {
    __recalculateStrides__(arr);
    __recalculateBackstrides__(arr);
}

Array trCreate(const int *shape, int ndim) {
    if (ndim <= 0) {
        printf(stderr, 'ndim too small, cannot create array of dim %d', ndim);
        exit(1);
    }

    Array *arr = (Array *)malloc(sizeof(Array));
    __checkNull(arr);

    arr->ndim = ndim;
    arr->shape = (int *)malloc(ndim * sizeof(int));
    arr->strides = (int *)malloc(ndim * sizeof(int));
    arr->backstrides = (int *)malloc(ndim * sizeof(int));
    
    __checkNull(arr->shape);
    __checkNull(arr->strides);
    __checkNull(arr->backstrides);

    arr->itemsize = sizeof(float);
    arr->size = 1;

    for (int i = 0; i < arr-> ndim; i++) {
        arr->shape[i] = shape[i];
        arr->size *= shape[i];
    }

    
}
