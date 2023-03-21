#include <iostream>

template <class keytype, class valuetype>

class RBTree {
    private:
    class Node {
        private:
        public:
        keytype key;
        valuetype value;
        Node* left;
        Node* right;
        Node* parent;

        bool is_red;
    };

    valuetype *searchRec(Node* root, const keytype& key) {
        if(root == nullptr || root->key == key) {
            return (root == nullptr) ? nullptr : &root->value;
        }

        else if(key < root->key) {
            return searchRec(root->left, key);
        }

        else {
            return searchRec(root->right, key);
        }
    }

    void preorderRec(Node* curr) {
        if (curr == TNULL) {
            return;
        }
 
        /* first print data of node */
        std::cout << curr->key << " ";
    
        /* then recur on left sutree */
        preorderRec(curr->left);
    
        /* now recur on right subtree */
        preorderRec(curr->right);
    }

    void inorderRec(Node* curr) {
        if (curr == TNULL) {
            return;
        }
 
        /* first recur on left child */
        inorderRec(curr->left);
    
        /* then print the data of node */
        std::cout << curr->key << " ";
    
        /* now recur on right child */
        inorderRec(curr->right);
    }

    void postorderRec(Node* curr) {
        if (curr == TNULL) {
            return;
        }
 
        /* first recur on left child */
        postorderRec(curr->left);
    
        /* now recur on right child */
        postorderRec(curr->right);

        /* then print the data of node */
        std::cout << curr->key << " ";
    }

    keytype selectRec(int pos, Node* k) {
        int leftCount = countNodes(k->left);
        
        if(pos == leftCount + 1) {
            return k->key;
        }

        else if(pos <= leftCount) {
            return selectRec(pos, k->left);
        }

        else {
            return selectRec(pos - leftCount - 1, k->right);
        }
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
			root = v;
		} 
        
        else if (u == u->parent->left){
			u->parent->left = v;
		} 
        
        else {
			u->parent->right = v;
		}

