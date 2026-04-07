# 1. Arrays and Hashing

## Contains Duplicate

### Problems had
1. When looping the vector I signaled it to iterate until i was less or equal to the size of the vector, which cased and out of bounds error.
2. Issues with the constructor of a vector and unordered_map, check documentation for different ways to initialize them.
    - Specially for the cases that use curly braces or brackets.

### Solution

Was able to solve? Yes, but needed frequent lookup of CPP syntax and documentation.

Is it optimal? Yes, time complexity is O(n) and space the same since we iterate once through the vector and only store a count of said vector.

```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>&nums){
        unordered_map<int, int> results;

        for(int i=0; i < nums.size(); i++){
            if (results.count(nums[i])){
                cout << "true" << endl;
                return true;
            }
            results[nums[i]]++;
        }
        cout << "false" << endl;
        return false;
    }
};
```

In short, we use the hashing to store the count of each number in the vector, finding one that already exists means that we have a duplicate, so we return true. If we finish the loop without finding any duplicates, we return false.

## Valid Anagram

### Problems had
1. Still struggling with differences between, ordered and unordered maps as well as their difference with sets.


### Solution

Was able to solve? Yes, but needed small lookups on syntax and documentation.

Is it optimal? Yes, time complexity is O(n) and space the same since we iterate once through the vector and only store a count of said vector.

```cpp
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

        for(int i = 0; i < s_hash.size(); i++){ //We can just compare the two hash maps.
            if(s_hash[i] != t_hash[i]){
                return false;
            }
        }
        return true;
    }
};
```

### Optimal solution

```cpp
class Solution {
public:

    bool isAnagram(string s, string t) {
        unordered_map<char, int> s_hash;
        unordered_map<char, int> t_hash;

        if (s.size() != t.size()){ // Good call to reject early if the sizes are different.
            return false; //We know from the start they can't be anagrams.
        } 

        for(int i = 0; i < s.size(); i++){
            s_hash[s[i]]++;
            t_hash[t[i]]++;
        }

        return s_hash == t_hash; //We can just compare the two hash maps.
    }
};
```

## Two Sum

### Problems had
1. Small issue in how to return a pair of integers, had to look up the syntax for that.
2. Reduced lookup of unordered_map synxtax. Improving with practice.
3. Took some time to figure out the order of what to store as key and value.
4. Did a lot of comments which is not inherently bad.

### Solution

Was able to solve? Yes, with small syntax lookups.

Is it optimal? Yes, time complexity is O(n) and space the same since we iterate once through the vector and only store a count of said vector.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> differences; // Key = Difference, Value = Num


        // Iterate through the vector
        // Calculate the difference  target - num[i] = result
        // 7 - 3 = 4
        // differences[4] = 3 index
        // Hash  differences[result] = i 
        // 7 - 4 = 3
        // if differences[4] exists 
        // If  target - num[j] exists within differences, we have found our result?

        for(int i = 0; i < nums.size(); i++){
            int result = target - nums[i]; // 7 - 3 = 4

            //In next iteration 7 - 4 = 3
            // If our current NUM exists as a KEY
            if(differences.count(nums[i])){
                return {differences[nums[i]],i};
            }
 
            differences[result] = i; // Add to has at the end so it doesn't consider itself as the second number. Also avoid an if statement.
        }

    }
};
```

## Group Anagrams

### Problems had
1.- Incompatibility in using vector as key for unordered_map, had to change to map for code to compile. Still need to look up the documentation to understand why this is the case.
2.- Issues with iterators trying access i and j beyond the size of the vector, had to change the condition of the loop to avoid out of bounds errors.

### Solution

Was able to solve? Yes, with small syntax lookups.

Is it optimal? Not exactly. Complexity is O(n*m*logn). An iteration through the vector of strings is O(n), then we have an iteration through the characters of each string which is O(m), and finally we have the logn complexity of inserting into the map. We can optimize this by using a different hashing approach. Finding a way to go back to using an unordered_map could bring down the complexity since we save the time.
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<vector<int>, int> char_counts; //We store the count of characters an the assigned output index as value
        // This right here is the reason for the logn complexity, since we are using a map instead of an unordered_map. We can optimize this by using a different hashing approach that allows us to use an unordered_map.
        // The complexity is still acceptable, but we can optimize it further.

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
```
### Optimal solution
Observation: While an unordered_map turns the code into something more optimal, maybe related to how map still needs some lookups. Need to review the documentation to understand better the differences between them and how they affect the complexity of the code.

Map allows for more than one value to be stored under the same key, which leads to the issue of having some lookups that are not O(1) since we need to iterate through the values of the same key to find the one we need. This is not the case with an unordered_map, which only allows for one value per key, so we can just do a direct lookup.

## Top K Frequent Elements


### Problems had
1.- Needed to lookup bucket sort.
2.- Need to lookup syntax for priority_queue as well as the core concept of min_heap and max_heap.
3.- Issues with iterating through vectors of vectors.
4.- Failed to take advantage of .second and .first functionality of unordered_map, which would have made the code cleaner and easier to read.
5.- Almost got it in second attempt but failed at the end in the iteration of the frequency vector. Getting close to the solution but missing some details in the implementation. Need to review the code and understand better the logic behind it to be able to implement it correctly.

### Solution

Was able to solve? Yes, during third attempt, with minor issues in the indexes but was able to address them with some debugging.

Is it optimal? While the nested for loop may suggest at first glance an O(n^2) complexity, the inner loop is not iterating through the entire vector, but only through the frequencies of the numbers, which in total will be O(n) since the sum of the frequencies is equal to the size of the input vector. Thus, the overall time complexity of this solution is O(n) and space complexity is also O(n) since we are using a vector of vectors to store the frequencies and an unordered_map to store the count of each number.

### My Solution
This solution is mostly similar to the optimal one with some small differences in the implementation of loops. The idea being making a bucket sort based on frequencies and then iterating through the buckets to get the most frequent numbers until we have k numbers.

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> counts;  // Key = Num[i], Value = Count;

        // Our max frequency is equal to nums.size(). Because at most an X element can fit nums.size() times in the array.
        // In a [0,1,1,4,6,7,8,8,1] vector size = 9
        vector<vector<int>> frequencies(nums.size()+1);

        // Victor with maximum capacity.
        vector<int> result;

        // We iterate through our num vector and count frequencies
        for(int num: nums){
            counts[num]++;
        }

        for(auto i: counts){
            // We store the numbers based on their frequency on the array.
            frequencies[i.second].push_back(i.first);
        }

        for(int i = frequencies.size()-1; i > 0; i--){
                for(int j = 0; j < frequencies[i].size(); j++){
                    result.push_back(frequencies[i][j]);
                }
                if(result.size() == k){
                     return result;
                }
        }
        return result;
    }
};
```


### Optimal solution
REMINDER: Keep solution hidden when retrying the problem on my own.

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count; // Key = Num in vector, Value = Frequency
        vector<vector<int>> freq(nums.size() + 1); // Vector of vectors that will store the numbers based on their frequency. Important to note it is created N + 1 frequencies. Becuase the size function on its own would create from 0 to N - 1, but we need to account for the case where a number appears N times, thus we need to create a vector of size N + 1 to have an index for that case.
        //We know the max lenght of this vector because at most a number can appear nums.size() times, so we create a vector of vectors of that size.

        for (int n : nums) { // Iterate through numbs
            count[n] = 1 + count[n]; // Adding to the count of the number, if it doesn't exist it is added.
        }
        for (const auto& entry : count) { // For each existing number in the hash
            freq[entry.second].push_back(entry.first); // Here we are using the pair that composes our KEY and VALUE in the hash map.
            // Push_back here will add the number at the end of the nested vector. This is only done since it is faster than inserting at the beginning, but it doesn't affect the final result since we will be iterating through the freq vector backwards, so we will get the most frequent numbers first.
            // The VALUE, entry.second, is used as the bucket index, and the KEY, entry.first, is added as the value. Thus we are putting the numbers in a bucket of how frequent it is.
        }

        vector<int> res; // Final result vector.
        for (int i = freq.size() - 1; i > 0; --i) { // We iterate through the frequency vector, since the biggest frequencies are at the back. e.g [0, 1, 2, 3, 4] where the index represents the frequency and the value is a vector of numbers that appear that many times. We start from the back since we want to get the most frequent numbers first.
            for (int n : freq[i]) { // Then we iterate through the nested vector to get the numbers that appear i times.
                res.push_back(n);
                if (res.size() == k) { // If we have already added k numbers to the result, we can return it.
                    return res;
                }
            }
        }
        return res;
    }
};
```

