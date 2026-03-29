#include <vector>

using namespace::std;


// Failed Solution

/*
    The thing that made the code fail in the end was the confusion between & and &&.

    & is the bitwise operator
    && is a logical and to compare true and false statements.

*/

/* 
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9] = {0}; // Basically nine zeroes that represent each row.
        int cols[9] = {0}; // Bitmaks for cols
        int squares[9] = {0};

        for(int r = 0; r < board.size(); r++){
            for(int c =0; c < board[r].size(); c++){
                if(board[r][c] == '.'){
                    continue;
                }

                int val = board[r][c] - '1'; // Ex:  '3' - '1' = 51 - 49 = 2. We displace a 00000001 two spaces.

                if(rows[r] && ( 1 << val) || 
                    cols[c] && (1 << val) ||
                    squares[((r/3) * 3 + (c/3))] && (1 << val)
                ){
                    return false;
                }else{
                    rows[r] |= 1 << val;
                    cols[c] |= 1 << val;
                    squares[((r/3) * 3 + (c/3))] |= 1 << val;
                }
            }
        }
        return true;
    }
};
*/