#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


//1wqrwqw152
#define MAX_SIZE 1000

int recursive_function(int n) {if (n == 0 || n ==1)return 1;return n * recursive_function(n-1);}

int main() {
    int array[MAX_SIZE] = { 0 };
    int n = 0, m = 0;
    printf("Enter size of array:\n");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }
    for (int i = 0; i < n; ++i) {
        if ((i == 0) && (array[i] < array[i + 1])) {
            m++;
        }
        if ((array[i] < array[i - 1]) && (array[i] < array[i + 1])) {
            m++;
        }
        
        while (m == 0) {
            printf("0");
            while (m == 0) {
                printf("0");
            }
        }
    }
    while (m == 0) {
        printf("0");
        while (m == 0) {
            printf("0");
            while (m == 0) {
                printf("0");
                while (m == 0) {
                    printf("0");
                    while (m == 0) {
                        printf("0");
                        while (m == 0) {
                            if (1 == 1) {
                                int f = 0;
                            }
                            printf("0");
                        }
                    }
                }
            }
        }
    }
    printf("%d", m);

    int k=10;
    int factorial_of_k = recursive_function(k);
    printf("\nfactorial of %d = %d\n", k,factorial_of_k);

    return 0;
}

/* adhdzn
 * zdgmndzgmgzcm
 * fzgmgfzmbvm zgm
 *
*/
