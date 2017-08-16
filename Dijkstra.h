//
//  Header.h
//  K-shortest path and cost
//
//  Created by Badrun Nahar on 2016-06-29.
//  Copyright © 2016 McGill University. All rights reserved.
//

#include<vector>
using namespace std;

#ifndef Dijkstra_h
#define Dijkstra_h

void Dijkstra (int number_of_node, vector< vector<int> > AdjMatrix, int source, int destination, vector<int> *shortestPath, int *totalCost);

#endif /* Dijkstra_h */
