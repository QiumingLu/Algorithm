#include <vector>
#include <stdio.h>

int Search(std::vector<int>& v, int target) {
  int size = v.size();
  int begin = 0, end = size - 1;
  while (begin <= end) {
    int mid = (begin + end) / 2;
    if (v[mid] == target) {
      return mid;
    } else if (v[begin] <= v[mid]) {
      if (target >= v[begin] && target < v[mid]) {
        end = mid - 1;
      } else {
        begin = mid + 1;
      }
    } else {
      if (target > v[mid] && target <= v[end]) {
        begin = mid + 1;
      } else {
        end = mid - 1;
      }
    }
  }
  return -1;
}

int main(int argc, char** argv) {
  int n, target;
  scanf("%d", &n);
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }
  scanf("%d", &target);
  int ret = Search(v, target);
  printf("%d\n", ret);
  return 0;
}
