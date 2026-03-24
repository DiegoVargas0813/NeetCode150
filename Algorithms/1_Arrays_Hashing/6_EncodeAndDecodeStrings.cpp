#include <string>
#include <vector>

using namespace::std;

// Failed Code

// class Solution {
// public:
//     string encode(vector<string>& strs) {
//         string result;

//         for(auto current_word: strs){
//             string lenght = to_string(current_word.size()); //Hello = 5
//             result = result + lenght + '#' + current_word;
//         }

//         return result;
//     }

//     vector<string> decode(string s) {
//         vector<string> result;

//         string built_string;
//         int int_lenght = 0;
//         int count= 0;

//         char separator = '#';
//         for(int i = 0; i < s.length(); i++){
//             if(int_lenght < 0){ //We have finished a word and need to find a new one.
//                 if(s[i] == separator){
//                     int_lenght = stoi(built_string); // We reached a separator
//                     // Int_lenght = 5
//                     built_string.clear(); //Reset the built string
//                 } else {
//                     built_string = built_string + s[i]; //We are still in numbers
//                 }
//             } else if(int_lenght > 0){
//                 built_string = built_string + s[i];
//                 int_lenght--;
//                 //H -> 4, e -> 3, l -> 2, l -> 1, o -> 0
//             } else {
//                 result.push_back(built_string);
//                 built_string.clear();
//             }
//         }
//         return result;
//     }
// };


class Solution {
public:

    string encode(vector<string>& strs) {
        string result = "";

        for(string str: strs){
            result = result + to_string(str.size()) + '#' + str;
        }

        return result;
    }

    vector<string> decode(string s) {
        int i = 0;
        int j = 1;

        int lenght = 0;

        vector<string> result;

        // 5#Hello

        // i  = 5
        // j = 5

        while(i < s.length()){
            if(s[j] == '#'){
                lenght = stoi(s.substr(i, j - i));
                i = j;
                i++; // i in this point is right at the start of the word.
                j++;
                result.push_back(s.substr(i, lenght));
            }
            j++; //J is being pushed even beyond the start of the next numbers.
        }
        return result;
    }
};