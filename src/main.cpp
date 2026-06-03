// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <fstream>
#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  std::vector<std::vector<char>> all = getAllPerms(tree);
  for (std::vector<char>& p : all) {
    for (char c : p) std::cout << c;
    std::cout << "\n";
  }

  std::srand(static_cast<unsigned>(std::time(nullptr)));
  std::ofstream csv("result/data.csv");
  csv << "n,all,p1,p2\n";

  for (int n = 1; n <= 10; ++n) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; ++i)
      alphabet.push_back(static_cast<char>('1' + i));

    PMTree t(alphabet);
    int64_t total = 1;
    for (int i = 2; i <= n; ++i) total *= i;
    int num = std::rand() % total + 1;

    auto t0 = std::chrono::high_resolution_clock::now();
    getAllPerms(t);
    auto t1 = std::chrono::high_resolution_clock::now();
    getPerm1(t, num);
    auto t2 = std::chrono::high_resolution_clock::now();
    getPerm2(t, num);
    auto t3 = std::chrono::high_resolution_clock::now();

    double a  = std::chrono::duration<double, std::micro>(t1 - t0).count();
    double p1 = std::chrono::duration<double, std::micro>(t2 - t1).count();
    double p2 = std::chrono::duration<double, std::micro>(t3 - t2).count();

    csv << n << "," << a << "," << p1 << "," << p2 << "\n";
    std::cout << n << "\t" << a << "\t" << p1 << "\t" << p2 << "\n";
  }
  csv.close();
  return 0;
}
