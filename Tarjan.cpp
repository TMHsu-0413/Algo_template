/*

Tarjan's algorithm, for Strongly Connected Component(SCC)

design for cses Strongly Connected Edges

https://cses.fi/problemset/task/2177

2023/7/13 by TMHsu

*/
#include <bits/stdc++.h>
using namespace std;
vector<int> dfn,low,lvl;
set<pair<int,int>> ans;
int bcnt = 0;
 
void tarjan(stack<int> &st,unordered_map<int,vector<int>> &mp,int cur,int prev,int &ct){
    low[cur] = dfn[cur] = ++ct;
    st.push(cur);
 
    for(auto &nxt:mp[cur]){
        if (nxt == prev) continue;
 
        if (!dfn[nxt])
            tarjan(st,mp,nxt,cur,ct);
        if (ans.find({cur,nxt}) == ans.end() && ans.find({nxt,cur}) == ans.end())
            ans.insert({cur,nxt});
        low[cur] = min(low[cur],low[nxt]);
    }
 
    if (dfn[cur] == low[cur]){
        ++bcnt;
        while(!st.empty() && st.top() != cur){
            lvl[st.top()] = bcnt;
            st.pop();
        }
        lvl[st.top()] = bcnt;
        st.pop();
    }
}
 
int main(){
    int n,m;
    cin>>n>>m;
    dfn.resize(n+1,0);
    low.resize(n+1);
    lvl.resize(n+1);
    unordered_map<int,vector<int>> mp;
    for(int i=0; i<m; i++){
        int a,b;
        cin>>a>>b;
        mp[a].push_back(b);
        mp[b].push_back(a);
    }
    for(int i=1; i<=n; i++){
        if (!dfn[i]){
            stack<int> st;
            int depth = 0;
            tarjan(st,mp,i,-1,depth);
        }
    }
    if (bcnt >= 2){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    for(auto &c:ans){
        cout<<c.first<<" "<<c.second<<endl;
    }
}