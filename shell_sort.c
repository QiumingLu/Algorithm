#include <stdio.h>

#define MAXSIZE 1000

typedef int KeyType;

typedef struct {
  KeyType key;
} RcdType;

typedef struct {
  RcdType r[MAXSIZE + 1];
  int length;
} SqList;

//对顺序表Ｌ做一趟增量为dk的希尔排序
void ShellInsert(SqList *L, int dk)	{
  if (L == NULL) return;
  int i, j;
  for (i = dk + 1; i <= L->length; ++i) {
    if (L->r[i].key < L->r[i-dk].key) {
      L->r[0] = L->r[i];
      for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j-=dk) {
        L->r[j + dk] = L->r[j];
      }

      L->r[j + dk] = L->r[0];
    }
  }
}

//对顺序表Ｌ做希尔排序，其中dlta[0..t-1]存放增量序列
void ShellSort(SqList *L, int dlta[], int t) {
  if (L == NULL) return;
  int k;
  for (k = 0; k < t; ++k) {
    ShellInsert(L, dlta[k]);
  }
}

int main() {
  int i;
  SqList L;
  L.length = 5;
  L.r[1].key = 3;
  L.r[2].key = 1;
  L.r[3].key = 5;
  L.r[4].key = 2;
  L.r[5].key = 8;

  int dlta[2] = {3, 1};
  ShellSort(&L, dlta, 2);

  for (i = 1; i <= L.length; ++i) {
    printf("%d\t", L.r[i].key);
  }

  printf("\n");
  return 0;
}
