Binary Search Tree:
                  A Binary Search Tree (BST) is a special type of binary tree where each node follows the BST property:
                                                             Left Side: Contains nodes with values less than the parent node.
                                                             Right Side: Contains nodes with values greater than the parent node.
                                                             This rule applies recursively to all nodes in the tree.
         11
       /   \
      5     13
       \       \
        7       17


In this tree, the root is 20. Nodes in the left subtree (10, 5, 15) are less than 20, and nodes in the right subtree (30, 35) are greater. This structure makes the BST efficient for operations like search and modification.

**NODE DELETION**
1.Deleting a leaf node (node with no children).
2.Deleting a node with one child.
3.Deleting a node with two children.

*Leaf Node: A node with no children is straightforward to delete. The node is simply removed without affecting other nodes.
     11       
   /   \                  Node 7 has no children, making it a leaf node.
  5     13
           \
            17
*Deleting a node with one child:
                                 Node 13 has one child (17).
                                 Replace node 13 with its child (17). 
                                   
    11
   /   \
  5     17

*Deleting a node with two children:
                                    Node 11 has two children (5 and 13).


