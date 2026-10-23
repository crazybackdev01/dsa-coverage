struct ListNode
{
    int val;
    ListNode *next;
};

ListNode *reverseLinkedList(ListNode *head)
{
    if (head == nullptr)
    {
        return head;
    }

    ListNode *curr = head;
    ListNode *prev = nullptr;

    while (curr != nullptr)
    {
        ListNode *nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    return prev;
}

ListNode *middleOfLL(ListNode *head)
{
}
