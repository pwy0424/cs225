/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */
#include "list.h"
#include <iostream>
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	ListNode* temp;
	if(head == NULL) return;
	while(head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	head = NULL;
	tail = NULL;
	length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
	length++;
	ListNode* temp = new ListNode(ndata);	
	if(head==NULL)
	{
		head = temp;
		tail = temp;
		tail->next = NULL;
		head->prev = NULL;
	}
	else
	{
		head->prev = temp;
		temp->next = head;
		temp->prev = NULL;
		head = temp;
	}
	temp = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
	length++;
	ListNode* temp = new ListNode(ndata);
	if(head==NULL)
	{
		head = temp;
		tail = temp;
		temp->next = NULL;
		temp->prev = NULL;
	}
	else
	{
		tail->next = temp;
		temp->prev = tail;
		temp->next = NULL;
		tail = temp;
	}
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    /// @todo Graded in MP3.1
	if(startPoint == endPoint) return;
	ListNode* originalhead = startPoint;
	ListNode* originaltail = endPoint;
	ListNode* temp1 = originalhead->prev;
	ListNode* temp2 = originaltail->next;
	ListNode* rightnow = startPoint;
	while(rightnow!=endPoint)
	{
		ListNode* temp = rightnow->next;
		rightnow->next = rightnow->prev;
		rightnow->prev = temp;
		rightnow = rightnow->prev;
	}
	ListNode* newtemp = rightnow->next;
	rightnow->next = rightnow->prev;
	rightnow->prev = newtemp;
	startPoint = originaltail;
	endPoint = originalhead;
	startPoint->prev = temp1;
	endPoint->next = temp2;	
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    /// @todo Graded in MP3.1
	if (head==NULL) return;
	int x = 0;
	if(length%n!=0) x = length/n + 1;
	else x = length/n;
	ListNode* endPoint = head;
	if(x==1) reverse();
	else
	{
		for(int i = n-1; i >= 1; i--) endPoint = endPoint->next;
		reverse(head,endPoint);
		(endPoint->next)->prev = endPoint;
		ListNode* startPoint = endPoint->next;
		endPoint = endPoint->next;
		//cout<<"x"<<endl;
		x--;
		while(x>=2)
		{
			for(int k = n-1; k >= 1; k--) endPoint = endPoint->next;
			reverse(startPoint,endPoint);
			(startPoint->prev)->next = startPoint;
			(endPoint->next)->prev = endPoint;	
			startPoint = endPoint->next;
			endPoint = endPoint->next;
			x--;
		}
		//cout<<"x"<<endl;
		
		reverse(startPoint,tail);
		(startPoint->prev)->next = startPoint;		
	}
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
	if (head == NULL) return;
	ListNode* curr = head;
	ListNode* temp = head->next;
	curr->next = temp->next;
	temp->next->prev = curr;
	tail->next = temp;
	temp->prev = tail;
	temp->next = NULL;
	tail = temp;
	
	while((curr->next->next!=tail)&(curr->next->next!=NULL))
	{
	curr = curr->next;
	temp = curr->next;
	curr->next = temp->next;
	temp->next->prev = curr;
	tail->next = temp;
	temp->prev = tail;
	temp->next = NULL;
	tail = temp;
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	/// @todo Graded in MP3.2
	if (splitPoint == 0)
	{
		start->prev->next = NULL;
		return start;
	}
	return split(start->next,splitPoint-1); // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2
	ListNode* small = NULL;
	ListNode* big = NULL;
	ListNode* result = NULL;
	if (first->data < second->data){
		big = second;
		small = first;
		result = first;
	}
	else{
		big = first;
		small = second;
		result = second;
	}
	//printf("small = %d\n",(*small).data);
	//printf("big = %d\n",(*big).data);
	while(small->next != NULL){
		if (small->next->data < big->data) small = small->next;
		else{
			ListNode * temp = small->next;
			small->next = big;
			big->prev = small;
			small = big;
			big = temp;
		}
	//printf("small = %d\n",(*small).data);
	//printf("big = %d\n",(*big).data);
	}
	small->next = big;
	return result; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
	if (chainLength==1){
		return start;
	}
	else{
		ListNode * h2 = split(start,chainLength/2);
		ListNode * p = mergesort(start,chainLength/2);
		ListNode * q = mergesort(h2,(chainLength-(chainLength/2)));
		return (merge(p,q));
	}
 // change me!
}
