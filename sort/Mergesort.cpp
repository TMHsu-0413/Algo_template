/*
 * Merge sort
 *
 * build by TM Hsu 2023/03/03
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums,int l,int mid,int r){
        vector<int> left,right;
        vector<int> all;
        int i1 = l,i2 = mid+1;
        while (i1 <= mid || i2 <= r){
            int a = (i1 <= mid) ? nums[i1]: INT_MAX;
            int b = (i2 <= r)   ? nums[i2]: INT_MAX;

            if (a < b){
                all.push_back(a);
                i1++;
            }
            else{
                all.push_back(b);
                i2++;
            }
        }

        for (int i=l,j=0; i<=r; i++,j++)
            nums[i] = all[j];

    }
    void merge_sort(vector<int>& nums,int l,int r){
        if (l < r){
            int mid = (l+r) >> 1;
            merge_sort(nums,l,mid);
            merge_sort(nums,mid+1,r);
            merge(nums,l,mid,r);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        merge_sort(nums,0,nums.size()-1);
        return nums;
    }
};
