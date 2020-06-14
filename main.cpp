//
// Created by Simon Aronsky on 5/21/20.
//

#include "RedBlack.cpp"
#include "Twothreefour.cpp"
#include <chrono>
#include <fstream>
#include <iostream>

int main() {
  fstream fin;
  fin.open("B_Tree_Input.txt",
           ios::in);
  fstream search;
  search.open("B_Tree_Searches.txt",
              ios::in);
  RedBlack redBlack;
  int rBTime = 0;
  int tTFTime = 0;
  int total = 0;
  Twothreefour twothreefour;
  while (fin.good()) {
    int newData;
    fin >> newData;
    rBTime += redBlack.add(newData);
    tTFTime += twothreefour.add(newData);
    total++;
  }
  cout << "The Red Black Tree took " << rBTime << " ns to add " << total
       << " numbers" << endl;
  cout << "The Two Three Four Tree took " << tTFTime << " ns to add " << total
       << " numbers" << endl
       << endl;

  total = 0;
  rBTime = 0;
  tTFTime = 0;
  while (search.good()) {
    total++;
    int newData;
    search >> newData;
    auto start = chrono::high_resolution_clock::now();
    bool rB = redBlack.search(newData, redBlack.root);
    auto end = chrono::high_resolution_clock::now();
    int diff = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    if (!rB)
      cout << newData << " was not found in the Red Black Tree in " << diff
           << " ns" << endl;
    else
      cout << newData << " was found in the Red Black Tree in " << diff << " ns"
           << endl;
    rBTime += diff;
    start = chrono::high_resolution_clock::now();
    bool tTF = twothreefour.search(newData, twothreefour.root);
    end = chrono::high_resolution_clock::now();
    diff = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    if (!tTF)
      cout << newData << " was not found in the Two Three Four Tree in " << diff
           << " ns" << endl
           << endl;
    else
      cout << newData << " was found in the Two Three Four Tree in " << diff
           << " ns" << endl
           << endl;
    tTFTime += diff;
  }
  cout << "The Red Black Tree found each item in " << rBTime / total
       << " ns on average" << endl;
  cout << "The Two Three Four Tree found each item in " << tTFTime / total
       << " ns on average" << endl;
  return 0;
}
