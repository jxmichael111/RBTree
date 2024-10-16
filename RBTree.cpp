#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;
    }
};


class RedBlackTree {
private:
    Node *root;
    Node *TNULL;

    void initializeNULLNode(Node *node, Node *parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = BLACK;
    }

    Node* searchTreeHelper(Node* node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key); 
    }

    void fixInsert(Node *k) {
        Node *u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

public:
    RedBlackTree() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void insert(int key) {
        Node *node = new Node(key);
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node *y = nullptr;
        Node *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    
    Node* search(int k) {
        return searchTreeHelper(this->root, k);
    }

    void clearTree() {
        root = TNULL;
    }
};

void runAndSaveResults(const string &outputFile) {
    ofstream outfile(outputFile);

    RedBlackTree tree;
    srand(time(0));

    
    for (int size = 10; size <= 10000; size += 200) {
        double totalElapsedTime = 0;

        for (int i = 0; i < 20; i++) {
            
            tree.clearTree();

            for (int j = 0; j < size; j++) {
                tree.insert(rand() % 10000);
            }

            auto start = chrono::high_resolution_clock::now();
            tree.search(rand() % 10000);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = end - start;
            totalElapsedTime += elapsed.count();
        }
        double averageTime = totalElapsedTime / 20;
        outfile << size << "," << averageTime << endl;
    }

    outfile.close();
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <archivo de salida>" << endl;
        return 1; 
    }
    
    string outputFile = argv[1];

    runAndSaveResults(outputFile);

    cout << "Resultados guardados en " << outputFile << endl;

    return 0;
}
