#include <stdio.h>

#define MAXSIZE 1000	//待排顺序表的最大长度
typedef int KeyType;	//关键字类型为整型

typedef struct {
  KeyType key;		//关键字项
}RcdType;				//记录类型

typedef struct {
  RcdType r[MAXSIZE + 1];		//r[0]闲置
  int length;
}SqList;

void InsertionSort(SqList *L) {
  int i;
  int j;
  if (L == NULL) return;
  for (i = 2; i <= L->length; ++i) {
    if (L->r[i].key < L->r[i-1].key) {
      L->r[0] = L->r[i];
      for (j = i - 1; L->r[0].key < L->r[j].key; --j) {
        L->r[j+1] = L->r[j];
      }
      L->r[j+1] = L->r[0];
    }
  }
}

int main() {
  SqList L;
  L.length = 5;
  L.r[1].key = 1;
  L.r[2].key = 4;
  L.r[3].key = 3;
  L.r[4].key = 2;
  L.r[5].key = 0;
  InsertionSort(&L);
  int i;
  for (i = 1; i <= L.length; ++i) {
    printf("%d\t", L.r[i].key);
  }

  printf("\n");

  return 0;
}
