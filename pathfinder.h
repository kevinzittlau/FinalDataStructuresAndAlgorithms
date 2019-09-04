#include <deque>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <cmath>

using namespace std;

// Structure for each node
struct Node{
    int row;
    int column;
    int value;
    vector<char> moves;
};

// Structure to order the priority queue
struct TestNodes {
    bool operator()(Node const & node1, Node const & node2) {
        return node1.value > node2.value;
    }
};



priority_queue<Node, vector<Node>, TestNodes> open;
  // Map to tell if location is still open
  map<pair<int,int>, int> closed;
  // Map to store the values 
  map<pair<int,int>, int> values;

// Variables to represent open, closed, or neither
int OPEN_VALUE = 1;
int CLOSED_VALUE = 2;
int NEITHER_VALUE = 0;

//template<std::size_t rows, std::size_t cols>
int endRow = 0;
int endColumn = 0;

// function to alter value in priority queue
void alterValue(int row, int column, int newValue, vector<char> moves){
    vector<Node> temp;
    // Iterate through the priority queue
    while(open.size() != 0){
        Node top = open.top();
        // Check if the correct node has been found
        if(top.row == row && top.column == column){
            // Update the values
            top.value = newValue;
            top.moves = moves;
            open.push(top);
            break;
        }
        else{
            // Store in temp if not
            open.pop();
            temp.push_back(top);
        }
    }
    // Push all values from temp back in the priority queue
    for(int i = 0; i < temp.size(); i++){
        open.push(temp.at(i));
    }
}

// Function to test neighbor
void testNeighbor(Node current, char neighborChar, int row, int col, char newMove){
    int bonus = 1;
    // Use manhattan a* algorithm
    int mDistance = abs(endRow - row) + abs(endColumn - col);
    // Check if there is a bonus which would be gold or a bomb
    if(neighborChar == 'b'){
        bonus = 20;
    }
    else if(neighborChar == 'g'){
        bonus = -4;
    }
    // Get the current set of moves up until this point
    vector<char> moves = current.moves;
    // Adds the new move
    moves.push_back(newMove);
    // Checks if it is a wall
    if(neighborChar != 'w'){
        // Checks if this node needs to be updated
        if(current.value + bonus + mDistance < values.at(make_pair(row, col)) && closed.at(make_pair(row,col)) == OPEN_VALUE){
            // Updates the node
            values.at(make_pair(row, col)) = current.value + bonus + mDistance;
            alterValue(row, col, current.value + bonus + mDistance, moves);
        }
        // Checks if node needs to be added
        else if(closed.at(make_pair(row, col)) == NEITHER_VALUE){
            // Adds the node to the priority queue and declares it open
            closed.at(make_pair(row, col)) = OPEN_VALUE;
            values.at(make_pair(row, col)) = current.value + bonus + mDistance;
            open.push(Node{row, col, current.value + bonus + mDistance, moves});
            
        }
    }
}


template<std::size_t rows, std::size_t cols> 
vector<char> pathfinder(char (&maze)[rows][cols]){
    int startingRow = 0;
    int startingColumn = 0;


    // Iterate through the map
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            // If the map location is an s
            if(maze[i][j] == 's'){
                // Save coordinates for startingRow and startingColumn
                startingRow = i;
                startingColumn = j;
            }
            // If the map location is an f
            else if(maze[i][j] == 'f'){
                // Store the location as the endRow and column
                endRow = i;
                endColumn = j;
                values.insert(make_pair(make_pair(i, j), 10000));
                closed.insert(make_pair(make_pair(i, j), NEITHER_VALUE));
            }
            else{
                // Set the value of the location to 10000 and that it is neither open or closed
               values.insert(make_pair(make_pair(i, j), 10000));
                closed.insert(make_pair(make_pair(i, j), NEITHER_VALUE));
            }
        }
    }
    // Push the starting node onto the priority queue
    // Use Manhattan a* for starting value, vector<char> represents the movements
    open.push(Node{startingRow, startingColumn, abs(endRow - startingRow) + abs(endColumn - startingColumn), vector<char>()});
    // Set starting value of starting location to neither
    closed.insert(make_pair(make_pair(startingRow, startingColumn), NEITHER_VALUE));
    // Set starting value to 0
    values.insert(make_pair(make_pair(startingRow, startingColumn), 0));
    // Iterate through the map again
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            // Get the top node from the priority queue
            Node current = open.top();
            // Use manhattan a* algorithm again
             int mDistance = abs(endRow - current.row) + abs(endColumn - current.column);
             // Subtract the manhattan a* distance
            current.value -= mDistance;
            // If the size does not equal 0 remove it from priority queue
            if(open.size() != 0){
                open.pop();
            }
            // Set value of current node to closed
            closed.at(make_pair(current.row, current.column)) = CLOSED_VALUE;
            // Check if it is the end
            if(maze[current.row][current.column] == 'f'){
                return current.moves;
            }
            // Check for out of bounds
            // Check the character that is up
            if(current.row - 1 >= 0){
                char left = maze[current.row - 1][current.column];
                // Check to see if it needs to be in the queue or updated
                testNeighbor(current, left, current.row - 1, current.column, 'U');
            }
            // Check the character that is down
            if(current.row + 1 < rows){
                char right = maze[current.row + 1][current.column];
                // Check to see if it needs to be in the queue or updated
                testNeighbor(current, right, current.row + 1, current.column, 'D');
            }
            // Check the character that is right
            if(current.column + 1 < cols){
                // Check to see if it needs to be in the queue or updated
                char up = maze[current.row][current.column + 1];
                testNeighbor(current, up, current.row, current.column + 1, 'R');
            }
            // Check the character that is left
            if(current.column - 1 >= 0){
                char down = maze[current.row][current.column - 1];
                // Check to see if it needs to be in the queue or updated
                testNeighbor(current, down, current.row, current.column - 1, 'L');
            }

        }
        
     }
     vector<char> noPath;
     noPath.push_back('\0');
     return noPath;

}




