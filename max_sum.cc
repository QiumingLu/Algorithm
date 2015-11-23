#include <vector>
#include <stdio.h>

int MaxSum(std::vector<int>& v) {
  if (v.size() <= 0) {
    return 0;
  }
  int temp = v[0], sum = temp;

  for (size_t i = 1; i < v.size(); ++i) {
    if (temp > 0) {
      temp += v[i];
    } else {
      temp = v[i];
    }
    if (temp > sum) {
      sum = temp;
    }
  }
  return sum;
}

int main(int argc, char** argv) {
  int n;
  scanf("%d", &n);
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }
  int ret = MaxSum(v);
  printf("%d\n", ret);
  return 0;
}