## Encode and Decode Strings

### Problems had
1.- Issues with amount of characters in the string. For example Hello turned confusing if 4 or 5 was needed to signal.
2.- Overcomplication with the use of for loops when a while loop was more appropriate to iterate through the string and extract the size of the string and the string itself. This is because we need to iterate until we find the separator, which can be at any position in the string, thus a for loop with a fixed number of iterations is not ideal for this case.
3.- In a way this solution is partially also using two pointers, since we have one pointer that is looking for the separator and another that is looking for the size of the string. This is a good example of how different concepts can be combined to solve a problem.
4.- During second attempt, I failed to totally comprehend where my i and j pointers should be at each moment until much later. It's important to keep some form of example in mind to understand the logic behind the movement of the pointers and how they interact with each other. This is a good example of how important it is to have a clear understanding of the problem and the solution before trying to implement it, since it can lead to confusion and mistakes in the implementation.

### Solution
Was able to solve? Yes, although still had some problems with indexes. Would be ideal to retake the problem on my own in a few days to see if the concepts are better understood.

```cpp
class Solution {
public:

    string encode(vector<string>& strs) {
        string result = "";

        for(string s: strs){
            result = result + to_string(s.length()) + '#' + s;
        }
        return result;
    }

    vector<string> decode(string s) {
        int i = 0;
        int j = 0;

        int lenght = 0;

        vector<string> result;

        // While J hasn't reached the end of the string...
        while(j < s.length()){
            // If we reach an index with our separator.
            // EX: 10# ->  i = 0 = '1', j = 2 = '#'
            if(s[j] == '#'){
                // Get a substring starting from index i ansd 
                // Ex:  Substr strartin from 0 and goes 2 character forward.
                cout << s.substr(i,j-i) << endl;
                lenght = stoi(s.substr(i,j-i));

                // i = j = 2
                i = j;
                // i = 3
                i++;
                // J = J + 10 = 12
                j += lenght;

                // Substr from 2 to a lenght of...
                // j - i = 12 - 2 = 10
                result.push_back(s.substr(i,j-i+1));

                i = j;
                i++;
            }
            j++;
        }
        return result;
    }
};
```

Is it optimal? Yes, time complexity is O(n) since we are iterating through the string once to decode it, and space complexity is also O(n) since we are storing the result in a vector of strings.

The way the indexes are handled in the end is a little clunky and lends itself to some confusion, but the overall logic is there and it works. With some practice and retaking the problem on my own, I can improve the implementation and make it cleaner.

### Optimal solution
```cpp
class Solution {
public:
    string encode(vector<string>& strs) {
        string res; // Result string
        for (const string& s : strs) { // For each string in the input vector.
            res += to_string(s.size()) + "#" + s; // We add, the size of the string, then the separator, then the string itself.
            // Example: "Hello" -> "5#Hello". This way we can easily decode it later by looking for the separator and then using the size to know how many characters to take for the string.
        }
        return res;
    }

    vector<string> decode(string s) {
        vector<string> res; // Result vector of strings
        int i = 0; //Iterator variable to go through the string.
        while (i < s.size()) { //While we haven't reached the end of the string.
            int j = i; // J iterator variable to find the separator.
            while (s[j] != '#') {
                j++;
            }
            // Now that J has found the separator, we have two points. I at the start of the number and J at the separator. We can use these two points to extract the number that represents the size of the string.
            int length = stoi(s.substr(i, j - i)); //IMPORTANT: SUBSTR IS NOT A RANGE, BUT A STARTING POSITION AND AMOUNT TO TAKE.
            // Substr logic: Starting from index i, we want to take the difference of j and i characters, since j is at the separator and i is at the start of the number, this will give us the correct length of the number. Then we use stoi to convert that substring into an integer, which will represent the length of the string we need to extract next.
            i = j + 1; // Push i to the position right after the separator, which is the start of the string we want to extract.
            j = i + length; // Push j to the position right after the string we want to extract, which is the start of the next number for the next iteration.
            res.push_back(s.substr(i, length)); // We extract the string using substr again, starting from i and taking length characters, which will give us the correct string. Then we add it to the result vector.
            i = j; // Make i jump to the end of the string we just extracted, which is the start of the next number for the next iteration.
        }
        return res;
    }
};
```
## Product of Array Except Self

### Problems had
1.- Some issues with the iteration of the vector. Although logic for it has improved, I still need to be careful with the conditions of the loops to avoid out of bounds errors.
2.- Quick issues with redeclaring variables and adding intead of multiplyin in final part. Not big deal but can confuse myself if I don't pay attention to it.
3.- Confused myself by getting my own example wrong before correcting it. The idea is there but need to be careful with the details.

### My Solution
Was able to solve? Yes, some struggles with mentally following an example. But can be solved with some pen and paper to keep track.

Is it optimal? Yes, time complexity is O(n) and space is O(1) since we are not using any extra space to store the products, we are just using the result vector to store the final products.

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(),1);

        // [2,4,6,8]

        // Result must be [192, 96, 64, 48] <- Be specially careful with your own examples, it's easy to mess up the calculations and get confused. Always double check your examples to make sure they are correct before using them to understand the logic of the solution.
   
        int product = 1;
        // Result we want [0, 1*2, 1*2*4, 1*2*4*6,]     
        // Result we want from here [0, 2, 8, 48]
        for(int i = 1; i < nums.size(); i++){ 
            product *= nums[i-1]; // This minus on is the key to achieve the skip of the current element. Since we are storing the product of PREVIOUS element, we are essentially skipping the current element in the multiplication, which is what we want since we want the product of all elements except the current one.
            result[i] = product;
        }

        // Result we want [ , , ,  ,48]

        product = 1;

        for(int i = nums.size() - 1; i > 0; i--){
            product *= nums[i];
            result[i-1] *= product;
        }

        return result;
    }
};
```

### Optimal solution
Some exercises have a very specific optimal solution that can not be easily guessed. In this ones I write the optimal solution first and then break it down. Retaking the problem on my own in a few days will help me understand better the concepts used in this solution.
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size(); // Define n as the size of the input vector.
        vector<int> res(n, 1); // Solution vector initialized with 1s, since we will be multiplying the values, starting with 1 is the neutral element for multiplication.

        // For each element in the input vector...
        for (int i = 1; i < n; i++) { //Note: By starting from 1, we are skipping the first element. This is because the prefix product of the first element is just 1, since there are no elements before it. This way we can avoid an if statement to handle the first element as a special case.
            
            // We calculate the prefix product.
            // To get the current prefix product, we take the previous prefix and multiply it by the previous number in the input vector. This way we are building the prefix product as we iterate through the vector.

            // Since we are storingt he prefix product of the previous element, we are skipping the current element in the multiplication, which is what we want since we want the product of all elements except the current one.
            // So if we are in res[3], we are storeing num[0] * num[1] * num[2], which is the product of all elements except num[3].
            // Right here we have achieved the skip of the current element, which is the main challenge of this problem. We are able to do this by using the prefix product of the previous element, which does not include the current element in its calculation.
            res[i] = res[i - 1] * nums[i - 1];
        }

        int postfix = 1; // Postfix product tracker, initialized to 1 for the same reason as the res vector.
        // We start at the end of the vector and move backwards to calculate the postfix product and multiply it with the prefix product we already have in the res vector. This way we are combining both products to get the final result.
        for (int i = n - 1; i >= 0; i--) {
            res[i] *= postfix; //Multiply current value * product.
            postfix *= nums[i]; // Update postfix by multiplying it with the current number in the input vector. This way we are building the postfix product as we iterate backwards through the vector. Since our skip logic is already handled in the prefix product, we can just multiply the current value in the res vector with the postfix product, which will give us the product of all elements except the current one.
        }

        return res;
    }
};
```

## Valid Sudoku

### Problems had
1. Understood the core concept of using bitwise operations, but used && instead of &. Still the core understanding of the  use of bits was there.
2. Had some issues with the calculation of the square index, but was able to address it with some debugging and writing down examples to understand better how the formula works.
3. Mismangement of parenthesis for operation order, while the code still worked it's better to ensure the correct order of operations to avoid any confusion and potential bugs in the future.

### My Solution
Was able to solve? No due to a mistake in the usage of operators confusing & with &&. Still the understanding of the problem was there.

