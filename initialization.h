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
vector<cluster_vectors> k_means_vector(vector_struct *vectors_array, unsigned int k, unsigned int size);
vector<cluster_curves> k_means_curve(vector<curve> *curves_array, unsigned int k, unsigned int size);
vector<cluster_vectors> random_selection_vector(vector_struct *vectors_array, unsigned int k, unsigned int size);
vector<cluster_curves> random_selection_curves(vector<curve> *curves_array, unsigned int k, unsigned int size);
vector<cluster_curves> init_clusters_curves(unsigned int number_of_clusters);
vector<cluster_vectors> init_clusters_vectors(unsigned int number_of_clusters);

#endif