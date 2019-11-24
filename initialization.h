#ifndef metrics_H_
#define metrics_H_

#include <iostream>
#include <vector>
#include "vector.h"
#include "curves.h"
#include "metrics.h"
#include "dtw.h"
#include <cmath>
#include "clusterStructs.h"

using namespace std;
typedef struct
{
    double start;
    double end;
    vector_struct *vector_struct_ptr;
} probability_space_vector;
typedef struct
{
    double start;
    double end;
    curve *curve_ptr;
} probability_space_curve;
vector<vector_struct> k_means_vector(vector_struct *vectors_array, unsigned int k, unsigned int size);
vector<curve> k_means_curve(vector<curve> curves_array, unsigned int k, unsigned int size);
void random_selection_vector(vector_struct *vectors_array, unsigned int k, unsigned int size, vector<vector_struct> &allCenters);
void random_selection_curves(vector<curve> curves, unsigned int k, unsigned int size, vector<curve> &allCenters);
vector<cluster_curves> init_clusters_curves(unsigned int number_of_clusters);

#endif