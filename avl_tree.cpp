/**
 * AVL树的C++实现
 * AVL树，平衡二叉搜索树
 * 平衡因子，Balance Factor，用来描述AVL树左子树和右子树的高度差，取值{-1, 0, 1}
 * 为了保持AVL树的平衡状态，在插入和删除节点时，需要对AVL进行调整以满足AVL树的平衡条件
 * 调整的操作主要有四种：LL，RR，LR，RL。右旋，左旋，先左旋后右旋，先右旋后左旋
 * 其中，左旋和右旋是两个最基本的操作。
 * 参考连接：https://blog.csdn.net/qq_25343557/article/details/89110319
 */

#include <iostream>
#include <vector>

using namespace std;

// 树节点定义类
struct TreeNode
{
    TreeNode() : val(0), left(nullptr), right(nullptr), height(1) {}
    TreeNode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
    TreeNode(int v, TreeNode *left, TreeNode *right) : val(0), left(left), right(right), height(1) {}

    int val;         // 节点存储的值
    TreeNode *left;  // 左子树
    TreeNode *right; // 右子树
    int height;      // 树的高度
};

class AVLTree
{
public:
    // 构造函数 后续考虑添加拷贝构造函数
    AVLTree();

    // 构造函数 使用vector进行初始化
    AVLTree(const vector<int> &nums);

    // 添加节点操作
    void insert(int elem);

    // 删除节点操作
    bool remove(int elem);

    // 搜索一个节点并返回 如果返回为空则表示该节点不在树中
    TreeNode* search(int elem);

    // 获取树的节点数量
    int size();

    // 判断树中是否有节点
    bool empty();

    // 判断树是否平衡
    bool balance();

    // 按中序遍历打印树的各个节点
    // 对于BST，中序遍历的结果就是一个从小到大排列的数组
    void inorder();

private:
    // 添加节点操作
    TreeNode* insert(TreeNode *node, int elem);

    // 删除节点操作
    TreeNode* remove(TreeNode *node, int elem);

    // 右旋操作 LL
    // 右旋是指向左子树的左孩子中插入一个新的节点后导致当前根节点不平衡
    // 这种情况下，需要右旋操作
    // 1.获得左子树
    // 2.获得左子树的右子树
    // 3.将根节点放在左子树的右子树位置
    // 4.将原始左子树的右子树放在根节点的左子树上
    // 5.更新树的高度
    // 6.返回左子树作为新的根节点
    TreeNode* rightRotate(TreeNode *y);

    // 左旋操作 RR
    // 左旋是指向右子树的右孩子中插入一个新的节点后导致当前根节点不平衡
    // 1.获得右子树
    // 2.获得右子树的左子树
    // 3.将根节点放在右子树的左子树位置
    // 4.将原始右子树的左子树放在根节点的右子树上
    // 5.更新树的高度
    // 6.返回右子树作为新的根节点
    TreeNode* leftRotate(TreeNode *y);

    // 搜索一个节点并返回 如果返回为空则表示该节点不在树中
    TreeNode* search(TreeNode *node, int elem);

    // 计算树的高度
    int height(TreeNode *node);

    // 计算树的平衡因子
    // 平衡因子计算公式为：height(lson) - height(rson);
    // 左子树高度-右子树高度 取值仅有三个 -1，0，1
    int balanceFactor(TreeNode *node);

    // 判断某一个树节点是平衡
    bool balance(TreeNode *node);

    // 按中序遍历打印树的各个节点
    void inorder(TreeNode *node);

    TreeNode *_root;
    int _size;
};

// 类中成员函数的实现
// 构造函数1
AVLTree::AVLTree() : _root(nullptr), _size(0)
{
}

// 构造函数2
// 插入的顺序会影响树的结构，也就是树的样子可能会不同，删除同理
AVLTree::AVLTree(const vector<int> &nums) : _root(nullptr), _size(0)
{
    for (auto &num : nums)
    {
        this->insert(num);
    }
}

// 添加节点
void AVLTree::insert(int elem)
{
    _root = insert(_root, elem);
}

// 删除节点
bool AVLTree::remove(int elem)
{
    TreeNode* node = search(_root, elem);
    if (!node) return false;
    _root = remove(_root, elem);
    return true;
}

