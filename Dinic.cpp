/*

dinic algorithm (maximum flow)

先用bfs建level
graph，再用dfs找路徑去填水流，填的時候只能走跟目前節點level差1的點
要注意dfs時需記錄走了但沒辦法到終點的節點，以防圖有很多種分支導致TLE

TC : O(V^2E)

2023/11/29 by TMHsu
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// build level graph
vector<ll> build(unordered_map<ll, unordered_set<ll>> &g,
                 vector<vector<ll>> &dis, ll start, ll end) {
  int n = dis.size();
  queue<ll> q;
  q.push(start);
  vector<ll> level_graph(n + 1, -1);
  level_graph[start] = 1;
  while (!q.empty()) {
    ll cur = q.front();
    q.pop();

    for (auto &nxt : g[cur]) {
      if (nxt == start)
        continue;
      else if ((dis[cur][nxt] > 0) && (level_graph[nxt] == -1)) {
        level_graph[nxt] = level_graph[cur] + 1;
        q.push(nxt);
      }
    }
  }
  return level_graph;
}

// find a valid path from start to end
bool dfs(unordered_map<ll, unordered_set<ll>> &g, vector<vector<ll>> &dis,
         ll cur, ll end, vector<ll> &level_graph, vector<ll> &pre) {
  if (cur == end) {
    return true;
  }

  for (auto &nxt : g[cur]) {
    // 如果這個節點沒有路能到終點，那可以記錄起來，之後再走到這個點就不用再試了
    // 如果沒有這條，會導致TLE
    if (pre[nxt] != -1)
      continue;
    if ((dis[cur][nxt] > 0) && (level_graph[nxt] - level_graph[cur]) == 1) {
      pre[nxt] = cur;
      if (dfs(g, dis, nxt, end, level_graph, pre))
        return true;
    }
  }
  return false;
}

// Dinic主要算法
ll Dinic(unordered_map<ll, unordered_set<ll>> &g, vector<vector<ll>> &dis,
         ll start, ll end) {
  int n = dis.size();
  ll ans = 0;

  while (true) {
    vector<ll> level_graph = build(g, dis, start, end);
    if (level_graph[end] == -1)
      break;

    while (true) {
      vector<ll> pre(n + 1, -1);
      bool have_path = dfs(g, dis, start, end, level_graph, pre);
      if (!have_path)
        break;
      ll cur = end;
      ll mn_flow = INT_MAX;
      while (pre[cur] != -1) {
        mn_flow = min(mn_flow, dis[pre[cur]][cur]);
        cur = pre[cur];
      }
      ans += mn_flow;
      cur = end;
      while (pre[cur] != -1) {
        dis[pre[cur]][cur] -= mn_flow;
        dis[cur][pre[cur]] += mn_flow;
        cur = pre[cur];
      }
    }
  }
  return ans;
}

int main() {
  ll n, m;
  cin >> n >> m;
  vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, 0));
  unordered_map<ll, unordered_set<ll>> g;

  for (int i = 0; i < m; i++) {
    ll a, b, c;
    cin >> a >> b >> c;
    dis[a][b] += c;
    g[a].insert(b);
    g[b].insert(a);
  }

  cout << Dinic(g, dis, 1, n) << endl;
}
