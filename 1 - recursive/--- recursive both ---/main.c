#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float computeSum(unsigned int n, float x, float factor,unsigned int i, float currentSum) {
    float currentResult = -1;

    if (i == n) {
        factor = -1 * factor * x * (3*i-5) / (3*i-3);
        printf("n = %d, result = %f, sum =%f\n",i,factor,currentSum);

        currentResult = factor;
        currentSum += factor;
        return currentSum;
    } else if (i == 1) {
        factor = 1;
        printf("n = %d, result = %f, sum =%f\n",i,factor,currentSum);

        currentResult = computeSum(n, x, factor, i+1,currentSum);

        currentSum += factor + currentResult;
        printf("n = %d, result = %f, sum =%f\n",i,factor,currentSum);
        return currentSum;
    } else {
        factor = -1 * factor * x * (3*i-5) / (3*i-3);
        printf("n = %d, result = %f, sum =%f\n",i,factor,currentSum);

        currentResult = computeSum(n, x, factor, i+1,currentSum);

        currentSum += factor + currentResult;
        printf("n = %d, result = %f, sum =%f\n",i,factor,currentSum);
        return currentSum;
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
    computeSum(n,x,0,1,0);
    return 0;
}
