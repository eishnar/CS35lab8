/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Spring 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/vdxo2w8
*/

// This file contains unit tests for the linkedBST class.
// Most of the unit tests have been provided for you, but you
//  will need to implement unit tests for three linkedBST methods:
//  contains(), getKeys(), and traverseInOrder().
//
// Each of these will have a TO DO: comment below.  Look at the other unit
//  tests for guidance on how to write them.

// NOTE: Be sure to make frequent use of the checkInvariants method
// which verifies that your BST contains the correct number of nodes
// and has properly implemented the BST property.

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <UnitTest++/UnitTest++.h>

#include "adts/BST.h"
#include "adts/list.h"
#include "linkedBST.h"
#include "linkedBSTNode.h"

using namespace std;

/**
 * This helper function will build a small BST on which we can perform
 * experiments.  We can call the methods of the BST
 * in a specific order to make sure it puts the nodes where we want them
 * (assuming, of course, that the insert and get functions work correctly).
 * Our tree will look like this:
 * @verbatim
 *         6
 *        / \
 *       /   \
 *      2     7
 *     / \     \
 *    1   4     9
 *       /
 *      3
 * @endverbatim
 * @return An example BST.  The caller is responsible for deleting this BST.
 */
LinkedBST<int, string>* makeExampleBST() {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    bst->insert(6, "6");
    bst->insert(2, "2");
    bst->insert(7, "7");
    bst->insert(1, "1");
    bst->insert(4, "4");
    bst->insert(9, "9");
    bst->insert(3, "3");
    bst->checkInvariants();
    return bst;
}

TEST(emptyBST) {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    CHECK_EQUAL(0, bst->getSize());
    CHECK(bst->isEmpty());
    bst->checkInvariants();
    delete bst;
}

TEST(exampleBST) {
    // Since we have to respect the BST interface -- we can't look directly at
    // the BST nodes -- we have to test the example BST to make sure that it
    // behaves like we'd think.  If this test fails, then either the insert or
    // the get method is broken and it's hard to tell which.
    // The upside is that we test both the insert and get functions with this
    // test.
    LinkedBST<int, string>* bst = makeExampleBST();
    for (int i = 1; i <= 9; i++) {
        if (i != 5 && i != 8) {
            CHECK_EQUAL(to_string(i), bst->get(i));
        }
    }
    delete bst;
}

TEST(exampleBSTSize) {
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(7, bst->getSize());
    CHECK(!bst->isEmpty());
    delete bst;
}


// test LinkedBST<K,V>::update
TEST(exampleBSTUpdate) {
  LinkedBST<int, string>* bst = makeExampleBST();
  CHECK_EQUAL("7", bst->get(7));
  CHECK_EQUAL("4", bst->get(4));
  bst->update(7,"77");
  CHECK_EQUAL("77", bst->get(7));
  bst->update(4, "7");
  CHECK_EQUAL("7", bst->get(4));
  bst->checkInvariants();
  delete bst;
}

// test LinkedBST<K,V>::remove
TEST(exampleRemove) {
  LinkedBST<int, string> *bst = makeExampleBST();
  CHECK_EQUAL(7, bst->getSize());
  // check removal of node that has just right child
  bst->remove(7);
  CHECK_EQUAL(6, bst->getSize());
  bst->checkInvariants();

  // check removal of leaf
  bst->remove(9);
  CHECK_EQUAL(5, bst->getSize());
  bst->checkInvariants();

  // check removal of node with just left child
  bst->remove(4);
  CHECK_EQUAL(4, bst->getSize());
  bst->checkInvariants();

  // check removal of node with two children
  bst->remove(2);
  CHECK_EQUAL(3, bst->getSize());
  bst->checkInvariants();

  delete bst;
}


