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

template <typename K, typename V> V LinkedBST<K, V>::findInSubtree(LinkedBSTNode<K, V>* current, K key) {

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

template <typename K, typename V> bool LinkedBST<K, V>::containsInSubtree(LinkedBSTNode<K, V>* current, K key) {

  //if tree has no contents, can't find. or if you hit a leaf with no children.
  if (current == nullptr) {
      return false;
  }

  //if the root is the key you are looking for, the subtree contains the root, thus it's true
  else if (key == current->getKey()) {
    return true;
  }

  //go left if less.
  else if (key < current->getKey()) {
     this->containsInSubtree(current->getLeft(), key); //change pointer of current to check the value to the left of the root.
  }

  //go right if more.
  else if (key > current->getKey()) {
     this->containsInSubtree(current->getRight(), key); //change pointer of current to check the value to the left of the root.
  }
  return true;
}

template <typename K, typename V>
void LinkedBST<K, V>::updateInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {

  //if tree has no contents, can't update anything. or if you go past the leaf. it means the key doesn't exist.
  if (current == nullptr) {
      throw runtime_error("Key not found: LinkedBST<K,V>::updateInSubtree");
  }

  //if the root is the key you are looking for, the subtree contains the root, thus it's true
  else if (key == current->getKey()) {
    current->setValue(value); //update they key's value since you found it.
  }

  else if (key < current->getKey()) {
    this->updateInSubtree(current->getLeft(), key, value); //change pointer of current to check the value to the left of the root.
  }

  //keep going on the right hand side untl you get to a child of a leaf that's a nullptr.
  else if (key > current->getKey()) {
    this->updateInSubtree(current->getRight(), key, value); //change pointer of current to check the value to the right of the root.
  }

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
  //we only ever have to go left given BST properties. NEVER check the right.
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
LinkedBSTNode<K, V>* LinkedBST<K, V>::insertInSubtree(LinkedBSTNode<K, V>* current, K key, V value) {

  //creates a node with the parameters.


  if (current==nullptr){
    LinkedBSTNode<K, V>* node_toinsert = new LinkedBSTNode<K, V> (key,value);
    current = node_toinsert;
    //return current;
    //this->root = current;
  }

  else if (key < current->getKey()){
    current->setLeft(insertInSubtree(current->getLeft(), key, value));
  }

  else if (key > current->getKey()){
    current->setRight(insertInSubtree(current->getRight(), key, value));
  }

  else if (current->getKey() == key){
    throw runtime_error("key already exists in BST");
  }

  return current;

}

template <typename K, typename V>
LinkedBSTNode<K, V>* LinkedBST<K, V>::removeFromSubtree(LinkedBSTNode<K, V>* current, K key) {
  throw runtime_error(       "Problem in BST: Node count doesn't match tree size");
  //we got beyond a leaf. and the key wasn't found. or the tree is empty.
  // if (current = nullptr){
  //     throw runtime_error("key does not exist in BST");
  // }
  //
  // if (key == current->getKey()){
  //     this->size = this->size - 1;
  //
  //     //OPTION 1: if key to remove is a leaf:
  //     if (current->getLeft() == nullptr) && (current->getRight() == nullptr);{
  //
  //       delete current;  //can simply delete it. //gets rid of 13
  //       return nullptr; //goes back to 12 - DRAW STACK to see where it returns nullptr to.
  //     }
  //
  //    //OPTION 2: if parent with 1 child.
  //    //in or logic, if one is true, it enters.
  //      if (current->getLeft() == nullptr) || (current->getRight() == nullptr);{
  //
  //       LinkedBSTNode<K, V>* child; //need to store store the child
  //       //if child is less than key.
  //       if (current->getLeft() != nullptr){
  //         child = current->getLeft();
  //         delete current; //now we can nix the child's parent wihout worrying about losing the child
  //         return child;
  //       }
  //
  //       //if child is more
  //       else{
  //         child = current->getRight();
  //         delete current; //now we can nix the child's parent without worrying about losing the child.
  //         return child;
//   //       }
//   //     }
//   //
//   //   //OPTION 3: if parent with 2 child. //YIKES!!!!!!!
//   //   if (current->getLeft() != nullptr) && (current->getRight() != nullptr);{
//   //     pair<K, V> temp_pair;
//   //     temp_pair = getMinInSubtree(current->getRight()); //min of right. <35, "35">
//   //
//   //
//   //     updateInSubtree(current, current->getKey(), temp_pair.second); //update value with min of right.
//   //     //update != remove. still needt to nix 35. value of 24 is now gone.
//   //     current->setKey(temp_pair.first); //now update the key.
//   //
//   //     current->setRight(removeFromSubtree(current, temp_pair.first)) //return for removeofSubtree is 36.
//   //     //now we nix the minimum in the right subree
//   //     return current;
//   //       //35 pair.first;  //check if setKey method.
//   //
//   //   }
//
//   }
//
//   //search for the key we want to remove. if less, go left.
//   // else if (key < current->getKey()){
//   //   current->setLeft(removeFromSubtree(current->getLeft(), key)); //update current.
//   //   //DO NOT RETURN because want to look at other subtree exclusively.
//   //   //return for remove is LinkedBSTNode<K, V>*, which is passed into setLeft(takes in pointer).
//   // }
//   //
//   // //search for the key we want to remove. if more, go right.
//   // else if (key > current->getKey()){
//   //   current->setRight(removeFromSubtree(current->getRight(), key)); //update current.
//   // }
//
 }

template <typename K, typename V>
void LinkedBST<K, V>::deleteSubtree(LinkedBSTNode<K, V>* current) {

    throw runtime_error("Not yet implemented: LinkedBST<K,V>::deleteSubtree");

    // if (current == nullptr){
    //   throw runtime_error("BST is empty, nothing to delete");
    // }
    //
    // //delete my child and then delte myself ONCE i no longer have children.
    // else if ((current->getLeft() == nullptr) && (current->getRight() == nullptr)){
    //   delete current->getLeft(); //use g as example. don't need to do this.
    //   delete current->getRight();
    //   delete current;
    //   return ;
    // }
    //
    // else{
    //   deleteSubtree(current->getLeft());
    //   deleteSubtree(current->getRight());
    //
    // }
    // //
    // // while((current->getLeft() != nullptr) && (current->getRight() != nullptr){
    // //
    // //   deleteSubtree(removeFromSubtree(current, current->getKey()));
    // //
    // // }
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPreOrderTraversal(LinkedBSTNode<K, V>* current,
                                             List<pair<K, V>>* list) {

     throw runtime_error("Not yet implemented: LinkedBST<K,V>::deleteSubtree");
    // if (current == nullptr){ //check if we have hit child of a leaf.
    //   return ; //we don't want to do anything. you don't want to add an empty node to the list.
    // }
    //
    // list->insertFirst(current); //traverse to current. then visit.
    // //add F to list. now add B.
    //
    // buildPreOrderTraversal(current->getLeft(), list);
    // buildPreOrderTraversal(current->getRight(), list);


}

template <typename K, typename V>
void LinkedBST<K, V>::buildInOrderTraversal(LinkedBSTNode<K, V>* current,
                                            List<pair<K, V>>* list) {

    if (current == nullptr){ //check if we have hit child of a leaf.
      return ; //we don't want to do anything. you don't want to add an empty node to the list.
    }

    buildPreOrderTraversal(current->getLeft(), list); //add  A to list.
    list.insertFirst(&current); //add F to list.
    buildPreOrderTraversal(current->getRight(), list);
}

template <typename K, typename V>
void LinkedBST<K, V>::buildPostOrderTraversal(LinkedBSTNode<K, V>* current,
                                              List<pair<K, V>>* list) {

    throw runtime_error("Not yet implemented: LinkedBST<K,V>::deleteSubtree");

    // if (current == nullptr){
    //   return ; //we don't want to do anything. you don't want to add an empty node to the list.
    // }
    //
    //
    // buildPreOrderTraversal(current->getLeft(), list); //add  A to list.
    // buildPreOrderTraversal(current->getRight(), list);
    //
    // list->insertFirst(current); //add F to list.


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
