// 稠密图

#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 稠密图-邻接矩阵
class DenseGraph
{

private:
    int n, m;      //  n 和 m 分别存放该图的点数和边数
    bool directed; // 该bool变量用于表示是有向图还是无向图
    vector<vector<bool>> g;
    // 采用一个二维矩阵（该二维矩阵使用一个vector套vector的结构来实现）来保存。
    // 每一个位置我们存储的数据类型为 bool 型， true代表有这一条边，false代表没有这条边

public:
    // 构造函数
    DenseGraph(int n, bool directed) : n(n), m(0), directed(directed)
    {
        // 在初始化这个图的时候，他的顶点数就是他传进来的n，边数都设置为0，
        // 后面会提供函数 添加边，来逐步完善这个图的边
        for (int i = 0; i < n; i++)
        {
            g.push_back(vector<bool>(n, false));
            // 这个for循环，在它的循环过程中，g里面它要push_back一个新的vector，
            // 这个vector中保存的是 n 个 元素，每一个元素都是false；
            // 这样一来我们就创建了一个 n * n 的矩阵，矩阵中每个元素都是false
        }
    }

    ~DenseGraph()
    {
    }

    int V() { return n; } // 该函数返回图中有多少个顶点
    int E() { return m; } // 该函数返回图中有多少条边

    // 给该图添加一条边
    // 对于这个方法，我们传入 v 和 w 分别代表该要设置这条边时相对应的 顶点索引
    // 其实这里也可以观察到,对于我们一个图来说,我们的顶点使用整形来表示, 为 0 到 n-1；
    // 我们调用 addEdge(v, w) 就表示我们要在顶点 v 和 顶点 w之间添加一条边。
    void addEdge(int v, int w)
    {
        // 对于这个方法，我们首先严谨一点，
        // 利用断言来考察 v 和 w 这两个索引值都不越界
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        // 先判断 g[v][w]之间是否已经有边了
        // 有边那就直接返回，没边再继续添加
        if (hasEdge(v, w))
        {
            return;
        }

        // 然后我们就可以很安全的在 g[v][w]上让它的值为true，从而完成  v -> w 的这条边的添加
        g[v][w] = true;

        // 然后我们判断这个图是不是无向图，如果是无向图，这里我们还要添加一条 w -> v 的边
        if (directed == false)
        {
            g[w][v] = true;
        }

        // 这里隐含一个潜在的bug，那就如果此前我们已经给这两个顶点之间添加过边了
        // 虽然上面的操作不会影响，但是下面这个 m++; 边的数量加1就不合理了，
        // 所以这里我们再添加一个函数，用来判断这两个节点之间是否已经添加过边了
        m++;
    }

    // 这里可能会有疑惑，说破案是否有边，直接 g[v][w] 判断不行吗？为什么还要封装一个函数？
    // 这是因为封装函数是为了考虑到可能外部用户会希望进行两个点之间是否有边的判断，如果不提供这个函数
    // 外部用户将很难判断
    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        return g[v][w];

        // 该函数的时间复杂度为O(1)，也正是因为如此，在addEdge添加边的时候，
        // 调用该函数进行平行边的取消，
        // addEdge的时间复杂度也就是O(1)，
        // 所以，从这里可以看出，邻接矩阵对于处理平行边是有着天然的优势（基本不会付出额外的代价）
    }
};

#endif