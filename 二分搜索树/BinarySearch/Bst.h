#ifndef __BST_H__
#define __BST_H__

#include <iostream>

// BinarySearchTree (二叉搜索树)
template <typename Key, typename Value>
class BST
{

private:
  // 这个私有的Node结构就是二叉搜索树里的节点
  struct Node
  {
    Key key;     // 查找表的 key
    Value value; // 查找表的 value
    Node *left;  // 该节点的左孩子节点
    Node *right; // 该节点的右孩子节点

    // 这个结构体的构造函数
    Node(Key k, Value v)
    {
      this->key = k;
      this->value = v;
      this->left = this->right = nullptr;
    }
  };

  // 对于我们这整棵树来说，他需要有一个根节点
  Node *root;
  int count; // 存储我们这棵二分搜索树有多少个节点

public:
  // 构造函数
  BST()
  {
    root = nullptr;
    count = 0;
  }

  // 析构函数
  ~BST()
  {
    destroy(root);
  }

  // 获取节点数
  int size()
  {
    return count;
  }

  // 判空函数
  bool isEmpty()
  {
    return count == 0;
  }

  // 往二叉搜索树中插入一个新的键值对
  void insert(Key key, Value value)
  {
    // 在这个函数这里调用一个insert的重载版本(写法随意，看自己习惯)
    // 这里调用这个函数传入的参数，
    // root节点，表示这个insert动作从root这个根节点那开始插入这个key-value
    // 然后这个insert函数它也有返回值，返回的就是我们插入这个到的这个二叉搜索树的根
    root = insert(root, key, value);
  }

  // 查看二叉搜索树中是否包含key这个键
  bool contain(Key key)
  {
    // 传入一个节点，查找以这个节点为根的二叉搜索树中是否包含key
    // 那这里就是从根节点root开始查找
    return contain(root, key);
  }

  Value *search(Key key)
  {
    return search(root, key);
  }

  // 前序遍历
  void preOrder()
  {
    // 这里依旧调用私有的preorder函数，传入一个根节点root表示从根节点进行前序遍历
    preOrder(root);
  }

  // 中序遍历
  void inOrder()
  {
    inOrder(root);
  }

  // 后续遍历
  void postOrder()
  {
    postOrder(root);
  }

private:
  // 向以node为根节点的二叉搜索树中，插入节点（key,value）
  // 返回的是插入新节点后的二叉搜索树的根（返回回去的目的就是为了做上一级的左子树或者右子树的根）
  Node *insert(Node *node, Key key, Value value)
  {
    if (node == nullptr)
    {
      // 传入的这个node节点为kong，就表示这个位置就是我们需要插入的这个新节点的位置
      // 这个时候我们的节点计数器count++
      count++;
      return new Node(key, value);
      // 这个时候我们就可以理解成，对于插入完成后要返回的这个二叉搜索树的根，就是我们新创建的这个Node节点
    }

    // 之后我们要做的要么是修改node节点的value，要么是给node添加新的左子树或者新的右子树

    if (key == node->key)
    {
      node->value = value;
    }
    else if (key < node->key)
    {
      // 往node的左子树插入
      // 插入节点之后，返回的这个节点的根，就应该重新赋值给这个node节点的左孩子节点
      node->left = insert(node->left, key, value);
    }
    else
    {
      // 往node节点的右子树插入
      node->right = insert(node->right, key, value);
    }

    // 最后我们返回的任然是这个处理过的node
    return node;
  }

  // 在以node为根的二叉搜索树中来查找是否包含有键值为key的节点
  bool contain(Node *node, Key key)
  {
    // 如果我们单前访问的节点已经为空了的话，就表示找不到等于key的节点，
    // 返回false
    if (node == nullptr)
    {
      return false;
    }

    // 如果这个key == 单前node的key，那么就说明找到这个键值为key的节点，返回true
    if (key == node->key)
    {
      return true;
    }
    // 如果key小于node的key,我们相对应的就应该递归进去这个node节点中相对应的左子树中去查找
    else if (key < node->key)
    {
      return contain(node->left, key);
    }
    else // 如果key大于node的key,我们相对应的就应该递归进去这个node节点中相对应的右子树中去查找
    {
      return contain(node->right, key);
    }
  }

  // 在以node为根的二叉搜索树中来查找是否包含有键值为key的节点
  // 如果找到该节点，就返回该节点的Value指针
  // 没找到就返回空指针
  Value *search(Node *node, Key key)
  {
    if (node == nullptr)
    {
      return nullptr;
    }

    if (node->key == key)
    {
      return &(node->value);
    }
    else if (node->key < key)
    {
      return search(node->right, key);
    }
    else
    {
      return search(node->left, key);
    }
  }

  // 前序遍历
  // 对以node为根的二叉搜索树进行前序遍历
  void preOrder(Node *node)
  {
    if (node != nullptr)
    {
      std::cout << node->key << std::endl;
      preOrder(node->left);
      preOrder(node->right);
    }
  }

  // 中序遍历
  // 对以node为根的二叉搜索树进行中序遍历
  void inOrder(Node *node)
  {
    if (node != nullptr)
    {
      inOrder(node->left);
      std::cout << node->key << std::endl;
      inOrder(node->right);
    }
  }

  // 后续遍历
  // 对以node为根的二叉搜索树进行后序遍历
  void postOrder(Node *node)
  {
    if (node != nullptr)
    {
      postOrder(node->left);
      postOrder(node->right);
      std::cout << node->key << std::endl;
    }
  }

  // 采用后续遍历的方式对二叉搜索树的所有节点进行释放
  void destroy(Node *node)
  {
    if (node != nullptr)
    {
      destroy(node->left);
      destroy(node->right);

      delete node;
      count--;
    }
  }
};

#endif