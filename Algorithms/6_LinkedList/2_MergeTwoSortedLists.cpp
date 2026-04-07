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

int main(){
    ListNode list1Third(4);
    ListNode list1Second(2, &list1Third);
    ListNode list1First(1, &list1Second);

    ListNode list2Third(5);
    ListNode list2Second(3, &list2Third);
    ListNode list2First(1, &list2Second);

    Solution solver;

    solver.mergeTwoLists(&list1First, &list2First);

    return 0;
}
