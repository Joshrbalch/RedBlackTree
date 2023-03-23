#include <iostream>
using namespace std;

template<typename keytype, typename valuetype>
class RBTree
{
private:
	struct RBNode {
		RBNode* left, *right;
		keytype key;
		valuetype val;
		bool color;
		int size;
	};

	RBNode* root;
	int sizeNum;
	int leftNum;
	int rightNum;

	RBNode* newNode(keytype key, valuetype val, bool color = true) { // color = true is color = red
		RBNode* newnode = new RBNode;
		newnode->left = NULL;
		newnode->right = NULL;
		newnode->key = key;
		newnode->val = val;
		newnode->color = color;
		newnode->size = 1;
		return newnode;
	}

	void clearMemory(RBNode* curr) { // clear memory of the tree
		if (curr == NULL) {
			return;
		}

		clearMemory(curr->left);

		if (curr->left != NULL) {
			free(curr->left);
		}

		clearMemory(curr->right);

		if (curr->right != NULL) {
			free(curr->right);
		}
	}

	RBNode* findMax(RBNode* root) {
		while (root->right) {
			root = root->right;
		}

		return root;
	}

	bool isRed(RBNode* curr) { // check if the node is red
		if (curr == NULL) {
			return 0;
		}

		return (curr->color);
	}

	int nodeSize(RBNode* curr) { // get the size of the node
		if (curr == NULL) {
			return 0;
		}

		return curr->size;
	}

	RBNode* rotateLeft(RBNode* curr) { // rotate left 
		RBNode* x = curr->right;
		curr->right = x->left;
		x->left = curr;
		x->color = x->left->color;
		x->left->color = 1;

		curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
		x->size = nodeSize(x->left) + nodeSize(x->right) + 1;
		return x;
	}


	RBNode* rotateRight(RBNode* curr) { // rotate right
		RBNode* x = curr->left;
		curr->left = x->right;
		x->right = curr;
		x->color = x->right->color;
		x->right->color = 1; 

		curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
		x->size = nodeSize(x->left) + nodeSize(x->right) + 1;
		return x;
	}

	void colorFlip(RBNode* curr) { // flip the color of the node
		curr->color = !curr->color;
		curr->left->color = !curr->left->color;
		curr->right->color = !curr->right->color;
	}

	RBNode* insertNode(RBNode* curr, keytype key, valuetype val) { // insert the node into the tree 
		if (curr == NULL) {
			return newNode(key, val);
		}

		if (isRed(curr->left) && isRed(curr->right)) {
			colorFlip(curr);
		}

		if (key < curr->key) {
			curr->left = insertNode(curr->left, key, val);
		}

		else if (key > curr->key) {
			curr->right = insertNode(curr->right, key, val);
		}

		else if (key == curr->key) {
			curr->val = val;
		}

		if (isRed(curr->right)) {
			curr = rotateLeft(curr);
		}

		if (isRed(curr->left) && isRed(curr->left->left)) {
			curr = rotateRight(curr);
		}

		curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
		return curr;
	}

	void printInOrder(RBNode* curr) { // print the tree in order recurcively 
		if (curr == NULL) {
			return;
		}

		printInOrder(curr->left);
		cout << curr->key << " ";
		printInOrder(curr->right);
	}

	void printPostOrder(RBNode* curr) { // print the tree in post order recurcively
		if (curr == NULL) {
			return;
		}

		printPostOrder(curr->left);
		printPostOrder(curr->right);
		cout << curr->key << " ";
	}

	void printPreOrder(RBNode* curr) { // print the tree in pre order recurcively
		if (curr == NULL) {
			return;
		}

		cout << curr->key << " ";
		printPreOrder(curr->left);
		printPreOrder(curr->right);
	}

	RBNode* fixUp(RBNode* curr) { // fix up the tree after deletion
		if (isRed(curr->right)) {
			curr = rotateLeft(curr);
		}

		if (isRed(curr->left) && isRed(curr->left->left)) {
			curr = rotateRight(curr);
		}

		if (isRed(curr->left) && isRed(curr->right)) {
			colorFlip(curr);
		}

		curr->size = nodeSize(curr->left) + nodeSize(curr->right) + 1;
		return curr;
	}


