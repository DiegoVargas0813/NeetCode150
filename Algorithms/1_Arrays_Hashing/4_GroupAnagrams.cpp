#include <vector>
#include <map>
#include <string>

using namespace::std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<vector<int>, int> char_counts; //We store the count of characters an the assigned output index as value

        vector<vector<string>> result;

        int result_index = 0;

        //We iterate through an i word which has j chars.
        for(int i = 0; i < strs.size(); i++){
            vector<int> chars(26,0); //A vector representing the 26 letters of the alphabet
            string current_word = strs[i];
            for(int j = 0; j < strs[i].length(); j++){
                chars[int(current_word[j])-97]++; //We take the ASCII value, substract it to start in 0 and then add to chars vector.
            }
            if(char_counts.count(chars)){
                result[char_counts[chars]].push_back(strs[i]);
            } else {
                char_counts[chars] = result_index;
                result.push_back({strs[i]});
                result_index++;
            }
        }
        return result;
    }
};
