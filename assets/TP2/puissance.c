//V0.0.2

#include <stdio.h>
#include <stdlib.h>

int puissance(int x, int n) {
    int result = 1;
    while(n > 0) {
        result = result * x;
        n--;
    }
    return result;
}

int main(int argc, char **argv) {
    int x = atoi(argv[1]);
    int n = atoi(argv[2]);
    printf("%i", puissance(x, n));
}