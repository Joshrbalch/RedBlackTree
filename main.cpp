



#include <iostream>
#include "C:\Users\12564\Documents\GitHub\RedBlackTree\RBTree.cpp"

using namespace std;

int main() {
    RBTree<int, int> tree;
    int TREE_SIZE = 100;

    RBTree<int,int> X;


	for (int i=1;i<=TREE_SIZE;i++) {
        X.insert(i,i);
        cout << "Red Nodes: " << X.countRed(X.root) << endl;
        X.inorder();
        
    }

    X.remove(2);

    return 0;
}

