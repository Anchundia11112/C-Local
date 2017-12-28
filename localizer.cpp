#include <vector>
#include "localizer.h"
#include "helpers.h"

#include<iostream>
using namespace std;


vector< vector <float> > initialize_beliefs(vector< vector <char> > grid)
{

    float height = grid.size();
    float width = grid[0].size();
    float area = height * width;

    float belief_per_cell = 1.0/area;
    vector< vector <float> > newGrid (height,vector<float> (width,belief_per_cell));   //Creating grid with the specific Belif

    return newGrid;
}


vector< vector <float> > sense(char color, vector< vector <char> > grid,vector< vector <float> > beliefs,float p_hit,float p_miss)
{

    int height = grid.size();
    int width = grid[0].size();

    vector <vector <float> > newGrid = zeros(height,width);

    for(int i = 0; i < height; ++i) {
    	for(int j = 0; j < width; ++j){
    		if(grid[i][j] == color){			//The boolean Flag from python
    			newGrid[i][j] = beliefs[i][j] * p_hit;		//If we land on the appropriate color...multiply by what p_hit is
    		}
    		else{
    			newGrid[i][j] = beliefs[i][j] * p_miss;		//If we land on the appropriate color...multiply by what p_miss is
    		}
    	}

    }
    return normalize(newGrid);
}

vector< vector <float> > move(int dy, int dx, vector < vector <float> > beliefs, float blurring)

{
    int height = beliefs.size();
    int width = beliefs[0].size();
    int new_i;
    int new_j;


    vector< vector <float> >newGrid = zeros(height,width);//Initialize matrix

    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            new_i = ( i + dy + height) % height; //Calc new_i
            new_j = ( j + dx + width) % width; //Calc new_j

            newGrid[new_i][new_j] = beliefs[i][j];  //Fill newGrid with updated beliefs
        }
    }

    return newGrid;
}


