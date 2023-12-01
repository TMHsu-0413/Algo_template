/*

Minumum cost - Maximum flow problem (MCMF)

use SPFA + Edmond-Karp algorithm

disign for cses problem

https://cses.fi/problemset/task/2121/

找最短路徑可以用SPFA或Bellman-ford，只要是可以對負數找cost的都行
要注意反向邊的時候，cost要加在負的那邊才對，因為這個卡了好幾次WA

2023/11/29 by TMHsu

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using al = array<ll, 2>;

ll remain;

// find a path from start to end with minimum cost
ll SPFA(unordered_map<ll, unordered_set<ll>> &g,
        vector<vector<map<ll, ll>>> &dis, ll start, ll end) {
  int n = dis.size();
  vector<ll> path_cost(n + 1, INT_MAX); // 紀錄從起點到n的最小cost是多少
  vector<bool> in_Queue(n + 1, false); // 是否在queue內，SPFA用的
  vector<al> pre(
      n + 1,
      {-1, -1}); // 紀錄上一個走的邊是走從哪個點的哪條cost的邊走來的， Ex.
                 // pre[2] = {1,3}，代表是從點1->點2，然後走cost為3的邊
  path_cost[start] = 0;
  in_Queue[start] = true;
  queue<ll> q;
  q.push(start);

  while (!q.empty()) {
    ll cur = q.front();
    q.pop();
    in_Queue[cur] = false;
    for (auto &nxt : g[cur]) {
      if (nxt == start)
        continue;
      else if (cur == nxt)
        continue;
      for (auto &[k, v] : dis[cur][nxt]) {
        if (dis[cur][nxt][k] > 0) {
          if ((path_cost[cur] + k) < path_cost[nxt]) {
            path_cost[nxt] = k + path_cost[cur];
            pre[nxt][0] = cur;
            pre[nxt][1] = k;
            if (!in_Queue[nxt]) {
              in_Queue[nxt] = true;
              q.push(nxt);
            }
          }
          break;
        }
      }
    }
  }

  if (pre[end][0] == -1)
    return -1;

  ll mn_flow = INT_MAX;
  ll cur = end;
  // 先取到能流過的flow上限
  while (pre[cur][0] != -1) {
    ll prev = pre[cur][0];
    ll c = pre[cur][1];
    mn_flow = min(mn_flow, dis[prev][cur][c]);
    cur = prev;
  }
  cur = end;
  // 把經過的邊做回沖
  while (pre[cur][0] != -1) {
    ll prev = pre[cur][0];
    ll c = pre[cur][1];
    dis[prev][cur][c] -= min(mn_flow, remain);
    // 這邊要加負的cost
    dis[cur][prev][-c] += min(mn_flow, remain);
    cur = prev;
  }
  ll ans = path_cost[end] * min(mn_flow, remain);
  remain -= min(remain, mn_flow);
  return ans;
}

// Edmond-Karp 主要算法
ll EK(unordered_map<ll, unordered_set<ll>> &g, vector<vector<map<ll, ll>>> &dis,
      ll start, ll end) {
  ll ans = 0;

  while (true) {
    if (remain == 0)
      break;
    ll flow = SPFA(g, dis, start, end);
    if (flow == -1)
      break;
    ans += flow;
  }
  return ans;
}

int main() {
  ll n, m, k;
  cin >> n >> m >> k;
  remain = k;
  unordered_map<ll, unordered_set<ll>> g;
  vector<vector<map<ll, ll>>> dis(n + 1, vector<map<ll, ll>>(n + 1));
  for (int i = 0; i < m; i++) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a == b)
      continue;
    dis[a][b][d] += c;
    g[a].insert(b);
    g[b].insert(a);
  }

  ll ans = EK(g, dis, 1, n);
  if (remain != 0)
    cout << -1 << endl;
  else
    cout << ans << endl;
}
