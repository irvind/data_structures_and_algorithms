#include <stdlib.h>

typedef struct BST_Node {
    int key;
    char *value;
    struct BST_Node *left;
    struct BST_Node *right;
} BST_Node;

typedef struct BinarySearchTree {
    BST_Node *root;
} BinarySearchTree;

BinarySearchTree* create_binary_search_tree() {
    BinarySearchTree *tree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    return tree;
}

typedef struct BST_FindNodeResult {
    BST_Node *node;
    BST_Node *parent_node;
} BST_FindNodeResult;

void free_binary_search_tree(BinarySearchTree *tree) {
    // TODO: free nodes

    free(tree);
}

BST_Node* create_bst_node(int key, char *value, BST_Node *left, BST_Node *right) {
    BST_Node *node = (BST_Node*)malloc(sizeof(BST_Node));
    node->key = key;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

void free_bst_node(BST_Node *node) {
    free(node);
}

void bst_set(BinarySearchTree *tree, int key, char *value) {
    if (tree->root == NULL) {
        tree->root = create_bst_node(key, value, NULL, NULL);
        return;
    }

    BST_Node *node = tree->root;
    while (node != NULL) {
        if (node->key == key) {
            // TODO: free previous value
            node->value = value;
            return;
        } else if (key > node->key) {
            if (node->right == NULL) {
                node->right = create_bst_node(key, value, NULL, NULL);
                return;
            }
            node = node->right;
        } else if (key < node->key) {
            if (node->left == NULL) {
                node->left = create_bst_node(key, value, NULL, NULL);
                return;
            }
            node = node->left;
        }
    }
}

BST_FindNodeResult bst_find_node(BinarySearchTree *tree, int key) {
    BST_FindNodeResult result;
    result.node = tree->root;
    result.parent_node = NULL;

    while (result.node != NULL) {
        if (result.node->key == key) {
            return result;
        } else if (key > result.node->key) {
            result.parent_node = result.node;
            result.node = result.node->right;
        } else {    // key < node->key
            result.parent_node = result.node;
            result.node = result.node->left;
        }
    }

    result.parent_node = NULL;
    return result;
}

char* bst_search(BinarySearchTree *tree, int key) {
    BST_FindNodeResult result = bst_find_node(tree, key);
    if (result.node != NULL) {
        return result.node->value;
    }
    return NULL;
}

void _bst_update_parent_child(BST_Node *parent_node, BST_Node *node, int set_left) {
    if (set_left) {
        parent_node->left = node;
    } else {
        parent_node->right = node;
    }
}

BST_FindNodeResult _bst_find_largest_key_node(BST_Node *node, BST_Node *parent_node) {
    BST_FindNodeResult result;
    result.node = node;
    result.parent_node = parent_node;
    while (result.node->right != NULL) {
        result.parent_node = result.node;
        result.node = result.node->right;
    }

    return result;
}

int _bst_nullify_subtree(BST_Node *node, BST_Node *subtree_node) {
    if (subtree_node == NULL) {
        return 0;
    } else if (node->left == subtree_node) {
        node->left = NULL;
        return 1;
    } else if (node->right == subtree_node) {
        node->right = NULL;
        return 1;
    } else {
        return 0;
    }
}

int bst_delete(BinarySearchTree *tree, int key) {
    if (tree->root == key) {
        // TODO
        return 1;
    }

    BST_FindNodeResult find_result = bst_find_node(tree, key);
    if (find_result.node == NULL) {
        return 0;
    }

    BST_Node *node = find_result.node;
    BST_Node *parent_node = find_result.parent_node;
    int is_left_subtree = parent_node->left == node ? 1 : 0;
    if (node->left == NULL && node->right == NULL) {
        _bst_update_parent_child(parent_node, NULL, is_left_subtree);
    } else if (node->left != NULL && node->right == NULL) {
        _bst_update_parent_child(parent_node, node->left, is_left_subtree);
    } else if (node->left == NULL && node->right != NULL) {
        _bst_update_parent_child(parent_node, node->right, is_left_subtree);
    } else {    // node->left != NULL && node->right != NULL
        find_result = _bst_find_largest_key_node(node->left, node);
        BST_Node *largest_left_node = find_result.node;
        BST_Node *largest_left_node_parent = find_result.parent_node;

        _bst_nullify_subtree(largest_left_node_parent, largest_left_node);
        _bst_update_parent_child(parent_node, largest_left_node, is_left_subtree);
        if (largest_left_node->left != NULL)  {
            _bst_update_parent_child(largest_left_node_parent, largest_left_node->left, 0);
        }
        largest_left_node->left = node->left;
        largest_left_node->right = node->right;

        // TODO: fix error
    }
    free_bst_node(node);

    return 0;
}

void binary_search_tree_test() {

}
