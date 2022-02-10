//
// 读取一个文本文件，将文本中的图读取出来（读取一个文件形成一个图）
//

#ifndef GRAPH_READGRAPH_H
#define GRAPH_READGRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

template <typename Graph>
class ReadGraph
{
public:
  // 构造函数（传递进来一个图，一个文件名）
  ReadGraph(Graph &graph, const string &filename)
  {
    ifstream file(filename); //  定义一个文件类型
    string line;             // 保存读取到的一行内容
    int V, E;                // 保存顶点数和边数

    assert(file.is_open()); // 断言文件确实被打开了

    assert(getline(file, line)); // 断言一行一行读取成功（将每一行读取到line中）

    stringstream ss(line); // 将line中的数据保存到ss中

    ss >> V >> E; // 将这个stringstream对象ss解析出V和E这两个整形变量

    // 到此为止我们就处理完了图文件的第一行，将顶点和边数都读取了进来

    // 注意，因为我们这里的graph是在外面声明传递进来的，
    // 声明的时候这个点的数量在图构造的时候就需要我们传入这个点的数量
    // 所以这里我们就需要使用断言来确定我们从文件中读取的点数和传入进来的 graph对象的点数是相同的

    assert(V == graph.V());

    // 断言判断成功后，就说明我们读取和传入的图都没问题
    // 那这个时候就需要循环读取E次，每次读取一行，这样就可以将整个图读取出来
    for (int i = 0; i < E; i++)
    {
      assert(getline(file, line));
      stringstream ss(line);

      int a, b;     // 声明a,b两个变量
      ss >> a >> b; // 将ss解析到a,b中

      // 为了严谨起见，这里使用断言对a,b的越界情况做判断
      assert(a >= 0 && a < V);
      assert(b >= 0 && b < V);

      // 然后将ab边添加进图中
      graph.addEdge(a, b);
    }

    // 经历这次遍历之后，我们的这个图就建立起来了
  }
};

#endif