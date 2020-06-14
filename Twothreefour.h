//
// Created by Simon Aronsky on 5/21/20.
//

#ifndef HOMEWORK4_TWOTHREEFOUR_H
#define HOMEWORK4_TWOTHREEFOUR_H
#pragma once
using namespace std;

class Twothreefour : public enable_shared_from_this<Twothreefour> {
public:
  struct Node : public enable_shared_from_this<Node> {
  private:
    int smallItem;
    int medItem;
    int lgItem;

    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> leftMid = nullptr;
    shared_ptr<Node> rightMid = nullptr;
    shared_ptr<Node> right = nullptr;
    shared_ptr<Node> parent = nullptr;

    Twothreefour *tree = nullptr;

  public:
    Node(int data) : smallItem(data), medItem(data), lgItem(data){};
    Node(int data, Twothreefour *tree)
        : smallItem(data), medItem(data), lgItem(data), tree(tree){};
    Node(int data, shared_ptr<Node> parent)
        : smallItem(data), medItem(data), lgItem(data), parent(parent),
          tree(parent->tree){};
    bool isLeaf() const {
      return left == nullptr && leftMid == nullptr && rightMid == nullptr &&
             right == nullptr;
    }
    bool isFull() { return uniqueCount() == 3; }
    int uniqueCount() {
      int count = 1;
      if (smallItem != medItem)
        count++;
      if (smallItem != lgItem)
        count++;
      return count;
    }

    int getSmallItem() const { return smallItem; }
    int getMedItem() const { return medItem; }
    int getLgItem() const { return lgItem; }

    void setSmallItem(const int &item) { smallItem = item; }
    void setMedItem(const int &item) { medItem = item; }
    void setLargeItem(const int &item) { lgItem = item; }
    void setParent(shared_ptr<Node> parent) { this->parent = parent; }
    void add(const int &item);    // add new item to node
    void remove(const int &item); // remove item from node
    shared_ptr<Node> getLeftChildPtr() const { return left; }
    shared_ptr<Node> getLeftMidChildPtr() const { return leftMid; }
    shared_ptr<Node> getRightMidChildPtr() const { return rightMid; }
    shared_ptr<Node> getRightChildPtr() const { return right; }
    shared_ptr<Node> getParentPtr() const { return parent; }

    void setLeftChildPtr(shared_ptr<Node> leftPtr) {
      left = leftPtr;
      if (leftPtr != nullptr)
        leftPtr->setParent(shared_from_this());
    }
    void setLeftMidChildPtr(shared_ptr<Node> leftMidPtr) {
      leftMid = leftMidPtr;
      if (leftMidPtr != nullptr)
        leftMidPtr->setParent(shared_from_this());
    }
    void setRightMidChildPtr(shared_ptr<Node> rightMidPtr) {
      rightMid = rightMidPtr;
      if (rightMidPtr != nullptr)
        rightMidPtr->setParent(shared_from_this());
    }
    void setRightChildPtr(shared_ptr<Node> rightPtr) {
      right = rightPtr;
      if (rightPtr != nullptr)
        rightPtr->setParent(shared_from_this());
    }
  };
  shared_ptr<Node> root = nullptr;
  void split(shared_ptr<Node> node);
  bool search(int data, shared_ptr<Node> node);
  int add(int data); // add new node to tree
  void addNode(shared_ptr<Node> node, shared_ptr<Node> root);
  void addRecursive(int data, shared_ptr<Node> node);
};
#endif // HOMEWORK4_TWOTHREEFOUR_H
