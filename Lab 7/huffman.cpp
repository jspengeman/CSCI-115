/*
 * Leaf node implementation
 */

// Constructor creates a node with a freq, value pair
template <typename T>
LeafNode<T>::LeafNode(const T& val, int freq){ 
	it = val; wgt = freq; 
}

// Returns the leaf nodes weight
template <typename T>
int LeafNode<T>::weight() const {
    return wgt;
}

// Returns the value stored in the LeafNode
template <typename T>
T LeafNode<T>::val() const {
    return it;
}

// Confirms that this is a leaf node
template <typename T>
bool LeafNode<T>::isLeaf() {
    return true;
}

// Over loaded comparison operators
// Needed for leafs and trees
template <typename T>
bool HuffNode<T>::operator< (const HuffNode& opperend) const {
    return (this->weight() < opperend.weight());
}

template <typename T>
bool HuffNode<T>::operator>(const HuffNode& opperend) const {
    return (this->weight() > opperend.weight());
}

/*
 * Internal node implementation
 */

// Constructor that takes in two arguements to create children
template <typename T>
IntlNode<T>::IntlNode(HuffNode<T>* l, HuffNode<T>* r) {
    wgt = l->weight() + r->weight();
    lc = l;
    rc = r;
}

// Basic getter to return the wgt of the IntlNode
template <typename T>
int IntlNode<T>::weight() const {
    return wgt;
}

// Simple flag that returns if it is a leaf or not
template <typename T>
bool IntlNode<T>::isLeaf() {
    return false;
}

// Sets the left child value in the IntlNode object
template <typename T>
void IntlNode<T>::setLeft(HuffNode<T>* b) {
    lc = (HuffNode<T>*)b;
}

// Returns the HuffNode object that is the left child
template <typename T>
HuffNode<T>* IntlNode<T>::left() const {
    return lc;
}

// Simple setter sets the right element of the tree
template <typename T>
void IntlNode<T>::setRight(HuffNode<T>* b) {
    rc = (HuffNode<T>*)b;
}

// Simple getter that returns the right child
template <typename T>
HuffNode<T>* IntlNode<T>::right() const {
    return rc;
}

/*
 * Huffman coding tree implementation
 */

// Constructor that will make a leaf node as the root
// of the tree. Needed for tree of singleton element
template <typename T>
HuffTree<T>::HuffTree(const T& val, int freq) {
    Root = new LeafNode<T> (val, freq);
}

// Constructor that takes in two trees and makes another
// tree out of them with l and r as subtrees
template <typename T>
HuffTree<T>::HuffTree(HuffTree<T>* l, HuffTree<T>* r) {
    Root = new IntlNode<T> (l->root(), r->root());
}

// Basic getter returns the root object
template <typename T>
HuffNode<T>* HuffTree<T>::root() {
    return Root;
}

// Basic getter returns the weight of the root
template <typename T>
int HuffTree<T>::weight() {
    return Root->weight();
}

// Overloaded comparison operators used to compare the
// weights of the trees. Not needed for internal nodes
template <typename T>
bool HuffTree<T>::operator> (HuffTree& opperend) {
    return this->root()->weight() > opperend.root()->weight();
}

template <typename T>
bool HuffTree<T>::operator< (HuffTree& opperend) {
    return this->root()->weight() < opperend.root()->weight();
}


template <typename T>
ostream& operator<< (ostream& os, const HuffTree<T>& tree)
{	
    os << "Tree weight: " << tree.weight();
    return os;
}



// Build huff function pops the two lowest freq of of the list
// then creates a new tree with those two trees as children
// until the heap is of size one then you are done.
HuffTree<char>* buildHuff(HuffTree<char>** TreeArray, int count) {
    heap<HuffTree<char>*, Min>* forest = new heap<HuffTree<char>*, Min> (TreeArray, count, count);
    HuffTree<char> *temp1, *temp2, *temp3 = 0;
    while (forest->size() > 1) {
        temp1 = forest->removefirst();
        temp2 = forest->removefirst();
        temp3 = new HuffTree<char> (temp1, temp2);
        forest->insert(temp3);
        delete temp1;
        delete temp2;
    }
    return temp3;
}
