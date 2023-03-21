



#include <iostream>
#include "C:\Users\12564\Documents\GitHub\RedBlackTree\RBTree.cpp"

using namespace std;

int main() {
    RBTree<int, int> tree;
    int TREE_SIZE = 10;

    RBTree<int,int> X;

    X.insert(1,1);
    X.insert(2,2);
    X.insert(3,3);
    cout << X.countRed(X.root) << endl;

	// for (int i=1;i<TREE_SIZE;i++) X.insert(i,i);
	// for (int i=1;i<TREE_SIZE;i++) {
	// 	// if(X.rank(i) != i) cout << "Rank error" << endl;
	// 	if(X.select(i) != i) cout << "Select error" << endl;
	// 	if(*(X.search(i)) != i) cout << "Search error" << endl;
	// }  


    return 0;
}

