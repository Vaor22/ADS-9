// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class PMTree {
 public:
  struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char v) : value(v) {}
  };

  Node* root;

  explicit PMTree(const std::vector<char>& in) {
    root = new Node('\0');
    std::vector<char> sorted = in;
    std::sort(sorted.begin(), sorted.end());
    build(root, sorted);
  }

  ~PMTree() { destroy(root); }

 private:
  void build(Node* node, std::vector<char> rest) {
    for (std::size_t i = 0; i < rest.size(); ++i) {
      Node* child = new Node(rest[i]);
      node->children.push_back(child);
      std::vector<char> next = rest;
      next.erase(next.begin() + i);
      build(child, next);
    }
  }

  void destroy(Node* node) {
    if (!node) return;
    for (Node* c : node->children) destroy(c);
    delete node;
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