Was able to solve? Yes, although some debugging was needed. Retaking the problem again later in the future is a good idea to see if the concepts are better understood and if I can implement it without mistakes.

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9] = {0};
        int cols[9] = {0};
        int squares[9] = {0};

        for(int r = 0; r < board.size(); r++){
            for(int c = 0; c <board[r].size(); c++){
                if(board[r][c] == '.'){
                    continue;
                }

                int val = board[r][c] - '1'; // How much we will displace a one

                if( rows[r] & (1 << val) ||
                    cols[c] & (1 << val) ||
                    squares[(r/3) * 3 + (c/3)] & (1 << val)
                ){
                    return false;
                }

                rows[r] |= 1 << val;
                cols[c] |= 1 << val;
                squares[(r/3) * 3 + (c/3)] |= 1 << val;
            }
        }
        return true;
    }
};
```

Is it optimal? Yes, time complexity is O(n^2) since we iterate through a 9x9 board once. And space complexity is O(n) due to the bitmasks used to store the presence of numbers in rows, columns and squares. The use of bit manipulation allows us to store the presence of numbers in a very compact way.

It is basically the same as the optimal solution due to constant repetition of the exercise. Still highly reccomended to retake the problem again in the future to see if the concepts are better understood and if I can implement it without mistakes.

### Optimal solution
A core concept of this solution is bit manipulation.

Basically in every index of the array we are using the bits of the integer to represent the presence of a number in the row, column or square. For example, if we have the number 3 in a row, we can set the 3rd bit of the integer at that index to 1. This way we can easily check if a number is already present in the row, column or square by checking if the corresponding bit is set to 1.

Example:

row[1] = 0000000000 (initially all bits are 0)
If we have the number 3 in the row, we set the 3rd bit to 1:
row[1] = 0000000100 (now the 3rd bit is set to 1, indicating that the number 3 is present in the row)

Then, if we want to check if the number 3 is already present in the row, we can just check if the 3rd bit is set to 1:

```cpp
/* Since 1 in binary is 0000000001, if we left shift it by 3 positions we get 0000000100, which will be representative here of the number 3.
Remember that 0000000100 in binary would actually be a 4 in decimal, but we are not interested in the decimal value. Instead, our focus is the bit position to use as a flag representing the presence of the number 3 in the row.
Then we can use a bitwise AND operation to check if that bit is set in the row[1] integer. If the result is not 0, it means that the bit is set and thus the number 3 is already present in the row.
*/
if (row[1] & (1 << 3)) {
    // The number 3 is already present in the row
}
```

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9] = {0}; //Vector to store the bitmasks for each row
        int cols[9] = {0}; //Vector to store the bitmasks for each column
        int squares[9] = {0}; //Vector to store the bitmasks for each 3x3 square, we can calculate the index of the square using the formula (r / 3) * 3 + (c / 3), where r is the row index and c is the column index.

        for (int r = 0; r < 9; ++r) { // For each row...
            for (int c = 0; c < 9; ++c) { // ... and for each column...
                if (board[r][c] == '.') continue; // If the cell is empty, we skip it.

                int val = board[r][c] - '1'; 
                /* 
                By substracting a char from another char, we get the difference in their ASCII values, which gives us the index of the number in the bitmask. For example, if we have the character '3', by substracting '1' from it, we get 2. So we move 0000000001 2 times which gives us 0000000100, which is the bitmask representation for the number 3. This way we can easily set and check the presence of numbers in the rows, columns and squares using bitwise operations.
                */


                /*
                    SO...

                    We want to set the 3 in our bitmask to present? We use the calculated 2 to push the 1 to the left 2 times, which gives us 0000000100. This way we have a bitmask with only the bit at index 2 set to 1, which represents the presence of the number 3 in our row, column or square.

                    Char '3' has an ASCII value of 51, and char '1' has an ASCII value of 49. So by doing '3' - '1', we get 51 - 49 = 2, which is the amount of position we want to shift the bit to the left to represent the number 3 in our bitmask. This is a common technique to convert a character representing a digit into its corresponding integer value, which can then be used for indexing or bit manipulation purposes.

                    Another more intuitive way to do this would converting the char to an integer and then substracting 1, but since we are working with chars, this is a neat trick to get the index directly without needing to convert to an integer first.
                */


                /*
                    We check if the current number is already present in the current row, column or square by checking if the corresponding bit is set to 1 in the respective bitmask. If any of these checks return true, it means that the number is already present and thus the board is not valid, so we return false.

                    Breakdown of the condition:
                    1 << val: This creates a bitmask with only the bit at index 'val' set to 1. For example, if val is 2, this will create the bitmask 0000000100.
                    
                    So if rows[r] is  something like 0110000100 then the operation looks like this

                    rows[r] & (1 << val) -> 0110000100 & 0000000100 = 0000000100 (which is not 0, meaning the bit is set and thus the number is already present in the row)

                    The same is applied for the columns and squares. If any of these checks return true, it means that the number is already present in that row, column or square, which violates the rules of Sudoku, so we return false.

                    Breakdown of squares index calculation:
                    The formula (r / 3) * 3 + (c / 3) is used to calculate the index of the 3x3 square that the current cell belongs to.

                    For example, if we are at row 4 and column 5, we can calculate the square index as follows:

                    (4 / 3) * 3 + (5 / 3) = (1) * 3 + (1) = 3 + 1 = 4 //

                    (1 / 3) * 3 + (1 / 3) = (0) * 3 + (0) = 0 + 0 = 0

                    (r / 3) tells us which group of 3 rows we are in. The times 3 is to scale it up to the correct index for the squares. Then we add (c / 3) to determine which column group of 3 we are in within that square.


                    Take into account the values are integer divisions, so they will be rounded down. Thus what a person would count as square 2, would be indexed as 1 since we start counting from 0. This is a neat way to map the 9 squares of the Sudoku board to indices from 0 to 8 in our squares array.
                
                */
                if ((rows[r] & (1 << val)) || (cols[c] & (1 << val)) ||
                    (squares[(r / 3) * 3 + (c / 3)] & (1 << val))) {
                    return false;
                }

                // The |= operator is used to set the bit at index 'val' to 1 in the respective bitmask, indicating that the number is now present in that row, column or square. This is done after we have checked for duplicates, so we are updating our bitmasks to reflect the presence of the current number for future checks.
                rows[r] |= (1 << val);
                cols[c] |= (1 << val);
                squares[(r / 3) * 3 + (c / 3)] |= (1 << val);
            }
        }
        return true;
    }
};
```

## Longest Consecutive Sequence
The problem consist on finding the lenght of the longest consecutive sequence in an unsorted array of integers. By sequence meaning to find all the elements that are consecutive to each other, for example in the array [100, 4, 200, 1, 3, 2], the longest consecutive sequence is [1, 2, 3, 4], which has a length of 4.

### Problemas had
1. Minor lookup with syntax, noticable need for lookup though.
2. Issues with the while loop passing an element that never advanced to end condition. Was able to address with printing and debugging.
3. Understood the use of Union Find could help in optimizing this problem, but could not see how to implement it.
4. Also forgot to handle empty array, but easily solved with an if statement at the beginning of the function.
5. Struggled with finding a condition to skip already processed numbers. My approach being any processed one would have a value greater than 0. 
    - The current solution uses (!mp[num]). This statement will return 1 only if the number is 0, which is the default value for any key that does not exist in the map. Any other number like 1,2,3... will be flipped to 0. The logic is the same, but the way it is implemented in the optimal solution is more elegant and less prone to confusion.

### Solution
Was able to solve? Yes, but with an complexity of O(n^2) in the worst case due to iteration of all possible sequences in hash map. Will retake some days later after optimal solution review. It is still important to notice this is one of the first problems where I was able to get a solution working on my own, which is a good sign of progress. This is in fact the Brute Force solution, which is a good starting point to then optimize it further.

Was able to solve in next attempt with some struggles in the condition to check if the number is already in the hash map, but was able to address it with some debugging and printing to understand better the logic behind it.

Is it optimal? While an O(n^2) is still acceptable depending the case, the optimal solution is O(n). Retake the problem once I have reviewed the optimal solution to see if I can understand the logic behind it and implement it on my own.

