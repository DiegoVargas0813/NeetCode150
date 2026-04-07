#include <stack>
#include <iostream>

using namespace::std;

class MinStack {
public:
    int min;
    stack<int> minStack;
    stack<int> mins;

    MinStack() {
        min = INT_MAX;
    }
    
    void push(int val) {
        if(val <= min){
            min = val;
            mins.push(val);
        }
        minStack.push(val);
    }
    
    void pop() {
        if(minStack.top() == mins.top()){
            mins.pop();
            if(!mins.empty()){
                min = mins.top();
            } else {
                min = INT_MAX;
            }
        }
        minStack.pop();
        
    }
    
    int top() {
        return minStack.top();
    }
    
    int getMin() {
        return min;
    }
};

int main(){
    MinStack m;
    m.push(10);
    m.pop();
    m.push(20);
    cout << m.top() << endl;
    m.push(-20);
    cout << m.getMin()<< endl;

    return 0;
}