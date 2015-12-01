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

int SelectMinKey(SqList *L, int i) {
  if (L == NULL) return;
  int j;
  int num = i;
  int min = L->r[i].key;
  for (j = i + 1; j <= L->length; ++j)
  {
    if (min > L->r[j].key) {
      min = L->r[j].key;
      num = j;
    }
  }
  return num;
}

void SelectSort(SqList *L) {
  if (L == NULL) return;
  int i, j;
  for (i = 1; i <= L->length; ++i) {
    j = SelectMinKey(L, i);
    if (i != j) {
      L->r[0] = L->r[i];
      L->r[i] = L->r[j];
      L->r[j] = L->r[0];
    }
  }
}

int main() {
  SqList L;
  L.length = 5;
  L.r[1].key = 4;
  L.r[2].key = 1;
  L.r[3].key = 2;
  L.r[4].key = 0;
  L.r[5].key = 9;

  SelectSort(&L);

  int i;
  for (i = 1; i <= L.length; ++i) {
    printf("%d\t", L.r[i].key);
  }

  printf("\n");
  return 0;
}
