# klee_practice

Repo for KLEE practice

### Test programs

Test programs with KLEE output screenshots can be found in `test_programs` folder

### How to run

klee & clang (version 13.0.0 or greater) are required

```Bash
export KLEE_INCLUDES=...
export TEST_PROGRAM=...

clang -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone -I ${KLEE_INCLUDES} ${TEST_PROGRAM}/main.c
klee --libc=uclibc main.bc
```
