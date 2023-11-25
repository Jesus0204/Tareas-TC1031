/*
 * main.cpp
 *
 *  Created on: 30/10/2020
 *      Author: clase
 */

#include <iostream>
#include <cstring>
#include "splay.h"

using namespace std;

int main(int argc, char* argv[]) {
  string in_ans = "", pre_ans = "";
  SplayTree<int> my_splay;
  bool found = 0;

  my_splay.add(16);
  my_splay.add(18);
  my_splay.add(20);
  my_splay.add(14);

  found = my_splay.find(20);
  found = my_splay.find(18);

  my_splay.add(15);
  my_splay.add(17);
  my_splay.add(21);
  my_splay.add(22);
  found = my_splay.find(21);
  found = my_splay.find(15);

  // my_splay.add(15);
  // my_splay.add(10);
  // my_splay.add(17);
  // my_splay.add(7);
  // my_splay.add(13);
  // my_splay.add(16);
  // found = my_splay.find(15);
  // found = my_splay.find(13);

  cout << my_splay.print_tree();

  my_splay.remove(16);  //bottom up

  cout << "After Remove: " << endl << endl;

  cout << my_splay.print_tree();
}