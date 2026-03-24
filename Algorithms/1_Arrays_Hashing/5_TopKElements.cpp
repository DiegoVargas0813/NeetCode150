// NUMS is our array
// K is the amount of top frequent elements we want to find
// Out can be returned in any order
#include <vector>
#include <unordered_map>



using namespace::std;

// Failed Code
// class Solution {
// public:
//     vector<int> topKFrequent(vector<int>& nums, int k) {
//         // The an i element of the array can appear 1 to N times. With N being the size of the array.

//         // We use an ordered_map because this one stores a key-value pair. Not just a key like an unordered_set.
//         unordered_map<int, int> frequencies;  // Key = number, frequency.

//         for(auto num: nums){
//             frequencies[num]++;
//         }

//         vector<int> vector_frequencies;

//         vector<int> result;

//         for(int i = 0; i < nums.size(); i++){
//             vector_frequencies[frequencies[nums[i]]] = nums[i];
//         }

//         int i = nums.size() - 1;

//         while(i > (nums.size() - k - 1)){
//             if(vector_frequencies[i] == 0){
//                 i--;
//             } else {
//                 result.push_back(vector_frequencies[i]);
//                 i--;
//             }
//         }
//         // for(int i: nums){
//         //     top_frequencies[frequencies[i]].push_back(nums[i]);
//         // }

//         return result;
//     }
// };


// class Solution {
// public:
//     vector<int> topKFrequent(vector<int>& nums, int k) {
//         unordered_map<int, int> count; // Key = Num, Value = Freq

//         vector<vector<int>> frequencies(nums.size() + 1);

//         vector<int> result;

//         // We iterate through the nums and count their values.
//         for(auto num:nums){
//             count[num]++;
//         }

//         // We define the index based on the frequency and the value with the numb value.
//         for(auto i: count){
//             frequencies[i.second].push_back(i.first);
//         }


//         for(int i = nums.size(); i >= nums.size() - k; i--){
//             for(int j = 0; j < frequencies[i].size(); j++){
//                 result.push_back(frequencies[i][j]);
//             }
//         }
//         return result;
//     }
// };


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> counts;  // Key = Num[i], Value = Count;

        // Our max frequency is equal to nums.size(). Because at most an X element can fit nums.size() times in the array.
        // In a [0,1,1,4,6,7,8,8,1] vector size = 9
        vector<vector<int>> frequencies(nums.size()+1);

        // Victor with maximum capacity.
        vector<int> result;

        // We iterate through our num vector and count frequencies
        for(int num: nums){
            counts[num]++;
        }

        for(auto i: counts){
            // We store the numbers based on their frequency on the array.
            frequencies[i.second].push_back(i.first);
        }

        for(int i = frequencies.size()-1; i > 0; i--){
                for(int j = 0; j < frequencies[i].size(); j++){
                    result.push_back(frequencies[i][j]);
                }
                if(result.size() == k){
                     return result;
                }
        }
        return result;
    }
};