The second solution only makes use of one for loop to iterate through the numbers once and even skipping processed ones. The space also would be O(n) since we are using a hash map to store the numbers and their corresponding sequence lengths. The optimal solution is more efficient than the brute force one, which is a good sign of progress in understanding how to optimize solutions.

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        if(nums.size() == 0){
            return 0;
        }

        unordered_map<int,int> sequence; // Key = num[i], Value = sequence lenght.
        int biggest = 0;

        // For each number in the input vector...
        for(int n:nums){
            if(sequence[n] > 0){
                // If sequence[n] > 0, it means we have already processed this number.
                continue;  
            }
            // Our current number checks its neighbors to find out if they are part of a sequence.
            sequence[n] = sequence[n-1] + sequence [n+1] + 1;
            // If our neighbors were already part of a sequence, we use their value to jump straight to the end of their sequences and update them with the new lenght of the sequence. This way we are able to skip all the numbers in between and directly update the ends of the sequence with the new lenght, which is the main optimization of this solution compared to the brute force one.
            sequence[n - sequence[n-1]] = sequence[n];
            sequence[n + sequence[n+1]] = sequence[n];
            if(sequence[n] > biggest){
                biggest = sequence[n];
            }

        }
        return biggest;
    }
};
```
### Optimal solution
```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> mp; // Unordered map storing a pair. They key is a num[i] and the value is the lenght of the sequence it belongs to.

        // Result variable to keep track of the longest sequence found.
        int res = 0;

        // For each num in the vector...
        for (int num : nums) {
            //  If the number is not already int the map... this piece here is how we ignore duplicates, since if a number is already in the map, it means we have already processed it as part of a sequence, so we can skip it to avoid redundant calculations and also to avoid counting duplicates as part of the sequence.
            if (!mp[num]) {
                /*
                    A number that is part of a sequence would obviosly add +1 to its value.

                    A sequence of 3 numbers would have 1+ for 1, another 1+ for 2 and another 1+ for 3.
                */

               // In this apprach each number is "bridging" to the others and extracting their lenghts.
               /*
                Ex:  [2,20,4,10,3,4,5]
                    The longest sequences if of 4 composed of 2,3,4,5.

                    When we reach to the following will happen.

                    Try to add mp[1] which does not exist so it will return 0...
                    Try to add mp[3] which exists but has a value of 0 since we haven't processed it yet, so it will return 0...
                    Add + 1 which is the own inherent addition to the  sequence of our current number, which is 2 in this case.

                    Then mp[2 - mp[num - 1]] = mp[num];
                    mp[2 - 0] = mp[2];
                    mp[2] = 1;

                    Then mp[2 + mp[num + 1]] = mp[num];
                    mp[2 + 0] = mp[2];
                    mp[2] = 1;

                    When we reach 3 the folowing will happen:

                    mp[2] + mp[4] + 1...

                    mp[2] already has a value of 1 since we have previously and mp[4] will return 0 since it is yet to be processed.

                    Thus our result will be 2, that means that for now we have a sequence of 2 numbers.

                    Then we do the following

                    mp[3 - mp[2]] = mp[3];
                    mp[3 - 1] = mp[3];
                    mp[2] = 2;

                    and

                    mp[3 + mp[4]] = mp[3];
                    mp[3 + 0] = mp[3];
                    mp[3] = 2;

                    Next we reach 4 and the following happens:
                    mp[3] + mp[5] + 1...
                    2 + 0 + 1 = 3, thus we have a sequence of 3 numbers.

                    Then we do the following:

                    mp[4 - mp[3]] = mp[4];
                    mp[4 - 2] = mp[4];
                    mp[2] = 3;
                    mp[4 + mp[5]] = mp[4];
                    mp[4 + 0] = mp[4];

                    So now we have the interesting behavior...

                    Now mp[2] = 3, mp[3] = 2 and mp[4] = 3.

                    While at first mp[3] being 2 may seem like an issue it is not.

                    There is not another number that will bridge to 3, thust it can stay at 2 without affecting the result.
                    But there are still numbers that could reach 2, which would be 1, and 4 which would be 5.

                    For visualization we will process a 1 instead of the 5 in the actual code.

                    If we process a 1, we would have the following:

                    mp[1] = mp[0] + mp[2] + 1;

                    Basically one for now assumes it self as the sequence with the +1...
                    That's the idea, every number is basically calling its neighbors asking if anybody got a sequence going already. And if they do they then link up.

                    So while 0 just returns 0 since it doesn't have a sequence going, 2 returns the current sequence of 3.

                    Thus mp[1] = 4.

                    Then we do the following:

                    mp[1 - mp[0]] = mp[1];
                    mp[1 - 0] = mp[1];
                    mp[1] = 4;

                    Basically 0 is saying there is no sequence here so don't even link to me or anyone behind me, just link to yourself.

                    Then we do the following:

                    mp[1 + mp[2]] = mp[1];
                    mp[1 + 3] = mp[1];
                    mp[4] = 4;

                    2 tells 1 that the current sequence is 3.
                    So 1 has to find the other edge of the sequence with those 3 steps and update it to 4, which is the new sequence lenght.

                    Basically we are always finding a new edge of the sequence. And if two sequences meet they will bridge and their previous and next element will give directions to find the new edges and update them with the new sequence lenght.
                    
               */
                mp[num] = mp[num - 1] + mp[num + 1] + 1;
                mp[num - mp[num - 1]] = mp[num];
                mp[num + mp[num + 1]] = mp[num];
                res = max(res, mp[num]);
            }
        }
        return res;
    }
};
```

# 2. Two Pointers

## Valid Palindrome
This problem consist on determining if a string is a palindrome, meaninng it can be read the same from both ways.

### Problems had
1. Issue with capital letters and spaces, had to look up how to ignore them.
2. Need to practice when to subtract one from functions like lenght or size to avoid out of bounds errors.
3. While I had added the i < j condition in the main while loop, I forgot  to add it in the inner while loops, which could cause out of bounds errors or infinite loops.
4. Forgetting to update the pointers at the end of comparison.
5. One very important error I did was the following:
    - Instead of comparing the alphanumeric values like this: (c >= 'A' && c <= 'Z'), I did ('A' <= c <= 'Z'). The  second notation is valid in SOME programming languages but not in C++. Sincer in C++ 'A' <= c is evaluated first which gives a boolean value and then that boolean value is compared to 'Z', which is not the intended logic and can lead to incorrect results. This is a common mistake when trying to compare a character to a range of characters, and it's important to remember that in C++ we need to compare the character to each boundary of the range separately.
    
### My Solution
Was able to solve? No, while the core problem was understood. Implementing it gave me trouble. I will try again in a few days to see if the concepts are better understood.

Was able to solve around the third attempt, running into some iteration issues but were quickly addressed. Retaking the problem again later in the future is a good idea to see if the concepts are better understood and if I can implement it without mistakes.

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0;
        int j = s.length();

        while(i < j){
            while(!isAlphNum(s[i]) && i < j){
                i++;
            }

            while(!isAlphNum(s[j]) && j > i){
                j--;
            }


            if(tolower(s[i]) != tolower(s[j])){
                return false;
            }
            i++;
            j--;
        }

        return true;
    }

    bool isAlphNum(char c){
        if( c  >= 'A' && c <= 'Z' ||
            c >= 'a' && c <= 'z' ||
            c >= '0' && c <= '9'
        ) {
            return true;
        }
        return false;
    }
};
```

Is it optimal? Yes, time complexity is O(n) since we are iterating through the string with two pointers. It may look lenghtier due to the various while loops but their logic is simply moving pointers forward in their direction until they find a valid alphanumeric character, which in the worst case would be O(n) if we have to skip all characters. Space complexity is O(1) since we are not using any extra space to store the results, we are just using a couple of variables to keep track of the pointers and the result.

This is basically the same as the optimal solution with some differences in syntax due to constant reattamps. It is recommended to retake the problem again in the future to see if the concepts are better understood and if I can implement it without mistakes.

### Optimal solution
```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.length() - 1;` //Left pointer -> Start of the string, Right pointer -> Lenght of string minus one since we are using 0 based indexing.

        while (l < r) { // This means while the left pointer hasn't passed OR met the right pointer.
            while (l < r && !alphaNum(s[l])) { // By using while we are skipping any non-alphanumeric characters until we find a valid one or our pointers cross.
                l++;
            }
            // Same logic as above, also just making sure the pointers haven met OR passed each other.
            while (r > l && !alphaNum(s[r])) {
                r--;
            }
            // Once the two pointers are at a valid alphanumeric, we lowercase them and compare.
            if (tolower(s[l]) != tolower(s[r])) {
                return false;
            }
            l++; r--; // Move the pointers forward once so they don't compare the same characters again.
        }
        return true; // If we finish the loop without finding any mismatch, it means the string is a palindrome, so we return true.
    }

    bool alphaNum(char c) { // Assistance function to determine if a character is alphanumeric.
        // The comparisons here are using their ASCII values. Essentially giving a valid range of characters. Say characters like space, punctuation, etc. are not included in these ranges, so they will be ignored in the palindrome check.
        
        // This is very important to consider in a lot of problems that require to extract information from a char or string. A char has a numeric value assigned to it based on the ASCII table. Implementation may depend on language but the point is this value is standardized and thue reliable. So, this specific part is more a topic of software knowledge rather than intuition.

        return (c >= 'A' && c <= 'Z' ||
                c >= 'a' && c <= 'z' ||
                c >= '0' && c <= '9');
    }
};

