// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include "tree.h"

static void traverse(PMTree::Node* node, std::vector<char>& cur,
                     std::vector<std::vector<char>>& out) {
  if (node->children.empty()) {
    out.push_back(cur);
    return;
  }
  for (PMTree::Node* child : node->children) {
    cur.push_back(child->value);
    traverse(child, cur, out);
    cur.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> out;
  std::vector<char> cur;
  if (tree.root) traverse(tree.root, cur, out);
  return out;
}

static int64_t factorial(int n) {
  int64_t f = 1;
  for (int i = 2; i <= n; ++i) f *= i;
  return f;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

static void navigate(PMTree::Node* node, int num, std::vector<char>& res) {
  if (node->children.empty()) return;
  int k = static_cast<int>(node->children.size());
  int64_t sub = factorial(k - 1);
  int idx = static_cast<int>((num - 1) / sub);
  int rem = static_cast<int>((num - 1) % sub) + 1;
  if (idx < 0 || idx >= k) return;
  PMTree::Node* chosen = node->children[idx];
  res.push_back(chosen->value);
  navigate(chosen, rem, res);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> res;
  if (!tree.root || tree.root->children.empty()) return {};
  int k = static_cast<int>(tree.root->children.size());
  int64_t total = factorial(k);
  if (num < 1 || num > total) return {};
  navigate(tree.root, num, res);
  return res;
}
