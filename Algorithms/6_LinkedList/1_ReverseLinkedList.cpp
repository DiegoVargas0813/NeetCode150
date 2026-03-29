 #include <iostream>

 using namespace::std;
 
 // Definition for singly-linked list.
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


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

int main(){
    ListNode fourth(4);
    ListNode third(3, &fourth);
    ListNode second(2, &third);
    ListNode first(1,&second);

    Solution solver;

    solver.reverseList(&first);
}