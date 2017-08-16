//
//  main.cpp
//  K-shortest path and cost
//
//  Created by Badrun Nahar on 2016-07-11.
//  Copyright © 2016 McGill University. All rights reserved.


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "YensKpath.h"


using namespace std;

int main(int argc, const char * argv[]) {
    
    int source, destination, k_paths;
    string DAG_node_connectivity;

    cout << "Enter the file name of the directed acyclic graph : ";
    cin >> DAG_node_connectivity;
    
    ifstream infile(DAG_node_connectivity);

    
    int number_of_node=0;
    vector<int> index,c1;
    string line;
    int maximum=0;
    
    while (getline(infile, line))
    {
        istringstream iss(line);
        int a,b,c;
        
        if (!(iss >> a >> b >> c  )) { break; } // error
        
        index.push_back(a);
        index.push_back(b);
        c1.push_back(c);
        // process pair (a,b)
        b = max(a,b);
        maximum = max(b,maximum);
        number_of_node=maximum;
       
    }
    
    cout << endl;
    cout << "Number of nodes in the directed acyclic graph (DAG): " << number_of_node << endl;
    
    int AdjacencyMatrix[number_of_node+1][number_of_node+1];
    
    for (int i = 0; i < number_of_node+1; i++)
        for (int j = 0; j < number_of_node+1; j++)
        {AdjacencyMatrix[i][j] = 1000000; // Here, 1000000 means there is no connectivity (infinite cost) between node i & j 
            for (int k=0; k< index.size()/2;k++)
                AdjacencyMatrix[index[2*k]][index[2*k+1]] = c1[k];
        }
    
    cout << endl;
    cout << "DAG edges and their weights: " << endl;
    cout << endl;
    cout << setw(6) << "node1" << setw(6) << "node2" << setw(7) << "weight" << endl;
    cout << "---------------------" << endl;
    for (int i=0; i<c1.size(); i++) 
        cout << setw(6) << index[2*i] << setw(6) << index[2*i+1] << setw(7) << c1[i] << endl;
    cout << "---------------------" << endl;    
    cout << endl;

    cout << "Adjacency Matrix format of the DAG: " << endl;
    for (int i=0; i< number_of_node+1; i++)
    {
        for (int j=0; j< number_of_node+1; j++){
            if (AdjacencyMatrix[i][j] == 1000000 )
                cout << "inf" << "\t";
            else
            cout << AdjacencyMatrix[i][j] << "\t";
           }
        cout << endl;
    }
    //this is convert 2D array to 2D vector. Since the dimensions of the array is only known during the run time, that's why passing 2D array to a function is not possible. It has to be done by using a 2D vector.
    vector<vector<int> > adjacencymatrix;
    for ( int i=0;i< sizeof (AdjacencyMatrix)/sizeof (AdjacencyMatrix[0]);i++)
    {  vector<int> temp;
        for (int j=0;j< sizeof (AdjacencyMatrix[0])/sizeof (AdjacencyMatrix[0][0]);j++)
            temp.push_back(AdjacencyMatrix[i][j]);
        adjacencymatrix.push_back(temp);
        temp.clear();  }
    
    
//    cout << "adjacencymatrix: " << endl;
//    for (int i=0; i< adjacencymatrix.size(); i++)
//    {
//        for (int j=0; j< adjacencymatrix[i].size(); j++)
//            cout << adjacencymatrix[i][j] << "\t";
//        cout << endl;
//    }
    
    cout << endl;
    cout << "Enter source node: " ;
    cin >> source;
    cout << "Enter destination node: " ;
    cin >> destination;
    cout << "Enter the number of k-shortest paths you want to calculate: ";
    cin >> k_paths; 
    
    cout << endl;
    vector< vector<int> > ShortestPaths1;
    vector<int> TotalCosts1;

    YensKpath(number_of_node, adjacencymatrix, source, destination, k_paths, &ShortestPaths1, &TotalCosts1);
        
    for (int i= 0; i<ShortestPaths1.size(); i++)
    { cout << "Path" << i+1 << ": ";
      for (int j=0; j<ShortestPaths1[i].size(); j++)
          cout << ShortestPaths1[i][j]<< " ";
      cout << ";  Path cost: " << TotalCosts1[i] << endl;
    }    
    
    return 0;
}

