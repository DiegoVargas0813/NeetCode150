#include <iostream>

using namespace::std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // I will remove one element at the nth-position from the list.

        // This is a dummy node that is used to hold the head 
        cout << "Before assign" << endl;
        ListNode dummy(0);
        cout << "Mid Assign" << endl;
        dummy.next = head;
        ListNode* temp;
        ListNode* prev = &dummy;
        ListNode* current = head;
        ListNode* fast = head;
        // n = 2
        // dummy-> 1 -> 2 -> 3 -> 4 

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

        while(fast != nullptr){
            prev = prev->next;
            current = current->next;
            fast = fast->next;
            cout << "Prev Val:" << prev->val << endl;
            cout << "Curr Val:" << current->val << endl;
            cout << "===== NEXT ====" << endl;
        }

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
        temp = current->next;
        prev->next = temp;


        return dummy.next;


    }
};

int main(){
    ListNode fourth(4);
    ListNode third(3, &fourth);
    ListNode second(2, &third);
    ListNode first(5, &second);
    
    Solution solver;

    solver.removeNthFromEnd(&first,1);

    return 0;
}