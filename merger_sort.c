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

void Merge(RcdType SR[], RcdType TR[], int i, int m, int n) {
  int j, k;
  for (j = m + 1, k = i; i <= m && j <= n; ++k) {
    if (SR[i].key <= SR[j].key) {
      TR[k] = SR[i++];
    } else {
      TR[k] = SR[j++];
    }
  }

  if (i <= m) {
    while (i <= m) {
      TR[k++] = SR[i++];
    }
  }

  if (j <= n) {
    while (j <= n) {
      TR[k++] = SR[j++];
    }
  }
}

void MSort(RcdType SR[], RcdType TR1[], int s, int t) {
  int m;
  RcdType TR2[t - s];
  if (s == t) {
    TR1[s] = SR[s];
  } else {
    m = (s+t)/2;
    MSort(SR, TR2, s, m);
    MSort(SR, TR2, m+1, t);
    Merge(TR2, TR1, s, m, t);
  }
}

void MergeSort(SqList *L) {
  if (L == NULL) return;
  MSort(L->r, L->r, 1, L->length);
}

int main() {
  SqList L;
  L.length = 6;
  L.r[1].key = 5;
  L.r[2].key = 1;
  L.r[3].key = 3;
  L.r[4].key = 0;
  L.r[5].key = 9;
  L.r[6].key = 2;

  MergeSort(&L);

  int i;
  for (i = 0; i < L.length; ++i) {
    printf("%d\t", L.r[i].key);
  }

  printf("\n");
  return 0;
}
