// Author: Colin Francis
// Description: An implementation of Dijkstra's Algorithm in C++
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;


class Dijkstra {
    private:
        map<string, map<string, int>> graph;
        map<string, string> pathTable;
        map<string, int> distanceTable;
        map<string, string> routingTable;
        string source;

        struct comparator {
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
        }

        void initPathTable(void) {
            map<string, map<string, int>>::iterator graphIter = this->graph.begin();

            while (graphIter != this->graph.end()) {
                this->pathTable.insert({graphIter->first, ""});
                graphIter = next(graphIter, 1);
            }
        }

        void initRoutingTable(void) {
            map<string, map<string, int>>::iterator mapIter = this->graph.begin();

            while (mapIter != this->graph.end()) {
                this->routingTable.insert({mapIter->first, ""});
                mapIter = next(mapIter, 1);
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
            map<string, string>::iterator routingIter = this->routingTable.begin();

            cout << "Routing Table For " << this->source << ":" << endl;
            while (routingIter != this->routingTable.end()) {
                cout << "\t" << routingIter->first << ": ";
                if (routingIter->second == "") {
                    cout << "*" << endl;
                } else {
                    cout << routingIter->second << endl;
                }
                routingIter = next(routingIter, 1);
            }
            cout << endl;
        }

        void showPathAndLength(string destination) {
            string path;
            string dest = destination;

            while (destination != this->source) {
                path.append(destination);
                destination = this->pathTable.find(destination)->second;
            }
            path.append(destination);

            reverse(path.begin(), path.end());

            cout << "Shortest Path from " << this->source << " to " << dest << ": " << path << endl;
            cout << "Path Length from " << this->source << " to " << dest << ": " << this->distanceTable.find(dest)->second << endl;
        }

        void updateRoutingTable(string currNode) {

        }

        void dijkstra(void) {
            map<string, bool> visited;
            priority_queue<vector<string>, vector<vector<string>>, comparator> pq;

            this->initDistanceTable();
            this->initPathTable();
            this->initRoutingTable();

            this->getRoutingTable();

            visited.insert({this->source, true});
            map<string, int>::iterator linkIter = this->graph.find(this->source)->second.begin();
            while (linkIter != this->graph.find(this->source)->second.end()) {
                pq.push({to_string(linkIter->second), linkIter->first, this->source});
                linkIter = next(linkIter, 1);
            }

            while (!pq.empty()) {
                vector<string> front = pq.top();
                pq.pop();

                int distance = stoi(front[0]);
                string currNode = front[1];
                string prevNode = front[2];

                if (visited.find(currNode) != visited.end()) {
                    continue;
                }

                if (this->distanceTable.find(currNode)->second < distance) {
                    continue;
                }

                visited.insert({currNode, true});
                this->distanceTable.find(currNode)->second = distance;
                this->pathTable.find(currNode)->second = prevNode;

                linkIter = this->graph.find(currNode)->second.begin();
                while (linkIter != this->graph.find(currNode)->second.end()) {
                    pq.push({to_string(linkIter->second + distance), linkIter->first, currNode});
                    linkIter = next(linkIter, 1);
                }
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
    d.showPathAndLength("E");

    return 0;
}
