#include <stdio.h>
#include <stdlib.h>

#include <klee/klee.h>

int main() {
    unsigned raw_size;
    klee_make_symbolic(&raw_size, sizeof(raw_size), "raw_size");

    unsigned buff_size = 1024;

    unsigned buffering_ratio = raw_size / buff_size;

    // Possible error!
    unsigned some_metric = 100 / buffering_ratio;

    return some_metric;
}
