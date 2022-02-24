#ifndef __BST_H__
#define __BST_H__

#include <iostream>
#include <queue>
#include <cassert>

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

    // 拷贝构造函数
    Node(Node *node)
    {
      this->key = node->key;
      this->value = node->value;
      this->left = node->left;
      this->right = node->right;
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

  // 广度优先遍历(层序遍历)
  void levelOrder()
  {
    // 广度优先遍历需要一个队列进行辅助，这里声明一个队列q，它存储的是Node*
    std::queue<Node *> q;
    // 然后将我们的根节点入队
    q.push(root);
    // 在我们的队列q不为空的时候进行循环
    while (!q.empty())
    {
      // 每次循环首先需要取出队首的元素
      Node *node = q.front();
      // 之后就可以让这个队首的元素出队（从队列中删除）
      q.pop();

      // 接下来要做的事情就是对我们刚刚拿出来的node节点进行操作
      std::cout << node->key << std::endl;

      // 然后，看node是否有左右孩子，如果有，那就将左右孩子入队
      if (node->left != nullptr)
      {
        q.push(node->left);
      }
      if (node->right != nullptr)
      {
        q.push(node->right);
      }

      // 之后这个循环继续进行，直到我们的队列为空
    }
  }

  // 寻找最小键值
  Key minimum()
  {
    // 找二叉树的最小值，那么首先我们得保证二叉树不为空
    assert(count != 0);
    // 依然使用递归的方式来寻找最小值
    // 传入根节点开始寻找key最小的值，返回的是哪个最小key值的node节点
    Node *minNode = minimum(root);
    return minNode->key;
  }

  // 寻找最大键值
  Key maxmum()
  {
    // 找二叉树的最大值，那么首先我们得保证二叉树不为空
    assert(count != 0);
    // 依然使用递归的方式来寻找最大值
    // 传入根节点开始寻找key最大的值，返回的是哪个最大key值的node节点
    Node *maxNode = maxmum(root);
    return maxNode->key;
  }

  // 从二叉搜索树中删除最小键值所在的节点
  void removeMin()
  {
    // 首先，这个函数只在根不为空的情况下才做具体的事情
    if (root)
      root = removeMin(root);
    // 同样的，这里调用一个递归函数，这个函数将删除以root节点为根的这个二叉树中最小的那个key的节点
    // 之后将新的根传回来
  }

  // 从二叉搜索树中删除最大键值所在的节点
  void removeMax()
  {
    // 首先，这个函数只在根不为空的情况下才做具体的事情
    if (root)
      root = removeMax(root);
    // 同样的，这里调用一个递归函数，这个函数将删除以root节点为根的这个二叉树中最大的那个key的节点
    // 之后将新的根传回来
  }

  // 从二叉搜索树中删除键值为key的节点
  void remoce(Key key)
  {
    // 调用一个递归函数，该函数首先尝试从root中删除键值为key的节点
    // 最终将删除的结果再返回给root
    root = remove(root, key);
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

  // 以node为根的二叉搜索树中，返回最小键值的节点
  Node *minimum(Node *node)
  {
    // 首先判断传入的这个node节点他的左孩子是否为空，如果是空，表示它没有左孩子，那么他就是这个最小节点，直接返回node
    if (node->left == nullptr)
    {
      return node;
    }

    // 否者就递归的传入他的左孩子，去向以node左孩子为根的这个树去找它的最小节点
    return minimun(node->left);
  }

  // 以node为根的二叉搜索树中，返回最大键值的节点
  Node *maxmum(Node *node)
  {
    // 首先判断传入的这个node节点他的右孩子是否为空，如果是空，表示它没有右孩子，那么他就是这个最大节点，直接返回node
    if (node->right == nullptr)
    {
      return node;
    }

    // 否者就递归的传入他的右孩子，去向以node右孩子为根的这个树去找它的最大节点
    return maxmum(node->right);
  }

  // 删除掉以node节点为根的二叉搜索树中最小的节点
  // 返回删除节点后新的二分搜索树的根
  Node *removeMin(Node *node)
  {
    // 首先我们要来看单前这个节点他的左孩子是否已经为空了。如果为空，表示它就是那个最小节点
    if (node->left == nullptr)
    {
      // 这个时候就需要看单前节点是否存在右节点
      // 其实存不存在这里我们的操作都一样，都是将他的右节点作为根节点返回回去
      Node *rightNode = node->right;
      delete node;
      count--;
      return rightNode;
    }

    // 否者就表示单前节点不是最小节点，继续递归进单前这个node的左孩子去找树的最小节点并删除
    // 然后将删除的那个节点返回的新的左孩子赋回给这个node的左孩子
    node->left = removeMin(node->left);
    return node;
  }

  // 删除掉以node节点为根的二叉搜索树中最大的节点
  // 返回删除节点后新的二分搜索树的根
  Node *removeMax(Node *node)
  {
    // 首先我们要来看单前这个节点他的右孩子是否已经为空了。如果为空，表示它就是那个最大节点
    if (node->right == nullptr)
    {
      // 这个时候就需要看单前节点是否存在左节点
      // 其实存不存在这里我们的操作都一样，都是将他的左节点作为根节点返回回去
      // 不存在就返回空
      Node *leftNode = node->left;
      delete node;
      count--;
      return leftNode;
    }

    // 否者就表示单前节点不是最大节点，继续递归进单前这个node的左孩子去找树的最大节点并删除
    // 然后将删除的那个节点返回的新的右孩子赋回给这个node的右孩子
    node->right = removeMax(node->right);
    return node;
  }

  // 删除掉以node为根的二分搜索树中键值为key的节点
  // 返回删除节点后新的二分搜索树的根
  Node *remove(Node *node, Key key)
  {
    // 首先在这个函数中，首先包含了寻找这个键值为key的节点的过程
    if (node == nullptr)
    {
      // 表示在这颗树中没有找到键值为key的节点
      return nullptr;
    }

    // 我们要找到的这个key和单前它这个node中的key做一个比较
    if (key < node->key)
    {
      // 如果小于单前node的key，那么就需要递归的进一步在node的左孩子中去查找和这个key节点并且将它删除
      // 将删除后的节点赋值回来给单前node的左孩子
      node->left = remove(node->left, key);
      // 这样一来我们就成功的删除了这个node节点，将这个node节点返回回去
      return node;
    }
    else if (key > node->key)
    {
      // 我们发现key大于单前node的key，那么就需要递归的进一步在node的右孩子中去查找和这个key节点并且安静他删除
      // 将删除返回的根节点赋值给单前node的右孩子
      node->right = remove(node->right, key);
      return node;
    }
    else // key == node->key
    {
      // 否者的haul就是找到了这个等于key的节点
      // 首先我们先看一下node到底有几个孩子？
      // 如果node只有右孩子
      if (node->left == nullptr)
      {
        Node *rightNode = node->right;
        delete node;
        count--;
        return rightNode;
      }
      if (node->right == nullptr)
      {
        Node *leftNode = node->left;
        delete node;
        count--;
        return leftNode;
      }

      // 走到这里，表示node它左右孩子都是存在的
      // node->left != nullptr && node->right != nullptr
      // 接着就在这个待删除节点node的右子树中找那个最小值,作为要删除节点node的后继节点（替代节点）
      // Node* successor = minmum(node->right);
      // 根据node的右子树的最小值拷贝构造一个node节点，赋值给我们的后继节点
      // 这里为什么不直接用返回的那个最小值节点，而需要拷贝构造一个新的Node节点？见下
      Node *successor = new Node(minmum(node->right));
      // 这里我们新建立了这个node节点，放入二叉树中，所以count++
      count++; // 这里不用担心count值不对，因为下面removeMin里面会把那个最小节点给抹除，计数会减一
      // 这里加1，那里减1，正好维持了正确的计数

      // 接下来做的事情就是为我们要删除节点的后继节点的左右节点进行赋值
      // 其中右孩子就是我们removeMin移除最小值之后返回回来的这个节点指针
      // 这里需要注意使用c++写这个的一个陷阱，我们的successor在上面那句代码中，指向了node的右子树的最小值
      // 而我们下面这句代码（removeMin）又将node右子树的最小值给删除了，
      // 这里需要注意，单这个节点给删除了以后，我们这个 successor 指向也就相对应的失败了。
      // 怎么解决这个问题呢？
      // 就是在上面那个代码里，将node右子树里最小值复制一份，（为了完成这个赋值，需要Node结构体提供一个拷贝构造函数）
      successor->right = removeMin(node->right);

      // 相应的后继节点的左孩子赋值就很简单了，直接就是我的删除节点的左孩子
      successor->left = node->left;

      // 当我们这样做好之后，就可以放心的删除我们的那个节点了
      delete node;
      count--;

      // 同时将 后继节点successor返回回去作为删除节点后，这个新的二叉搜索树的根节点返回给原来node节点他的父节点
      return successor;
    }
  }
};

#endif