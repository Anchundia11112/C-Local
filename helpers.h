/*
 * helpers.h
 *
 *  Created on: Dec 26, 2017
 *      Author: Michael Anchundia
 */

#ifndef HELPERS_H_
#define HELPERS_H_

#include<string>


#include <vector>


std::vector< std::vector<float> > normalize(std::vector< std::vector <float> > grid);
std::vector < std::vector <float> > blur(std::vector < std::vector < float> > grid, float blurring);
std::vector <char> read_line(std::string s);
std::vector < std::vector <char> > read_map(std::string file_name);
std::vector < std::vector <float> > zeros(int height, int width);

bool close_enough(float v1, float v2);

bool close_enough(std::vector < std::vector <float> > g1, std::vector < std::vector <float> > g2);


#endif /* HELPERS_H_ */
