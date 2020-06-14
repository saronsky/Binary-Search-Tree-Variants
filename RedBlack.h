//
// Created by Simon Aronsky on 5/21/20.
//

#ifndef HOMEWORK4_REDBLACK_H
#define HOMEWORK4_REDBLACK_H
#include <memory>
using namespace std;

class RedBlack {
public:
  struct Node {
  public:
    enum Color { red, black };
    Color getColor() { return color; }
    int getData() { return item; }
    shared_ptr<Node> getLeftChildPtr() { return left; }
    shared_ptr<Node> getRightChildPtr() { return right; }
    shared_ptr<Node> getParentPtr() { return parent; }
    void setLeftChildPtr(shared_ptr<Node> node) { left = node; }
    void setRightChildPtr(shared_ptr<Node> node) { right = node; }
    void setParentPtr(shared_ptr<Node> node) { parent = node; }
    void setColor(const Color &color) { this->color = color; }
    Node(int item) : item(item){};
    Node(int item, Color color) : item(item), color(color){};
    Node(int item, shared_ptr<Node> parent) : item(item), parent(parent){};

  private:
    int item;
    Color color = Color::red;
    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> right = nullptr;
    shared_ptr<Node> parent = nullptr;
  };
  shared_ptr<Node> root = nullptr;
  shared_ptr<Node> addRecursive(int data, shared_ptr<Node> node);
  int add(int data);
  void correctColor(shared_ptr<Node> node);
  bool rotateRight(shared_ptr<Node> node);
  bool rotateLeft(shared_ptr<Node> node);

  bool search(int data, shared_ptr<Node> node);
};
#endif // HOMEWORK4_REDBLACK_H
