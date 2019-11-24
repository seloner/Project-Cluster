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
typedef struct Cluster_Curves
{
    curve *centerOfCluster;
    vector<curve *> cluster_curves;
} cluster_curves;

typedef struct Vector_Curves
{
    vector_struct *centerOfCluster;
    vector<vector_struct *> cluster_vectors;
} vector_curves;

//about points
//TODO
#endif