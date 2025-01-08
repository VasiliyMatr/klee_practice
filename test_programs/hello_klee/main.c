#include <stdio.h>
#include <stdlib.h>

#include <klee/klee.h>

int main() {
    int foo;
    klee_make_symbolic(&foo, sizeof(foo), "foo");

    int bar;
    klee_make_symbolic(&bar, sizeof(bar), "bar");

    if (foo <= 0 || bar <= 0) {
        return -1;
    }

    if (foo > 10 || bar > 10) {
        return -2;
    }

    int iter_num = 0;
    for (; foo < bar; ++foo) {
        ++iter_num;
    }

    return iter_num;
}