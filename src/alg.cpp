// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <vector>
#include <algorithm>

PMTreeNode::PMTreeNode(char c) : symbol(c) {}

PMTreeNode::~PMTreeNode() {
    for (auto child : children) {
        delete child;
    }
}

PMTree::PMTree(const std::vector<char>& elements) {
    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());
    n = sorted.size();
    root = new PMTreeNode('\0');
    buildNode(root, sorted);
}

void PMTree::buildNode(PMTreeNode* parent, const std::vector<char>& elements) {
    for (int i = 0; i < elements.size(); ++i) {
        PMTreeNode* child = new PMTreeNode(elements[i]);
        parent->children.push_back(child);

        std::vector<char> new_elements;
        for (int j = 0; j < elements.size(); ++j) {
            if (j != i) {
                new_elements.push_back(elements[j]);
            }
        }
        buildNode(child, new_elements);
    }
}

PMTree::~PMTree() {
    if (root) {
        delete root;
    }
}

int PMTree::getSize() const {
    return n;
}

PMTreeNode* PMTree::getRoot() const {
    return root;
}

void traverse(PMTreeNode* node, std::vector<char>& current, std::vector<std::vector<char>>& result) {
    if (node->symbol != '\0') {
        current.push_back(node->symbol);
    }

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (auto child : node->children) {
            traverse(child, current, result);
        }
    }

    if (node->symbol != '\0') {
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    traverse(tree.getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    int total = all.size();
    if (num < 1 || num > total) {
        return std::vector<char>();
    }
    return all[num - 1];
}

std::vector<char> getPermHelper(PMTreeNode* node, int index, int remaining, const std::vector<int>& factorials) {
    std::vector<char> res;
    if (node->symbol != '\0') {
        res.push_back(node->symbol);
    }

    if (node->children.empty()) {
        return res;
    }

    int sub_size = factorials[remaining - 1];
    int child_index = index / sub_size;
    int remainder = index % sub_size;

    if (child_index >= node->children.size()) {
        return std::vector<char>();
    }

    PMTreeNode* child = node->children[child_index];
    std::vector<char> child_perm = getPermHelper(child, remainder, remaining - 1, factorials);
    res.insert(res.end(), child_perm.begin(), child_perm.end());
    return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    int n = tree.getSize();
    std::vector<int> factorials(n + 1);
    factorials[0] = 1;
    for (int i = 1; i <= n; ++i) {
        factorials[i] = factorials[i - 1] * i;
    }

    int total = factorials[n];
    if (num < 1 || num > total) {
        return std::vector<char>();
    }

    int index = num - 1;
    return getPermHelper(tree.getRoot(), index, n, factorials);
}
