/*
  Copyright (c) 2020
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Spring 2020
  CPSC 035: Data Structures and Algorithms
  https://tinyurl.com/vdxo2w8
*/

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "adts/list.h"
#include "adts/BST.h"
#include "adts/stlList.h"
#include "linkedBST.h"


// TODO: put #includes here

using namespace std;


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


int main() {


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

  // CHECK_EQUAL(myitems.size(), items.size());
  if(myitems.size() == items.size()) {
    for(int i=0; i<myitems.size(); i++) {
      int count =0;
      for(int j=0; j<items.size(); j++) {
        if(items[j].second == myitems[i]) {
          count++;
        }
      }
      // CHECK_EQUAL(1, count);
    }
  }
  delete bst;

    return 0;
}
