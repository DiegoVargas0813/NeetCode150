#include <string>
#include <unordered_map>

using namespace::std;

class Solution {
public:

    bool isAnagram(string s, string t) {
        unordered_map<char, int> s_hash;
        unordered_map<char, int> t_hash;

        if (s.size() != t.size()){
            return false; //We know from the start they can't be anagrams.
        } 

        for(int i = 0; i < s.size(); i++){
            s_hash[s[i]]++;
            t_hash[t[i]]++;
        }

        for(int i = 0; i < s_hash.size(); i++){
            if(s_hash[i] != t_hash[i]){
                return false;
            }
        }
        return true;
    }
};
