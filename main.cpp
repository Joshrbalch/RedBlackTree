#include <iostream>
#include "redBlack.cpp"

using namespace std;

int main() {
    RBTree<int, int> tree;

    for(int i = 0; i < 5; i++) {
        tree.insert(i, i);
    }
    // tree.insert(1, 1);
    // tree.insert(2, 2);
    // tree.insert(3, 3);
    // tree.insert(4, 4);
    // tree.insert(5, 5);

    // cout << tree.rank(1) << tree.rank(10) << tree.rank(15) << endl;
    tree.printBalance();
    
    tree.inorder();

    tree.remove(2);

    tree.printBalance();

    return 0;
}