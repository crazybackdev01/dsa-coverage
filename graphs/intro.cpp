#include <iostream>
#include <vector>
using namespace std;

class Graph {
    private:
        int V;
        vector<vector<int>> adjList;
        bool isDirected;
    
    public:
        // Constructor to initialize the graph
        Graph(int V, bool isDirected=false){
            this->V = V;
            this->isDirected = isDirected;
            this->adjList.resize(V);
        }

        // Function to add an edge from source (u) to destination (v)
        void addEdge(int u,int v){
            if (u < 0 || u >= V || v < 0 || v >= V) {
                cout << "Error: Invalid edge (" << u << ", " << v << ")\n";
                return;
            }
            this->adjList[u].push_back(v);

            if(!isDirected){
                this->adjList[v].push_back(u);
            }
        }
        // Function to print the adjacency list representation
        void printGraph(){
            for(int i=0;i<this->V;i++){
                cout<<"Vertex "<<i<<" -> ";
                for(int neighbour : this->adjList[i]){
                    cout<<neighbour<<" ";
                }
                cout<<endl;
            }
        }
};

int main(){

    Graph G(5,true);

    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(1,3);
    G.addEdge(1,4);
    G.addEdge(0,4);
    G.addEdge(4,3);

    G.printGraph();

    return 0;
}