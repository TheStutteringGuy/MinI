#include <stdio.h>

int main() {
    int *p = NULL;
    *p = 42;  // Dereferencing a NULL pointer causes a segfault
    return 0;
}
