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
        int distance;
        string prevVertex;

        Node(string nam){this->name=nam; this->distance=100000;}
};

class PathGraph{
    public:
        vector<Edge> edges;
        vector<Edge> safeEdges;
        vector<string> points;
        vector<string> safePoints;
        vector<Node> path;
        vector<string> removed;
        int flag;
        PathGraph(){this->flag = 0;}
        void addEdge(Edge,bool);
        void filterEnemies();
        void removeFromSafePoint(string);
        void findShortestPath(string);
};

void PathGraph::addEdge(Edge edge, bool flag){
    if(flag){
        if(!(find(this->safePoints.begin(), this->safePoints.end(), edge.getSource()) != this->safePoints.end())){
            this->safePoints.push_back(edge.getSource());
        }
        if(!(find(this->safePoints.begin(), this->safePoints.end(), edge.getDestination()) != this->safePoints.end())){
            this->safePoints.push_back(edge.getDestination());
        }
        this->safeEdges.push_back(edge);
    }
    else{
        if(!(find(this->points.begin(), this->points.end(), edge.getSource()) != this->points.end())){
            this->points.push_back(edge.getSource());
        }
        if(!(find(this->points.begin(), this->points.end(), edge.getDestination()) != this->points.end())){
            this->points.push_back(edge.getDestination());
        }
        this->edges.push_back(edge);
    }
}

void PathGraph::filterEnemies(){
    for(auto iter: this->edges){
        if(iter.getSource()[0] == 'E' || iter.getDestination()[0] == 'E'){
            if(iter.getDistance() < 5){ //spy range is 5
                if(iter.getSource()[0] == 'E'){
                    removeFromSafePoint(iter.getDestination());
                }
                else{
                    removeFromSafePoint(iter.getSource());
                }
            }
        }
        else{
            addEdge(iter,true);
        }
    }
}

void PathGraph::removeFromSafePoint(string removed){
    vector<string>::iterator iter = find(this->safePoints.begin(), this->safePoints.end(), removed);
    int index = distance(this->safePoints.begin(),iter);
    safePoints.erase(safePoints.begin() + index);

    for(auto temp: this->safeEdges){
        if(temp.getSource() == removed || temp.getDestination() == removed){
            vector<Edge>::iterator iter2 = find(safeEdges.begin(), safeEdges.end(), temp);
            int index2= distance(safeEdges.begin(),iter2);
            safeEdges.erase(safeEdges.begin() + index2);
        }
    }
    this->flag++;
}

void PathGraph::findShortestPath(string start){
    for(string iter: safePoints){
        Node temp = Node(iter);
        if(iter == start){
            temp.distance = 0;
        }
        path.push_back(temp);
    }
    for(unsigned int i=0; i<safeEdges.size(); i++){
        int dist1, x1, dist2, x2;
        for(unsigned int x=0; x<path.size(); x++){
            if(safeEdges[i].getSource() == path[x].name){
                dist1 = path[x].distance;
                x1 = x;
            }
            if(safeEdges[i].getDestination() == path[x].name){
                dist2 = path[x].distance;
                x2 = x;
            }
        }

        if(dist2 > dist1 + safeEdges[i].getDistance() ){
            path[x2].distance = path[x1].distance + safeEdges[i].getDistance();
            path[x2].prevVertex = path[x1].prevVertex + safeEdges[i].getSource() + " ";
        }
    }
}

int main(){
    string filename;
    cin >> filename;
    ifstream file;
    file.open(filename);
    string line,base,destination;
    int distance;

    PathGraph way = PathGraph();

    while(!file.eof()){
        getline(file,line,',');
        base = line;

        getline(file,line,',');
        destination = line;

        getline(file, line,'\n');
        distance = stoi(line);

        Edge givenEdge = Edge(base,destination,distance);
        way.addEdge(givenEdge, false);
    }

    way.filterEnemies();

    string startVertex = "Ma";

    way.findShortestPath(startVertex);

    int index = way.path.size() - way.flag - 1;

    cout << way.path[index].prevVertex << way.path[index].name <<" "<< way.path[index].distance <<endl;

    return EXIT_SUCCESS;
}