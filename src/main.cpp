// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::cout << "All permutations for {'1','2','3'}:" << std::endl;
    auto perms = getAllPerms(tree);
    for (const auto& perm : perms) {
        for (char c : perm) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    std::cout << "\nPermutation #1: ";
    auto p1 = getPerm1(tree, 1);
    for (char c : p1) std::cout << c;
    std::cout << std::endl;

    std::cout << "Permutation #2: ";
    auto p2 = getPerm2(tree, 2);
    for (char c : p2) std::cout << c;
    std::cout << std::endl;

    std::ofstream data("data.csv");
    data << "n,getAllPerms,getPerm1,getPerm2\n";

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> input;
        for (int i = 1; i <= n; ++i) {
            input.push_back('0' + i);
        }

        PMTree tree(input);

        auto start = std::chrono::high_resolution_clock::now();
        auto all_perms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double time_all = std::chrono::duration<double>(end - start).count();

        double time_perm1 = 0.0;
        double time_perm2 = 0.0;
        int num_tests = 100;
        int total_perms = all_perms.size();

        if (total_perms > 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(1, total_perms);

            for (int i = 0; i < num_tests; ++i) {
                int num = dist(gen);

                start = std::chrono::high_resolution_clock::now();
                getPerm1(tree, num);
                end = std::chrono::high_resolution_clock::now();
                time_perm1 += 
                    std::chrono::duration<double>(end - start).count();

                start = std::chrono::high_resolution_clock::now();
                getPerm2(tree, num);
                end = std::chrono::high_resolution_clock::now();
                time_perm2 +=
                    std::chrono::duration<double>(end - start).count();
            }
            time_perm1 /= num_tests;
            time_perm2 /= num_tests;
        }
        data << n << "," << std::scientific << time_all 
             << "," << time_perm1 << "," << time_perm2 << "\n";
        std::cout << "n=" << n << " completed." << std::endl;
    }

    data.close();
    return 0;
}
