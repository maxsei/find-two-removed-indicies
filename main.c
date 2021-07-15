#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void print_array_int(int * array, size_t length);
int search_array_int(int * array, size_t length, int x);
int search_int(int length, bool(*f)(int));

int main(int argc, char *argv[])
{
  /* Allocate array of size 100 with 2 elements removed. */
  int n = 100;
  int n_removed = 2;
  int n_arr = n - n_removed;

  int *arr = (int*)malloc(sizeof(int) * n_arr);
  int *removed = (int*)malloc(sizeof(int) * n_removed);

  /* Seed random number generator. */
  srand48(0);

  /* Randomly initialize removed with random numbers between [0, n-1]. */
  {
    void *end;
    int *p = &removed[0];
    int i = 0;
    for (end = &removed[n_removed]; p != end; p++) {
      *p = (int)(drand48() * 100);
      i++;
    }
  }

  
  /* Set array to [0, n-1] ascending. */
  {
    void *end;
    int *p = &arr[0];;
    int i = 0;
    int j;

    for (end = &arr[n_arr]; p != end; p++) {
      /* If i is in removed then increment i once before setting arr to skip. */
      j = search_array_int(removed, n_removed, i);
      if ( (j != n_removed) && (removed[j] == i ) )
        i++;
      *p = i;
      i++;
    }
  }
  
  /* Problem statment. */
  printf("dataset:\n\n");
  print_array_int(arr, n_arr);
  printf("\n");

  printf("solution:\n\n");
  print_array_int(removed, n_removed);
  printf("\n");

  /* Solution here. */
  {
    void *end;
    int *p = &arr[0];
    int prev = *p;
    p++;

    int *removed_found = (int*)malloc(sizeof(int) * n_removed);
    int *p_removed_found = &removed_found[0];


    for (end = &arr[n_arr]; p != end; p++) {
      if ( (*p - prev) > 1 ) {
        *p_removed_found = *p - 1;
        p_removed_found++;
      }
      prev = *p;
    }

    printf("my solution:\n");
    print_array_int(removed_found, n_removed);
    printf("\n");
  }

  return 0;
}

void print_array_int(int * array, size_t length)
{
    void *end;
    int *p = &array[0];
    for (end = &array[length]; p != end; p++) 
      printf("%d\n", *p);
}


int * search_array_int_array;
int * search_array_int_x;

bool search_array_int_cmp(int i) {
  return search_array_int_array[i] >= *search_array_int_x;
}

int search_array_int(int * array, size_t length, int x) {
  int result;

  search_array_int_array = array;
  search_array_int_x = &x;

  result = search_int(length, search_array_int_cmp);

  search_array_int_array = NULL;
  search_array_int_x = NULL;

  return result;
}

int search_int(int j, bool(*f)(int)) {
    // Define f(-1) == false and f(n) == true.
    // Invariant: f(i-1) == false, f(j) == true.
    int i = 0;
    while ( i < j ) {
        int h = (int)( ( (unsigned int)(i + j) ) >> 1 ); // avoid overflow when computing h
        // i ≤ h < j
        if ( !f(h) ) {
            i = h + 1; // preserves f(i-1) == false
        } else {
            j = h; // preserves f(j) == true
        }
    }
    // i == j, f(i-1) == false, and f(j) (= f(i)) == true  =>  answer is i.
    return i;
}