// 搜索节点
TreeNode* AVLTree::search(int elem)
{
    return search(_root, elem);
}

// 获取树的节点数量
int AVLTree::size()
{
    return _size;
}

// 判断树中是否有节点
bool AVLTree::empty()
{
    return _size == 0;
}

// 判断树是否平衡
bool AVLTree::balance()
{
    return balance(_root);
}

// 按中序遍历打印树的各个节点，递归方式
void AVLTree::inorder()
{
    inorder(_root);
    cout << endl;
}

// 添加节点操作
TreeNode* AVLTree::insert(TreeNode *node, int elem)
{
    // 如果这个节点为空，那么就新建一个节点返回
    // 此时已经走到树的叶子上了
    if (!node)
    {
        _size++;
        return new TreeNode(elem);
    }
    // 如果待插入的值比当前节点的值小，说明待插入的值理想位置应该是当前节点的左子树
    if (elem < node->val)
    {
        node->left = insert(node->left, elem);
    }
    // 如果待插入的值比当前节点的值大，说明待插入的值理想位置应该是当前节点的右子树
    else if (elem > node->val)
    {
        node->right = insert(node->right, elem);
    }
    // 注意，此处不考虑插入的值是重复的情况，也就是说，树中的各个节点的值都不相同

    // 更新node的高度 当前节点的高度应该是左子树和右子树中较大的那个加1
    node->height = 1 + max(height(node->left), height(node->right));

    // 计算平衡因子，看是否需要进行调整
    int bf = balanceFactor(node);
    // 根据得到的平衡因子进行调整 一定要记住，左旋和右旋都是针对根节点的
    // 首先，考虑插入节点的位置，共有四种情况：
    // 1.左子树的左子树 根节点的BF=2  左子树的BF>0 RR 右旋
    // 2.左子树的右子树 根节点的BF=2  左子树的BF<0 LR 先左旋再右旋
    // 3.右子树的左子树 根节点的BF=-2 右子树的BF>0 RL 先右旋再左旋
    // 4.右子树的右子树 根节点的BF=-2 右子树的BF<0 LL 左旋
    // LL
    if (bf > 1 && balanceFactor(node->left) > 0)
    {
        return rightRotate(node);
    }
    // RR
    if (bf < -1 && balanceFactor(node->right) < 0)
    {
        return leftRotate(node);
    }
    // LR
    if (bf > 1 && balanceFactor(node->left) < 0)
    {
        // 先对左子树进行左旋 转换为LL的情况 完成后根节点就应该是插入的节点也就是原始左子树的右子树
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (bf < -1 && balanceFactor(node->right) > 0)
    {
        // 先对右子树进行右旋 转换为RR的情况
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 删除节点操作
TreeNode* AVLTree::remove(TreeNode *node, int elem)
{
    // 如果当前的节点为空，说明这个树中没有需要删除的元素 删除失败 ？？这里似乎有点问题
    if (!node) return nullptr;
    TreeNode *ret = nullptr;
    // 如果待删除的值比当前节点小，则理想位置是在当前节点的左子树上
    if (elem < node->val)
    {
        node->left = remove(node->left, elem);
        ret = node;
    }
    // 如果带删除的值比当前节点小，则理想位置是在当前节点的右子树上
    else if (elem > node->val)
    {
        node->right = remove(node->right, elem);
        ret = node;
    }
    else // 当前的节点就是待删除的节点
    {
        // 如果左子树为空，那需要保留右子树并对右子树进行重新平衡
        if (!node->left)
        {
            TreeNode *right_node = node->right;
            node->right = nullptr;
            _size--;
            // 为什么不再外层直接_size--?
            // 因为后面两个子树都不为空的时候会进行一个交换的操作，交换的时候会进行一个删除的操作
            // 此时待删除的节点的左子树或者右子树的节点必然有一个为空，这个时候再减1，可以保持正确
            ret = right_node;
        }
        // 如果右子树为空，那需要保留左子树并对左子树进行重新平衡
        else if (!node->right)
        {
            TreeNode *left_node = node->left;
            node->left = nullptr;
            _size--;
            ret = left_node;
        }
        // 如果两个树都不为空 此时由于根节点需要删除，要找一个代替根节点的
        // 方法是寻找根节点左子树中的最大节点，让这个节点顶替根节点
        // 然后将这个节点在左子树中删除
        // !!! 这里删除节点的方式有两种，一种是从左子树找最大的那个，另一种是从右子树找最小的那个
        // !!! 默认使用从左子树找最大的那个，为了和这个演示网站保持一致:
        // https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
        else
        {
            TreeNode *mleft = node->left;
            while (mleft->right) mleft = mleft->right;
            mleft->left = remove(node->left, mleft->val);
            mleft->right = node->right;
            node->left = nullptr;
            node->right = nullptr;
            ret = mleft;

            // TreeNode *mright = node->right;
            // while (mright->left) mright = mright->left;
            // mright->right = remove(node->right, mright->val);
            // mright->left = node->left;
            // node->left = nullptr;
            // node->right = nullptr;
            // ret = mright;
        }
    }

    if (!ret) return nullptr;

    // 更新AVL树的平衡状态使之重新平衡
    // 更新树的高度
    ret->height = 1 + max(height(ret->left), height(ret->right));

    // 计算平衡因子
    int bf = balanceFactor(ret);
    // LL
    if (bf > 1 && balanceFactor(ret->left) >= 0)
    {
        return rightRotate(ret);
    }
    // RR
    if (bf < -1 && balanceFactor(ret->right) <= 0)
    {
        return leftRotate(ret);
    }
    // LR
    if (bf > 1 && balanceFactor(ret->left) < 0)
    {
        ret->left = leftRotate(ret->left);
        return rightRotate(ret);
    }
    // RL
    if (bf < -1 && balanceFactor(ret->right) > 0)
    {
        ret->right = rightRotate(ret->right);
        return leftRotate(ret);
    }

    return ret;
}

// 右旋操作
TreeNode* AVLTree::rightRotate(TreeNode *y)
{
    TreeNode *x = y->left;
    TreeNode *t3 = x->right;
    x->right = y;
    y->left = t3;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// 左旋操作
TreeNode* AVLTree::leftRotate(TreeNode *y)
{
    TreeNode *x = y->right;
    TreeNode *t2 = x->left;
    x->left = y;
    y->right = t2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// 搜索一个节点并返回 如果返回为空则表示该节点不在树中
TreeNode* AVLTree::search(TreeNode *node, int elem)
{
    if (!node) return nullptr;
    if (node->val == elem) return node;
    // 下面的查找方法利用了的BST的性质
    return node->val > elem ? search(node->left, elem) : search(node->right, elem);
}

// 计算树的高度
int AVLTree::height(TreeNode *node)
{
    if (!node) return 0;
    return node->height;
}

// 计算树的平衡因子
int AVLTree::balanceFactor(TreeNode *node)
{
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

// 判断某一个树节点是平衡
bool AVLTree::balance(TreeNode *node)
{
    if (!node) return true;
    return abs(balanceFactor(node)) <= 1 && balance(node->left) && balance(node->right);
}

// 按中序遍历打印树的各个节点，递归方式
void AVLTree::inorder(TreeNode *node)
{
    if (!node) return;
    inorder(node->left);
    cout << node->val << " ";
    inorder(node->right);
}

int main(int argc, char *argv[])
{
    AVLTree *t1 = new AVLTree();
    t1->insert(1);
    t1->insert(3);
    t1->insert(2);
    t1->insert(-1);
    cout << t1->balance() << endl;
    t1->inorder();
    cout << (t1->search(3) != nullptr) << endl;
    cout << (t1->search(4) != nullptr) << endl;
    cout << t1->size() << endl;
    t1->remove(3); // 删除节点操作还有问题
    t1->inorder(); // 按中序遍历打印
    t1->remove(-1);
    t1->inorder();

    vector<int> nums1 = { 9, 0, 2, -8, 33, 7, 3, 1 };
    AVLTree *t2 = new AVLTree(nums1);
    t2->inorder();
    cout << t2->remove(-7) << endl;
    cout << t2->size() << endl;
    cout << t2->remove(2) << endl;
    t2->inorder();
    cout << t2->size() << endl;
    cout << t2->balance() << endl;
}