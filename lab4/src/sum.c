#include "utils.h"

struct SumArgs {
    int *array;
    int begin;
    int end;
};

long long int Sum(const struct SumArgs* args) {
    long long int sum = 0;

    for (int i = args->begin; i < args->end; i++) {
        sum += args->array[i];
    }

    return sum;
}