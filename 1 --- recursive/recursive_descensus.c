#include <stdio.h>
#include <stdlib.h>

float sum = 0;

float recursive(unsigned int i, float x, int n) {
    if (i == 1) {
        float res = 1;
        sum += res;

        printf("Result in %d iteration = %f; Sum of all iteration =%f;\n", i, res, sum);
        return res;
    }
    else if (i <= n) {
        float res = 0;

        printf("Result in %d iteration = %f; Sum of all iteration =%f;\n", i, res, sum);

        float prev = recursive(i - 1, x, n);
        res = -1 * prev * x * (3 * i - 5) / (float)(3 * i - 3);
        sum += res;

        printf("Result in %d iteration = %f; Sum of all iteration =%f;\n", i, res, sum);
        return res;
    } else {
        return 0;
    }
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
    recursive(n, x, n);

    return 0;
}
