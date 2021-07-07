#include <stdio.h>

float div (float a, float b);
float mult (float a, float b);
long fac (int a);
int bsearch (float ra[], int low, int high, float target);
int bsearch2(float ra[], int low, int high, float target, float results[], int size);

int main() {
  float a = 5, b = 8;
  printf("%f divided by %f is %f\n", a, b, div(a, b));

  // Part 2 - to test mult
  printf("%f x %f is %f (expected 40)\n", a, b, mult(a, b));

  // Part 2 - to test fac
  printf("factorial of -4 is %ld (expected 0)\n", fac(-4));
  printf("factorial of 10 is %ld (expected 3628800)\n", fac(10));

  // Part 3 - to test bsearch
  float myray[] = {3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.0, 10, 15, 20, 25, 100};
  int capacity = sizeof(myray) / sizeof(myray[0]);
  int where = bsearch(myray, 0, capacity-1, 5.6);
  printf("binary search of 5.6 found at index: %d\n", where);
  where = bsearch(myray, 0, capacity-1, 30);
  printf("binary search of 30 found at index: %d\n", where);

  // Part 3 - to test bsearch2
  float results[12] = {0};
  where = bsearch2(myray, 0, capacity-1, 10, results, 0);
  printf("binary search of 10 found at index: %d\n", where);
  printf("results array is: " );
  for (int i = 0; i < capacity; i++) {
    printf("%.1f ", results[i]);
  }
  printf("\n");

  return 0;
}

float div(float a, float b) {
  return a / b;
}

float mult(float a, float b) {
  return a * b;
}


long fac(int a) {
  if (a <= 0) {
    return 0;
  }
  if (a == 1) {
    return 1;
  }
  else {
    return a * fac(a - 1);

  }

}

//binary search
int bsearch (float ra[], int low, int high, float target) {

  while (low <= high) {
    int m = (low + high)/2;
    if (ra[m] == target) {
      return m;

    }
    else if (ra[m] > target) {
      high = m - 1; 
      //recursive: bsearch (ra, low, m - 1, target);
    }
    else if (ra[m] < target) {
      low = m + 1;
      //recursive: bsearch (ra, m + 1, high, target);
    }
 
  }
  return -1;

}

int bsearch2(float ra[], int low, int high, float target, float results[], int size) {
   while (low <= high) {
    int m = (low + high)/2;
    if (ra[m] < target) {
      results[size] = ra[m];
      low = m + 1;
      size++;
    }
    else if (ra[m] > target) {
      results[size] = ra[m];
      high = m - 1;
      size++;
      
    }
    else {
      results[size] = ra[m];
      size++;
      return m;
    }

  }
  return -1;

}
