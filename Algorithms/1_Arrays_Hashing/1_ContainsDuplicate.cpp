#include <vector>
#include <unordered_map>
#include <iostream>

using namespace::std;


class Solution {
public:
    bool hasDuplicate(vector<int>&nums){
        unordered_map<int, int> results;

        for(int i=0; i < nums.size(); i++){
            if (results.count(nums[i])){
                cout << "true" << endl;
                return true;
            }
            results[nums[i]]++;
        }
        cout << "false" << endl;
        return false;
    }
};

int main(){
    vector<int> nums = {1,2,3,3};

    Solution solution;

    solution.hasDuplicate(nums);

    return 0;
};