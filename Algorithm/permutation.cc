// 简单的字母全排列问题

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Solution {
 public:
  std::vector<std::string> Permutation(std::string& s) {
    std::vector<std::string> res;
    sort(s.begin(), s.end(), std::greater<char>());
    Helper(res, s, 0);
    sort(res.begin(), res.end(), std::greater<std::string>());
    return res;
  }

 private:
  void Helper(std::vector<std::string>& res, std::string& s, unsigned n) {
    if (n == s.size() - 1) {
      std::string temp(s.begin(), s.end());
      res.push_back(temp);
    } else {
      for (unsigned i = n; i < s.size(); ++i) {
        std::swap(s[n], s[i]);
        Helper(res, s, n+1);
        std::swap(s[n], s[i]);
      }
    }
  }
};

int main() {
  Solution solution;
  std::vector<std::string> v;
  std::string s = "ABC";
  v = solution.Permutation(s);
  std::vector<std::string>::iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << std::endl;
  }
  return 0;
}

