#include <iostream>
#include <vector>

#include <frame/frame.h>

using namespace stl;
using namespace std;

// 从1加到N的结果
class Sum : public Algorithm<int(int)> {};

class SumBasic : public Sum {
public:
  int operator()(int n) override {
    int sum{0};
    for (int i{1}; i <= n; ++i) {
      sum += i;
    }
    return sum;
  }
  string type_name() const override { return "Sum (Naive)"; }
};

class SumAP : public Sum {
public:
  int operator()(int n) override { return n * (n + 1) / 2; }
  string type_name() const override { return "Sum (AP formula)"; }
};

class SumAP2 : public Sum {
public:
  int operator()(int n) override {
    if (n % 2 == 0) {
      return n / 2 * (n + 1);
    } else {
      return (n + 1) / 2 * n;
    }
  }
  string type_name() const override { return "Sum (AP formula / Robust)"; }
};

class SumAP2Limited : public SumAP2 {
  static constexpr int THRESHOLD{0x0001'0000};

public:
  int operator()(int n) override {
    if (n <= 0) {
      return 0;
    } else if (n > THRESHOLD) {
      return numeric_limits<int>::max();
    } else {
      return SumAP2::operator()(n);
    }
  }
  string type_name() const override {
    return "Sum (AP formula / Robust & limited)";
  }
};

vector testData{
  10,    // 都能输出正确的值
  50'000,// AP溢出，AP2正确
  70'000,// 全部溢出，但AP2Limited能返回饱和值
  -8     // 负输入，AP2Limited能返回0
};

// 可以将您的实现加入到测试框架的参数列表中
TestFramework<Sum, SumBasic, SumAP, SumAP2, SumAP2Limited> test;

int main() {
  for (auto data: testData) {
    cout << "Input: " << data << endl;
    test(data);
  }
  return 0;
}
