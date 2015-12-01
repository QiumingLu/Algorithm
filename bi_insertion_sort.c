#include <stdio.h>
#include <malloc.h>

#define MAXSIZE 1000		//待排顺序表的最大长度

typedef int KeyType;		//关键字的类型为整型

typedef struct {
  KeyType key;			    //关键字项
} RcdType;					//记录字项

typedef struct {
  RcdType r[MAXSIZE + 1];	//r[0]闲置
  int length;
}SqList;

void BiInsertionSort(SqList *L) {
  if (L == NULL) return;
  int i, j, low, high, min;

  for (i = 2; i <= L->length; ++i) {
    if (L->r[i].key < L->r[i-1].key) {
      L->r[0] = L->r[i];

      //在L[1..i-1]中折半查找插入位置（high+1）
      low = 1;
      high = i -1;
      while (low <= high) {
        min = (low+high)/2;			//折半
        if (L->r[min].key < L->r[i].key) {
          low = min + 1;			//插入高半区
        } else {
          high = min - 1;			//插入低半区
        }
      }

      for (j = i - 1; j >= high+1; --j) {
        L->r[j+1] = L->r[j];		//记录后移
      }
      L->r[high+1] = L->r[0];			//插入
    }
  }
}

int main() {
  SqList *L = (SqList*) malloc(sizeof(SqList));
  L->length = 5;
  L->r[1].key = 5;
  L->r[2].key = 1;
  L->r[3].key = 1;
  L->r[4].key = 4;
  L->r[5].key = 8;

  BiInsertionSort(L);

  int i;
  for (i = 1; i <= L->length; ++i) {
    printf("%d\t", L->r[i].key);
  }
  printf("\n");

  free(L);

  return 0;
}