// test LinkedBST<K,V>::getItems
TEST(exampleGetItems) {
  LinkedBST<int, string>* bst = makeExampleBST();
  vector<string> myitems;

  // don't forget to add in expected items
  myitems.push_back("1");
  myitems.push_back("2");
  myitems.push_back("3");
  myitems.push_back("4");
  myitems.push_back("6");
  myitems.push_back("7");
  myitems.push_back("9");

  vector<pair<int, string> > items = bst->getItems();

  CHECK_EQUAL(myitems.size(), items.size());
  if(myitems.size() == items.size()) {
    for(int i=0; i<myitems.size(); i++) {
      int count =0;
      for(int j=0; j<items.size(); j++) {
        if(items[j].second == myitems[i]) {
          count++;
        }
      }
      CHECK_EQUAL(1, count);
    }
  }
  delete bst;
}

// test LinkedBST<K,V>::getHeight
TEST(exampleGetHeight) {
  LinkedBST<int, string>* bst = makeExampleBST();

  CHECK_EQUAL(3, bst->getHeight());
  bst->insert(10, "10");
  bst->insert(11, "11");
  bst->insert(12, "12");
  CHECK_EQUAL(5, bst->getHeight());
  bst->checkInvariants();
  delete bst;
}

// test LinkedBST<K,V>::getMax
TEST(exampleGetMax) {
  LinkedBST<int, string>*bst = makeExampleBST();
  CHECK_EQUAL(9, bst->getMaxKey());
  bst->insert(11, "11");
  CHECK_EQUAL(11, bst->getMaxKey());
  delete bst;
}

// test LinkedBST<K,V>::getMin
TEST(exampleGetMin) {
  LinkedBST<int, string>* bst = makeExampleBST();
  CHECK_EQUAL(1, bst->getMinKey());
  bst->insert(-4, "-4");
  CHECK_EQUAL(-4, bst->getMinKey());

  delete bst;
}

// test LinkedBST<K,V>::traversePreOrder
TEST(examplePreOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traversePreOrder();

    // build vector containing what we the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(9, "9"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}


// test LinkedBST<K,V>::traversePostOrder
TEST(examplePostOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traversePostOrder();

    // build vector containing what we the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(9, "9"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(6, "6"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

// test LinkedBST<K,V>::traverseLevelOrder
TEST(exampleLevelOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traverseLevelOrder();

    // build vector containing what we the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(9, "9"));
    expected.push_back(pair<int, string>(3, "3"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

//test LinkedBST<K,V>::contains
TEST(exampleContains){
  LinkedBST<int, string>* bst = makeExampleBST();

  CHECK_EQUAL(true, bst->contains(9));
  CHECK_EQUAL(false, bst->contains(-9));

  //insert a new key value pair and
  bst->insert(-4, "-4");
  CHECK_EQUAL(8, bst->getHeight());
  bst->checkInvariants();
  CHECK_EQUAL(true, bst->contains(-4));

  //remove a key value pair. then check contains.
  bst->remove(3);
  CHECK_EQUAL(7, bst->getHeight());
  bst->checkInvariants();
  CHECK_EQUAL(false, bst->contains(3));


  delete bst;
}

//test LinkedBST<K,V>::getKeys
TEST(exampleGetKeys){
  LinkedBST<int, string>* bst = makeExampleBST();

  vector<K> all_keys;
  all_keys.push_back(1);
  all_keys.push_back(2);
  all_keys.push_back(3);


  CHECK_EQUAL(all_keys, bst->getKeys())

  delete bst;

}

//test LinkedBST<K,V>::traverseInOrder
TEST(exampleInOrderTraversal){
  LinkedBST<int, string>* bst = makeExampleBST();
  vector<pair<int, string>> traversal = bst->traverseInOrder();

  //order of keys is changed.
  vector<pair<int, string>> expected;
  expected.push_back(pair<int, string>(1, "1"));
  expected.push_back(pair<int, string>(2, "2"));
  expected.push_back(pair<int, string>(3, "3"));
  expected.push_back(pair<int, string>(4, "4"));
  expected.push_back(pair<int, string>(6, "6"));
  expected.push_back(pair<int, string>(7, "7"));
  expected.push_back(pair<int, string>(9, "9"));
  REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
  for (int i = 0; i < expected.size(); i++) {
      CHECK_EQUAL(expected[i].first, traversal[i].first);
      CHECK_EQUAL(expected[i].second, traversal[i].second);
  }

  delete bst;

}

int main() {
    return UnitTest::RunAllTests();
}
