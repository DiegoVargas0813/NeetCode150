#include <vector>
#include <unordered_map>
#include <iostream>

using namespace::std;

/*
    In this excercise we need to find the LENGHT of the longest sequence of elements that can be formed. Not the elements

    EX:

    nums = [2,20,4,10,3,4,5]

    Output: 4 

    Because 2 -> 3 -> 4 -> 5
*/

// =================== Unoptimal Solution =========================

/*
     The main issue with this solution is that we are iterating through the map and for each element we are iterating through the map again to find the next element in the sequence. 
     This results in a time complexity of O(n^2) in the worst case, which is not optimal for this problem.
     Still a valid solution, but we can do better.
*/

/*
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int,int> currentAndNext;  // Key = nums[i], Value = num[i]+1;

        if(nums.size() == 0){
            return 0;
        }

        int result = 1;

        int currentNumber;
        int currentSequence = 0;

        for(int num:nums){
            currentAndNext[num] = num + 1;
        }

        for(auto i: currentAndNext){
            currentNumber = i.first;
            currentSequence = 0;
            cout << "Current number: " << currentNumber << endl; 
            cout << "Sequence: " << currentSequence << endl; 
            while(currentAndNext.count(currentNumber)){
                currentSequence++;
                currentNumber = currentAndNext[currentNumber];
                cout << "Current number in loop: " << currentNumber << endl; 
                cout << "Sequence in loop: " << currentSequence << endl; 
            }
            if (currentSequence > result){
                result = currentSequence;
            }
        }

        return result;
    }
};
*/



class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        if(nums.size() == 0){
            return 0;
        }

        unordered_map<int,int> sequence; // Key = num[i], Value = sequence lenght.
        int biggest = 0;

        // Here we are trying to join just in case the sequence by checking our adjacent numbers in case they also got a sequence going;
        for(int n:nums){
            if(sequence[n] > 0){
              continue;  
            }
            sequence[n] = sequence[n-1] + sequence [n+1] + 1;
            // We are jumping to the edge of the sequence on the left and right to inform them of the new sequence
            sequence[n - sequence[n-1]] = sequence[n];
            sequence[n + sequence[n+1]] = sequence[n];
            if(sequence[n] > biggest){
                biggest = sequence[n];
            }

        }
        return biggest;
    }
};



int main(){
    vector<int> nums = {2,20,4,10,3,4,5};

    Solution solver;

    solver.longestConsecutive(nums);

    return 0;
}