#ifndef lsh_H_
#define lsh_H_

#include <iostream>
#include "vector"
#include "curves.h"
#include "metrics.h"
#include "clusterStructs.h"
#include "grid_functions.h"
#include "dtw.h"

using namespace std;

//this struct is for RANDOM LSH PAM CURVES
typedef struct dtwInfo
{
    int id;
    double distance;

} dtwInfo;

vector<vector<int>> generateSi(int k, int w, int dimension);
vector<int> *creteHashTable(int hash_table_size, int dimension, vector_struct *vectors_array, unsigned int size, int k, int w, int M, int m, vector<vector<int>> siarray);
vector<int> nearestVectors(vector<vector<vector<int>>> siarrays, int dimension, int k, int w, int M, int m, int L, vector_struct query, int hash_table_size, vector<int> **hashtables,vector_struct *vectors_array,unsigned int size,unsigned int range);
vector<int> bucketRangeSearch(vector_struct *vectors_array,unsigned int size, vector<int> bucket, vector_struct query,unsigned int range);
bool vectorExists(unsigned int index,vector<int> all_indexes);

vector<int> nearestCurves(vector<vector<vector<int>>> siarrays, vector<int> dimensionsQueryTable, int k, int w, int M, int m, curve queryCurves, vector<curve> allCurves, int L, grid_vectors *grid_vectors_query, int hash_table_size, vector<int> **hashtables);
vector<int> *creteHashTablev2(int hash_table_size, int dimension, vector<vector<double>> vectors, int k, int w, int M, int m, vector<vector<int>> siarray);
unsigned int gFunctionv2(vector<vector<int>> siarrays, int dimension, int k, int w, int M, int m, vector<double> xiArray);
unsigned int hFunctionv2(vector<int> siArray, int dimensions, int W, int M, int m, vector<double> xiArray);
vector<int> dtwNearestInBucket(vector<int> bucket, vector<curve> curves, int threshold, curve query);

#endif