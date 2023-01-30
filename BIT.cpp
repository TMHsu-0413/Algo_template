/*
 Binary Indexed Tree

 build by TM Hsu 2023/01/31
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
class BIT {
public:
  vector<ll> arr;
  BIT(int n) { arr.resize(n + 1, 0); }

  void update(int n, int delta = 1) {
    while (n < arr.size()) {
      arr[n] += delta;
      n += n & (-n);
    }
  }

  ll query(int n) {
    ll sum = 0;
    while (n > 0) {
      sum += arr[n];
      n -= n & (-n);
    }
    return sum;
  }
};

int main() {
  BIT bit(10);
  bit.update(5);
  bit.update(3);

  cout << bit.query(4) << endl;
  bit.update(8);
  cout << bit.query(10) << endl;
  return 0;
}
