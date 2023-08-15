/*

dinic algorithm (maximum flow)

先用bfs建level graph，再用dfs找路徑去填水流，填的時候只能走跟目前節點level差1的點
要注意dfs時需用一個used來記錄走了但沒辦法到終點的節點，以防圖有很多種分支導致TLE

TC : O(V^2E)

*/
#include <bits/stdc++.h>
using LL = long long;
using namespace std;

vector<int> build_lvl_graph(vector<vector<int>> &g,vector<vector<LL>> &flow,int n){
    queue<int> q;
    vector<int> level(n+1,-1);
    q.push(1);
    level[1] = 1;
    while (!q.empty()){
        queue<int> nq;
        while(!q.empty()){
            int cur = q.front(); q.pop();
            for(auto &nxt:g[cur]){
                if (level[nxt] == -1 && flow[cur][nxt] > 0){
                    level[nxt] = level[cur] + 1;
                    nq.push(nxt);
                }
            }
        }
        q = nq;
    }
    return level;
}
bool dfs(vector<vector<int>> &g,vector<int> &lvl,vector<vector<LL>> &flow,vector<bool>&used,int n,int cur,LL mn,vector<int> &path,LL &mn_flow){
    if (used[cur])
        return false;
    used[cur] = true;
    if (cur == n){
        mn_flow = mn;
        return true;
    }
    for(auto &nxt:g[cur]){
        if (flow[cur][nxt] > 0 && (lvl[nxt] - lvl[cur]) == 1){
            path.push_back(nxt);
            if (dfs(g,lvl,flow,used,n,nxt,min(mn,flow[cur][nxt]),path,mn_flow))
                return true;
            path.pop_back();
        }
    }
    return false;
}
LL dinic(vector<vector<int>> &g,vector<vector<LL>> &flow,int n){
    LL ans = 0;
    while (true){
        vector<int> lvl = build_lvl_graph(g,flow,n);
        if (lvl[n] == -1)
            break;
        else if (lvl[n] != -1){
            vector<int> path;
            path.push_back(1);
            LL mn_flow = 0;
            vector<bool> used(n+1,false);
            while (dfs(g,lvl,flow,used,n,1,INT_MAX,path,mn_flow)){
                for(int i=0; i<path.size()-1; i++){
                    int cur = path[i],nxt = path[i+1];
                    flow[cur][nxt] -= mn_flow;
                    flow[nxt][cur] += mn_flow;
                }
                ans += mn_flow;
                path.clear();
                path.push_back(1);
            }
        }
    }
    return ans;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n+1);
    vector<vector<LL>> flow(n+1,vector<LL>(n+1,0));
    for(int i=0; i<m; i++){
        LL a,b,c;
        cin>>a>>b>>c;
        if (flow[a][b] == 0){
            g[a].push_back(b);
            g[b].push_back(a);
        }
        flow[a][b] += c;
    }
    LL ans = dinic(g,flow,n);

    cout<<ans<<endl;
}