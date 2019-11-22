#ifndef CLUSTERSTRUCTS_H_
#define CLUSTERSTRUCTS_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "curves.h"

#define CONFLINES 4

using namespace std;

typedef struct Cluster
{
    int number_of_clusters;
    int number_of_grids;
	int number_of_vector_hash_tables;
    int number_of_vector_hash_functions;
} cluster;

//about curves
typedef struct ClusterNodeCurves
{
    curve *machingCurve;
} clusternodecurves;

typedef struct ClusterArrayCurves
{
    clusternodecurves centerOfCluster;
    vector<clusternodecurves> nodes;
} clusterarraycurves;

//about points
//TODO
#endif