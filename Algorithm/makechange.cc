// 给定数量不限的硬币，币值为25分，10分，5分和1分，编写代码计算n分有几种表示法
#include <iostream>
#include <assert.h>

class Solution {
 public: 
  int MakeWays(int n, int number) {	  
    int next_number;
    switch(number) {
      case 25: {
        next_number = 10;
        break;
      }
      case 10: {
        next_number = 5;
        break;
      }
      case 5: {
        next_number = 1;
        break;
      }
      case 1: {
        return 1;
      }
      default: {
        assert(false);
      }
    }

    int ways = 0;
    for (int i = 0; i*number <= n; ++i) {
      ways += MakeWays(n - i*number, next_number);
    }
    return ways;
  }
};

int main() {
  Solution solution;
  int res = solution.MakeWays(4, 25);
  std::cout << res << std::endl;
  return 0;
}
