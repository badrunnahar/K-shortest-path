//
//  YensKpath.h
//  K-shortest path and cost
//
//  Created by Badrun Nahar on 2016-07-13.
//  Copyright © 2016 McGill University. All rights reserved.
//

#include <vector>

using namespace std;

#ifndef YensKpath_h
#define YensKpath_h

void YensKpath(int number_of_node, vector< vector<int> > adjacencymatrix, int source, int destination, int k_paths, vector < vector<int> > * ShortestPaths1,  vector<int>  * TotalCosts1);

#endif /* YensKpath_h */
