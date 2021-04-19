#include <iostream>
#include <fstream>
#include <string>
#include<unordered_map>
#include<list>
#include<vector>
#include <algorithm>
#include<map>


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
        int currentVerticeCount;
        vector<Edge> edges;
        vector<string> vertices;
        map<string,int> parents;
        vector<Edge> minimumSpanningTree;

    public:
        void sortEdges();
        void addEdge(Edge);
        void print();
        int getVerticeCount(){return this->currentVerticeCount;}

        void kruskalAlgorithm();
        int findParent(map<string,int>,int);
        void changeParents(map<string,int>, int, int);
        void createParents();

        CityGraph(){
            this->currentVerticeCount = 0;
        }
};

void CityGraph::addEdge(Edge edge){
    if(!(find(this->vertices.begin(), this->vertices.end(), edge.getSource()) != this->vertices.end())){
        this->vertices.push_back(edge.getSource());
        this->currentVerticeCount++;
    }
    if(!(find(this->vertices.begin(), this->vertices.end(), edge.getDestination()) != this->vertices.end())){
        this->vertices.push_back(edge.getDestination());
        this->currentVerticeCount++;
    }

    this->edges.push_back(edge);
}

void CityGraph::print(){
    for(Edge edge: this->edges){
        cout<<edge.getSource()<<" to "<<edge.getDestination()<<" = "<<edge.getDistance()<<endl;
    }
}

void CityGraph::sortEdges(){
    sort(this->edges.begin(), this->edges.end());
}

int CityGraph::findParent(map<string,int> vertices, int numericVertex){
    int i=0;
    int parent;

    for(auto x: vertices){
        if(i != numericVertex){
            i++;
            continue;
        }
        else{
            parent = x.second;
            break;
        }
    }

    if(parent == numericVertex){
        return parent;
    }
    else{
        return findParent(vertices,parent);
    }
}

void CityGraph::createParents(){
    for(int i=0; i< this->currentVerticeCount; i++){
        pair<string,int> temp = make_pair(this->vertices[i],i);
        this->parents.insert(temp);
    }
    for(auto x: this->parents){
        cout<<x.first<<" : "<<x.second<<endl;
    }
}

void CityGraph::changeParents(map<string,int> parent, int src, int dest){
    pair<string, int> temp;
    int i=0;
    for(auto node: parent){
        if(i != src){
            i++;
            continue;
        }
        else{
            temp = node;
            break;
        }
    }

    int j=0;
    for(auto node: parent){
        if(j != dest){
            j++;
            continue;
        }
        else{
            node.second = temp.second;
        }
    }
}

void CityGraph::kruskalAlgorithm(){
    vector<Edge> temp = this->edges;

    createParents();
    for(int i=0; i < this->currentVerticeCount; i++){
        Edge curEdge = temp[i];
        cout<<endl<<curEdge.getSource();
        int src = this->parents.at(curEdge.getSource());
        int dest = this->parents.at(curEdge.getDestination());
        cout<<src<<" "<<"dest";
        int srcParent= findParent(this->parents, src);
        int destParent = findParent(this->parents, dest);
        cout<<"1111111111"<<endl;
        if(src != dest){
            this->minimumSpanningTree.push_back(curEdge);
            changeParents(this->parents, srcParent, destParent);
        }
    }
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
    Monstantinapolis.kruskalAlgorithm();
    Monstantinapolis.print();
    
    return EXIT_SUCCESS;
}