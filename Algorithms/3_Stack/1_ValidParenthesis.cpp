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

class Solution {
public:
    bool isValid(string s) {
        unordered_map<char,char> parenthesis;

        stack<char> validator;

        // Stack = [{(

        // hash = )}]

        parenthesis[']'] = '[';
        parenthesis[')'] = '(';
        parenthesis['}'] = '{';

        for (char c: s){
            if(!parenthesis[c]){
                validator.push(c);
                continue;
            }

            if(!validator.empty()){
                if(parenthesis[c] == validator.top()){
                    validator.pop();
                    continue;
                }
            }
            return false;
        }

        if(validator.empty()){
            return true;
        }
        return false;
     }
};
