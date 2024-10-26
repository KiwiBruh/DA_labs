#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
using namespace std;

struct edge {
    int node1;
    int node2;
    int weight;
};

 long long minTrail( int nodes, int edges,  int start,  int finish, std::vector<edge> graph) {
    std::vector< long long> result(nodes + 1, -1); // точно не будет
    std::vector<bool> checked(nodes + 1, 0);// здесь отмечаем посещённые вершины
    set<pair<long long , int>> queue;
    queue.insert({ 0,start });
    result[start] = 0;
    long long fullTrail;
    while (!queue.empty()){
        auto firstElement = queue.begin();
        int id = (*firstElement).second;
        queue.erase(firstElement);
        if (checked[id] == true) continue;
        checked[id] = true;
        for ( int i = 0; i < edges; i++) {
            if (graph[i].node1 == id) {
                fullTrail = result[id] + graph[i].weight;
                if (fullTrail < result[graph[i].node2] || result[graph[i].node2] == -1) {
                    result[graph[i].node2] = fullTrail;
                    queue.insert({ fullTrail,graph[i].node2 });
                }
                        
            }
            else if (graph[i].node2 == id) {
                fullTrail = result[id] + graph[i].weight;
                if (fullTrail < result[graph[i].node1] || result[graph[i].node1] == -1) {
                    result[graph[i].node1] = fullTrail;
                    queue.insert({ fullTrail,graph[i].node1});
                }
                    
            }
            
        }
        
    }
    return result[finish];

}

int main() {
     int nodes, edges;
     int start, finish;
    std::cin >> nodes >> edges >> start >> finish;
    std::vector<edge> graph;
     int node1, node2;
     int edgeWeight;
    for ( int k = 0; k < edges; k++) {
        std::cin >> node1 >> node2 >> edgeWeight;
        graph.push_back({ node1, node2, edgeWeight });
    }
    long long trail = minTrail(nodes,edges, start, finish, graph);
    if (trail == -1) {
        std::cout << "No solution" << std::endl;
    }
    else {
        std::cout << trail << std::endl;
    }
}
