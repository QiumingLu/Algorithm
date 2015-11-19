#include <vector>
#include <stack>

struct TreeNode {
  int value;
  TreeNode* left;
  TreeNode* right;
};

//三种递归遍历

//前序遍历
void preorder(TreeNode* root, std::vector<int>& v) {
  if (root != NULL) {
    v.push_back(boot->value);
    preorder(root->left, v);
    preorder(root->right, v);
  }
}

//中序遍历
void inorder(TreeNode* root, std::vector<int>& v) {
  if (root != NULL) {
    inorder(root->left, v);
    v.push_back(root->value);
    inorder(root->right, v);
  }
}

//后续遍历
void postorder(TreeNode* root, std::vector<int>& v) {
  if (root != NULL) {
    postorder(root->left, v);
    postorder(root->right, v);
    v.push_back(root->value);
  }
}

//非递归前序遍历
void preorderTraversal(TreeNode* root, std::vector<int>& v) {
  std::stack<TreeNode*> st;
  TreeNode* p = root;
  while (p != NULL || !st.empty()) {
    while(p != NULL) {
      v.push_back(p->value);
      st.push(p);
      p = p->left;
    }
    if (!st.empty()) {
      p = st.top();
      st.pop();
      p = p->right;
    }
  }
}

//非递归中序遍历
void inorderTraversal(TreeNode* root, std::vector<int>& v) {
  std::stack<TreeNode*> st;
  TreeNode* p = root;
  while (p != NULL || !st.empty()) {
    while(p != NULL) {
      st.push(p);
      p = p ->left;
    }
    if (!st.empty()) {
      p = st.top();
      st.pop();
      v.push_back(p->value);
      p = p ->right;
    }
  }
}

//非递归后序遍历
struct TempNode {
  TreeNode* btnode;
  bool isFirst;	
  TempNode() {}
  TempNode(TreeNode* p, bool isF = true) : btnode(p), isFirst(isF) {}
};
void postorderTraverse(TreeNode* root, std::vector<int>& v) {
  std::stack<TempNode*> st;
  TreeNode* p = root;
  TempNode* temp;

  while (p != NULL || !st.empty()) {
    while (p != NULL) {
      TempNode* tempNode = new TempNode(p);
      st.push(tempNode);
      p = p->left;
    }
    if (!st.empty()) {
      temp = st.top()
        st.pop();
      if (temp->isFirst) {
        temp->isFirst = false;
        s.push(temp);
        p = temp->btnode->right;
      } else {
        v.push_back(temp->btnode->value);
        p = NULL;
      }
    }
  }
}
