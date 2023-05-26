#include <stdio.h>
#include <stdlib.h>

float summary = 0;

#include <stdio.h>

float recursive(unsigned int n, float x, float result, unsigned int i, float summary) {
    float endResult = -1;

    if (i <= n) {
        if (i == 1) {
            result = 1;
            summary += result;

            printf("n = %d, Result = %f, Sum = %f\n", i, result,summary);
        } else {
            result = -1 * result * x * (3 * i - 5) / (3 * i - 3);
            summary += result;

            printf("n = %d, Result = %f, Sum = %f\n", i, result,summary);
        }

        if (i < n) {
            endResult = recursive(n, x, result, i + 1, summary);
            printf("n = %d, Result = %f, Sum = %f\n", i, result,summary);

            return endResult;
        } else {
            endResult = result;

            return endResult;
        }
    }

    return endResult;
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
    recursive(n,x,0,1,0);

    return 0;
}