		v->parent = u->parent;
    }

    Node* findMinimum(Node* node) {
        while (node->left) {
            node = node->left;
        }

        return node;
    }

    Node* findNode(Node* node, const keytype& k) {
        if (!node) {
            return nullptr;
        }
        if (k < node->key) {
            return findNode(node->left, k);
        } else if (k > node->key) {
            return findNode(node->right, k);
        } else {
            return node;
        }
    }

    int countNodes(Node* root) {
        int num = 1;

        if(root == nullptr) {
            return 0;
        }

        else {
            num += countNodes(root->left);
            num += countNodes(root->right);
            return num;
        }
    }

    void rotateLeft(Node* curr) {
        Node* y = curr->right;
        curr->right = y->left;
        
        if(y->left != TNULL) {
            y->left->parent = curr;
        }

        y->parent = curr->parent;

        if(curr->parent == nullptr) {
            this->root = y;
        }

        else if(curr == curr->parent->left) {
            curr->parent->left = y;
        }

        else {
            curr->parent->right = y;
        }

        y->left = curr;
        curr->parent = y;
    }

    void rotateRight(Node* &curr) {
        Node* y = curr->left;
        curr->left = y->right;

        if(y->right != TNULL) {
            y->right->parent = curr;
        }

        y->parent = curr->parent;

        if(curr->parent == nullptr) {
            this->root = y;
        }

        else if(curr == curr->parent->right) {
            curr->parent->right = y;
        }

        else {
            curr->parent->left = y;
        }

        y->right = curr;
        curr->parent = y;
    }

    void fixDelete(Node* x) {
        Node* s;

        while(x != root && x->is_red == 0) {
            if(x == x->parent->left) {
                s = x->parent->right;

                if(s->is_red) {
                    s->is_red = false;
                    x->parent->is_red = true;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                }

                if(s->left->is_red == false && s->right->is_red == false) {
                    s->is_red = true;
                    x = x->parent;
                }

                else {
                    if(s->right->is_red == false) {
                        s->left->is_red = false;
                        s->is_red = true;
                        rotateRight(s);
                        s = x->parent->right;
                    }

                    s->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    s->right->is_red = false;
                    rotateLeft(x->parent);
                    x = root;
                }
            }

            else {
                s = x->parent->left;
                if(s->is_red) {
                    s->is_red = false;
                    x->parent->is_red = true;
                    rotateRight(x->parent);
                    s = x->parent->left;
                }

                if(s->right->is_red == 0 && s->right->is_red == 0) {
                    s->is_red = true;
                    x = x->parent;
                }

                else {
                    if(s->left->is_red == false) {
                        s->right->is_red = false;
                        s->is_red = true;
                        rotateLeft(s);
                        s = x->parent->left;
                    }

                    s->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    s->left->is_red = false;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->is_red = false;
    }

    void fixViolation(Node* k){
		Node* u;
		while (k->parent->is_red == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->is_red == 1) {
					// case 3.1
					u->is_red = 0;
					k->parent->is_red = 0;
					k->parent->parent->is_red = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rotateRight(k);
					}
					// case 3.2.1
					k->parent->is_red = 0;
					k->parent->parent->is_red = 1;
					rotateLeft(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right; // uncle

				if (u->is_red == 1) {
					// mirror case 3.1
					u->is_red = 0;
					k->parent->is_red = 0;
					k->parent->parent->is_red = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						rotateLeft(k);
					}
					// mirror case 3.2.1
					k->parent->is_red = 0;
					k->parent->parent->is_red = 1;
					rotateRight(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->is_red = 0;
	}
    
    public:
    int sizeNum;
    Node* root;
    Node* TNULL;
    int leftNum;
    int rightNum;

    Node* newNode() {
        Node* node = new Node;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;
        node->is_red = true;

        return node;
    }

    Node* newNode(keytype k, valuetype v) {
        Node* n = new Node;
        n->value = v;
        n->key = k;
        n->left = nullptr;
        n->right = nullptr;

        return n;
    }
    
    public:
    RBTree() {
        TNULL = new Node;
        TNULL->is_red = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        sizeNum = 0;
        leftNum = 0;
        rightNum = 0;
    }

    RBTree(keytype k[], valuetype V[], int s) {
        root = nullptr;
        sizeNum = 0;
        leftNum = 0;
        rightNum = 0;
        for(int i = 0; i < s; i++) {
            insert(k[i], V[i]);
        }
    }

    ~RBTree() {

    }

    Node* searchNode(Node* root, const keytype& k) {
        if (root == nullptr || root->key == k) {
            return root;
        }

        else if(k < root->key) {
            return searchNode(root->left, k);
        }

        else {
            return searchNode(root->right, k);
        }
    }

    valuetype *search(keytype k) {
        return searchRec(root, k);
    }

    void insert(keytype k, valuetype v) {
        Node *node = new Node;
        node->key = k;
        node->value = v;
        node->parent = nullptr;
        node->is_red = true;
        node->left = TNULL;
        node->right = TNULL;

        Node* y = nullptr;
        Node* x = this->root;

        while(x != TNULL) {
            y = x;
            if(node->key < x->key) {
                x = x->left;
            }

            else {
                x = x->right;
            }
        }

        node->parent = y;

        if(y == nullptr) {
            root = node;
        }

        else if(node->key < y->key) {
            y->left = node;
        }

        else {
            y->right = node;
        }

        if(node->parent == nullptr) {
            node->is_red = false;
            return;
        }

        if(node->parent->parent == nullptr) {
            return;
        }

        fixViolation(node);
    }

    int remove(keytype k) {
        Node* z = nullptr;
        Node* x, y;
        Node* node = root;

        while(node != nullptr) {
            if(node->key == k) {
                z = node;
            }

            if(node->key <= k) {
                node = node->right;
            }

            else {
                node = node->left;
            }
        }

        if(z == nullptr) {
            return 0;
        }

        y = z;

        bool y_original_color = y->is_red;

        if(z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }

        else if(z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }

        else {
            y = minimum(z->right);
            y_original_color = y->is_red;
            x = y->right;

            if(y->parent == z) {
                x->parent = y;
            }

            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->is_red = z->is_red;
        }

        delete z;
        if(y_original_color == false) {
            fixDelete(x);
        }
    }


   void rankRec(Node* curr, keytype nums[], int i) {
        if (curr == nullptr) {
            return;
        }
 
        /* first recur on left child */
        rankRec(curr->left, nums, i);

        nums[i] = curr->key;
        i++;
    
        /* now recur on right child */
        rankRec(curr->right, nums, i);

        return;
    }

    int rank(keytype k) {
        if(k < root->key) {
            keytype nums[leftNum];
            rankRec(root->left, nums, 0);

            for(int i = 0; i < leftNum; i++) {
                if(nums[i] == k) {
                    return i + 1;
                }
            }

            return 0;
        }

        else if(k > root->key) {
            keytype nums[rightNum];
            rankRec(root->right, nums, 0);

            for(int i = 0; i < rightNum; i++) {
                if(nums[i] == k) {
                    // std::cout << i << std::endl;
                    return i + leftNum + 1;
                }
            }

            return 0;
        }

        else if(k == root->key){
            return leftNum + 1;
        }

        return 0;
    }


    keytype select(int pos) {
        if(pos > sizeNum || pos < 1) {
            return 0;
        }

        else {
            return selectRec(pos, root);
        }

        return 0;
    }

    int countRed(Node* curr) {
        if(curr == nullptr) {
            return 0;
        }

        int count{};

        if(curr->is_red) {
            count = 1;
        }

        count += countRed(curr->left) + countRed(curr->right);
        return count;
    }
    
    keytype *successor(keytype k) {
        Node* temp = root;
        keytype* out;

        while(1) {
            if(temp == nullptr) {
                return 0;
            }

            if(temp->key == k) {
                if(temp->right != nullptr) {
                    temp = temp->right;
                    out = &temp->key;
                    return out;
                }

                else {
                    std::cout << "No successor" << std::endl;
                    return nullptr;
                }
            }

            else {
                if(k < temp->key) {
                    temp = temp->left;
                }

                else {
                    temp = temp->right;
                }
            }
        }
    }

    keytype *predecessor(keytype k) {
        Node* pred = nullptr;
        Node* curr = root;
        keytype* out;

        while(curr != nullptr) {
            if(root->key >= k) {
                curr = curr->left;
            }

            else {
                pred = curr;
                curr = curr->right;
            }
        }
        out = &pred->key;
        return out;
    }

    int size() {
        return sizeNum;
    }

    void preorder() {
        preorderRec(root);
        std::cout << std::endl;
    }

    void inorder() {
        inorderRec(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorderRec(root);
        std::cout << std::endl;
    }

    void printBalance() {
        std::cout << "LEFT: " << leftNum << std::endl;
        std::cout << "RIGHT: " << rightNum << std::endl;
    }

    void help() {
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