```

## 2. Two Sum II - Input Array Is Sorted
This problem is a variation of the Two Sum problem, but in this case the input array is sorted in non-decreasing order.

### Problems had
1.- Slight issues with forgetting to advance the J pointers, thus a condition not fulfilling and getting stuck.
2.- Reduced issues with size of input array in comparison with other exercises, but still need to be careful with the conditions of the loops to avoid out of bounds errors.
3.- Small issue in the return in which a correct answer was being returned, but not the one expected by the problem.

### My Solution
Was able to solve? Yes, with a small problem at the end with an odd behaviour in the return. In one of the final cases [748, 749] was returned which was a correct answer but not the one expected of the problem which was [498, 999]. This happened because I pushed the indexes within the range of the while statement and returning after its execution. This cas fixed by returning the result immediately after finding the solution, thus avoiding any further changes to the result variable.

The problem was that with such a large array... going from -999 to 999, the solution could be found more than once. Thus it is important to return after the first solution is found. The error I did was just pushiong the pointers forward in an incorrect assumption they would've crossed and not considering there could be more array to explore. This is a good example of how important it is to understand the problem and the edge cases that may arise, especially when dealing with large input sizes. Retaking the problem again in the future is a good idea to see if the concepts are better understood and if I can implement it without mistakes. Also an important example of knowing when to exit a loop and return a result, which is a common point of confusion in coding interviews.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0; //Left and right pointers
        int r = numbers.size() - 1;
        vector<int> result(2, -1);

        while(l < r){
            int sum = numbers[l] + numbers[r];

            if(sum < target){
                l++;
            } else if (sum > target){
                r--;
            } else {
                result[0] = l+1;
                result[1] = r+1;
                return result;
            }
        }
        return result; 
    }
};
```

Is it optimal? Yes, time complexity is O(n) since we are iterating through the array with two pointers, taking advantage of the sorted nature of the array to skip unnecessary comparisons. Space complexity is O(1) since we are not using any extra space to store the results, we are just using a vector of size 2 to store the indices of the result.
 
### Previous Solution
Was able to solve? Yes, with some struggles in the implementation.


```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {        
        int i = 0;
        int j = 1;

        vector<int> result(2,-1);


        while(j < numbers.size() && i < numbers.size() -1){
            while(i != j){
                if((numbers[i] + numbers[j]) == target){
                    result[0] = i+1;
                    result[1] = j+1;
                    return result;
                 }
                i++;
            }   
            i = 0;
            j++;     
        }
        return result;
    }
};
```

Is it optimal? No, time complexity is O(n^2) since in the worst case we iterate through the array with both pointers, and space complexity is O(1) since we are not using any extra space to store the results, we are just using a vector of size 2 to store the indices of the result.

### Optimal solution
This solution has a time complexity of O(n) since we are iterating through the array with two pointers, and space complexity is O(1) since we are not using any extra space to store the results, we are just using a vector of size 2 to store the indices of the result.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1; //Declare two pointers, one at the start of the array and another at the end.

        // This implementation properly takes advantage of the fact the array is sorted since we can always move to a smaller or bigger number for our sum. 
        // And we can have the confidence this move is not skipping the solution.
        while (l < r) {
            int curSum = numbers[l] + numbers[r]; // We make a first sum with the border numbers, this will be our starting point to compare with the target.

            if (curSum > target) { // If our current sum is bigger than the target, it means we need to reduce it. Since the array is sorted we can just move the right pointer closer.
                r--;
            } else if (curSum < target) { // On the opposite case, if our current sum is smaller than the target, it means we need to increase it. Since the array is sorted we can 
                l++;
            } else {
                // If the sum is not bigger or smaller, then it can just mean its equal, which means we have found our solution and we can return the indices. We add one to each pointer since the problem statement asks for 1-based indices.
                return { l + 1, r + 1 };
            }
        }
        return {};
    }
};
```

## 3. Three Sum
The problem consist on finding all unique triplets in the array which sum up to zero. The indexes of the triplets must be different and the solution set must not contain duplicate triplets.

### Problems had
1. Issues with iteration through the array and handling pointers, although no out of bounds errors.
2. Struggles with handling duplicates and how to prevent them.
3. Was creating a "current" vector to store the current triplet while I could just make the push with a constructed triple during the result.push_back, which is more elegant and less prone to errors.

### My Solution
Was able to solve? No, the main issue with my attempted solution is it depended on a very specific position of the I and J pointers while only K was the one exploring which would miss some possible combinations. Retaking the problem again in the future is a good idea to see if the concepts are better understood and if I can implement it without mistakes.

### Optimal solution
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // Even if sorting the array has an additional cost of O(n log n), it allows us to use the two pointers technique based on moving the pointers inwards to find the solution.
        // Without the sorting our complexity goes up to O(n^3) which is much larger than the O(n^2) we can achieve with the two pointers technique.
        // Thus, sorting is an acceptable cost to achieve a much better time complexity.
        // In Big-O notation the fastest growing term is the one that matters. So the O(nlogn) is we could say...
        // ... absorbed by the O(n^2) since n^2 grows faster than n log n, thus we can say the overall time complexity is O(n^2).
        sort(nums.begin(), nums.end());
        // Result vector
        vector<vector<int>> res;

        // For each element in the array...
        for (int i = 0; i < nums.size(); i++) {
            // Now that the array is sorted we can include an early exit condition...
            // If our current i is bigger than 0, it means we are in the positive numbers, thus we can stop since we won't be able to find a sum of 0 with only positive numbers.
            // Keep in mind it must be bigger than, not equal to, since we could have a 0 in the array which would be a valid solution if we have two other 0s.
            if (nums[i] > 0) break;
            // If the current number is the same as the previous one, we would end up with duplicate triplets, thus we skip it to avoid that.
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // We define a left pointer that is one position ahead of i, and a right pointer that is at the end...
            // ... of the array, and we will move them inwards to find the combinations that sum up to 0 with the current i.
            int l = i + 1, r = nums.size() - 1;
            // From here we are basically doing the same as the two sum problem with a sorted array.
            // So while our left and right pointers don't cross...
            while (l < r) {
                // We calculate the sum of the current triplet.
                int sum = nums[i] + nums[l] + nums[r];
                // If the sum is bigger than 0, we need to move the right pointer to the left.
                if (sum > 0) {
                    r--;
                // Otherwise if sum is smaller, we need to make our number bigger by moving the left pointer to the right.
                } else if (sum < 0) {
                    l++;
                // Otherwise it's equal to 0 and we can push it for our result.
                } else {
                    res.push_back({nums[i], nums[l], nums[r]});
                    // Move our pointers to avoid returning the same triplet again, since we could have duplicates in the array.
                    l++;
                    r--;
                    // We also do a while to try and skip any duplicate AND adjacent numbers. 
                    // Duplicates numbers in itself COULD give a different result, but if they are adjacent and in a sorted array we will be stumbling upon the same triplet again, thus we skip them to avoid duplicate triplets in our result.
                    // Again, remember that repeated numbers that are not adjacent CAN give different results.
                    while (l < r && nums[l] == nums[l - 1]) {
                        l++;
                    }
                }
            }
        }
        return res;
    }
};
```

## 4. Container With Most Water

### Problems had
1. Very minimal issues with the size of the input array.

### Solution
Was able to solve? Yes, with minimal issues.

```cpp
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
```

Is it optimal? Yes, time complexity is O(n) since we are iterating through the array with two pointers, and space complexity is O(1) since we are not using any extra space to store the results, we are just using a variable to store the best area found. There is some small optimizations on the handling of the best variable, but overall the logic is the same.

Logic Breakdown: Since our best possible case is the two edges of the array composing the best container, the only way to find a better solution is moving the smallest of the pointers inwards in hopes of trying to find a bigger height that can compensate the reduction of the base. If we move the bigger pointer, we are just reducing the base without any chance of finding a bigger height, thus we would be reducing the area and not finding a better solution.

### Optimal solution
The previous solution is already optimal, this code just some optimizations and cleanliness improvements, but the core logic and complexity is the same.
 
The main difference is this code doesn't calculate a first case before the loop, but instead it calculates the area inside the loop and compares it with the best area found so far. This way we can avoid some redundant code and make it cleaner.
```cpp
class Solution {
public:
    int maxArea(vector<int>& heights) {
        int l = 0;
        int r = heights.size() - 1;
        int res = 0;

        while (l < r) {
            int area = min(heights[l], heights[r]) * (r - l);
            res = max(res, area);

            if (heights[l] <= heights[r]) {
                l++;
            } else {
                r--;
            }
        }
        return res;
    }
};
```



