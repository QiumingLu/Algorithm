#include <stdio.h>

void MinHeapFixup(int array[], int i) {
  int j, temp;
  j = (i-1)/2;               //新加入i结点，其父节点为(i-1)/2
  temp = array[i];
  while (j>= 0 && i != 0) {
    if(array[j] <= temp) break;
    array[i] = array[j];	//把较大的子节点往下移动，替换它的子节点
    i = j;
    j = (i-1)/2;
  }
  array[i] = temp;
}

//往最小堆里面加入新的数据nNum 
void MinHeapAddNumber(int array[], int n, int nNum)	{
  array[n] = nNum;
  MinHeapFixup(array, n);
}
	
//从i结点开始调整，n为结点总数，从0开始计算，i结点的子节点为2i+1,2i+2
void MinHeapFixdown(int array[], int i, int n) {
  int j, temp;
  j = 2*i + 1;
  temp = array[i];
  while (j < n) {
    if (j+1 < n && array[j + 1] < array[j]) {
      j++;
    }
    if (array[j] >= temp) {
      break;
    }
    array[i] = array[j];
    i = j;
    j = 2*i + 1;
  }
  array[i] = temp;
}


//在最小堆中删除数
void MinHeadDeleteNumber(int array[], int n) {
  int temp;
  temp = array[0];
  array[0] = array[n - 1];
  array[n - 1] = temp;
  MinHeapFixdown(array, 0, n - 1);
}

//建立最小堆
void MakeMinHeap(int array[], int n) {
  int i;
  for (i = n/2 -1; i >= 0; --i)	{
    //叶子节点已经是合法堆，父节点则不一定，对于完全二叉树来说，父节点的个数为n/2
    MinHeapFixdown(array, i, n);
  }
}

//最小堆排序后的是递减数组，要得到递增数组，可以使用最大堆
void MinHeapSortTodescendarray(int array[], int n) {
  int i;
  int temp;
  for (i = n -1; i >= 1; --i) {
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    MinHeapFixdown(array, 0, i);
  }
}


//对堆进行排序会破坏堆的结构，需要重新建堆
int main() {
  int array[9] = {1, 3, 2, 0, 89, 4, 52, 9, 99};
  MakeMinHeap(array, 9);

  int i;
  for (i = 0; i < 9; ++i) {
    printf("%d\t", array[i]);
  }
  printf("\n");
  /*
     MinHeapSortTodescendarray(array, 9);

     for (i = 0; i < 9; ++i)
     {
     printf("%d\t", array[i]);
     }
     printf("\n");
     */
  MinHeapAddNumber(array, 9, 100);
  //	MakeMinHeap(array, 10);
  //	MinHeapSortTodescendarray(array, 10);

  for (i = 0; i < 10; ++i) {
    printf("%d\t", array[i]);
  }
  printf("\n");

  MinHeadDeleteNumber(array, 10);
  //	MakeMinHeap(array, 9);
  //	MinHeapSortTodescendarray(array, 9);
  for (i = 0; i < 9; ++i) {
    printf("%d\t", array[i]);
  }
  printf("\n");

  MinHeapSortTodescendarray(array, 9);

  for (i = 0; i < 9; ++i) {
    printf("%d\t", array[i]);
  }
  printf("\n");

  return 0;
}
