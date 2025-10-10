#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//a) Generate all the prime numbers smaller than a given natural number `n`.
void sieve_eratostene(int n, int v[], int *x) {
    /*
    Calculates the prime numbers smaller than a given number
     @param n The upper limit for finding prime numbers.
     @param v An output array where the function stores the prime numbers found.
    */
    bool prim[n];
    for (int i = 0; i < n; i++) {
        prim[i] = true;
    }

    prim[0] = false;
    prim[1] = false;

    for (int i = 2; i * i < n; i++) {
        if (prim[i]) {
            for (int j = i * i; j < n; j += i) {
                prim[j] = false;
            }
        }
    }
    *x = 0;
    for (int i = 0; i < n; i++) {
        if (prim[i]) {
            v[*x] = i;
            (*x)++;
        }
    }
}

void print_primes(int v[], int count, int n){
    /*
    The function prints the prime numbers smaller than n
    @param v is a vector which contains the prime numbers
    @param count is the number of the primes 
    @param n is the upper limit for finding prime numbers. It is used for printing the result
    */
    printf("Primes up to %d:\n", n);
    for (int i = 0; i < count; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

//b) Given a vector of numbers, find the longest increasing contiguous subsequence, such the sum of that any 
//2 consecutive elements is a prime number.

bool is_prime(int nr){
    /*
    This function verifies if the given number is prime
    @param nr is the number which has to be verified
    */
    if(nr < 2)
        return false;
    if(nr == 2)
        return true;
    if(nr % 2 == 0)
        return false;
    for(int i = 3; i * i <= nr; i = i + 2)
        if(nr % i == 0)
            return false;
    return true;
}

void print_subsequence(int arr[], int first, int last){
    /*
    This function prints a contiguous subsequence from index `first` to `last - 1` of the given array `arr`.
    @param arr The input array containing the numbers.
    @param first The starting index of the subsequence (inclusive).
    @param last The ending index of the subsequence (exclusive).
    */
    printf("Longest valid sequence of the given array:\n");
        for (int i = first; i < last; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
}

void longest_valid_subsequence(int arr[], int n) {
    int max_len = 0, start = 0;
    /*
    This function identifies the longest contiguous subsequence in the given array `arr`
    where consecutive elements form an increasing sequence and the sum of adjacent elements
    is a prime number. The found subsequence is printed using `print_subsequence()`.
    @param arr The input array of integers.
    @param n The number of elements in the array.
    */
    for (int i = 0; i < n - 1; i++) {
        int len = 1;
        int j = i;
        while (j < n - 1 && arr[j] < arr[j + 1] && is_prime(arr[j] + arr[j + 1])) {
            len++;
            j++;
        }
    if (len > max_len) {
            max_len = len;
            start = i;
        }
    }

    if (max_len > 1) {
        print_subsequence(arr, start, start + max_len);
    } 
    else {
        printf("No valid increasing contiguous subsequence.\n");
    }
    }

void print_menu(){
    printf("1. Insert numbers\n");
    printf("2. Generate all the prime numbers smaller than n\n");
    printf("3. Find the longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number\n");
    printf("x. Exit\n");
}

int main() {
    int n = 0;
    int *v = NULL; 

    while (1) {
        print_menu();
        char option;
        scanf(" %c", &option); 
        switch(option){
        case('1'): {
            printf("Introduce a number n: ");
            scanf("%d", &n);

            if (v != NULL) {
                free(v);
            }

            v = (int *)malloc(n * sizeof(int));
        
            printf("Introduce a vector of length %d: ", n);
            for (int i = 0; i < n; i++) {
                scanf("%d", &v[i]);
            }

        } 
        case ('2'): {
            if (n == 0) {
                printf("Please insert numbers first\n\n");
                continue;
            }
            int count, primes[n];
            sieve_eratostene(n, primes, &count);
            print_primes(primes, count, n);
            printf("\n");

        } 
        case ('3'): {
            if (n == 0) {
                printf("Please insert numbers first\n\n");
                continue;
            }
            longest_valid_subsequence(v, n);
            printf("\n");

        } 
        case ('x'): {
            free(v); 
            return 0;

        } 
        default: {
            printf("Invalid option\n\n");
        }
    }
  }
}