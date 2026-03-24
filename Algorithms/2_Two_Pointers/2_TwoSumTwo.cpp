#include <vector>
// In Two Sum II the input array is sorted in non-decreasing order

using namespace::std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {        
        int i = 0;
        int j = 1;

        vector<int> result(2,-1);


        while(j < numbers.size() && i < numbers.size() -1){
            while(i != j){
                if((numbers[i] + numbers[j]) == target){
                    result[0] = i+1;
                    result[1] = j+1;
                    return result;
                 }
                i++;
            }   
            i = 0;
            j++;     
        }
        return result;
    }
};