	RBNode* moveRedRight(RBNode* curr) { // move the red node to the right
		colorFlip(curr);

		if (isRed(curr->left->left)) {
			curr = rotateRight(curr);
			colorFlip(curr);
		}

		return curr;
	}


	RBNode* moveRedLeft(RBNode* curr) { // move the red node to the left
		colorFlip(curr);

		if (isRed(curr->right->left)) {
			curr->right = rotateRight(curr->right);
			curr = rotateLeft(curr);
			colorFlip(curr);
		}

		return curr;
	}

	RBNode* deleteMin(RBNode* curr) { // delete the minimum node
		if (curr->left == NULL) {
			return NULL;
		}

		if (!isRed(curr->left) && !isRed(curr->left->left)) {
			curr = moveRedLeft(curr);
		}

		curr->left = deleteMin(curr->left);
		return fixUp(curr);
	}

	RBNode* removeNode(RBNode* curr, keytype key) { // remove the node from the tree
		if (key < curr->key) {
			if (!isRed(curr->left) && !isRed(curr->left->left)) {
				curr = moveRedLeft(curr);
			}

			curr->left = removeNode(curr->left, key);
		}

		else {
			if (isRed(curr->left)) {
				curr = rotateRight(curr);
			}

			if (key == curr->key && curr->right == NULL) {
				return NULL;
			}

			if (!isRed(curr->right) && !isRed(curr->right->left)) {
				curr = moveRedRight(curr);
			}

			if (key == curr->key) {
				RBNode* x = curr->right;

				while (x->left != NULL) {
					x = x->left;
				}

				curr->key = x->key;
				curr->val = x->val;
				curr->right = deleteMin(curr->right);
			}

			else {
				curr->right = removeNode(curr->right, key);
			}
		}

		return fixUp(curr);
	}

	RBNode* copy(RBNode* curr) { // copy the tree
		RBNode* newnode = newNode(curr->key, curr->val, curr->color);
		if (curr->left != NULL) {
			newnode->left = copy(curr->left);
		}

		if (curr->right != NULL) {
			newnode->right = copy(curr->right);
		}

		newnode->size = curr->size;
		return newnode;
	}

	valuetype* findVal(RBNode* curr, keytype key) { // returns a pointer to the value in the same node as the given key
		if (curr == NULL) {
			return NULL;
		}

		else if (curr->key == key) {
			return &(curr->val);
		}

		else if (key > curr->key) {
			return findVal(curr->right, key);
		}

		else if (key < curr->key) {
			return findVal(curr->left, key);
		}

		return NULL;
	}

	RBNode* findNode(RBNode* curr, keytype key) { // returns a pointer to the node with the given key
		if (curr == NULL) {
			return NULL;
		}

		else if (curr->key == key) {
			return curr;
		}

		else if (key > curr->key) {
			return findNode(curr->right, key);
		}

		else if(key < curr->key) {
			return findNode(curr->left, key);
		}

		return NULL;
	}

	int getRank(RBNode* curr, keytype key) { // returns the rank of the given key
		if (curr == NULL) {
			return 0;
		}

		else if (key > curr->key) {
			return nodeSize(curr->left) + 1 + getRank(curr->right, key);
		}

		else if (key < curr->key) {
			return getRank(curr->left, key);
		}

		else if (key == curr->key) {
			return curr->size - nodeSize(curr->right);
		}

		else {
			return 0;
		}
	}

	keytype getPos(RBNode* curr, int k) { // returns the key at the given position
		int place = nodeSize(curr->left) + 1;
		if (k == place) {
			return curr->key;
		}

		else if (k < place) {
			return getPos(curr->left, k);
		}

		else {
			return getPos(curr->right, k - place);
		}
	}

public:

	RBTree() { // constructor
		root = NULL;
		sizeNum = 0;
		leftNum = 0;
		rightNum = 0;
	}

	RBTree(keytype k[], valuetype v[], int s) { // constructor
		root = NULL;
		sizeNum = 0;
		leftNum = 0;
		rightNum = 0;

		for (int i = 0; i < s; i++) {
			root = insertNode(root, k[i], v[i]);
			root->color = 0;
		}
	}

