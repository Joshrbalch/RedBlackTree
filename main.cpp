#include <iostream>
#include "redBlack.cpp"

using namespace std;

int main() {
    RBTree<int, int> tree;

    tree.help();

    // for(int i = 100; i >= 0; i--) {
    //     tree.insert(i, i);
    // }
    tree.insert(10, 10);
    tree.insert(1, 1);
    tree.insert(15, 15);

    cout << tree.rank(1) << tree.rank(10) << tree.rank(15) << endl;

    tree.inorder();

    tree.printBalance();

    return 0;
}