# 3. Stack

## 1. Valid Parentheses
This problem consists on determining if a string of parenthesis is valid, meaning every opening parenthesis has a corresponding closing parenthesis in the correct order.

### Problems had
1. Issues with the insertion and removal of elements in the stack.
2. Good call using a hash map to store possible pairs, but didn't use it to its full potential.
3. While not fully remembering the solution, was able to come back to the solution with logic. Which is in its own way better than just memory, just need to train it more to be more efficient and less prone to errors.
4. Small struggles with edge cases, specifically having a closing parenthesis without opnening ones.

### My Solution
Was able to solve? No, some issues with the stack going out of bounds.

Was able to solve on third attempt, just some struggles with fully figuring out the logic and edge cases, but was able to get there with some debugging and printing.

```cpp
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
```

Is it optimal? Yes, time complexity is O(n) since we iterate through the string once, and space at worst is of O(n) if all the string is opening parenthesis. One important thing to notice is there are more elegant ways to handle some things like the final return of true or false. Simply returning the result of is empty would be cleaner than the if statement.

### Optimal solution
My first solution was very close to the optimal one, but only failed due to failure of addressing some edge cases and not using the hash map to its full potential. The optimal solution is cleaner and more efficient since it uses the hash map to store the pairs of parentheses and thus can easily check if the current closing parenthesis matches the last opening parenthesis in the stack. Also the way if statements are organized could be more readable even if the logic in the optimal solution and this one is the same. Still a functional code that is open to be optimized is a good sign of progress.

```cpp
class Solution {
public:
    bool isValid(string s) {
        std::stack<char> stack; // Create stack to store opening parenthesis.

        // Hash map to store pairs of parenthesis, this avoids creating lengthy if statements to compare each case of parenthesis, we can just do a lookup in the hash map to check if the current closing parenthesis matches the last opening parenthesis in the stack. 
        // With some extra code it can even reject invalid characters that are not parenthesis, but since the problem statement doesn't mention that, we can assume the input will only contain valid parenthesis characters.
        std::unordered_map<char, char> closeToOpen = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        // For each character in the string...
        for (char c : s) {
            // If we can find the character in the hash map, it means it is a closing parenthesis...
            if (closeToOpen.count(c)) {
                // If our stack is empty AND the top of the stack matches with the corresponding parenthesis we can pop anc continue.
                if (!stack.empty() && stack.top() == closeToOpen[c]) {
                    stack.pop();
                } else {
                    // Otherwise it means we have a mismatch either through a lack of opening parenthesis or a mismatch of types, thus we can return false.
                    // This here covers edge cases of the parenthesis being closed without being opened, or the wrong type of parenthesis being closed.
                    return false;
                }
            } else {
                // If the character is not within the hash map, it means it is an opening parenthesis, thus we can just push it to the stack and continue.
                // This assuming all the character are parenthensis, which they are as per the problem statement.
                stack.push(c);
            }
        }
        // If we finish iterating through the string and our stack is empty, it means all the parenthesis were properly closed and thus we can return true. If the stack is not empty, it means we have some opening parenthesis that were not closed, thus we return false.
        
        // This also covers the edge case of an empty string, since if the input string is empty, we will never enter the loop and thus we will just return true at the end since an empty string is considered a valid parentheses string.
        return stack.empty();
    }
};
```

## 2. Min Stack
This problem consists on designing a stack that supports push, pop, top operations in constant time, and also retrieving the minimum element in constant time.

### Problems had
1. Issues with the handling of minimum elements. My approach using a secondary stack to keep tracks of minimums that had some edge cases that were not handled properly such as trying to update the min when the stack is empty, or when the new element is equal to the current minimum.
2. While the logic of the secondary stack was still efficient, it still represented some extra space usage that could be optimized.

### My Solution
Was able to solve? Yes, with some issues in the handling of the minimum stack.


Is it optimal? My first solution... yes since all operations are in O(1) time, but the use of a secondary stack could be optmized.

### Optimal solution
What this approach does is instead of storing the actual values, it stores encoded ones via pushing the difference between the current value and the min value. And when a new minimum is pushed we store a negative encoded value, which signals a change in min. This stack is storing changes in the minimum rather than the actual values, since the core of the problem and our interest is the minimum value, not neccesarely the whole stack of values.

```cpp
class MinStack {
private:
    // Values of minimum and the stack
    long min;
    std::stack<long> stack;

public:
    // Constructor doesn't need any starting values since the first push will set the minimum and the stack will be empty, thus we can just initialize them as they are.
    MinStack() {}

    void push(int val) {
        // If the stack is empty...
        if (stack.empty()) {
            // We push a 0 to the stack since the difference between the current value and the minimum is 0, and we set the minimum to the current value.
            stack.push(0);
            // Since it is our first item we can just put it as the minimum without any calculations.
            min = val;
        // If the stack is not empty...
        } else {
            // We push the difference between the current value and the minimum of the stack.
            // So if we pushed 5 and our min is 4 the stack will store a 1, which is the difference between the current value and the minimum. This way we can keep track of how much we are above the minimum with each value.
            // Instead if we stored a 2 and our min is 4, we would end up pushing a -2, which is a signal that we have a new minimum, since we are 2 below the current minimum. This way we can keep track of how much we are below the minimum with each value, and also know when we have a new minimum.
            // Essentially the stack is storing changes in the minimum. By pushing the two we are telling the stack, "The min is has decreased by 2"
            // If the current value
            if (val < min) min = val;
        }
    }

    void pop() {
        // We just ignore a pop if the stack is already empty.
        if (stack.empty()) return;

        // We store the popped value since it may contain information about the min or even be the minimum itself, since we are pushing differences in the stack.
        long pop = stack.top();
        // We pop the value from the stack.
        stack.pop();

        // If pop is a negative, it means we had a new minimum.
        // Say we had a -2 like we had said in the stored 2 and min 4 example...
        // We know our min had been reduced by 2...
        // And if we substract a negative we get a positive, thus this operation adds the 2 back to the minimum. 
        // Essentially we are asking "Did the popped number lead to a change in the min? If so, restore the min to the previous value before the change."
        if (pop < 0) min = min - pop;
    }

    int top() {
        // Here something interesting occurs, since our stack is storing difference, the top is not what was pushed.
        long top = stack.top();
        // So if top is a positive number, it means the current value is a above the min. So we just add back that difference to the min to get the actual value.
        // If its a negative it means the min is the current top, so we just return the min since the current value is the new minimum.
        return (top > 0) ? (top + min) : (int)min;
    }

    int getMin() {
        // A simple return of the minimum value, since we are keeping track of it with each push and pop, we can just return it in O(1) time.
        return (int)min;
    }
};
```

# 4. Binary Search

## 1. Binary Search
This problem consist on finding the index of a target value in a sorted array of integers. If the target value is not present in the array, return -1.

### Problems had
1. Issues with the handling of indexes, specially considering this problem can have a lot of off by one errors. Practice more with the handling of indexes and the conditions of the loops to avoid out of bounds errors.
2. Problems with the condition to stop the while loop, which is a common point of confusion in binary search problems. Practice more with the conditions of the loops to avoid infinite loops or missing the target value.
3. While the core logic of the binary search was understood, implementing it gave me some trouble. Practice more with the implementation of binary search to be more efficient and less prone to errors.

### My Solution
Was able to solve? No, some issues with the handling of indexes and the conditions of the loops.

For example in the case [5] with target 5, my condition was while (l < mid && r > mid) which would exit the loop without checking the mid value because mid = l = r = 0, thus missing the target value. This was fixed by changing the condition to while (l <= mid && r >= mid) which allows us to check the mid value even when l and r are equal to mid.

Another struggle was how my change of middle was implemented. I was only doing a division of the difference between r and l, but forgot to add the value.

