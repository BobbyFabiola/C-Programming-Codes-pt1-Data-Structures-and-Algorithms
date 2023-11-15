# My-First-Cursor-Based
DSA: Bobby's First Hands-on on Cursor Based


What is Cursor Based for?
    This is an Array List representation of data in Linked List implementation. Wherein, memory management is done manually; think of it more like how you do string function without the string library by manually defining the functions yourself.

0. Initialize
    Sets the list to empty by indicating the head pointer to point to -1(NULL), avail at index zero, all next pointers to the list to point to the next node, and last node points to -1(NULL);
0.1 Insert At Available
    Insert First, Rear, atPos, and Sorted
    If there is still space to insert, allocate space for a node by having temp get the value of avail, update your avail to point to the next node, assign the element to insert into the temp node; no need to worry much about linking since next "pointers" are pre-assigned from initialization.

1. Display List.
    Pass by copy. We pass the head of the list and the entire list itself. Traverse the entire list by only accessing its next pointers. The update for a variable 'i' solely relies on the next index of each node of the list. The list is not in order in terms of the arrangement in nodes. However, they are still contiguous in memory - since this is still represented as an array list.

2. Insert Front.
    Allocate space by declaring temp to get the available node, update the value of avail to point to the next available pointer via temp->next, insert new elem by initializing into temp->data, assign temp->next to what previous head was pointing to, lastly assign the head to point to the new node temp.

3. Insert Rear.
    To insert node at rear, get a hold of previous last node by traversing the list - assign trav to hold previous last node. If there is still space to insert, allocate space for newNode (temp) to get available node, update avail to next available node, insert the element into temp. Since temp will be inserted at rear, simply state its next pointer to -1(NULL), then dereference trav to point to temp - this makes the previous last node pointer next point to temp which is current new node at rear. 

4. Insert At.
    Declare a counter for every time you traverse to insert at given position. Value of counter i is now position to insert, trav is node to point to temp. Allocate space for temp node, udpdate the avail to the next available node currently pointed by temp->next, assign element into temp node, temp->next will get whate trav was pointing to, directly assigning trav to point to temp

5. Insert Sorted.
    Traverse the list until you find an element in the list that is greater than the element to be inserted. Loops until elem is less than the next node, allocate space for node to insert, update value of avail, assign elem into node, temp->next will get the next node that is of greater value than elem, link temp node into list. 

6. Delete Front.
    Assign the first node to temp, to be "deleted". Re-direct the head of the list to point to the node that the first node was pointing to; basically pointing over to the next node or toward the second node. Assign temp->next to point to the previous avail node. Current value of avail will now be temp.

7. Delete Rear.
    Loop to get the second to the last node, basically the node pointing to the node that we are to delete. Assign the very last node to temp, which is now the node that we are to delete. Second to the last node will now point to -1(NULL). Assign the previous avail to temp->next and the new value for the avail will now be temp itself. Finally

8. Delete At.
    Loop to traverse to the position on the node to be deleted. Assign node to delete to temp. Node pointing to temp should now point to the node after temp (*trav->next = temp->next), "pointing-over". Temp pointer next should now point to previous avail, new avail should now be temp itself.  