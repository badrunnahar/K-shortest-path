# K-shortest-path

K-shortest-path take a directed acyclic graph (DAG) as one of the inputs and returns the list of K first shortest paths and 
their costs from a given source node to a destination node. The original algorithm is based on Yen's K-shortest Path algorithm 
(1971) which calls a slightly modified version of Dijkstra's algorithm implemented by Xiaodong Wang 2004.

ExampleGraph contains two example DAGs: DAG1.txt and DAG2.txt. Each line of these text files contain three numbers. The first 
two numbers represent two connected nodes of an edge and the third number represents the corresponding edge cost.  
 
Following is an example of calculating k-shortest paths by using these source codes.
First compile the codes as follows and then enter the name of the DAG's file and, source and destination nodes. 

$ g++  main.cpp  Dijkstra.cpp  Dijkstra.h  YensKpath.cpp  YensKpath.h 
$ ./a.out 
==> Enter the file name of the directed acyclic graph : ExampleGraph/DAG1.txt 

This will give the following output and then ask for source and destination nodes: 

Number of nodes in the directed acyclic graph (DAG): 6

DAG edges and their weights: 

 node1 node2 weight
---------------------
     1     2      5
     1     3     10
     1     4     15
     1     5     20
     2     1      5
     2     3     10
     2     6      5
     3     1     10
     3     2     10
     3     4     15
     3     6     10
     4     1     15
     4     3     15
     4     5     20
     4     6     15
     5     1     20
     5     4     20
     5     6     20
---------------------

Adjacency Matrix format of the DAG: 
inf inf inf inf inf inf inf 
inf inf 5 10  15  20  inf 
inf 5 inf 10  inf inf 5 
inf 10  10  inf 15  inf 10  
inf 15  inf 15  inf 20  15  
inf 20  inf inf 20  inf 20  
inf inf inf inf inf inf inf 

==> Enter source node: 4
==> Enter destination node: 6
==> Enter the number of k-shortest paths you want to calculate: 5

These entries will list upto 5th shortest paths between nodes 4 and 6, and the corresponding path costs.

Path1: 4 6 ;  Path cost: 15
Path2: 4 3 6 ;  Path cost: 25
Path3: 4 1 2 6 ;  Path cost: 25
Path4: 4 3 2 6 ;  Path cost: 30
Path5: 4 1 3 2 6 ;  Path cost: 40
