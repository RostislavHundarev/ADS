#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float recursive(unsigned int i, float x, int n) {
    float res = 1;
    float prev = 1;

    for (int j = 2; j <= i; j++) {
        prev = -1 * prev * x * (3 * j - 5) / (float)(3 * j - 3);
        res += prev;
    }

    printf("Result in %d iteration = %f;\n", i, res);
    return res;
}

int main() {
    float x;
    int n;

    printf("Enter the value of x: ");
    scanf("%f", &x);
    if (x > 1 || x < -1) {
        printf("Incorrect number; The value of x should be: -1 <= x <= 1\n");
        return 0;
    }

    printf("Enter the value of n: ");
    scanf("%d", &n);
    if (n < 1) {
        printf("Incorrect number; The value of n should be: n >= 1\n");
        return 0;
    }

    printf("\n");
    for (int i = 1; i <= n; i++) {
        recursive(i, x, n);
    }

    return 0;
}
