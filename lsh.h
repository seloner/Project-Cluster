#ifndef lsh_H_
#define lsh_H_

#include <iostream>
#include "vector"
#include "metrics.h"
#include "clusterStructs.h"
using namespace std;
vector<vector<int>> generateSi(int k, int w, int dimension);
vector<int> *creteHashTable(int hash_table_size, int dimension, vector_struct *vectors_array, unsigned int size, int k, int w, int M, int m, vector<vector<int>> siarray);
vector<int> nearestVectors(vector<vector<vector<int>>> siarrays, int dimension, int k, int w, int M, int m, int L, vector_struct query, int hash_table_size, vector<int> **hashtables,vector_struct *vectors_array,unsigned int size,unsigned int range);
vector<int> bucketRangeSearch(vector_struct *vectors_array,unsigned int size, vector<int> bucket, vector_struct query,unsigned int range);
bool vectorExists(unsigned int index,vector<int> all_indexes);

#endif