/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file. IMPORTANT: read avltree.h to understand
 * what to do in this lab.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    /**
     * TODO: your code here. Make sure the following cases are included:
     * Case 1: subtree is NULL
     * Case 2: (key, value) pair should be inserted into left subtree
     * Case 3: (key, value) pair should be inserted into right subtree
     */
    if (subtree == NULL)
        subtree = new Node(key, value);
    else {
        if (key < subtree->key) {
            insert(subtree->left, key, value);
        } else {
            insert(subtree->right, key, value);
        }
    }


    // Rebalance tree after insertion (don't remove this)
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node* node)
{
    // TODO: your code here
    // int lh = -1;
    // int rh = -1;
    // int newHeight = 0;
    //
    // if(node->left != NULL) {
    //   lh = node->left->height;
    // }
    // if(node->right != NULL) {
    //   rh = node->right->height;
    // }
    //
    // if(lh > rh) {
    //   newHeight = lh;
    // } else if (rh > lh) {
    //   newHeight = rh;
    // }
    //
    // node->height = newHeight + 1;

    int lh = height(node->left);
    int rh = height(node->right);
    int newHeight = max(lh, rh) + 1;
    node->height = newHeight;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    Node* newSubRoot = t->right;
    t->right = newSubRoot->left;
    newSubRoot->left = t;
    t = newSubRoot;

    // TODO: update the heights for t->left and t (in that order)

    updateHeight(t->left);
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    // TODO: your code here
    Node* newSubRoot = t->left;
    t->left = newSubRoot->right;
    newSubRoot->right = t;
    t = newSubRoot;

    updateHeight(t->right);
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    // TODO: your code here
    // HINT: you should make use of the other functions defined in this file,
    // instead of manually changing the pointers again
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

   // TODO: your code here
   rotateRight(t->right);
   rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    /**
      * TODO: your code here. Make sure the following cases are included:
      * Cases 1-4: the four cases of tree imbalance as discussed in lecture
      * Case 5: the tree is already balanced. You MUST still correctly update
      * subtree's height
      */

      Node* subLeft = subtree->left;
      Node* subRight = subtree->right;

      if((height(subLeft) - height(subRight) >= 2)) {
        if(height(subLeft->left) > height(subLeft->right)){
          rotateRight(subtree);
        }
        else {
          rotateLeftRight(subtree);
        }
      }

      if((height(subRight) - height(subLeft) >= 2)) {
        if(height(subRight->right) > height(subRight->left)){
          rotateLeft(subtree);
        }
        else {
          rotateRightLeft(subtree);
        }
      }

      updateHeight(subtree);

      // if(subLeft != NULL) {
      //   if(subLeft->left != NULL) {
      //     //case LL
      //     if(subLeft->right == NULL) {
      //       rotateRight(subLeft);
      //     }
      //     // case LL
      //     else if(subLeft->left->height > subLeft->right->height && (subLeft->left->height - subLeft->right->height) > 2) {
      //       rotateRight(subLeft);
      //     }
      //     // case LR
      //     else if(subLeft->right->height > subLeft->left->height && (subLeft->right->height - subLeft->left->height) > 2) {
      //       rotateLeftRight(subLeft);
      //     }
      //   }
      // }
      //
      // //case RR
      // if(subRight != NULL) {
      //   if(subRight->right != NULL) {
      //     // case RR
      //     if(subRight->left == NULL) {
      //       rotateLeft(subRight);
      //     }
      //     //Case RR
      //     else if(subRight->right->height > subRight->left->height && (subRight->right->height - subRight->left->height) > 2){
      //       rotateLeft(subRight);
      //     }
      //   }
      // }

      //predecessor = max of left subtree

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        /* Reached the node that we need to delete */
        if (subtree->left == NULL && subtree->right == NULL) {
            /* Case 1: Node to remove has no children */
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /**
             * Case 2: Node to remove has two children
             * TODO: your code here. For testing purposes, you
             * should use the PREDECESSOR.
             */

        } else {
            /* Case 3: Node to remove has one child */
            Node* curr = subtree;
            subtree = max(subtree->left, subtree->right);
            delete curr;
        }
        rebalance(subtree);
    }
}
