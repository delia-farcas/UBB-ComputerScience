#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

//BC = WC = Theta(1)
SortedIndexedList::SortedIndexedList(Relation r) {
	root = nullptr;
	rel = r;
	listSize = 0;
}

//BC = WC = Theta(1)
int SortedIndexedList::size() const {
	return this->listSize;
}

//BC = WC = Theta(1)
bool SortedIndexedList::isEmpty() const {
	return this->listSize == 0;
}

//BC = WC = Theta(n)
void SortedIndexedList::inOrderTraversal(BSTNode* node, TComp* arr, int& index) const {
	if (node != nullptr) {
		inOrderTraversal(node->left, arr, index);
		arr[index++] = node->data;
		inOrderTraversal(node->right, arr, index);
	}
}

//BC = WC = Theta(n)
TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >= listSize) {
		throw exception();
	}

	TComp* arr = new TComp[listSize];
	int index = 0;
	inOrderTraversal(root, arr, index);

	TComp result = arr[i];
	delete[] arr;
	return result;
	
}

//Bc = Theata(1), Wc = Theta(n), Total = O(n)
BSTNode* SortedIndexedList::insertRec(BSTNode* node, TComp e) {
	if (node == nullptr) {
		return new BSTNode(e);
	}

	if (rel(e, node->data)) {
		node->left = insertRec(node->left, e);
	}
	else {
		node->right = insertRec(node->right, e);
	}

	return node;
}

//Bc = Theata(1), Wc = Theta(n), Total = O(n)
void SortedIndexedList::add(TComp e) {
	root = insertRec(root, e);
	listSize++;
}

//Bc = Theata(1), Wc = Theta(n), Total = O(n)
BSTNode* SortedIndexedList::findMin(BSTNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

//BC = THETA(1) WC = Theta(n), Total = O(n)
BSTNode* SortedIndexedList::removeRec(BSTNode* node, TComp e, bool& found) {
    if (node == nullptr) {
        found = false;
        return nullptr;
    }

    if (e == node->data) {
        found = true;

        //No children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        // One child
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        // Two children
        BSTNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = removeRec(node->right, successor->data, found);
        found = true;
        return node;
    }

    if (rel(e, node->data)) {
        node->left = removeRec(node->left, e, found);
    }
    else {
        node->right = removeRec(node->right, e, found);
    }

    return node;
}

//BC = THETA(1) WC = Theta(n), Total = O(n)
TComp SortedIndexedList::remove(int pos) {
    if (pos < 0 || pos >= listSize) {
        throw exception();
    }

    TComp element = getElement(pos);
    bool found = false;
    root = removeRec(root, element, found);

    if (found) {
        listSize--;
    }

    return element;
}

//BC = WC = Theta(n)
int SortedIndexedList::search(TComp e) const {
    // Find position using in-order traversal
    TComp* arr = new TComp[listSize];
    int index = 0;
    inOrderTraversal(root, arr, index);

    for (int i = 0; i < listSize; i++) {
        if (arr[i] == e) {
            delete[] arr;
            return i;
        }
    }

    delete[] arr;
    return -1;
}

//BC = WC = Theta(1)
ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}


//Bc = WC = Theta(n)
void SortedIndexedList::destroyTree(BSTNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

//BC = WC = Theta(n)
int SortedIndexedList::removeAll(SortedIndexedList& list) {
    int removed = 0;
    ListIterator list_iterator = list.iterator();
    list_iterator.first();
    while (list_iterator.valid()) {
        bool found = false;
        root = removeRec(root, list_iterator.getCurrent(), found);
        if (found == true)
            removed++;
        list_iterator.next();
    }
    listSize -= removed;
    return removed;
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
    destroyTree(root);
}
