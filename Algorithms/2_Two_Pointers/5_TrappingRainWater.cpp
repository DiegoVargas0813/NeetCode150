#include <vector>

using namespace::std;

class Solution {
public:
    int trap(vector<int>& height) {
        int total_water = 0; //The total amount of water that we are 100% sure will be trapped.
        int current_water = 0; //Speculative amount of water that COULD be trapped if first and second height are at least equal.

        //bool first_height_found = 0;

        int i = 0; // First height, will always be at the back
        int j = 0; // Second height, will always be up front

        //We can only dump the full amount of current_water if the second height is equal or highger than the first.
        //Otherwise we will need to subtract 
        //The way we detect the end of a "container" is having a

        for(j; j < height.size();j++){
            
        }
    }
};
