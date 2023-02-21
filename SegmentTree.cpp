/*
Segment Tree with lazy propogation (single & range update,query)

design for cses range update queries problem

2023/2/21 by TMHsu

*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
class SegNode{
public:
    int lx,rx;     // range
    SegNode* left;
    SegNode* right;
    ll sum;        // range sum 
    bool lazy_tag; // 
    ll lazy_val;   // 
    
    SegNode(int l,int r,vector<ll>& arr){ // build Segment Tree with arr[l:r]
        lazy_tag = false;
        lazy_val = 0;
        left = nullptr;
        right = nullptr;
        lx = l;
        rx = r;
        
        if (l == r){
            sum = arr[l];
            return;
        }
        int mid = (l+r) / 2;
        
        left = new SegNode(l,mid,arr);
        right = new SegNode(mid+1,r,arr);
        sum = left->sum + right->sum;
        return;
    }
    void pushDown(){
        if (lazy_tag && left) {
            left->sum += lazy_val * (left->rx - left->lx + 1);
            right->sum += lazy_val * (right->rx - right->lx + 1);
            
            left->lazy_tag = true; left->lazy_val += lazy_val;
            right->lazy_tag = true; right->lazy_val += lazy_val;
            
            lazy_tag = false;
            lazy_val = 0;
        }
    }

    // add idx by val
    void single_update(int idx,int val){
        if (lx == idx && rx == idx){
            sum += val;
            return;
        }
        
        int mid = lx + (rx-lx) / 2;
        
        if (idx <= mid)
            left->single_update(idx,val);
        else 
            right->single_update(idx,val);

        if (left) {
            pushDown();
            sum = left->sum + right->sum;
        }
        return;
    }
    
    // add range [l,r] by val
    void range_update(int l,int r,int val){
        if (rx < l || lx > r) // not covered by [lx,rx] at all
            return;
        
        if (l <= lx && rx <= r){ // totally covered by [lx,rx]
            sum += val * (rx-lx+1);
            lazy_tag = true;
            lazy_val += val;
            return;
        }
        
        if (left){ // not leaf node
            pushDown();
            left->range_update(l,r,val);
            right->range_update(l,r,val);
            sum = left->sum + right->sum;
        }
    }
    
    // return rqnge query [l,r]
    ll query(int l,int r){
        if (rx < l || lx > r) // not covered by [lx,rx] at all
            return 0;
        if (l <= lx && rx <= r) // totally covered bt [lx,rx]
            return sum;

        if (left){ // not leaf node
            pushDown();
            ll ans = left->query(l,r) + right->query(l,r);
            sum = left->sum + right->sum;
            return ans;
        }
        return sum;
    }
};

int main(){
    int a,b;
    cin>>a>>b;
    vector<ll> arr(a);
    for (int i=0;i<a;i++){
        int c;
        cin >> c;
        arr[i] = c;
    }

    SegNode* root = new SegNode(0,a-1,arr);

    for (int i=0;i<b;i++){
        int c,d,e,f;
        cin >> c;
        if (c == 1){
            cin >> d >> e >> f;
            root->range_update(d-1,e-1,f);
        }
        else {
            cin >> d;
            cout<<root->query(d-1,d-1)<<endl;
        }
    }
    return 0;
}