#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 /*

Segment Tree with lazy propogation (range add, update, query)

design for cses Range Updates and Sums problem

https://cses.fi/problemset/task/1735/

2023/7/13 by TMHsu

*/
class SegNode {
public:
  ll lx, rx;
  SegNode *left, *right;

  // lazy1 -> for update range, lazy2 -> for add range
  ll lazy1 = 0,lazy2 = 0, sum = 0;
  SegNode(vector<ll> &v, int l, int r) {
    lx = l;
    rx = r;
    if (l == r) {
      sum = v[l];
      return;
    }
 
    int mid = (l + r) / 2;
    left = new SegNode(v, l, mid);
    right = new SegNode(v, mid + 1, r);
 
    sum = left->sum + right->sum;
  }

  // push lazy tag
  void pushDown() {
    if (lazy1 > 0 && left) {
      left->sum = lazy1 * (left->rx - left->lx + 1);
      right->sum = lazy1 * (right->rx - right->lx + 1);
 
      left->lazy1 = lazy1;
      right->lazy1 = lazy1;

      left->sum += lazy2 * (left->rx - left->lx + 1);
      right->sum += lazy2 * (right->rx - right->lx + 1);
 
      left->lazy2 = lazy2;
      right->lazy2 = lazy2;
 
      lazy1 = 0;
      lazy2 = 0;
    }

    else if (lazy2 > 0 && left) {
      left->sum += lazy2 * (left->rx - left->lx + 1);
      right->sum += lazy2 * (right->rx - right->lx + 1);
 
      left->lazy2 += lazy2;
      right->lazy2 += lazy2;
 
      lazy2 = 0;
    }
  }
 
 // increase range [l,r] by valToAdd 
  void AddRange(int l, int r, int valToAdd) {
    if (rx < l || lx > r)
      return;
 
    if (l <= lx && rx <= r) {
      sum += (valToAdd * (rx - lx + 1));
      lazy2 += valToAdd;
      return;
    }
 
    int mid = (lx + rx) / 2;
    pushDown();
 
    if (r <= mid)
      left->AddRange(l, r, valToAdd);
    else if (l > mid)
      right->AddRange(l, r, valToAdd);
    else {
      left->AddRange(l, mid, valToAdd);
      right->AddRange(mid + 1, r, valToAdd);
    }
 
    sum = left->sum + right->sum;
  }

  // update range [l,r] to valToUpdate
  void updateRange(int l, int r, int valToUpdate) {
    if (rx < l || lx > r)
      return;
 
    if (l <= lx && rx <= r) {
      sum = (valToUpdate * (rx - lx + 1));
      lazy1 = valToUpdate;
      lazy2 = 0;
      return;
    }
 
    int mid = (lx + rx) / 2;
    pushDown();
 
    if (r <= mid)
      left->updateRange(l, r, valToUpdate);
    else if (l > mid)
      right->updateRange(l, r, valToUpdate);
    else {
      left->updateRange(l, mid, valToUpdate);
      right->updateRange(mid + 1, r, valToUpdate);
    }
    sum = left->sum + right->sum;
  }

  // get [l,r] sum
  ll query(int l, int r) {
    if (lx > r || rx < l)
      return 0;
    else if (l == lx && r == rx)
      return sum;
 
    pushDown();
 
    int mid = (lx + rx) / 2;
    if (r <= mid)
      return left->query(l, r);
    else if (l > mid)
      return right->query(l, r);
    else
      return left->query(l, mid) + right->query(mid + 1, r);
  }
};

// The below code is for cses  
int main() {
  ll n, m, a;
  cin >> n >> m;
  vector<ll> v(n, 0);
  for (int i = 0; i < n; i++) {
    cin >> a;
    v[i] = a;
  }
  SegNode *root = new SegNode(v, 0, n - 1);
 
  for (int i = 0; i < m; i++) {
    int type;
    ll a, b, c;
    cin >> type;
    if (type == 1) {
      cin >> a >> b >> c;
      root->AddRange(a - 1, b - 1, c);
    } else if (type == 2) {
      cin >> a >> b >> c;
      root->updateRange(a - 1, b - 1, c);
    } else {
      cin >> a >> b;
      cout << root->query(a - 1, b - 1) << endl;
    }
  }
}