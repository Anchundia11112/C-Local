#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "helpers.h"
#include "debugging_helpers.h"


using namespace std;


vector< vector<float> > normalize(vector< vector <float> > grid) {

	int height = grid.size();
	int width = grid[0].size();
	signed int i;
	signed int j;

	float total = 0.0;

	vector< vector<float> > newGrid = zeros(height,width);

	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){ 			//Getting total Sum
			total += grid[i][j];
		}
	}

	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			newGrid[i][j] = grid[i][j]/total;		//Getting the grid and deviding each element by the total
		}
	}
    return newGrid;
}

vector < vector <float> > blur(vector < vector < float> > grid, float blurring) {

    //Initialize everything

    vector < vector <float> > newGrid ;
    vector < vector <float> >  window;

    int grid_height = grid.size();
    int grid_width = grid[0].size();
    int dy;
    int dx;

    const float center_prob = 1 - blurring;
    const float corner_prob = blurring / 12.0;		//The probabilitiesq...never change
    const float adjacent_prob = blurring / 6.0;

    float mult = 0;
    float new_i = 0;
    float new_j = 0;
    float newVal;

    vector <int> DX = {-1, 0, 1};   //Needed for the "in range(-1,2) from Python
    vector <int> DY = {-1, 0, 1};	//Needed for the "in range(-1,2) from Python

    //create a grid_height by grid_width Matrix

    vector<float>singleRow (grid_height,0);

    for(int col = 0; col < grid_width; ++col){
        newGrid.push_back(singleRow);
    }

    //Create a 3X3 with the following probabilities
    window = { {corner_prob, adjacent_prob, corner_prob},
               {adjacent_prob, center_prob, adjacent_prob},
               {corner_prob, adjacent_prob, corner_prob}
    };

    //Initialize newGrid
    newGrid = zeros(grid_height, grid_width);

    for(int i = 0; i < grid_height; ++i){
    	for(int j = 0; j < grid_width; ++j){
    		newVal = grid[i][j];			//Getting the val from grid that we will be using to get the actual newGrid values

    		for(int k = 0; k < grid_width; ++k){
    			dy = DY[k];

    			for(int l = 0; l < 3; l++){
    				dx = DX[l];
    				mult = window[k][l]; //What to multiply
    				new_i = (i + dy + grid_height) % grid_height;
    				new_j = (j + dx + grid_width) % grid_width;
    				newGrid[new_i][new_j] += newVal * mult;
    			}
    		}

    	}

    }

    return newGrid;
}


/** -----------------------------------------------
#
#
#	You do not need to modify any code below here.
#
#
# ------------------------------------------------- */


/**
    Determines when two grids of floating point numbers
    are "close enough" that they should be considered
    equal. Useful for battling "floating point errors".

    @param g1 - a grid of floats

    @param g2 - a grid of floats

    @return - A boolean (True or False) indicating whether
    these grids are (True) or are not (False) equal.
*/
bool close_enough(vector < vector <float> > g1, vector < vector <float> > g2) {
    unsigned int i, j;
    float v1, v2;
    if (g1.size() != g2.size()) {
        return false;
    }

    if (g1[0].size() != g2[0].size()) {
        return false;
    }
    for (i=0; i<g1.size(); i++) {
        for (j=0; j<g1[0].size(); j++) {
            v1 = g1[i][j];
            v2 = g2[i][j];
            if (abs(v2-v1) > 0.0001 ) {
                return false;
            }
        }
    }
    return true;
}

bool close_enough(float v1, float v2) {
    if (abs(v2-v1) > 0.0001 ) {
        return false;
    }
    return true;
}

/**
    Helper function for reading in map data

    @param s - a string representing one line of map data.

    @return - A row of chars, each of which represents the
    color of a cell in a grid world.
*/
vector <char> read_line(string s) {
    vector <char> row;

    size_t pos = 0;
    string token;
    string delimiter = " ";
    char cell;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());

        cell = token.at(0);
        row.push_back(cell);
    }

    return row;
}

/**
    Helper function for reading in map data

    @param file_name - The filename where the map is stored.

    @return - A grid of chars representing a map.
*/
vector < vector <char> > read_map(string file_name) {
    ifstream infile(file_name);
    vector < vector <char> > map;
    if (infile.is_open()) {
        vector <char> row;

        string line;

        while (std::getline(infile, line)) {
            row = read_line(line);
            map.push_back(row);
        }
    }
    return map;
}

vector < vector <float> > zeros(int height, int width) {
    int i, j;
    vector < vector <float> > newGrid;
    vector <float> newRow;

    for (i=0; i<height; i++) {
        newRow.clear();
        for (j=0; j<width; j++) {
            newRow.push_back(0.0);
        }
        newGrid.push_back(newRow);
    }
    return newGrid;
}

/*
int main() {
    vector < vector < char > > map = read_map("maps/m1.txt");
    show_grid(map);
    return 0;
}

*/
