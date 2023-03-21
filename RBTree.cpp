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
        if (curr == nullptr) {
            return;
        }
 
        /* first print data of node */
        std::cout << curr->key << " ";
    
        /* then recur on left sutree */
        preorderRec(curr->left);
    
        /* now recur on right subtree */
        preorderRec(curr->right);
    }

    void postorderRec(Node* curr) {
        if (curr == nullptr) {
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

    void rotateLeft(Node* curr) {
        std::cout << "rotate left" << std::endl;
        Node* y = curr->right;
        curr->right = y->left;

        if(y->left != nullptr) {
            y->left->parent = curr;
        }

        y->parent = curr->parent;

        if(curr->parent == nullptr) {
            root = y;
        }

        else if(curr == curr->parent->left) {
            curr->parent->left = y;
        }

        else {
            curr->parent->right = y;
        }

        y->left = curr;
        curr->parent = y;
        // Node* pivot = node->right;
        // node->right = pivot->left;

        // if(pivot->left) {
        //     pivot->left->parent = node;
        // }

        // pivot->parent = node->parent;

        // if(!node->parent) {
        //     curr = pivot;
        // }

        // else if(node == node->parent->left) {
        //     node->parent->left = pivot;
        // }

        // else {
        //     node->parent->right = pivot;
        // }

        // pivot->left = node;
        // node->parent = pivot;
    }

    void rotateRight(Node* &curr) {
        Node* y = curr->left;
        curr->left = y->right;

        if(y->right != nullptr) {
            y->right->parent = curr;
        }

        y->parent = curr->parent;

        if(curr->parent == nullptr) {
            root = y;
        }

        else if(curr == curr->parent->left) {
            curr->parent->left = y;
        }

        else {
            curr->parent->right = y;
        }

        y->right = curr;
        curr->parent = y;
        // Node* pivot = node->left;
        // node->left = pivot->right;

        // if(pivot->right) {
        //     pivot->right->parent = node;
        // }

        // pivot->parent = node->parent;

        // if(!node->parent) {
        //     curr = pivot;
        // }

        // else if(node == node->parent->left) {
        //     node->parent->left = pivot;
        // }

        // else {
        //     node->parent->right = pivot;
        // }

        // pivot->right = node;
        // node->parent = pivot;
    }

    void fixViolation(Node* curr) {
        if(sizeNum == 1) {
            return;
        }
        

        if(curr->parent->is_red == true) {
            
            while(curr->parent->is_red == true) {
                
                if(curr->parent == curr->parent->parent->left) {
                    
                    Node* y = curr->parent->parent->right;

                    if(y->is_red == true) {
                        curr->parent->is_red = false;
                        y->is_red = false;
                        curr->parent->parent->is_red = true;
                        curr = curr->parent->parent;
                    }

                    else if(curr = curr->parent->right) {
                        curr = curr->parent;
                        rotateLeft(curr);
                    }

                    curr->parent->is_red = false;
                    curr->parent->parent->is_red = true;
                    rotateRight(curr);
                }

                else {
                    
                    Node* y = curr->parent->parent->left;

                    if(y->is_red == true) {
                        
                        curr->parent->is_red = false;
                        y->is_red = false;
                        curr->parent->parent->is_red = true;
                        curr = curr->parent->parent;
                    }

                    else if(curr == curr->parent->left) {
                        curr = curr->parent;
                        rotateRight(curr);
                    }
                    //TRACKED PROBLEM TO HERE
                    curr->parent->is_red = false;
                    curr->parent->parent->is_red = true;
                    rotateLeft(curr);
                }
            }
            root->is_red = false;
        }




        // if(node == curr) {
        //     node->is_red = false;
        //     return;
        // }

        // if(!node->parent->is_red) {
        //     return;
        // }

        // Node *parent = node->parent;
        // Node* grandparent = parent->parent;
        // Node* uncle = nullptr;

        // if(parent == grandparent->left) {
        //     uncle = grandparent->right;
        //     if(uncle && uncle->is_red) {
        //         parent->is_red = false;
        //         uncle->is_red = false;
        //         grandparent->is_red = true;
        //         fixViolation(curr, grandparent);
        //         return;
        //     }

        //     if(node == parent->right) {
        //         rotateLeft(curr, parent);
        //         std::swap(node, parent);
        //     }

        //     parent->is_red = false;
        //     grandparent->is_red = true;
        //     rotateRight(curr, grandparent);
        // }

        // else {
        //     uncle = grandparent->left;
        //     if(uncle && uncle->is_red) {
        //         parent->is_red = false;
        //         uncle->is_red = false;
        //         grandparent->is_red = true;
        //         fixViolation(curr, grandparent);
        //         return;
        //     }

        //     if(node == parent->left) {
        //         rotateRight(curr, parent);
        //         std::swap(node, parent);
        //     }

        //     parent->is_red = false;
        //     grandparent->is_red = true;
        //     rotateLeft(curr, grandparent);
        // }
    }
    



    
    public:
    int sizeNum;
    Node* root;
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
        root = nullptr;
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
        Node *node = newNode(k, v);
        if(sizeNum == 0) {
            root = node;
            root->is_red = false;
            sizeNum++;
            return;
        }

        // if(sizeNum == 0 || root == nullptr) {
        //     std::cout << "CHECK" << std::endl;
        //     root = node;
        //     node->is_red = false;
        //     sizeNum++;
        //     return;
        // }

        Node* y = nullptr;
        Node* x = root;

        while(x != nullptr) {
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
            root->is_red = false;
        }

        else if(node->key < y->key) {
            y->left = node;
        }

        else {
            y->right = node;
        }

        sizeNum++;

        node->left = nullptr;
        node->right = nullptr;
        node->is_red = true;

        fixViolation(node);

        // if(sizeNum == 0 || root == nullptr) {
        //     root = node;
        //     node->is_red = false;
        //     sizeNum++;
        //     return;
        // }

        // Node *curr = root;
        // Node *parent = nullptr;

        // while(curr != nullptr) {
        //     parent = curr;

        //     if(k < curr->key) {
        //         curr = curr->left;
        //     }

        //     else if(k > curr->key) {
        //         curr = curr->right;
        //     }

        //     else {
        //         curr->value = v;
        //         return;
        //     }
        // }

        // node->parent = parent;

        // if(k < parent->key) {
        //     parent->left = node;
        // }

        // else {
        //     parent->right = node;
        // }

        // if(k < root->key) {
        //     leftNum++;
        // }

        // else {
        //     rightNum++;
        // }
        
        // fixViolation(root, node);
        // leftNum = countNodes(root->left);
        // rightNum = countNodes(root->right);
        // sizeNum++;
    }

    int remove(keytype k) {
        Node *curr = newNode();
        curr = searchNode(root, k);

        if(curr == nullptr) {
            return 0;
        }

        if(curr->left == nullptr) {
            transplant(curr, curr->right);
            sizeNum--;
            leftNum = countNodes(root->left);
            rightNum = countNodes(root->right);
            return 1;
        }

        else if(curr->right == nullptr) {
            transplant(curr, curr->left);
            sizeNum--;
            leftNum = countNodes(root->left);
            rightNum = countNodes(root->right);
            return 1;
        }

        else {
            Node *y = newNode();
            y = findMinimum(curr->right);

            if(y->parent != curr) {
                transplant(y, y->right);
                y->right = curr->right;
                y->right->parent = y;
            }

            transplant(curr, y);
            y->left = curr->left;
            y->left->parent = y;
            y->is_red = curr->is_red;
            leftNum = countNodes(root->left);
            rightNum = countNodes(root->right);
            sizeNum--;
            return 1;
        }

        return 0;
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