//
//  main.cpp
//  CS250_ProgramFive
//
//  Created by Charlotte Luquer on 12/4/24.
//
// Description: finds paths and costs in a graph using two search methods (DFS and BFS) and checks if there is a way to go from one point to another
//
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <limits>
using namespace std;

class WeightedGraph {
private:
    unordered_map<char, vector<pair<char, int>>> graph;

public:

    void addEdge(char u, char v, int weight) {
        graph[u].push_back({v, weight});
    }
    void dfs(char start) {
        unordered_set<char> visited;
        vector<char> path;
        int totalCost = 0;
        function<void(char)> dfsHelper = [&](char node) {
            visited.insert(node);
            path.push_back(node);
            for (auto &[neighbor, weight] : graph[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    totalCost += weight;
                    dfsHelper(neighbor);
                }
            }
        };
        dfsHelper(start);
        cout << "DFS Path: ";
        for (char node : path) cout << node << " ";
        cout << "Total Cost: " << totalCost << endl;
    }
    void bfs(char start) {
        unordered_set<char> visited;
        queue<pair<char, int>> q;
        vector<char> path;
        int totalCost = 0;
        q.push({start, 0});
        while (!q.empty()) {
            auto [node, cost] = q.front();
            q.pop();
            if (visited.find(node) == visited.end()) {
                visited.insert(node);
                path.push_back(node);
                totalCost += cost;
                for (auto &[neighbor, weight] : graph[node]) {
                    q.push({neighbor, weight});
                }
            }
        }
        cout << "BFS Path: ";
        for (char node : path) cout << node << " ";
        cout << "Total Cost: " << totalCost << endl;
    }
    void findPath(char source, char destination) {
        unordered_set<char> visited;
        unordered_map<char, char> parent;
        queue<pair<char, int>> q;
        bool found = false;
        int totalCost = 0;
        q.push({source, 0});
        while (!q.empty() && !found) {
            auto [node, cost] = q.front();
            q.pop();
            if (visited.find(node) == visited.end()) {
                visited.insert(node);
                for (auto &[neighbor, weight] : graph[node]) {
                    if (visited.find(neighbor) == visited.end()) {
                        parent[neighbor] = node;
                        if (neighbor == destination) {
                            found = true;
                            totalCost = cost + weight;
                            break;
                        }
                        q.push({neighbor, cost + weight});
                    }
                }
            }
        }

        if (found) {
            vector<char> path;
            for (char at = destination; at != 0; at = parent[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());

            cout << "Path from " << source << " to " << destination << ": ";
            for (char node : path) cout << node << " ";
            cout << "Total Cost: " << totalCost << endl;
        } else {
            cout << "No path exists from " << source << " to " << destination << endl;
        }
    }
};
int main() {
    WeightedGraph graph;
    graph.addEdge('E', 'A', 7);
    graph.addEdge('A', 'B', 10);
    graph.addEdge('A', 'D', 12);
    graph.addEdge('D', 'C', 32);
    graph.addEdge('E', 'C', 60);
    cout << "DFS Traversal starting from node E:" << endl;
    graph.dfs('E');
    cout << "BFS Traversal starting from node E:" << endl;
    graph.bfs('E');
    cout << "Finding path from E to C:" << endl;
    graph.findPath('E', 'C');
    cout << "Finding path from A to D:" << endl;
    graph.findPath('A', 'D');
    cout << "Finding path from B to E:" << endl;
    graph.findPath('B', 'E');
    return 0;
}
