/*
 * Quick sort
 * 
 * build by TM Hsu 2023/03/03
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int partition(vector<int>& nums,int l,int r){
        int pivot = rand() % (r-l) + l; 
        swap(nums[r],nums[pivot]);

        int cur = l-1;

        for (int i=l; i<r; i++)
            if (nums[i] < nums[r])
                swap(nums[i],nums[++cur]);

        swap(nums[r],nums[++cur]);

        return cur;
    }
    void qsort(vector<int>& nums,int l,int r){
        if (l < r){
            int mid = partition(nums,l,r);
            qsort(nums,l,mid-1);
            qsort(nums,mid+1,r);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        //unordered_set<int> st(nums.begin(),nums.end());
        //if (st.size() == 1)
        //    return nums;
        qsort(nums,0,nums.size()-1);
        return nums;
    }
};
