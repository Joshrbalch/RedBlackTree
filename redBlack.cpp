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

        bool color;
    };

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
            if(sizeNum == 0) {
                root = newNode();
                root->key = k;
                root->value = v;
                sizeNum++;

                return;
            }

            else {
                sizeNum++;
                Node* temp = root;

                while(1) {
                    if(k < temp->key) {
                        if(temp->left == nullptr) {
                            Node* n = newNode(k, v);
                            temp->left = n;
                            leftNum++;
                            return;
                        }

                        else {
                            temp = temp->left;
                        }
                    }

                    else {
                        if(temp->right == nullptr) {
                            Node* n = newNode(k, v);
                            temp->right = n;
                            rightNum++;
                            return;
                        }

                        else {
                            temp = temp->right;
                        }
                    }
                }
            }
        }

        int remove(keytype k) {
            return 0;
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