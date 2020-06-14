//
// Created by Simon Aronsky on 5/21/20.
//

#include "Twothreefour.h"
#include <algorithm>
#include <chrono>

void Twothreefour::addRecursive(int data, shared_ptr<Node> node) {
  if (data < node->getSmallItem()) {
    if (node->getLeftChildPtr() == nullptr) {
      if (node->isFull()) {
        split(node);
        addRecursive(data, node->getParentPtr());
      } else
        node->add(data);
    } else
      addRecursive(data, node->getLeftChildPtr());
  } else if (data > node->getSmallItem() && data < node->getMedItem()) {
    if (node->getLeftMidChildPtr() == nullptr) {
      if (node->isFull()) {
        split(node);
        addRecursive(data, node->getParentPtr());
      } else
        node->add(data);
    } else
      addRecursive(data, node->getLeftMidChildPtr());
  } else if (data > node->getSmallItem() && data < node->getLgItem()) {
    if (node->getRightMidChildPtr() == nullptr) {
      if (node->isFull()) {
        split(node);
        addRecursive(data, node->getParentPtr());
      } else
        node->add(data);
    } else
      addRecursive(data, node->getRightMidChildPtr());
  } else if (data > node->getLgItem()) {
    if (node->getRightChildPtr() == nullptr) {
      if (node->isFull()) {
        split(node);
        addRecursive(data, node->getParentPtr());
      } else
        node->add(data);
    } else
      addRecursive(data, node->getRightChildPtr());
  }
}

void Twothreefour::split(shared_ptr<Node> node) {
  int medVal = node->getMedItem();
  if (node == root) {
    node->setParent(make_shared<Node>(medVal, this));
    root = node->getParentPtr();
    root->setRightChildPtr(node);
    root->setLeftChildPtr(make_shared<Node>(node->getSmallItem(), root));
    root->getLeftChildPtr()->setLeftChildPtr(
        root->getRightChildPtr()->getLeftChildPtr());
    root->getLeftChildPtr()->setRightChildPtr(
        root->getRightChildPtr()->getLeftMidChildPtr());
    root->getRightChildPtr()->setLeftChildPtr(
        root->getRightChildPtr()->getRightMidChildPtr());
    root->getRightChildPtr()->setRightMidChildPtr(nullptr);
    root->getRightChildPtr()->setLeftMidChildPtr(nullptr);
    root->getRightChildPtr()->remove(root->getRightChildPtr()->getSmallItem());
    root->getRightChildPtr()->remove(root->getRightChildPtr()->getMedItem());
  } else {
    if (node->getParentPtr()->isFull())
      split(node->getParentPtr());
    int medVal = node->getMedItem();
    shared_ptr<Node> parent = node->getParentPtr();
    parent->add(medVal);
    node->remove(medVal); // check for change in connections
    if (parent->uniqueCount() == 2) {
      if (parent->getSmallItem() == medVal) {
        parent->setRightMidChildPtr(
            make_shared<Node>(node->getLgItem(), parent));
        parent->getRightMidChildPtr()->setLeftChildPtr(
            node->getRightMidChildPtr());
        parent->getRightMidChildPtr()->setRightChildPtr(
            node->getRightChildPtr());
        node->remove(node->getLgItem());
        node->setRightChildPtr(node->getLeftMidChildPtr());
        node->setLeftMidChildPtr(nullptr);
        node->setRightMidChildPtr(nullptr);
      } else if (parent->getLgItem() == medVal) {
        parent->setRightMidChildPtr(make_shared<Node>(
            parent->getRightChildPtr()->getSmallItem(), parent));
        parent->getRightMidChildPtr()->setLeftChildPtr(
            parent->getRightChildPtr()->getLeftChildPtr());
        parent->getRightMidChildPtr()->setRightChildPtr(
            parent->getRightChildPtr()->getLeftMidChildPtr());
        parent->getRightChildPtr()->setLeftChildPtr(
            parent->getRightChildPtr()->getRightMidChildPtr());
        parent->getRightChildPtr()->setLeftMidChildPtr(nullptr);
        parent->getRightChildPtr()->setRightMidChildPtr(nullptr);
        parent->getRightChildPtr()->remove(
            parent->getRightChildPtr()->getSmallItem());
      }
    } else if (parent->uniqueCount() == 3) {
      if (parent->getSmallItem() == medVal) {
        parent->setLeftMidChildPtr(
            make_shared<Node>(parent->getLeftChildPtr()->getLgItem(), parent));
        parent->getLeftMidChildPtr()->setLeftChildPtr(
            parent->getLeftChildPtr()->getRightMidChildPtr());
        parent->getLeftMidChildPtr()->setRightChildPtr(
            parent->getLeftChildPtr()->getRightChildPtr());
        parent->getLeftChildPtr()->setRightChildPtr(
            parent->getLeftChildPtr()->getLeftMidChildPtr());
        parent->getLeftChildPtr()->setLeftMidChildPtr(nullptr);
        parent->getLeftChildPtr()->setRightMidChildPtr(nullptr);
        parent->getLeftChildPtr()->remove(
            parent->getLeftChildPtr()->getLgItem());
      } else if (parent->getMedItem() == medVal) {
        parent->setLeftMidChildPtr(make_shared<Node>(
            parent->getRightMidChildPtr()->getSmallItem(), parent));
        parent->getLeftMidChildPtr()->setLeftChildPtr(
            parent->getRightMidChildPtr()->getLeftChildPtr());
        parent->getLeftMidChildPtr()->setRightChildPtr(
            parent->getRightMidChildPtr()->getLeftMidChildPtr());
        parent->getRightMidChildPtr()->setLeftChildPtr(
            parent->getRightMidChildPtr()->getRightMidChildPtr());
        parent->getRightMidChildPtr()->setLeftMidChildPtr(nullptr);
        parent->getRightMidChildPtr()->setRightMidChildPtr(nullptr);
        parent->getRightMidChildPtr()->remove(
            parent->getRightMidChildPtr()->getSmallItem());
      } else if (parent->getLgItem() == medVal) {
        parent->setLeftMidChildPtr(parent->getRightMidChildPtr());
        parent->setRightMidChildPtr(make_shared<Node>(
            parent->getRightChildPtr()->getSmallItem(), parent));
        parent->getRightMidChildPtr()->setLeftChildPtr(
            parent->getRightChildPtr()->getLeftChildPtr());
        parent->getRightMidChildPtr()->setRightChildPtr(
            parent->getRightChildPtr()->getLeftMidChildPtr());
        parent->getRightChildPtr()->setLeftChildPtr(
            parent->getRightChildPtr()->getRightMidChildPtr());
        parent->getRightChildPtr()->setLeftMidChildPtr(nullptr);
        parent->getRightChildPtr()->setRightMidChildPtr(nullptr);
        parent->getRightChildPtr()->remove(
            parent->getRightChildPtr()->getSmallItem());
      }
    }
  }
}

