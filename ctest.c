#include <stdio.h>

//#define BIGTING 3000000

// pointer declarations in functions indicate that the x in the *x is being dereferenced
// so that one can physically moify the value that x is pointing to (which is *x)

// modify all values in a given int array by adding 3 to each value
void moda(int *ar, int n);
// modify a particular int located in memory by adding 100 to value
void modaa(int *a);
// print all values in int array length n to stdout
void printa(int *ar, int n);

int main() {
  register int n = 9;
  int a[] = {3, 5, 3, 2, 6, 34, 2, 3, 1};
  // can get the size of an array by taking size of all array elements divided by individual
  // array element type (size)
  printf("size of a[]: %d\n", sizeof(a) / sizeof(int));
  // given an a[], a degrades to a pointer to a[0]
  moda(a, n);
  printf("original int array\n");
  printa(a, n);
  printf("modified int array\n");
  // must pass the pointer to a[n - 1]
  modaa(&a[n - 1]);
  printa(a, n);
  printf("doubly-modified int array\n");
  // doing some pointer arithmetic here; same as &a[n - 1]
  modaa(a + (n - 1));
  printa(a, n);
  return 0;
}

void moda(int *ar, int n) {
  int i;
  for (i = 0; i < n; i++) {
    ar[i] = ar[i] + 3;
  }
}

void modaa(int *a) {
  // dereference the pointer to physically modify the value pointed to by the pointer
  *a = *a + 100;
}

void printa(int *a, int n) {
  int i;
  printf("{ ");
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("}\n");
}
