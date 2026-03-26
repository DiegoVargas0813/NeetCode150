# Arrays and Hashing

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

### Optimal solution
A core concept of this solution is bit manipulation.

Basically in every index of the array we are using the bits of the integer to represent the presence of a number in the row, column or square. For example, if we have the number 3 in a row, we can set the 3rd bit of the integer at that index to 1. This way we can easily check if a number is already present in the row, column or square by checking if the corresponding bit is set to 1.

Example:

row[1] = 0000000000 (initially all bits are 0)
If we have the number 3 in the row, we set the 3rd bit to 1:
row[1] = 0000000100 (now the 3rd bit is set to 1, indicating that the number 3 is present in the row)

Then, if we want to check if the number 3 is already present in the row, we can just check if the 3rd bit is set to 1:

```cpp
// Since 1 in binary is 0000000001, if we left shift it by 3 positions we get 0000000100, which is the bit representation of the number 3. Then we can use a bitwise AND operation to check if that bit is set in the row[1] integer. If the result is not 0, it means that the bit is set and thus the number 3 is already present in the row.
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

                int val = board[r][c] - '1'; // By substracting a char from another char, we get the difference in their ASCII values, which gives us the index of the number in the bitmask. For example, if we have the character '3', by substracting '1' from it, we get 2, which is the index of the bit that represents the number 3 in our bitmask.

                /*
                    SO...

                    We want 3 to be in the third position of a bitmask? Like in other indexes, this would be index 2 since we count from 0.

                    Char '3' has an ASCII value of 51, and char '1' has an ASCII value of 49. So by doing '3' - '1', we get 51 - 49 = 2, which is the index we want to set in our bitmask to represent the presence of the number 3.

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

                    (4 / 3) * 3 + (5 / 3) = (1) * 3 + (1) = 3 + 1 = 4

                    (1 / 3) * 3 + (1 / 3) = (0) * 3 + (0) = 0 + 0 = 0

                    (r / 3) tells us which group of 3 rows we are in. The 3 + (c / 3) tells us which group of 3 columns we are in. By multiplying the row group by 3, we are essentially moving to the correct block of 3 squares, and then by adding the column group, we are moving to the correct square within that block.


                    Take into account the values are integer divisions, so they will be rounded down. Thus what a person would count as square 2, would be indexed as 1 since we start counting from 0. This is a neat way to map the 9 squares of the Sudoku board to indices from 0 to 8 in our squares array.
                
                */
                if ((rows[r] & (1 << val)) || (cols[c] & (1 << val)) ||
                    (squares[(r / 3) * 3 + (c / 3)] & (1 << val))) {
                    return false;
                }

                rows[r] |= (1 << val);
                cols[c] |= (1 << val);
                squares[(r / 3) * 3 + (c / 3)] |= (1 << val);
            }
        }
        return true;
    }
};
```

# Two Pointers

## Valid Palindrome
This problem consist on determining if a string is a palindrome, meaninng it can be read the same from both ways.

### Problems had
1. Issue with capital letters and spaces, had to look up how to ignore them.
2. Need to practice when to subtract one from functions like lenght or size to avoid out of bounds errors.
3. While I had added the i < j condition in the main while loop, I forgot  to add it in the inner while loops, which could cause out of bounds errors or infinite loops.
4. Forgetting to update the pointers at the end of comparison.
5. One very important error I did was the following:
    - Instead of comparing the alphanumeric values like this: (c >= 'A' && c <= 'Z'), I did ('A' <= c <= 'Z'). The  second notation is valid in SOME programming languages but not in C++. Sincer in C++ 'A' <= c is evaluated first which gives a boolean value and then that boolean value is compared to 'Z', which is not the intended logic and can lead to incorrect results. This is a common mistake when trying to compare a character to a range of characters, and it's important to remember that in C++ we need to compare the character to each boundary of the range separately.
    
### Solution
Was able to solve? No, while the core problem was understood. Implementing it gave me trouble. I will try again in a few days to see if the concepts are better understood.

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

### Solution
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

# Stack

## 1. Valid Parentheses
This problem consists on determining if a string of parenthesis is valid, meaning every opening parenthesis has a corresponding closing parenthesis in the correct order.

### Problems had
1. Issues with the insertion and removal of elements in the stack.
2. Good call using a hash map to store possible pairs, but didn't use it to its full potential.

### My Solution
Was able to solve? No, some issues with the stack going out of bounds.

### Optimal solution
My first solution was very close to the optimal one, but only failed due to failure of addressing some edge cases and not using the hash map to its full potential. The optimal solution is cleaner and more efficient since it uses the hash map to store the pairs of parentheses and thus can easily check if the current closing parenthesis matches the last opening parenthesis in the stack.

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