	RBTree(RBNode* root) { // constructor
		this->root = root;
		this->root->color = 0;
	}

	~RBTree() { // destructor
		clearMemory(root);
		free(root);
	}

	RBTree(const RBTree& other) { // copy constructor
		root = copy(other.root);
	}

	RBTree& operator=(const RBTree& other) { // assignment operator
		root = copy(other.root);
		return *this;
	}

	void insert(keytype k, valuetype v) { // parent function for insertNode algorithm
		root = insertNode(root, k, v);
		sizeNum++;
		root->color = 0;
	}

	int remove(keytype k) { // parent function for removeNode algorithm
		if (search(k) == NULL) {
			return 0;
		}

		int s = nodeSize(root);
		root = removeNode(root, k);

		return s - nodeSize(root);
	}

	valuetype* search(keytype key) { // parent function for findVal algorithm
		return findVal(root, key);
	}

	int rank(keytype k) { // Returns the rank of the key k in the tree. Returns 0 if the key k is not found
		return getRank(root, k);
	}

	keytype select(int pos) { // Returns the key of the node at position pos in the tree
		if (pos > nodeSize(root) || pos < 1) {
			return 0;
		}

		return getPos(root, pos);
	}

	keytype* successor(keytype k) { // Returns the key of the successor of k in the tree. Returns NULL if k has no successor
		RBNode* succ = nullptr;
		RBNode* curr = root;

		while (curr != nullptr) {
			if (curr->key < k) {
				curr = curr->right;
			}

			else if (curr->key > k) {
				succ = curr;
				curr = curr->left;
			}
			else {
				if (curr->right != nullptr) {
					succ = curr->right;

					while (succ->left != nullptr) {
						succ = succ->left;
					}
				}
				return &succ->key;
			}
		}

		return &succ->key;
	}

	keytype* predecessor(keytype k) { // Returns a pointer to the key after k in the tree. Returns NULL if no successor exists
		RBNode* pred = NULL;
		RBNode* curr = root;
		while (curr != NULL) {
			if (curr->key > k) {
				curr = curr->left;
			}

			else if (curr->key < k) {
				pred = curr;
				curr = curr->right;
			}

			else {
				if (curr->left != NULL) {
					pred = curr->left;
					while (pred->right != NULL) {
						pred = pred->right;
					}
				}
				return &pred->key;
			}
		}
		return &pred->key;
	}

	int size() { // Returns the size of the tree
		return nodeSize(root);
	}

	void preorder() { // Prints the preorder of the tree
		printPreOrder(root);
		cout << endl;
	}

	void inorder() { // Prints the inorder of the tree
		printInOrder(root);
		cout << endl;
	}

	void postorder() { // Prints the post order of the tree
		printPostOrder(root);
		cout << endl;
	}

	int countRed(RBNode* curr) { // Counts and returns the number of red nodes in the tree
		if (curr == nullptr) {
			return 0;
		}

		int count{};

		if (curr->is_red) {
			count = 1;
		}

		count += countRed(curr->left) + countRed(curr->right);
		return count;
	}
	
	void help() { // Helper function for user
		std::cout << "FUNCTIONALITY:" << std::endl;
		std::cout << "\t" << "search(keytype k)" << std::endl;
		std::cout << "\t" << "insert(keytype k, valuetype v)" << std::endl;
		std::cout << "\t" << "remove(keytype k)" << std::endl;
		std::cout << "\t" << "rank(keytype k)" << std::endl;
		std::cout << "\t" << "select(int pos)" << std::endl;
		std::cout << "\t" << "successor(keytype k)" << std::endl;
		std::cout << "\t" << "predecessor(keytype k)" << std::endl;
		std::cout << "\t" << "size()" << std::endl;
		std::cout << "\t" << "preorder()" << std::endl;
		std::cout << "\t" << "inorder()" << std::endl;
		std::cout << "\t" << "postorder()" << std::endl;
		std::cout << "\t" << "printBalance()" << std::endl;
		std::cout << "---------------------------------------" << std::endl;

	}
};