#include <iostream>
#include "RBTree.cpp"

using namespace std;

int main() {
    RBTree<int, int> tree;
    int TREE_SIZE = 10;

    string K[10] = {"A","B","C","D","E","F","G","H","I","K"};
	int V[10] = {10,9,8,7,6,5,4,3,2,1};
	
	RBTree<string,int> T1(K,V,10), T2;

    for(int i = 0; i < TREE_SIZE; i++) {
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

    // for(int i = 0; i < 10; i++) {
    //     cout << i << ": " << tree.rank(i) << endl;
    // }

    tree.printBalance();

    for(int i = 0; i < TREE_SIZE; i++) {
        tree.remove(i);
    }

    tree.inorder();
    tree.printBalance();


    return 0;
}