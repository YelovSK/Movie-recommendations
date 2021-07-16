#include <iostream>
#include "gtest/gtest.h"
#include "2_AVL.h"

using namespace ::testing;

vector<string> lines = {"0", "1", "2", "3", "4", "5", "6", "7"};

TEST(AVL, TreeSize) {
    AVL<string> tree;
    for (auto &line : lines) {
        tree.insert(line);
    }
    ASSERT_EQ(tree.getSize(), lines.size());
}

TEST(AVL, TreeSizeDuplicateName) {
    AVL<string> tree;
    for (auto &line : lines) {
        tree.insert(line);
    }
    string x = lines[0];
    tree.insert(x);
    ASSERT_EQ(tree.getSize(), lines.size());
}

TEST(AVL, TreeHeight) {
    AVL<string> tree;
    for (auto &line : lines) {
        tree.insert(line);
    }
    int height = tree.getHeight();
    ASSERT_EQ(height, 3);
}

TEST(AVL, TreeList) {
    AVL<string> tree;
    for (auto &line : lines) {
        tree.insert(line);
    }
    vector<string> list = tree.list();
    ASSERT_EQ(list.size(), 8);
}