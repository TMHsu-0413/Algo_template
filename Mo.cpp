 /*
 
 mo's algorithm 

 把多次區間查詢問題變成離線問題，並透過sort來降低搜尋時間
 這篇的code是用來解這題 https://www.spoj.com/problems/DQUERY/

 TC : $O(n * sqrt(n))$

 */
#include <bits/stdc++.h>
using namespace std;

vector<int> v;
unordered_map<int,int> cnt;
int k;
int l = 0,r = -1, res = 0;

void add(int i){
    if(cnt[v[i]] == 0) res++;
    cnt[v[i]]++;
}

void sub(int i){
    if(cnt[v[i]] == 1) res--;
    cnt[v[i]]--;
}

int main(){
    cin.tie(0);
    cout.sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        int a;
        cin>>a;
        v.push_back(a);
    }

    int q;
    cin>>q;
    vector<array<int,3>> Q;
    for(int i=0; i<q; i++){
        int a,b;
        cin>>a>>b;
        a--; b--;
        Q.push_back({a,b,i});
    }

    vector<int> ans(q);
    k = sqrt(n)+1;
    sort(Q.begin(),Q.end(),[](array<int,3> &a,array<int,3> &b){
        if ((a[0]/k) == (b[0]/k))
            return a[1] < b[1];
        return (a[0]/k) < (b[0]/k);
    });
    for(auto &e:Q){
        while (l < e[0]) sub(l++);
        while (l > e[0]) add(--l);
        while (r < e[1]) add(++r);
        while (r > e[1]) sub(r--);

        ans[e[2]] = res;
    }

    for(int i=0; i<ans.size(); i++)
        cout<<ans[i]<<"\n";
}