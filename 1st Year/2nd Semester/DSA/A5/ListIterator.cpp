#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

//BC = WC = Theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    currentNode = nullptr;
    first();
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
BSTNode* ListIterator::findLeftmost(BSTNode* node) {
    if (node == nullptr) return nullptr;

    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
BSTNode* ListIterator::findSuccessor(BSTNode* node) {
    if (node == nullptr) return nullptr;

    if (node->right != nullptr) {
        return findLeftmost(node->right);
    }

    BSTNode* successor = nullptr;
    BSTNode* current = list.root;

    while (current != nullptr) {
        if (node->data == current->data && node == current) {
            break;
        }

        if (list.rel(node->data, current->data)) {
            successor = current;
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return successor;
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
void ListIterator::first() {
    currentNode = findLeftmost(list.root);
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
void ListIterator::next() {
    if (!valid()) {
        throw exception();
    }

    currentNode = findSuccessor(currentNode);
}

//BC = WC = Theta(1)
bool ListIterator::valid() const {
    return currentNode != nullptr;
}

//BC = WC = Theta(1)
TComp ListIterator::getCurrent() const {
    if (!valid()) {
        return NULL_TCOMP;
    }
    return currentNode->data;
}