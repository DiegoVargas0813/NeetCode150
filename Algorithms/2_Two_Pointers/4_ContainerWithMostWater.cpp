#include <vector>

using namespace::std;

class Solution {
public:
    int maxArea(vector<int>& heights) {
        int i = 0;
        int j = heights.size()-1;

        // [1,7,2,5,4,7,3,6]
        //  min(1,7) = 1
        // 1 * (1-0) = 1 * 1
        int best = min(heights[i], heights[j]) * (j-i);

        

        while(i < j){
            if(heights[i] > heights[j]){
                j--;
            } else {
                i++;
            }
            int current = min(heights[i], heights[j]) * (j-i); 
            if(current > best){
                best = current;
            }
        }
        return best;
    }
};
