#include <iostream>
#include <string>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int x) {
    data = x;
    left = right = nullptr;
  }
};

class Bst {
  Node *root;

  void _print(Node *subroot) {
    if (!subroot) {
      return;
    }
    _print(subroot->left);
    cout << subroot->data << " ";
    _print(subroot->right);
  }

  void _insert(Node *&subroot, int x) {
    if (!subroot) {
      subroot = new Node(x);
    } else {
      if (x < subroot->data) {
        _insert(subroot->left, x);
      } else {
        _insert(subroot->right, x);
      }
    }
  }

  Node* _delete(Node *subroot, int x) {
    if (!subroot) return nullptr;

    if (x < subroot->data) {
      subroot->left = _delete(subroot->left, x);
    } else if (x > subroot->data) {
      subroot->right = _delete(subroot->right, x);
    } else {
      // Node found
      if (!subroot->left && !subroot->right) {
        // Case 1: No children (leaf node)
        delete subroot;
        return nullptr;
      } else if (!subroot->left) {
        // Case 2: One child (right)
        Node *temp = subroot->right;
        delete subroot;
        return temp;
      } else if (!subroot->right) {
        // Case 2: One child (left)
        Node *temp = subroot->left;
        delete subroot;
        return temp;
      } else {
        // Case 3: Two children
        Node *successor = _minValueNode(subroot->right);
        subroot->data = successor->data;
        subroot->right = _delete(subroot->right, successor->data);
      }
    }
    return subroot;
  }

  Node* _minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left) {
      current = current->left;
    }
    return current;
  }

public:
  Bst() { root = nullptr; }

  void insert(int x) { _insert(root, x); }

  void remove(int x) { root = _delete(root, x); }

  void print() { _print(root); }
};

int main() {
  Bst tree;
  tree.insert(11);
  tree.insert(13);
  tree.insert(5);
  tree.insert(7);
  tree.insert(17);

  cout << "Tree before deletion: ";
  tree.print();
  cout << endl;

  tree.remove(13);  // Delete node with two children
  tree.remove(5);   // Delete node with one child
  tree.remove(17);  // Delete leaf node

  cout << "Tree after deletion: ";
  tree.print();
  cout << endl;

  return 0;
}
