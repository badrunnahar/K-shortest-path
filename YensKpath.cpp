//
//  YensKpath.cpp
//  K-shortest path and cost
//
//  Created by Badrun Nahar on 2016-07-11.
//  Copyright © 2016 McGill University. All rights reserved.


/********************************************************************************************************/
// YensKpath returns the K first shortest paths from a source node to a destination node of a directed acyclic  
// graph. It returns the list of K shortest paths and their costs. The original algorithm is based on Yen's 
// K-shortest Path algorithm (1971) which calls a slightly modified version of Dijkstra's algorithm implemented
// by Xiaodong Wang 2004.
//  This source code has been written in C++ based on the MATLAB implementation done by the author Meral Shirazipour  
// (http://www.mathworks.com/matlabcentral/fileexchange/32513-k-shortest-path-yen-s-algorithm). 
/********************************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Dijkstra.h"


using namespace std;


class Path_info{
public:
    int path_no;
    vector<int> path_nodes;
    int path_cost;
};


void YensKpath(int number_of_node, vector< vector<int> > adjacencymatrix, int source, 
                int destination, int k_paths, vector < vector<int> > * ShortestPaths1,  vector<int>  * TotalCosts1) {
    
  /*
    cout << "adjacencymatrix: " << endl;
    for (int i=0; i< adjacencymatrix.size(); i++)
    {
        for (int j=0; j< adjacencymatrix[i].size(); j++)
            cout << adjacencymatrix[i][j] << "\t";
        cout << endl;
    }
    */
     
    
    vector<int> path;
    int cost;
    
    Dijkstra (number_of_node, adjacencymatrix, source, destination, &path, &cost);
    
    /*  cout<< " Shortest Path: ";
     for(int i=0; i<path.size(); i++)
     cout << path[i] << " ";
     cout << endl;
     cout << cost << endl; */
    
    vector< vector<int> > temp_adjacencymatrix;
    vector< vector<int> > ShortestPaths;
    vector<int> TotalCosts;
    
    vector<Path_info> P;
    vector<Path_info> X;
    
    int path_number = 1;
    vector<int> S;
    
    Path_info path1;
    
    
    if (path.empty())
        cout << "There is no path between source node and destination node." << endl;
    else {
        {
            path1.path_no = path_number;
            path1.path_nodes = path;
            path1.path_cost = cost;
            
        }
        
        X.push_back(path1);
        P.push_back(path1);
        
        /*
         cout << X[0].path_cost << "; Path: ";
         for (int i=0; i<X[0].path_nodes.size(); i++)
         cout << X[0].path_nodes[i] << " "; */
        
        S.push_back(path[0]);
        
        
        ShortestPaths.push_back(path);
        TotalCosts.push_back(cost);
        
        
        int k=0;
        int current_P = path_number;
        
        /***********************/
        while (k<(k_paths-1) && X.size() !=0){
            //remove current path from paths
            for (int i=0; i< X.size(); i++)
            {   if (X[i].path_no == current_P)
            {
                
                X.erase(X.begin()+i);
                break;
            }
            }
            
            /***********************/
            
            vector<int> P_;
            int w, w_index_in_path=0;
            P_.clear();
            P_ = P[current_P-1].path_nodes;
            w = S[current_P-1];
            
            
            for (int i=0; i<P_.size();i++)
            {if (w == P_[i])
                w_index_in_path = i;}
            
            
            int index_dev_vertex=0;
            int v;
            
            for (index_dev_vertex = w_index_in_path; index_dev_vertex <(P_.size()-1); index_dev_vertex++)
            {            
            for (int i=0; i< number_of_node+1; i++)
               {vector<int> temp;
                    for (int j=0; j< number_of_node+1; j++)
                     //temp_AdjMatrix[i][j] = adjacencymatrix[i][j];
                        temp.push_back(adjacencymatrix[i][j]);
                temp_adjacencymatrix.push_back(temp);
                temp.clear();}
            
                //Remove vertices in P before index_dev_vertex and there incident edges
                for (int i=0; i<=(index_dev_vertex-1); i++ )
                { v = P_[i];
                    for (int j=0; j<number_of_node+1;j++ ) //since adjacency matrix is a square matrix only one for loop for both temp_AdjMatrx
                    {
                        temp_adjacencymatrix[v][j] = 1000000;
                        temp_adjacencymatrix[j][v] = 1000000;
                    }
                }
                
                //remove incident edge of v if v is in shortestPaths (K) U P_  with similar sub_path to P_....
                vector< vector<int> > SP_sameSubPath;
                vector<int> temp,temp1;
                
                SP_sameSubPath.clear();
                SP_sameSubPath.push_back(P_);
                
                for (int i =0; i<=(ShortestPaths.size()-1);i++)
                    if (ShortestPaths[i].size() > index_dev_vertex+1)
                        for (int j = 0; j<=index_dev_vertex; j++)
                            for (int m=0; m<=index_dev_vertex; m++)
                                if ( P_[j] == ShortestPaths[i][m])
                                    SP_sameSubPath.push_back(ShortestPaths[i]);


                int v_ , next;
                v_ = P_[index_dev_vertex];
                for (int j=0; j< SP_sameSubPath.size(); j++)
                {
                    next = SP_sameSubPath[j][index_dev_vertex+1];      
                    temp_adjacencymatrix[v_][next] = 1000000;
                }
             
                
                // get the cost of the sub path before deviation vertex v
                vector <int> sub_P;
                for (int i=0; i <= index_dev_vertex; i++)
                    sub_P.push_back(P_[i]);
                
                
                int cost_sub_P = 0;
                for (int i=0; i< (sub_P.size()-1); i++)
                    cost_sub_P = cost_sub_P + adjacencymatrix[sub_P[i]][sub_P[i+1]];
                
                
                vector<int> dev_p;
                int c;
                Dijkstra(number_of_node,temp_adjacencymatrix, P_[index_dev_vertex], destination, &dev_p, &c);
                
                if (!dev_p.empty())
                {  
                    path_number = path_number + 1; 
                    Path_info temp;
                    temp.path_no = path_number;
                    
                    for (int i=0; i<(sub_P.size()-1); i++ )
                        temp.path_nodes.push_back(sub_P[i]);
                    
                    for (int i=0; i<dev_p.size(); i++)
                        temp.path_nodes.push_back(dev_p[i]);
                    
                    temp.path_cost = cost_sub_P + c;
                    
                    P.push_back(temp);
                    S.push_back(P_[index_dev_vertex]);
                    X.push_back(temp);    
                }

                else
                    cout << "" ;
                
            }//for index_dev_vertex
            
            
            /*************************************/
            //Step necessary otherwise if k is bigger than number of possible paths
            //the last results will get repeated !
            
            if (X.size() > 0)
                
            { int shortestXCost, shortestX;
                vector<int> shortestXpath;
                
                shortestXCost = X[0].path_cost;
                shortestX = X[0].path_no;
                
                //for(int i =0; i<X[0].path_nodes.size(); i++)
                //shortestXpath.push_back(X[0].path_nodes[i]);
                
                for (int i=1; i<X.size(); i++)
                { if (X[i].path_cost < shortestXCost)
                    
                { shortestX = X[i].path_no; //  fix this line
                    shortestXCost = X[i].path_cost; // fix this line
                }
                }
                
                current_P = shortestX;
                /***************/
                k = k + 1;
                //vector<int> temp2;
                //for(int i=0; i< P[current_P].path_nodes.size();i++)
                //  temp2.push_back(P[current_P].path_nodes[i]);
                
                ShortestPaths.push_back(P[current_P-1].path_nodes);
                TotalCosts.push_back(P[current_P-1].path_cost);
                
            }
            else
                cout << "";
            
        }//while
    }//if path.empty()
    
    
    
//    for (int i= 0; i<ShortestPaths.size(); i++)
//    { cout << "Path" << i+1 << ": ";
//        for (int j=0; j<ShortestPaths[i].size(); j++)
//            cout << ShortestPaths[i][j]<< " ";
//        cout << ";  Path cost: " << TotalCosts[i] << endl;
//    }
    
    *ShortestPaths1 = ShortestPaths;
    *TotalCosts1  = TotalCosts;    
    
}

