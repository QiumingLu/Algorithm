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

int Partition(SqList *L, int low, int high)
{
  //交换顺序表Ｌ中字表ｒ[low..high]的记录，枢轴记录到位，并返回其所在位置，
  //此时在它之前（后）的记录均不大于它
  if (L == NULL) return;
  int pivotkey;
  L->r[0] = L->r[low];	
  pivotkey = L->r[low].key;					//枢轴记录关键字

  while (low < high) {
	//从表的两端交替地向中间扫描
    while (low < high && L->r[high].key >= pivotkey) {
      --high;
    }
    L->r[low] = L->r[high];					//将比枢轴记录小的记录移到低端
    while (low < high && L->r[low].key <= pivotkey) {
      ++low;
    }
    L->r[high] = L->r[low];					//将比枢轴记录大的记录移到高端
  }

  L->r[low] = L->r[0];						//枢轴记录到位
  return low;								//返回枢轴位置
}

void QSort(SqList *L, int low, int high)
{
  if (L == NULL) return;
  int pivotloc;
  //对顺序表Ｌ中的子序列L.r[low..high]做快速排序
  if (low < high) {
    pivotloc = Partition(L, low, high);
    QSort(L, low, pivotloc - 1);
    QSort(L, pivotloc + 1, high);
  }
}

void QuickSort(SqList *L) {
  if (L == NULL) return;
  QSort(L, 1, L->length);
}

int main() {
  int i;
  SqList L;
  L.length = 6;
  L.r[1].key = 9;
  L.r[2].key = 4;
  L.r[3].key = 6;
  L.r[4].key = 1;
  L.r[5].key = 0;
  L.r[6].key = 7;

  QuickSort(&L);

  for (i = 1; i <= L.length; ++i) {
    printf("%d\t", L.r[i].key);
  }
  printf("\n");
  return 0;
}
