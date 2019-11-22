#ifndef metrics_H_
#define metrics_H_

#include <iostream>
#include <vector>
#include "vector.h"
#include "curveStructs.h"
#include "metrics.h"

using namespace std;
vector<vector_struct> k_means_vector(vector_struct *vectors_array, unsigned int k, unsigned int size);
void random_selection_vector(vector_struct *vectors_array, unsigned int k, unsigned int size, vector<vector_struct> &allCenters);
void random_selection_curves(vector<curve> curves, unsigned int k, unsigned int size, vector<curve> &allCenters);

#endif