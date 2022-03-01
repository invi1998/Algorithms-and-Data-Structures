#ifndef MINIMUMSPANTREE_READGRAPH_H
#define MINIMUMSPANTREE_READGRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>

using namespace std;

template <typename Graph, typename Weight>
class ReadGraph
{

public:
  ReadGraph(Graph &graph, const string &filename)
  {
    ifstream file(filename);
    string line;
    int V, E;

    assert(file.is_open());

    assert(getline(file, line));

    stringstream ss(line);
    ss >> V >> E;
    assert(graph.V() == V);

    for (int i = 0; i < E; i++)
    {
      assert(getline(file, line));
      stringstream ss(line);

      int a, b;
      Weight wt;

      ss >> a >> b >> wt;

      assert(a >= 0 && a < V);
      assert(b >= 0 && b < V);
      graph.addEdge(a, b, wt);
    }
  }
};

#endif