#include <iostream>
#include <random>

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

    Node* moveRedRight(Node* curr) {
        colorFlip(curr);
        if (is_red(curr->left->left)) {
            curr = rotateRight(curr);
            colorFlip(curr);
        }
        return curr;
    }


    Node* moveRedLeft(Node* curr) {
        colorFlip(curr);
        if (is_red(curr->right->left)) {
            curr->right = rotateRight(curr->right);
            curr = rotateLeft(curr);
            colorFlip(curr);
        }
        return curr;
    }

    void colorFlip(Node* curr) {
        curr->is_red = !curr->is_red;
        curr->left->is_red = !curr->left->is_red;
        curr->right->is_red = !curr->right->is_red;
    }

    valuetype findVal(Node* curr, keytype key) {
        if (curr == nullptr) {
            return nullptr;
        }

        else if (curr->key == key) {
            return &(curr->value);
        }

        else if(key > curr->key) 
            return findVal(curr->right, key); {
		}
		else 
            return findVal(curr->left, key); {
		}

        return nullptr;
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
        if (v != nullptr) {
            v->parent = u->parent;
        }
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

        if(root == TNULL) {
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
        if(curr == root) {
            int collateral = countNodes(y->left);
            leftNum += collateral + 1;
            rightNum = rightNum - 1 - collateral;
        }

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

    void rotateRight(Node* curr) {
        Node* y = curr->left;
        if(curr == root) {
            int collateral = countNodes(y->right);
            rightNum += collateral + 1;
            leftNum = leftNum - 1 - collateral;
        }

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

        while(x != nullptr && x != root && x->is_red == 0) {
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
        root->is_red = false;
    }

    void fixViolation(Node* k){
		Node* u;
        
		while (k->parent->is_red == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u != nullptr && u->is_red == 1) {
					// case 3.1
					u->is_red = 0;
					k->parent->is_red = 0;
					k->parent->parent->is_red = 1;
					k = k->parent->parent;
				} 
                
                else {
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

			} 
            
            else {
				u = k->parent->parent->right; // uncle

				if (u->is_red == 1) {
					// mirror case 3.1
					u->is_red = 0;
					k->parent->is_red = 0;
					k->parent->parent->is_red = 1;
					k = k->parent->parent;	
				} 
                
                else {
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

    valuetype *search(keytype k) {
        return findVal(root, k);
    }

    void insert(keytype k, valuetype v) {
        Node* node = new Node;
        node->key = k;
        node->value = v;
        node->parent = nullptr;
        node->is_red = true;
        node->left = TNULL;
        node->right = TNULL;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            }

            else {
                x = x->right;
            }
        }

        sizeNum = sizeNum + 1;

        if (root != TNULL) {
            if (k < root->key) {
                leftNum++;
            }

            else {
                rightNum++;
            }
        }

        node->parent = y;

        if (y == nullptr) {
            root = node;
        }

        else if (node->key < y->key) {
            y->left = node;
        }

        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->is_red = false;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixViolation(node);
    }

    Node* deleteMinimum(Node* curr) {
        if (curr->left == TNULL) {
            return TNULL;
        }

        if(curr->left->is_red == 0 && curr->left->left->is_red == 0) 
            curr = moveRedLeft(curr); {
		}

        curr->left = deleteMinimum(curr->left);
        return fix(curr);
    }

    Node* removeNode(Node* curr, keytype key) {
        if (key < curr->key) {
            if (curr->left->is_red == 0 && curr->left->left->is_red == 0) {
                curr = moveRedLeft(curr);
            }
            curr->left = removeNode(curr->left, key);
        }

        else {
            if (curr->left->is_red) {
                rotateRight(curr);
            }

            if (key == curr->key && (curr->right == TNULL)) {
				return TNULL;
			}

            if (curr->right->is_red == 0 && curr->right->left->is_red == 0) {
				curr = moveRedRight(curr);
			}

            if (key == curr->key) {
                Node* x = curr->right;

                while (x->left != TNULL) {
					x = x->left;
				}

                curr->key = x->key;
                curr->value = x->value;
                curr->right = 
            }
        }
    }

    int remove(keytype k) {
        if (search(k) == nullptr) {
            return 0;
        }

        root = removeNode(root, k)
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
        return 0;
    }


    keytype select(int pos) {
        if(pos > sizeNum - 1 || pos < 1) {
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