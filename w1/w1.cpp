/*
Write a program where:

- struct node: represents a node in linkedlists

- functions createLinkedList:

    + Receive the size of a linked list (>0)
    + create a linked list with value from standard input (stdin) a new node is add to the  END  of the linked list
    + Return a pointer which points to the first node of the linked list.

- Function isEqual compare two linked list:

   + Receive the pointer head1 of the 1st linked list , pointer head2 of the 2nd linked list

   + Return true if and only if 2 the linked lists have indentical size, and node value. Otherwise, return false.


- Function main reads the size of the linked list, calls function createLinkedList to Initialize the linked list, then call functdion print to print all the node's values of the linked list.

Complete function createLinkedList, isEqual 

Input: 

The value input from standard input (stdin) with value in (0; 5000)
*/

#include <iostream>
using namespace std;
struct node
{
    int data;
    node *next;
};
node *createLinkedList(int n)
{
    // TO DO
    node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        node *temp = new node();
        cin >> temp->data;
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
        }
        else
        {
        node *tmp = head;
        while (tmp->next != NULL)
            tmp = tmp->next;
            tmp->next = temp;
        }
    }
    return head;
}

bool isEqual(node *head1, node *head2)
{
    // TO DO
    node *tmp1 = head1;
    node *tmp2 = head2;
    int size1 = 0, size2 = 0;
    while(tmp1 != NULL || tmp2 != NULL)
    {
        tmp1 = tmp1->next;
        size1++;
        tmp2 = tmp2->next;
        size2++;
    }
    
    if(size1 == size2)
    {
        tmp1 = head1;
        tmp2 = head2;
        while(tmp1 != NULL && tmp2 != NULL)
        {
            if(tmp1->data != tmp2->data)
                return false;
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
    }
    return true;
}

int main()
{
    int n = 0;
    cin >> n;
    node *head1 = createLinkedList(n);
    node *tmp = head1;
    while (tmp != NULL)
    {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    int m = 0;
    cin >> m;
    node *head2 = createLinkedList(m);
    node *tmp1 = head2;
    while (tmp1 != NULL)
    {
        cout << tmp1->data << " ";
        tmp1 = tmp1->next;
    }

    cout << "------------------"<<endl;
    cout << isEqual(head1, head2) << endl;
    return 0;
}
