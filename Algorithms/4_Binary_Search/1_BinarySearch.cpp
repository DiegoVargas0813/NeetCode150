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



int main(){
    // 0 4
    // 4 > 3
    // new mid = mid + (right - mid) / 2
    // new mid = 3 + (3 - 3) / 2




    vector<int> nums = {5};

    Solution solver;

    solver.search(nums, 5);

    return 0;
}
