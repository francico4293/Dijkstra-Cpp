// Author: Colin Francis
// Description: An implementation of Dijkstra's Algorithm in C++
#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;


class Dijkstra {
    private:
        map<string, map<string, int>> graph;
        map<string, string> pathTable;
        map<string, int> distanceTable;
        map<char, char> routingTable;
        string source;

        struct comparitor {
            bool operator() (vector<string>& a, vector<string>& b) {
                return stoi(a[0]) > stoi(b[0]);
            }
        };

        void initDistanceTable(void) {
            map<string, map<string, int>>::iterator graphIter = this->graph.begin();

            while (graphIter != this->graph.end()) {
                if (graphIter->first == this->source) {
                    distanceTable.insert({graphIter->first, 0});
                } else {
                    distanceTable.insert({graphIter->first, INT_MAX});
                }

                graphIter = next(graphIter, 1);
            }

            map<string, int>::iterator linkIter = this->graph.find(this->source)->second.begin();
            
            while (linkIter != this->graph.find(this->source)->second.end()) {
                this->distanceTable.find(linkIter->first)->second = linkIter->second;
                linkIter = next(linkIter, 1);
            }
        }

        void initPathTable(void) {
            map<string, map<string, int>>::iterator graphIter = this->graph.begin();

            while (graphIter != this->graph.end()) {
                this->pathTable.insert({graphIter->first, ""});
                graphIter = next(graphIter, 1);
            }

            map<string, int>::iterator linkIter = this->graph.find(this->source)->second.begin();

            while (linkIter != this->graph.find(this->source)->second.end()) {
                this->pathTable.find(linkIter->first)->second = this->source;
                linkIter = next(linkIter, 1);
            }
        }
    
    public:
        // Constructor for Dijkstra class
        Dijkstra(map<string, map<string, int>> graph, string source) {
            this->graph = graph;
            this->source = source;
        }

        // Displays graph of network for class instance
        void getGraph(void) {
            map<string, map<string, int>>::iterator graphIter = this->graph.begin();

            cout << "Graph of Network: " << endl;
            while (graphIter != this->graph.end()) {
                cout << "\t" << graphIter->first << ": {";
                map<string, int>::iterator linkIter = graphIter->second.begin();
                while (linkIter != graphIter->second.end()) {
                    cout << "{" << linkIter->first << ", " << linkIter->second << "}";
                    if (next(linkIter, 1) != graphIter->second.end()) {
                        cout << ", ";
                    }
                    linkIter = next(linkIter, 1);
                }
                cout << "}" << endl;
                graphIter = next(graphIter, 1);
            }
            cout << endl;
        }

        void getPathTable(void) {
            map<string, string>::iterator pathIter = this->pathTable.begin();

            cout << "Current Node: Previous Node" << endl;
            while (pathIter != this->pathTable.end()) {
                cout << "\t" << pathIter->first << ": ";
                if (pathIter->second == "") {
                    cout << "*" << endl;
                } else {
                    cout << pathIter->second << endl;
                }
                pathIter = next(pathIter, 1);
            }
            cout << endl;
        }

        void getDistanceTable(void) {
            map<string, int>::iterator distIter = this->distanceTable.begin();

            cout << "Distance From Node " << this->source << " To Other Nodes:" << endl;
            while (distIter != this->distanceTable.end()) {
                cout << "\t" << distIter->first << ": " << distIter->second << endl;
                distIter = next(distIter, 1);
            }
            cout << endl;
        }

        void getRoutingTable(void) {

        }

        void dijkstra(void) {
            map<string, bool> visited;
            priority_queue<vector<string>, vector<vector<string>>, comparitor> pq;
            this->initDistanceTable();
            this->initPathTable();

            this->getGraph();
            this->getDistanceTable();
            this->getPathTable();

            visited.insert({this->source, true});
            map<string, int>::iterator linkIter = this->graph.find(this->source)->second.begin();
            while (linkIter != this->graph.find(this->source)->second.end()) {
                pq.push({to_string(linkIter->second), linkIter->first});
                linkIter = next(linkIter, 1);
            }

            while (!pq.empty()) {
                vector<string> front = pq.top();
                pq.pop();

                int distance = stoi(front[0]);
                string node = front[1];

                cout << "Distance: " << distance << ", " << "Node: " << node << endl;
            }
        }
};

int main(int argc, char* argv[]) {
    map<string, map<string, int>> network = {
        {"A", map<string, int>{{"B", 7}, {"E", 9}}},
        {"B", map<string, int>{{"A", 7}, {"C", 3}, {"E", 6}}},
        {"C", map<string, int>{{"B", 3}, {"D", 11}, {"F", 2}}},
        {"D", map<string, int>{{"C", 11}, {"G", 3}}},
        {"E", map<string, int>{{"A", 9}, {"B", 6}}},
        {"F", map<string, int>{{"B", 8}, {"C", 2}, {"G", 5}}},
        {"G", map<string, int>{{"D", 3}, {"F", 5}}}
    };

    Dijkstra d = Dijkstra(network, "D");
    d.dijkstra();

    return 0;
}