bool Twothreefour::search(int data, shared_ptr<Node> node) {
  if (node == nullptr)
    return false;
  if (node->getSmallItem() == data || node->getMedItem() == data ||
      node->getLgItem() == data)
    return true;
  else if (data < node->getSmallItem())
    return search(data, node->getLeftChildPtr());
  else if (data < node->getMedItem() && data > node->getSmallItem())
    return search(data, node->getLeftMidChildPtr());
  else if (data < node->getLgItem() && data > node->getSmallItem())
    return search(data, node->getRightMidChildPtr());
  else
    return search(data, node->getRightChildPtr());
}
int Twothreefour::add(int data) { // add new node to tree
  auto start = chrono::high_resolution_clock::now();
  if (root == nullptr)
    root = make_shared<Node>(data, this);
  else
    addRecursive(data, root);
  auto end = chrono::high_resolution_clock::now();
  int diff = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  return (diff);
}

void Twothreefour::Node::add(const int &item) { // add new item to node
  // 2Node all same, 3 Node small/med same, 4 Node all Different
  if (uniqueCount() == 1) { // 2Node->3Node
    setSmallItem(min(item, getSmallItem()));
    setMedItem(min(item, getSmallItem()));
    setLargeItem(max(item, getLgItem()));
  } else if (uniqueCount() == 2) { // 3Node->4Node
    int oldSmall = getSmallItem();
    int newSmall;
    if (item < oldSmall)
      newSmall = item;
    else
      newSmall = oldSmall;
    setSmallItem(newSmall);
    int oldLg = getLgItem();
    int newLg;
    if (item > oldLg)
      newLg = item;
    else
      newLg = oldLg;
    setLargeItem(newLg);
    if (getLgItem() != oldLg)
      setMedItem(oldLg);
    if (getMedItem() == getSmallItem())
      setMedItem(item);
  } else if (uniqueCount() == 3) {
    tree->split(shared_from_this());
    tree->addRecursive(item, tree->root);
  }
}
void Twothreefour::Node::remove(const int &item) { // remove item from node
  if (uniqueCount() == 3) {
    if (smallItem == item)
      smallItem = medItem;
    else if (medItem == item)
      medItem = smallItem;
    else if (lgItem == item) {
      lgItem = medItem;
      medItem = smallItem;
    }
  } else if (uniqueCount() == 2) {
    if (smallItem == item) {
      smallItem = lgItem;
      medItem = lgItem;
    } else if (lgItem == item) {
      lgItem = smallItem;
    }
  }
}
