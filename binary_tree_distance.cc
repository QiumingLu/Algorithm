//编程之美3.8：求二叉树中节点的最大距离

//如果把二叉树看成一个图，父子节点之间的连线看成是双向的，定义“距离”为两个节点之间边的个数。
//写一个程序求一棵二叉树中相距最远的两个节点之间的距离。

//1 分析

//二叉树中节点的最大距离必定是两个叶子节点的距离。求某个子树的节点的最大距离，有三种情况：
//1.两个叶子节点都出现在左子树；2.两个叶子节点都出现在右子树；3.一个叶子节点在左子树，一个叶子节点在右子树。
//只要求得三种情况的最大值，结果就是这个子树的节点的最大距离。

//int find_max_len(Node *root);

//case 1: 两个叶子节点都出现在左子树。find_max_len(root->pLeft);

//case 2: 两个叶子节点都出现在右子树。find_max_len(root->pRight);

//case 3: 一个出现在左子树，一个出现在右子树。distance(root->pLeft) + distance(root->pRight) + 2;
//其中，distance()计算子树中最远的叶子节点与根节点的距离，其实就是左子树的高度减1。

//实现

struct  Node {
  int data;
  Npde* pLeft;
  Node* pRight;
};

int height(Node* root) {
  if (root == NULL) {
    return 0;
  }
  return max(height(root->pLeft), height(root->pRight)) + 1;
}

int find_max_len(Node* node) {
  if (root == NULL) {
    return 0;
  }

  int lmax = find_max_len(root->pLeft);     // left tree max len;
  int rmax = find_max_len(root->pRight);    // right tree max len;

  int lh = 0, rh = 0;
  if (root->pLeft) {
    lh = height(root->pLeft);
  }
  if (root->pRight) {
    rh = height(root->pRight);
  }

  return max(max(lmax, rmax), lh + rh);
}
