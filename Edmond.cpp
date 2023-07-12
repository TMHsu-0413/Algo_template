/*

Edmond-Karp algorithm, for maximum flow problem

design for cses Download Speed

https://cses.fi/problemset/task/1694/

2023/7/13 by TMHsu

*/



#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
vector<vector<int>> g;
vector<vector<ll>> cost;
void BFS(vector<int> &pre, vector<ll> &pre_cost, int n) {
  queue<int> q;
  q.push(1);
  pre_cost[1] = INT_MAX;
  while (!q.empty()) {
    int m = q.size();
    for (int i = 0; i < m; i++) {
      int cur = q.front();
      q.pop();
 
      for (auto &nxt : g[cur]) {
        if (pre[nxt] != -1 || cost[cur][nxt] <= 0)
          continue;
 
        q.push(nxt);
        pre[nxt] = cur;
        pre_cost[nxt] = min(cost[cur][nxt], pre_cost[cur]);
      }
    }
    if (pre[n] != -1)
      break;
  }
}
 
ll EK(int n) {
  ll ans = 0;
  while (true) {
    vector<int> pre(n + 1, -1);
    vector<ll> pre_cost(n + 1, 0);
    BFS(pre, pre_cost, n);
    if (pre[n] == -1)
      break;
    int cur = n;
    while (cur != 1) {
      int prev = pre[cur];
      cost[prev][cur] -= pre_cost[n];
      cost[cur][prev] += pre_cost[n];
 
      cur = prev;
    }
    ans += (ll)pre_cost[n];
  }
  return ans;
}

// below code for cses 
int main() {
  int n, m;
  cin >> n >> m;
  int a, b, c;
  g.resize(n + 1);
  cost.resize(n + 1, vector<ll>(n + 1, 0));
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c;
    g[a].push_back(b);
    g[b].push_back(a);
    cost[a][b] += c;
  }
 
  ll ans = EK(n);
  cout << ans << endl;
  return 0;
}