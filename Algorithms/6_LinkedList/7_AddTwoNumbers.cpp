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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // We add the 2 items of the result nodes.
        // We have to build a new linked list.
        // There is a final edge case of having last remainder.

        cout << "Declarations" << endl;
        ListNode* dummy = new ListNode(0);
        ListNode* result = new ListNode(0);

        dummy->next = result;

        int remainder = 0;
        // 9 + 9
        // if (sum <= 10)
        // remainder++;
        // sum - 10;


        while(l1->next != nullptr){
            // 5 -> 0
            // 5 -> 7 -> 0
            // 5 -> 7

            int sum = l1->val + l2->val + remainder;
            remainder = 0;
            if(sum >= 10){
                remainder++;
                sum -= 10;
            }
            result->val = sum;
            cout << result->val << endl;
            result->next = new ListNode(0);
            result = result->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        int sum = l1->val + l2->val + remainder;
        // final case
        if(sum >= 10){
            sum -= 10;
            result->val = sum;
            result->next = new ListNode(1);
        } else {
            result->val = sum;
        }
        cout << result->val << endl;
        return dummy->next;
    }
};

int main(){
    ListNode firstthird(3);
    ListNode firstsecond(2, &firstthird );
    ListNode firstfirst(1, &firstsecond);

    ListNode secondthird(6);
    ListNode secondsecond(5, &secondthird);
    ListNode secondfirst(4, & secondsecond);

    Solution solver;

    solver.addTwoNumbers(&firstfirst, &secondfirst);

    return 0;
}
