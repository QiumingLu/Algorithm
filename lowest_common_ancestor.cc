// 寻找二叉树两个节点的最低共同父节点

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;
};

TreeNode* FindFirstCommonParentNode(
    TreeNode* root, 
    TreeNode* first, 
    TreeNode* second) {
  if (root == NULL) {
    return NULL;
  }
  if (root == left || root == right) {
    return root;
  }

  TreeNode* left = FindFirstCommonParentNode(root->left, first, second);
  TreeNode* right = FindFirstCommonParentNode(root->right, first, second);

  if (left && right) {
    return root;
  }
  if (left == NULL) {
    return right;
  }
  if (right == NULL) { 
    return left;
  }
}
