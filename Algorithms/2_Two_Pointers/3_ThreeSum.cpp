#include <vector>
#include <iostream>

using namespace::std;

/*
    The approach here was able to catch some triplets via an approach of closing in on the numbers slowly.

    However it could miss some cases like this:

    nums = [-1,0,1,2,-1,-4]

    Case missed: [-1,2,-1] Since I didn't consider positions that didn't involve I and J being anywhere beyond our current edge.
*/

/* Failed Solution
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int i = 0;
        int j = nums.size() - 1;
        int k = 0;

        vector<vector<int>> result;

        while(i < j){
            k = i+1;
            while(k < j){
                vector<int> current;
                cout << "i: " << nums[i] << endl;
                cout << "k: " << nums[k] << endl;
                cout << "j: " << nums[j] << endl;
                cout << "===== next =====" << endl;
                if(nums[i] + nums[j] + nums[k] == 0){
                    current.push_back(nums[i]);
                    current.push_back(nums[j]);
                    current.push_back(nums[k]);
                    result.push_back(current);
                }
                k++;
            }
            i++;
            j--;
        }
        return result;
    }
};
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int i;
        int j;
        int k = 1;
        
        while(i + 1 < j){
            i = 0;
            j = nums.size() - 1;
            int current = k;
            while(i < current && current < j){
                int sum = nums[i] + nums[current] + nums[k];    
                if(sum < 0){

                }
            }
        }
    }
};


int main(){
    vector<int> nums = {-1,0,1,2,-1,-4};

    Solution solver;

    solver.threeSum(nums);

    return 0;
}