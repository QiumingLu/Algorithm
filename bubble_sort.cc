#include <stdio.h>

void BubbleSort(int array[], int n) {
  int i, j, temp;
  for (i = 0; i < n; ++i) {
    for (j = i; j < n; ++j) {
      if (array[i] > array[j]) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}

int main() {
  int i;
  int array[8] = {2,4,3,1,4,5,6,7};

  BubbleSort(array, 8);

  for (i = 0; i < 8; ++i) {
    printf("%d\t", array[i]);
  }

  printf("\n");
  return 0;
}
