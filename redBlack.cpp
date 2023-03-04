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

    void transplant(Node* u, Node* v) {
        if (!u->parent) {
            root = v;
        } 
        
        else if (u == u->parent->left) {
            u->parent->left = v;
        } 
        
        else {
            u->parent->right = v;
        }

        if (v) {
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

    void fixDoubleBlack(Node* &curr, Node* &node) {
    if(node == curr) {
        return;
    }

    Node* sibling = nullptr;

    if(node == node->parent->left) {
        sibling = node->parent->right;

        if(sibling && sibling->is_red) {
            sibling->is_red = false;
            node->parent->is_red = true;
            rotateLeft(curr, node->parent);
            sibling = node->parent->right;
        }

        if((!sibling->left || !sibling->left->is_red) && (!sibling->right || !sibling->right->is_red)) {
            sibling->is_red = true;
            fixDoubleBlack(curr, node->parent);
        }

        else {
            if(!sibling->right || !sibling->right->is_red) {
                sibling->left->is_red = false;
                sibling->is_red = true;
                rotateRight(curr, sibling);
                sibling = node->parent->right;
            }

            sibling->is_red = node->parent->is_red;
            node->parent->is_red = false;
            sibling->right->is_red = false;
            rotateLeft(curr, node->parent);
        }
    }

    else {
        sibling = node->parent->left;

        if(sibling && sibling->is_red) {
            sibling->is_red = false;
            node->parent->is_red = true;
            rotateRight(curr, node->parent);
            sibling = node->parent->left;
        }

        if((!sibling->left || !sibling->left->is_red) && (!sibling->right || !sibling->right->is_red)) {
            sibling->is_red = true;
            fixDoubleBlack(curr, node->parent);
        }

        else {
            if(!sibling->left || !sibling->left->is_red) {
                sibling->right->is_red = false;
                sibling->is_red = true;
                rotateLeft(curr, sibling);
                sibling = node->parent->left;
            }

            sibling->is_red = node->parent->is_red;
            node->parent->is_red = false;
            sibling->left->is_red = false;
            rotateRight(curr, node->parent);
        }
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

    void inorderRec(Node* curr) {
        if (curr == nullptr) {
            return;
        }
 
        /* first recur on left child */
        inorderRec(curr->left);
    
        /* then print the data of node */
        std::cout << curr->key << " ";
    
        /* now recur on right child */
        inorderRec(curr->right);
    }

    void rotateLeft(Node* &curr, Node* &node) { 
        Node* pivot = node->right;
        node->right = pivot->left;

        if(pivot->left) {
            pivot->left->parent = node;
        }

        pivot->parent = node->parent;

        if(!node->parent) {
            curr = pivot;
        }

        else if(node == node->parent->left) {
            node->parent->left = pivot;
        }

        else {
            node->parent->right = pivot;
        }

        pivot->left = node;
        node->parent = pivot;
    }

    void rotateRight(Node* &curr, Node* &node) {
        Node* pivot = node->left;
        node->left = pivot->right;

        if(pivot->right) {
            pivot->right->parent = node;
        }

        pivot->parent = node->parent;

        if(!node->parent) {
            curr = pivot;
        }

        else if(node == node->parent->left) {
            node->parent->left = pivot;
        }

        else {
            node->parent->right = pivot;
        }

        pivot->right = node;
        node->parent = pivot;
    }

    void fixViolation(Node* &curr, Node* &node) {
        if(node == curr) {
            node->is_red = false;
            return;
        }

        if(!node->parent->is_red) {
            return;
        }

        Node *parent = node->parent;
        Node* grandparent = parent->parent;
        Node* uncle = nullptr;

        if(parent == grandparent->left) {
            uncle = grandparent->right;
            if(uncle && uncle->is_red) {
                parent->is_red = false;
                uncle->is_red = false;
                grandparent->is_red = true;
                fixViolation(curr, grandparent);
                return;
            }

            if(node == parent->right) {
                rotateLeft(curr, parent);
                std::swap(node, parent);
            }

            parent->is_red = false;
            grandparent->is_red = true;
            rotateRight(curr, grandparent);
        }

        else {
            uncle = grandparent->left;
            if(uncle && uncle->is_red) {
                parent->is_red = false;
                uncle->is_red = false;
                grandparent->is_red = true;
                fixViolation(curr, grandparent);
                return;
            }

            if(node == parent->left) {
                rotateRight(curr, parent);
                std::swap(node, parent);
            }

            parent->is_red = false;
            grandparent->is_red = true;
            rotateLeft(curr, grandparent);
        }
    }
    



    
    public:
    int sizeNum;
    Node* root;
    int leftNum;
    int rightNum;

    Node* newNode() {
        Node* n = new Node;
        n->left = nullptr;
        n->right = nullptr;

        return n;
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
            root = nullptr;
            sizeNum = 0;
            leftNum = 0;
            rightNum = 0;
        }

        RBTree(keytype k[], valuetype V[], int s) {
            for(int i = 0; i < s; i++) {
                insert(k[i], V[i]);
            }
        }

        ~RBTree() {

        }

        valuetype *search(keytype k) {

        }

        void insert(keytype k, valuetype v) {
            Node *node = new Node;
            node->key = k;
            node->value = v;
            node->left = nullptr;
            node->right = nullptr;
            node->parent = nullptr;
            node->is_red = true;

            if(!root) {
                root = node;
                node->is_red = false;
                sizeNum++;
                return;
            }

            Node *curr = root;
            Node *parent = nullptr;

            while(curr != nullptr) {
                parent = curr;

                if(k < curr->key) {
                    curr = curr->left;
                }

                else if(k > curr->key) {
                    curr = curr->right;
                }

                else {
                    curr->value = v;
                    return;
                }
            }

            node->parent = parent;

            if(k < parent->key) {
                parent->left = node;
            }

            else {
                parent->right = node;
            }

            fixViolation(root, node);
            leftNum = countNodes(root->left);
            rightNum = countNodes(root->right);
            sizeNum++;
        }

        int remove(keytype k) {
    Node* node = findNode(root, k);
    if (node == nullptr) {
        return 0;
    }

    // Perform standard BST delete
    Node* parent = node->parent;
    if (node->left == nullptr) {
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        transplant(node, node->left);
    } else {
        Node* successor = findMinimum(node->right);
        if (successor->parent != node) {
            transplant(successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        transplant(node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
    }
    delete node;

    // Fix any violations of the Red-Black tree properties
    if (parent == nullptr) {
        if (root != nullptr) {
            root->is_red = false;
        }
        return 1;
    } else if (!node->is_red) {
        fixDoubleBlack(root, node);
    }

    return 1;
}



        int rank(keytype k) {
            return rankRec(root, k, leftNum, rightNum);
        }

        int rankRec(Node* curr, keytype k, int leftNum, int rightNum) {
            if(curr == nullptr) {
                return 0;
            }

            if(k == curr->key) {
                return leftNum + 1 + count(curr->left);
            }

            else if(k < root->key) {
                return rankRec(curr->left, k, leftNum, leftNum + rightNum);
            }

            else {
                return leftNum + 1 + count(root->left) + rankRec(curr->right, k, leftNum + count(curr->left) + 1, rightNum);
            }
        }

        int count(Node* curr) {
            if(curr == nullptr) {
                return 0;
            }

            return 1 + count(curr->left) + count(curr->right);
        }

        keytype select(int pos) {

        }
        
        keytype *successor(keytype k) {
            Node* temp = root;

            while(1) {
                if(temp == nullptr) {
                    return 0;
                }

                if(temp->key == k) {
                    if(temp->right != nullptr) {
                        temp = temp->right;
                        return temp->key;
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

            while(curr != nullptr) {
                if(root->key >= k) {
                    curr = curr->left;
                }

                else {
                    pred = curr;
                    curr = curr->right;
                }
            }

            return pred->key;
        }

        int size() {
            return sizeNum;
        }

        void preorder() {

        }

        void inorder() {
            inorderRec(root);
            std::cout << std::endl;
        }

        void postorder() {

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