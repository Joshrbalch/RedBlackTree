



#include <iostream>
#include "C:\Users\12564\Documents\GitHub\RedBlackTree\RBTree.cpp"

using namespace std;

int main() {
    RBTree<int, int> tree;
    int TREE_SIZE = 1001000;

    RBTree<int,int> X;


	for (int i = 0; i < TREE_SIZE; i++) {
        X.insert(i,i);
        // cout << i << ": ";
        // cout << endl;
        // X.printBalance();
    }

    std::cout << X.countRed(X.root) << std::endl;
    X.printBalance();

    // for(int i = 0; i < TREE_SIZE; i++) {
    //     X.remove(i);
    // }

    // X.printBalance();
    // std::cout << X.countRed(X.root) << std::endl;

    return 0;
}

