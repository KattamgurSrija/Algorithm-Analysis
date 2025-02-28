#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <random>

using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class BST {
private:
    Node *root;
    bool useSuccessor;  // Toggle for symmetric deletion

    void _insert(Node *&node, int x) {
        if (!node) {
            node = new Node(x);
        } else {
            if (x < node->data) _insert(node->left, x);
            else _insert(node->right, x);
        }
    }

    Node* _minValueNode(Node *node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* _maxValueNode(Node *node) {
        while (node->right) node = node->right;
        return node;
    }

    Node* _asymmetricDelete(Node *node, int x) {
        if (!node) return node;

        if (x < node->data)
            node->left = _asymmetricDelete(node->left, x);
        else if (x > node->data)
            node->right = _asymmetricDelete(node->right, x);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            Node *successor = _minValueNode(node->right);
            node->data = successor->data;
            node->right = _asymmetricDelete(node->right, successor->data);
        }
        return node;
    }

    Node* _symmetricDelete(Node *node, int x) {
        if (!node) return node;

        if (x < node->data)
            node->left = _symmetricDelete(node->left, x);
        else if (x > node->data)
            node->right = _symmetricDelete(node->right, x);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;

            if (useSuccessor) {
                Node *successor = _minValueNode(node->right);
                node->data = successor->data;
                node->right = _symmetricDelete(node->right, successor->data);
            } else {
                Node *predecessor = _maxValueNode(node->left);
                node->data = predecessor->data;
                node->left = _symmetricDelete(node->left, predecessor->data);
            }
            useSuccessor = !useSuccessor;  // Toggle for next deletion
        }
        return node;
    }

    int _ipl(Node *node, int depth = 0) {
        if (!node) return 0;
        return depth + _ipl(node->left, depth + 1) + _ipl(node->right, depth + 1);
    }

public:
    BST() {
        root = nullptr;
        useSuccessor = true;
    }

    void insert(int x) { _insert(root, x); }

    void asymmetricDelete(int x) { 
        if (!root) return;  // Prevent deleting from an empty tree
        root = _asymmetricDelete(root, x); 
    }

    void symmetricDelete(int x) { 
        if (!root) return;  // Prevent deleting from an empty tree
        root = _symmetricDelete(root, x); 
    }

    int computeIPL() { return _ipl(root); }
};

void runExperiment(int treeSize, int numPairs, bool isSymmetric, const string &filename) {
    BST tree;
    set<int> keys;  // Store unique keys
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10 * treeSize);

    // Initial population of tree
    while (keys.size() < treeSize) {
        int val = dist(gen);
        if (keys.insert(val).second) tree.insert(val);
    }

    // Open file for recording IPL data
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << "Step,IPL\n";

    // Initial IPL before insert/delete cycles
    file << "0," << tree.computeIPL() << "\n";

    // Insertion and Deletion cycles
    for (int i = 1; i <= numPairs; i++) {
        int insertKey = dist(gen);
        int deleteKey;
        
        if (keys.empty()) continue;  // Prevent deleting from an empty tree

        // Ensure `deleteKey` exists before attempting deletion
        auto it = next(keys.begin(), rand() % keys.size());
        deleteKey = *it;

        // Insert new key
        tree.insert(insertKey);
        keys.insert(insertKey);

        // Delete a key using the selected strategy
        if (isSymmetric)
            tree.symmetricDelete(deleteKey);
        else
            tree.asymmetricDelete(deleteKey);

        keys.erase(deleteKey);

        // Record IPL
        file << i << "," << tree.computeIPL() << "\n";

        // Debugging output (optional)
        if (i % 1000 == 0) {
            cout << "Step " << i << " completed. IPL: " << tree.computeIPL() << endl;
        }
    }

    file.close();
}

int main() {
    vector<int> treeSizes = {64, 128, 256};
    int numPairs = 5000;  // Reduced for performance

    for (int size : treeSizes) {
        cout << "Running experiment for asymmetric deletion with size: " << size << endl;
        runExperiment(size, numPairs, false, "asymmetric_" + to_string(size) + ".csv");
        
        cout << "Running experiment for symmetric deletion with size: " << size << endl;
        runExperiment(size, numPairs, true, "symmetric_" + to_string(size) + ".csv");
    }

    cout << "Experiments complete! Check the CSV files for IPL data.\n";
}
