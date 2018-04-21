#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Image.h"

using namespace std;

const int MAX_EDGES = 5000;
map<int, vector<int> > edges;
map<int, bool> nodes;
map<int, pair<int, int> > node_position;

int main()
{
      ifstream graph("hep-th-citations");
      Image img(5000, 5000, "result.ppm");

      // Creating edges & nodes
      for (int i = 0; i < MAX_EDGES; i++)
      {
            int from, to;
            graph >> from >> to;
            edges[from].push_back(to);

            nodes[from] = true;
            nodes[to] = true;
      }

      // Creating x, y position for every node
      for (auto u : nodes)
      {
            int x = rand() % 5000;
            int y = rand() % 5000;
            node_position[u.first] = make_pair(x, y);

            // Drawing points on x, y node_position
            img.dot(x, y);
      }

      // Drawing lines
      for (auto e : edges)
      {
            for (unsigned int u = 0; u < e.second.size(); u++)
            {
                  pair <int , int> from = node_position[e.first];
                  pair <int , int> to = node_position[e.second[u]];

                  img.line(from, to);
            }
      }

      img.save();
      graph.close();


      return 0;
}
