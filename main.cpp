#include <iostream>
#include <fstream>
#include <string>
#include<unordered_map>

using namespace std;

class CityGraph{
    unordered_map<string, list< pair<string, int>>> nodes;
    public:
        void addEdge(string, string, int);
        bool isInGraph(string);
        void print();
};

void CityGraph::addEdge(string base, string destination, int distance){
    if(this->isInGraph(base)){
        nodes[base].push_back(make_pair(destination, distance));
        if(this->isInGraph(destination)){
            nodes[destination].push_back(make_pair(base, distance));
        }
        else{
            nodes.insert(destination, make_pair(base, distance));
        }
    }
    else{
        nodes.insert(base, make_pair(destination, distance));
        if(this->isInGraph(destination)){
            nodes[destination].push_back(make_pair(base, distance));
        }
        else{
            nodes.insert(destination, make_pair(base,distance));
        }
    }
}

bool CityGraph::isInGraph(string x){
    bool returnValue = false;
    for(auto iter: this->nodes){
        if(iter.first == x){
            returnValue = true;
        }
    }
    return returnValue;
}

void CityGraph::print(){
    for(auto iter: this->nodes){
        string place = iter.first;
        list<pair<string,int>> adjancies = iter.second;

        cout<<place<<"->";
        for(auto adj:adjancies){
            int distance = adj.second;
            string destinationPlace = adj.first;

            cout<<destinationPlace<<" "<<distance<<" ";
        }
        cout<<endl;
    }
}

int main(){
    string filename = "city_plan.txt";
    ifstream file;
    file.open(filename);
    string line;

    string base,destination;
    int distance;

    CityGraph Monstantinapolis;


    while(!file.eof()){
        getline(file,line,',');
        base = line;

        getline(file,line,",");
        destination = line;

        getline(file, line,"\n");
        distance = stoi(line);

        Monstantinapolis.addEdge(base,destination,distance);
    }

    Monstantinapolis.print();

    return EXIT_SUCCESS;
}