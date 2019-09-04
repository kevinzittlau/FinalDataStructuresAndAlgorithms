#include <unordered_map>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{
    string startLoc;
    string finishLoc;
    double size;
    int cost;
    int id;
};
// Holds the values for each node id
unordered_map<int, double> values;

// Map of nodes with starting location as the key and vector of nodes as pair
map<string, vector<Node>> m;


bool compareCost(const Node &a, const Node &b)
{
    return a.cost < b.cost;
}

int recurssion(int currentMax, Node n, vector<string> fin, vector<string> visitedCities){
    // Equals starting size
    double sizeToGoThrough = 0;
    double totalThrough = 0;
    // Check which is bigger node size
    if(currentMax < (n.size - values[n.id])){
        sizeToGoThrough = currentMax;
    }
    else{
        sizeToGoThrough = n.size - values[n.id];
    }
    // Check if the node is the finish node
    if(find(fin.begin(), fin.end(), n.finishLoc) != fin.end()){
        values[n.id] += sizeToGoThrough;
        return sizeToGoThrough;
    }
    // Checks if the size going through is 0 if so return 0
    else if(sizeToGoThrough == 0){
        return 0;
    }
    // Checks if the new location is the start which returns 0
    else if(find(visitedCities.begin(), visitedCities.end(), n.finishLoc) != visitedCities.end()){
        return 0;
    }
    // Checks if the location has roads away from it
    else if(m.count(n.finishLoc) == 1){
        // Get the paths for the node
        visitedCities.push_back(n.finishLoc);
        vector<Node> nodes = m[n.finishLoc];
        // Support the nodes by cost
        sort(nodes.begin(), nodes.end(), compareCost);
        // Loop through all its paths
        for(int i = 0; i < nodes.size(); i++){
            // Use recurssion
            
            double gotThrough = recurssion(sizeToGoThrough, nodes.at(i), fin, visitedCities);
            // Change for next iteration to send less
            sizeToGoThrough -= gotThrough;
            // Add values for what got through
            values[n.id] += gotThrough;
            totalThrough += gotThrough;
           
        }
    }
    else{
        return 0;
    }
    // Returns the total amount that got through to last recurssion
    return totalThrough;
}

unordered_map<int, double> organizeLogistics(vector<pair<string,double>> start, vector <pair<string,double>> end){
    // Reads the input file
    ifstream input("worldmap.txt");
    int id;
    // Loops until the whole input file has been read
    while(input >> id){
        // Reads the inputs
        string startLoc;
        string finishLoc;
        double size;
        int cost;
        input >> startLoc;
        input >> finishLoc;
        input >> size;
        input >> cost;
      
        // Creates new node and adds it to map based on starting location
        Node newNode = Node{startLoc, finishLoc, size, cost, id};
        if (m.count(startLoc) == 1){
            m[startLoc].push_back(newNode);
        }
        else{
            vector<Node> vec;
            vec.push_back(newNode);
            m[startLoc] = vec;
        }
        // Sets value in unordered map to 0
        values[id] = 0;
    }
    // Gets all the end locations given
    vector<string> endLocations;
    for(int i = 0; i < end.size(); i++){
        endLocations.push_back(end.at(i).first);
    }
    int total = 0;
    // Iterates through all the starting nodes
    for(int i = 0; i < start.size(); i++){
        // Gets first starting location and amount
        pair<string,double> s = start.at(i);
        string sCity = s.first;
        double startingAmount = s.second;
        // Gets the Nodes that lead off from the start
        vector<Node> startCities;
        if(m.count(sCity) == 1){
            startCities = m[sCity];
        }
        // Sorts nodes by the cost
        sort(startCities.begin(), startCities.end(), compareCost);
        // Iterates through the starting nodes
        for(int j = 0; j < startCities.size(); j++){
            // Gets the starting value to go through each node
            int sizeToGoThrough = 0;
            Node n = startCities.at(j);
            // Checks if the startingAmount or the amount that can through is bigger
            if(startingAmount < (n.size - values[n.id])){
                sizeToGoThrough = startingAmount;
            }
            else{
                sizeToGoThrough = n.size - values[n.id];
            }
            // Vector visited cities to handle the possiblity of a loop and the issue of an endless loop causing a segmentation fault
            vector<string> visitedCities;
            visitedCities.push_back(sCity);
            // Use recurssion to get values
            double gotThrough = recurssion(sizeToGoThrough, n, endLocations, visitedCities);
            // Subtract from starting amount for next starting node
            startingAmount -= gotThrough;
            total += gotThrough;
        }
        
        
    }
    return values;
}