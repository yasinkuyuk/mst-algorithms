#include <iostream>
#include <fstream>
#include <string>
#include<unordered_map>
#include<list>
#include<vector>
#include <algorithm>


using namespace std;

class Edge{
    private:
        string source;
        string destination;
        int distance;
    public:
        const string getSource(){return this->source;}
        const string getDestination(){return this->destination;}
        const int getDistance(){return this->distance;}

        friend bool operator<(Edge const& first, Edge const& second){return first.distance < second.distance;}
        friend bool operator>(Edge const& first, Edge const& second){return first.distance > second.distance;}

        Edge(string src, string dest, int dist){
            this->source = src;
            this->destination = dest;
            this->distance = dist;
        }
};

class CityGraph{
    private:
        int currentEdgeCount;
        vector<Edge> edges;

    public:
        void sortEdges();
        void addEdge(Edge);
        void print();

        CityGraph(){
            this->currentEdgeCount = 0;
        }
};

void CityGraph::addEdge(Edge edge){
    this->edges.push_back(edge);
    this->currentEdgeCount++;
}

void CityGraph::print(){
    for(Edge edge: this->edges){
        cout<<edge.getSource()<<" to "<<edge.getDestination()<<" = "<<edge.getDistance()<<endl;
    }
}

void CityGraph::sortEdges(){
    sort(this->edges.begin(), this->edges.end());
}

int main(){
    string filename = "city_plan.txt";
    ifstream file;
    file.open(filename);
    string line;

    string base,destination;
    int distance;

    CityGraph Monstantinapolis = CityGraph();


    while(!file.eof()){
        getline(file,line,',');
        base = line;

        getline(file,line,',');
        destination = line;

        getline(file, line,'\n');
        distance = stoi(line);

        Edge givenEdge = Edge(base,destination,distance);
        Monstantinapolis.addEdge(givenEdge);
    }

    Monstantinapolis.sortEdges(); //sorting edges in ascending order
    Monstantinapolis.print();

    return EXIT_SUCCESS;
}