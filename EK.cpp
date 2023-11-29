/*

Edmond-Karp algorithm, for maximum flow problem

design for cses Download Speed

https://cses.fi/problemset/task/1694/

2023/11/29 by TMHsu

TC : O(V * E^2)

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// find a path from start to end
ll bfs(unordered_map<ll, set<ll>> &g, vector<vector<ll>> &dis, ll start,
       ll end) {
  int n = dis.size();
  queue<ll> q;
  vector<ll> pre(n + 5, -1);
  q.push(start);

  while (!q.empty()) {
    ll cur = q.front();
    q.pop();
    if (cur == end)
      break;
    for (auto &nxt : g[cur]) {
      if (nxt == start)
        continue;
      else if (pre[nxt] == -1 && dis[cur][nxt] > 0) {
        pre[nxt] = cur;
        q.push(nxt);
      }
    }
  }
  if (pre[end] == -1)
    return -1;
  ll mn_flow = INT_MAX;
  ll cur = end;
  while (pre[cur] != -1) {
    mn_flow = min(mn_flow, dis[pre[cur]][cur]);
    cur = pre[cur];
  }
  cur = end;
  while (pre[cur] != -1) {
    dis[pre[cur]][cur] -= mn_flow;
    dis[cur][pre[cur]] += mn_flow;
    cur = pre[cur];
  }
  return mn_flow;
}

// Edmond-Karp 主要算法
ll EK(unordered_map<ll, set<ll>> &g, vector<vector<ll>> &dis, ll start,
      ll end) {
  ll ans = 0;

  while (true) {
    ll flow = bfs(g, dis, start, end);
    if (flow == -1)
      break;
    ans += flow;
  }
  return ans;
}

int main() {
  ll n, m;
  cin >> n >> m;
  vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, 0));
  unordered_map<ll, set<ll>> g;
  ll start = 1;

  for (int i = 0; i < m; i++) {
    ll a, b, c;
    cin >> a >> b >> c;
    dis[a][b] += c;
    g[a].insert(b);
    g[b].insert(a);
  }

  cout << EK(g, dis, 1, n) << endl;
}
