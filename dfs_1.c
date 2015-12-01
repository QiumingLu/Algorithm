#include <stdio.h>
#include <math.h>

#define MaxBox 1000
int globalWeight[MaxBox], globalNum, globalC1;	//输入参数
int globalX[MaxBox];							//保存状态X的全局变量
int globalWt, globalBd, globalMaxWt;			//保存中间量的全局变量

void loadingBacktrack(int t) {
  //边界条件，得到一个C1的更好可行解
 if (t == globalNum) {
    globalMaxWt = globalWt;			
    return;
  }

  globalBd -= globalWeight[t];				//扩展子节点时减少globalBd
	
  //约束剪枝
  if (globalWt + globalWeight[t] <= globalC1)  {
    globalX[t] = 1;
    globalWt += globalWeight[t];			//增大globalWt	
    loadingBacktrack(t+1);					//扩展左子树
    globalWt -= globalWeight[t];			//回溯时恢复globalWt
  }

  //限界剪枝
  if (globalWt + globalBd > globalMaxWt) {
    globalX[t] = 0;
    loadingBacktrack(t+1);					//扩展右子树
  }

  globalBd += globalWeight[t];				//回溯时恢复globalBd
}

int main() {
  int C2, totalWt;
	
  //读入参数
  while (EOF != scanf("%d%d%d", &globalNum, &globalC1, &C2)) {
    totalWt = 0;

    //读入集装箱重量
    for (int i = 0; i < globalNum; ++i) {
      scanf("%d", globalWeight+i);
      totalWt += globalWeight[i];
    }

    //初始化全局变量
    globalBd = totalWt;
    globalWt = 0;
    globalMaxWt = 0;
    loadingBacktrack(0);

	//剩下的集装箱重量可装入C2
    if (C2 >= (totalWt - globalMaxWt)) {
      printf("%d\n", globalMaxWt);
    } else {
      printf("No\n");
    }
  }
  return 0;
}
