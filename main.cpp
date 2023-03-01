#include <iostream>
#include "redBlack.cpp"

using namespace std;

int main() {
    RBTree<int, int> tree;

    tree.help();

    for(int i = 10; i >= 0; i--) {
        tree.insert(i, i);
    }

    tree.inorder();

    tree.printBalance();

    return 0;
}