#include <iostream>
#include <fstream>
#include <string>
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
        void setDistance(int x){this->distance=x;}
        void setDestination(string x){this->destination=x;}
        void setSource(string x){this->source = x;}

        friend bool operator<(Edge const& first, Edge const& second){return first.distance < second.distance;}
        friend bool operator>(Edge const& first, Edge const& second){return first.distance > second.distance;}
        friend bool operator==(Edge const& first, Edge const& second){
            bool x = false;
            if(first.destination == second.destination && first.source == second.source && first.distance == second.distance){
                x = true;
            }
            return x;
        }

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

void CityGraph::sortEdges(){
    sort(this->edges.begin(), this->edges.end());
    Edge minBetweenGPandChurch =  Edge("","",0);
    Edge hippodrome = Edge("","",0);

    for(auto iter: this->edges){
        if(iter.getSource() == "GP" && iter.getDestination().substr(0,2) == "Ch"){
            minBetweenGPandChurch.setSource(iter.getSource());
            minBetweenGPandChurch.setDestination(iter.getDestination());
            minBetweenGPandChurch.setDistance(iter.getDistance());
        }
        if(iter.getSource() == "GP" && iter.getDestination()=="Hipp"){
            hippodrome.setSource(iter.getSource());
            hippodrome.setDestination(iter.getDestination());
            hippodrome.setDistance(iter.getDistance());
        }
    }

    vector<Edge>::iterator itr2 = find(this->edges.begin(), this->edges.end(), hippodrome);
    int index2 = distance(this->edges.begin(),itr2);
    this->edges.erase(this->edges.begin()+index2);
    this->edges.insert(this->edges.begin(),hippodrome);

    vector<Edge>::iterator itr = find(this->edges.begin(), this->edges.end(), minBetweenGPandChurch);
    int index = distance(this->edges.begin(),itr);
    this->edges.erase(this->edges.begin()+index);  
    this->edges.insert(this->edges.begin(),minBetweenGPandChurch);
}

int CityGraph::findParent(vector<Node> vertices, int numericVertex){
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
}

int CityGraph::findNumeric(string name){
    int rt;
    for(int i=0; i<this->currentVerticeCount; i++){
        if(this->vertices[i] == name){
            rt = i;
        }
    }
    return rt;
}

void CityGraph::printMST(){
    int curDistance = 0;
    sort(this->minimumSpanningTree.begin(), this->minimumSpanningTree.end());
    for(auto x: this->minimumSpanningTree){
        cout<<x.getSource() << " "<< x.getDestination()<<" "<<x.getDistance()<<endl;
        curDistance += x.getDistance();
    }

    cout<<curDistance<<endl;
}

void CityGraph::kruskalAlgorithm(){
    vector<Edge> temp = this->edges;

    createParents();
    for(unsigned int i=0; i < this->edges.size(); i++){
        Edge curEdge = temp[i];
        if(curEdge.getSource().substr(0,2) =="Hp" && curEdge.getDestination().substr(0,2) =="Hp"){
            continue;
        }
        if(curEdge.getSource() == "Hipp" && curEdge.getDestination().substr(0,3) == "Bas"){
            continue;
        }
        if(curEdge.getDestination() == "Hipp" && curEdge.getSource().substr(0,3) == "Bas"){
            continue;
        }
    
        int src = findNumeric(curEdge.getSource());
        int dest = findNumeric(curEdge.getDestination());

        int srcParent= findParent(this->parents, src);
        int destParent = findParent(this->parents, dest);

        if(srcParent != destParent){
            this->minimumSpanningTree.push_back(curEdge);
            this->parents[destParent].name = this->parents[srcParent].name;
            this->parents[destParent].numeric = this->parents[srcParent].numeric;
        }
    }
}

int main(){
    string filename = "city_plan_2.txt";
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
    Monstantinapolis.kruskalAlgorithm();
    Monstantinapolis.printMST();
    
    return EXIT_SUCCESS;
}