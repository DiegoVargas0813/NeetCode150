#include <vector>
#include <unordered_map>

using namespace::std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> differences; // Key = Difference, Value = Num


        // Iterate through the vector
        // Calculate the difference  target - num[i] = result
        // 7 - 3 = 4
        // differences[4] = 3 index
        // Hash  differences[result] = i 
        // 7 - 4 = 3
        // if differences[4] exists 
        // If  target - num[j] exists within differences, we have found our result?

        for(int i = 0; i < nums.size(); i++){
            int result = target - nums[i]; // 7 - 3 = 4

            //In next iteration 7 - 4 = 3
            // If our current NUM exists as a KEY
            if(differences.count(nums[i])){
                return {differences[nums[i]],i};
            }
 
            differences[result] = i; // [4] -> Index of 3
        }

    }
};
