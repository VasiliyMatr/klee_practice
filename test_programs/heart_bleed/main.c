#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <klee/klee.h>

void send_buff(const char *buff, int size) {
    // Just touch memory
    // Note: such cycles can significantly increase paths
    // num when parametrised with symbolic variables
    for (int i = 0; i != size; ++i) {
        (void)buff[i];
    }
}

#define DATA1 "foo! bar! baz!"
#define DATA2 "password=\"aboba\""

int main() {
    int read_len;
    klee_make_symbolic(&read_len, sizeof(read_len), "read_len");

    char *data1 = calloc (sizeof(DATA1), 1);
    char *data2 = calloc (sizeof(DATA2), 1);

    if (data1 == NULL || data2 == NULL) {
        return -1;
    }

    memcpy(data1, DATA1, sizeof(DATA1));
    memcpy(data2, DATA2, sizeof(DATA2));

    // Normal request -> OK
    if (read_len <= strlen(data1)) {
        send_buff(data1, read_len);
        return 0;
    }

    int detected_suspicious_activity;
    klee_make_symbolic(&detected_suspicious_activity, sizeof(detected_suspicious_activity), "detected_suspicious_activity");

    // Suspicious request is reported -> OK
    if (detected_suspicious_activity) {
        return -1;
    }

    // Typo leads to error on wrong request handling
    int safe_read_len = strlen(data1);
    send_buff(data1, read_len); // copy-pasted !

    return 0;
}
