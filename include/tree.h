// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class PMTreeNode {
 public:
    char symbol;
    std::vector<PMTreeNode*> children;

    explicit PMTreeNode(char c);
    ~PMTreeNode();
};

class PMTree {
 private:
    PMTreeNode* root;
    int n;

    void buildNode(PMTreeNode* parent, const std::vector<char>& elements);

 public:
    explicit PMTree(const std::vector<char>& elements);
    ~PMTree();

    int getSize() const;
    PMTreeNode* getRoot() const;
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
