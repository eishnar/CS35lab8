/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Spring 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/vdxo2w8
*/

#include <stdexcept>
#include <utility>

#include "adts/list.h"
#include "adts/stlList.h"

using std::runtime_error;

template <typename K, typename V>
V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {
    //If key not found, throw an error
    if (current == nullptr) {
        throw runtime_error("Key not found: LinkedBST<K,V>::findInSubtree");
    }
    // Found it. Return value
    else if (key == current->getKey()) {
        return current->getValue();
    }
    // If key less, search left subtree
    else if (key < current->getKey()) {
        return this->findInSubtree(current->getLeft(), key);
    }
    // If key greater, search right subtree
    else { //key > current->getKey()
        return this->findInSubtree(current->getRight(), key);
    }
}

template <typename K, typename V>
bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {
    throw runtime_error(
        "Not yet implemented: LinkedBST<K,V>::containsInSubtree");
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key,
                                      V value) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::updateInSubtree");
}

template <typename K, typename V>
int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return -1;
    }

    int left_height = this->getHeightInSubtree(current->getLeft());
    int right_height = this->getHeightInSubtree(current->getRight());

    if (left_height > right_height) {
        return left_height + 1;
    }
    else { //right_height >= left_height
        return right_height +  1;
    }
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMinInSubtree(LinkedBSTNode<K, V>* current) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::getMinInSubtree");
}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::getMaxInSubtree");
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::insertInSubtree");
}

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {
    throw runtime_error(
        "Not yet implemented: LinkedBST<K,V>::removeFromSubtree");
}

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::deleteSubtree");
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current,
                                             List<pair<K, V>>* list) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::buildPreOrder");
}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current,
                                            List<pair<K, V>>* list) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::buildInOrder");
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current,
                                              List<pair<K, V>>* list) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::buildPostOrder");
}

template <typename K, typename V>
int LinkedBST<K, V>::countNodes(LinkedBSTNode<K, V>* current) {
    if (current == nullptr) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) +
               this->countNodes(current->getRight()) + 1;
    }
}

template <typename K, typename V>
void LinkedBST<K, V>::verifyKeysBoundedBy(LinkedBSTNode<K, V>* current,
                                          bool minApplies, K minBound,
                                          bool maxApplies, K maxBound) {
    if (minApplies && current->getKey() < minBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a "
                            "right descendent with lesser key");
    }
    if (maxApplies && current->getKey() > maxBound) {
        throw runtime_error("LinkedBST::verifyKeysBoundedBy: a node has a left "
                            "descendent with greater key");
    }
    if (current->getLeft() != nullptr) {
        verifyKeysBoundedBy(current->getLeft(), minApplies, minBound, true,
                            current->getKey());
    }
    if (current->getRight() != nullptr) {
        verifyKeysBoundedBy(current->getRight(), true, current->getKey(),
                            maxApplies, maxBound);
    }
}
