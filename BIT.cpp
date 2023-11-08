/*
 Binary Indexed Tree with range update & range query

 build by TM Hsu 2023/01/31
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class BIT{
public:
    vector<ll> arr1,arr2;
    BIT(vector<ll> &v,int n){
        arr1.resize(n+5,0);
        arr2.resize(n+5,0);

        for(int i=0; i<v.size(); i++){
            update(i+1,v[i]);
        }
    }
    void update(ll idx,ll val){
        int x = idx;
        for(int i=idx; i<arr1.size(); i+= i & (-i)){
            arr1[i] += val;
            arr2[i] += (val*(x-1));
        }
    }
    // add range [l,r] by val (1-indexed)
    void update(ll l,ll r,ll val){
        update(l,val);
        update(r+1,-val);
    }

    ll query(ll idx){
        int x = idx;
        ll ans = 0;
        for(int i=idx; i>0; i-= i & (-i)){
            ans += arr1[i] * x - arr2[i];
        }
        return ans;
    }
    // return range sum [l,r]  (1-indexed)
    ll query(ll l,ll r){
        return query(r) - query(l-1);
    }
};

int main(){
    int n,q;
    cin>>n>>q;
    ll prev = 0;
    vector<ll> v;
    for(int i=0; i<n; i++){
        ll s;
        cin>>s;
        v.push_back(s - prev);
        prev = s;
    }
    BIT bit(v,v.size());
    for(int i=0; i<q; i++){
        ll a;
        cin>>a;
        if (a == 1){
            ll l,r,v;
            cin>>l>>r>>v;
            bit.update(l,r,v);
        }
        else{
            ll k;
            cin>>k;
            cout<<bit.query(k,k)<<endl;
        }
    }
}