#include <iostream>

template <class keytype, class valuetype>

class RBTree {
    private:
    int size;
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
            size = 0;
            leftNum = 0;
            rightNum = 0;
        }

        RBTree(keytype k[], valuetype V[], int s) {
            for(int i = 0; i < s; i++) {
                insert(k[i], v[i]);
            }
        }

        ~RBTree() {

        }

        valuetype *search(keytype k) {

        }

        void insert(keytype k, valuetype v) {
            if(size = 0) {
                root = newNode();
                root->key = k;
                root->value = v;
                size++;

                return;
            }

            else {
                size++;
                Node* temp = root;

                while(1) {
                    if(k < temp->key) {
                        if(temp->left == nullptr) {
                            Node* n = newNode(k, v);
                            temp->left = n;
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

        }

        int rank(keytype k) {

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

        }

        int size() {
            return size;
        }

        void preorder() {

        }

        void inorder() {

        }

        void postorder() {

        }
};