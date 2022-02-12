//
// 对于有权图中的统一的 边 类
//

#ifndef MINIMUMSPANTREE_EDGE_H
#define MINIMUMSPANTREE_EDGE_H

#include <iostream>
#include <cassert>

using namespace std;

// 首先对于我们每一个边，他的权值类型是不固定的，有可能是bool型，有可能是int型，等等等等
// 所以这里我们使用模板类来进行边的设计
template <typename Weight>
class Edge
{
private:
  // 对于我们设计的这个类，我这里希望它能同时表达有向边和无向边
  // 对于有向边，那么我们就设置为a指向b，对于无向边，那么a,b的顺序就不重要
  int a, b;
  Weight weight;

public:
  Edge(int a, int b, Weight weight)
  {
    this->a = a;
    this->b = b;
    this->weight = weight;
  }

  Edge() {}

  ~Edge() {}

public:
  // 为了让外部用户能够获得边的相关信息，这里提供几个方法

  // 获取顶点1（对于有向图来说是起始点）
  int v() { return a; }

  // 获取顶点2（对于无向图来说是终点）
  int w() { return b; }

  // 获取边的权重
  Weight wt() { return weight; }

  // 有些时候我们知道边的一个顶点，我们想通过这个顶点获取边的另外一个顶点
  int other(int x)
  {
    // 严谨期间，具体返回之前需要检查x的合法性
    assert(x == a || x == b);
    return x == a ? b : a;
  }

  // 对Edge这个类这里我们做几个重载
  // 重载输出运算符 <<
  friend ostream &operator<<(ostream &os, const Edge &e)
  {
    // 输出 a-b : weight
    os << e.a << "-" << e.b << " : " << e.weight;
    return os;
  }

  // 后续我们的图算法经常要对两个边的信息进行比较，所以这里重载一下比较运算符
  bool operator<(Edge<Weight> &e)
  {
    return weight < e.wt();
  }

  bool operator>(Edge<Weight> &e)
  {
    return weight > e.wt();
  }

  bool operator==(Edge<Weight> &e)
  {
    return weight > e.wt();
  }

  bool operator!=(Edge<Weight> &e)
  {
    return weight != e.wt();
  }

  bool operator<=(Edge<Weight> &e)
  {
    return weight <= e.wt();
  }

  bool operator>=(Edge<Weight> &e)
  {
    return weight >= e.wt();
  }

  // 当然对于这6个重载运算符，如果是在c++20中，可以使用 <=> 三路比较运算符来进行书写
};

#endif