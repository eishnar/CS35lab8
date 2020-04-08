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

  this->size = 0;
  this->root = nullptr; //only two data members in the constructor. rest will be pointers to link stuff.
}

template <typename K, typename V> LinkedBST<K, V>::~LinkedBST() {
    if (this->root != nullptr){
      deleteSubtree(this->root);
    }
}

template <typename K, typename V>
int LinkedBST<K, V>::getSize() {

  return this->size;
}

template <typename K, typename V> bool LinkedBST<K, V>::isEmpty() {

  return(this->size==0);
}

template <typename K, typename V> void LinkedBST<K, V>::insert(K key, V value) {

    // LinkedBSTNode<K, V>* node = insertInSubtree(this->root, key, value); //three parameters for insert in private file.
    // this->root = node; //update the root.
    this->root = insertInSubtree(this->root, key, value); //three parameters for insert in the private file.
    this->size += 1;
}

template <typename K, typename V> void LinkedBST<K, V>::update(K key, V value) {
    updateInSubtree(this->root, key, value);
}


template <typename K, typename V>
V LinkedBST<K, V>::get(K key) {

    return this->findInSubtree(this->root, key); //only two parameters

}

template <typename K, typename V> bool LinkedBST<K, V>::contains(K key) {
    return containsInSubtree(this->root, key);

}

template <typename K, typename V> void LinkedBST<K, V>::remove(K key) {
  //LinkedBSTNode<K, V>* new_root;
  this->root = removeFromSubtree(this->root, key);
  this->size -= 1;
}



template <typename K, typename V> vector<K> LinkedBST<K, V>::getKeys() {

  vector<K> keys;
  List<pair<K, V>>* list_param = new STLList<pair<K, V>>; //empty right now, just allocated allocate memory

  buildInOrderTraversal(this->root, list_param); //List<pair<K, V>>* list is second parameter.

  //list_param is now updated, since this funciton is called. it is no longer empty.
  for(int i = 0; i< list_param->getSize(); i++) {
    K temp_key = list_param->get(i).first; //grab the key from the first item in each pair in the list.
    keys.push_back(temp_key);
  }

  return keys; //this return type matches the one the function, getKeys, returns.
  delete list_param;

}

template <typename K, typename V> vector<pair<K, V>> LinkedBST<K, V>::getItems() { //already implemented.
    return this->traverseInOrder();
}

template <typename K, typename V> int LinkedBST<K, V>::getHeight() {

    return this->getHeightInSubtree(this->root);
}

template <typename K, typename V>
K LinkedBST<K, V>::getMaxKey() {

  pair<K, V> max_pair = getMaxInSubtree(this->root);
  return max_pair.first;
}

template <typename K, typename V>
K LinkedBST<K, V>::getMinKey() {

  pair<K, V> min_pair = getMinInSubtree(this->root); //subtree that starts at root is whole tree.
  return min_pair.first;
}

template <typename K, typename V>
vector<pair<K, V>> LinkedBST<K, V>::traversePreOrder() {

  vector<pair<K,V>> pre_traversal;
  List<pair<K, V>>* list_param = new STLList<pair<K, V>>; //empty right now, just allocated some memory

  buildPreOrderTraversal(this->root, list_param); //List<pair<K, V>>* list is second parameter.

  for(int i = 0; i< list_param->getSize(); i++) {
    K temp_key = list_param->get(i).first; //grab the key from the first item in each pair in the list.
    V temp_value = list_param->get(i).second; //grab the value from the first second in each pair in the list.
    pre_traversal.push_back(pair<K, V>(temp_key, temp_value)); //add them both to the list as a pair item.

  }
    return pre_traversal;
    delete list_param;

  }




template <typename K, typename V> vector<pair<K, V>> LinkedBST<K, V>::traverseInOrder() {

  vector<pair<K,V>> inorder_traversal; //initliazes the variable we want to return
  List<pair<K, V>>* list_param = new STLList<pair<K, V>>; //empty right now, just allocated allocate memory

  buildInOrderTraversal(this->root, list_param); //List<pair<K, V>>* list is second parameter.

  for(int i = 0; i< list_param->getSize(); i++) {
    K temp_key = list_param->get(i).first; //grab the key from the first item in each pair in the list.
    V temp_value = list_param->get(i).second; //grab the value from the first second in each pair in the list.
    inorder_traversal.push_back(pair<K, V>(temp_key, temp_value)); //add them both to the list as a pair item.

  }

  return inorder_traversal;

  //delete inorder_traversal;
  delete list_param;

}


template <typename K, typename V> vector<pair<K, V>> LinkedBST<K, V>::traversePostOrder() {

  vector<pair<K,V>> post_traversal;
  List<pair<K, V>>* list_param = new STLList<pair<K, V>>; //empty right now, just allocated allocate memory

  buildPostOrderTraversal(this->root, list_param); //List<pair<K, V>>* list is second parameter.

  for(int i = 0; i< list_param->getSize(); i++) {
    K temp_key = list_param->get(i).first; //grab the key from the first item in each pair in the list.
    V temp_value = list_param->get(i).second; //grab the value from the first second in each pair in the list.
    post_traversal.push_back(pair<K, V>(temp_key, temp_value));
  }

    return post_traversal;

    //delete post_traversal;
    delete list_param; //need a for loop. 
    delete &list_param;


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
        throw runtime_error("Problem in BST: Node count doesn't match tree size");
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
