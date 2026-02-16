tree *findBrother(tree *root, int key)
{
    while (root) {
        if (key < root->key) root = root->left;
        else if (key > root->key) root = root->right;
        else break;
    }
    if (!root) return 0;

    tree *p = root->parent;
    if (!p) return 0;

    if (p->left == root) return p->right ? p->right : 0;
    if (p->right == root) return p->left ? p->left : 0;

    return 0;
}

