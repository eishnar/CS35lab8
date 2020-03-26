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
#include <vector>

#include "adts/list.h"
#include "adts/queue.h"
#include "adts/stlList.h"
#include "adts/stlQueue.h"

#include "linkedBSTNode.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinkedBST<K, V>::LinkedBST() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::LinkedBST");
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {
    // To do: implement the destructor
}

template <typename K, typename V> int LinkedBST<K, V>::getSize() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::getSize");
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::isEmpty");
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::insert");
}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::update");
}

template <typename K, typename V> V LinkedBST<K, V>::get(K key) {
    return this->findInSubtree(this->root, key);
}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::contains");
}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::remove");
}

template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::getKeys");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::getItems() {
    return this->traverseInOrder();
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {
    return this->getHeightInSubtree(this->root);
}

template <typename K, typename V> K LinkedBST<K, V>::getMaxKey() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::getMax");
}

template <typename K, typename V> K LinkedBST<K, V>::getMinKey() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::getMin");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {
    throw runtime_error(
        "Not yet implemented: LinkedBST<K,V>::traversePreOrder");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {
    throw runtime_error("Not yet implemented: LinkedBST<K,V>::traverseInOrder");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {
    throw runtime_error(
        "Not yet implemented: LinkedBST<K,V>::traversePostOrder");
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traverseLevelOrder() {
    // Start BFS at root. As nodes are removed from queue, add pairs to vector.
    vector<pair<K,V>> level_traversal;

    // Note, there's no need to deal with finding neighbors or marking visited
    // here. A node's only neighbors that haven't already been visited will be
    // their children.
    if (this->root != nullptr) {
        STLQueue<LinkedBSTNode<K,V>*> search_queue;
        search_queue.enqueue(this->root);
        while (search_queue.getSize() > 0) {
            LinkedBSTNode<K,V>* current = search_queue.dequeue();
            // Add to traversal
            level_traversal.push_back(pair<K,V>(current->getKey(), current->getValue()));
            if (current->getLeft() != nullptr) {
                search_queue.enqueue(current->getLeft());
            }
            if (current->getRight() != nullptr) {
                search_queue.enqueue(current->getRight());
            }
        }
    }

    return level_traversal;
}

template <typename K, typename V> void LinkedBST<K, V>::checkInvariants() {
    if (this->countNodes(this->root) != this->size) {
        throw runtime_error(
            "Problem in BST: Node count doesn't match tree size");
    }
    if (this->root != nullptr) {
        // The bounds provided here are arbitrary because the false arguments
        // indicate that they do not apply.  But we need a value of type K to
        // fill this parameter since we don't have globally min/max K values
        // generically.
        this->verifyKeysBoundedBy(this->root, false, this->root->getKey(),
                                  false, this->root->getKey());
    }
}
