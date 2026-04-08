#include <vector>
#include <iostream>

using namespace::std;

// Failed Solution
/*
class Solution {
public:
    int search(vector<int>& nums, int target) {


        int mid = nums.size() / 2;
        int left = 0;
        int right = nums.size() - 1;

        while(right > mid && left < mid){
            cout << "Left: " << left << endl;
            cout << "Rigth: " << right << endl;
            cout << "Mid: " << mid << endl;
            if(nums[mid] > target){
                right = mid;
                mid = mid - (right - left) / 2;
            } else if (nums[mid] < target){
                left = mid;
                mid = mid + (right - left) / 2;
            } else {
                return mid;
            }
        }
        if(nums[mid] == target){
            return mid;
        }

        return -1;
    }
};
*/


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        int m = 0;
        
        while(l < r){
            cout << "L: " << l << endl; 
            cout << "R: " << r << endl; 

            // 0 + (5-0) / 2
            // 2 + (5-3) / 2
            // 3 + (5 - 4) / 2
            // 4 + 0
            m = l + (r-l) / 2;
            cout << "M: " << m << endl; 
            cout << "==== NEXT ====" << endl;
            // m = 
            if(nums[m] >= target){
                    r = m;
            } else {
                l = m + 1;
            }
        }

        if(l < nums.size() && nums[l] == target ){
            return l;
        }
        return -1;
    }
};




int main(){
    // 0 4
    // 4 > 3
    // new mid = mid + (right - mid) / 2
    // new mid = 3 + (3 - 3) / 2




    vector<int> nums = {-1,0,3,5,9,12};

    Solution solver;

    solver.search(nums, 9);

    return 0;
}
