//
// Created by Simon Aronsky on 5/21/20.
//

#include "RedBlack.h"
#include <chrono>

using namespace std;

shared_ptr<RedBlack::Node>
RedBlack::addRecursive(int data,
                       shared_ptr<Node> node) { // adds nodes to the tree
  if (data < node->getData()) {
    if (node->getLeftChildPtr() == nullptr) {
      auto returns = make_shared<Node>(data, node);
      node->setLeftChildPtr(returns);
      return node->getLeftChildPtr();
    } else
      return addRecursive(data, node->getLeftChildPtr());
  } else if (data > node->getData()) {
    if (node->getRightChildPtr() == nullptr) {
      auto returns = make_shared<Node>(data, node);
      node->setRightChildPtr(returns);
      return node->getRightChildPtr();
    } else
      return addRecursive(data, node->getRightChildPtr());
  }
  return nullptr;
}
int RedBlack::add(int data) {                        // adds nodes to the tree
  auto start = chrono::high_resolution_clock::now(); // timing
  if (root == nullptr)
    root = make_shared<Node>(data, Node::Color::black);
  else
    correctColor(addRecursive(data, root));
  auto end = chrono::high_resolution_clock::now();
  int diff = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  return (diff);
}
void RedBlack::correctColor(
    shared_ptr<Node> node) { // corrects color of a node, using
                             // standard Red Black Tree algorithm
  if (node != nullptr && node != root &&
      node->getColor() == RedBlack::Node::Color::red &&
      node->getParentPtr()->getColor() == RedBlack::Node::Color::red) {
    shared_ptr<Node> parent = node->getParentPtr();
    shared_ptr<Node> gParent = parent->getParentPtr();
    shared_ptr<Node> uncle = nullptr;
    if (gParent->getRightChildPtr() == parent)
      uncle = gParent->getLeftChildPtr();
    else if (gParent->getLeftChildPtr() == parent)
      uncle = gParent->getRightChildPtr();
    if (uncle == nullptr || uncle->getColor() == RedBlack::Node::Color::black) {
      if (gParent->getLeftChildPtr() == parent &&
          parent->getLeftChildPtr() == node) { // left left
        rotateRight(gParent);
        RedBlack::Node::Color temp = gParent->getColor();
        gParent->setColor(parent->getColor());
        parent->setColor(temp);
      } else if (gParent->getLeftChildPtr() == parent &&
                 parent->getRightChildPtr() == node) { // left right
        rotateLeft(parent);
        correctColor(parent);
      } else if (gParent->getRightChildPtr() == parent &&
                 parent->getRightChildPtr() == node) {
        rotateLeft(gParent);
        RedBlack::Node::Color temp = gParent->getColor();
        gParent->setColor(parent->getColor());
        parent->setColor(temp);
      } else if (gParent->getRightChildPtr() == parent &&
                 parent->getLeftChildPtr() == node) {
        rotateRight(parent);
        correctColor(parent); // CHECK
      }
    } else if (uncle->getColor() == RedBlack::Node::Color::red) {
      parent->setColor(RedBlack::Node::Color::black);
      uncle->setColor(RedBlack::Node::Color::black);
      if (gParent != root)
        gParent->setColor(RedBlack::Node::Color::red);
      else
        gParent->setColor(RedBlack::Node::Color::black);
      correctColor(gParent);
    }
  }
}
bool RedBlack::rotateLeft(shared_ptr<Node> node) {
  if (node->getRightChildPtr() == nullptr)
    return false;
  shared_ptr<Node> t4 = node->getRightChildPtr()->getLeftChildPtr();
  node->getRightChildPtr()->setLeftChildPtr(node);
  if (node != root) {
    node->getRightChildPtr()->setParentPtr(node->getParentPtr());
    if (node->getParentPtr()->getLeftChildPtr() == node)
      node->getParentPtr()->setLeftChildPtr(node->getRightChildPtr());
    else if (node->getParentPtr()->getRightChildPtr() == node)
      node->getParentPtr()->setRightChildPtr(node->getRightChildPtr());
  } else {
    node->getRightChildPtr()->setParentPtr(nullptr);
    root = node->getRightChildPtr();
  }
  node->setParentPtr(node->getRightChildPtr());
  node->setRightChildPtr(t4);
  if (t4 != nullptr)
    t4->setParentPtr(node);
  return true;
}
bool RedBlack::rotateRight(shared_ptr<Node> node) {
  if (node->getLeftChildPtr() == nullptr)
    return false;
  shared_ptr<Node> t4 = node->getLeftChildPtr()->getRightChildPtr();
  node->getLeftChildPtr()->setRightChildPtr(node);
  if (node != root) {
    node->getLeftChildPtr()->setParentPtr(node->getParentPtr());
    if (node->getParentPtr()->getLeftChildPtr() == node)
      node->getParentPtr()->setLeftChildPtr(node->getLeftChildPtr());
    else if (node->getParentPtr()->getRightChildPtr() == node)
      node->getParentPtr()->setRightChildPtr(node->getLeftChildPtr());
  } else {
    node->getLeftChildPtr()->setParentPtr(nullptr);
    root = node->getLeftChildPtr();
  }
  node->setParentPtr(node->getLeftChildPtr());
  node->setLeftChildPtr(t4);
  if (t4 != nullptr)
    t4->setParentPtr(node);
  return true;
}

bool RedBlack::search(int data, shared_ptr<Node> node) {
  if (node == nullptr)
    return false;
  else if (node->getData() == data)
    return true;
  else if (data < node->getData())
    return search(data, node->getLeftChildPtr());
  else if (data > node->getData())
    return search(data, node->getRightChildPtr());
}
