#include <vector>

using namespace::std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(),1);

        // [2,4,6,8]

        // Result must be [192, 96, 64, 48]
   
        int product = 1;
        // Result we want [0, 1*2, 1*2*4, 1*2*4*6,]     
        // Result we want from here [0, 2, 8, 48]
        for(int i = 1; i < nums.size(); i++){
            product *= nums[i-1];
            result[i] = product;
        }

        // Result we want [ , , ,  ,48]

        product = 1;

        for(int i = nums.size() - 1; i > 0; i--){
            product *= nums[i];
            result[i-1] *= product;
        }

        return result;
    }
};
