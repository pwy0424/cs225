/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
	// Call recursive helper function on root
	return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL)
        return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	 mirror_helper(root);  //call helper function with root;
}



template <typename T>  
void BinaryTree<T>::mirror_helper(Node *input)
{
         if(input!=NULL) {
              Node* right=input->right;  
              input->right=input->left;
              input->left=right;        
              mirror_helper(input->left);     
              mirror_helper(input->right);    
         }
}
/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    return isOrdered_helper(root); // Stub: Your code here
}


template <typename T>
bool BinaryTree<T>::isOrdered_helper(Node *input)  const
{

    bool a,b = 0;

    if (input == NULL) return true;
    
    Node* iop = input->left;
    Node* ios  = input->right;

    if(ios !=NULL){
       while(ios ->left!=NULL)
        {ios = ios ->left;}
    }

    if(iop!=NULL){
       while(iop->right!=NULL)
        { iop = iop->right;}
    }

    if(iop==NULL) 
	a = 1;
    	else if((iop->elem) <= (input->elem))
             a = isOrdered_helper(input->left);
    if(ios == NULL) 
	b = 1; 
    	else  if((ios ->elem) >= (input->elem))
             b = isOrdered_helper(input->right);
    
    return(a&&b);
}


/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    vector<int> result;
	 printPaths_helper(root, result);
}


template <typename T>
void BinaryTree<T>::printPaths_helper(Node * input, vector<int> temp) const
{
        bool null = 0;
        if (input == NULL) 
		return;
	else temp.push_back(input->elem);
	if(input->left == NULL && input->right == NULL)
	 	null = true;
	if (null){
          	 cout<<"Path:";
	  	 typename vector<T>::iterator iter;	
	   	 for(iter = temp.begin(); iter < temp.end(); iter++) 
			cout << " " << *iter;  cout << endl;
          	 return;}	
	printPaths_helper(input->left, temp);
	printPaths_helper(input->right, temp);
}

/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
        return sumDistances_helper(root, 0);
}



template <typename T>
int BinaryTree<T>::sumDistances_helper(Node * input, int temp) const
{
	if (input == NULL) 
	     return 0;
        int temp_left, temp_right;
	temp_left = sumDistances_helper(input->left, temp + 1);
        temp_right = sumDistances_helper(input->right , temp + 1);
        return temp + temp_left + temp_right;
}

