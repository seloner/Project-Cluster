#ifndef lsh_H_
#define lsh_H_

#include <iostream>
#include "vector"
#include "metrics.h"
#include "clusterStructs.h"
using namespace std;
vector<vector<int>> generateSi(int k, int w, int dimension);
vector<int> *creteHashTable(int hash_table_size, int dimension, vector_struct *vectors_array, unsigned int size, int k, int w, int M, int m, vector<vector<int>> siarray);

#endif