#include <string>
#include <stack>
#include <unordered_map>

using namespace::std;

// Failed solution
/*
class Solution {
public:
    bool isValid(string s) {
        stack<char> parenthesis;
        unordered_map<char,char> pairs;

        pairs[']'] = '[';
        pairs['}'] = '{';
        pairs[')'] = '(';
        
        if(s.size() < 2){
            return false;
        }

        for(char c: s){
            if(c == ('[' || '{' || '(')){
                parenthesis.push(c);
            }

            if(pairs[c] == parenthesis.top()){
                parenthesis.pop();
            } else {
                return false;
            }
        }

        return true;
    }
};
*/
