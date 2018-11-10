#include <stdio.h>
#include "brick.h"

int main (int argc, char** argv) {
    ev3_init();
    ev3_uninit();
    printf("brum\n");

    return 0;
}
