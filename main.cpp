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

class Node{
    public:
        string name;
        int numeric;
        Node(string nam, int num){this->name=nam; this->numeric=num;}
        Node(int num){this->numeric = num;}
};

class CityGraph{
    private:
        int currentVerticeCount;
        vector<Edge> edges;
        vector<string> vertices;
        vector<Edge> minimumSpanningTree;
        vector<Node> parents;

    public:
        void sortEdges();
        void addEdge(Edge);
        void print();
        void printMST();
        int getVerticeCount(){return this->currentVerticeCount;}

        void kruskalAlgorithm();
        int findParent(vector<Node>,int);
        int findNumeric(string);
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
    Edge temp = Edge("","",0);
    for(auto iter: this->edges){

    }
}

int CityGraph::findParent(vector<Node> vertices, int numericVertex){
    cout<<"paremeter: "<<numericVertex<<endl;
    int parent = vertices[numericVertex].numeric;
    if(parent == numericVertex){
        return parent;
    }
    else{
        return findParent(vertices,parent);
    }
}

void CityGraph::createParents(){
    for(int i=0; i< this->currentVerticeCount; i++){
        Node temp = Node(this->vertices[i],i);
        this->parents.push_back(temp);
    }
    for(auto x: this->parents){
        cout<<x.name<<" : "<<x.numeric<<endl;
    }
}

int CityGraph::findNumeric(string name){
    int rt;
    for(int i=0; i<this->currentVerticeCount; i++){
        if(this->vertices[i] == name){
            rt = i;
            cout<<vertices[i]<<" "<<rt<<endl;
        }
    }
    return rt;
}

void CityGraph::printMST(){
    cout<<".... Printing the MST by Kruskal's Algorithm...."<<endl;
    int curDistance = 0;

    for(auto x: this->minimumSpanningTree){
        cout<<x.getSource() << " "<< x.getDestination()<<" "<<x.getDistance()<<endl;
        curDistance += x.getDistance();
    }

    cout<<"Total: "<<curDistance<<endl;
}

void CityGraph::kruskalAlgorithm(){
    vector<Edge> temp = this->edges;

    createParents();
    for(int i=0; i < this->currentVerticeCount; i++){
        Edge curEdge = temp[i];

        int src = findNumeric(curEdge.getSource());
        int dest = findNumeric(curEdge.getDestination());

        int srcParent= findParent(this->parents, src);
        int destParent = findParent(this->parents, dest);

        if(srcParent != destParent){
            this->minimumSpanningTree.push_back(curEdge);
            this->parents[destParent].name = this->parents[srcParent].name;
            this->parents[destParent].numeric = this->parents[srcParent].numeric;
            cout<<parents[destParent].name<<" "<<parents[destParent].numeric<<" ------ "<<parents[srcParent].name<<" "<<parents[srcParent].numeric<<endl;
        }
        cout<<i<<endl;
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
    Monstantinapolis.printMST();
    
    return EXIT_SUCCESS;
}