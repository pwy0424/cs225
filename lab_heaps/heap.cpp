/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <iostream>

using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the left child.
    return 2*(currentIdx+1)-1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    return 2*(currentIdx+1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    return (currentIdx+1)/2-1;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child
	int temp = leftChild(currentIdx);
    int size = _elems.size();
    if(temp<size) return true;
    else return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
	int x = 2*(currentIdx+1)-1;
	int y = 2*(currentIdx+1);
	if(higherPriority(_elems[x], _elems[y])) return x;
	else return y;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    /// @todo Implement the heapifyDown algorithm.
	if(hasAChild(currentIdx)){
		int childIdx = maxPriorityChild(currentIdx);
		if (higherPriority(_elems[childIdx],_elems[currentIdx])){
			std::swap(_elems[childIdx],_elems[currentIdx]);
			heapifyDown(childIdx);
		}
	}
     //   return;
	//size_t childIdx = maxPriorityChild(currentIdx);
	//if (higherPriority( _elems[childIdx], _elems[currentIdx])){
	//	std::swap(_elems[childIdx],_elems[currentIdx] );
    //    heapifyDown(childIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
	int size = elems.size();
	//printf("x");
	//cout<<"x"<<endl;
	for (int i = 0; i < size; i++) _elems.push_back(elems[i]);
	//printf("x");
	//cout<<"x"<<endl;
	for (int i = parent(size); i >= 0; i--) heapifyDown(i); 
	//heapifyDown(0);
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    /// @todo Remove, and return, the element with highest priority
    T temp = _elems[0];
	_elems[0] = _elems.back();
	_elems.pop_back();
	heapifyDown(0);
	return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    /// @todo Return, but do not remove, the element with highest priority
    T temp = _elems[0];
	return temp;
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    /// @todo Add elem to the heap
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    /// @todo Determine if the heap is empty
    return _elems.empty();
}
