/*
 Union find

 build by TM Hsu 2023/01/31
*/
#include <bits/stdc++.h>
using namespace std;

class UF {
public:
  vector<int> parent;
  vector<int> count;
  UF(int n) {
    count.resize(n, 1);
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int n) {
    if (parent[n] != n)
      parent[n] = find(parent[n]);
    return parent[n];
  }
  void _union(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py)
      return;

    if (count[px] > count[py]) {
      parent[py] = px;
      count[px] += count[py];
    } else {
      parent[px] = py;
      count[py] += count[px];
    }
  }
  bool connected(int x, int y) { return find(x) == find(y); }
};

int main() {
  UF uf(10);

  uf._union(2, 3);
  uf._union(6, 8);
  cout << uf.connected(3, 6) << " " << uf.connected(6, 8) << endl;
  uf._union(3, 6);
  cout << uf.connected(3, 8) << endl;

  return 0;
}
