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

    tree.inorder();
    tree.preorder();
    tree.postorder();

    for(int i = 0; i < 5; i++) {
        cout << i << ": " << tree.rank(i) << endl;
    }

    tree.printBalance();

    return 0;
}