### Optimal solution

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // We can calculate the middle point at the moment by having a left and right pointer.
        int l = 0, r = nums.size();

        // While our left and right pointer haven't crossed each other...
        while (l < r) {
            // In this approach the left pointer is the one that will be moving forward and the right pointer will be moving backwards, but they will never cross each other. Thus we can use the condition l < r to make sure we are still within the bounds of the array and haven't missed the target value.

            // Ex:  [1,2,3,4,5,6,7,8,9,10], target = 3
            /*
                m = 0 + (10 - 0) / 2 = 5;
                m = 0 + (5 - 0) / 2 = 2; -> Found target value, return index 2.

                Target = 9
                m = 0 + (10 - 0) / 2 = 5;
                m = 0 + (10 - 5) / 2 = 7;
                m = 7 + (10 - 7) / 2 = 8; -> Found target value, return index 8.

                Target = 11
                m = 0 + (10 - 0) / 2 = 5;
                m = 0 + (10 - 5) / 2 = 7;
                m = 7 + (10 - 7) / 2 = 8;
                m = 8 + (10 - 8) / 2 = 9;
                m = 9 + (10 - 9) / 2 = 9; -> Left and right pointers have crossed each other, exit loop and return -1 since target value is not found.
                
                
            */

            // We add to l the difference between r and l divided by 2, this way we are moving the left pointer forward to the middle point. We could also move the right pointer backwards to the middle point, but in this implementation we are moving the left pointer forward.
            // This was a important mistake in my implementation, since I was only doing (r - l) / 2, but forgot to add the value of l, thus always calculating the middle point from the start of the array instead of from the current left pointer, which would cause us to miss the target value if it was in the right half of the array.
            int m = l + (r - l) / 2;
            if (nums[m] >= target) {
                // An important thing to notice is that we are checking if m is greater than or EQUAL to the target,
                // With this approach our search is contantly CLOSING IN on the target value.
                // Thus if we did m > target, we would be stuck in an index at least 1 position away from the target value, and we would miss it if it was in the right half of the array.
                r = m;
            } else {
                // If we are here, we know that m is not greater than or EQUAL to the target. That is why the + 1 is important here, since we know for sure that m is not the target value, thus we can move the left pointer to m + 1 to skip it and move forward in our search. This also helps prevent infinite loops in cases where l and m are the same, since if we did l = m, we would be stuck in the same index and never move forward, thus missing the target value if it was in the right half of the array.

                // Now, how would these two cross to exit the loop? If we have a case where l and r are next to each other, say l = 0 and r = 1, and m is calculated as 0 + (1 - 0) / 2 = 0, if nums[0] is less than the target, we would move l to m + 1, which would make l = 1. Now l and r are both at index 1, and if nums[1] is greater than or equal to the target, we would move r to m, which would make r = 0. Now l is greater than r, which means we have crossed each other and thus we exit the loop.

                // Basically l eventually would close in and PASS r, r would not pass l since it is acting as an upper bound, but l is the one that is actually moving forward in our search, thus it is the one that can eventually cross r and exit the loop.
                l = m + 1;
            }
        }
        // If l isnt out of bounds and the value at index l is equal to the target value, it means we have found the target value and we can return its index. Otherwise, it means the target value is not in the array and we can return -1.
        return (l < nums.size() && nums[l] == target) ? l : -1;
    }
};
```

 
# 6. Linked List

## 1. Reverse Linked List

### Problems had
1. Issues with the handling of the pointers, practice more with the handling of them.
2. Issues with what to return when using a recursive solution.
3. Very lenghty time to come up with a solution, but could come up with one. Improve time with practice and review of optimal solution.

### My Solution
Was able to solve? Yes, with some struggles in the implementation.

Solution 1: Recursive approach
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr){
            return nullptr;
        }

        return reverseListRecursive(head);
    }

    ListNode* reverseListRecursive(ListNode* head){
        if(head->next == nullptr){
            return head;
        }
        cout << "Before switch: " << head->val << endl;

        ListNode* newHead = reverseListRecursive(head->next);

        ListNode* temp;

        // 1 -> 2 <- 3 <- 4
        // 1 -> 2
        // temp = 2
        // 1 -> nullptr
        // 2 -> 1
        
        temp = head->next;
        head->next = nullptr;
        temp->next = head;

        cout << "After switch: " << head->val << endl;

        return newHead;
    }
};
```

Is it optimal? Yes, the time complexity in recursion is O(n) since we visit every node once. Space complexity is O(n) since we store every recursive call. While this is acceptable, we can optimize the space complexity to O(1) by using an iterative approach.


### Optimal solution
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr; // Previous node pointer.
        ListNode* curr = head; // Current node pointer, initialized to head of the list.

        // While current means that any node that is not null is a valid node to process.
        while (curr) {
            // 1 -> 2 -> 3 -> 4
            // temp = 2;
            ListNode* temp = curr->next; // We store the next node ina  temporary variable.
            // 1 -> nullptr
            curr->next = prev;
            // prev = 1
            prev = curr;
            // curr = 2
            curr = temp;

            // Basically we store the next node in the sequence in temp...
            // Then we make the current node point to its previous one instead of the next one, thus reversing the link between them...
            // Also by starting prev with null we are making sure the new tail has a null pointer.
            // We now give the new prev value to what was our current node, we can say we already passed it.
            // Finally our current is what was the next node.
        }
        // At the end of the sequence the last item processed will be stored in the prev pointer, thus we return it as the new head of the reversed list.

        // The main thing to keep in mind here is what to store, when to update pointers and what to return. As well as the while loop condition, which is just checking if we have a valid node to process.
        return prev;
    }
};
```

## 2. Merge Two Sorted Lists
The problem consists on merging two sorted linked lists into one sorted linked list.

### Problems had
1. Was passing the greater number of the two instead of the smaller one, which was causing the list to be sorted in the wrong order.
2. Minor Issues with handling of pointers, practice more with them.
3. Ran into some edge cases but was able to quickly address them once detected.

### My Solution
Was able to solve? Yes, with some struggles in the implementation. While the time I took to solve was quite long, there is still noticeable improvement in my detection of issues as well as my ability to come up with a solution on my own, which is a good sign of progress. Retake the problem in a few days to see if I can solve it faster and with less issues.

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1 == nullptr && list2 == nullptr){
            return list1;
        }

        return mergeTwoListsRecursive(list1, list2);
    }

    ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2){
        if(list1 == nullptr){
            return list2;
        } else if (list2 == nullptr) {
            return list1;
        }

        ListNode* temp;
        cout << "list1 val: " << list1->val << endl;
        cout << "list2 val: " << list2->val << endl;

        // list1 = 2
        // list2 = 3
        if(list1->val <= list2->val){
            //
            cout << "list1 val is bigger" << endl;
            temp = list1->next;
            list1->next = mergeTwoListsRecursive(temp, list2);
            return list1;
        }

        cout << "list2 val is bigger" << endl;
        temp = list2->next;
        list2->next = mergeTwoListsRecursive(list1,temp);
        return list2;
    }
};
```
Is it optimal? Yes, time complexity is O(n + m) based on the lenght of the two lists, while space complexity is O(n + m) in the worsr case due to recursive calls. We can optimize the space complexity to O(1) by using an iterative approach.

Also some cleaner code could be made in the following areas:
- Handling of null pointers is already done in the recursive, thus avoiding the need for the first call function.
- Forgot to use if statements that just ask if something like (list1) or list(!list1) to check if a pointer is null, which would be cleaner than comparing it to null directly.

### Optimal solution
```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        /*
            Dummy is the starting point of our new list, but WON'T be returned in the result.
            Basically, dummy is a placeholder node from which we can start building and still have access to the actual head of the merged list through dummy.next
            This also helps handle edge cases with nulls since we always have a valid node to work with and the dummy->next return will already be a null if both lists are null, or if one of them is null, it will just return the other list as the result, which is the expected behavior.
        */
        ListNode dummy(0);
        // Node is our pointer that will iterate through the new list as we build it, starting from the dummy node.
        ListNode* node = &dummy;

        // While both lists items are valid...
        while (list1 && list2) {
            // If list1-> val is the smaller...
            if (list1->val < list2->val) {
                // If we are just starting then dummy -> next = list1.
                node->next = list1;
                // We "consume" the node we just added to the new list from the old list by advancing the pointer to the next item.
                list1 = list1->next;
            } else {
                // Same logic as above but for list2, if list2->val is smaller or equal, we add it to the new list and advance the pointer in list2.
                node->next = list2;
                list2 = list2->next;
            }
            // We advance the node to the position we have just added, so we can keep building the list from there.
            node = node->next;

            /*
                You can picture this as our new merged list constatly growing as the other two lists consume themselves. Once we add a node to the new list, we move the point of the old list forward, thus "consuming" that node and making it unavailable for future additions.

                While confusing and even seemingly as causing a memory leak, remember the following: Every item consumed in the original two lists is within the new merged list. Since we are not creating any new nodes and just changing pointers in the existing ones, we are not losing access to any node, we are just rearranging them into a new order and thus creating the merged list. The original lists are basically being deconstructed and reconstructed into the new merged list, but all the nodes are still there and accessible through the new list, thus there is no memory leak or loss of data.
            */
        }

        // Handler final edge case.

        // Since our while above requires both lists with valid items, we just do this handle the remaining items.
        // So if list1 = 6 and list2 = null, we just add whatever remaining items there are. And if both are null, we just add null, which is the expected behavior.
        // It is important to notice this will also handle cases in which more than one item from a list is remaining.
        // For example:
        /*
            list1 = 6 -> 7 -> 8
            list2 = null

            When we reach this part of the code, we will just add the remaining items of list1 to the new list, thus we will have:

            dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8

        */
        if (list1) {
            node->next = list1;
        } else {
            node->next = list2;
        }

        // We return dummy -> next since dummy is just a placeholder and the actual head of the merged list is the next item after dummy.
        // As for Dummy, since it was initialized within the function, it will be automatically deallocated once we return from the function, thus there is no memory leak or loss of data, since all the nodes that were part of the original lists are still accessible through the merged list that starts at dummy->next.
        return dummy.next;
    }
};
```

