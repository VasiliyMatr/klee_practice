#include <stdio.h>
#include <stdlib.h>

#include <klee/klee.h>

int main() {
    void *buff = calloc(10, 1);

    int status;
    klee_make_symbolic(&status, sizeof(status), "status");

    int failure_is_critical;
    klee_make_symbolic(&failure_is_critical, sizeof(failure_is_critical), "failure_is_critical");

    switch (status) {
        case 1:
        case 2:
        case 3:
            break; // OK

        // error
        default:
            free(buff);
            if (failure_is_critical) {
                return -1;
            }
    }

    free(buff);
    return 0;
}
