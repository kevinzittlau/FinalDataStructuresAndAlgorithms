
#include "pathfinder.h"

using namespace std;

int main(){
    
    char arr[15][20] ={{'s','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},{'e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},{'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','w','w'},{'e','w','e','w','b','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},{'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','g','g'},{'e','w','e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},{'e','w','e','w','e','w','w','w','w','w','w','w','e','e','e','e','e','w','g','g'},{'e','w','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','w','w','e'},{'e','w','e','w','e','e','b','e','e','e','w','w','e','w','e','e','e','e','w','e'},{'e','w','e','w','e','g','b','f','e','e','w','e','e','w','e','w','w','e','w','e'},{'e','w','e','w','e','e','b','e','g','g','w','e','e','w','e','e','w','e','w','e'},{'e','w','e','w','e','e','e','e','e','e','w','w','e','w','e','e','w','e','e','e'},{'e','w','e','w','e','e','e','e','e','e','e','w','e','w','e','e','w','e','e','e'},{'e','w','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','e','e','e'},{'e','w','e','w','e','e','e','e','e','e','w','e','e','e','e','e','e','e','e','e'},};
    vector<char> path = pathfinder(arr);

    int locationRows = 0;
    int locationCols = 0;
    
    for(int i = 0; i < path.size(); i++){
        if(path.at(i) == 'D'){
            locationRows += 1;
        }
        else if(path.at(i) == 'U'){
            locationRows -= 1;
        }
        else if(path.at(i) == 'R'){
            locationCols += 1;
        }
        else if(path.at(i) == 'L'){
            locationCols -= 1;
        }
        arr[locationRows][locationCols] = '-';
    }
    for(int i = 0; i < 15; i++){
        cout << '\n';
        for(int j = 0; j < 20; j++){
            cout << arr[i][j] << " ";
        }
    }
    return 0;
}