## 5. Remove Node From End of Linked List
In this problem we are given the head of a linked list and an integer n. We need to remove the nth node with our count starting from the end of the list and return the head of the modified list.

### Problems had
1. Issues with the handling of pointers, practice more with them.
2. Misunderstanding of the problem statement, I was trying to remove the nth node from the start of the list instead of from the end, which is a common point of confusion in this problem. Practice more with understanding problem statements and clarifying any doubts before starting to code.
3. Struggles with edge cases at start, but was able to address with the use of dummy node.

### My Solution
Was able to solve? Yes, with some struggles in the implementation. While I lost some time in trying to implement the problem without fully understanding the statement, I was able to apply previosly seen techniques such as the use of a dummy node to handle edge cases, which is a good sign of progress. Retake the problem in a few days to see if I can solve it faster and with less issues. Not only that but land in to an optimal solution on my own, only detail would be cleanliness of code and the elegance of the solution, which can be improved with practice and review of optimal solution.

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // I will remove one element at the nth-position from the list.

        // This is a dummy node that is used to hold the head. This is very useful since it also helps handle edge cases like eliminating the head.
        // Also since it is created within the function, it will be automatically deallocated once we return from the function, thus there is no memory leak or loss of data, since all the nodes that were part of the original list are still accessible through the modified list that starts at dummy->next.
        ListNode dummy(0);
        dummy.next = head;
        // Here I made use of various assisting pointers to keep track of the current node, the previous node, and a fast pointer to find the nth node from the end.
        // While the time solution is still optimal, there is room to improve also the use of pointers and the cleanliness of the code, which can be achieved with practice and review of optimal solution.
        ListNode* temp;
        ListNode* prev = &dummy;
        ListNode* current = head;
        ListNode* fast = head;
        // n = 2
        // dummy-> 1 -> 2 -> 3 -> 4 

        // We let the fast pointer get ahead by n positions, this way when we start moving both fast and current pointers, the fast pointer will reach the end of the list when the current pointer is at the nth node from the end, which is the one we want to remove.
        while(n > 0){
            // n = 1
            // fast = -> 2
            // n = 0
            // fast -> 3

            n--;
            fast = fast->next;
        }

        // slow = 1
        // fast = 3
        // slow = 2
        // fast = 4
        // slow = 3
        // fast = nullptr

        // We move fast pointer nutil it reaches the end of the list as well as prev and current.
        while(fast != nullptr){
            prev = prev->next;
            current = current->next;
            fast = fast->next;
            cout << "Prev Val:" << prev->val << endl;
            cout << "Curr Val:" << current->val << endl;
            cout << "===== NEXT ====" << endl;
        }

        /*
            This commented piece of code is the one I had made before fully understanding the problem.
            This while loop finds the nth element starting from the beginning of the list, which is not what we want, but it was a good attempt and shows that I was on the right track in terms of using pointers to traverse the list, just needed to adjust the logic to find the nth element from the end instead of from the start.
        */

        /*
        while(n > 1){
            n--;
            // n = 2
            // 1 -> 2
            // n = 1 
            // 2 -> 3
            prev = prev->next;
            current = current->next;
            cout << "Prev Val:" << prev->val << endl;
            cout << "Curr Val:" << current->val << endl;
            cout << "===== NEXT ====" << endl;
        }
        */
        // dummy -> 1
        // temp = nullptr
        // dummy->next = 

        // Once we have reached the end with the fast pointer, the current pointer will be at the nth node from the end, which is the one we want to remove. We just need to adjust the pointers to skip the current node and thus remove it from the list.
        temp = current->next;
        prev->next = temp;

        // And thanks to dummy node, we can just return dummy->next as the head of the modified list, since dummy is just a placeholder and the actual head of the modified list is the next item after dummy.
        return dummy.next;
    }
};
```

Is it optimal? Yes, time complexity is O(n) since we traverse the list technically just once with the fast pointer, the current pointer just following behind, and the prev pointer just following the current pointer. Space could be considered O(1) since we only use constant space of extra pointers. But still there is room for improvement in the cleanliness of the code and the elegance of the solution, which can be achieved with practice and review of optimal solution.

### Optimal solution
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Dummy node to handle edge cases such as removing the head of the list. As well as being able to easily turn the head of the list.
        ListNode* dummy = new ListNode(0, head);
        // Node that will traverse the list a little after right. Notice how left begins in the dummy node, this is important since it allows us to easily handle edge cases such as removing the head of the list, since if we start left at head, we would have trouble removing the head since we would lose access to the rest of the list. By starting at dummy, we always have access to the head of the list through dummy->next, thus we can easily remove the head if needed.
        ListNode* left = dummy;
        // Node that will skip to n node ahead of left.
        ListNode* right = head;

        // We exhaust the n value to move the right pointer n nodes ahead.
        while (n > 0) {
            right = right->next;
            n--;
        }

        // Now we also move the left pointer together with the right. Since right had already moved n positions when it reaches the end of the list the left pointer will be at the node just before the one we want to remove, which is perfect since we just need to adjust its next pointer to skip the node we want to remove.
        while (right != nullptr) {
            left = left->next;
            right = right->next;
        }

        // We change the next pointer of the left node to instead go to the node after the next one, thus skipping the next node and effectively removing it from the list.
        // We can assing left-> next to left->next->next without the risk of trying to reach the next of a null pointer since with the help of the dummy node as well as the right node always making sure we at least have n nodes ahead, we are guaranteed to have a valid next node to skip to.
        left->next = left->next->next;
        // We use the dummy to return the head of the modified list.
        return dummy->next;
    }
};
```

# Up Next

This section is just for taking notes of a problem that I plan to solve in the future, brainstorming their solutions with no code, and then solving them when I feel ready.

## Two Sum

In this problem we have an array of integers and a target number, we need to find the indices of the two numbers that add up to the target.
We can assume there will always be a solution.

Maybe dynamic programming can be useful? Substracting the value from the target and using it for lookup in the array? If the key ends up yielding a value we can assume it exists in the array.

## Group Anagrams
We have an array of words and we need to group the ones that are anagrams together.
Wen can assume even blank strings can be present in the array, and that all inputs will be in lowercase.

While we can use the same approach as in "Is Anagram" problem, we still have the issue of comparing the hash maps.
For this I'm thiknig of using another hashing approach. If their hashes are the same, they will collide in the new hash map, and we can just return the values of the new hash map as the result.


## Trapping Rain Water
The problem consists of an array of heights. We have to determine how much rain water can be trapped in between heights. The edges of the array do not trap water.

What we can do is have one of our pointers take the lead and find a first height and hand it to the other pointer. Then it will continue until it finds a height equal or higher. As it is exploring it can store how much water could be theoretically be stored if we assume an equal height at first.

First height -> The pointer behind
Second height -> The pointer in front

Onece the first height has been the defined the pointer up front continues moving in the array. Adding to the result the difference between the first height and current height. This addition is assuming the second height will be the same or bigger. If, it indeed is we can just add the calculation to our total. If not, then we need to considered the distance between heights (base of the rectangle to be taken away from the count) and the diffeence of heights (height of the rectangle to be taken away from the count). This way we can calculate the amount of water that can be trapped between the two heights.

Essentially we are optimistically assuming that the second height will be the same as the first one, and we keep adding to the count until we find a height that is equal or higher than the first one. If we find a height that is lower, we need to take away the water that would actually NOT be trapped due to the second height being lower than the first one. This is done by calculating the area of the rectangle that would be formed by the distance between the two heights and the difference in height between the first height and the current height. We need to take away this area from our count since it represents the water that would not be trapped due to the second height being lower than the first one.

As always this is speculation that will be proven right or wrong when actually tackling the problem.