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
//#include "LinkedBSTNode.h" //where getleft and getright are.

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

  //if tree has no contents, can't find
  if (current == nullptr) {
      return false;
      //throw runtime_error("Key not found: LinkedBST<K,V>::contains");
  }
  //if the root is the key you are looking for, the subtree contains the root, thus it's true
  else if (key == current->getKey()) {
    return true;
  }

  else if (key < current->getKey()) {
    return this->containsInSubtree(current->getLeft(), key); //change pointer of current to check the value to the left of the root.
    // current = current->getLeft();
    // if (key == current){
    //   return true;
    // }
    // else{
    //   return false;
    // }
  }

  else if (key > current->getKey()) {
    return this->containsInSubtree(current->getRight(), key); //change pointer of current to check the value to the left of the root.

  //   current = current->getRight(); //change pointer of current to check the value to the left of the root.
  //   if (key == current){
  //     return true;
  //   }
  //   else{
  //     return false;
  //   }
  //
  }
}

template <typename K, typename V> void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key,
                                      V value) {

  //if tree has no contents, can't update anything
  if (current == nullptr) {
      throw runtime_error("Key not found: LinkedBST<K,V>::updateInSubtree");
  }

  //if the root is the key you are looking for, the subtree contains the root, thus it's true
  else if (key == current->getKey()) {
    current->setValue(value); //update they key's value since you found it.
  }

  else if (key < current->getKey()) {
    this->updateInSubtree(current->getLeft(), key); //change pointer of current to check the value to the left of the root.
  }

  else if (key > current->getKey()) {
    this->updateInSubtree(current->getRight(), key); //change pointer of current to check the value to the right of the root.
    
    //keep going on the right hand side untl you get to a child of a leaf that's a nullptr.

  //   current = current->getRight();
  //   if (key == current){
  //     current->setValue(value); //update they key's value since you found it.
  //   }
  //   else{
  //     runtime_error("Key not found: LinkedBST<K,V>::updateInSubtree");
  //   }
  //
  // }

}

template <typename K, typename V> int LinkedBST<K, V>::getHeightInSubtree(LinkedBSTNode<K, V>* current) {
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

  pair<K, V> min_pair;

  //we want to stop before we get to a childless leaf/ an empty box.
  //we want to stop there and grab the value of the left most leaf.

  if (current->getLeft() == nullptr) {

      K key = current->getKey();
      V value = current->getValue();
      min_pair = pair<K,V> (key,value);
      return min_pair;

  }

  else {
    return getMinInSubtree(current->getLeft()); //keep going until you have left left most
  }

}

template <typename K, typename V>
pair<K, V> LinkedBST<K, V>::getMaxInSubtree(LinkedBSTNode<K, V>* current) {

  pair<K, V> max_pair;

  //we want to stop before we get to a childless leaf/ an empty box, thus we check if the next thing will be nullptr.
  //we want to stop there and grab the value of the rightmost leaf.
  if (current->getRight() == nullptr) {

      K key = current->getKey();
      V value = current->getValue();
      max_pair = pair<K,V> (key,value);
      return max_pair;

  }

  else {
    return getMaxInSubtree(current->getRight()); //keep going until you have right rightmost
  }


  }

template <typename K, typename V>
LinkedBSTNode<K, V>*
LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {

  // LinkedBSTNode<K, V> node_toinsert = <key, value>; //creates a node with the parameters.
  //
  //
  // if (current->getLeft() == nullptr) && (current->getRight() == nullptr) { //the base case? 
  //   if (current < key){
  //       current->setLeft(node_toinsert*);
  //   }
  //   else{
  //       current->setRight(node_toinsert*);
  //   }
  // }
  //
  // else if (key < current->getKey()){
  //   insertInSubtree(current->getLeft(), key, value); //need to call recursively?
  //   current->setLeft(node_toinsert*);
  // }
  //
  // else if (key > current->getKey()){
  //   current->setRight(node_toinsert*);
  // }
  //
  // Return node_toinsert*;

  throw runtime_error(
      "Not yet implemented: LinkedBST<K,V>::removeFromSubtree");
}

template <typename K, typename V>
LinkedBSTNode<K, V>* LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {
  
  if (current = nullptr){
      throw runtime_error("key does not exist in BST");
  }
  
  
  else if (key < current->getKey()){
    current->setLeft(removeFromSubtree(current->getLeft(), key)); //DO NOT RETURN. why: want to look at other subtree exclusively. 
  }
  
  
  else if (key > current->getKey()){
    current->setRight(removeFromSubtree(current->getRight(), key)); //13 returns nullptr.
    //DO NOT RETURN. why: want to look at other subtree exclusively. 
  }
    
    
  else if (key == current->getKey()){
    if leaf
      (current->getLeft() == nullptr) && (current->getRight() == nullptr); 
      delete current;  //gets rid of 13
      return nullptr; //goes back to 12 - DRAW STACK to see where it returns nullptr to. 
    
    
    if parent with 1 kid. 
      
      //less
    return current->getLeft();
    
      //more
    return current->getRight();

    
    if parent with 2 kids. //YIKES!!!!!!!
   
      (current->getLeft() == nullptr) || (current->getRight() == nullptr);
    
      //max of left. min of right. 
    
      pair = minofsubtree(current->getRight()); 
      updateinsubtree(current, current->getKey(), pair.second); //update != remove. still needt to nix 35. value of 24 is now gone. 
      
      current = removeFromSubtree(current, 35))   //now we nix 35. but use pair.first. 
      current->key = (//35) pair.first;  //check if setKey method. 
      
  return current;         
  
    
    //or delete &current; 
  }
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

  //what i would have done: create an int variable called total. create a left and right.

    if (current == nullptr) {
        return 0;
    } else {
        return this->countNodes(current->getLeft()) + //what if a parent only had a right child, but not a lef
               this->countNodes(current->getRight()) + 1; //how does it know when to stop? how does it know when it hits a leaf?
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
