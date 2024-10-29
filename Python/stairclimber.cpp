/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Alexandra Anthony
 * Date        : Ocober 5, 2024
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    if (num_stairs==0) {
        return {{}};
    }

    vector<vector<int>> ways; 

    // Try taking 1, 2, or 3 steps
    if (num_stairs >= 1) {
        vector<vector<int>> result=get_ways(num_stairs - 1);  // Subtract 1 
        for (auto& way : result) {
            way.insert(way.begin(), 1);  // Add 1 
            ways.push_back(way);
        }

    }
    if (num_stairs >= 2) {
        vector<vector<int>> result=get_ways(num_stairs - 2);  // Subtract 2 
        for (auto& way : result) {
            way.insert(way.begin(), 2);  // Add 2 t
            ways.push_back(way);
        }


    }
    if (num_stairs >= 3) {
        vector<vector<int>> result=get_ways(num_stairs - 3);  // Subtract 3 
        for (auto& way : result) {
            way.insert(way.begin(), 3);  // Add 3 to each 
            ways.push_back(way);
        }


    }

    return ways;  // Return all possible ways to climb the stairs
}



void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.


    
    int num_ways = ways.size();
    cout << num_ways << (num_ways==1 ? " way" : " ways") << " to climb the stairs." << endl;
    
    for (int i=0; i<num_ways; ++i) {
        cout << i + 1 << ". [";
        for (size_t j=0; j<ways[i].size(); ++j) {
            cout << ways[i][j];
            if (j != ways[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}


int main(int argc, char * const argv[]) {



    if (argc != 2) {
        cout<< "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    int num_stairs;
    try {


        num_stairs = stoi(argv[1]);  // Convert input to integer
    } catch (...) {
        cout<< "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    if (num_stairs <= 0) {
        cout<< "Error: Number of stairs must be a positive integer." <<endl;
        return 1;
    }
    vector<vector<int>> ways=get_ways(num_stairs);
    display_ways(ways);
    return 0;
}

