/*
 * localizer.h
 *
 *  Created on: Dec 26, 2017
 *      Author: Michael Anchundia
 */

#ifndef LOCALIZER_H_
#define LOCALIZER_H_

#include <vector>
#include "string"


std::vector< std::vector <float> > initialize_beliefs(std::vector< std::vector <char> > grid);

std::vector< std::vector<float> > sense(char color, std::vector< std::vector<char> > grid, std::vector<std::vector<float> > beliefs, float p_hit, float p_miss);

std::vector< std::vector <float> > move(int dy, int dx, std::vector < std::vector <float> > beliefs, float blurring);



#endif /* LOCALIZER_H_ */
