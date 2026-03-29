#include <string>
#include <cctype>

using namespace::std;

// FAILED CODE
/*
class Solution {
public:
    bool isPalindrome(string s) {
        // Pointers to start and end of string.
        int i = 0;
        int j = s.size() - 1;

        // While our pointers haven't crossed...
        while(i < j){
            while(i < j && !isAlphNum(s[i])){
                i++;
            }
            while(j > i && !isAlphNum(s[j])){
                j--;
            }
            if (tolower(s[i]) != tolower(s[j])){
                return false;
                i++;
                j--;
            } 
            i++;
            j--;
        }
        return true;
    }

    // We take advantage of the fact ASCII chars have a value we can compare.
    bool isAlphNum(char c){
        if( c >= 'A' && c <= 'Z' ||
                c >= 'a' && c <= 'z' ||
                c >= '0' && c <= '9'
        ){
            return true;
        }
        return false;
    }
};
*/
