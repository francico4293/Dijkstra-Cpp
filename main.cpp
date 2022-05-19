// Author: Colin Francis
// Description: An implementation of Dijkstra's Algorithm in C++
#include <iostream>
#include <map>
using namespace std;


class Dijkstra {
    private:
        map<char, map<char, int>> graph;
        map<char, char> pathTable;
        map<char, int> distanceTable;
        map<char, char> routingTable;
        char source;

        void initDistanceTable(void) {
            map<char, map<char, int>>::iterator graphIter = this->graph.begin();

            while (graphIter != this->graph.end()) {
                if (graphIter->first == this->source) {
                    this->distanceTable.insert({graphIter->first, 0});
                } else {
                    this->distanceTable.insert({graphIter->first, INT_MAX});
                }

                graphIter = next(graphIter, 1);
            }
        }
    
    public:
        // Constructor for Dijkstra class
        Dijkstra(map<char, map<char, int>> graph, char source) {
            this->graph = graph;
            this->source = source;
        }

        // Displays graph of network for class instance
        void getGraph(void) {
            map<char, map<char, int>>::iterator graphIter = this->graph.begin();

            cout << "\nGraph of Network: " << endl;
            while (graphIter != this->graph.end()) {
                cout << "\t" << graphIter->first << ": {";
                map<char, int>::iterator linkIter = graphIter->second.begin();
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

        }

        void getDistanceTable(void) {
            map<char, int>::iterator distIter = this->distanceTable.begin();

            cout << "Distance Table From " << this->source << " To Other Nodes:" << endl;
            while (distIter != this->distanceTable.end()) {
                cout << "\t" << distIter->first << ": " << distIter->second << endl;
                distIter = next(distIter, 1);
            }
        }

        void getRoutingTable(void) {

        }

        void dijkstra(void) {
            this->initDistanceTable();
            this->getDistanceTable();
        }
};

int main(int argc, char* argv[]) {
    map<char, map<char, int>> network = {
        {'A', map<char, int>{{'B', 7}, {'E', 9}}},
        {'B', map<char, int>{{'A', 7}, {'C', 3}, {'E', 6}}},
        {'C', map<char, int>{{'B', 3}, {'D', 11}, {'F', 2}}},
        {'D', map<char, int>{{'C', 11}, {'G', 3}}},
        {'E', map<char, int>{{'A', 9}, {'B', 6}}},
        {'F', map<char, int>{{'B', 8}, {'C', 2}, {'G', 5}}},
        {'G', map<char, int>{{'D', 3}, {'F', 5}}}
    };

    Dijkstra d = Dijkstra(network, 'D');
    d.getGraph();
    d.dijkstra();

    return 0;
}
