#include <iostream>
#include "PageReplacement.h"

int main()
{
  PageReplacement pageReplacement;
  while(1)
  {
    int choose;
    std::cout << "请输入选择：";
    std::cin >> choose;
    switch(choose)
    {
      case 1:
        pageReplacement.optimal();
        break;
      case 2:
        pageReplacement.random();
        break;
      case 3:
        pageReplacement.FIFO();
        break;
      case 4:
        pageReplacement.LRU();
        break;
      case 5:
        pageReplacement.clock();
        break;
      default:
        pageReplacement.clockBetter();
        break;
    }
  }
  return 0;
}
